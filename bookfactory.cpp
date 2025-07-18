#include "bookfactory.h"
#include "book.h"


std::unique_ptr<Product> BookFactory::createProduct(const QString& name) const{
    return std::make_unique<Book>(name);
}
