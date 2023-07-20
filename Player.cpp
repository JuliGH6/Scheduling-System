//Julian Worn
//07/17/2023
//Player.cpp

//Source File for the Player Class in the Scheduling system
//for pre/post conditions as well as class/implementation invariants, check header file Player.h


#include "Player.h"
using namespace std;

Player::Player(string n, unsigned lN, string**& a) { 
    name = n;
    lessonNeed = lN;
    if (a==nullptr){
        a = new string*[7];
        for (int i=0; i<7; i++){
            a[i] = nullptr;
        }
    }
    practiceSchedule = a;
    a = nullptr;
}
Player::Player(string n, unsigned p, unsigned lN, string**& a){
    name = n;
    priority = p;
    if (lN>=7) lN=7;
    lessonNeed = lN;
    if (a==nullptr){
        a = new string*[7];
        for (int i=0; i<7; i++){
            a[i] = nullptr;
        }
    }
    practiceSchedule = a;
    a = nullptr;
}

void Player::copy(const Player& source)
{
    name = source.name;
    priority = source.priority;
    lessonNeed = source.lessonNeed;
    lessonReceived = source.lessonReceived;
    scheduleFail = source.scheduleFail;
    if (source.practiceDays){
        practiceDays = new int[7];
        for (int i=0; i<7; i++){
            practiceDays[i] = source.practiceDays[i];
        }
    }
    if (source.practiceSchedule){
        practiceSchedule = new string*[7];
        for (int i=0; i<7; i++){
            if (source.practiceSchedule[i]){
                practiceSchedule[i] = new string[24];
                for(int j=0; j<24; j++){
                    practiceSchedule[i][j] = source.practiceSchedule[i][j];
                }
            }
            else practiceSchedule[i] = nullptr;
        }
    }
}

Player::Player(shared_ptr<Player>& player) {
    if (!player) return;
    *this = *player;
}

Player::Player(const Player& source)
{
    copy(source);
}

void Player::operator=(const Player& source)
{
    if (this == &source) {return;}
    if (practiceDays) delete[] practiceDays;
    if (practiceSchedule){
        for (int i=0; i<7; i++){
            delete[] practiceSchedule[i];
        }
        delete[] practiceSchedule;
    }
    copy(source);
}


Player::Player(Player&& source)
{
    name = source.name;
    priority = source.priority;
    lessonNeed = source.lessonNeed;
    lessonReceived = source.lessonReceived;
    scheduleFail = source.scheduleFail;
    practiceDays = source.practiceDays;
    practiceSchedule = source.practiceSchedule;

    source.name = "";
    source.priority = 0;
    source.lessonNeed = 0;
    source.lessonReceived = 0;
    source.scheduleFail = false;
    source.practiceDays = 0;
    source.practiceSchedule = 0;
}

void Player::operator=(Player&& source)
{
    swap(name, source.name);
    swap(priority, source.priority);
    swap(lessonNeed, source.lessonNeed);
    swap(lessonReceived, source.lessonReceived);
    swap(scheduleFail, source.scheduleFail);
    swap(practiceDays, source.practiceDays);
    swap(practiceSchedule, source.practiceSchedule);
}


Player::~Player()
{
    if (practiceDays) delete[] practiceDays;
    if (practiceSchedule){
        for (int i=0; i<7; i++){
            delete[] practiceSchedule[i];
        }
        delete[] practiceSchedule;
    }
}

string Player::getName(){ return name;}
unsigned Player::getPriority(){ return priority;}
void Player::setPriority(unsigned p) { priority = p;}
void Player::setPracticeSchedule(string**& a){
    if (a==nullptr){
        a = new string*[7];
        for (int i=0; i<7; i++){
            a[i] = nullptr;
        }
    }
    practiceSchedule = a;
    a = nullptr;
}
string** Player::getPracticeSchedule(){return practiceSchedule;}
unsigned Player::getLessonNeed(){return lessonNeed;}
void Player::decLessonNeed(){lessonNeed --;}
void Player::setLessonNeed(unsigned lN) { lessonNeed = lN;}
void Player::incLessonReceived(){lessonReceived ++;}
int Player::getLessonReceived(){return lessonReceived;}
void Player::lessonAdd(){
    incLessonReceived();
    decLessonNeed();
}
void Player::setScheduleFail(bool f) {scheduleFail = f;}
bool Player::getScheduleFail() {return scheduleFail;}
int* Player::getPracticeDays() {return practiceDays;}
