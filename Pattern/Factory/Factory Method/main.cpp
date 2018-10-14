
#include"FactoryMethod.h"

int main(int argc, char const *argv[])
{
    std::shared_ptr<Factory> factory(new Factory_B);
    
    std::shared_ptr<Product> product = factory->createProduct();

    product->printf();
   
    return 0;
}
