#include "types.h"
#include "Game.h"
#include "DisplayUtils.h"
#include "InputUtils.h"
#include "GameUtils.h"
#include "SettingUtils.h"
#include "MenuUtils.h"
#include <experimental/random>

using namespace std;

void ClassicGame(){
    Settings st = LoadSettings();
    unsigned highscore = st.ClassicModeHighScore["1"];
    const char keyUp(st.MovementChar.find("KeyUp")->second);
    const char keyDown(st.MovementChar.find("KeyDown")->second);
    const char keyRight(st.MovementChar.find("KeyRight")->second);
    const char keyLeft(st.MovementChar.find("KeyLeft")->second);

    char input;
    bool hasMoved = false;
    Direction direction;

    //The all time classic !
    GameMap map;
    Pacman pacman;
    Ghosts ghosts;
    unsigned pacGumsNumber = 0;
    unsigned levelNumber = 1;

    while(levelNumber < 15){

        LoadGameMap("../iut_pacman/Nos_Fichiers/maps/" + to_string(levelNumber) + ".txt", map, pacman, ghosts, pacGumsNumber);
        while(true){
            hasMoved = false;
            ClearDisplay();
            DisplayLevelHeader(pacman.Score, pacman.Lives, highscore);
            DisplayGameMap(map,pacman,ghosts);

            while(!hasMoved){
                input = ReadSpecificKeyboardInput({keyUp,keyDown,keyLeft,keyRight});

                if(input == keyUp){
                    direction = make_pair(0,-1);
                    pacman.DirectionSprite = PacmanUp;
                } else if(input == keyDown){
                    direction = make_pair(0,1);
                    pacman.DirectionSprite = PacmanDown;
                }else if(input == keyLeft){
                    direction = make_pair(-2,0);
                    pacman.DirectionSprite = PacmanLeft;
                }else{ //keyRight
                    direction = make_pair(2,0);
                    pacman.DirectionSprite = PacmanRight;
                }

                hasMoved = Move(map,pacman.Pos, direction, true);
            }
            //Deal with status duration
            if(pacman.IsInSuperState){
                pacman.SuperStateDuration -= 1;
                if(pacman.SuperStateDuration == 0){
                    pacman.IsInSuperState = false;
                    pacman.Killstreak = 0;
                }
            }

            Eat(map[pacman.Pos.second][pacman.Pos.first], pacman, pacGumsNumber, ghosts);
            if(pacGumsNumber == 0){
                break;
            }

            //Check ghosts condition before ghosts are moving
            for(Ghost &ghost : ghosts){
                if(ghost.HasBeenEaten){
                    ghost.Pos = ghost.SpawnPos;
                    ghost.HasBeenEaten = false;
                    ghost.HasEscaped = false;
                    continue;
                }
                if(CollisionCheck(pacman.Pos, ghost.Pos)){
                    //Pacman is incompetent
                    // TODO a better system ?
                    pacman.Lives -= 1;
                    if(pacman.Lives == 0){
                        YouLostMenu(pacman.Score);
                        break;
                    }

                    pacman.Pos = pacman.SpawnPos;

                    for(Ghost &_ghost : ghosts){
                        _ghost.Pos = _ghost.SpawnPos;
                        _ghost.HasEscaped = false;
                    }
                    break;
                }
            }

            //Make ghost move
            if(!ghosts[0].HasEscaped){
                Escape(map, ghosts[0]);
            }else{
                CLYDE(ghosts[0].Pos, pacman, map);
            }

            if(!ghosts[1].HasEscaped){
                Escape(map, ghosts[1]);
            }else{
                IARandom(map, ghosts[1]);
            }

            if(!ghosts[2].HasEscaped){
                Escape(map, ghosts[2]);
            }else{
                MoveToPacMan(ghosts[2], pacman, map);
            }

            //Pacman can still eat after they moved.
            Eat(map[pacman.Pos.second][pacman.Pos.first], pacman, pacGumsNumber, ghosts);
            if(pacGumsNumber == 0){
                break;
            }
            //Update highscore if we are beating it !
            highscore = max(pacman.Score, highscore);

            //Check ghosts condition after they moved
            for(Ghost &ghost : ghosts){
                if(ghost.HasBeenEaten){
                    ghost.Pos = ghost.SpawnPos;
                    ghost.HasBeenEaten = false;
                    ghost.HasEscaped = false;
                    continue;
                }
                if(CollisionCheck(pacman.Pos, ghost.Pos)){
                    //Pacman is incompetent
                    // TODO a better system ?
                    pacman.Lives -= 1;
                    if(pacman.Lives == 0){
                        YouLostMenu(pacman.Score);
                        break;
                    }

                    pacman.Pos = pacman.SpawnPos;

                    for(Ghost &_ghost : ghosts){
                        _ghost.Pos = _ghost.SpawnPos;
                        _ghost.HasEscaped = false;
                    }
                    break;
                }
            }
        }
        levelNumber +=1;
        if(levelNumber > 14){
            YouWonMenu(pacman.Score);
        }
    }
}

void InfiniteGame(){
    Settings st = LoadSettings();
    unsigned highscore = st.ClassicModeHighScore["1"];
    const char keyUp(st.MovementChar.find("KeyUp")->second);
    const char keyDown(st.MovementChar.find("KeyDown")->second);
    const char keyRight(st.MovementChar.find("KeyRight")->second);
    const char keyLeft(st.MovementChar.find("KeyLeft")->second);

    char input;
    bool hasMoved = false;
    Direction direction;

    //The all time classic !
    GameMap map;
    Pacman pacman;
    Ghosts ghosts;
    unsigned pacGumsNumber = 0;
    unsigned levelNumber;

    while(true){
        levelNumber = experimental::randint(1,14);
        LoadGameMap("../maps/map_" + to_string(levelNumber) + ".txt", map, pacman, ghosts, pacGumsNumber);
        while(true){
            hasMoved = false;
            ClearDisplay();
            DisplayLevelHeader(pacman.Score, pacman.Lives, highscore);
            DisplayGameMap(map,pacman,ghosts);

            while(!hasMoved){
                input = ReadSpecificKeyboardInput({keyUp,keyDown,keyLeft,keyRight});

                if(input == keyUp){
                    direction = make_pair(0,-1);
                    pacman.DirectionSprite = PacmanUp;
                } else if(input == keyDown){
                    direction = make_pair(0,1);
                    pacman.DirectionSprite = PacmanDown;
                }else if(input == keyLeft){
                    direction = make_pair(-2,0);
                    pacman.DirectionSprite = PacmanLeft;
                }else{ //keyRight
                    direction = make_pair(2,0);
                    pacman.DirectionSprite = PacmanRight;
                }

                hasMoved = Move(map,pacman.Pos, direction, true);
            }
            //Deal with status duration
            if(pacman.IsInSuperState){
                pacman.SuperStateDuration -= 1;
                if(pacman.SuperStateDuration == 0){
                    pacman.IsInSuperState = false;
                    pacman.Killstreak = 0;
                }
            }

            //Make ghost move
            if(!ghosts[0].HasEscaped){
                Escape(map, ghosts[0]);
            }else{
                //MoveToPacMan(ghosts[0], pacman, map);
                CLYDE(ghosts[0].Pos, pacman, map);
            }

            if(!ghosts[1].HasEscaped){
                Escape(map, ghosts[1]);
            }else{
                IARandom(map, ghosts[1]);
            }

            if(!ghosts[2].HasEscaped){
                Escape(map, ghosts[2]);
            }else{
                MoveToPacMan(ghosts[2], pacman, map);
            }


            Eat(map[pacman.Pos.second][pacman.Pos.first], pacman, pacGumsNumber, ghosts);
            if(pacGumsNumber == 0){
                break;
            }
            //Update highscore if we are beating it !
            highscore = max(pacman.Score, highscore);

            //Check ghosts condition
            for(Ghost &ghost : ghosts){
                if(ghost.HasBeenEaten){
                    ghost.Pos = ghost.SpawnPos;
                    ghost.HasBeenEaten = false;
                    ghost.HasEscaped = false;
                    continue;
                }
                if(CollisionCheck(pacman.Pos, ghost.Pos)){
                    //Pacman is incompetent
                    // TODO a better system ?
                    pacman.Lives -= 1;
                    if(pacman.Lives == 0){
                        YouLostMenu(pacman.Score);
                        break;
                    }

                    pacman.Pos = pacman.SpawnPos;

                    for(Ghost &_ghost : ghosts){
                        _ghost.Pos = _ghost.SpawnPos;
                        _ghost.HasEscaped = false;
                    }
                    break;
                }
            }
        }
    }
}

