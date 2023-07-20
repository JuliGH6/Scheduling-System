//Julian Worn
//07/17/2023
//Player.h

//Header File for the Player Class in the Scheduling system

#include <iostream>
#include <memory>
#ifndef PLAYER_H
#define PLAYER_H
using namespace std;


/*
Class Invariants:
-the player needs to be given a unique name and a priority, to function in the scheduling system
-the name needs to be provided at construction, the priority can be set later
-there is a maximum of 7 lessons Needed that I player can ask for. everything above will be converted to 7
-scheduleFail is true when the player couldn't be scheduled completely
-the higher the priority, the more likely the player will get all his lessons scheduled
-construction with default constructor is prohibited and impossible -> parameters must be provided
-deep copying as well as move semantics are supported
-the practiceSchedule needs to be a pointer to a 2d array of 7x24 to resemble the hours in a week, 0 means no time, 
1 means available, "P" means practice scheduled, nullptr for a day means no availability at all for that day
*/


class Player{

    string name;
    unsigned priority = 0;
    unsigned lessonNeed = 0;
    unsigned lessonReceived = 0;
    string** practiceSchedule = nullptr;
    int* practiceDays = new int[7];
    bool scheduleFail = true;

    //preconditions: parameters must be provided
    //postconditions: deep copying of all class members happens here
    void copy(const Player& source);

    public:
    //preconditions: parameter can't be nullptr
    //postconditions: deep copy of pointed object is created
    Player(shared_ptr<Player>& player);
    
    //preconditions: parameters must be provided
    //postconditions: ownership assumed, pointer of parameter set to null, object created with priority 0
    //if parameter of array nullptr, interpreted as no availability at all
    Player(string n, unsigned lN, string**& a);

    //preconditions: if parameter of array nullptr, interpreted as no availability at all
    //postconditions: ownership assumed, pointer of parameter set to null
    //if parameter of array nullptr, interpreted as no availability at all
    Player(string n, unsigned p, unsigned lN, string**& a);

    //deep copying supported for copy constructor
    Player(const Player& source);

    //move constructor
    //preconditions: -
    //postconditions: leaves parameter object in invalid state
    Player(Player&& source);

    //deep copying supported for assignment operator
    void operator=(const Player& source);

    //move assignment operator
    //preconditions: -
    //postconditions: leaves parameter object in unknown state  
    void operator=(Player&& source);

    //customized destructor
    ~Player();

    //preconditions: -
    //postconditions: returns name string
    string getName();

    //preconditions: -
    //postconditions: returns priority int
    unsigned getPriority();

    //preconditions: unsigned parameter needed
    //postconditions: sets priority
    void setPriority(unsigned p);

    //preconditions: -
    //postconditions: if pointer nullptr, no availability, ownership is assumed and parameter pointer is set to null
    void setPracticeSchedule(string**& a);

    //preconditions: -
    //postconditions: returns real practiceSchedule handle. modify carefully, shared ownership!
    string** getPracticeSchedule();

    //preconditions: -
    //postconditions: returns unsigned lessonNeeded
    unsigned getLessonNeed();

    //preconditions: -
    //postconditions: decrements lessonNeed
    void decLessonNeed();

    //preconditions: unsigned parameter needed
    //postconditions: sets lessonNeed to parameter
    void setLessonNeed(unsigned lN);

    //preconditions: -
    //postconditions: increments lessonReceived
    void incLessonReceived();

    //preconditions: -
    //postconditions: returns unsigned lessonReceived
    int getLessonReceived();

    //preconditions: -
    //postconditions: increments lessonReceived and decrements lessonNeeded
    void lessonAdd();

    //preconditions: bool parameter required
    //postconditions: sets scheduleFail to parameter
    void setScheduleFail(bool f);

    //preconditions: -
    //postconditions: returns scheduleFail bool
    bool getScheduleFail();

    //preconditions: -
    //postconditions: returns real practiceDays handle. modify carefully, shared ownership!
    int* getPracticeDays();
};

#endif

/*
Implementation Invariants:

-class members are encapsulated with getters and setters being provided if necessary
-deep copying as well as move semantics are supported
-practiceSchedule is received through dependency injection and ownership is assumed
-the practiceSchedule stores the availabity as well as it gets updated when you have practice lessons 
(0 means no time, 1 means time, P means practice, nullptr means that the player is not available on that day)
-practice days is only needed for more efficiency (0 for days with no practice, 1 for days with practice)
-the name must be unique to idenity each student, full names with spaces are supported
-operator overloading only for assignment operator.
*/
