#pragma once

#include <stack>
#include <mutex>
#include <exception>
#include <condition_variable>

namespace NBT
{
	template <typename T>
	class ThreadSafeStack
	{
	public:
		ThreadSafeStack() = default;

		ThreadSafeStack(const ThreadSafeStack& other)
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_Stack = other.m_Stack;
		}

		ThreadSafeStack& operator=(const ThreadSafeStack&) = delete;

		void push(T value)
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_Stack.push(std::move(value));
			m_Condition.notify_one();
		}

		void wait_and_pop(T& val)
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_Condition.wait(lock, [this]{ return !m_Stack.empty(); });
			val = std::move(m_Stack.top());
			m_Stack.pop();
		}

		std::shared_ptr<T> wait_and_pop()
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_Condition.wait(lock, [this]{ return !m_Stack.empty(); });
			std::shared_ptr<T> res(std::make_shared<T>(std::move(m_Stack.top())));
			m_Stack.pop();
			return res;
		}

		bool try_pop(T& val)
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			if (m_Stack.empty())
				return false;
			val = std::move(m_Stack.top());
			m_Stack.pop();
			return true;
		}

		std::shared_ptr<T> try_pop()
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			if (m_Stack.empty())
				return nullptr;
			std::shared_ptr<T> res(std::make_shared<T>(std::move(m_Stack.top())));
			m_Stack.pop();
			return res;
		}

		[[nodiscard]] bool empty() const
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			return m_Stack.empty();
		}

	private:
		std::stack<T> m_Stack;
		mutable std::mutex m_Mutex;
		std::condition_variable m_Condition;
	};
}