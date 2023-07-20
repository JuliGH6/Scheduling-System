//Julian Worn
//07/17/2023
//driver.cpp

//Possible Driver Implementation for the Scheduling system to use Player, Node, and Coach class

#include <iostream>
#include "Coach.h"
using namespace std;


void PlayerSignUp(Coach& coach);
void WhoAreYou(Coach& coach);
void CoachInterface(Coach& coach);
void myPlayersInterface(Coach& coach);
void changeWorkHours(Coach& coach);
void myScheduleInterface(Coach& coach);



int main(){
    Coach John("John");
    WhoAreYou(John);
    return 0;
}

//start here and the whole system starts
//precondition: coach parameter must be provided
//postcondition: menu opens and further functions can be callled
void WhoAreYou(Coach& coach){
    int inp;
    cout << endl << endl;
    cout << "Hello\nIf you are a Player who signs up for tennis practice, enter 1.\n"
        << "If you are the Coach, enter 2.\nEnter -1 to leave." << endl;
    cin >> inp;
    cout << endl;
    if (inp == 1) PlayerSignUp(coach);
    if (inp == 2) CoachInterface(coach);
    if (inp == -1) cout << "GoodBye\n";
}

//gets called through WhoAreYou
//precondition: coach parameter must be provided
//postcondition: asks questions to create player and adds it in the coach newPlayers system
//Who are you function is called after
void PlayerSignUp(Coach& coach){
    cout << endl << endl << "Hello Player\n";
    string name;
    cout << "Enter Name (no spaces allowed): ";
    getline(cin, name);
    while (true){
        getline(cin, name);
        if (!coach.nameExists(name)) break;
        else cout << "Name exists already, try again\n";
    }
    
    int lessonNeed;
    while (true){
        cout << "How many lessons do you want to take per week? ";
        cin >> lessonNeed;
        if (lessonNeed <=7 && lessonNeed >= 1) break;
        else cout << "Lesson count needs to be between 1-7, try again.\n";
    }


    string weekdays[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    string** availability = new string*[7];

    for (int i=0; i<7; i++){
        string answer = "";
        cout << "Can you take lessons on " << weekdays[i] << " (y/n): ";
        cin >> answer;

        if (answer == "y"){
            int start;
            int end;
            while (true){
                cout << "At what time can you start (only full hours, e.g. 14 is 2pm): ";
                cin >> start;
                cout << "Till when are you available (must be later than start): ";
                cin >> end;
                if ((start >= 0 && start <= 23) && (end > start && end <= 24)) break;
                else cout << "Invalid times, try again.\n";
            }

            availability[i] = new string[24];
            for (int j=0; j<24; j++){
                if (j>=start && j<end) availability[i][j] = "1";
                else availability[i][j] = "0";
            }
        } else {
            availability[i] = nullptr;
        }
    }
    coach.addToNewPlayer(make_shared<Player>(name, lessonNeed, availability));
    cout << "The Player " << name << " got added\n";
    WhoAreYou(coach);
}

//gets called through WhoAreYou
//precondition: coach parameter must be provided
//postcondition: menu opens and further functions can be callled
void CoachInterface(Coach& coach){

    while (true){
        cout << endl << endl << "Hello Coach\n";
        if (!coach.getNoNewPlayers()) {
            cout << "There are some new Players that need to be rated first.\n";
            cout << "Enter 0 to rate them\n\n";
        }
        int inp;
        cout << "Enter 1 to go to schedule\n";
        cout << "Enter 2 to go to your Players\n";
        cout << "Enter 3 to change workHours\n";
        cout << "Enter -1 to go back\n";
        cin >> inp;
        if (inp == 0 && !coach.getNoNewPlayers()) coach.rateNewPlayers();
        if (inp == 1) myScheduleInterface(coach);
        if (inp == 2) myPlayersInterface(coach);
        if (inp == 3) changeWorkHours(coach);
        if (inp == -1) WhoAreYou(coach);
    }
}

//gets called through CoachInterface
//precondition: coach parameter must be provided
//postcondition: see all Players and option to rate newPlayers
void myPlayersInterface(Coach& coach){

    cout << endl << endl << "Your players: \n\n";
    coach.printRatedPlayers();
    if (!coach.getNoNewPlayers()) {
        cout << "There are some more new Players that need to be rated first.\n";
        cout << "Enter 0 to rate them\n";
    }
    cout << "Enter -1 to go back\n";
    int inp;
    cin >> inp;
    if (inp == -1) CoachInterface(coach);
    else if (inp == 0) {
        coach.rateNewPlayers();
        cout << endl << endl << "Your players: \n\n";
        coach.printRatedPlayers();
        CoachInterface(coach);
    }
}

//gets called through CoachInterface
//precondition: coach parameter must be provided
//postcondition: questionnaire to create workHours
void changeWorkHours(Coach& coach){
    string weekdays[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    string** workHours = new string*[7];
    for (int i=0; i<7; i++){
        string answer = "";
        cout << "Can you give lessons on " << weekdays[i] << " (y/n): ";
        cin >> answer;

        if (answer == "y"){
            int start;
            int end;
            while (true){
                cout << "At what time can you start (only full hours, e.g. 14 is 2pm): ";
                cin >> start;
                cout << "Till when are you available (must be later than start): ";
                cin >> end;
                if ((start >= 0 && start <= 23) && (end > start && end <= 24)) break;
                else cout << "Invalid times, try again.\n";
            }

            workHours[i] = new string[24];
            for (int j=0; j<24; j++){
                if (j>=start && j<end) workHours[i][j] = "1";
                else workHours[i][j] = "0";
            }
        } else {
            workHours[i] = nullptr;
        }
    }

    coach.setHours(workHours);
    CoachInterface(coach);
}

//gets called through CoachInterface
//precondition: coach parameter must be provided
//postcondition: prints schedule if all necessary part were provided, optional creation of cfv file
void myScheduleInterface(Coach& coach)
{
    if(!coach.getScheduleUpdated()) coach.makeSchedule();
    coach.printSchedule();
    int inp;
    cout << endl << endl << "Enter 0 to create csv file of schedule, enter -1 to go back: ";
    cin >> inp;
    if (inp == -1) CoachInterface(coach);
    if (inp == 0) {
        coach.createFile();
        CoachInterface(coach);
    }
}
