//
//  ShapeNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeNode class below

#include <iostream>
#include <sstream>
#include <string>
#include "ShapeNode.h"

using namespace std;

ShapeNode:: ShapeNode(){
    myShape = nullptr;
    next = nullptr;
}
ShapeNode::~ShapeNode(){ 
    delete myShape;
    myShape = nullptr;
}       
Shape* ShapeNode:: getShape() const{       // returns myShape
    return myShape;
}    
void ShapeNode::setShape(Shape* ptr){     // sets myShape to ptr
    myShape = ptr;
}    
ShapeNode* ShapeNode:: getNext() const{    // returns next
    return next;
}    
void ShapeNode:: setNext(ShapeNode* ptr){  // sets next to ptr
    next = ptr;
}
void ShapeNode:: print() const{            // prints the ShapeNode
    myShape->draw();
}
