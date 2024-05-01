#ifndef HAND_H
#define HAND_H

#include <iostream>
#include "Card.h"
using namespace std;

class Hand {
  private:
    Card *card = new Card[15];
    int numCards;
    void swap(Card &a, Card &b);
    void setColor(int);
    void resetColor();
  public:
    // constructor
    Hand();
    ~Hand()
    { delete[] card; }

    // methods
    void sortHand();
    void printHand(bool);
    void drawCard();
    void playCard(int);
    int unPlayedCards()
      { return 15 - numCards; }
    int playedCards()
      { return numCards; }

    // operator
    Card& operator[](int i)
      { return card[i]; }
};
Hand::Hand() {
  // fill first seven cards
  numCards = 7;
  for (int i = 0; i < numCards; i++)
    card[i].newCard();

  // fill other cards to default
  for (int i = numCards; i < 15; i++)
    card[i].cardPlayed();
}
void Hand::sortHand() {
  for (int i = 0; i < numCards-1; i++)
    for (int j = 0; j < numCards-1-i; j++)
      if (card[j+1] < card[j])
        swap(card[j+1], card[j]);
}
void Hand::swap(Card &a, Card &b) {
  Card temp = b;
  b = a;
  a = temp;
}
void Hand::printHand(bool show) {
  if (show) {
    for (int i = 0; i < numCards; i++) {
      if (card[i].getValue() != -1) {
        int sendColor;
        if (card[i].getColor() == 'g') sendColor = 2;
        else if (card[i].getColor() == 'r') sendColor = 1;
        else if (card[i].getColor() == 'b') sendColor = 4;
        else if (card[i].getColor() == 'y') sendColor = 3;
        setColor(sendColor);
        cout << card[i].getColor() << card[i].getValue();
        resetColor();
        cout << " ";
      }
    }
    cout << endl;
  } else {
    for (int i = 0; i < numCards; i++) {
      if (card[i].getValue() != -1)
        cout << "• ";
    }
    cout << endl;
  }
}
void Hand::drawCard() {
  for (int i = 0; i < 15; i++) {
    if (card[i].getValue() == -1 && card[i].getColor() == 'a') {
      card[i].newCard();
      numCards++;
      break;
    } else if (i == 14) {
      cout << "No space in hand left to draw!" << endl;
      break;
    }
  }
}
void Hand::playCard(int index) {
  card[index].cardPlayed();

  // past the index of the played card
  // move it down one to the left
  for (int i = index; i < numCards-1; i++)
    card[i] = card[i+1];

  // set the last card slot to used
  card[numCards-1].cardPlayed();
  
  // decrease num cards, then resort
  numCards--;
  sortHand();
}
void Hand::setColor(int color) {
  cout << "\033[" << (color+30) << "m";
}
void Hand::resetColor() {
  cout << "\033[0m";
}

#endif