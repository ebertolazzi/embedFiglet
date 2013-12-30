/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Copyright (C) 2013                                                      |
 |                                                                          |
 |         , __                 , __                                        |
 |        /|/  \               /|/  \                                       |
 |         | __/ _   ,_         | __/ _   ,_                                | 
 |         |   \|/  /  |  |   | |   \|/  /  |  |   |                        |
 |         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       |
 |                           /|                   /|                        |
 |                           \|                   \|                        |
 |                                                                          |
 |      Enrico Bertolazzi                                                   |
 |      Dipartimento di Ingegneria Industriale                              |
 |      Universita` degli Studi di Trento                                   |
 |      email: enrico.bertolazzi@unitn.it                                   |
 |                                                                          |
\*--------------------------------------------------------------------------*/

#include "Figlet.hh"
#include <sstream>

using namespace std ;

int
main() {

  Figlet::standard.print("Fractions") ;
  for ( int i = 2 ; i <= 4 ; ++i ) {
    ostringstream ss ;
    ss << "5/" << i << " = " << 5.0/i ;
    Figlet::small.print(ss.str().c_str()) ;
  }
  
  Figlet::standard.setMonospaced() ;
  Figlet::standard.print("Monospaced") ;

  Figlet::standard.setFullWidth() ;
  Figlet::standard.print("FullWidth") ;

  Figlet::standard.setPacked() ;
  Figlet::standard.print("Packed") ;

  Figlet::standard.setSmushed() ;
  Figlet::standard.print("Smushed") ;

  Figlet::small.printFramed("SINGLE",cout,Figlet::FIGLET_SINGLE);
  Figlet::small.printFramed("DOUBLE",cout,Figlet::FIGLET_DOUBLE);

  Figlet::big.print("check \"_\" 7l 7_l e_s") ;
  Figlet::standard.print("check \"_\" 7l 7_l e_s") ;

  cout << "ALL DONE!\n" ;
  return 0;
}
