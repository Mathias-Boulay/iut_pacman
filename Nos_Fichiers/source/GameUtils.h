#ifndef GAMEUTILS_H
#define GAMEUTILS_H

/**
 * \file GameUtils.h
 * \brief A set of function which defines basic game systems.
 * \author BOULAY Mathias,
 * \author MONBEIG Maxime
 * \author PINEL Anthony
 * \author JUBERT Killian
 * \author DAURELLE Nicolas
 * \version 1.0
 * \date 17 janvier 2021
 */

#include "types.h"
#include <sstream>
#include <fstream>
#include <codecvt>
#include <iostream>
#include <cwchar>


/**
 * @brief Récupère le contenu d'un fichier et le stock dans un wstring (pour la gestion des caractères unicodes)
 * @param[in] filename Chemin vers le fichier à lire
 * @fn std::wstring readFile(std::string filename);
 * @return std::wstring
 */
std::wstring readFile(std::string filename);

/**
 * @brief vérifie la présence d'un mur à la case spécifié
 * @param[in] Case la case à vérifier
 * @param[in] CheckX booléen pour vérifier (ou non) les barbelés
 * @fn bool isWall(const MapCase &Case, const bool CheckX = true);
 * @return bool
 */
bool isWall(const MapCase &Case, const bool CheckX = true);

/**
 * @brief vérifie si les deux positions sont identiques
 * @param[in] FirstEntity La première position
 * @param[in] SecondEntity La seconde position
 * @fn bool CollisionCheck(const Position &FirstEntity,const Position &SecondEntity);
 * @return bool
 */
bool CollisionCheck(const Position &FirstEntity,const Position &SecondEntity);

/**
 * @brief Déplace l'entité dans la direction donnée, si il n'y a pas de mur. La valeur renvoyé exprime la réussite du mouvement.
 * @param[in] Map La map sur laquelle se déplacer
 * @param[in, out] InitialPosition Position initiale de l'entité
 * @param[in] Direction Direction vers laquelle l'entité se déplace
 * @fn bool Move(const GameMap &Map, Position &InitialPosition,const Direction &Direction, const bool checkX);
 * @return bool
 */
bool Move(const GameMap &Map, Position &InitialPosition,const Direction &Direction, const bool checkX);

/**
 * @brief Gère le positionnement quand une entité prend un tunnel.
 * @param[in] Map La map sur laquelle se déplacer
 * @param[in, out] PosToWrap Position initiale (puis finale) de l'entité
 * @fn void Wrap(const GameMap &Map, Position &PosToWrap);
 * @return void
 */
void Wrap(const GameMap &Map, Position &PosToWrap);

/**
 * @brief Fait manger pacman, il mange les fantômes et les (super-)pacgommes
 * @param[in, out] Case La case sur laquelle manger
 * @param[in, out] Pacman Le pacman qui mange
 * @param[in, out] PacGumNumber nombre de pacgommes restantes
 * @param[in, out] Ghosts Les fantômes qui peuvent être mangés
 * @fn void Eat(MapCase &Case, Pacman &Pacman, unsigned &PacGumNumber, Ghosts &Ghosts);
 * @return void
 */
void Eat(MapCase &Case, Pacman &Pacman, unsigned &PacGumNumber, Ghosts &Ghosts);

/**
 * @brief Vide la GameMap
 * @param[in, out] GameMap GameMap à vider
 * @fn void ResetGameMapContent(GameMap &Map);
 * @return void
 */
void ResetGameMapContent(GameMap &Map);

/**
 * @brief Charge une GameMap depuis un fichier. Donne aussi les emplacements des fantômes, le nombre de pacgommes et l'emplacement de pacman.
 * @param[in] FilePath Chemin vers le fichier à charger;
 * @param[in, out] GameMap Map à charger
 * @param[in, out] Pacman Le pacman qui obtient ses coordonnées d'apparition
 * @param[in, out] Ghosts Les fantômes qui obtiennent leurs coordonnées d'apparition
 * @param[in, out] PacGumNumber Nombre de pacgommes sur le terrain
 * @fn void LoadGameMap(const std::string FilePath, GameMap &Map, Pacman &Pacman, Ghosts &Ghosts, unsigned &PacGumsNumber);
 * @return void
 */
void LoadGameMap(const std::string FilePath, GameMap &Map, Pacman &Pacman, Ghosts &Ghosts, unsigned &PacGumsNumber);

/**
 * @brief Renvoie si les entitées sont à moins de la distance spécifié l'un de l'autre.
 * @param[in] FirstEntity La position de la première entité
 * @param[in] SecondEntity La position de la seconde entité
 * @param[in] Distance La distance à vérifier
 * @fn bool isNear(const Position &FirstEntity,const Position &SecondEntity,const unsigned Distance);
 * @return bool
 */
bool isNear(const Position &FirstEntity,const Position &SecondEntity,const unsigned Distance);

/**
 * @brief Renvoie vrai si l'entité est dans un cul de sac
 * @param[in] Map La carte étudiée
 * @param[in] SecondEntity La position de l'entité pottentiellement bloqué
 * @fn bool isDeadEnd(const GameMap & Map, const Position & Position);
 * @return bool
 */
bool isDeadEnd(const GameMap & Map, const Position & Position);

/**
 * @brief Fonction booléenne qui renvoie vrai si une direction DirectionInComing va en sens inverse par rapport à une direction LastDir
 * @param[in] LastDir : Dernière direction du fantôme
 * @param[in] DirectionInComing : Direction que le fantôme va prendre
 * @fn bool isHalfTurn (const Direction & LastDir,const Direction & DirectionInComing);
 * @return bool
 */
bool isHalfTurn (const Direction & LastDir,const Direction & DirectionInComing);

/**
 * @brief Renvoie la direction opposée à pacman
 * @param[in] Pacman : Pacman, pour connaître sa position
 * @param[in, out] PositionGhost : La position du fantôme à changer
 * @param[in, out] Previous : Le mouvement précédent du fantôme, pour le comparer au mouvement à venir et éviter les demi-tours
 * @param[in] Map : la carte actuelle, pour tester si il ne va pas dans une direction avec un mur
 * @fn Direction GoOpposite (const Pacman &Pacman, Position &PositionGhost, Direction & Previous,const GameMap &Map);
 * @return Direction
 */
Direction GoOpposite (const Pacman &Pacman, Position &PositionGhost, Direction & Previous,const GameMap &Map);

/**
 * @brief Intelligence Artificielle du fantôme Clyde : Il fuit dès que Pacman s'approche et prend des direction aléatoires le reste du temps
 * @param[in, out] PositionClyde : Position du Fantôme à bouger
 * @param[in] Pacman : Pacman, pour avoir la distance relative du fantôme
 * @param[in] Map : La carte actuelle, pour pouvoir tester si il ne rentre pas dans un mur
 * @fn void CLYDE(Position & PositionClyde,const Pacman &Pacman,const GameMap & Map);
 * @return void
 */
void CLYDE(Position & PositionClyde,const Pacman &Pacman,const GameMap & Map);

/**
  * @brief Fonction permettant à un fantôme de suivre Pacman en fonction de sa position par rapport à celle de Pacman
  * @param [in, out] Ghost & Ghost : Permet de récuperer la struct du fantôme pour obtenir sa position et le déplacer
  * @param [in] const Pacman & Pacman : Permet de récuperer la struct de Pacman pour obtenir sa position et la comparer à celle du fantôme
  * @param [in] GameMap & Map : Permet de récuper la map sur laquelle le fantôme évolue pour pouvoir le déplacer dessus en conséquence
  * @fn void MoveToPacMan (Ghost & Ghost, const Pacman & Pacman,const GameMap & Map);
  * @return void
*/
void MoveToPacMan (Ghost & Ghost, const Pacman & Pacman,const GameMap & Map);

/**
 * @brief Intelligence artificielle d'un fantôme qui change aléatoirement de direction lorsque l'occasion est présente.
 * @param[in] Map La map sur laquelle se déplacer
 * @param[in] ghost L'entité qui se déplace.
 * @fn void IARandom(const GameMap &Map, Ghost &ghost);
 * @return void
 */
void IARandom(const GameMap &Map, Ghost &ghost);

/**
 * @brief IA par défaut pour les fantômes qui se trouvent dans leur cage d'apparition. Aide les fantômes à sortir de là.
 * @param[in] Map La map sur laquelle se déplacer
 * @param[in] ghost L'entité qui se déplace.
 * @fn void Escape(const GameMap &Map, Ghost &ghost);
 * @return void
 */
void Escape(const GameMap &Map, Ghost &ghost);

/**
 * @brief Retourne un entier prenant les valeurs -1;0;1 en fonction du signe de l'argument
 * @param[in] x Valeur dont le signe est testé
 * @fn int sign(const int x);
 * @return int
 */
int sign(const int x);

#endif // GAMEUTILS_H
