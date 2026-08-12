#pragma once
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <memory>
#include <vector>

namespace amp {
	class command {
	public:
		virtual ~command() = default;
		virtual bool run() { return true; }
		virtual void quit() {}
		virtual void force_quit() {}
	};
	class repeat_cmd : public command {
	public:
		template<typename T>
		explicit repeat_cmd(T&& inner_cmd)
		    : inner(std::make_unique<std::decay_t<T>>(
		          std::forward<T>(inner_cmd))) {}

		void stop() { stopped = true; }

		bool run() override {
			if (stopped) return true; // Tell scheduler to remove me
			inner->run();             // Run the wrapped command
			return false;             // Keep repeating
		}

	private:
		std::unique_ptr<command> inner;
		bool stopped = false;
	};
	class group_repeat_cmd : public command {
	public:
		template<typename... Ts>
		explicit group_repeat_cmd(Ts&&... cmds) {
			// Fold expression over the argument pack
			(add_one(std::forward<Ts>(cmds)), ...);
		}

		void stop() { stopped = true; }

		bool run() override {
			if (stopped)
				return true; // tell scheduler to remove this whole group

			for (auto& c : commands) {
				c->run(); // ignore inner return values; we control lifetime
			}
			return false; // keep repeating
		}

	private:
		std::vector<std::unique_ptr<command>> commands;
		bool stopped = false;

		template<typename T>
		void add_one(T&& cmd) {
			using U = std::decay_t<T>;
			static_assert(
			    std::is_base_of_v<command, U>,
			    "group_repeat_cmd can only contain types derived from command");

			// Create a unique_ptr<command> that owns a U*
			commands.emplace_back(
			    std::unique_ptr<command>(new U(std::forward<T>(cmd))));
		}
	};

	class Scheduler {
	public:
		template<typename T, class... Args>
		T& enqueue(Args&&... args) {
			static_assert(std::is_base_of<command, T>::value,
			              "Cmd must derive from command");
			auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
			T& ref = *ptr;
			schedule.emplace_back(
			    std::move(ptr)); // commands is vector<unique_ptr<command>>
			return ref;
		}

		bool tick() {
			if (schedule.empty()) { return false; }
			command* cmd = schedule.front().get();
			// std::cout << "ticking" << "\n";
			// std::cout << schedule.size() << "\n";

			const bool done = cmd->run();

			if (done) {
				cmd->quit();
				schedule.pop_front();
				// gpsRefinerTask(gps);

				tick();
			}
			return !schedule.empty();
		};
		auto get_current() { return schedule.front().get(); }

		void move_to_back() {
			if (schedule.empty()) return;
			schedule.emplace_back(std::move(schedule.front()));
			schedule.front()->quit();
			schedule.pop_front();
		}
		void move_back(int amount) {

			schedule.emplace(schedule.begin() + amount,
			                 std::move(schedule.front()));
			schedule.front()->quit();

			schedule.pop_front();
		}
		void move_to_front() {
			if (schedule.empty()) return;
			schedule.back()->force_quit();

			schedule.emplace_front(std::move(schedule.back()));

			schedule.pop_back();
		}
		void force_quit_current() {
			if (schedule.empty()) return;
			schedule.front()->force_quit();
			schedule.pop_front();
		}

		bool empty() const { return schedule.empty(); }
		void clear() {
			while (!schedule.empty())
				force_quit_current();
		}

	private:
		std::deque<std::unique_ptr<command>> schedule;
	};
}