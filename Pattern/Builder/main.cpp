#include "Builder.h"


int main()
{
    std::shared_ptr<IBuilder>  builder(new Builder);
    std::shared_ptr<IDirector> director(new Director);
    
    director->setBuilder(builder);
    director->construct();

    std::shared_ptr<Product> product = builder->product();

    product->printf();

    return 0;
}