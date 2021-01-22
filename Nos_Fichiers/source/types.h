#ifndef TYPES_H
#define TYPES_H

/*!
 * \file types.h
 * \brief Un ensemble de types facilitant la création du jeu
 * \author BOULAY Mathias,
 * \author MONBEIG Maxime
 * \author PINEL Anthony
 * \author JUBERT Killian
 * \author DAURELLE Nicolas
 * \version 1.0
 * \date 15 janvier 2021
 */

#include <iostream>
#include <vector>
#include <map>

#define BOLD_TEXT "\033[1m"
#define BLUE_TEXT "\033[34m"
#define RESET_TEXT "\033[0m"
#define WHITE_TEXT "\033[97m"
#define RED_TEXT "\033[31m"
#define GREEN_TEXT "\033[32m"

/**
 * @brief MapCase : alias à une case d'une GameMap
 * @typedef wchar_t MapCase;
 */
typedef wchar_t MapCase;

/**
 * @brief MapLine : alias à la ligne d'une GameMap
 * @typedef std::vector<MapCase> MapLine;
 */
typedef std::vector<MapCase> MapLine;

/**
 * @brief GameMap : alias pour une matrice de MapCase
 * @typedef std::vector<MapLine> GameMap;
 */
typedef std::vector<MapLine> GameMap; //Map[y][x]

/**
 * @brief Position : alias à une position dans une GameMap (X,Y)
 * @typedef std::pair<int, int> Position;
 */
typedef std::pair<int, int> Position; //(X, Y)

/**
 * @brief Direction : alias pour une direction au sein d'une GameMap. Utilisé en combinaison avec Position
 * @typedef std::pair<int, int> Position;
 */
typedef std::pair<int, int> Direction; //(dX, dY)

/**
 * @brief Un tableau des différents murs. Utilisé par la fonction isWall();
 */
const std::vector<wchar_t> Walls = {L'╔',L'╗',L'╚',L'╝',L'═',L'║',L'╣',L'╩',L'╦',L'╠',L'╬'};

/**
 * @brief Sprite direction droite
 */
const std::string PacmanRight = BOLD_TEXT "⊂" RESET_TEXT;

/**
 * @brief Sprite direction gauche
 */
const std::string PacmanLeft = BOLD_TEXT "⊃" RESET_TEXT;

/**
 * @brief Sprite direction haut
 */
const std::string PacmanUp = BOLD_TEXT "∪" RESET_TEXT;

/**
 * @brief Sprite direction bas
 */
const std::string PacmanDown = BOLD_TEXT "∩" RESET_TEXT;

/**
 * @brief Struct contenant des éléments pour pacman
 * @struct Pacman
 */
struct Pacman{
    Position Pos;
    Position SpawnPos;
    unsigned Lives = 3;
    unsigned Score = 0;

    unsigned Killstreak = 0;

    std::string DirectionSprite = PacmanRight;

    bool IsInSuperState = false;
    unsigned SuperStateDuration = 0;
};

/**
 * @brief Sprite du fantôme par défaut
 */
const std::string DefaultGhost = GREEN_TEXT "⋂" RESET_TEXT;

/**
 * @brief Struct contenant des éléments pour les fantômes
 * @struct Ghost
 */
struct Ghost{
    Position Pos;
    Position SpawnPos;
    std::string Color;
    bool HasBeenEaten = false;
    bool HasEscaped = false;
};

/**
 * @brief alias pour plusieurs fantômes
 * @typedef std::vector<Ghost> Ghosts;
 */
typedef std::vector<Ghost> Ghosts;

/**
 * @brief PacGomme
 */
const wchar_t PacGum = L'•';

/**
 * @brief Super PacGomme
 */
const wchar_t SuperPacGum = L'o';


/**
 * @brief Table de correspondance entre les caractères de la map, et les caractères à afficher
 */
const std::map <wchar_t, std::string> RenderedChar
{
    {L'╔',BLUE_TEXT "╔" RESET_TEXT},
    {L'╗',BLUE_TEXT "╗" RESET_TEXT},
    {L'╚',BLUE_TEXT "╚" RESET_TEXT},
    {L'╝',BLUE_TEXT "╝" RESET_TEXT},
    {L'═',BLUE_TEXT "═" RESET_TEXT},
    {L'║',BLUE_TEXT "║" RESET_TEXT},
    {L'╣',BLUE_TEXT "╣" RESET_TEXT},
    {L'╩',BLUE_TEXT "╩" RESET_TEXT},
    {L'╦',BLUE_TEXT "╦" RESET_TEXT},
    {L'╠',BLUE_TEXT "╠" RESET_TEXT},
    {L'╬',BLUE_TEXT "╬" RESET_TEXT},
    {L'•',WHITE_TEXT "•" RESET_TEXT},
    {L' '," "},
    {L'x',RED_TEXT "x" RESET_TEXT},
    {L'≠',"≠"},
    {L'o',WHITE_TEXT "o" RESET_TEXT}
};

/**
 * @brief Struct contenant les paramètres utilisateur
 * @struct Settings
 */
struct Settings{
    std::map<std::string, char> MovementChar;

    std::map<std::string, unsigned> ClassicModeHighScore;

    std::map<std::string, unsigned> InfiniteModeHighScore;

    std::map<std::string, std::string> MiscSetting;
};

/**
 * @brief Liste contenant les clés acceptées.
 * @struct AuthorizedKey
 */
struct AuthorizedKey {
    /** List of authorized keys for moving */
    const std::vector <std::string> MovementKey {"KeyUp", "KeyDown", "KeyLeft", "KeyRight"};
    /** List of authorized keys for highscore */
    const std::vector <std::string> HighScoreKey {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    /** List of authorized keys for Misc settings. Note: Ant Misc Key is stored as a string, for compatibility purposes*/
    const std::vector <std::string> MiscellaneousKey {"Gamemode"};
};

/**
 * @brief AuthorizedKey
 */
const AuthorizedKey AuthorizedKey;

#endif // TYPES_H
