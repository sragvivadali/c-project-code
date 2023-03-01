#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include "GameWorld.h"
#include "Board.h" // required to use our provided class
#include <cstddef>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), m_peach(nullptr), m_bank(0) {
}

// adding objects

bool StudentWorld::addPlayer(double x, double y, int num) {
    x *= (BOARD_WIDTH);
    y *= (BOARD_HEIGHT);
    if (x > VIEW_WIDTH || y > VIEW_HEIGHT)
        return false;
    addCoinSquare(x/BOARD_WIDTH, y/BOARD_HEIGHT, 'b');
    if (num == 0){
        m_peach = new Player(this, IID_PEACH, x, y,1);
        m_actors.push_back(m_peach);
        m_peach -> addCoins(3);
    }
    else {
        m_yoshi = new Player(this, IID_YOSHI,x,y,2);
        m_actors.push_back(m_yoshi);
        m_yoshi -> addCoins(3);
    }

    return true;
}

bool StudentWorld::addBaddie(double x, double y, int num) {
    x *= (BOARD_WIDTH);
    y *= (BOARD_HEIGHT);
    if (x > VIEW_WIDTH || y > VIEW_HEIGHT)
        return false;
    addCoinSquare(x/BOARD_WIDTH, y/BOARD_HEIGHT, 'b');
    if (num == 0){
        m_actors.push_back(new Bowser(this, IID_BOWSER, x, y, "Bowser"));
    }
    else {
        m_actors.push_back(new Boo(this, IID_BOO, x, y, "Boo"));
    }

    return true;
}

bool StudentWorld::addCoinSquare(double x, double y, char color){
    x *= (BOARD_WIDTH);
    y *= (BOARD_HEIGHT);
    if (x > VIEW_WIDTH || y > VIEW_HEIGHT)
        return false;
    switch (color){
        case 'b':
            m_actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, x, y, "BlueSquare"));
            break;
        case 'r':
            m_actors.push_back(new CoinSquare(this, IID_RED_COIN_SQUARE, x, y, "RedSquare"));
            break;
    }
    return true;
} 

bool StudentWorld::addDirSquare(double x, double y, int dir){
    x *= (BOARD_WIDTH);
    y *= (BOARD_HEIGHT);
    if (x > VIEW_WIDTH || y > VIEW_HEIGHT)
        return false;
    switch (dir){
        case 0:
            m_actors.push_back(new DirectionSquare(this, IID_DIR_SQUARE, x, y, "RightDirectionSquare", 0));
            break;
        case 90:
            m_actors.push_back(new DirectionSquare(this, IID_DIR_SQUARE, x, y, "UpDirectionSquare", 90));
            break;
        case 180:
            m_actors.push_back(new DirectionSquare(this, IID_DIR_SQUARE, x, y, "LeftDirectionSquare", 180));
            break;
        case 270:
            m_actors.push_back(new DirectionSquare(this, IID_DIR_SQUARE, x, y, "DownDirectionSquare", 270));
            break;
    }
    return true;
} 

bool StudentWorld::addStarSquare(double x, double y){
    x *= (BOARD_WIDTH);
    y *= (BOARD_HEIGHT);
    if (x > VIEW_WIDTH || y > VIEW_HEIGHT)
        return false;

    m_actors.push_back(new StarSquare(this, IID_STAR_SQUARE, x, y, "StarSquare"));
}

bool StudentWorld::addEventSquare(double x, double y){
    x *= (BOARD_WIDTH);
    y *= (BOARD_HEIGHT);
    if (x > VIEW_WIDTH || y > VIEW_HEIGHT)
        return false;

    m_actors.push_back(new EventSquare(this, IID_EVENT_SQUARE, x, y, "EventSquare"));
}

// checks if there is a square at the location
bool StudentWorld::hasSquare(int x, int y, int&i){
    for (Actor* actor : m_actors){
        i ++;
        if (actor -> getObjectType().find("Square")){
            if (actor -> getX() == x && actor -> getY() == y){
                return true;
            }
        }
    }
    return false;
}

std::string StudentWorld::playerOnSquare(int x, int y){
    int i1 = 0;
    int i2 = 0;
    if(hasSquare(m_peach -> getX(), m_peach -> getY(), i1) || hasSquare(m_yoshi -> getX(), m_yoshi -> getY(), i2))
        return m_actors[i1] -> getObjectType();
}

// adds coins to new Player

int StudentWorld::init()
{
    startCountdownTimer(99); // supposed to be 99
    Board bd;
    char boardNum = getBoardNumber() + 48;
    string board = "board0";
    board += boardNum;
    board += ".txt";
    string board_file = assetPath() + board;
    Board::LoadResult result = bd.loadBoard(board_file);
    if (result == Board::load_fail_file_not_found)
        cerr << "Could not find board01.txt data file\n";
    else if (result == Board::load_fail_bad_format)
        cerr << "Your board was improperly formatted\n";
    else if (result == Board::load_success) {
        cerr << "Successfully loaded board\n";
        for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {
                Board::GridEntry ge = bd.getContentsOf(x, y);
                switch (ge) {
                    case Board::empty:
                        cout << "Location " << x << "," << y << " is empty\n";
                        break;
                    case Board::player:
                        cout << "Location " << x << "," << y << " has Peach & Yoshi and a blue coin square\n";
                        addPlayer(x, y, 0);
                        addPlayer(x, y, 1);
                        break;
                    case Board::blue_coin_square:
                        cout << "Location " << x << "," << y << " has a blue coin square\n";
                        addCoinSquare(x, y, 'b');
                        break;
                    case Board::red_coin_square:
                        cout << "Location " << x << "," << y << " has a red coin square\n";
                        addCoinSquare(x, y, 'r');
                        break;
                    case Board::left_dir_square:
                        cout << "Location " << x << "," << y << " has a left direction square\n";
                        addDirSquare(x, y,  180);
                        break;
                    case Board::right_dir_square:
                        cout << "Location " << x << "," << y << " has a right direction square\n";
                        addDirSquare(x, y,  0);
                        break;
                    case Board::up_dir_square:
                        cout << "Location " << x << "," << y << " has a up direction square\n";
                        addDirSquare(x, y,  90);
                        break;
                    case Board::down_dir_square:
                        cout << "Location " << x << "," << y << " has a down direction square\n";
                        addDirSquare(x, y,  270);
                        break;
                    case Board::star_square:
                        cout << "Location " << x << "," << y << " has a star square\n";
                        addStarSquare(x, y);
                        break;
                    case Board::event_square:
                        cout << "Location " << x << "," << y << " has a event square\n";
                        addEventSquare(x, y);
                        break;
                    case Board::bank_square:
                        cout << "Location " << x << "," << y << " has a bank square\n";
                        m_actors.push_back(new EventSquare(this, IID_BANK_SQUARE, x * 16, y * 16, "BankSquare"));
                        break;
                    case Board::bowser:
                        cout << "Location " << x << "," << y << " has bowser\n";
                        addBaddie(x, y, 0);
                        break;
                    case Board::boo:
                        cout << "Location " << x << "," << y << " has boo\n";
                        addBaddie(x, y, 1);
                        break;
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
// page 18
{
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.

    for (int i = 0; i < m_actors.size(); i ++){
        if (m_actors[i] -> isAlive()){
            m_actors[i] -> doSomething();
        }
        else{
            delete m_actors[i];
            m_actors.erase(m_actors.begin() + i); 
            i --;
        }
    }

    ostringstream ossP1;
    ostringstream timer;
    ostringstream ossP2;

    ossP1 << "P1 Roll:  " << m_peach -> getTick() << " Stars: " << m_peach -> getStar() << " $$: " << m_peach -> getCoins();
    timer << " | Timer " << this -> timeRemaining() << " | Bank " << m_bank << " | ";
    ossP2 << "P2 Roll: " << m_yoshi -> getTick() << " Stars: " << m_yoshi -> getStar() << " $$: " << m_yoshi -> getCoins();
    
    string s = ossP1.str() + timer.str() + ossP2.str();
    setGameStatText(s);
    
    if (timeRemaining() <= 0){
		setFinalScore(m_peach -> getStar(), m_peach -> getCoins());
        return GWSTATUS_PEACH_WON;
    }
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
// page 21
{
    for (Actor* c : m_actors)
        delete c;
    m_actors.clear();
}

StudentWorld::~StudentWorld(){
    cleanUp();
}
