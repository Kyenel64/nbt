#pragma once

#include <thread>

namespace nbt
{
	class scoped_thread
	{
	public:
		scoped_thread(std::thread thread)
				: m_Thread(std::move(thread))
		{
			if (!m_Thread.joinable())
				std::logic_error("No thread");
		}
		~scoped_thread()
		{
			m_Thread.join();
		}

		// Disable copy constructor and copy assignment
		scoped_thread(scoped_thread const&) = delete;
		scoped_thread& operator=(scoped_thread const&) = delete;
	private:
		std::thread m_Thread;
	};
}
