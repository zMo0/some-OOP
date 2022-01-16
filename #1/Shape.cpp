//
//  Shape.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//  ECE244 Student:
//  Write the implementation (and only the implementation) of the Shape class below
#include <iostream>
#include <sstream>
#include <string>
#include "Shape.h"

using namespace std;
Shape::Shape(string n, string t, int x_loc, int y_loc, int x_sz, int y_sz){
    name = n;
    type = t;
    x_location = x_loc;
    y_location = y_loc;
    x_size = x_sz;
    y_size = y_sz;
    cout<< "Created "<< name << ": "<< type<<" "<< x_location<<" "<<y_location<<" "<<x_size<<" "<<y_size<<endl;
}

string Shape::getName(){
    return name;
}
string Shape::getType(){
    return type;
}
int Shape::getXlocation(){
    return x_location;
}

int Shape::getYlocation(){
    return y_location;
}
int Shape::getXsize(){
    return x_size;
}
int Shape::getYsize(){
    return y_size;
}

void Shape::setYlocation(int y_loc) // Sets location of the shape on the y-axis
{
    y_location = y_loc;
} 
void Shape::setXlocation(int x_loc) // Sets location of the shape on the x-axis
{
    x_location = x_loc;
} 
void Shape::setYsize(int y_sz){       // Sets size of the shape in the y-dimension
    y_size = y_sz;
}
void Shape::setXsize(int x_sz){       // Sets size of the shape in the y-dimension
    x_size = x_sz;
}
void Shape::setRotate(int angle){     // sets the rotation of the shape
    rotation = angle;
}
// Utility methods
void Shape::draw(){                  // Draws a shape; for this assignment it only prints the information of the shape
    cout<<"Drew " <<name<<": "<< type <<" " 
        <<" " <<x_location << " "<< y_location << " " << x_size <<" "
        << y_size << endl;   
}                