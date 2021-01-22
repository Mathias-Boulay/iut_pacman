#include "DisplayUtils.h"
#include <iostream>
#include <iomanip>
#include "types.h"

#define YELLOW_TEXT "\033[33m"
#define PINK_TEXT "\033[35m"

using namespace std;

void ClearDisplay(){
    cout << "\033[H\033[2J";
}

void DisplayGameMap(const GameMap &Map,const Pacman &Pacman,const Ghosts &Ghosts){
    for(unsigned i(0); i < Map.size(); i+=1){ //For each row
        for(unsigned j(0); j < Map[i].size(); j+=1 ){ //Go through it and display it

           string displayedCase = RenderedChar.find(Map[i][j])->second;

            //Check if anything is overriding the gameMap
            if(Pacman.Pos.second == (int)i && Pacman.Pos.first == (int)j){
                displayedCase = Pacman.IsInSuperState ? PINK_TEXT : YELLOW_TEXT;
                displayedCase += Pacman.DirectionSprite;
            }

            for(const Ghost &ghost : Ghosts){
                if(ghost.Pos.second == (int)i && ghost.Pos.first == (int)j){
                    //TODO change the ghost sprite ?
                    displayedCase = DefaultGhost;
                    break; //Don't need to render other ghosts
                }
            }

            //TODO render bonuses/maluses

            cout << displayedCase;
        }
        cout << endl;
    }
}

void DisplayLevelHeader(const unsigned &Score,const unsigned &Lives,const unsigned &HighScore){
    cout << "CURRENT SCORE : " << to_string(Score) << "      " << "LIVES: ";
    for(unsigned i (0); i < Lives; i+=1){
        cout << "♥ ";
    }
    cout << endl;
    cout << "HIGHSCORE : " << to_string(HighScore) << endl;
}






