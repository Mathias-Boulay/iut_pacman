#ifndef INPUTUTILS_H
#define INPUTUTILS_H

/*!
 * \file InputUtils.h
 * \brief Ensemble de fonctions permettant de simplifier la capture d'entrées au clavier
 * \author BOULAY Mathias (pour le wrapping des méthodes),
 * \author Gens sur internet.
 * \version 1.0
 * \date 15 janvier 2021
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <vector>
#include <cctype>

/**
 * @brief Ré-initialise le terminal à son mode normal
 * @fn void ResetRawInput();
 * @return void
 */
void ResetRawInput();


/**
 * @brief Change la console dans un mode non-buffurisé. Permet la capture touche par touche.
 * @fn void SetRawInput();
 * @return void
 */
void SetRawInput();

/**
 * @brief Donne la première touche du clavier pressée imprimable dans une console.
 * @fn char ReadKeyboardInput();
 * @return char
 */
char ReadKeyboardInput();

/**
 * @brief Donne la première touche de clavier pressée qui est dans l'ensemble passé en argument.
 * @param[in] Keys Liste de touches considérées valides
 * @fn char ReadSpecificKeyboardInput(const std::vector<char> Keys);
 * @returns char
 */
char ReadSpecificKeyboardInput(const std::vector<char> Keys);



#endif // INPUTUTILS_H
