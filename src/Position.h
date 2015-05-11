#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

/**
    @brief Voici le module Position, qui permet la gestion du positionnement en X et Y
    @author Jonathan P.
    @author Cyril C.
    @version 0.3

    @struct Position
*/
typedef struct
{
    unsigned char positionX;    /*!< \brief Position en X, comprise entre 0 et 255 */
    unsigned char positionY;    /*!< \brief Position en X, comprise entre 0 et 255 */
} Position;

/**
    @brief Constructeur pour Position
    @param [in] positionX Entier entre 0 et 255
    @param [in] positionY Entier entre 0 et 255
    @return Pointeur sur Position
*/

Position * PositionConstructeur(const unsigned char positionX,const unsigned char positionY);

/**
    @brief Destructeur pour Position
    @param [in-out] position Structure Position
*/

void PositionDestructeur (Position * position);

/**
    @brief Accesseur pour PositionX
    @param [in] position Structure Position
    @return positionX, Entier compris entre 0 et 255
*/
unsigned char PositionGetX(const Position * position);

/**
    @brief Accesseur pour PositionY
    @param [in] position Structure Position
    @return positionY, Entier compris entre 0 et 255
*/
unsigned char PositionGetY(const Position * position);

/**
    @brief Mutateur pour PositionX
    @param [in,out] position Structure Position
    @param [in] x Entier compris entre 0 et 255
    @return Pas de retour
*/
void PositionSetX(Position * Position, const unsigned char x);

/**
    @brief Mutateur pour PositionY
    @param [in,out] position Structure Position
    @param [in] y Entier compris entre 0 et 255
    @return Pas de retour
*/
void PositionSetY(Position * position, const unsigned char y);

/**
    @brief Fonction pour obtenir la position de la case suivante par rapport a une direction
    @param [in] position Pointeur sur position
    @param [in] direction Entier compris entre 0 et 7
    @return Position Structure Position
*/
Position PositionDirectionSuivante(const Position * position, const unsigned char direction);

/**
    @brief Test de regression
    @return Pas de retour
*/
void PositionTestRegression();

#endif
