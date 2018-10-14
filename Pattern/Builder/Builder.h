#ifndef BUILDER_H_
#define BUILDER_H_

#include<memory>
#include<string>
#include<iostream>

class Product
{
public:
    Product(){};
    virtual ~Product(){}

    void setPartA(const std::string & str)
    {
        _strA = str;
    }
    void setPartB(const std::string & str)
    {
        _strB = str;
    }
    void setPartC(const std::string & str)
    {
        _strC = str;
    }

    void printf()
    {
        std::cout << "PartA: " << _strA
                    << "PartB: " << _strB
                    << "PartC: " << _strC << std::endl; 
    }
private:
    std::string _strA;
    std::string _strB;
    std::string _strC;
};

class IBuilder
{
public:
    IBuilder(){}
    virtual ~IBuilder(){}
    virtual void builderPartA() = 0;
    virtual void builderPartB() = 0;
    virtual void builderPartC() = 0;
    virtual std::shared_ptr<Product> product() = 0;
};

class Builder : public IBuilder
{
public:
    Builder(): _product(new Product){}
    virtual ~Builder(){}

    virtual void builderPartA() override
    {
        _product->setPartA("PartA");
    }

    virtual void builderPartB() override
    {
        _product->setPartB("PartB");
    }

    virtual void builderPartC() override
    {
        _product->setPartC("PartC");
    }

    virtual std::shared_ptr<Product> product() override
    {
        return _product;
    }

private:
    std::shared_ptr<Product> _product;
};

class IDirector
{
public:
    IDirector(){}
    virtual ~IDirector(){}

    virtual void construct() = 0;
    virtual void setBuilder(const std::shared_ptr<IBuilder> & builder) = 0;
};

class Director : public IDirector
{
public:
    Director(){}
    virtual ~Director(){}

    virtual void construct() override
    {
        _builder->builderPartA();
        _builder->builderPartB();
        _builder->builderPartC();
    }
    virtual void setBuilder(const std::shared_ptr<IBuilder> & builder) override
    {
        _builder = builder;
    }
private:
    std::shared_ptr<IBuilder> _builder;
};


#endif //BUILDER_H_