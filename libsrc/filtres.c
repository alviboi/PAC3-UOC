#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "filtres.h"
/**
  @file filtres.c
  @brief Codi font de diferents funcions que serveixen per filtrar un text donat com a paràmetre d'entrada en format .txt.

	Les funcions són:
	
	void fs_head( int fd ) Filtre que mostra les tres primeres línies de l'arxiu i ho mostra per pantalla. Les línies estan separades pel caràcter salt de línia.
	
	void fs_wc( int fd ) Filtre que conta el nombre de caràcters, paraules i línies de l'arxiu d'entrada i ho mostra per pantalla. 

	void fs_nl( int fd ) Filtre que numera les línies de l'entrada i ho trau per pantalla.

	void fs_cut( int fd, int col ) Filtre que mostra la paraula a la posició col de cada línia, la primera paraula de cada línia està a la posició 1, no 0.

  @author Alfredo Rafael Vicente Boix i Eduardo César Galobardes.
  @date 14/12/2015

*/

/*************************************************************************************************/
/**
@brief Funció que imprimix per pantalla el número donat en el paràmetre d'entrada

Amb aquesta funció fem la reserva de memòria necessària per a possar en memòria els enters passats en el paràmetre d'entrada que s'alliberarà posteriorment. Després es crea una cadena de tipus "1. " que es passa per a ser escrita per pantalla. Si la funció presenta cap error es deixa d'executar i no s'allibera la memòria. Si es desitja modificar aquest punt es pot utlitzar la següent modificació:
\verbatim
if(write( 1, nstr, strlen( nstr ) ) == -1){free (nstr); exit;}
\endverbatim

@param num enter proporcionat per a ser escrit per pantalla. 

@returns void la funció no torna cap valor

  */

void printstr(int num)
{
	int aux, i;
	char *nstr;
	

        aux = 1;
	for( i = 1; i < num; i*=10 ) aux++;
	nstr = (char *)malloc( num + 2 );
        sprintf(nstr, "%d ", num);
        if(write( 1, nstr, strlen( nstr ) ) == -1){free (nstr); exit;}
	free (nstr);
	
}

/*************************************************************************************************/
/**
@brief Funció que imprimix per pantalla les tres primeres línees.

Aquest filtre mostrarà les tres primeres línies llegides. Les línies estan separades pel caràcter salt de línia.

@param fd enter que proporcionar l'identificador de l'arxiu que hem obert per a poder filtrar.

@returns void la funció no torna cap valor

  */



void fs_head( int fd )
{
	int count = 0;
	char c;

	while( read( fd, &c, 1 ) && (count < 3) ){
		if(write( 1, &c, 1 )==-1){exit;}
		if ( c == '\n' ) count++;
	}
}

/*************************************************************************************************/
/**
@brief Funció que conta el nombre de caràcters, paraules i línies.

Aquest filtre contarà el nombre de caràcters, paraules i línies de l'entrada i ho mostrarà per pantalla. Es consideren com a separadors de paraules els caràcters salt de línia, tabulador i espai en blanc; i com a separador de línies només el salt de línia. Dues paraules poden estar separades per diversos caràcters separadors.

@param fd enter que proporcionar l'identificador de l'arxiu que hem obert per a poder filtrar.

@returns void la funció no torna cap valor

  */


void fs_wc ( int fd )
{
	int nl = 0, np = 0, nc = 0, sep = 0;
	char c;
	
	while( read( fd, &c, 1 ) ){
		nc++;
		switch( c ){
			case '\n': nl++;
			case '\t':
			case ' ': if( !sep ) {np++; sep = 1;}
				  break;
			default: sep = 0;
		}
	 }
	printstr( nc );
	printstr( np );
	printstr( nl );
	c = 10;
	if(write( 1, &c, 1 )==-1){exit;}
}

/*************************************************************************************************/
/**
@brief Filtre que numera les línies de l'entrada i ho trau per pantalla.

Aquest filtre numera les línies de l'entrada, de manera que queden numerades de la següent manera:
1. Primera línea.
2. Segona línea.
3. etc...

@param fd enter que proporcionar l'identificador de l'arxiu que hem obert per a poder filtrar.

@returns void la funció no torna cap valor

  */


void fs_nl( int fd )
{
	int nl = 1, new = 1;
	char c;

	while( read( fd, &c, 1) ){
		if( new ){
			printstr( nl );
			nl++;
			new = 0;
		}
		if ( c == '\n' ) new = 1;
		if(write( 1, &c, 1 )==-1){exit;}		
	}
}

/*************************************************************************************************/
/**
@brief Filtre que mostra la paraula a la posició col de cada línia, la primera paraula de cada línia està a la posició 1, no 0.

Aquest filtre mostra la paraula a la posició col, que és un paràmetre que s'ha de proporcionar a la funció, de cada línia. El filtre comença a contar per la paraula 1 i a continuació la segona, i així fins acabar. Si no hi ha prou columnes en la línea, la obvia i no la té en compte de manera que una línea amb 3 paraules i donant-li com a paràmetre d'entrada 4, no mostraria res per pantalla i passaria a la següent línea.

@param fd enter que proporcionar l'identificador de l'arxiu que hem obert per a poder filtrar.
@param col enter que indica quin és el número de columna que es vol mostrat de cada línea.
@returns void la funció no torna cap valor

  */


void fs_cut( int fd, int col )
{
	char c;
	int pal = 1, nc = 0, aux2 = 0;

	while( read( fd, &c, 1 ) ){
		if ( c == '\n' ){
			if(pal >= col) {if(write( 1, &c, 1 ) == -1){exit;}}
			pal = 1;
			nc = 0;
		} 
		else if ( pal == col ){ nc++; if(write( 1, &c, 1 )==-1){exit;}}
		if (( c == '\t' ) || ( c == ' ' )) { if (aux2 == 1){} else {pal++;} aux2=1;}
		else {aux2 = 0;}
	}
}

