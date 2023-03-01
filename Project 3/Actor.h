#ifndef ACTOR_H_
#define ACTOR_H_

#include "GameWorld.h"
#include "GraphObject.h"
#include "StudentWorld.h"

#include <string>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject {
    public:
        Actor(StudentWorld* world, int imageID, double startX, double startY, int startDirection, int depth = 0) 
        : GraphObject(imageID, startX, startY, startDirection = right, depth), 
        m_world(world), m_alive(true), m_objectType("actor") {};
        virtual void doSomething() = 0; // pure virtual function
        StudentWorld* getWorld() { return m_world; };
        virtual ~Actor(){}

        // Setters
        void setAlive(bool alive) {m_alive = alive;}
        virtual void addCoins(int coins){return;};
        virtual void addStar(int star){return;};
        virtual void setObjectType(std::string objectType){m_objectType = objectType;}

        // Getter
        bool isAlive() { return m_alive;}
        virtual int getCoins() const {}
        virtual int getStar() const {}
        virtual int getTick() const {}
        virtual std::string getObjectType() const {return m_objectType;}

    private:
        StudentWorld *m_world;
        bool m_alive;
        std::string m_objectType;
};

// PLayer Movement initialization


class Avatar : public Actor {
    public :
        Avatar(StudentWorld* world, int imageID, double startX, double startY, int playerNumber, int startDirection = right, int depth = 0) 
        : Actor(world, imageID, startX, startY, startDirection, depth), m_notValidDir(left){}
        void doSomething(){return;}
        int m_notValidDir;
    private:

};

class Player : public Avatar {
    public:
        Player(StudentWorld* world, int imageID, double startX, double startY, int playerNumber, int startDirection = right, int depth = 0) 
        : Avatar(world, imageID, startX, startY, startDirection, depth), m_ticksToMove(0), m_waitToRoll(true), m_direction(startDirection), 
        m_playerNumber(playerNumber), m_coins(0), m_stars(0), m_vortex(0){};
        virtual void doSomething();
        
        // Setters
        virtual void addCoins(int coins){m_coins += coins;}
        virtual void addStar(int star){m_stars += star;}
        void setObjectType(std::string objectType);

        // Getter
        virtual int getCoins() const {return m_coins;}
        virtual int getStar() const {return m_stars;}
        virtual int getTick();

        // Moving Functions
        void setNewDir(int& direction);
        bool checkDirectionInFront(int dir);
        

    private:
        int m_ticksToMove;
        int m_direction;
        int m_coins;
        int m_stars;
        int m_vortex;
        int m_playerNumber;
        bool m_waitToRoll;
        bool m_isNew;
};

class Bowser : public Avatar {
    public:
        Bowser(StudentWorld* world, int imageID, double startX, double startY, std::string objectType, int startDirection = right, int depth = 0) 
        : Avatar(world, imageID, startX, startY, startDirection, depth){}
        void doSomething(){return;}
};

class Boo : public Avatar {
    public:
        Boo(StudentWorld* world, int imageID, double startX, double startY, std::string objectType, int startDirection = right, int depth = 0) 
        : Avatar(world, imageID, startX, startY, startDirection, depth){}
        void doSomething(){return;}
};

// Square Initialization


class Square : public Actor {
    public:
        Square(StudentWorld* world, int imageID, double startX, double startY, std::string objectType, int startDirection = 0, int depth = 1) 
        : Actor(world, imageID, startX, startY, startDirection, depth) {Actor::setObjectType(objectType);}
        virtual void doSomething() = 0;
    private:

};

class CoinSquare : public Square {
    public:
        CoinSquare(StudentWorld* world, int imageID, double startX, double startY, std::string objectType)
        : Square (world, imageID, startX, startY, objectType), m_coin(3){objectType == "BlueSquare" ? m_coin = 3 : m_coin = -3;}
        virtual void doSomething();
    private:
        int m_coin;
};

class DirectionSquare : public Square {
    public:
        DirectionSquare(StudentWorld* world, int imageID, double startX, double startY, std::string objectType, int dir)
        : Square (world, imageID, startX, startY, objectType, dir), m_directionOfSquare(dir){setDirection(dir);}
        virtual void doSomething();

    private:
        int m_directionOfSquare;
};

class StarSquare : public Square {
    public:
        StarSquare(StudentWorld* world, int imageID, double startX, double startY, std::string objectType)
        : Square (world, imageID, startX, startY, objectType){}
        virtual void doSomething(){return;};

    private:
        int m_directionOfSquare;
};

class EventSquare : public Square {
    public:
        EventSquare(StudentWorld* world, int imageID, double startX, double startY, std::string objectType)
        : Square (world, imageID, startX, startY, objectType){}
        virtual void doSomething(){return;};

    private:
        int m_directionOfSquare;
};

#endif // ACTOR_H_
