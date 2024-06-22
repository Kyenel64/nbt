#pragma once

#include <thread>
#include "ThreadSafeQueue.h"

namespace NBT
{
	class ThreadPool
	{
	public:

	private:
		std::atomic_bool m_Done;
		ThreadSafeQueue<std::function<void()>> m_WorkQueue;


	};
}