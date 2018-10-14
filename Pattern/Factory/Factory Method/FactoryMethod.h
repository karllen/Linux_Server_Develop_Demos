#ifndef FACTORY_METHOD_H_
#define FACTORY_METHOD_H_
#include<iostream>
#include<memory>

class Product
{
public:
    Product(){}
    virtual ~Product(){}
    virtual void printf(){}
    
};

class Product_A : public Product
{
public:
    Product_A(){}
    virtual ~Product_A(){}
    virtual void printf() 
    {
        std::cout << "Product_A" << std::endl;
    }
};

class Product_B : public Product
{
public:
    Product_B(){}
    virtual ~Product_B(){}
    virtual void printf()
    {
        std::cout << "Product_B" << std::endl;
    }
};


class Factory
{
public:
    Factory(){}
    virtual ~Factory(){}
    virtual std::shared_ptr<Product> createProduct() = 0;
  
};

class Factory_A : public Factory
{
public:
    Factory_A(){}
    virtual ~Factory_A(){}
    virtual std::shared_ptr<Product> createProduct() override
    {
        return std::make_shared<Product_A>();
    }

};

class Factory_B : public Factory
{
public:
    Factory_B(){}
    virtual ~Factory_B(){}
    virtual std::shared_ptr<Product> createProduct() override
    {
        return std::make_shared<Product_B>();
    }
};



#endif //FACTORY_METHOD_H_