/*
 *  $Id$
 *  Typer
 *  
 *  Wrote By mmr <mmr@b1n.org>
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DELAY_ERROR 570000   /* 0.57 seconds */
#define DELAY_RIGHT 350000   /* 0.35 seconds */
#define DELAY_FINAL 1000000  /* 1.0  seconds */

#define TERM_CHAR   '_'
#define TERM_COLOR  "5;1;33" /* Light Blinking Green */
#define TEXT_COLOR  "0;1;32" /* Turn Off Blinking, Turn On Bold with (Light)Green */

void printSentence( char * , int );
void printChar( char );
void printTerminal( char, char *, char * );
void usage( char * );
void clearScreen( void );

int
main( int argc, char **argv )
{
    if( argc <= 2 )
    {
        usage(argv[0]);
        return 1;
    }

    printSentence( argv[1], atoi(argv[2]) );
    return 0;
}

void
printSentence( char *string, int error_possibility )
{
    int i = 0;
    char aux  = 0;
    int tmp; 

    if(error_possibility == 0)
    {
        error_possibility = 100;
    }

    srandom((unsigned int) ((long) time((time_t *) 0) ^ getpid()));

    /* coloca em verde e imprime _ intermitente */
    clearScreen();
    printTerminal( TERM_CHAR, TERM_COLOR, TEXT_COLOR );
    while( string[i] != '\0' )
    {
        /* BackSpace pra apagar o _ intermitente */
        printChar( '\b' );

        /* Vendo se Errou */
        tmp = 0;
        tmp = random();
        if( tmp %  error_possibility == 0 )
        {
            /*
                Se Errou, pegar um char randomico entre 'a' (97) e 'z' 122
                122 - 97 = 25
            */

            aux = (((int)random()%25)+97);

            /*
                Se a tecla pega, miseravelmente, foi a esperada, nao fazer nada.
                Se nao for, imprimir a errada, esperar um pouco e apagar a errada (\b)
            */
            if(aux != string[i])
            {
                printChar( aux );
                usleep(((int)random() % DELAY_ERROR));
                printChar( '\b' );
            }
        }
        usleep(random() % DELAY_RIGHT);
        printChar( string[i] );
        printTerminal( TERM_CHAR, TERM_COLOR, TEXT_COLOR );
        i++;
    }
    usleep( DELAY_FINAL );
    printTerminal(' ', "0", "0");
    clearScreen();
}

void
usage( char *name )
{
    printf( "Usage: %s string error_possibility\n", name );
}

void
clearScreen( void )
{
    printf("\033[2J\033[0;0H");
    fflush(stdout);
}

void
printChar( char c )
{
    printf( "%c", c );
    fflush(stdout);
}

void
printTerminal( char term_char, char *term_color, char *text_color )
{
    printf("\033[%sm%c\033[0m\033[%sm", term_color, term_char, text_color );
    fflush(stdout);
}
