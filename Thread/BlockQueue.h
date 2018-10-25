#pragma once

#ifndef _BLOCK_QUEUE_H_
#define _BLOCK_QUEUE_H_

#include<list>
#include<mutex>
#include<condition_variable>

namespace alsus
{
	template<typename T>
	class BlockQueue
	{
	public:
		BlockQueue(){}
		virtual ~BlockQueue(){}

		BlockQueue(const BlockQueue &) = delete;
		BlockQueue & operator(const BlockQueue &) = delete;

		void Push(T &t)
		{
			std::lock_guard<std::mutex> lck(_mtx);
			_queue.push_back(t);
			_ne_cv.notify_one();
		}

		T Get()
		{
			std::unique_lock<std::mutex> lck(_mtx);
			while (_queue.empty())
			{
				_ne_cv.wait(lck);
			}

			T t(_queue.front());
			_queue.pop_front();
			return t;
		}

		size_t Size() const
		{
			std::lock_guard<std::mutex> lck(_mtx);
			return _queue.size();
		}

	private:
		std::mutex _mtx;
		std::condition_variable _ne_cv;
		std::list<T> _queue;
	};

}


#endif // _BLOCK_QUEUE_H
