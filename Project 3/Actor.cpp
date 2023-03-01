#include <algorithm>
#include <iostream>

#include "Actor.h"
#include "GameConstants.h"
#include "StudentWorld.h"
#include "GraphObject.h"
#include "GameWorld.h"

using namespace std;
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void Player::setNewDir(int& direction){
    int newX, newY;
    if (180 - direction <= 0){
        m_notValidDir = direction - 180;
    }
    else{
        m_notValidDir = 180 + direction;
    }
    direction += 90;
    getPositionInThisDirection(direction, 16, newX, newY);
    int i = 0;
    if (!getWorld() -> hasSquare(newX, newY, i))
        direction += 180;
    if (direction == 180){
        setDirection(direction);
    }
    else
        setDirection(right);
    if (direction >= 360)
        direction -= 360;
}

bool Player::checkDirectionInFront(int dir){
    /*while (!checkDirectionInFront(dir)){
        int xNew, yNew;
        getPositionInThisDirection(dir, BOARD_WIDTH, xNew, yNew);
        int i = 0;
        if (!getWorld() -> hasSquare(xNew, yNew, i)){
            if (getWorld() -> hasSquare(getX(), getY() + BOARD_HEIGHT, i) && getWorld() -> hasSquare(getX(), getY() - BOARD_HEIGHT)){
                checkDirectionInFront(up);
            }
            else if (getWorld() -> hasSquare(getX() + BOARD_WIDTH, getY()) && getWorld() -> hasSquare(getX() - BOARD_WIDTH, getY())){
                checkDirectionInFront(down);
            }
            else
                setNewDir(m_direction);
                checkDirectionInFront(m_direction);
        }
        return false;
    }*/
    return true;
}

int Player::getTick(){
    int tick = m_ticksToMove / 8;
    if (m_ticksToMove % 8 == 0 && tick > 0)
        tick --;
    return tick;
}

void Player::setObjectType(std::string objectType){
    if (m_playerNumber == 1){
        Actor::setObjectType("peach");
    }
    else if (m_playerNumber == 2) {
        Actor::setObjectType("peach");
    }
    else 
        Actor::setObjectType("player");
}

void Player::doSomething(){
	if (m_waitToRoll){
        switch (getWorld()->getAction(m_playerNumber)) {
            case ACTION_NONE:
                return;
                break;
            case ACTION_ROLL:
                //int dice = randInt(1, 10);
                int dice = 1;
                m_ticksToMove = dice * 8;
                m_waitToRoll = false;
                break;
        }
    }
    else {
        if (m_ticksToMove % 8 == 0){
            int xNew, yNew;
            getPositionInThisDirection(m_direction, BOARD_WIDTH, xNew, yNew);
            int i = 0;
            if (!getWorld() -> hasSquare(xNew, yNew, i)){
                if (getWorld() -> hasSquare(getX(), getY() + BOARD_HEIGHT, i) && getWorld() -> hasSquare(getX(), getY() - BOARD_HEIGHT, i)){
                    m_direction = up;
                }
                else if (getWorld() -> hasSquare(getX() + BOARD_WIDTH, getY(), i) && getWorld() -> hasSquare(getX() - BOARD_WIDTH, getY(), i)){
                    m_direction = right;
                }
                else
                    setNewDir(m_direction);
            }
        }
 
        moveAtAngle(m_direction, 2);
        m_ticksToMove --;
        if (m_ticksToMove == 0)
            m_waitToRoll = true;
    }
}

void CoinSquare::doSomething(){
    return;
}

void DirectionSquare::doSomething(){
    if (getWorld() -> playerOnSquare(getX(), getY()).find("DirectionSquare")){
        cout << "Player on dir square" << endl;
    }
}
