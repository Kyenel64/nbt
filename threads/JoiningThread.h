#pragma once

#include <thread>

namespace NBT
{
	class JoiningThread
	{
	public:
		JoiningThread() noexcept = default;

		template<typename Callable, typename... Args>
		explicit JoiningThread(Callable&& func, Args&&... args)
				: m_Thread(std::thread(std::forward<Callable>(func), std::forward<Args>(args)...)) {}

		explicit JoiningThread(std::thread t) noexcept : m_Thread(std::move(t)) {}
		JoiningThread(JoiningThread&& other) noexcept : m_Thread(std::move(other.m_Thread)) {}

		~JoiningThread() noexcept
		{
			if (m_Thread.joinable())
				m_Thread.join();
		}

		JoiningThread& operator=(JoiningThread&& other) noexcept
		{
			if (m_Thread.joinable())
				m_Thread.join();
			m_Thread = std::move(other.m_Thread);
			return *this;
		}

		JoiningThread& operator=(std::thread other) noexcept
		{
			if (m_Thread.joinable())
				m_Thread.join();
			m_Thread = std::move(other);
			return *this;
		}

		void swap(JoiningThread& other) { m_Thread.swap(other.m_Thread); }
		void join() { m_Thread.join(); }
		void detach() { m_Thread.detach(); }

		[[nodiscard]] bool joinable() const { return m_Thread.joinable(); }
		[[nodiscard]] std::thread::id get_id() const { return m_Thread.get_id(); }
		[[nodiscard]] std::thread& get_thread() { return m_Thread; }
		[[nodiscard]] const std::thread& get_thread() const { return m_Thread; }

	private:
		std::thread m_Thread;
	};
}
