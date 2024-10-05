// UMBC - CMSC 341 - Fall 2024 - Proj1
#include "snakes.h"
Snakes::Snakes(){ 
    //Empty object
    m_start = nullptr;     
    m_player1 = nullptr;
    m_player2 = nullptr;
    m_playerTurn = 0;
}
Snakes::~Snakes(){
    clear();
}
void Snakes::clear(){
    //While loop to delete
    while (m_start != nullptr){
        Cell *next = m_start->m_next;
        delete m_start;
        m_start = next;
    }

    //Set to empty
    m_start = nullptr;     
    m_player1 = nullptr;
    m_player2 = nullptr;
    m_playerTurn = 0;
}
const Snakes & Snakes::operator=(const Snakes & rhs){
    //Self assignment, check for if the current object is the same as rhs
    if (this == &rhs){
        //Return the value/object since they are the same
        return *this;
    }
    //If not same, clear lhs board for the new object
    this->clear();


    //Check if the rhs object is empty
    if (rhs.m_start != nullptr){
        //Create the first copy cell
        this->m_start = new Cell(rhs.m_start->getID());

        //Pointers for temp use
        Cell *next = rhs.m_start->getNext();
        Cell *temp = this->m_start;

        //While loop to create cells
        while (next != nullptr){
            Cell *newCell = new Cell(next->getID());
            temp->setNext(newCell);
            temp = newCell;
            next = next->getNext();
        }

        //Reinitialize temps
        next = rhs.m_start;
        temp = this->m_start;

        //While loop to implement snakes and ladders
        while (next != nullptr){
            if (next->m_south != nullptr){
                int snakeID = next->getSouth()->getID();
                Cell *snakeTail = this->m_start;
                while (snakeTail != nullptr && snakeTail->getID() != snakeID){
                    snakeTail = snakeTail->getNext();
                }
                temp->setSouth(snakeTail);
            }
            if (next->m_north != nullptr){
                int ladderID = next->getNorth()->getID();
                Cell *ladderTop = this->m_start;
                while (ladderTop != nullptr && ladderTop->getID() != ladderID){
                    ladderTop = ladderTop->getNext();
                }
                temp->setNorth(ladderTop);
            }
            temp = temp->getNext();
            next = next->getNext();
        }
    }
    //Set player
    this->m_player1 = this->m_start;
    this->m_player2 = this->m_start;

    //Set turn
    this->m_playerTurn = rhs.m_playerTurn;
    //Return copied object
    return *this;

}

int Snakes::rollDice(){
    //Return random num 1-6
    Random rand;
    rand.init(1, 6);
    return rand.getRandNum();

}

Snakes::Snakes(int boardSize){
    //If size is less than 9, create empty object
    if (boardSize < 9){
        m_start = nullptr;     
        m_player1 = nullptr;
        m_player2 = nullptr;
        m_playerTurn = 0;
        return;
    }
    
    //Square root the num given into int, int conversion for scaling down when given invalid input
    int sqrtNum = static_cast<int>(sqrt(boardSize));
    int size = sqrtNum * sqrtNum;


    //Intialize the first cell, use temporary pointer and iterate with for loop to create until boardSize is reached
    m_start = new Cell(1);
    Cell *temp = m_start;
    for (int i = 2; i <=size; i++){
        Cell *newCell = new Cell(i);
        temp->m_next = newCell;
        temp = newCell;
    }
    //Set player to first cell
    m_player1 = m_start;
    m_player2 = m_start;

    //Start with player 1
    m_playerTurn = 1;

    //Initialize number of snakes and ladders
    int numSnakesLadders = size/4;
    int numSnakes = numSnakesLadders/2;
    int numLadders = numSnakesLadders - numSnakes;
    

    //Create random class for picking random IDs
    Random random;
    random.init(2, size - 1);

    //Ensure evenly spread
    int minSizeDif = size/5;

    //Placing snakes
    for (int i = 0; i < numSnakes; i++) {
        Cell* snakeHead = nullptr;
        Cell* snakeTail = nullptr;
        do {
            int randomID1 = static_cast<int>(random.getRandNum());
            int randomID2 = static_cast<int>(random.getRandNum());
        
            // Find snakeHead by traversing the linked list
            Cell* current = m_start;  // Start at beginning
            while (current != nullptr) {
                if (current->getID() == randomID1) {
                    snakeHead = current;
                }
                current = current->getNext();  //Next cell
            }
            // Reset current
            current = m_start;  // Start again at the beginning
            while (current != nullptr) {
                if (current->getID() == randomID2) {
                    snakeTail = current;
                }
                current = current->getNext();  //Next cell
            }
        //Make sure that snakeHead id is greater than tail
        //Make sure that it has no ladder or snake already
        } while (abs(snakeHead->getID() - snakeTail->getID()) < minSizeDif || snakeHead == snakeTail || snakeHead == nullptr || snakeTail == nullptr || snakeHead->getID() < snakeTail->getID() || snakeTail->m_south != nullptr || snakeTail->m_north != nullptr || snakeHead->m_south != nullptr || snakeHead->m_north != nullptr);
        //Set m_south
        snakeHead->m_south = snakeTail;
    }

    //Placing ladder
    for (int i = 0; i <  numLadders; i++){
        Cell *ladderTop = nullptr;
        Cell *ladderBottom = nullptr;
        do {
            int randomID1 = static_cast<int>(random.getRandNum());
            int randomID2 = static_cast<int>(random.getRandNum());

        //Find snakeHead by traversing the linked list
        Cell *current = m_start;//Start at beginning
        while (current != nullptr) {
            if (current->getID() == randomID1) {
                ladderTop = current;
            }
            current = current->getNext();//Next cell
        }

        //Reset current
        current = m_start; //Start again at the beginning
        while (current != nullptr) {
            if (current->getID() == randomID2) {
                ladderBottom = current;
            }
            current = current->getNext(); //Next cell
        }

        //Make sure that snakeHead id is greater than tail
        //Make sure that it has no ladder or snake already
        } while (abs(ladderTop->getID() - ladderBottom->getID()) < minSizeDif || ladderBottom == ladderTop || ladderBottom == nullptr || ladderTop == nullptr || ladderBottom->getID() > ladderTop->getID()|| ladderBottom->m_south != nullptr ||ladderBottom->m_north != nullptr || ladderTop->m_south != nullptr || ladderTop->m_north != nullptr);
        //Set m_north
        ladderBottom->m_north = ladderTop;
    }
}
bool Snakes::makeDefaultBoard(int boardSize){
    //Check if theres a board already
    if (m_start != nullptr){
        return false;
    }
    //If size is less than 9, false
    if (boardSize < 9){
        return false;
    }
    
    //Square root the num given into int, int conversion for scaling down when given invalid input
    int sqrtNum = static_cast<int>(sqrt(boardSize));
    int size = sqrtNum * sqrtNum;

    //Initialize number of snakes and ladders
    int numSnakesLadders = size/4;
    int numSnakes = numSnakesLadders/2;
    int numLadders = numSnakesLadders - numSnakes;


    //Intialize the first cell, use temporary pointer and iterate with for loop to create until boardSize is reached
    m_start = new Cell(1);
    Cell *temp = m_start;
    for (int i = 2; i <=size; i++){
        Cell *newCell = new Cell(i);
        temp->m_next = newCell;
        temp = newCell;
    }
    //Set player to first cell
    m_player1 = m_start;
    m_player2 = m_start;

    //Start with player 1
    m_playerTurn = 1;

    //Create random class for picking random IDs
    Random random;
    random.init(2, size - 1);

    //Ensure evenly spread
    int minSizeDif = size/5;

    //Placing snakes
    for (int i = 0; i < numSnakes; i++) {
        Cell *snakeHead = nullptr;
        Cell *snakeTail = nullptr;
        do {
            int randomID1 = static_cast<int>(random.getRandNum());
            int randomID2 = static_cast<int>(random.getRandNum());
        
            // Find snakeHead by traversing the linked list
            Cell* current = m_start;  // Start at beginning
            while (current != nullptr) {
                if (current->getID() == randomID1) {
                    snakeHead = current;
                }
                current = current->getNext();  //Next cell
            }
            // Reset current
            current = m_start;  // Start again at the beginning
            while (current != nullptr) {
                if (current->getID() == randomID2) {
                    snakeTail = current;
                }
                current = current->getNext();  //Next cell
            }
        //Make sure that snakeHead id is greater than tail
        //Make sure that it has no ladder or snake already
        } while (abs(snakeHead->getID() - snakeTail->getID()) < minSizeDif || snakeHead == snakeTail || snakeHead == nullptr || snakeTail == nullptr || snakeHead->getID() < snakeTail->getID() || snakeTail->m_south != nullptr || snakeTail->m_north != nullptr || snakeHead->m_south != nullptr || snakeHead->m_north != nullptr);
        //Set m_south
        snakeHead->m_south = snakeTail;
    }

    //Placing ladder
    for (int i = 0; i <  numLadders; i++){
        Cell *ladderTop = nullptr;
        Cell *ladderBottom = nullptr;
        do {
            int randomID1 = static_cast<int>(random.getRandNum());
            int randomID2 = static_cast<int>(random.getRandNum());

        //Find snakeHead by traversing the linked list
        Cell* current = m_start;//Start at beginning
        while (current != nullptr) {
            if (current->getID() == randomID1) {
                ladderTop = current;
            }
            current = current->getNext();//Next cell
        }
        //Reset current
        current = m_start; //Start again at the beginning
        while (current != nullptr) {
            if (current->getID() == randomID2) {
                ladderBottom = current;
            }
            current = current->getNext(); //Next cell
        }
        //Make sure that snakeHead id is greater than tail
        //Make sure that it has no ladder or snake already
        } while (abs(ladderTop->getID() - ladderBottom->getID()) < minSizeDif || ladderBottom == ladderTop || ladderBottom == nullptr || ladderTop == nullptr || ladderBottom->getID() > ladderTop->getID()|| ladderBottom->m_south != nullptr ||ladderBottom->m_north != nullptr || ladderTop->m_south != nullptr || ladderTop->m_north != nullptr);
        //Set m_north
        ladderBottom->m_north = ladderTop;
    }
    return true;
}
void Snakes::makeRandomBoard(int boardSize, int numSnakesLadders){
    //If size is less than 9, create empty object
    if (boardSize < 9){
        m_start = nullptr;     
        m_player1 = nullptr;
        m_player2 = nullptr;
        m_playerTurn = 0;
        return;
    }
    
    //Square root the num given into int, int conversion for scaling down when given invalid input
    int sqrtNum = static_cast<int>(sqrt(boardSize));
    int size = sqrtNum * sqrtNum;


    //Intialize the first cell, use temporary pointer and iterate with for loop to create until boardSize is reached
    m_start = new Cell(1);
    Cell *temp = m_start;
    for (int i = 2; i <=size; i++){
        Cell *newCell = new Cell(i);
        temp->m_next = newCell;
        temp = newCell;
    }

    //Initialize number of snakes and ladders
    int numSnakes = numSnakesLadders/2;
    int numLadders = numSnakesLadders - numSnakes;

    //Ensure that is at least greater than 2
    while (numSnakes + numLadders < 2){
        if (numSnakes == 0){
            numSnakes++;
        } else {
            numLadders++;
        }

    }

    //Ensure that it is not greater than half the boardsize minus 2
    while ((numSnakes + numLadders > (size/2)-2)){
        if (numSnakes > numLadders){
            numSnakes--;
        } else {
            numLadders--;
        }
    }
    

    //Create random class for picking random IDs
    Random random;
    random.init(2, size - 1);


    //Set player to first cell
    m_player1 = m_start;
    m_player2 = m_start;

    //Start with player 1
    m_playerTurn =1;

    //Placing snakes
    for (int i = 0; i < numSnakes; i++) {
        Cell* snakeHead = nullptr;
        Cell* snakeTail = nullptr;
        do {
            int randomID1 = static_cast<int>(random.getRandNum());
            int randomID2 = static_cast<int>(random.getRandNum());
        
            // Find snakeHead by traversing the linked list
            Cell* current = m_start;  // Start at beginning
            while (current != nullptr) {
                if (current->getID() == randomID1) {
                    snakeHead = current;
                }
                current = current->getNext();  //Next cell
            }
            // Reset current
            current = m_start;  // Start again at the beginning
            while (current != nullptr) {
                if (current->getID() == randomID2) {
                    snakeTail = current;
                }
                current = current->getNext();  //Next cell
            }
        //Make sure that snakeHead id is greater than tail
        //Make sure that it has no ladder or snake already
        } while (snakeHead == snakeTail || snakeHead == nullptr || snakeTail == nullptr || snakeHead->getID() < snakeTail->getID() || snakeTail->m_south != nullptr || snakeTail->m_north != nullptr || snakeHead->m_south != nullptr || snakeHead->m_north != nullptr);
        //Set m_south
        snakeHead->m_south = snakeTail;
    }

    //Placing ladder
    for (int i = 0; i < numLadders; i++){
        Cell *ladderTop = nullptr;
        Cell *ladderBottom = nullptr;
        do {
            int randomID1 = static_cast<int>(random.getRandNum());
            int randomID2 = static_cast<int>(random.getRandNum());

        //Find snakeHead by traversing the linked list
        Cell* current = m_start;//Start at beginning
        while (current != nullptr) {
            if (current->getID() == randomID1) {
                ladderTop = current;
            }
            current = current->getNext();//Next cell
        }

        //Reset current
        current = m_start; //Start again at the beginning
        while (current != nullptr) {
            if (current->getID() == randomID2) {
                ladderBottom = current;
            }
            current = current->getNext(); //Next cell
        }

        //Make sure that snakeHead id is greater than tail
        //Make sure that it has no ladder or snake already
        //Make sure that they don't lead to the same cell
        } while (ladderBottom == ladderTop || ladderBottom == nullptr || ladderTop == nullptr || ladderBottom->getID() > ladderTop->getID()|| ladderBottom->m_south != nullptr ||ladderBottom->m_north != nullptr || ladderTop->m_south != nullptr || ladderTop->m_north != nullptr);
        //Set m_north
        ladderBottom->m_north = ladderTop;
    }
    
}

bool Snakes::play(int dice) {
    // Counter to check for the last cell ID
    int lastCellID = 0;
    Cell *currCell = m_start;

    // Get the ID of the last cell
    while (currCell != nullptr) {
        lastCellID = currCell->getID();
        currCell = currCell->getNext();
    }

    // Player 1's turn
    if (m_playerTurn == 1) {
        int starterNum = m_player1->getID();
        int target = starterNum + dice;

        // If dice result goes beyond the last cell
        if (target > lastCellID) {
            m_playerTurn = 2;  // Switch to player 2's turn
            return true;
        }
        // If player lands exactly on the last cell
        else if (target == lastCellID) {
            while (m_player1->getID() != lastCellID) {
                m_player1 = m_player1->getNext();
            }
            // End the game when reaching the last cell
            return false;
        }
        // Valid move within boundaries
        else {
            //While loop to move player
            while (m_player1->getID() != target) {
                if (m_player1 == nullptr) {
                    return true;  // Safeguard against nullptr
                }
                m_player1 = m_player1->getNext();
            }
            //Move player for ladder
            if (m_player1->m_north != nullptr){
                m_player1 = m_player1->getNorth();
            }
            //Move player for snake
            if (m_player1->m_south != nullptr){
                m_player1 = m_player1->getSouth();
            }
            m_playerTurn = 2;  // Switch to player 2's turn
            return true;
        }
    }
    // Player 2's turn
    else if (m_playerTurn == 2) {
        int starterNum = m_player2->getID();  // Initialize target for player 2
        int target = starterNum + dice;

        // If dice result goes beyond the last cell
        if (target > lastCellID) {
            m_playerTurn = 1;  // Switch back to player 1's turn
            return true;
        }
        // If player lands exactly on the last cell
        else if (target == lastCellID) {
            while (m_player2->getID() != lastCellID) {
                if (m_player2 == nullptr) {
                    return true;  // Safeguard against nullptr
                }
                m_player2 = m_player2->getNext();
            }
            // End the game when reaching the last cell
            return false;
        }
        // Valid move within boundaries
        else {
            while (m_player2->getID() != target) {
                if (m_player2 == nullptr) {
                    return true;  // Safeguard against nullptr
                }
                m_player2 = m_player2->getNext();
            }
            if (m_player2->m_north != nullptr){
                m_player2 = m_player2->getNorth();
            }
            //Move player for snake
            if (m_player2->m_south != nullptr){
                m_player2 = m_player2->getSouth();
            }
            m_playerTurn = 1;  // Switch back to player 1's turn
            return true;
        }
    }
    // Safeguard return statement(in case m_playerTurn is neither 1 nor 2)
    return false;
}


void Snakes::reStart(){
    if (m_start != nullptr){
        m_player1 = m_start;
        m_player2 = m_start;
        m_playerTurn =1;
    }
}

void Snakes::dumpBoard(){
    if (m_start != nullptr){
        int ladderCode, snakeCode;
        Cell *temp = m_start;
        cout << "START => ";
        while(temp != nullptr){
            cout << temp->m_cellID;

            if (temp == m_player1) cout << " (Player 1)";
            if (temp == m_player2) cout << " (Player 2)";
            if (temp->m_north != nullptr) ladderCode = temp->m_north->m_cellID;
            else ladderCode = -1;
            if (temp->m_south != nullptr) snakeCode = temp->m_south->m_cellID;
            else snakeCode = -1;
            if (ladderCode != -1 || snakeCode != -1){
                cout << " (";
                if (ladderCode != -1) cout << "\033[1;32mLadder to: " << ladderCode << "\033[0m";// green text
                if (snakeCode != -1) cout << "\033[1;31mSnake to: " << snakeCode << "\033[0m";//red text
                cout << ")";
            }
            cout << " => ";
            temp = temp->m_next;
        }
        cout << "END" << endl;
    }
}