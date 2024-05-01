#ifndef CARD_H
#define CARD_H

#include <iostream>
using namespace std;

class Card {
  private:
    char color;
    int value;
  public:
    // constructor
    Card();

    // methods
    void newCard();
    void cardPlayed();
    void setCard(char, int);
    char getColor()
      { return color; }
    int getValue()
      { return value; }

    // operator
    bool operator==(const Card &other) const
      { return (value == other.value || color == other.color); }
    bool operator<(const Card &other) const;
};  
Card::Card() {
  color = 'a';
  value = -1;
}
void Card::newCard() {
  // random color
  int randColorProb = rand() % 4;
  switch (randColorProb) {
    case 0: color = 'b'; break;
    case 1: color = 'r'; break;
    case 2: color = 'y'; break;
    case 3: color = 'g'; break;
  }

  // random number
  // 76 = 4 colors * (# of 0's) + 4 colors * (#'s 1-9 )
  int randCardValue = rand() % 76;

  // 4/76 chance to get 0, so first 4 are dedicated to zero
  if (randCardValue < 4) value = 0;
  else {
    // not looking at the first 4 values
    // because those are zero; resets range
    randCardValue -= 4;
    
    // integer division
    // truncates the decimal and rounds down
    // therefore, add 1 to round up

    // ex. randCardValue = 0 now (originally 4)
    // 0 / 8 = 0
    // 0 + 1 = 1, which is expected
    // ...
    // randCardValue = 71 (originally 75)
    // 71 / 8 = 8 
    // 8 + 1 = 9; Expected
    value = (randCardValue / 8) + 1;
  }
}
bool Card::operator<(const Card &other) const {
  if (color == other.color) {
    if (value < other.value) return true;
    else return false;
  } else return (color < other.color);
}
void Card::cardPlayed() {
  color = 'a';
  value = -1;
}
void Card::setCard(char c, int v) {
  if (c=='r'||c=='b'||c=='g'||c=='y') color = c;
  else cout << "Invalid color." << endl;

  if (v>=0 && v <=9) value = v;
  else cout << "Invalid value." << endl;
}

#endif