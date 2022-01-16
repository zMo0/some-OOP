//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
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

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

//track the existence database, since only one is allowed to exist at a time
bool dataBaseExits = false;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
void newDataBase();
void removeOldDataBase();
void move(Shape* shape, int x, int y);
void rotate(Shape* shape, int angle);
void drawAll();
void draw(Shape* shape);
void draw1(Shape* shape);
void deleteAll();
void deleteShape(int index);

int main() {

    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        command  = "";
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        //maxShape
        if (command == keyWordsList[1]){ 
            max_shapes = 0;
            lineStream >> max_shapes;
            bool proceed = true;
                
            //check input type
            if (lineStream.fail()&&(!lineStream.eof())){
                cout<< "Error: invalid argument"<<endl;
                lineStream.clear();
                proceed = false;
            }     
            //check right amount of input
            if (proceed){
                if (lineStream.fail()&&lineStream.eof()){
                    cout<< "Error: too few arguments"<<endl;
                    proceed = false;
                }
                if (lineStream.peek()!= EOF){
                    string temp;
                    lineStream>>temp;
                    if (!lineStream.fail()){
                        cout<< "Error: too many arguments"<<endl;
                        proceed =false;
                    }
                }        
            }
            
            //check if value is valid
            if (proceed){
                if (max_shapes<=0){
                    cout<< "Error: invalid value"<<endl;
                    proceed = false;
                }
            }
            
            //create dataBase is everything is ok
            if(proceed){newDataBase();}
        }
        
        //Create
        else if (command == keyWordsList[2]){
                int x, y, s1, s2;
                string name, type;
                lineStream >> name >> type >> x >> y >> s1>> s2;
                
                bool proceed  = true;

                //Check for incorrect input type
                if (lineStream.fail() && (!lineStream.eof())){
                    cout << "Error: invalid argument"<< endl;
                    proceed = false;
                }
                //check if there's enough input
                if (proceed){
                    if (lineStream.fail()&&lineStream.eof()){
                        cout<< "Error: too few arguments"<<endl;
                        proceed = false;
                    }
                }
                
                  //Check for correct number of arguments
                if (proceed){
                    
                    if (lineStream.peek()!= EOF){
                        string temp;
                        lineStream>>temp;
                        if (!lineStream.fail()){
                            cout<< "Error: too many arguments"<<endl;
                            proceed = false;
                        }
                    }
                }
                //Check for invalid name, do so only if input type is correct
                if (proceed){
                    //if name in keyword list
                    for (int j = 0; j<7;++j){
                        if (name == keyWordsList[j]){
                            cout << "Error: invalid shape name" <<endl;
                            proceed = false;
                            break;
                        }
                    }
                    //if name is a shape type
                    for (int j = 0; j < 4; ++j){
                        if (name == shapeTypesList[j]){
                            cout << "Error: invalid shape name" <<endl;
                            proceed = false;
                            break;
                        }
                    }

                    //if name is in data base
                    for (int a = 0; a < shapeCount; ++a){
                        string n = shapesArray[a]->getName();
                        if (name == n){
                            cout <<"Error: shape name exists" <<endl;
                            proceed = false;
                            break;
                        }
                    }
                }
                
                //Check for invalid type
                if (proceed){
                    proceed = false;
                    for (int a = 0; a < 4; ++a){
                        if (type == shapeTypesList[a]){
                            proceed = true;
                            break;
                        }
                    }
                    if (!proceed){
                        cout<< "Error: invalid shape type"<<endl;
                    }
                }
                
                //Check for invalid value
                if (proceed){
                    if (x >= 0 && y >= 0 && s1 > 0 && s2 > 0 ){
                        if (type == "circle"){
                            proceed = (s1 == s2);
                        }
                        else {proceed = true;}
                    }
                    else {proceed = false;}
                    if (!proceed){
                        cout << "Error: invalid value" << endl;
                    }
                }
                
               
               
                //Check is database array is full, only do so if all previous checks are passed
                //if not full, create object
                if (proceed){
                    //check database
                    if (shapeCount < max_shapes){
                        //create object if successful
                        shapesArray[shapeCount] = new Shape(name, type, x, y, s1, s2);
                        shapeCount++;
                        lineStream.clear();
                    }
                    //database is full
                    else{
                        cout<<"Error: shape array is full"<<endl;
                    }
                }
            }
        
        //move
        else if (command == keyWordsList[3]){
            int locx, locy;
            string name;
            lineStream>> name >> locx >> locy;
            bool proceed = true;
            
            //Check for incorrect input type
            if (lineStream.fail() && (!lineStream.eof())){
                cout << "Error: invalid argument"<< endl;
                proceed = false;
            }
            if (proceed){
                if (name ==""){
                    proceed = false;
                    cout<< "Error: too few arguments"<<endl;
                }
            }
            //check if entered name is in array
            if(proceed){
                bool nameExists = false;
                for (int i = 0; i < shapeCount; ++i){
                    if (name == (shapesArray[i])-> getName()){
                        nameExists = true;
                    }
                }
                if (!nameExists){
                    cout<<"Error: shape "<< name <<" not found"<<endl;
                    proceed = false;
                }
                
            //Check for correct number of arguments
            if (proceed){
                if (lineStream.fail()&&lineStream.eof()){
                    cout<< "Error: too few arguments"<<endl;
                    proceed = false;
                }
                    
                if (lineStream.peek()!= EOF){
                    string temp;
                    lineStream>>temp;
                    if (!lineStream.fail()){
                        cout<< "Error: too many arguments"<<endl;
                        proceed = false;
                    }
                }
            }
            
            }
            //check if value is valid
            if (proceed){
                if (locx >= 0 && locy >= 0){
                    proceed = true;
                }
                else {
                    proceed = false;
                    cout << "Error: invalid value" << endl;
                }
            }
            //If input all ok, perform move
            if (proceed){
                for (int i = 0; i < shapeCount; ++i){
                    if (name == (shapesArray[i])-> getName()){
                        move(shapesArray[i], locx, locy);
                        break;
                    }
                }
                
            }
                
        }
        
        //rotate
        else if (command == keyWordsList[4]){
            int angle;
            string name;
            lineStream>> name>> angle;
            bool proceed = true;
            
            //Check for incorrect input type
            if (lineStream.fail() && (!lineStream.eof())){
                cout << "Error: invalid argument"<< endl;
                proceed = false;
            }
            if (proceed){
                if (name ==""){
                    proceed = false;
                    cout<< "Error: too few arguments"<<endl;
                }
            }
            //check if entered name is in array
            if(proceed){
                bool nameExists = false;
                for (int i = 0; i < shapeCount; ++i){
                    if (name == (shapesArray[i])-> getName()){
                        nameExists = true;
                    }
                }
                if (!nameExists){
                    cout<<"Error: shape "<< name <<" not found"<<endl;
                    proceed = false;
                }
            }
            //Check for correct number of arguments
            if (proceed){
                if (lineStream.fail()&&lineStream.eof()){
                    cout<< "Error: too few arguments"<<endl;
                    proceed = false;
                }
                    
                if (lineStream.peek()!= EOF){
                    string temp;
                    lineStream>>temp;
                    if (!lineStream.fail()){
                        cout<< "Error: too many arguments"<<endl;
                        proceed = false;
                    }
                }
            }
            
            
            //check if value is valid
            if (proceed){
                if (!(angle > 0 && angle < 360)){
                    proceed = false;
                    cout << "Error: invalid value" << endl;
                }
            }

            //rotate if value is all good
            if (proceed){
                for (int i = 0; i < shapeCount; ++i){
                    if (name == (shapesArray[i])-> getName()){
                        rotate(shapesArray[i], angle);
                        break;
                    }
                }
            }
            
        }
        
        //draw
        else if (command == keyWordsList[5]){
            string item;
            lineStream >> item;
            bool proceed = true;
            int index = 0;
            
            //Check for incorrect input type
            if (lineStream.fail() && (!lineStream.eof())){
                cout << "Error: invalid argument"<< endl;
                proceed = false;
            }
            
            if (proceed){
                if (item ==""){
                    proceed = false;
                    cout<< "Error: too few arguments"<<endl;
                }
            }
            //check if entered name is in array
            
            if(proceed){
                bool nameExists = false;
                for (int i = 0; i < shapeCount; ++i){
                    if (shapesArray[i] != NULL){
                        if (item == (shapesArray[i])-> getName()){
                            nameExists = true;
                            index = i;
                            break;
                        }
                    }
                }
                if (!nameExists && item != "all"){
                    cout<<"Error: shape "<< item <<" not found"<<endl;
                    proceed = false;
                }
            }    
            //Check for correct number of arguments
            if (proceed){
                if (lineStream.fail()&&lineStream.eof()){
                    cout<< "Error: too few arguments"<<endl;
                    proceed = false;
                }
                    
                if (lineStream.peek()!= EOF){
                    string temp;
                    lineStream>>temp;
                    if (!lineStream.fail()){
                        cout<< "Error: too many arguments"<<endl;
                        proceed = false;
                    }
                }
            }
            
            //check if input is "all"
            if (proceed){
                if (item == "all"){
                    drawAll();
                    proceed = false;
                }
            }
            //attempt to draw individual shape
            if(proceed){
                draw(shapesArray[index]);
            }
            
        }
        //delete
        else if (command == keyWordsList[6]){
            string item;
            lineStream >> item;
            bool proceed = true;
            
            //Check for incorrect input type
            if (lineStream.fail() && (!lineStream.eof())){
                cout << "Error: invalid argument"<< endl;
                proceed = false;
            }
            if (proceed){
                if (item ==""){
                    proceed = false;
                    cout<< "Error: too few arguments"<<endl;
                }
            }
            //check if entered name is in array
            int index = 0;
            if(proceed){
                bool nameExists = false;
                for (int i = 0; i < shapeCount; ++i){
                    if (shapesArray[i] != NULL){
                        if (item == (shapesArray[i])-> getName()){
                            nameExists = true;
                            index = i;
                            break;
                        }
                    }
                }
                if (!nameExists && item != "all"){
                    cout<<"Error: shape "<< item <<" not found"<<endl;
                    proceed = false;
                }
            }    
            //Check for correct number of arguments
            if (proceed){
                if (lineStream.fail()&&lineStream.eof()){
                    cout<< "Error: too few arguments"<<endl;
                    proceed = false;
                }
                    
                if (lineStream.peek()!= EOF){
                    string temp;
                    lineStream>>temp;
                    if (!lineStream.fail()){
                        cout<< "Error: too many arguments"<<endl;
                        proceed = false;
                    }
                }
            }
            
            //check if input is "all"
            if (proceed){
                if (item == "all"){
                    deleteAll();
                    proceed = false;
                }
            }
            
            if(proceed){
                cout<<"Deleted shape "<< shapesArray[index]->getName()<<endl;
                deleteShape(index);
            }
            
        }
            
        else{
            cout<< "Error: invalid command" <<endl;
        }
       
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  
}
     

    
void newDataBase(){
    if (dataBaseExits){
        removeOldDataBase();
        dataBaseExits = false;
    }
    shapesArray = new Shape* [max_shapes];

    for (int i = 0; i < max_shapes; ++i){
        shapesArray[i] = NULL;
    }
    cout<< "New database: max shapes is " << max_shapes<< endl;
    dataBaseExits = true;
    return;
}

void removeOldDataBase(){
    for (int i; i < max_shapes; ++i){
        delete shapesArray[i];
        shapesArray = nullptr;
    }
    delete[] shapesArray;
    shapesArray = nullptr;
    shapeCount = 0;
    return;
}

void move(Shape* shape, int x, int y){
    shape->setXlocation(x);
    shape->setYlocation(y);
    cout<< "Moved "<< shape->getName() <<" to "<< x <<" "<< y <<endl;
    return;
}

void rotate(Shape* shape, int angle){
    shape->setRotate(angle);
    cout<<"Rotated "<<shape->getName() <<" by "<< angle <<endl;
    return;
}

void drawAll(){
    cout <<"Drew all shapes"<<endl;
    if (shapeCount != 0){ 
        for (int i = 0; i < shapeCount; ++i){
            draw1(shapesArray[i]);
        }
    }
    return;
}

void draw(Shape* shape){
    
    if (shape != nullptr){
        cout<< "Drew "<<shape->getName()<< ": "<< shape->getType()<<" "<<
                shape->getXlocation()<<" "<<shape->getYlocation()<<" "
                <<shape->getXsize()<<" "<<shape->getYsize()<<endl;
    }
    return;
}
void draw1(Shape* shape){
    
    if (shape != nullptr){
        cout<<shape->getName()<< ": "<< shape->getType()<<" "<<
                shape->getXlocation()<<" "<<shape->getYlocation()<<" "
                <<shape->getXsize()<<" "<<shape->getYsize()<<endl;
    }
    return;
}

void deleteAll(){
    cout<<"Deleted: all shapes"<<endl;
    for (int i = 0; i<shapeCount; ++i){
        deleteShape(i);
    }
    shapeCount = 0;
    return;
}

void deleteShape(int index){
    
    delete shapesArray[index];
    shapesArray[index]= nullptr;
    
    return;
}