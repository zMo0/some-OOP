//
//  GroupNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupNode class below

#include <iostream>
#include <sstream>
#include <string>
#include "GroupNode.h"

using namespace std;
GroupNode::GroupNode(string n){                   // sets group name to n and makes myShapeList
                                           // point to a new ShapeList; sets next to nullptr
    name = n;
    myShapeList = new ShapeList;
    next = nullptr;
}    
GroupNode::~GroupNode(){                          // deletes the myShapeList list
    delete myShapeList;
    myShapeList = nullptr;
}    
string GroupNode::getName() const{                // returns group name
    return name;
}    
ShapeList* GroupNode::getShapeList() const{       // returns myShapeList
    return myShapeList;
} 
void GroupNode::setShapeList(ShapeList* ptr){     // sets myShapeList to ptr
    myShapeList = ptr;
}
GroupNode* GroupNode::getNext() const{            // returns next
    return next;
}
void GroupNode::setNext(GroupNode* ptr){          // sets next to ptr
   
    next = ptr;
}    
void GroupNode::print() const{                    // prints the GroupNode
    cout<< name << ": "<<endl;
}
