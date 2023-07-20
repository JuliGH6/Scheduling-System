//Julian Worn
//07/17/2023
//Node.cpp

//Source File for the Node Class in the Scheduling system
//for pre/post conditions as well as class/implementation invariants, check header file Node.h

#include "Node.h"

Node::Node(shared_ptr<Player> p){
    player = p;
    next = nullptr;
    p = nullptr;
}
Node::Node(shared_ptr<Player> p, shared_ptr<Node> n){
    player = p;
    next = n;
    p = nullptr;
}
