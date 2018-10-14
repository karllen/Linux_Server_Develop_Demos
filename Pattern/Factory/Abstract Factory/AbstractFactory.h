#ifndef ABSTRACT_FACTORY_H_
#define ABSTRACT_FACTORY_H_

#include<memory>
#include<iostream>

class AsProductA
{
public:
    AsProductA(){}
    virtual ~AsProductA(){}
    virtual void jacket() = 0;
};

class ProductA : public AsProductA
{
public:
    ProductA(){}
    virtual ~ProductA(){}
    virtual void jacket() override
    {
        std::cout << "jacket ProductA" << std::endl;
    }
}; 

class AsProductB
{
public:
    AsProductB(){}
    virtual ~AsProductB(){}
    virtual void pants() = 0;

};

class ProductB : public AsProductB
{
public:
    ProductB(){}
    virtual ~ProductB(){}
    virtual void pants() override
    {
        std::cout << "pants ProductB" << std::endl;
    }
};

class AsFactory
{
public:
    AsFactory(){}
    virtual ~AsFactory(){}

    virtual std::shared_ptr<AsProductA> createProductA() = 0;
    virtual std::shared_ptr<AsProductB> createProductB() = 0;

};


class Factory1 : public AsFactory
{
public:
    Factory1(){}
    virtual ~Factory1(){};

    virtual std::shared_ptr<AsProductA> createProductA() override
    {
        return std::make_shared<ProductA>();
    }
    virtual std::shared_ptr<AsProductB> createProductB() override
    {
        return std::make_shared<ProductB>();
    }

};


#endif //ABSTRACT_FACTORY_H_