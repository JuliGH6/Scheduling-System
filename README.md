# Scheduling-System
My Tennis-Coach complained about having to create a practice schedule twice a year, so I decided to create a program, which can do it for him.
Important to know:
  - a player can only have one hour practice lessons per day
  - the lessons start and end at a full hour
  - the players have different priorities, meaning that the scheduling of some players practice lessons have more importance than of others
  - Players with the same priority will be scheduled depending on who signed up for lessons first

To take the priorities into account, I decided to store the players in a priority queue. 
Knowing that the players will sign up over the course of multiple days, the time complexity of inserting a player was of less importance, than 
retrieving the Player with the highest priority which would happen in the "creating Schedule Process", which should be as fast as possible. 
That's why I decided to use a linked list implementation of the priority queue which has O(n) for adding a player, 
but O(1) retrieving and removing the player with the highest priority.

This programm demonstrates the use of smart pointers as well as raw pointers. 

Within my classes Player and Coach, I use encapsulation with getters and setters (if necessary), dependency injection with safety checks
and postponed instantiation of the schedules, as both classes can only accept availability schedules from the outside. Until then
the arrays are not initialized. Existence checks in the functions are provided.

Both classes provide deep copying and move semantics.

The Coach classes also provides overloaded functionality for the operators Coach + Player, Player + Coach, Coach += Player.

Additionally the Coach class provides a function that creates a cfv table file with the current schedule.

The Node class is only used for the linked list. It provides a customized constructor to pass in the former head of the linked list as parameter
and set it to the next pointer of the node, so the new node will be the head of the list.

The whole project is devided into multiple files and are compiled with the help of a makefile.

The driver is functionally decomposed. In the future I want to learn how to connect backend with frontend, to build a web-application to use the scheduling system.
With that in mind, more functionalities like e.g. removing players from the list manually can be added to the programm. It will also be my goal to make working on the 
schedule manually possible, in addition to the automatic creation.




