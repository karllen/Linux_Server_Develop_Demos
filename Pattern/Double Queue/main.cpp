#include "DBQueue.h"

int main()
{
    DBQueue que;
    std::thread trd_1(std::bind(&produce, &que));
    std::thread trd_2(std::bind(&consume, &que));
    trd_1.join();
    trd_2.join();
	
    return 0;
}