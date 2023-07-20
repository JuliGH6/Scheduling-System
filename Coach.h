//Julian Worn
//07/17/2023
//Coach.h

//Header file for the Coach class in the scheduling system

#include <iostream>
#include <queue>
#include <fstream>
#include "Node.h"
#ifndef Coach_H
#define Coach_H
using namespace std;

/*
Class Invariant:
- only players that got "prioritized" within the addPlayer() function will be included in the schedule
- players will be added to newPlayers first, waiting to be rated
- you can only make a schedule after providing workHours for the coach
- the workSchedule needs to be a pointer to a 2d array of 7x24 to resemble the hours in a week, 0 means no time, 
1 means available, <name> means player with name <name> scheduled, nullptr for a day means no availability at all for that day
- deep copying, and move semantics supported
- the scheduling will schedule as many lessons as possible, finishing off people from the highest priority before moving on,
same priority means first come first serve in regards of signing up for lessons
-operator overloading provided as adding feature when adding Player to Coach (C=C+P , C=P+C , C+=P)
*/

class Coach{

    string name = "";
    bool scheduleUpdated = false;
    string** workSchedule = nullptr;
    queue< shared_ptr<Player> > newPlayers;
    shared_ptr<Node> allPlayers = nullptr;

    //preconditions: parameter
    //postconditions: deep copying happens here
    void copy(const Coach& source);

    //preconditions: parameter
    //postconditions: recursively deep copies linked list and returns pointer to head
    shared_ptr<Node> copyList(shared_ptr<Node> iter);

    public:
    //preconditions: parameters must be provided
    //postconditions: constructing object with given name and empty queue and nullptrs for players and workSchedule
    Coach(string n);

    //preconditions: parameters must be provided
    //postconditions: instance of coach created with passed workSchedule. 
    //ownership assumed, pointer of parameter set to null, if parameter of array is nullptr, 
    //interpreted as no availability at all
    Coach(string n, string**& hours);

    //deep copying supported for copy constructor
    Coach(const Coach& source);


    //move constructor
    //preconditions: -
    //postconditions: leaves parameter object in invalid state
    Coach(Coach&& source);

    //deep copying supported for assignment operator
    void operator=(const Coach& source);

    //move assignment operator
    //preconditions: -
    //postconditions: leaves parameter object in unknown state  
    void operator=(Coach&& source);

    //customized destructor
    //deallocates array and sets reference count of shared pointer handles to 0 to be deallocated immediately
    ~Coach();

    //preconditions: parameters must be provided
    //postconditions: ownership assumed, pointer of parameter set to null, if parameter of array is nullptr, 
    //interpreted as no availability at all, work schedule changed to new array
    void setHours(string**& workHours);

    //preconditions: -
    //postconditions: newPlayers queue empty, players get rated in priority and added to allPlayers
    //scheduleUpdated is false
    void rateNewPlayers();

    //preconditions: parameters must be provided
    //postconditions: new player gets added to newPlayers queue (no priority specified yet, won't be included in schedule)
    void addToNewPlayer(shared_ptr<Player> p);

    //preconditions: parameters must be provided
    //postconditions: new player gets rated and added to linked list of AllPlayers
    //scheduleUpdated false
    void addPlayer(shared_ptr<Player>& p);

    //preconditions: -
    //postconditions: creates schedule based on workHours and listed Players in allPlayers. Coaches and Players arrays get updated
    //scheduleUpdated true
    void makeSchedule();

    //preconditions: -
    //postconditions: prints schedule and list of players who's wish is not satisfied
    void printSchedule();

    //preconditions: -
    //postconditions: returns bool, true if there are no new players
    bool getNoNewPlayers();

    //preconditions: -
    //postconditions: prints allPlayers list (rated players)
    void printRatedPlayers();

    //preconditions: -
    //postconditions: returns bool state, true if the schedule was updated
    bool getScheduleUpdated();

    //preconditions: -
    //postconditions: returns bool true, if the name exists already in the players list
    bool nameExists(string n);

    //preconditions: -
    //postconditions: creates a cfv file in the current directory of the current schedule
    void createFile();

    //+ operator for mixed type addition
    //precondition:
    //postcondition: p gets added to current coach's allPlayer list, priority will be asked for
    Coach operator+(const Player& p) const;

    //+= operator for mixed type addition
    //precondition:
    //postcondition: p gets added to current coach's allPlayer list, priority will be asked for
    Coach& operator+=(const Player& p);
};

//callback function to support all + operations for mixed types
//precondition:
//postcondition: p gets added to c allPLayer list, priority will be asked for
Coach operator+(const Player& p, const Coach& c);

#endif


/*
Implementation Invariant:
-class members are encapsulated with getters and setters being provided if necessary
-deep copying as well as move semantics are supported
-workSchedule is received through dependency injection and ownership is assumed
-the workSchedule stores the availabity as well as it gets updated when you schedule practice lessons 
(0 means no time, 1 means time, any name means this person has practice then, 
nullptr means that the coach is not available on that day)
-operator overloading provided as adding feature when adding Player to Coach
-newPlayers is implemented as a queue to add in Players as received by time
-allPlayers is a priority queue, implemented as linked list that adds Players sorted by priority and time
I picked this priority queue implementation because the adding of the player happens over multiple weeks so 
O(n) is negligible, but makeSchedule function can interate through the list and retrieve the highest priority from the
start till end with O(n) instead of O(log n * n) for example (heap implementation)
*/
