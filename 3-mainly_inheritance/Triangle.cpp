//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Shape.h"
#include "Triangle.h"
#include <cmath>

Triangle :: Triangle(string n, float x, float y, float X1, float Y1, float X2, float Y2, float X3, float Y3):Shape(n, x, y){
    x1 = X1;
    x2 = X2;
    x3 = X3;
    y1 = Y1;
    y2 = Y2;
    y3 = Y3;
}

Triangle::~Triangle(){
    
}
        
float Triangle:: getX1() const{
    return x1;
}
float Triangle:: getX2() const{
    return x2;
}
float Triangle:: getX3() const{
    return x3;
}
float Triangle:: getY1() const{
    return y1;
}
float Triangle:: getY2() const{
    return y2;
}
float Triangle:: getY3() const{
    return y3;
}

void Triangle::setX1(float a){
    x1 = a;
}
void Triangle::setX2(float a){
    x2 = a;
}
void Triangle::setX3(float a){
    x3 = a;
}
void Triangle::setY1(float a){
    y1 = a;
}
void Triangle::setY2(float a){
    y2 = a;
}
void Triangle::setY3(float a){
    y3 = a;
}

void Triangle::draw() const{
    cout << std::fixed;
    cout << std::setprecision(2);
    
    cout << "triangle: " << name << " " << x_centre << " "<< y_centre << " " << x1 << " " <<
            y1 << " " << x2 << " " << y2 << " " << x3 <<
            " " << y3 <<" "<< computeArea() << endl;
}

float Triangle::computeArea() const{
    float a = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
    return (abs(a/2));
}

Shape* Triangle :: clone() const{
    return (new Triangle(*this));
}
