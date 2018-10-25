#include "ThreadPool.h"

namespace alsus
{

	ThreadPool::ThreadPool()
		: _running(false), _max_queue_size(0)
	{
		
	}

	ThreadPool::~ThreadPool()
	{
	}

	void ThreadPool::SetMaxQueueSize(size_t size)
	{
		_max_queue_size = size;
	}
	
	void ThreadPool::Start(int threads_numbers)
	{
		if (threads_numbers > 0)
		{
			_threads.reserve(threads_numbers);
			_running = true;
			for (int i = 0; i < threads_numbers; i++)
			{
				_threads.push_back(std::thread(std::bind(&ThreadPool::ThreadRun, this)));
			}
		}
	}
	
	void ThreadPool::Stop()
	{
		_running = false;
		_not_empty_cv.notify_all();

		for (auto &t : _threads)
		{
			t.join();
		}
		
	}
	
	void ThreadPool::Execute(const Task & task)
	{
		if (_threads.empty())
		{
			task();
		}
		else
		{
			std::unique_lock<std::mutex> lck(_mtx);
			while (IsFull())
			{
				_not_full_cv.wait(lck);
			}

			_queue.push_back(task);
			_not_empty_cv.notify_one();
		}
	}
	
	bool ThreadPool::IsFull()
	{

		return (_queue.size() >= _max_queue_size);
	
	}
	
	void ThreadPool::ThreadRun()
	{
		while (_running)
		{
			Task  task;
			{
				std::unique_lock<std::mutex> lck(_mtx);
				while (_queue.empty() && _running)
				{
					_not_empty_cv.wait(lck);
				}
				if(!_queue.empty())
				{
					task = _queue.front();
					_queue.pop_front();
					_not_full_cv.notify_one();
				}
			}
			if (task)
			{
				task();
			}
		}
	}

	size_t ThreadPool::QueueSize()
	{
		std::lock_guard<std::mutex> lck(_mtx);

		return _queue.size();
	}
}
