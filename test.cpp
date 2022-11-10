/*
 * Copyright 2022 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <Chris Horger, Ella Coulter, Isabella Vong, Keith Wu>
 * <horgerc, emcoult, isvong, keithwu>
 *
 * Final Project - Elevators (Lab 9)
 */
 
////////////////////////////////////////////////
// You will submit test.cpp to the autograder //
// FOR LAB 8, but NOT the final project Core  //
////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "AI.h"
#include "Building.h"
#include "BuildingState.h"
#include "Elevator.h"
#include "Floor.h"
#include "Game.h"
#include "Move.h"
#include "Person.h"
#include "SatisfactionIndex.h"
#include "Utility.h"

using namespace std;

// declare your test functions here
void person_tests();
void elevator_tests();
void floor_tests();
void move_tests();
void game_tests();
void file_tests();

void start_tests() {
    // call your test functions here
    person_tests();
    elevator_tests();
    floor_tests();
    move_tests();
    game_tests();
    file_tests();
    
    return;
}

void person_tests() {
    //initialize a person with targetFloor 5, anger 5

    cout << "########################" << endl;
    cout << "TESTING PERSON FUNCTIONS" << endl;
    cout << "########################" << endl << endl;

    cout << "----------------------------------------" << endl;
    cout << "Testing getTargetFloor and getAngerLevel" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    Person p("0f0t5a5");
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 5" << endl << endl;
    //simulate time being a multiple of TICKS_PER_ANGER_INCREASE

    cout << "---------------------------" << endl;
    cout << "Testing exploded and p.tick" << endl;
    cout << "---------------------------" << endl;
    cout << endl;

    bool exploded = p.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 0" << endl;
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    //simulate time not being a multiple
    p.tick(TICKS_PER_ANGER_INCREASE - 1);
    //no change
    p.tick(2);
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    cout << "Expected: f0t5a6, actual: ";
    p.print(cout);
    cout << endl << endl;

    cout << "----------------------------------" << endl;
    cout << "Testing incremental anger increase" << endl;
    cout << "----------------------------------" << endl;
    cout << endl;

    p.tick(TICKS_PER_ANGER_INCREASE); //7 after
    cout << p.getAngerLevel() << endl;
    p.tick(TICKS_PER_ANGER_INCREASE); //8 after
    cout << p.getAngerLevel() << endl;
    p.tick(TICKS_PER_ANGER_INCREASE); //9 after
    cout << p.getAngerLevel() << endl;
    exploded = p.tick(TICKS_PER_ANGER_INCREASE);

    cout << endl;
    cout << "-----------------------" << endl;
    cout << "Testing Explosion Count" << endl;
    cout << "-----------------------" << endl;
    cout << endl;

    cout << exploded << " Expected 1" << endl;

    cout << endl;
    cout << "------------------------" << endl;
    cout << "Testing New Person Print" << endl;
    cout << "------------------------" << endl;
    cout << endl;

    Person p2("1f2t3a4");
    cout << "Expected: f2t3a4, actual: ";
    p2.print(cout);
    cout << endl;
}

void elevator_tests() {

    cout << endl << "##########################" << endl;
    cout << "TESTING ELEVATOR FUNCTIONS" << endl;
    cout << "##########################" << endl << endl;

    Elevator e1;
    cout << "Expected: 0w, actual: ";
    e1.print(cout);
    cout << endl;

    e1.serviceRequest(3);
    e1.tick(TICKS_PER_ELEVATOR_MOVE);
    cout << "Expected: 1s3, actual: ";
    e1.print(cout);
    cout << endl;

    Elevator e2;
    e2.tick(3);
    cout << "Expected: 0s0, actual: ";
    e2.print(cout);

    cout << endl;
    cout << "Expected: 1, actual: " << e1.getCurrentFloor() << endl;
    cout << "Expected: 3, actual: " << e1.getTargetFloor() << endl;
    cout << "Expected: 1, actual: " << e1.isServicing() << endl;
    e1.tick(TICKS_PER_ELEVATOR_MOVE);
    e1.tick(TICKS_PER_ELEVATOR_MOVE);
    cout << "Expected: 0, actual: " << e1.isServicing() << endl;
    e1.serviceRequest(1);
    e1.tick(TICKS_PER_ELEVATOR_MOVE);
    cout << "Expected: 2, actual: " << e1.getCurrentFloor() << endl;
    cout << endl;
}

void floor_tests() {

    Floor f1;
    Person p1;
    cout << endl;
    cout << "#######################" << endl;
    cout << "TESTING FLOOR FUNCTIONS" << endl;
    cout << "#######################" << endl;
    cout << endl;

    cout << endl;
    cout << "-------------------" << endl;
    cout << "TESTING ADD AND GET" << endl;
    cout << "-------------------" << endl;
    cout << endl;

    f1.addPerson(p1, 10);

    f1.tick(1);
    f1.tick(2);
    f1.tick(3);
    f1.tick(4);
    f1.tick(5);

    cout << "Expected: f0t0a1, Actual ";
    cout << f1.getPersonByIndex(0) << endl;
}

void move_tests() {
    Move move1("");
    Move move2("s");
    Move move3("q");
    Move move4("e1p");
    Move move5("e1f4");
    Move invalid_move1("e4f5");
    Move valid_move1("e2f0");
    Move invalid_move2("e1f2");

    Elevator elevators[NUM_ELEVATORS];
    elevators[0] = Elevator();
    elevators[1] = Elevator();
    elevators[2] = Elevator();
    elevators[2].setCurrentFloor(3);

    cout << endl;
    cout << "######################" << endl;
    cout << "TESTING MOVE FUNCTIONS" << endl;
    cout << "######################" << endl;
    cout << endl;

    cout << "------------------------" << endl;
    cout << "TESTING GETTER FUNCTIONS" << endl;
    cout << "------------------------" << endl;
    cout << endl;

    cout << "Move """ << endl;
    cout << "Elevator ID: " << move1.getElevatorId() << endl;
    cout << "Target Floor: " << move1.getTargetFloor() << endl;
    cout << "Number to Pick up: " << move1.getNumPeopleToPickup() << endl;
    cout << "Total Satisfaction: " << move1.getTotalSatisfaction() << endl;

    cout << "Move 'e1f4'" << endl;
    cout << "Elevator ID: " << move5.getElevatorId() << endl;
    cout << "Target Floor: " << move5.getTargetFloor() << endl;
    cout << "Number to Pick up: " << move5.getNumPeopleToPickup() << endl;
    cout << "Total Satisfaction: " << move5.getTotalSatisfaction() << endl;

    cout << endl;
    cout << "-------------------" << endl;
    cout << "TESTING VALID MOVES" << endl;
    cout << "-------------------" << endl;
    cout << endl;

    cout << "Expects 1: " << move1.isValidMove(elevators) << endl;
    cout << "Expects 1: " << move3.isValidMove(elevators) << endl;
    cout << "Expects 1: " << valid_move1.isValidMove(elevators) << endl;

    cout << endl;
    cout << "---------------------" << endl;
    cout << "TESTING INVALID MOVES" << endl;
    cout << "---------------------" << endl;
    cout << endl;

    cout << "Expects 0: " << invalid_move1.isValidMove(elevators) << endl;
    cout << "Expects 0: " << invalid_move2.isValidMove(elevators) << endl;

    cout << "TESTING setPeopleToPickup" << endl;
    Floor a;
    Floor b;
    a.addPerson(Person(), 4);
    a.addPerson(Person(), -2);
    a.addPerson(Person(), 3);

    int newlist[MAX_PEOPLE_PER_FLOOR];

    move5.setPeopleToPickup("23", 0, b);
    cout << "TARGET FLOOR: " << elevators[1].getTargetFloor() << endl;
    cout << "CURRENT FLOOR: " << elevators[1].getCurrentFloor() << endl;
    cout << "num people to pick up" << move5.getNumPeopleToPickup() << endl;
    move5.copyListOfPeopleToPickup(newlist);
    cout << newlist[0] << endl;
    cout << move5.getTotalSatisfaction() << endl;
}

void game_tests() {
    Game Newgame;

    cout << endl;
    cout << "####################################" << endl;
    cout << "Testing Game Functions IsValidPickup" << endl;
    cout << "####################################" << endl;

    cout << endl;
    cout << "---------------" << endl;
    cout << "TRUE CONDITIONS" << endl;
    cout << "---------------" << endl;
    cout << endl;

    bool test = Newgame.isValidPickupList("9876543210", 2);
    cout << test << endl;
    test = Newgame.isValidPickupList("9876543210", 3);
    cout << test << endl;
    test = Newgame.isValidPickupList("0", 9);
    cout << test << endl;
    test = Newgame.isValidPickupList("5", 4);
    cout << test << endl;
    test = Newgame.isValidPickupList("5", 5);
    cout << test << endl;
    test = Newgame.isValidPickupList("5", 6);
    cout << test << endl;

    cout << endl;
    cout << "----------------" << endl;
    cout << "FALSE CONDITIONS" << endl;
    cout << "----------------" << endl;
    cout << endl;

    test = Newgame.isValidPickupList("01135", 1);
    cout << test << endl;
    test = Newgame.isValidPickupList("99", 0);
    cout << test << endl;
}

void file_tests() {
    cout << endl;
    cout << "#############################" << endl;
    cout << "TESTING FILE OPENING FUNCTION" << endl;
    cout << "#############################" << endl;
    cout << endl;

    // open one of the text files that are part of the starter code
    ifstream ins;
    ins.open("new.in");
    // if the file was not in the correct directory, the stream state is fail
    if (ins.fail()) {
        cout << "Could not open new.in" << endl;
    }
    else {
        cout << "Success! Text files are in the right directory." << endl;
    }
    return;
}