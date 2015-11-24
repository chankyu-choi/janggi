#include <iostream>
#include <string>
using namespace std;   

#include "defines.h"
#include "janggi.h"

#define ASCIIBASE 48

bool string2ints(string in, Pos& current, Pos& next);
void autoMode(Janggi& janggi);
void manaualMode(Janggi& janggi);

int main()
{
  Janggi janggi;
  janggi.Show(Pos(-1,-1)); 

  autoMode(janggi);
  //manualMode(janggi);

  return 1;
}

void autoMode(Janggi& janggi)
{
  Turn turn = TURN_CHO;
  do {
    cout << "Press enter";
    cin.get();

    Action action = janggi.CalculateNextAction(turn);
    if ( janggi.PerformAction(action) ) {      
      janggi.Show(action.curr);      
    } else {
      cout << "Can't move" << endl;
    }
    turn = (turn == TURN_CHO ? TURN_HAN : TURN_CHO);
  } while(1);
}

void manaualMode(Janggi& janggi)
{
  Pos current, next;
  string inputs;
  do {
    cout << "Act : ";
    getline(cin, inputs);
    
    if (string2ints(inputs, current, next) && janggi.PerformAction(Action(current, next)))
      janggi.Show(current);
    else
      cout << "Can't move" << endl;
  } while (1);
}

bool string2ints(string in, Pos& current, Pos& next)
{
  if (in.size() != 4)
    return false;

  current.x = in[0] - ASCIIBASE;
  current.y = in[1] - ASCIIBASE;
  next.x = in[2] - ASCIIBASE;
  next.y = in[3] - ASCIIBASE;

  return true;
}