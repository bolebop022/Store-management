#include "magazinefactory.h"
#include "magazine.h"


std::unique_ptr<Product> MagazineFactory::createProduct(const QString& name) const{
    return std::make_unique<Magazine>(name);
}
