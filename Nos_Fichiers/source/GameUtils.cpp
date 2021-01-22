#include "types.h"
#include "GameUtils.h"
#include <fstream>
#include <experimental/random>

using namespace std;

wstring readFile(std::string filename)
{
    wifstream wif(filename);
    static locale empty;
    wif.imbue(locale(empty, new codecvt_utf8<wchar_t>));
    wstringstream wss;
    wss << wif.rdbuf();
    return wss.str();
}

bool isWall(const MapCase &Case, const bool CheckX){
    for(auto const& x : Walls){
        if(Case == x) return true;
    }
    //Wall specific to pacman
    if(CheckX){
        return (Case == L'x');
    }
    return false;
}

bool CollisionCheck(const Position &FirstEntity,const Position &SecondEntity){
    return ((FirstEntity.first == SecondEntity.first) && (FirstEntity.second == SecondEntity.second));
}

void Wrap(const GameMap &Map, Position &PosToWrap){


    //X > width
    if (PosToWrap.first > (int) (Map[PosToWrap.second].size()-1)){
        PosToWrap.first -= (int)Map[PosToWrap.second].size();
    }

    //X < width
    if(PosToWrap.first < 0){
        PosToWrap.first = (int)Map[PosToWrap.second].size()-2;
    }

    //Y axis
    if(Map[PosToWrap.second][PosToWrap.first] == L'≠'){
        unsigned i;
        if(isWall(Map[PosToWrap.second+1][PosToWrap.first], true)){
            //If the wall is under us, the tp point is over us.
            i = 0;
        }else{
            i = PosToWrap.second+1;
        }
        for(; Map[i][PosToWrap.first] != L'≠'; i+=1);
        PosToWrap.second = i;
    }

    return;
}

bool Move(const GameMap &Map, Position &EntityPosition,const Direction &Direction,const bool CheckX){
    bool hasMoved = false;

    Position futurePos (EntityPosition.first + Direction.first, EntityPosition.second + Direction.second);
    //Wrap around the map
    Wrap(Map,futurePos);
    if(!isWall(Map[futurePos.second][futurePos.first], CheckX)){
        EntityPosition = futurePos;
        hasMoved = true;
    }
    return hasMoved;
}


void Eat(MapCase &Case, Pacman &Pacman, unsigned &PacGumNumber, Ghosts &Ghosts){
   if(Case == PacGum){
       Case = L' ';
       PacGumNumber -= 1;
       Pacman.Score += 10;
   }

   if(Case == SuperPacGum){
       Case = L' ';
       Pacman.Score += 20;
       Pacman.IsInSuperState = true;
       Pacman.SuperStateDuration = 20;
   }

   if (Pacman.IsInSuperState){
       for(Ghost &ghost : Ghosts){
           if(CollisionCheck(Pacman.Pos, ghost.Pos)){
               //I should implement something about the ghosts being eaten
               ghost.Pos = ghost.SpawnPos;
               ghost.HasBeenEaten = true;
               Pacman.Score += 200*(Pacman.Killstreak+1);
           }
       }
   }

   //TODO: Add the ability to eat bonuses and maluses.




}

void ResetGameMapContent(GameMap &Map){
    Map.resize(0);
}

void ResetGhosts(Ghosts &Ghosts){
    Ghosts.resize(0);
}

void LoadGameMap(const string FilePath, GameMap &Map, Pacman &Pacman, Ghosts &Ghosts, unsigned &PacGumsNumber){
    PacGumsNumber = 0;
    ResetGhosts(Ghosts);
    ResetGameMapContent(Map);


    wstring mapString = readFile(FilePath);
    int i (0);
    int j (0);
    Map.resize(1);
    for (wstring::iterator it = mapString.begin(); it < mapString.end(); it++){
        wchar_t mapCase = *it;

        switch (mapCase) {
        case L'\n':
            Map.resize(Map.size()+1);
            i += 1;
            j = 0;
            continue;
            break;

        case PacGum:
            PacGumsNumber += 1;
            break;

        case L'▲':
            Pacman.SpawnPos.first = j;
            Pacman.SpawnPos.second = i;
            Pacman.Pos.first = j;
            Pacman.Pos.second = i;
            mapCase = L' ';
            break;

        case L'¤':
            Ghost ghost;
            ghost.HasEscaped = false;
            ghost.SpawnPos.first = j;
            ghost.SpawnPos.second = i;
            ghost.Pos.first = j;
            ghost.Pos.second = i;
            mapCase = L' ';
            Ghosts.push_back(ghost);
            break;
        }
        Map[i].push_back(mapCase);
        j+=1;

    }

    



}

bool isNear(const Position &FirstEntity, const Position &SecondEntity, unsigned Distance){
    return (((unsigned)abs(FirstEntity.first - SecondEntity.first) < Distance) && ((unsigned)abs(FirstEntity.second - SecondEntity.second) < Distance));
}

bool isHalfTurn (const Direction & LastDir,const Direction & DirectionInComing){
    if (DirectionInComing.first + LastDir.first == 0 && DirectionInComing.second + LastDir.second == 0)
        return true;
    return false;
}

bool isDeadEnd(const GameMap & Map, const Position & Position){
    unsigned count = 0;
    count += isWall(Map[Position.second-1][Position.first]);
    count += isWall(Map[Position.second+1][Position.first]);
    count += isWall(Map[Position.second][Position.first-2]);
    count += isWall(Map[Position.second][Position.first+2]);
    return (count >= 3);
}

Direction GoOpposite (const Pacman &Pacman, Position &PositionGhost, Direction & Previous,const GameMap &Map){
    Direction Opposite(0,0);//On crée la direction retournée
        if(Pacman.Pos.first - PositionGhost.first < 0 && isHalfTurn(Previous, Opposite)){//Est à gauche de Pacman et évite les demi-tours
            if (!isWall(Map[PositionGhost.second][PositionGhost.first + 2], true)){
                Opposite.first = 2;
                return Opposite;
            }
            else if (!isWall(Map[PositionGhost.second - 1][PositionGhost.first], true)){
                    Opposite.second = -1;
                    return Opposite;
            }
            else if (!isWall(Map[PositionGhost.second + 1][PositionGhost.first], true)){
                Opposite.second = 1;
                return Opposite;
            }
            else if (!isWall(Map[PositionGhost.second][PositionGhost.first -2], true)){
                Opposite.first = -2;
                return Opposite;
            }
        }
        else if (Pacman.Pos.first - PositionGhost.first > 0 && isHalfTurn(Previous, Opposite)){//Est à droite de PacMan et évite les demi-tours
            if (!isWall(Map[PositionGhost.second][PositionGhost.first -2], true)){
                Opposite.first = -2;
                return Opposite;
            }
            else if (!isWall(Map[PositionGhost.second -1][PositionGhost.first], true)){
                    Opposite.second = -1;
                    return Opposite;
            }
            else if (!isWall(Map[PositionGhost.second + 1][PositionGhost.first], true)){
                Opposite.second = 1;
                return Opposite;
            }
            if (!isWall(Map[PositionGhost.second][PositionGhost.first +2], true)){
                Opposite.first = 2;
                return Opposite;
            }
        }
else if (Pacman.Pos.second - PositionGhost.second < 0 && isHalfTurn(Previous, Opposite)){//Est en dessous de Pacman et évite les demi-tours
            if(!isWall(Map[PositionGhost.second +1][PositionGhost.first], true)){
                Opposite.second = 1;
                return Opposite;
            }
            if (!isWall(Map[PositionGhost.second][PositionGhost.first +2], true)){
                Opposite.first = 2;
                return Opposite;
            }
            if (!isWall(Map[PositionGhost.second][PositionGhost.first -2], true)){
                Opposite.first = -2;
                return Opposite;
            }
            else if (!isWall(Map[PositionGhost.second -1][PositionGhost.first], true)){
                Opposite.second = -1;
                return Opposite;
            }
        }
        else if (Pacman.Pos.second - PositionGhost.second > 0 && isHalfTurn(Previous, Opposite)){//Est au dessus de Pacman et évite les demi-tours
            if(!isWall(Map[PositionGhost.second -1][PositionGhost.first], true)){
                Opposite.second = -1;
                return Opposite;
            }
            if (!isWall(Map[PositionGhost.second][PositionGhost.first +2], true)){
                Opposite.first = 2;
                return Opposite;
            }
            if (!isWall(Map[PositionGhost.second][PositionGhost.first -2], true)){
                Opposite.first = -2;
                return Opposite;
            }
            else if (!isWall(Map[PositionGhost.second +1][PositionGhost.first], true)){
                Opposite.second = 1;
                return Opposite;
            }
        }
    return Opposite;
    }

void CLYDE(Position & PositionClyde,const Pacman &Pacman,const GameMap &Map){
    static Direction Previous;
    Direction DirectionClyde(0,0);
        if (isNear(Pacman.Pos, PositionClyde, 10)) {//Condition où Clyde est proche de Pacman à 10 cases près
            for (unsigned i(0); i<2; ++i){
            DirectionClyde = GoOpposite(Pacman, PositionClyde, Previous, Map);
            Move(Map,PositionClyde,DirectionClyde, true);
            Previous.first = DirectionClyde.first;
            Previous.second = DirectionClyde.second;
            }
        }//Clyde fuit lorsqu'il est proche de PacMan
        else {
            int c;
            while (true){//Boucle infinie où Clyde prend une direction aléatoire
                c = experimental::randint(0,3);
                switch(c){
                    case 0:
                        DirectionClyde.first=2;
                        break;
                    case 1:
                        DirectionClyde.first =-2;
                        break;
                    case 2:
                        DirectionClyde.second = 1;
                        break;
                    case 3:
                        DirectionClyde.second = -1;
                        break;
                }
                if (!isWall(Map[PositionClyde.second + DirectionClyde.second][PositionClyde.first + DirectionClyde.first], true) && (!isHalfTurn(Previous, DirectionClyde) || isDeadEnd(Map,PositionClyde))){
                    Move(Map,PositionClyde,DirectionClyde,true);
                    Previous.first = DirectionClyde.first;
                    Previous.second = DirectionClyde.second;
                    break;
                }//Si La direction de Clyde n'est pas un mur, il s'y dirige et casse la boucle
                DirectionClyde.first = 0;
                DirectionClyde.second = 0;
            }
        }
}


void MoveToPacMan (Ghost & Ghost, const Pacman & Pacman,const GameMap & Map)
{
    Position NewPosGhost (0,0); // Nouvelle position du fantôme
    int DiffX = sign ((Pacman.Pos.first - Ghost.Pos.first)); // Horizontal
    int DiffY = sign ((Pacman.Pos.second - Ghost.Pos.second)); // Vertical
    int WhereToGo = sign ((DiffX - DiffY));

    if(DiffX > 0 && DiffY < 0) // Pacman en haut à droite
        {
                Position VerifPos (Ghost.Pos);
        if (WhereToGo > 0) // Droite / Haut / Gauche / Bas
        {


        VerifPos.first +=2; // A droite
                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                 NewPosGhost.first += 2; // S'il n'y a pas de murs on peut déplacer le fantôme
                 Move(Map, Ghost.Pos, NewPosGhost, true);
                 return;
            }


        VerifPos.first -= 2;

        VerifPos.second -= 1; // En haut


                 if (! isWall (Map[VerifPos.second][VerifPos.first]))
             {

                  NewPosGhost.second -= 1; // S'il n'y a pas de murs on peut déplacer le fantôme

                  Move(Map, Ghost.Pos, NewPosGhost, true);
                  return;
             }

            VerifPos.second +=1;

        VerifPos.first -= 2; // A gauche

                if (! isWall (Map[VerifPos.second][VerifPos.first]))
                {
                NewPosGhost.first -= 2; // S'il n'y a pas de murs on peut déplacer le fantôme

                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
                }
            VerifPos.first += 2;

        NewPosGhost.second += 1;
        Move(Map, Ghost.Pos, NewPosGhost, true);
                return;


            }

        if (WhereToGo <= 0) // Haut / Droite / Bas / Gauche
        {


        VerifPos.second -= 1; // En haut


                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {

                NewPosGhost.second -= 1; // S'il n'y a pas de murs on peut déplacer le fantôme

                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }

            VerifPos.second +=1;

        VerifPos.first +=2; // A droite
                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first += 2; // S'il n'y a pas de murs on peut déplacer le fantôme
                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }


        VerifPos.first -= 2;

        VerifPos.second += 1; // En bas
            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
            NewPosGhost.second += 1; // S'il n'y a pas de murs on peut déplacer le fantôme

            Move(Map, Ghost.Pos, NewPosGhost, true);
            return;
            }
            VerifPos.second -= 1;

        NewPosGhost.first -= 1;
        Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
                }
    }








    if(DiffX > 0 && DiffY > 0) // Pacman en bas à droite
        {
                Position VerifPos (Ghost.Pos);
        if (WhereToGo > 0) // Droite / Bas / Gauche / Haut
        {


        VerifPos.first +=2; // A droite
                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first += 2; // S'il n'y a pas de murs on peut déplacer le fantôme
                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }


        VerifPos.first -= 2;

        VerifPos.second += 1; // En bas
            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
            NewPosGhost.second += 1; // S'il n'y a pas de murs on peut déplacer le fantôme

            Move(Map, Ghost.Pos, NewPosGhost, true);
            return;
            }
            VerifPos.second -= 1;

        VerifPos.first -= 2; // A gauche

            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first -= 2; // S'il n'y a pas de murs on peut déplacer le fantôme

                    Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }
    VerifPos.first += 2;

        NewPosGhost.second += 1;
        Move(Map, Ghost.Pos, NewPosGhost, true);
        return;
            }

        if (WhereToGo <= 0) // Bas / Droite / Haut / Gauche
        {


        VerifPos.second += 1; // En bas
            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
            NewPosGhost.second += 1; // S'il n'y a pas de murs on peut déplacer le fantôme

            Move(Map, Ghost.Pos, NewPosGhost, true);
            return;
            }
            VerifPos.second -= 1;

        VerifPos.first +=2; // A droite
                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first += 2; // S'il n'y a pas de murs on peut déplacer le fantôme
                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }


        VerifPos.first -= 2;

        VerifPos.second -= 1; // En haut


                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {

                NewPosGhost.second -= 1; // S'il n'y a pas de murs on peut déplacer le fantôme

                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }

            VerifPos.second +=1;

        NewPosGhost.first -= 2;
        Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
                }
    }






    if(DiffX < 0 && DiffY < 0) // Pacman en haut à gauche
        {
                Position VerifPos (Ghost.Pos);
        if (WhereToGo > 0) // Gauche / Haut / Bas / Droite
        {


        VerifPos.first -= 2; // A gauche

            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first -= 2; // S'il n'y a pas de murs on peut déplacer le fantôme

                    Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }
        VerifPos.first += 2;

        VerifPos.second -= 1; // En haut


                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {

                NewPosGhost.second -= 1; // S'il n'y a pas de murs on peut déplacer le fantôme

                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }

            VerifPos.second +=1;

        VerifPos.second += 1; // En bas
            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
            NewPosGhost.second += 1; // S'il n'y a pas de murs on peut déplacer le fantôme

            Move(Map, Ghost.Pos, NewPosGhost, true);
            return;
            }
            VerifPos.second -= 1;

        NewPosGhost.first += 2;
        Move(Map, Ghost.Pos, NewPosGhost, true);
            return;
            }

        if (WhereToGo <= 0) // Haut / Gauche / Droite / Bas
        {


        VerifPos.second -= 1; // En haut


                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {

                NewPosGhost.second -= 1; // S'il n'y a pas de murs on peut déplacer le fantôme

                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }

            VerifPos.second +=1;

        VerifPos.first -= 2; // A gauche

            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first -= 2; // S'il n'y a pas de murs on peut déplacer le fantôme

                    Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }
    VerifPos.first += 2;

        VerifPos.first +=2; // A droite
                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first += 2; // S'il n'y a pas de murs on peut déplacer le fantôme
                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }


        VerifPos.first -= 2;

        NewPosGhost.second += 1;
        Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
                }
    }






    if(DiffX < 0 && DiffY > 0) // Pacman en bas à gauche
        {
                Position VerifPos (Ghost.Pos);
        if (WhereToGo <= 0) // Gauche / Bas / Haut / Droite
        {


        VerifPos.first -= 2; // A gauche

            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first -= 2; // S'il n'y a pas de murs on peut déplacer le fantôme

                    Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }
    VerifPos.first += 2;

        VerifPos.second += 1; // En bas
            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
            NewPosGhost.second += 1; // S'il n'y a pas de murs on peut déplacer le fantôme

            Move(Map, Ghost.Pos, NewPosGhost, true);
            return;
            }
            VerifPos.second -= 1;

        VerifPos.second -= 1; // En haut


                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {

                NewPosGhost.second -= 1; // S'il n'y a pas de murs on peut déplacer le fantôme

                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }

            VerifPos.second += 1;

        NewPosGhost.first += 2;
        Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }

        if (WhereToGo > 0) // Bas / Gauche / Droite / Haut
        {


        VerifPos.second += 1; // En bas
            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
            NewPosGhost.second -= 1; // S'il n'y a pas de murs on peut déplacer le fantôme

            Move(Map, Ghost.Pos, NewPosGhost, true);
            return;
            }
            VerifPos.second -= 1;

        VerifPos.first -= 2; // A gauche

            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first -= 2; // S'il n'y a pas de murs on peut déplacer le fantôme

                    Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }
    VerifPos.first += 2;

        VerifPos.first +=2; // A droite
                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first += 2; // S'il n'y a pas de murs on peut déplacer le fantôme
                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }


        VerifPos.first -= 2;

        NewPosGhost.second += 1;
        Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
                }
    }

    if(DiffX > 0 && DiffY == 0) // Pacman à droite
        {
                Position VerifPos (Ghost.Pos);
        // Droite / Haut / Bas / Gauche

        VerifPos.first +=2; // A droite
                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first += 2; // S'il n'y a pas de murs on peut déplacer le fantôme
                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }


        VerifPos.first -= 2;

        VerifPos.second -= 1; // En haut


                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {

                NewPosGhost.second -= 1; // S'il n'y a pas de murs on peut déplacer le fantôme

                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }

            VerifPos.second +=1;

        VerifPos.second += 1; // En bas
            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
            NewPosGhost.second += 1; // S'il n'y a pas de murs on peut déplacer le fantôme

            Move(Map, Ghost.Pos, NewPosGhost, true);
            return;
            }
            VerifPos.second -= 1;

        NewPosGhost.first -= 2;
        Move(Map, Ghost.Pos, NewPosGhost, true);
            return;

    }

    if(DiffX == 0 && DiffY < 0) // Pacman au dessus
        {
                Position VerifPos (Ghost.Pos);
        // Haut / Droite / Gauche / Bas

        VerifPos.second -= 1; // En haut


                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {

                NewPosGhost.second -= 1; // S'il n'y a pas de murs on peut déplacer le fantôme

                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }

            VerifPos.second +=1;

        VerifPos.first +=2; // A droite
                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first += 2; // S'il n'y a pas de murs on peut déplacer le fantôme
                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }


        VerifPos.first -= 2;

        VerifPos.first -= 2; // A gauche

            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first -= 2; // S'il n'y a pas de murs on peut déplacer le fantôme

                    Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }
    VerifPos.first += 2;

        NewPosGhost.second += 1;
        Move(Map, Ghost.Pos, NewPosGhost, true);
                return;

    }

    if(DiffX < 0 && DiffY == 0) // Pacman à gauche
        {
                Position VerifPos (Ghost.Pos);
        // Gauche / Haut / Bas / Droite

        VerifPos.first -= 2; // A gauche

            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first -= 2; // S'il n'y a pas de murs on peut déplacer le fantôme

                    Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }
    VerifPos.first += 2;

        VerifPos.second -= 1; // En haut


                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {

                NewPosGhost.second -= 1; // S'il n'y a pas de murs on peut déplacer le fantôme

                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }

            VerifPos.second +=1;

        VerifPos.second += 1; // En bas
            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
            NewPosGhost.second += 1; // S'il n'y a pas de murs on peut déplacer le fantôme

            Move(Map, Ghost.Pos, NewPosGhost, true);
            return;
            }
            VerifPos.second -= 1;

        NewPosGhost.first += 2;
        Move(Map, Ghost.Pos, NewPosGhost, true);
                return;

    }

    if(DiffX == 0 && DiffY > 0) // Pacman en dessous
        {
                Position VerifPos (Ghost.Pos);
        // Bas / Droite / Gauche / Haut

        VerifPos.second += 1; // En bas
            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
            NewPosGhost.second += 1; // S'il n'y a pas de murs on peut déplacer le fantôme

            Move(Map, Ghost.Pos, NewPosGhost, true);
            return;
            }
            VerifPos.second -= 1;

        VerifPos.first +=2; // A droite
                if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first += 2; // S'il n'y a pas de murs on peut déplacer le fantôme
                Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }


        VerifPos.first -= 2;

        VerifPos.first -= 2; // A gauche

            if (! isWall (Map[VerifPos.second][VerifPos.first]))
            {
                NewPosGhost.first -= 2; // S'il n'y a pas de murs on peut déplacer le fantôme

                    Move(Map, Ghost.Pos, NewPosGhost, true);
                return;
            }
    VerifPos.first += 2;

        NewPosGhost.second -= 1;
        Move(Map, Ghost.Pos, NewPosGhost, true);
                return;

    }

}

void IARandom(const GameMap &Map, Ghost &ghost){
    static Direction lastDirection = make_pair(2,0);
    int c;

    if(lastDirection.first != 0){
        if(!isWall(Map[ghost.Pos.second-1][ghost.Pos.first], true)){
            c = experimental::randint(0,3);
            if(c == 0){// 25 % de chance
                lastDirection = make_pair(0,-1);
                Move(Map,ghost.Pos,lastDirection,true);
                return;
            }
        }

        if(!isWall(Map[ghost.Pos.second+1][ghost.Pos.first], true)){
            c = experimental::randint(0,2);
            if(c == 0){// 33 % de chance
                lastDirection = make_pair(0,1);
                Move(Map,ghost.Pos,lastDirection,true);
                return;
            }
        }

        if(!isWall(Map[ghost.Pos.second + lastDirection.second][ghost.Pos.first + lastDirection.first], true)){
            Move(Map, ghost.Pos, lastDirection, true);
            return;
        }
        bool hasMoved = false;
        Direction dir;
        while(!hasMoved){

            c = experimental::randint(0,4);

            switch (c) {
            case 0:
            case 3:
                dir = make_pair(0,1);
                hasMoved = Move(Map, ghost.Pos, dir, true);
                break;

            case 1:
            case 4:
                dir = make_pair(0,-1);
                hasMoved = Move(Map, ghost.Pos, dir, true);
                break;

            case 2:
                dir = make_pair(lastDirection.first * -1, 0);
                hasMoved = Move(Map, ghost.Pos, dir, true);
                break;
            }
        }
        lastDirection = dir;
        return;



    }else{ //we can assume lastDirection is != 0 on the y axis
        if(!isWall(Map[ghost.Pos.second][ghost.Pos.first-2], true)){
            c = experimental::randint(0,3);
            if(c == 0){// 25 % de chance
                lastDirection = make_pair(-2,0);
                Move(Map,ghost.Pos,lastDirection,true);
                return;
            }
        }

        if(!isWall(Map[ghost.Pos.second][ghost.Pos.first+2], true)){
            c = experimental::randint(0,2);
            if(c == 0){// 33 % de chance
                lastDirection = make_pair(2,0);
                Move(Map,ghost.Pos,lastDirection,true);
                return;
            }
        }

        if(!isWall(Map[ghost.Pos.second + lastDirection.second][ghost.Pos.first + lastDirection.first], true)){
            Move(Map,ghost.Pos,lastDirection,true);
            return;
        }

        bool hasMoved = false;
        Direction dir;
        while(!hasMoved){

            c = experimental::randint(0,4);

            switch (c) {
            case 0:
            case 3:
                dir = make_pair(2,0);
                hasMoved = Move(Map, ghost.Pos, dir, true);
                break;

            case 1:
            case 4:
                dir = make_pair(-2,0);
                hasMoved = Move(Map, ghost.Pos, dir, true);
                break;

            case 2:
                dir = make_pair(0, lastDirection.second * -1);
                hasMoved = Move(Map, ghost.Pos, dir, true);
                break;
            }
        }
        lastDirection = dir;
        return;
    }
}

void Escape(const GameMap &Map, Ghost &ghost){
    Direction direction (0, -1);
    Move(Map, ghost.Pos, direction, false);
    if(Map[ghost.Pos.second+1][ghost.Pos.first] == L'x'){
        ghost.HasEscaped = true;
    }
}

//TODO make use of generic types ?
int sign(const int x){
    return (x > 0) - (x < 0);
}
