//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below

#include <iostream>
#include <sstream>
#include <string>
#include "ShapeList.h"

using namespace std;

ShapeList::ShapeList(){                        // sets head to nullptr
    head = nullptr;
}    
ShapeList::~ShapeList(){                       // deletes all list nodes starting                                       // with head plus associated Shapes
    ShapeNode* node = head;
    ShapeNode* nodeNext = node->getNext();                         // with head plus associated Shapes
    
    while (node!= nullptr){
        nodeNext = node->getNext();
        node->~ShapeNode();
        node-> setShape(nullptr);
        node = nodeNext;
    }
    delete node;
    node = nullptr;
    delete nodeNext;
    nodeNext = nullptr;
}    
ShapeNode* ShapeList::getHead() const{         // returns the head pointer
    return head;
}    
void ShapeList::setHead(ShapeNode* ptr){       // sets the head pointer to ptr
    head = ptr;
}   
ShapeNode* ShapeList::find(string name) const{ // finds a shape node with the specified shape name
                                    // returns a pointer to the node if found, otherwise
                                    // returns nullptr if the node is not found
    ShapeNode* node = head;
    while (node->getShape() != nullptr){
        if (node->getShape()->getName() == name){
            break;
        }
        node = node->getNext();;
    }
    return node;
}

void ShapeList::insert(ShapeNode* s){          // inserts the node pointed to by s at the end
                                          // of the list; s should never be nullptr
    if (s == nullptr) return;
    if (head == nullptr){
        head = s;
        s->setNext(nullptr);
    }
    else{
        ShapeNode* node = head;
        while (node->getNext() != nullptr){
            node = node -> getNext();
        }
        node->setNext(s);
        s->setNext(nullptr);
    }
}

ShapeNode* ShapeList::remove(string name){     // removes the node with the shape called name
                                    // returns a pointer to the removed node or
                                    // nullptr is a node with name does not exist
    if (head->getShape()== nullptr){
        return nullptr;
    }

    ShapeNode* node = head;
    ShapeNode* prenode = nullptr;

    while (node->getShape() !=nullptr){
        if (node->getShape()-> getName() == name)break;
        prenode = node;
        node = node->getNext();
    }
    if (node->getShape() == nullptr) return nullptr;
    if (node == head){
        setHead(head-> getNext());
        return node;
    }
    prenode-> setNext(node->getNext());
    return node;
}   

void ShapeList::print() const{                 // prints the list
    ShapeNode* node = head;
    if (node == nullptr){
        return;
    }

    while (node != nullptr){
        node-> print();
        node = node->getNext();
    }
    return;
}

