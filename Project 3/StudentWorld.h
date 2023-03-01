#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
// class Player;

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  virtual ~StudentWorld();
  
  bool addPlayer(double x, double y, int num);
  bool addBaddie(double x, double y, int num);
  bool addCoinSquare(double x, double y, char color);
  bool addDirSquare(double x, double y, int dir);
  bool addStarSquare(double x, double y);
  bool addEventSquare(double x, double y);
  
  bool hasSquare(int x, int y, int& i);
  std::string playerOnSquare(int x, int y);

private:
  Actor *m_peach;
  Actor *m_yoshi;
  std::vector<Actor*> m_actors;
  
  int m_bank;
};

#endif // STUDENTWORLD_H_
