#pragma once

#include <queue>
#include <mutex>
#include <exception>
#include <condition_variable>

namespace NBT
{
	template <typename T>
	class ThreadSafeQueue
	{
	public:
		ThreadSafeQueue() = default;

		ThreadSafeQueue(const ThreadSafeQueue& other)
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_Queue = other.m_Queue;
		}

		ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

		void push(T value)
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_Queue.push(std::move(value));
			m_Condition.notify_one();
		}

		void wait_and_pop(T& val)
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_Condition.wait(lock, [this]{ return !m_Queue.empty(); });
			val = std::move(m_Queue.front());
			m_Queue.pop();
		}

		std::shared_ptr<T> wait_and_pop()
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_Condition.wait(lock, [this]{ return !m_Queue.empty(); });
			std::shared_ptr<T> res(std::make_shared<T>(std::move(m_Queue.front())));
			m_Queue.pop();
			return res;
		}

		bool try_pop(T& val)
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			if (m_Queue.empty())
				return false;
			val = std::move(m_Queue.front());
			m_Queue.pop();
			return true;
		}

		std::shared_ptr<T> try_pop()
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			if (m_Queue.empty())
				return nullptr;
			std::shared_ptr<T> res(std::make_shared<T>(std::move(m_Queue.front())));
			m_Queue.pop();
			return res;
		}

		[[nodiscard]] bool empty() const
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			return m_Queue.empty();
		}

	private:
		std::queue<T> m_Queue;
		mutable std::mutex m_Mutex;
		std::condition_variable m_Condition;
	};
}