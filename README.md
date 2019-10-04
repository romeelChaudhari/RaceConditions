# CSC 415 - Project 4 - Thread Racing

## Student Name: Romeel Chaudhari

## Student ID :  917262962

## Build Instructions
To build the code go to the respective directory and type in the following command gcc "pthread_race.c"
## Run Instructions
To run the file after building type the following command ./.a.out
## Explain why your program produces the wrong output
Because multiple threads are accessing the shared data and they try to change it at the same time, which is also called as race condition. 
