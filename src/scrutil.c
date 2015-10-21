/*
    Manejo de la consola
*/

#include "scrutil.h"

#include <string.h>
#include <stdio.h>

/* Detectar el sistema operativo */
#ifdef _WIN32
    #define SO_WINDOWS
#else
    #ifdef __WIN32__
        #define SO_WINDOWS
    #else
        #ifdef __WINDOWS__
            #define SO_WINDOWS
        #else
            #define SO_UNIX
        #endif
    #endif
#endif

#ifdef SO_WINDOWS
#include <windows.h>

/* WinColors */
/// Colores para tinta
static short int winInkColors[ scrUndefinedColor + 1 ];
/// Colores para fondo
static short int winPaperColors[ scrUndefinedColor + 1 ];

static void initWindowsColors()
/**
    Windows distingue entre colores de fondo y colores de tinta,
    y sigue el std. RGB, lo que obliga a definir los colores
    sencillos para construirlos.
*/
{
    winInkColors[ scrBlack ]     = 0;
    winInkColors[ scrBlue ]      = FOREGROUND_BLUE;
    winInkColors[ scrRed ]       = FOREGROUND_RED;
    winInkColors[ scrMagenta ]   = FOREGROUND_BLUE | FOREGROUND_RED;
    winInkColors[ scrGreen ]     = FOREGROUND_GREEN;
    winInkColors[ scrCyan ]      = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    winInkColors[ scrYellow ]    = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    winInkColors[ scrWhite ]     = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    winInkColors[ scrUndefinedColor ]  = 0;

    winPaperColors[ scrBlack ]   = 0;
    winPaperColors[ scrBlue ]    = BACKGROUND_BLUE;
    winPaperColors[ scrRed ]     = BACKGROUND_RED;
    winPaperColors[ scrMagenta ] = BACKGROUND_BLUE | BACKGROUND_RED;
    winPaperColors[ scrGreen ]   = BACKGROUND_GREEN;
    winPaperColors[ scrCyan ]    = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    winPaperColors[ scrYellow ]  = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    winPaperColors[ scrWhite ]   = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    winPaperColors[ scrUndefinedColor ] = 0;
}
#else
    // Commands
    static const short int MaxCmdBuffer = 32;
    /// Caracts. por el que empiezan todos los comandos
    static const char * CSI = "\33[";
    static const char * CmdClearScreen = "2J";
    static char cmd[MaxCmdBuffer];

    // Colors
    /// Colores para la tinta
    static char cmdUnixInkColors[ scrUndefinedColor + 1 ][MaxCmdBuffer];
    /// Colores para el fondo
    static char cmdUnixPaperColors[ scrUndefinedColor + 1 ][MaxCmdBuffer];
    /// Max. filas en pantalla
    static const short int UnixLastLine = 25;
    static const short int UnixLastColumn = 80;


    static void initUnixColors()
    /**
        Linux sigue los c�digos de control ANSI que comienzan con
        ESC, y con ellos se puede limpiar la pantalla, cambiar los colores, ...
    */
    {
        sprintf( cmdUnixInkColors[ scrBlack ], "%s%s", CSI, "30m" );
        sprintf( cmdUnixInkColors[ scrBlue ], "%s%s", CSI, "34m" );
        sprintf( cmdUnixInkColors[ scrRed ], "%s%s", CSI, "31m" );
        sprintf( cmdUnixInkColors[ scrMagenta ], "%s%s", CSI, "35m" );
        sprintf( cmdUnixInkColors[ scrGreen ], "%s%s", CSI, "32m" );
        sprintf( cmdUnixInkColors[ scrCyan ], "%s%s", CSI, "36m" );
        sprintf( cmdUnixInkColors[ scrYellow ], "%s%s", CSI, "93m" );
        sprintf( cmdUnixInkColors[ scrWhite ], "%s%s", CSI, "37m" );
        sprintf( cmdUnixInkColors[ scrUndefinedColor ], "%s%s", CSI, "30m" );

        sprintf( cmdUnixPaperColors[ scrBlack ], "%s%s", CSI, "40m" );
        sprintf( cmdUnixPaperColors[ scrBlue ], "%s%s", CSI, "44m" );
        sprintf( cmdUnixPaperColors[ scrRed ], "%s%s", CSI, "41m" );
        sprintf( cmdUnixPaperColors[ scrMagenta ], "%s%s", CSI, "45m" );
        sprintf( cmdUnixPaperColors[ scrGreen ], "%s%s", CSI, "42m" );
        sprintf( cmdUnixPaperColors[ scrCyan ], "%s%s", CSI, "46m" );
        sprintf( cmdUnixPaperColors[ scrYellow ], "%s%s", CSI, "103m" );
        sprintf( cmdUnixPaperColors[ scrWhite ], "%s%s", CSI, "47m" );
        sprintf( cmdUnixPaperColors[ scrUndefinedColor ], "%s%s", CSI, "40m" );
    }
#endif

static scrAttributes libAttrs;
static bool inited = false;

static inline void scrInit()
{
    if ( !inited ) {
        #ifdef SO_WINDOWS
            initWindowsColors();
        #else
            initUnixColors();
        #endif

        libAttrs.ink = scrWhite;
        libAttrs.paper = scrBlack;
        inited = true;
    }

    return;
}

void scrClear()
{
    scrInit();

    #ifdef SO_WINDOWS
	COORD pos = { 0, 0 };
        DWORD cars;
        HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD dwConSize;

        if( hStdOut != INVALID_HANDLE_VALUE
         && GetConsoleScreenBufferInfo( hStdOut, &csbi ) )
        {
            dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

            FillConsoleOutputCharacter(
                hStdOut,
                ' ',
                dwConSize,
                pos,
                &cars
            );

            FillConsoleOutputAttribute(
                hStdOut,
                winPaperColors[ libAttrs.paper ] | winInkColors[ libAttrs.ink ],
                dwConSize,
                pos,
                &cars
            );
        }
    #else
        strcpy( cmd, CSI );
        strcat( cmd, CmdClearScreen );
        printf( "%s", cmd );
    #endif

    scrMoveCursorTo( 0, 0 );
}

void scrSetColorsWithAttr(scrAttributes colors)
{
    scrInit();

    libAttrs.paper = colors.paper;
    libAttrs.ink = colors.ink;

    #ifdef SO_WINDOWS
        SetConsoleTextAttribute(
            GetStdHandle( STD_OUTPUT_HANDLE ),
            winPaperColors[ libAttrs.paper ] | winInkColors[ libAttrs.ink ]
        );
    #else
        printf( "%s%s",
            cmdUnixInkColors[ colors.ink ],
            cmdUnixPaperColors[ colors.paper ]
        );
    #endif
}

void scrSetColors(Color tinta, Color papel)
{
    scrAttributes atrs;

    atrs.paper = papel;
    atrs.ink = tinta;

    scrSetColorsWithAttr( atrs );
}

void scrMoveCursorToPos(scrPosition pos)
{
    scrMoveCursorTo( pos.row, pos.column );
}

void scrMoveCursorTo(unsigned short int fila, unsigned short int columna)
{
    scrInit();

    #ifdef SO_WINDOWS
        COORD pos;

        pos.X = columna;
        pos.Y = fila;

        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
    #else
        printf( "%s%d;%dH", CSI, fila + 1, columna + 1 );
    #endif
}

scrPosition scrGetConsoleSize()
{
    scrPosition pos;

    pos.row = pos.column = -1;
    scrInit();

    #ifdef SO_WINDOWS
        CONSOLE_SCREEN_BUFFER_INFO infoPantalla;
        GetConsoleScreenBufferInfo(
                GetStdHandle( STD_OUTPUT_HANDLE ), &infoPantalla
        );

        pos.row = infoPantalla.srWindow.Bottom + 1;
        pos.column = infoPantalla.srWindow.Right + 1;
    #else
        pos.row = UnixLastLine;
        pos.column = UnixLastColumn;
    #endif

    return pos;
}

scrAttributes scrGetCurrentAttributes()
{
    scrInit();
    return libAttrs;
}

unsigned short int scrGetMaxRows()
{
    return scrGetConsoleSize().row;
}

unsigned short int scrGetMaxColumns()
{
    return scrGetConsoleSize().column;
}

scrPosition scrGetCursorPosition()
{
    scrPosition toret;

    scrInit();
    memset( &toret, 0, sizeof( scrPosition ) );

    #ifdef SO_WINDOWS
        CONSOLE_SCREEN_BUFFER_INFO infoPantalla;
        GetConsoleScreenBufferInfo(
                GetStdHandle( STD_OUTPUT_HANDLE ),
                &infoPantalla
        );

        toret.row = infoPantalla.dwCursorPosition.Y;
        toret.column = infoPantalla.dwCursorPosition.X;
    #else
        toret.row = -1;
        toret.column = -1;
    #endif

    return toret;
}

void scrShowCursor(bool see)
{
    scrInit();

    #ifdef SO_WINDOWS
        CONSOLE_CURSOR_INFO info;

        info.dwSize = 10;
        info.bVisible = (BOOL) see;
        SetConsoleCursorInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &info );
    #else
        printf( "%s?25%c", CSI, see ? 'h' : 'l' );
    #endif
}
