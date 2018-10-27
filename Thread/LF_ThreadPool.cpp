#include "LF_ThreadPool.h"
#include <iostream>


namespace alsus
{
	LF_ThreadPool::LF_ThreadPool() : _running(false), _new_leader(false)
	{
	}


	LF_ThreadPool::~LF_ThreadPool()
	{
	}

	void LF_ThreadPool::Execute(const Task &task)
	{
		std::lock_guard<std::mutex> lck(_tasks_mtx);
		_tasks.push_back(task);
		_task_cv.notify_one();
	}

	void LF_ThreadPool::Start(int thread_numbers)
	{
		_threads.reserve(thread_numbers);
		
		_running = true;

		for (int i = 0; i < thread_numbers; i++)
		{
			_threads.push_back(std::thread(std::bind(&LF_ThreadPool::ThreadRun, this)));
		}
		
		//care about this
		PromoteNewLeader();
		
	}

	void LF_ThreadPool::Stop()
	{
		_running = false;

		for (auto & t : _threads)
		{
			t.join();
		}

	}

	void LF_ThreadPool::ThreadRun()
	{
		while (_running)
		{
			TryToLeader();

			//select epoll poll handle event block
			{
				std::unique_lock<std::mutex> lck(_tasks_mtx);
				while (_tasks.empty() && _running)
				{
					_task_cv.wait(lck);
				}
			}

			Task task;
			{
				std::lock_guard<std::mutex> lck(_tasks_mtx);
				if (!_tasks.empty())
				{
					task = _tasks.front();
					_tasks.pop_front();
				}
			}
			PromoteNewLeader();

			//process handle event
			PorcessTask(task);
		}

	}

	void LF_ThreadPool::PromoteNewLeader()
	{
		std::lock_guard<std::mutex> lck(_leader_mtx);
		_new_leader = true;
		_leader_cv.notify_one();
	}

	void LF_ThreadPool::TryToLeader()
	{
		std::unique_lock<std::mutex> lck(_leader_mtx);

		while (!_new_leader && _running)
		{
			_leader_cv.wait(lck);
		}

		_new_leader = false;
	}

	void LF_ThreadPool::PorcessTask(const Task &task)
	{
		if (task)
		{
			task();
		}
	}
}
