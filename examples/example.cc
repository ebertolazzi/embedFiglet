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

static
void
do_test() {
  Figlet::big.print("font: big") ;
  Figlet::larry3d.print("font: larry3d") ;
  Figlet::script.print("font: script") ;
  Figlet::standard.print("font: standard") ;
  Figlet::banner.print("font: banner") ;
  Figlet::doom.print("font: doom") ;
  Figlet::mini.print("font: mini") ;
  Figlet::small.print("font: small") ;
  Figlet::straight.print("font: straight") ;
}

static
void
setMonospaced() {
  Figlet::big.setMonospaced() ;
  Figlet::larry3d.setMonospaced() ;
  Figlet::script.setMonospaced() ;
  Figlet::standard.setMonospaced() ;
  Figlet::banner.setMonospaced() ;
  Figlet::doom.setMonospaced() ;
  Figlet::mini.setMonospaced() ;
  Figlet::small.setMonospaced() ;
  Figlet::straight.setMonospaced() ;
}

static
void
setFullWidth() {
  Figlet::big.setFullWidth() ;
  Figlet::larry3d.setFullWidth() ;
  Figlet::script.setFullWidth() ;
  Figlet::standard.setFullWidth() ;
  Figlet::banner.setFullWidth() ;
  Figlet::doom.setFullWidth() ;
  Figlet::mini.setFullWidth() ;
  Figlet::small.setFullWidth() ;
  Figlet::straight.setFullWidth() ;
}

static
void
setPacked() {
  Figlet::big.setPacked() ;
  Figlet::larry3d.setPacked() ;
  Figlet::script.setPacked() ;
  Figlet::standard.setPacked() ;
  Figlet::banner.setPacked() ;
  Figlet::doom.setPacked() ;
  Figlet::mini.setPacked() ;
  Figlet::small.setPacked() ;
  Figlet::straight.setPacked() ;
}

static
void
setSmushed() {
  Figlet::big.setSmushed() ;
  Figlet::larry3d.setSmushed() ;
  Figlet::script.setSmushed() ;
  Figlet::standard.setSmushed() ;
  Figlet::banner.setSmushed() ;
  Figlet::doom.setSmushed() ;
  Figlet::mini.setSmushed() ;
  Figlet::small.setSmushed() ;
  Figlet::straight.setSmushed() ;
}

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
  
  setMonospaced() ; do_test() ;
  setFullWidth()  ; do_test() ;
  setPacked()     ; do_test() ;
  setSmushed()    ; do_test() ;
  
  Figlet::standard.print("Figlet") ;

  cout << "ALL DONE!\n" ;
  return 0;
}
