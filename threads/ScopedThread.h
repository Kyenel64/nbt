#pragma once

#include <thread>

namespace NBT
{
	class ScopedThread
	{
	public:
		ScopedThread(std::thread thread)
				: m_Thread(std::move(thread))
		{
			if (!m_Thread.joinable())
				std::logic_error("No thread");
		}
		~ScopedThread()
		{
			m_Thread.join();
		}

		// Disable copy constructor and copy assignment
		ScopedThread(ScopedThread const&) = delete;
		ScopedThread& operator=(ScopedThread const&) = delete;
	private:
		std::thread m_Thread;
	};
}
