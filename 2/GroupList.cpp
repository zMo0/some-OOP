//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below
#include <iostream>
#include <sstream>
#include <string>
#include "GroupList.h"

using namespace std;
GroupList::GroupList(){                      // sets head to nullptr
    head = nullptr;
}
GroupList::~GroupList(){                     // deletes all list nodes, including all the ShapeList
                                  // attached to each GroupNode
    GroupNode* node;
    GroupNode* nodenext;
    node = head;
    nodenext = head->getNext();

    while (node!= nullptr){
        node->~GroupNode();
        node->setShapeList(nullptr);
        node = nodenext;
        nodenext = nodenext->getNext();
    }
    delete node;
    node = nullptr;
    delete nodenext;
    nodenext = nullptr;
}    
GroupNode* GroupList::getHead() const{       // returns the head pointer
    return head;
}    
void GroupList::setHead(GroupNode* ptr){     // sets the head pointer to ptr
    head = ptr;
}    
void GroupList::insert(GroupNode* s){        // inserts the node pointed to by s at the end of the list
    if (head == nullptr){
        head = s;
    }
    else{
        GroupNode* node = head;
        while (node->getNext() != nullptr){
            node = node -> getNext();
        }
        node->setNext(s);
        s->setNext(nullptr);
    }
}
GroupNode* GroupList::remove(string name){   // removes the group with the name "name" from the list
                                  // and returns a pointer to the removed GroupNode
                                  // returns nullptr is name is not found on list
    if (head == nullptr){
        return nullptr;
    }
    
    GroupNode* node = head;
    GroupNode* preNode = nullptr;
    
    while (node != nullptr){
        if (node->getName() == name)break;
        preNode = node;
        node = node->getNext();
    }
    
    if (node == nullptr) return nullptr;
    if (node == head){
        head-> setNext(head->getNext());
        return node;
    }
//    if (node->getNext()!=nullptr){
//        preNode->setNext(node->getNext());
//    }
    preNode->setNext(node->getNext());
    return node;
}    
    
void GroupList::print() const{               // prints the list, one GroupNode at a time
    GroupNode* node = head;
    while(node!=nullptr){
        cout<< (node->getName()) << ":"<<endl;
        node->getShapeList()->print();
        node = node->getNext();
    } 
}

