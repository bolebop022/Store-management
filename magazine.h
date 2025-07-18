#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "product.h"

class Magazine : public Product
{
public:
    Magazine(const QString& name);
};

#endif // MAGAZINE_H
