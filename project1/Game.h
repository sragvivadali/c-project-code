#ifndef GAME_H
#define GAME_H

#include <string>

class Arena;

bool decodeDirection(char ch, int &dir);
int computeDanger(const Arena &a, int r, int c);
bool recommendMove(const Arena &a, int r, int c, int &bestDir);

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
};

#endif
