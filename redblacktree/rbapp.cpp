/**
 * @file rbapp.cpp
 *
 * @brief functions for red black tree 
 *
 * @author Oliver Lynch
 * @date 11/22/19
 */


#include <iostream>
#include <sstream>
#include "rbapp.h"
#include "rbtree.h"

using std::cin;
using std::cout;
using std::endl;
using std::istringstream;

/*
 * @brief   Process command from command line
 *          
 * @param   command: insert, find, delete, print, quit
 *              if no command return to main loop
 * 
 * @return false if comand == quit;
 */
bool RBapp::processCommand(string& line){
    bool rval = true;
    string command;
    istringstream ss (line);
    ss >> command;
    
    if (command == "insert")
        processInsert(line);

    else if(command == "find")
        processFind(line);

    else if(command == "delete")
        processDelete(line);

    else if(command == "print")
        processPrint();

    else if(command == "quit")
        rval = false;

    return rval; //return false if quit
}

/*
 * @brief   pasrses imput and calls RBTree insert
 *          
 * @param   command line line
 */
void RBapp::processInsert(string& line){
    string trash;
    string key = "blabla";
    string satellite_data = "blabla";
    istringstream ss (line);
    ss >> trash;
    ss >> key;
    ss.ignore();
    getline(ss, satellite_data);
    if(key != "blabla" && satellite_data != "blabla"){
        myRBT.rbInsert(key, satellite_data);
    }

}

/*
 * @brief   pasrses imput and calls RBTree print
 */
void RBapp::processPrint(){
    myRBT.rbPrintTree();
}

/*
 * @brief   pasrses imput into key and value and calls RBTree find
 *          
 * @param   command line line
 */
void RBapp::processFind(string& line){
    string trash;
    string key = "blabla";
    istringstream ss (line);
    ss >> trash;
    ss >> key;
    if(key != "blabla"){
        vector<const string*> found = myRBT.rbFind(key); 
        for (int i = 0; i < (signed)found.size(); i++){
            cout << key << " " << *(found[i]) << endl;
        }
    }
}

/*
 * @brief   pasrses imput into key and value and calls RBTree delete
 *          
 * @param   command line line
 */
void RBapp::processDelete(string& line){
    string trash = "blabla";
    string key = "blabla";
    string satellite_data;
    istringstream ss (line);
    ss >> trash;
    ss >> key;
    ss.ignore();
    getline(ss, satellite_data);
    if(key != "blabla" && satellite_data != "blabla"){
        myRBT.rbDelete(key , satellite_data);
    }
}

/*
 * @brief   loop to call process function,
 *              ends loop if EOF or Quit is called
 */
void RBapp::mainLoop(){
    bool run = true;
    char quit;
    string line;
    while(run){
        quit = cin.peek();
        if(quit == EOF){
            run = false;
        }
        else{
            getline(cin, line);
            run = processCommand(line);
        }
    }
}

/*
 * @brief   makes RBTree app object and calls main loop
 */
int main(){

    RBapp MyApp;

    MyApp.mainLoop();

}