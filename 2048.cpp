#include <iostream>
using namespace std;

int TwoOrFour() {
  srand(time(0));
  if (rand() % 2 == 0) {
    return 2;
  }
  return 4;
}

int* _compress(int* x) {
  int* res;
  res = new int[4];
  int k = 0;
  for (int i = 0; i < 4; i++) {
    if (x[i] != 0) {
      res[k] = x[i];
      k++;
    }
  }
  while (k < 4) {
    res[k] = 0;
    k++;
  }
  return res;
}

void compress(int** x) {
  for (int i = 0; i < 4; i++) {
    x[i] = _compress(x[i]);
  }
}

int* _merge(int* x) {
  int* res;
  res = new int[4];
  int i = 0;
  int k = 0;
  while (k < 4) {
    if ((k + 1 < 4) && (x[k] == x[k + 1])) {
      res[i] = x[k] + x[k + 1];
      k += 2;
      i++;
    } 
    else {
      res[i] = x[k];
      k++;
      i++;
    }
  }
  while (i < 4) {
    res[i] = 0;
    i++;
  }
  return res;
}

void merge(int** x) {
  for (int i = 0; i < 4; i++) {
    x[i] = _merge(x[i]);
  }
}

int* _verticalTurn(int* x) {
  int* res;
  res = new int[4];
  for (int i = 0; i < 4; i++) {
    res[3 - i] = x[i];
  }
  return res;
}

void verticalTurn(int** x) {
  for (int i = 0; i < 4; i++) {
    x[i] = _verticalTurn(x[i]);
  }
}

void clockwise90(int** x) {
  int** res = new int*[4];
  for (int i = 0; i < 4; i++) {
    res[i] = new int[4];
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      res[j][3 - i] = x[i][j];
    }
  }
  for (int i = 0; i < 4; i++) {
    x[i] = res[i];
  }
}

class Board {
  private:
    int** board;

  public:
    Board();
    int getCell(int i, int j);
    void setCell(int i, int j, int newValue);
    int** emptyCells();
    int emptyCellsNumber();
    void generateTwoOrFour();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void printBoard();
};

Board::Board() {
  this->board = new int*[4];
  for (int i = 0; i < 4; i++) {
    this->board[i] = new int[4];
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      this->setCell(i, j, 0);
    }
  }
  generateTwoOrFour();
  generateTwoOrFour();
}

int Board::getCell(int i, int j) {
  return this->board[i][j];
}

void Board::setCell(int i, int j, int newValue) {
  this->board[i][j] = newValue;
}

int** Board::emptyCells() {
  int** res;
  res = new int*[16];
  int k = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (this->getCell(i, j) == 0) {
        res[k] = new int[2];
        res[k][0] = i;
        res[k][1] = j;
        k++;
      }
    }
  }
  return res;
}

int Board::emptyCellsNumber() {
  int res = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (this->getCell(i, j) == 0) {
        res++;
      }
    }
  }
  return res;
}

void Board::generateTwoOrFour() {
  int x = this->emptyCellsNumber();
  if (x == 0) {
    return;
  }
  srand(time(0));
  int y = rand() % x;
  this->setCell(this->emptyCells()[y][0], this->emptyCells()[y][1], TwoOrFour());
}

void Board::moveLeft() {
  compress(this->board);
  merge(this->board);
  generateTwoOrFour();
}

void Board::moveRight() {
  verticalTurn(this->board);
  compress(this->board);
  merge(this->board);
  verticalTurn(this->board);
  generateTwoOrFour();
}
void Board::moveUp() {
  clockwise90(this->board);
  clockwise90(this->board);
  clockwise90(this->board);
  compress(this->board);
  merge(this->board);
  clockwise90(this->board);
  generateTwoOrFour();
}

void Board::moveDown() {
  clockwise90(this->board);
  compress(this->board);
  merge(this->board);
  clockwise90(this->board);
  clockwise90(this->board);
  clockwise90(this->board);
  generateTwoOrFour();
}

void Board::printBoard() {
  for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
          cout << this->getCell(i, j) << "   ";
      }
      cout << "\n";
  }
}

int main() {
  Board b;
  char input;
  while (input != 'e') {
    b.printBoard();
    cout << "Enter wsad to move the cells, e to exit" << "\n";
    cin >> input;
    switch (input) {
      case 'w':
        b.moveUp();
        break;
      case 's':
        b.moveDown();
        break;
      case 'a':
        b.moveLeft();
        break;
      case 'd':
        b.moveRight();
        break;
      case 'e':
        break;
      default:
        cout << "invalid input" << "\n";
    }
  }
  return 0;
}