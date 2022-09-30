#include <stdio.h>
#include <stdlib.h>
#include "scrutil.h"

int main()
{
    scrAttributes colors;
    char buffer[ 255 ];
    char nombre[ 255 ];
    int age;

    // Init
    colors.paper = scrBlue;
    colors.ink = scrYellow;
    scrSetColorsWithAttr( colors );
    scrClear();

    // Show console info
    scrMoveCursorTo( scrGetMaxRows() - 1, 20 );
    printf( "scrutil demo    max rows: %d max cols: %d", scrGetMaxRows(), scrGetMaxColumns() );
    scrMoveCursorTo( scrGetMaxRows() - 2, 20 );
    printf( "_________________________________________" );

    // Title
    scrMoveCursorTo( 0, 33 );
    scrSetColorsWithAttr( scrInvertColors( colors ) );
    printf( "Input data card" );
    scrSetColorsWithAttr( colors );
    scrMoveCursorTo( 1, 33 );
    printf( "_______________" );
    
    // Show form labels
    scrMoveCursorTo( 10, 10 );
    printf( "Name:" );
    scrMoveCursorTo( 12, 10 );
    printf( "Age:" );
    
    // Input data
    scrMoveCursorTo( 10, 30 );
    scrSetColorsWithAttr( scrInvertColors( colors ) );
    printf( "______________________________" );
    scrMoveCursorTo( 10, 30 );
    fgets( nombre, 255, stdin );
    
    scrMoveCursorTo( 12, 30 );
    printf( "______________________________" );
    scrMoveCursorTo( 12, 30 );
    fgets( buffer, 255, stdin );
    age = atoi( buffer );

    // Show data
    scrSetColors( scrRed, scrWhite );
    scrPrintCard( 15, 30, 30, 2 );
    scrMoveCursorTo( 15, 30 );
    printf( "Your name is %s", nombre );
    scrMoveCursorTo( 16, 30 );
    printf( "Your age is %d", age );
    printf( "\n" );

    // Back to safety attributes
    scrSetColors( scrWhite, scrBlack );
    scrShowCursor( true );
    return 0;
}
