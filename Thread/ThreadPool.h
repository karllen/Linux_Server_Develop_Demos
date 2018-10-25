#pragma once

//Half Sync / Half Async
//Sync Layer
//Queue Layer
//Async Layer

#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <list>
#include <mutex>
#include <thread>
#include <vector>
#include <functional>
#include <condition_variable>

namespace alsus
{
	typedef std::function<void()> Task;

	class ThreadPool
	{
	public:
		ThreadPool();
		virtual ~ThreadPool();

		ThreadPool(const ThreadPool &) = delete;
		ThreadPool & operator = (const ThreadPool &) = delete;

		void SetMaxQueueSize(size_t size);
		void Start(int threads_numbers);
		void Stop();
		void Execute(const Task & task);
		bool IsFull();
		void ThreadRun();
		size_t QueueSize();

	private:
		bool _running;
		size_t _max_queue_size;
		std::mutex _mtx;
		std::condition_variable _not_full_cv;
		std::condition_variable _not_empty_cv;
		std::list<Task> _queue;
		std::vector<std::thread> _threads;
	};
}



#endif //_THREAD_POOL_H_