#ifndef DISPLAYUTILS_H
#define DISPLAYUTILS_H

#include <iostream>
#include "types.h"

/*!
 * \file DisplayUtils.h
 * \brief Un ensemble de fonction permettant de simplifier notre travail avec la console
 * \author BOULAY Mathias,
 * \author MONBEIG Maxime
 * \author PINEL Anthony
 * \author JUBERT Killian
 * \author DAURELLE Nicolas
 * \version 1.0
 * \date 15 janvier 2021
 */


/**
 * @brief Nettoie l'écran pour qu'il n'y ai plus rien sur l'écran
 * @fn void ClearDisplay();
 * @return void
 */
void ClearDisplay();

/**
 * @brief Affiche le terrain utilisé. Gère aussi les couleurs via une table de correspondance.
 * @param[in] Map Le terrain à afficher
 * @param[in] Pacman Le pacman à afficher
 * @param[in] Ghosts Les fantômes à afficher
 * @fn void DisplayGameMap(const GameMap &Map,const Pacman &Pacman,const Ghosts &Ghosts);
 * @return void
 */
void DisplayGameMap(const GameMap &Map,const Pacman &Pacman,const Ghosts &Ghosts);

/**
 * @brief Affiche le score, le highscore ainsi que les vies restantes.
 * @param[in] Map Le terrain à afficher
 * @param[in] Pacman Le pacman à afficher
 * @param[in] Ghosts Les fantômes à afficher
 * @fn void DisplayLevelHeader(const unsigned &Score,const unsigned &Lives,const unsigned &HighScore);
 * @return void
 */
void DisplayLevelHeader(const unsigned &Score,const unsigned &Lives,const unsigned &HighScore);

#endif // DISPLAYUTILS_H
