#ifndef SETTINGUTILS_H
#define SETTINGUTILS_H

/**
 * \file SettingUtils.h
 * \brief A set of function to ease our work with storing and retrieving settings
 * \author BOULAY Mathias,
 * \author MONBEIG Maxime
 * \author PINEL Anthony
 * \author JUBERT Killian
 * \author DAURELLE Nicolas
 * \version 1.0
 * \date 16 janvier 2021
 */

#include "types.h"
#include <fstream>
#include <iostream>
#include <algorithm>

/**
 * @brief Charge les paramètres par défaut. Renvoie les paramètres
 * @fn Settings LoadDefaultSettings();
 * @returns Settings
 */
Settings LoadDefaultSettings();

/**
 * @brief Charge les paramètres utilisateur.
 * @fn Settings LoadSettings();
 * @returns Settings
 */
Settings LoadSettings();

/**
 * @brief Applique les paramètres utilisateur
 * @param[in] St Paramètres utilisateur
 * @fn void ApplySettings(const Settings &St);
 * @returns void
 */
void ApplySettings(const Settings &St);

/**
 * @brief Stocke le score si il est assez bon.
 * @param[in, out] St Paramètres utilisateur
 * @param[in]
 * @fn InsertHighScore(Settings &St,const unsigned &Highscore, const bool ClassicGamemode);
 * @returns void
 */
void InsertHighScore(Settings &St,const unsigned &Highscore, const bool ClassicGamemode);

#endif // SETTINGUTILS_H
