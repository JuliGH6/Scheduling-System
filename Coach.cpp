//Julian Worn
//07/17/2023
//Coach.cpp

//Source File for the Coach Class in the Scheduling system
//for pre/post conditions as well as class/implementation invariants, check header file Coach.h



#include "Coach.h"

Coach::Coach(string n){ name = n;}
Coach::Coach(string n, string**& hours){
    name = n;
    if (hours==nullptr){
        hours = new string*[7];
        for (int i=0; i<7; i++){
            hours[i] = nullptr;
        }
    }
    workSchedule = hours;
    hours = nullptr;
}

void Coach::copy(const Coach& source)
{
    name = source.name;
    scheduleUpdated = source.scheduleUpdated;
    string** workSchedule = nullptr;
    if (source.workSchedule){
        workSchedule = new string*[7];
        for (int i=0; i<7; i++){
            if (source.workSchedule[i]){
                workSchedule[i] = new string[24];
                for(int j=0; j<24; j++){
                    workSchedule[i][j] = source.workSchedule[i][j];
                }
            }
            else workSchedule[i] = nullptr;
        }
    }
    if (!source.newPlayers.empty()){
        queue<shared_ptr<Player>> tempQueue = source.newPlayers;
        while (!tempQueue.empty()) {
            shared_ptr<Player> playerPtr = tempQueue.front();
            newPlayers.push(make_shared<Player>(*playerPtr));
            tempQueue.pop();
        }
    }
    if (source.allPlayers){
        allPlayers = copyList(source.allPlayers);
    }
}
shared_ptr<Node> Coach::copyList(shared_ptr<Node> iter){
    if (!iter) return nullptr;
    shared_ptr<Node> newNode = make_shared<Node>(make_shared<Player>(iter->player));
    newNode->next = copyList(iter->next);
    return newNode;
}

Coach::Coach(const Coach& source)
{
    copy(source);
}
Coach::Coach(Coach&& source)
{
    name = source.name;
    scheduleUpdated = source.scheduleUpdated;
    workSchedule = source.workSchedule;
    newPlayers = source.newPlayers;
    allPlayers = source.allPlayers;

    source.name = "";
    source.scheduleUpdated = 0;
    source.workSchedule = 0;
    while(!source.newPlayers.empty()){
        source.newPlayers.pop();
    }
    source.allPlayers = 0;

}
void Coach::operator=(const Coach& source)
{
    if (workSchedule){
        for (int i=0; i<7; i++){
            delete[] workSchedule[i];
        }
        delete[] workSchedule;
    }
    while (!newPlayers.empty()){//manually decrease reference count so object gets deleted (smartpointer)
        newPlayers.pop();
    }
    allPlayers = nullptr; //nodes get deallocated through reference count in singly linked list
    copy(source);
}
void Coach::operator=(Coach&& source)
{
    swap(name, source.name);
    swap(scheduleUpdated, source.scheduleUpdated);
    swap(workSchedule, source.workSchedule);
    swap(newPlayers, source.newPlayers);
    swap(allPlayers, source.allPlayers);
}

Coach::~Coach()
{
    if (workSchedule){
        for (int i=0; i<7; i++){
            delete[] workSchedule[i];
        }
        delete[] workSchedule;
    }
    while (!newPlayers.empty()){//manually decrease reference count so object gets deleted (smartpointer)
        newPlayers.pop();
    }
    allPlayers = nullptr; //nodes get deallocated through reference count in singly linked list
}

void Coach::setHours(string**& hours){
    if (hours==nullptr){
        hours = new string*[7];
        for (int i=0; i<7; i++){
            hours[i] = nullptr;
        }
    }
    workSchedule = hours;
    hours = nullptr;
}
bool Coach::getNoNewPlayers(){return newPlayers.empty();}
void Coach::addToNewPlayer(shared_ptr<Player> p){
    newPlayers.push(p);
}
void Coach::rateNewPlayers(){
    while (!newPlayers.empty()){
        addPlayer(newPlayers.front());
        newPlayers.pop();
    }
    scheduleUpdated = false;
}
void Coach::addPlayer(shared_ptr<Player>& p){
    if (p == nullptr) return;
    int priority;
    cout << "Enter Priority for " << p->getName() << " or enter -1 to not add player: ";
    cin >> priority;
    if (priority == -1) return;
    p->setPriority(priority);
    if (!allPlayers){
        allPlayers = make_shared<Node>(p);
    }
    else if (allPlayers->player->getPriority() < p->getPriority()){ 
        allPlayers = make_shared<Node>(p, allPlayers);
    }
    else {
        shared_ptr<Node> temp = allPlayers;
        while (true){
            if (!temp->next){
                temp->next = make_shared<Node>(p);
                return;
            }
            if (temp->next->player->getPriority() >= p->getPriority()) temp = temp->next;
            else {
                temp->next = make_shared<Node>(p,temp->next);
                return;
            }
        }
    }
    scheduleUpdated = false;
}
void Coach::makeSchedule(){
    if (!workSchedule) return;
    shared_ptr<Node> temp = allPlayers;
    while(temp)
    {
        string** studentSchedule = temp->player->getPracticeSchedule();
        int* studentPracticeDays = temp->player->getPracticeDays();
        for (int i=0; i<7; i++)
        {
            if (temp->player->getLessonNeed() == 0) break;
            if (!workSchedule[i] || !studentSchedule[i]) continue;
            bool dayScheduled = false;
            for (int j=0; j<24; j++)
            {
                if(workSchedule[i][j]=="1" && studentSchedule[i][j]=="1")
                {
                    workSchedule[i][j] = temp->player->getName();
                    studentSchedule[i][j] = "P";
                    temp->player->lessonAdd();
                    dayScheduled = true;
                    break;
                }
            }
            if (dayScheduled) studentPracticeDays[i] = 1;
        }
        if (temp->player->getLessonNeed() != 0)
        {
            shared_ptr<Node> iter = allPlayers;
            while ((iter->player->getName() != temp->player->getName()) && temp->player->getScheduleFail())
            {
                string** iterSchedule = iter->player->getPracticeSchedule();
                int* iterPracticeDays = iter->player->getPracticeDays();
                for (int i=0; i<7; i++)
                {
                    if (!workSchedule[i] || !studentSchedule[i] || studentPracticeDays[i]==1 || iterPracticeDays==0) continue;
                    int dayMatch = -1;
                    int hourMatch = -1;
                    for(int j=0; j<24; j++)
                    {
                        if (studentSchedule[i][j] == "1" && iterSchedule[i][j] == "P")
                        {
                            dayMatch=i;
                            hourMatch=j;
                            break;
                        }
                    }
                    if (dayMatch == -1) continue;
                    for (int d=i; d<7; d++)
                    {
                        if (!workSchedule[d] || !iterSchedule[d] || (iterPracticeDays[d] == 1 && d!=i)) continue;
                        bool changed = false;
                        for (int k=0; k<24; k++)
                        {
                            if (workSchedule[d][k] == "1" && iterSchedule[d][k] == "1")
                            {
                                iterSchedule[d][k] = "P";
                                workSchedule[d][k] = iter->player->getName();
                                cout << "Print dM and hM: " << dayMatch << ", " << hourMatch << endl;
                                iterSchedule[dayMatch][hourMatch] = "1";
                                workSchedule[dayMatch][hourMatch] = temp->player->getName();
                                studentSchedule[dayMatch][hourMatch] = "P";
                                studentPracticeDays[dayMatch] = 1;
                                iterPracticeDays[d] = 1;
                                if (d!=i) iterPracticeDays[i] = 0;
                                temp->player->lessonAdd();
                                changed = true;
                                break;
                            }
                        }
                        if (changed) break;

                    }

                    if (temp->player->getLessonNeed() == 0) 
                    {
                        temp->player->setScheduleFail(false);
                        break;
                    }
                }
                iter = iter->next;
            }
        }
        if (temp->player->getLessonNeed() == 0) temp->player->setScheduleFail(false);
        temp = temp->next;
    }

    scheduleUpdated = true;

}
void Coach::printSchedule(){
    if (!workSchedule) {
        cout << "No work Hours provided yet";
        return;
    }
    cout << "0 - not available, 1 - available\n\n";
    cout << "     Monday  Tuesday  Wednesday Thursday  Friday  Saturday  Sunday\n";
    for (int i=0; i<24; i++){
        cout << i;
        for (int j=0; j<7; j++){
            if (workSchedule[j]) cout << "    " << workSchedule[j][i];
            else cout << "     0";
        }
        cout << endl;
    }
    cout << "These Players wishes are not satisfied:\n";
    cout << "Players get printed in the format Name, Priority, Lessons Needed, Lessons Planned\n";
    shared_ptr<Node> temp = allPlayers;
    while (temp){
        if (temp->player->getScheduleFail()){
            cout << temp->player->getName() << "," << temp->player->getPriority() << "," << temp->player->getLessonNeed()
                << "," << temp->player->getLessonReceived() << endl;
        }
        
        temp = temp->next;
    }
}
void Coach::printRatedPlayers(){
    if (!allPlayers){
        cout << "There are no rated Players currently\n";
        return;
    } 
    cout << "Players get printed in the format Name, Priority, Lessons Needed, Lessons Planned, full Scheduling Successful\n";
    if (!scheduleUpdated) cout << "The schedule is not updated currently\n";
    shared_ptr<Node> temp = allPlayers;
    while (temp) {
        cout << temp->player->getName() << "," << temp->player->getPriority() << "," << temp->player->getLessonNeed()
        << "," << temp->player->getLessonReceived();
        if (!temp->player->getScheduleFail()) cout << ", true" << endl;
        else cout << ", false" << endl;
        temp = temp->next;
    }
}
bool Coach::getScheduleUpdated(){ return scheduleUpdated;}
bool Coach::nameExists(string n){
    if (!allPlayers && newPlayers.empty()) return false;
    shared_ptr<Node> temp = allPlayers;
    while (temp)
    {
        if (temp->player->getName() == n) return true;
        temp = temp->next;
    }
    queue<shared_ptr<Player>> qcopy = newPlayers;
    while(!qcopy.empty()){
        if (n == qcopy.front()->getName()) return true;
        qcopy.pop();
    }
    return false;
}


void Coach::createFile(){
    if (!workSchedule){
        cout << endl << endl << "No Schedule exists yet";
        return;
    }
    ofstream myFile;
    myFile.open ("schedule.csv");
    myFile << ",Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday\n";
    for (int i=0; i<24; i++){
        myFile << i << ",";
        if (workSchedule[0]) myFile << workSchedule[0][i] << ",";
        else myFile << "0,";
        if (workSchedule[1]) myFile << workSchedule[0][i] << ",";
        else myFile << "0,";
        if (workSchedule[2]) myFile << workSchedule[0][i] << ",";
        else myFile << "0,";
        if (workSchedule[3]) myFile << workSchedule[0][i] << ",";
        else myFile << "0,";
        if (workSchedule[4]) myFile << workSchedule[0][i] << ",";
        else myFile << "0,";
        if (workSchedule[5]) myFile << workSchedule[0][i] << ",";
        else myFile << "0,";
        if (workSchedule[6]) myFile << workSchedule[0][i] << "\n";
        else myFile << "0\n";
    }
}


Coach Coach::operator+(const Player& p) const
{
    Coach local(*this);
    shared_ptr<Player> temp = make_shared<Player>(p);
    local.addPlayer(temp);
    return local;
}


Coach& Coach::operator+=(const Player& p)
{
    shared_ptr<Player> temp = make_shared<Player>(p);
    addPlayer(temp);
    return *this;
}


Coach operator+(const Player& p, const Coach& c)
{
    return (c+p);
}
