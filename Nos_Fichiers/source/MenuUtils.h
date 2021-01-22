#ifndef MENUUTILS_H
#define MENUUTILS_H

/**
 * \file MenuUtils.h
 * \brief A set of function to ease our work with storing and retrieving settings
 * \author BOULAY Mathias,
 * \author MONBEIG Maxime
 * \author PINEL Anthony
 * \author JUBERT Killian
 * \author DAURELLE Nicolas
 * \version 1.0
 * \date 18 janvier 2021
 */

#include "types.h"
#include "SettingUtils.h"
#include "InputUtils.h"
#include "DisplayUtils.h"

/**
 * @brief Affiche le menu principal, et appel les sous menus si demandé par l'utilisateur
 * @fn void MainMenu();
 * @returns void
 */
void MainMenu();

/**
 * @brief Affiche des instructions liées au mode de jeu séléctionné et propose de lancer le jeu
 * @fn void PlayMenu();
 * @returns void
 */
void PlayMenu();

/**
 * @brief Affiche les paramètres et réagit en fonction de ce qui est demandé par l'utilisateur
 * @fn void SettingMenu();
 * @returns void
 */
void SettingMenu();

/**
 * @brief Permet à l'utilisateur de séléctionner son mode de jeu favori
 * @fn void SelectGamemodeMenu();
 * @returns void
 */
void SelectGamemodeMenu();

/**
 * @brief Affiche les meilleurs scores
 * @fn void LeaderdoardMenu();
 * @returns void
 */
void LeaderdoardMenu();

/**
 * @brief Permet de re-initialiser les tableaux de scores
 * @fn void ResetLeaderbordMenu();
 * @returns void
 */
void ResetLeaderbordMenu();

/**
 * @brief Permet de re-initialiser les tableaux de scores
 * @fn void ChangeBindingsMenu();
 * @returns void
 */
void ChangeBindingsMenu();

/**
 * @brief Affiche le logo pacman
 * @fn void DisplayPacmanHeader();
 * @returns void
 */
void DisplayPacmanHeader();

/**
 * @brief Afficher les instructions du mode classique
 * @fn void DisplayClassicInstruction();
 * @returns void
 */
void DisplayClassicInstruction();

/**
 * @brief Afficher les instructions du mode infini
 * @fn void DisplayInfiniteInstruction();
 * @returns void
 */
void DisplayInfiniteInstruction();

/**
 * @brief Démonte le moral du joueur avec un message "sympa". Stocke le score si il est bon
 * @param[in] Score Le score du joueur.
 * @param[in] Si le score fait partie du mode classique
 * @fn void YouLostMenu(const unsigned & Score, const bool isClassicMode = true);
 * @returns void
 */
void YouLostMenu(const unsigned & Score, const bool isClassicMode = true);

/**
 * @brief Démonte le moral du joueur avec un message "sympa". Stocke le score si il est bon
 * @param[in] Score Le score du joueur.
 * @param[in] Si le score fait partie du mode classique
 * @fn void YouLostMenu(const unsigned & Score, const bool isClassicMode = true);
 * @returns void
 */
void YouWonMenu(const unsigned &Score, const bool isClassicMode = true);


#endif // MENUUTILS_H
