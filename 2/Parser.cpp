//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
bool nameValid(string s);
bool nameExists(string s);
bool validShapeName(string s);
bool validGroupName(string s);

int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the pool group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    
    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        if (command == keyWordsList[0]){
            string name, type;
            int x_loc, y_loc, x_sz, y_sz;
            
            
            lineStream >> name >> type >> x_loc >> y_loc >>x_sz >> y_sz;
            if (!nameValid(name)){cout << "error: invalid name"<<endl;}
            else if (!nameExists(name)){cout <<"error: name "<< name <<" exists"<<endl;}
            else{
                Shape * thisShape;
                ShapeNode* node = new ShapeNode;//0x6187b0
                thisShape = new Shape(name, type, x_loc, y_loc, x_sz, y_sz);
                node->setShape(thisShape);
                poolGroup->getShapeList()->insert(node);
                cout<< name<< ": "<<type<<" "<<x_loc<<" "<<y_loc<<" "<<x_sz<<" "<<y_sz<<endl;
            }
        }

        else if (command == keyWordsList[1]){
            string groupName;
            lineStream >> groupName;
            if (!nameValid(groupName)){cout << "error: invalid name"<<endl;}
            else if (!nameExists(groupName)){cout <<"error: name "<< groupName <<" exists"<<endl;}
            else{
                GroupNode* newNode = new GroupNode(groupName);
                gList->insert(newNode);
                cout<< groupName<<": group"<<endl;
            }
        }

        else if (command == keyWordsList[4]){
            cout<<"drawing: "<<endl;
            gList->print();
        }

        else if (command == keyWordsList[2]){
            string shape, group;
            lineStream>>shape>>group;
            GroupNode* storedGroup;
            ShapeNode* storedShape;
            if (!validShapeName(shape)){cout << "error: shape "<< shape<< " not found"<<endl;}
            else if (!validGroupName(group)){cout << "error: group "<< group << " not found"<<endl;}
            else{
                GroupNode* gn = gList->getHead();
                while (gn!= nullptr){
                    if (gn->getName() == group){
                        storedGroup = gn;
                    }
                    ShapeNode *a;
                    a = gn->getShapeList()->getHead();
                    while (a!= nullptr){
                        if(a->getShape()->getName() == shape){
                            storedShape = a;
                            gn->getShapeList()->remove(shape);
                        }
                        a = a->getNext();
                    }
                    gn = gn->getNext();
                }
                storedGroup->getShapeList()->insert(storedShape);
                cout<<"moved "<< shape<< " to " << group<<endl;
            }
        }

        else if (command == keyWordsList[3]){
            string name;
            lineStream>>name;
            if (!nameValid(name)) cout<<"error: invalid name"<<endl;
            else if ((! validShapeName(name)) && (! validGroupName(name))) {
                cout << "error: shape " << name <<" not found" <<endl;
            }
            else{
                //delete a group
                if (validGroupName(name)){
                    GroupNode* gn = gList->getHead();
                    while (gn!= nullptr){
                        if (gn->getName() == name){
                            ShapeNode* node = gn->getShapeList()->getHead(); 
                            ShapeNode* nextNode;
                            while (node!= nullptr){
                                nextNode = node->getNext();
                                gList-> getHead()->getShapeList()->insert(node);
                                node = nextNode;
                            }
                            gList->remove(name);
                            delete gn;
                            gn = nullptr;
                            cout<< name << ": deleted"<<endl;
                            break;
                        }
                        gn = gn->getNext();
                    } 
                }
                //delete a shape
                else{
                    GroupNode* gn = gList->getHead();
                    while (gn!= nullptr){
                        ShapeNode* a = gn->getShapeList()->getHead();
                        while (a!= nullptr){
                            if (a->getShape()->getName() == name){
                                gn->getShapeList()->remove(name);
                                a->~ShapeNode();
                                delete a;
                                a = nullptr;
                                cout<< name << ": deleted"<<endl;
                                break;
                            }
                            a = a->getNext();
                        }
                        gn = gn->getNext();
                    }
                }
            }
        }
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

bool nameValid (string s){
    //check if is a reserved word
    for (int i = 0; i <  NUM_KEYWORDS ; ++i){
        if (s == keyWordsList[i])return false;
    }
    
    for (int i = 0; i <  NUM_TYPES; ++i){
        if (s == shapeTypesList[i])return false;
    }
    
    return true;
}

bool nameExists(string s){
    //check if name already exists
    GroupNode* gn = gList->getHead();
    while (gn!= nullptr){
        if (gn->getName() == s)return false;
        ShapeNode* a = gn->getShapeList()->getHead();
        while (a != nullptr){
           if(a->getShape()->getName() == s)return false;
           a = a->getNext();
        }
        gn = gn->getNext();
    }
    return true;
}
bool validShapeName(string s){
    GroupNode* gn = gList->getHead();
    while (gn!= nullptr){
        ShapeNode* a = gn->getShapeList()->getHead();
        while (a!= nullptr){
            if(a->getShape()->getName() == s)return true;
            a = a->getNext();
        }
        gn = gn->getNext();
    }
    return false;
}
bool validGroupName(string s){
    GroupNode* gn = gList->getHead();
    while (gn!= nullptr){
        if (gn->getName() == s) return true;
        gn = gn->getNext();
    }
    return false;
}
