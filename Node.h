//Julian Worn
//07/17/2023
//Node.cpp

//Header File for the Node Class in the Scheduling system

#include <iostream>
#include "Player.h"
#ifndef Node_H
#define Node_H
using namespace std;

/*
Class Invariants:
-this class only functions as the node in the linked list encapsulated in the Coach class
-careful, public members are declared to be accessed
*/




class Node{

    public:
    shared_ptr<Player> player;
    shared_ptr<Node> next;

    //constructor
    //precondition: pointer shouldn't be nullptr
    //postcondition: create node with empty next pointer
    //ownership over p assumed
    Node(shared_ptr<Player> p);

    //constructor
    //precondition: pointers shouldn't be nullptr
    //postcondition: create node and put n in next (if n is head of linked list, new node will be head now)
    //ownership over p assumed
    Node(shared_ptr<Player> p, shared_ptr<Node> n);
};

#endif

/*
Implementation Invariants:
-this class only functions as the node in the linked list encapsulated in the Coach class
-members are declared public to be accessed
*/
