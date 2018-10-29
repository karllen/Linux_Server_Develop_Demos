#pragma once

#ifndef ASIO_THREAD_POOL_H_
#define ASIO_THREAD_POOL_H_

#include "boost/asio.hpp"
#include <vector>
#include <functional>
#include <thread>

namespace alsus
{
	class Asio_ThreadPool
	{
	public:
		Asio_ThreadPool()
			: _work(_service)
		{
		}
		virtual ~Asio_ThreadPool()
		{
		}

		Asio_ThreadPool(const Asio_ThreadPool &) = delete;
		Asio_ThreadPool & operator = (const Asio_ThreadPool &) = delete;

		void Start(int thread_numbers)
		{
			_threads.reserve(thread_numbers);

			for (int i = 0; i < thread_numbers; i++)
			{
				_threads.push_back(std::thread(
										[&]()
										{	
											_service.run();
										}));
			}
		}

		void Stop()
		{
			_service.stop();

			for (auto & t : _threads)
			{
				t.join();
			}
		}

		template <typename F>
		void Execute(F fc)
		{
			_service.post(fc);
		}
	
	private:
		boost::asio::io_service _service;
		boost::asio::io_service::work _work;
		std::vector<std::thread> _threads;
	};

}

#endif //ASIO_THREAD_POOL
