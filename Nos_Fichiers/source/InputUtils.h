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
 * @param[in] TimePressure Le temps (en ds) avant que le char par défaut '\0' soit renvoyé
 * @fn void SetRawInput();
 * @return void
 */
void SetRawInput(const unsigned TimePressure = 0);

/**
 * @brief Donne la première touche du clavier pressée imprimable dans une console.
 * @param[in] TimePressure Le temps (en ds) avant que le char par défaut '\0' soit renvoyé
 * @fn char ReadKeyboardInput();
 * @return char
 */
char ReadKeyboardInput(const unsigned TimePressure = 0);

/**
 * @brief Donne la première touche de clavier pressée qui est dans l'ensemble passé en argument.
 * @param[in] Keys Liste de touches considérées valides
 * @param[in] TimePressure Le temps (en ds) avant que le char par défaut '\0' soit renvoyé. Le char nul est renvoyé uniquement si ce paramètre est différent de 0;
 * @fn char ReadSpecificKeyboardInput(const std::vector<char> Keys);
 * @returns char
 */
char ReadSpecificKeyboardInput(std::vector<char> Keys, const unsigned TimePressure = 0);



#endif // INPUTUTILS_H
