#ifndef BOOK_H
#define BOOK_H

#include "product.h"

class Book: public Product
{
public:
    Book(const QString& name);
};

#endif // BOOK_H
