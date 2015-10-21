#ifndef SCRUTIL_H_INCLUDED
#define SCRUTIL_H_INCLUDED

#include <stdbool.h>

/** Colores */
typedef enum _Color {
    scrBlack, scrBlue, scrRed, scrMagenta,
    scrGreen, scrCyan, scrYellow, scrWhite,
    scrUndefinedColor
} Color;

/**
    Describe una pos. en la pantalla
*/
typedef struct _scrPosition {
    unsigned short int row;
    unsigned short int column;
} scrPosition;

typedef struct _scrAttributes {
    Color paper;
    Color ink;
} scrAttributes;

/**
    Borra la pantalla
*/
void scrClear();

/**
    Indica los colores del texto a escribir
    @param tinta Color de la tinta
    @param papel Color de fondo
*/
void scrSetColors(Color tinta, Color papel);

/**
    Indica los colores del texto a escribir
    @param color Color de la tinta y el papel
    @see scrAttributes
*/
void scrSetColorsWithAttr(scrAttributes color);

/**
    Obtiene los atributos en uso
    @return Los colores como una estructura scrAttributes
    @see scrAttributes
*/
scrAttributes scrGetCurrentAttributes();

/**
    Obtiene el char en una pos.
    @param La pos. como una estructura scrPosition
    @return El valor entero del char
    @see scrAttributes
*/
int scrGetCharacterAt(scrPosition pos);

/**
    Mover el cursor a una pos. determinada
    @param fila La fila en la que colocar el cursor
    @param columna La columna en la que colocar el cursor
*/
void scrMoveCursorTo(unsigned short int fila, unsigned short int columna);

/**
    Mover el cursor a una pos. determinada
    @param pos Estructura scrPosition conteniendo la pos.
    @see scrPosition
*/
void scrMoveCursorToPos(scrPosition pos);

/**
    Devuelve el num. de filas y columnas max.
    @return La info. como estructura scrPosition
    @see scrPosition
    @note en Unix siempre devuelve 25x80
*/
scrPosition scrGetConsoleSize();

/**
    Devuelve el num. de filas
    @return El max. num. de filas
    @see scrPosition
    @note En caso de que la funcionalidad no se soporte,
          devuelve -1 en ambos campos de scrPosition
*/
unsigned short int scrGetMaxRows();

/**
    Devuelve el num. de columnas
    @return El max. num. de columnas
    @see scrGetConsoleSize
*/
unsigned short int scrGetMaxColumns();

/**
    Devuelve la pos. del cursor
    @return La pos. del cursor
    @see scrGetConsoleSize
    @see en Unix siempre devuelve -1, -1
*/
scrPosition scrGetCursorPosition();

/**
    Esconde o visualiza el cursor
    @param see Si es verdadero, lo visualiza, si es falso lo esconde.
*/
void scrShowCursor(bool see);

#endif // SCRUTIL_H_INCLUDED
