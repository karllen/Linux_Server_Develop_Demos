#include<mutex>
#include<thread>
#include<queue>
#include<iostream>
#include<chrono>

class DBQueue{
public:
    void push(int i_) 
	{
        std::lock_guard<std::mutex> lock(m_mt);
        std::cout << "write_que push " << i_ << std::endl;
        m_write_que.push(i_);
    }
    void swap(std::queue<int> & read_que) 
	{
        std::lock_guard<std::mutex> lock(m_mt);
        std::swap(m_write_que,read_que);
        std::cout << "switch swap" << std::endl;
    }
private:
    std::queue<int> m_write_que;
    std::mutex m_mt;
};
void produce(DBQueue * que) 
{
    while (true) 
	{
        std::this_thread::sleep_for(std::chrono::microseconds(20*1000));
        que->push(1);
    }
}
void consume(DBQueue * que) 
{
    std::queue<int> read_que;
    while (true) 
	{
        std::this_thread::sleep_for(std::chrono::microseconds(20*1000));
        if (read_que.empty()) 
		{
            que->swap(read_que);
            //xxoo
            while (!read_que.empty()) 
			{
                std::cout << "read_que pop" << std::endl;
                read_que.pop();
            }
        }
    }
}
