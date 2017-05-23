#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"

class Square : public Figure
{
public:
    Square(double*, double*, double*, double*);
    void draw() const;
};


#endif // SQUARE_H
