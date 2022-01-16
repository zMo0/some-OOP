//
//  Triangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#ifndef Triangle_h
#define Triangle_h

#include <iostream>
#include <string>
using namespace std;

#include "Shape.h"


// This class implements the triangle Shape objects.
// ECE244 Student: Write the definition of the class here.

class Triangle : Shape{
private:
    float x1;
    float x2;
    float x3;
    float y1;
    float y2;
    float y3;
public: 
    Triangle (string n, float xc, float yc, float x1, float y1, float x2, float y2, float x3, float y3);
    virtual ~Triangle();
    
    //accessors
    float getX1() const;
    float getX2() const;
    float getX3() const;
    float getY1() const;
    float getY2() const;
    float getY3() const;
    
    //mutator
    void setX1 (float a);
    void setX3 (float a);
    void setX2 (float a);
    void setY1 (float a);
    void setY2 (float a);
    void setY3 (float a);
    
    virtual void draw () const;
    virtual float computeArea() const;
    virtual Shape* clone() const;
    
};

#endif /* Triangle_h */


