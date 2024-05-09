#include "Card.h"
#include "Hand.h"
#include <iostream>

// need these #includes to
// pause output 
// ex. bots are "thinking"
#include <thread>
#include <chrono>

using namespace std;

// prototypes
void Welcome();
string getName();
int nextTurn(int);
bool isWin(int);
void setColor(int);
void resetColor();
void endOfGame(int, int, int);
void printMiddleCard(char, int);
void Uno();

int main() {

  srand(time(0));
  Welcome();

  // variables
  string name = getName();
  bool play = true;
  int turn = rand() % 3 + 1;
  int playerNumPlays = 0;
  int c1NumPlays = 0;
  int c2NumPlays = 0;

  // initialize the card in the middle
  Card playCard;
  playCard.newCard();

  // initialize all hands
  Hand c1, c2, p1;

  while (play) {

    // display the current card in the middle
    // displays it in the current color!
    printMiddleCard(playCard.getColor(), playCard.getValue());

    // player's turn
    if (turn == 1) {
      playerNumPlays++;

      // print player turn
      cout << name << ", it is your turn!" << endl;
      cout << "Cards: " << p1.playedCards() << " | ";
      p1.printHand(true);

      if (p1.playedCards() == 1)
        Uno();

      // get and validate user input
      cout << "1. Draw" << endl;
      cout << "2. Play -> Color -> Value" << endl;
      int input;
      cin >> input;

      while (input < 1 || input > 2) {
        cout << "Invalid choice. Try again!" << endl;
        cin >> input;
      }

      // based on input, draw or play
      if (input == 1) {
        p1.drawCard();
        turn = nextTurn(turn);
      } else if (input == 2) {
        char c = 'a';
        int v = -1;
        cin >> c >> v;
        c = tolower(c);

        int indexOfPlayCard = -1;
        for (int i = 0; i < p1.playedCards(); i++)
          // find the index of the card that matches
          // not using overloaded operator ==
          // because I want && not ||
          // otherwise, it can take the wrong card
          if (p1[i].getColor() == c && p1[i].getValue() == v)
            indexOfPlayCard = i;

        // validate that this card can be played
        if (!(p1[indexOfPlayCard] == playCard)) {
          setColor(1);
          cout << "Invalid card play." << endl;
          p1.drawCard();
          indexOfPlayCard = -1;
          resetColor();
          p1.sortHand();
        }

        // if the card was found, play it
        if (indexOfPlayCard != -1) {
          // save card color and value before it is discarded
          char playedCardColor = p1[indexOfPlayCard].getColor();
          int playedCardValue = p1[indexOfPlayCard].getValue();

          p1.playCard(indexOfPlayCard);
          playCard.setCard(playedCardColor, playedCardValue);
        }

        // win condition
        if (p1.unPlayedCards()== 15) {
          cout << name << " has won!" << endl;
          play = false;
        }

        // go to next turn
        turn = nextTurn(turn);
      }
    } else if (turn == 2) { // computer 1's turn
      c1NumPlays++;

      // display hand
      bool cardPlayed = false;
      cout << "Computer 1's hand: " << endl;
      cout << "Cards: " << c1.playedCards() << " | ";
      c1.printHand(false);
      if (c1.playedCards() == 1)
        Uno();

      // sleep for 1-3 seconds to imply the computer is "thinking"
      this_thread::sleep_for(chrono::seconds(rand() % 3 + 1));

      // find what cards can be played
      for (int i = 0; i < c1.playedCards(); i++) {
        if (c1[i].getColor() == playCard.getColor() || c1[i].getValue() == playCard.getValue()) {
          cout << "Computer 1 is placing " << c1[i].getColor() << c1[i].getValue() << endl;
          playCard.setCard(c1[i].getColor(), c1[i].getValue());
          c1.playCard(i);
          cardPlayed = true;
          break;
        }
      }

      // draw card if nothing was played
      if (!cardPlayed)
        c1.drawCard();

      // win detection
      if (c1.unPlayedCards() == 15) {
        cout << "Computer 1 has won!" << endl;
        play = false;
      }

      // next turn
      turn = nextTurn(2);

    } else if (turn == 3) { // computer 2's hand
      c2NumPlays++;

      // display hand
      bool cardPlayed = false;
      cout << "Computer 2's hand:" << endl;
      cout << "Cards: " << c2.playedCards() << " | ";
      c2.printHand(false);
      if (c2.playedCards() == 1)
        Uno();

      this_thread::sleep_for(chrono::seconds(rand() % 3 + 1));

      // find card
      for (int i = 0; i < c2.playedCards(); i++) {
        if (c2[i].getColor() == playCard.getColor() ||
            c2[i].getValue() == playCard.getValue()) {
          cout << "Computer 2 is placing " << c2[i].getColor()
              << c2[i].getValue() << endl;
          playCard.setCard(c2[i].getColor(), c2[i].getValue());
          c2.playCard(i);
          cardPlayed = true;
          break;
        }
      }

      if (!cardPlayed)
        c2.drawCard();
      if (c2.unPlayedCards() == 15) {
        cout << "Computer 2 has won!" << endl;
        play = false;
      }
      turn = nextTurn(3);
    }
  }

  endOfGame(playerNumPlays, c1NumPlays, c2NumPlays);

  return 0;
}
void Welcome() {
  setColor(1);
  cout << "   __  ___   ______ " << endl;
  cout << "  / / / / | / / __ \\" << endl;
  setColor(2);
  cout << " / / / /  |/ / / / /" << endl;
  setColor(4);
  cout << "/ /_/ / /|  / /_/ /" << endl;
  setColor(3);
  cout << "\\____/_/ |_/\\____/" << endl;
  resetColor();
}
string getName() {
  cout << "\n\nPlease enter your name" << endl;
  string name = "John Doe";
  cin >> name;

  // clear the screen
  // need to save the result from system("clear")
  // as an int
  // otherwise, warning when compiling
  // 0 = success
  int isClear = system("clear");
  if (isClear != 0) cout << "Failure to clear screen" << endl;
  
  return name;
}
int nextTurn(int currentTurn) {
  if (currentTurn == 1)
    return 2;
  else if (currentTurn == 2)
    return 3;
  else
    return 1;
}
bool isWin(int numCards) { 
  return (numCards == 0); 
}
void setColor(int color) { 
  cout << "\033[" << (color + 30) << "m"; 
}
void resetColor() { 
  cout << "\033[0m"; 
}
void endOfGame(int p, int c1, int c2) {
  cout << "\nPlayer turns: " << p << endl;
  cout << "Computer 1 turns: " << c1 << endl;
  cout << "Computer 2 turns: " << c2 << endl;
  cout << "Total number of turns: " << (p + c1 + c2) << endl;
}
void printMiddleCard(char color, int value) {
  cout << "\n" << endl;

  // find the color of the card
  if (color == 'g')
    setColor(2);
  else if (color == 'r')
    setColor(1);
  else if (color == 'b')
    setColor(4);
  else if (color == 'y')
    setColor(3);

  // print card
  cout << "+----------+" << endl;
  cout << "|          |" << endl;
  cout << "|          |" << endl;
  cout << "|     " << value << "    |" << endl;
  cout << "|          |" << endl;
  cout << "|          |" << endl;
  cout << "+----------+" << endl;

  // reset color
  cout << "\n" << endl;
  resetColor();
}
void Uno() {
  cout << "\n\n" << endl;
  cout << "     UNO!" << endl;
  cout << "\n\n" << endl;
}