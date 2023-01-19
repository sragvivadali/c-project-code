#include <iostream>
#include <string>
#include "History.h"
#include "globals.h"

using namespace std;

History::History(int nRows, int nCols) {
  m_cols = nCols;
  m_rows = nRows;
  for (int r = 0; r < m_rows; r++) {
    for (int c = 0; c < m_cols; c++) {
      m_nCarrot[r][c] = 0;
    }
  }
}

bool History::record(int r, int c) {
  r--;
  c--;
  if ((r > 0) & (r < m_rows) & (c > 0) & (c < m_cols)) {
    if (m_nCarrot[r][c] != 26) {
      m_nCarrot[r][c]++;
      return true;
    }
  }
  return false;
}

void History::display() const {
  char m_historyDisplay[MAXROWS][MAXCOLS];
  for (int r = 0; r < m_rows; r++) {
    for (int c = 0; c < m_cols; c++) {
      if (m_nCarrot[r][c] == 0) {
        m_historyDisplay[r][c] = '.';
      } else {
        m_historyDisplay[r][c] = 64 + m_nCarrot[r][c];
      }
      cout << m_historyDisplay[r][c];
    }
    cout << endl;
  }
  cout << endl;
}
