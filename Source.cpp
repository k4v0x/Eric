#include <ncurses.h>
#include <random>

using namespace std;

int directieOpusa ( int directie ) {
  return ( directie + 2 ) % 4;
}

char mapareCaractere( int a1 ) {
  if( a1 == 0 ) { return '.'; }
  if( a1 == 1 ) { return '#'; } 
  if( a1 == 2 ) { return 'S'; } 
  if( a1 == 3 ) { return '@'; } 
  return ' ';
}

void dispMap( int map[][100], int w, int h ){
  int row,col;
  for(row=0;row<h - 1;row++){
    for(col=0;col<w - 1;col++){
      mvaddch(row,col, mapareCaractere( map[row][col] ) );
    }
  }
}

int main () {
    initscr();
    
    cbreak();
    noecho();
    
    curs_set( 0 );
    timeout( 100 );
    
    clear();
    
    bool areWePlaying = true;
    
    int harta[ COLS ] [ 100 ];
    int xS = 2, yS = 2;
    int xC = xS, yC = yS;
   
    int d = 1;
    int dir[ COLS * LINES ];
   
    int directieAcum = 1;
    dir [ 0 ] = directieAcum; 
    
    int dY[ 4 ] = { 0, 1, 0, -1 };
    int dX[ 4 ] = { -1, 0, 1, 0 }; 
    
    harta[ 6 ][ 3 ] = 3;
    
    for( int i = 0 ; i < COLS; i++ ) {
      harta [ 0 ] [ i ] = 1;
      harta [ LINES - 2 ] [ i ] = 1;
    }
    
    for( int i = 0 ; i < LINES; i++ ) {
      harta [ i ] [ 0 ] = 1;
      harta [ i ] [ COLS - 2 ] = 1;
    }
    
    while( areWePlaying ) {
      dispMap( harta, COLS, LINES );
      
      refresh();
      
      for( int i = d; i > 0; i-- ) {
        dir[ i ] = dir[ i - 1 ];
      }
      dir[ 0 ] = directieAcum;
      
      harta[ xS ][ yS ] = 1;
      
      xS += dX[ directieAcum ];
      yS += dY[ directieAcum ];
      
      if( harta[ xS ][ yS ] == 1 || harta[ xS ][ yS ] == 2 ) {
        areWePlaying = false;
        break;
      }
      
      if( harta[ xS ][ yS ] == 3 ) {
        xC += dX [ directieOpusa( dir[ d - 1 ] ) ];
        yC += dY [ directieOpusa( dir[ d - 1 ] ) ];
        dir[ d ] = dir[ d - 1 ];
        d++;
        harta[ 6 ][ 3 + d * 3 ] = 3;
      }
      
      harta[ xS ][ yS ] = 2;
      harta[ xC ][ yC ] = 0;
      
      xC += dX[ dir[ d - 1 ] ];
      yC += dY[ dir[ d - 1 ] ];
       
      switch ( getch() ) {
        case 'w' :
          if( directieAcum != 2 ) { directieAcum = 0; }
          break;
        case 'd' :
          if( directieAcum != 3 ) { directieAcum = 1; }
          break;
        case 's' :
          if( directieAcum != 0 ) { directieAcum = 2; }
          break;
        case 'a' :
          if( directieAcum != 1 ) { directieAcum = 3; }
          break;
        case 'q' :
          areWePlaying = false;
          break;
      }
      
    }
    timeout( -1 );
    getch();
    
    endwin();  
}
