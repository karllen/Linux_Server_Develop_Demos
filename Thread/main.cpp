#include <iostream>
#include <mutex>
#include <chrono>
#include <fstream>

#include "Asio_ThreadPool.h"

static std::mutex g_tx;

void prinfttt(int i)
{
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		{
			std::lock_guard<std::mutex> lck(g_tx);
			std::cout << "index =" << i << " thead id=" << std::this_thread::get_id() << std::endl;
		}
	}
}

int main()
{
	alsus::Asio_ThreadPool pool;
	pool.Start(5);

	for (int i = 0; i < 5; i++)
	{
		std::cout << "123" << std::endl;
		pool.Execute(std::bind(prinfttt, i));
	}

	getchar();
	pool.Stop();

	return 0;
}