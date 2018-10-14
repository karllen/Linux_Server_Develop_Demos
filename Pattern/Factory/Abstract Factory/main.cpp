#include "AbstractFactory.h"

#include<memory>

int main()
{
    std::shared_ptr<AsFactory> factory(new Factory1);
    factory->createProductA()->jacket();
    factory->createProductB()->pants();

    return 0;
}