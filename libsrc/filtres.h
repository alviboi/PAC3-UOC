/**
  @file filtres.h
  @brief Capçaleres de les funcions de filtres.c

  A l'arxiu de capaçaleres es troben les funcions necessàries per a processar l'arxiu font filtres.c. Les funcions són:
	
	void fs_head( int fd ); Filtre que mostra les tres primeres línies de l'arxiu i ho mostra per pantalla. Les línies estan separades pel caràcter salt de línia '\n'.
	
	void fs_wc( int fd ); Filtre que conta el nombre de caràcters, paraules i línies de l'arxiu d'entrada i ho mostra per pantalla. 

	void fs_nl( int fd ); Filtre que numera les línies de l'entrada i ho trau per pantalla.

	void fs_cut( int  fd, int col ); Filtre que mostra la paraula a la posició col de cada línia, la primera paraula de cada línia està a la posició 1, no 0.

  @author Alfredo Rafael Vicente Boix i Eduardo César Galobardes 
  @date 14/12/2015

*/

void fs_head( int fd );
void fs_wc( int fd );
void fs_nl( int fd );
void fs_cut( int  fd, int col );

