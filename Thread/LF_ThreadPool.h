#pragma once
#ifndef LF_THREAD_POOL_H_
#define LF_THREAD_POOL_H_

#include<functional>
#include<mutex>
#include<condition_variable>
#include<thread>
#include<vector>
#include<list>

namespace alsus
{

	class LF_ThreadPool
	{
		typedef std::function<void()> Task;		

	public:
		LF_ThreadPool();
		virtual ~LF_ThreadPool();

		LF_ThreadPool(const LF_ThreadPool &) = delete;
		LF_ThreadPool & operator =(const LF_ThreadPool &) = delete;

		void Execute(const Task &task);
		void Start(int thread_numbers);
		void Stop();

	protected:
		void ThreadRun();
		void PromoteNewLeader();
		void TryToLeader();
		void ProcessTask(const Task &task);
	private:
		bool _running;
		std::mutex _leader_mtx;
		std::condition_variable _leader_cv;
		std::vector<std::thread> _threads;

		//
		std::mutex _tasks_mtx;
		std::condition_variable _task_cv;
		std::list<Task> _tasks; 
		bool _new_leader;
	};
}



#endif //LF_THREAD_POOL_