#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>

using namespace std;   

#include "defines.h"
#include "janggi.h"

#define ASCIIBASE 48

bool string2ints(string in, Pos& current, Pos& next);
void autoMode(Janggi& janggi);
void man2Computer(Janggi& janggi);
void manualMode(Janggi& janggi);

int main()
{
  srand(time(NULL));

  Janggi janggi;
  janggi.Print();

  autoMode(janggi);
  //man2Computer(janggi);
  //manualMode(janggi);

  return 1;
}

void autoMode(Janggi& janggi)
{
    Turn turn = TURN_CHO;
    do {
        cout << "Press enter";
        cin.get();
        
        clock_t start = clock();
        Action action = janggi.CalculateNextAction(turn);
        double duration = (clock() - start )/(double)CLOCKS_PER_SEC;
        cout << "max depth : " << MINMAX_DEPTH << endl;
        cout << "calc time : " << duration << endl;
        janggi.PerformAction(action); //throws on error. use 'try-catch' to handle exception.
        janggi.Print();

        printf("best : %d,%d -> %d,%d\n",
          action.prev.x,
          action.prev.y,
          action.next.x,
          action.next.y);

        turn = (turn == TURN_CHO ? TURN_HAN : TURN_CHO);
    } while(1);
}

void man2Computer(Janggi& janggi)
{
  string inputs;
  Pos current, next;
  Turn turn;

  do {    
    turn = TURN_CHO;
    cout << "Act : ";
    getline(cin, inputs);
    
    bool isCorrect = true;
    do {
      isCorrect = string2ints(inputs, current, next);
      if (isCorrect) {
        janggi.PerformAction(Action(current, next));
        janggi.Print();
      } else {
        cout << "Type the correct command" << endl;
      }

    } while (!isCorrect);

    turn = TURN_HAN;
    clock_t start = clock();
    Action action = janggi.CalculateNextAction(turn);
    double duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    cout << "max depth : " << MINMAX_DEPTH << endl;
    cout << "calc time : " << duration << endl;
    janggi.PerformAction(action); //throws on error. use 'try-catch' to handle exception.
    janggi.Print();    
  } while (1);
}

void manualMode(Janggi& janggi)
{
    Pos current, next;
    string inputs;
    do {
        cout << "Act : ";
        getline(cin, inputs);
        
        if (string2ints(inputs, current, next)) { // Pilhoon did not test this. Tests are needed.
            janggi.PerformAction(Action(current, next));
            janggi.Print();
        }
        else {
            cout << "Can't move" << endl;
        }
        
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