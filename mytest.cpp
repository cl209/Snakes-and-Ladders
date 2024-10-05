#include "snakes.h"
using namespace std;

class Tester {
public:
    bool altConstructorNormal(); 
    bool altConstructorError();
    bool functRestartNormal();
    bool overloadedAssignmentNormal(); 
    bool overloadedAssignmentEdge();
    bool playSnakeNormal();
    bool playLadderNormal();
    bool makeDefaultBoardNormal();
    bool makeRandomBoardNormal();
    bool makeRandomBoardError();
};

bool Tester::altConstructorNormal(){
    Snakes obj(9); //snake obj for default board

    //Check for starting positions and player turn when object is created
    if (!(obj.m_player1 == obj.m_start && obj.m_player2 == obj.m_start && obj.m_playerTurn == 1)){
        return false;
    }

    //Traverse the linked list and check
    Cell *cell = obj.m_start;
    int counter = 0;
    while (cell != nullptr){
        cell = cell->getNext();
        counter++;
    }
    if (counter != 9){
        return false;
    }

    return true;

}
bool Tester::altConstructorError(){
    Snakes obj(27); //Create invalid board

    //Check for starting positions and player turn when object is created
    if (!(obj.m_player1 == obj.m_start && obj.m_player2 == obj.m_start && obj.m_playerTurn == 1)){
        return false;
    }


    Cell *cell = obj.m_start;
    int counter = 0;
    while (cell != nullptr){
        cell = cell->getNext();
        counter++;
    }


    //Check that invalid is turned into valid
    if (counter != 25){
        return false;
    }

    return true;

}
bool Tester::functRestartNormal(){
    Snakes obj(25); //Create snake object
    obj.reStart(); //Restart the game

    //Check that restart is working, no need to simulate a game
    if (!(obj.m_player1 == obj.m_start || obj.m_player2 == obj.m_start || obj.m_playerTurn == 1)) {
        return false;
    }
    return true;
}
bool Tester::overloadedAssignmentNormal() {
    Snakes obj1(9);  // Create the first object
    Snakes obj2;     // Create an empty object

    obj2 = obj1;     // Call the overloaded assignment operator

    // Create temp pointers to traverse both obj1 and obj2
    Cell *object1 = obj1.m_start;
    Cell *object2 = obj2.m_start;

    // Check that the contents of both are the same
    while (object1 != nullptr && object2 != nullptr) {
        // Compare the values (IDs) of the cells
        if (object1->getID() != object2->getID()) {
            return false;  // IDs should match
        }

        // Snake (south) check
        if (object1->getSouth() != nullptr && object2->getSouth() != nullptr) {
            if (object1->getSouth()->getID() != object2->getSouth()->getID()) {
                return false;  // The snake destinations should match
            }
        } else if (object1->getSouth() != nullptr || object2->getSouth() != nullptr) {
            return false;  // One has a snake, the other doesn't
        }

        // Ladder (north) check
        if (object1->getNorth() != nullptr && object2->getNorth() != nullptr) {
            if (object1->getNorth()->getID() != object2->getNorth()->getID()) {
                return false;  // The ladder destinations should match
            }
        } else if (object1->getNorth() != nullptr || object2->getNorth() != nullptr) {
            return false;  // One has a ladder, the other doesn't
        }

        // Move to the next cell
        object1 = object1->getNext();
        object2 = object2->getNext();
    }

    // Now check for different memory addresses
    object1 = obj1.m_start;  // Reinitialize to start of obj1
    object2 = obj2.m_start;  // Reinitialize to start of obj2

    while (object1 != nullptr && object2 != nullptr) {
        // Compare the memory addresses
        if (object1 == object2) {
            return false;  // They should point to different memory addresses
        }

        // Snake (south) memory check
        if (object1->getSouth() != nullptr && object2->getSouth() != nullptr) {
            if (object1->getSouth() == object2->getSouth()) {
                return false;  // Snake destinations should be in different memory locations
            }
        }

        // Ladder (north) memory check
        if (object1->getNorth() != nullptr && object2->getNorth() != nullptr) {
            if (object1->getNorth() == object2->getNorth()) {
                return false;  // Ladder destinations should be in different memory locations
            }
        }

        // Move to the next cell
        object1 = object1->getNext();
        object2 = object2->getNext();
    }

    return true;  // If no issues, the test passes
}

bool Tester::overloadedAssignmentEdge(){
    Snakes object1(25);//Create a snake object
    Snakes object2(9);//Create another

    object2 = object1;//Assign object 1 to object 2

    Cell *obj1 = object1.m_start;
    Cell *obj2 = object2.m_start;

    //Traverse and check that it is the same
    while (obj1 != nullptr && obj2 != nullptr){
        if (obj1->getID() != obj2->getID()){
            return false;
        }
        obj1 = obj1->getNext();
        obj2 = obj2->getNext();
    }

    //Clear object 2
    object2.clear();

    //Check for object 2
    if (object2.m_start != nullptr || object2.m_player1 != nullptr || object2.m_player2 != nullptr || object2.m_playerTurn != 0){
        return false;
    }

    //Assign object 1 to the cleared board, object 2
    object1 = object2;

    //Check object 1 is correct
    if (object1.m_start != nullptr || object1.m_player1 != nullptr || object1.m_player2 != nullptr || object1.m_playerTurn != 0){
        return false;
    }
    
    //Else true
    return true;
}

bool Tester::playSnakeNormal(){
    Snakes obj(25);//Create object

    //Temp pointer
    Cell *object = obj.m_start;
    Cell *snake;//For storing snake destination

    //While iteration to store snake
    while (object != nullptr){
        if (object->m_south != nullptr){
            snake = object;
            break;
        }
        object = object->getNext();
    }
    //Check if snakes
    if (snake->m_south == nullptr){
        return false;
    }

    //Store diceroll value and play
    int diceRoll = snake->getID() - obj.m_player1->getID();
    obj.play(diceRoll);

    //Check that the move happened
    if (obj.m_player1 != snake->getSouth()){
        return false;
    }

    //Else true
    return true;
}

bool Tester::playLadderNormal(){
    Snakes obj(25);//Create object

    //Temp pointer
    Cell *object = obj.m_start;
    Cell *ladder;//For storing snake destination

    //While iteration to store snake
    while (object != nullptr){
        if (object->m_north != nullptr){
            ladder = object;
            break;
        }
        object = object->getNext();
    }
    //Check if ladder
    if (ladder->m_north == nullptr){
        return false;
    }

    //Store diceroll value and play
    int diceRoll = ladder->getID() - obj.m_player1->getID();
    obj.play(diceRoll);

    //Check that the move happened
    if (obj.m_player1 != ladder->getNorth()){
        return false;
    }

    //Else true
    return true;
}
bool Tester::makeDefaultBoardNormal(){
    int size = 25;
    Snakes obj; //snake obj
    obj.makeDefaultBoard(size);//Make default board


    //Check for starting positions and player turn when object is created
    if (!(obj.m_player1 == obj.m_start && obj.m_player2 == obj.m_start && obj.m_playerTurn == 1)){
        return false;
    }

    //Traverse the linked list and check
    Cell *cell = obj.m_start;
    int counter = 0;
    while (cell != nullptr){
        cell = cell->getNext();
        counter++;
    }
    if (counter != size){
        return false;
    }

    return true;
    
}
bool Tester::makeRandomBoardNormal(){
    Snakes obj;//create snake object
    obj.makeRandomBoard(25, 10);//Create 5x5 with 10 numSnakesLadder

    //Counter for numSnakesLadder and Cell
    int cellCounter = 0;
    int numSnakesLadder = 0;

    //Temp pointer
    Cell *object = obj.m_start;

    //Iterate through linked list for counter
    while (object != nullptr){
        //Check if object has either snake or ladder
        if(object->m_north != nullptr || object->m_south != nullptr){
            numSnakesLadder++;
        }
        //Check that they do not store both snake and ladder in same cell
        if(object->m_north != nullptr && object->m_south != nullptr){
            return false;
        }
        //Increment
        cellCounter++;
        //Assign next
        object = object->getNext();
    }

    //Check that it creates the desired cell and numSnakesLadder
    if (cellCounter != 25 || numSnakesLadder != 10){
        return false;
    }

    //Else true
    return true;
}
bool Tester::makeRandomBoardError(){
    Snakes obj;//create snake object
    obj.makeRandomBoard(27, 25);//Create board and numSnakesLadder with error case

    //Counter for numSnakesLadder and Cell
    int cellCounter = 0;
    int numSnakesLadder = 0;

    //Temp pointer
    Cell *object = obj.m_start;

    //Iterate through linked list for counter
    while (object != nullptr){
        //Check if object has either snake or ladder
        if(object->m_north != nullptr || object->m_south != nullptr){
            numSnakesLadder++;
        }
        //Check that they do not store both snake and ladder in same cell
        if(object->m_north != nullptr && object->m_south != nullptr){
            return false;
        }
        //Increment
        cellCounter++;
        //Assign next
        object = object->getNext();
    }

    //Check that it creates the desired cell and numSnakesLadder
    if (cellCounter != 25 || numSnakesLadder != 10){
        return false;
    }

    //Else true
    return true;
}
int main() {
    Tester test;

    cout << "altConstructorNormal: " << (test.altConstructorNormal() ? "PASS" : "FAIL") << endl;
    cout << "altConstructorError: " << (test.altConstructorError() ? "PASS" : "FAIL") << endl;
    cout << "functRestartNormal: " << (test.functRestartNormal() ? "PASS" : "FAIL") << endl;
    cout << "overloadedAssignmentNormal: " << (test.overloadedAssignmentNormal() ? "PASS" : "FAIL") << endl;
    cout << "overloadedAssignmentEdge: " << (test.overloadedAssignmentEdge() ? "PASS" : "FAIL") << endl;
    cout << "playSnakeNormal: " << (test.playSnakeNormal() ? "PASS" : "FAIL") << endl;
    cout << "playLadderNormal: " << (test.playLadderNormal() ? "PASS" : "FAIL") << endl;
    cout << "makeDefaultBoardNormal: " << (test.makeDefaultBoardNormal() ? "PASS" : "FAIL") << endl;
    cout << "makeRandomBoardNormal: " << (test.makeRandomBoardNormal() ? "PASS" : "FAIL") << endl;
    cout << "makeRandomBoardError: " << (test.makeRandomBoardError() ? "PASS" : "FAIL") << endl;

    return 0;
}

