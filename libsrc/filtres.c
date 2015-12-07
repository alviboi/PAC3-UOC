#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "filtres.h"

void printstr(int num)
{
	int aux, i;
	char *nstr;
	

        aux = 1;
	//nstr = (char *)malloc( 10 );
        for( i = 1; i < num; i*=10 ) aux++;
	nstr = (char *)malloc( num + 2 );
        sprintf(nstr, "%d ", num);
        if(write( 1, nstr, strlen( nstr ) ) == -1){exit;}
	free (nstr);
	
}

void fs_head( int fd )
{
	int count = 0;
	char c;

	while( read( fd, &c, 1 ) && (count < 3) ){
		if(write( 1, &c, 1 )==-1){exit;}
		if ( c == '\n' ) count++;
	}
}

void fs_wc( int fd )
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

