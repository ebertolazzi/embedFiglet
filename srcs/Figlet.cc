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

//
// file: Figlet.cc
//

#include "Figlet.hh"
#include <string.h>

namespace Figlet {

  using namespace std ;

  Banner::Banner( FontFiglet const * _characters, 
                  char               _Hardblank,
                  unsigned           _Height,
                  unsigned           _FontMaxLen,
                  unsigned           _FontSize )
  : characters(_characters)
  , Hardblank(_Hardblank)
  , Height(_Height)
  , FontMaxLen(_FontMaxLen)
  , FontSize(_FontSize)
  , charPosition(0)
  , printMode(FIGLET_SMUSHED)
  {
    fill(charToTable,charToTable+maxTableSize,0) ; // caratteri non noti mappati in spazi
    fill(rspaces,rspaces+Height,0) ;
    for ( unsigned i=0 ; i < FontSize ; ++i ) {
      unsigned ipos = characters[i].nchar ;
      if ( ipos < maxTableSize ) {
        charToTable[ipos] = i ;
        charWidth[ipos]   = strlen(characters[i].rows[0]) ;
      }
    }
    Width = charWidth[charToTable[int('M')]] ;
  }

  void
  Banner::init() {
    charPosition = 0 ;
    std::fill( rspaces, rspaces+Height, 0  ) ;
    for ( unsigned i = 0 ; i < Height ; ++i ) *lines[i] = '\0' ;
  }
  
  // ---------------------------------------------------------------------------

  bool
  Banner::pushFullWidth( unsigned c ) {
    FontFiglet const * f = characters + charToTable[c]  ;
    unsigned cw = charWidth[c] ;

    // controllo che il carattere stia nel buffer
    if ( charPosition+cw > maxLenght ) return false ;

    for ( unsigned i = 0 ; i < Height ; ++i ) strcpy( lines[i]+charPosition, f->rows[i] ) ;
    charPosition += cw ;

    // aggiorno spazi liberi a destra
    std::copy( f -> rspaces, f -> rspaces + Height, rspaces ) ;
    return true ;
  }
  
  // ---------------------------------------------------------------------------

  bool
  Banner::pushMonospaced( unsigned c ) {
    FontFiglet const * f = characters + charToTable[c] ;
    unsigned cw = charWidth[c] ;
    unsigned dd = Width >= cw ? Width - cw : 0 ; // extra spazi

    // controllo che il carattere stia nel buffer
    if ( charPosition+cw+dd > maxLenght ) return false ;

    // centratura carattere
    unsigned dR = dd/2 ;
    unsigned dL = dd-dR ;
    
    for ( unsigned i = 0 ; i < Height ; ++i ) {
      char       * p = lines[i]+charPosition ;
      char const * q = f->rows[i] ;
      for ( unsigned j = 0 ; j < dL ; ++j ) *p++ = ' ' ;
      for ( unsigned j = 0 ; j < cw ; ++j ) *p++ = *q++ ;
      for ( unsigned j = 0 ; j < dR ; ++j ) *p++ = ' ' ;
      *p = '\0' ;
    }
    charPosition += cw+dd ;

    // aggiorno spazi liberi a destra
    std::copy( f -> rspaces, f -> rspaces + Height, rspaces ) ;
    return true ;
  }
  
  // ---------------------------------------------------------------------------

  bool
  Banner::pushPacked( unsigned c ) {
    FontFiglet const * f = characters + charToTable[c]  ;
    unsigned cw = charWidth[c] ;
    // calcolo overlapping
    short overlap = rspaces[0] + f->lspaces[0] ;
    for ( unsigned i = 1 ; i < Height ; ++i ) {
      short tmp = rspaces[i] + f->lspaces[i] ;
      if ( tmp < overlap ) overlap = tmp ;
    }

    // controllo che il carattere stia nel buffer
    if ( charPosition+cw > maxLenght+overlap ) return false ;
    
    for ( unsigned i = 0 ; i < Height ; ++i ) {
      short dd = overlap - f->lspaces[i] ;
      // copio porzione di stringa
      if ( dd > 0 ) strcpy( lines[i]+charPosition-dd, f->rows[i]+f->lspaces[i] ) ;
      else          strcpy( lines[i]+charPosition,    f->rows[i]+overlap ) ;
    }
    charPosition += cw-overlap ;

    // aggiorno spazi liberi a destra
    std::copy( f -> rspaces, f -> rspaces + Height, rspaces ) ;
    return true ;
  }

  // ---------------------------------------------------------------------------

  static
  inline
  unsigned
  findClass( char c ) {
    if ( c == '|' ) return 1 ;
    if ( c == '/' || c == '\\' ) return 3 ;
    if ( c == '[' || c == ']'  ) return 4 ;
    if ( c == '{' || c == '}'  ) return 5 ;
    if ( c == '(' || c == ')'  ) return 6 ;
    return 0 ;
  }
  
  char
  Banner::smushingRules( char left, char right ) const {
    // rule 0: left blank use right
    if ( left == ' ' ) return right ;
    // rule 1: equal character smushing
    if ( left == right ) return left ;
    // rule 2: underscore smushing
    if ( left  == '_' && strchr( "|/\\[]{}()<>", right ) != NULL ) return right ;
    if ( right == '_' && strchr( "|/\\[]{}()<>", left )  != NULL ) return left  ;
    // rule 3: hierarchy smushing
    unsigned class_left  = findClass( left ) ;
    unsigned class_right = findClass( right ) ;
    if ( class_left > 0 && class_right > 0 ) {
      if      ( class_left < class_right ) return right ;
      else if ( class_left > class_right ) return left  ;
    }
    // rule 4: opposite pair smushing
    if ( left == '[' && right == ']' ) return '|' ;
    if ( left == ']' && right == '[' ) return '|' ;
    if ( left == '{' && right == '}' ) return '|' ;
    if ( left == '}' && right == '{' ) return '|' ;
    if ( left == '(' && right == ')' ) return '|' ;
    if ( left == ')' && right == '(' ) return '|' ;
    // rule 5: big X smushing
    if ( left == '/'  && right == '\\' ) return '|' ;
    if ( left == '\\' && right == '/'  ) return 'Y' ;
    if ( left == '>'  && right == '<'  ) return 'X' ;
    // rule 6: hardblack smushing
    // extra rules
    if ( left == '<'  && right == '|'  ) return '<' ;
    return '\0';
  }

  bool
  Banner::pushSmushed( unsigned c ) {
    FontFiglet const * f = characters + charToTable[c]  ;
    unsigned cw = charWidth[c] ;
    // calcolo overlapping
    short overlap = rspaces[0] + f->lspaces[0] ;
    for ( unsigned i = 1 ; i < Height ; ++i ) {
      short tmp = rspaces[i] + f->lspaces[i] ;
      if ( tmp < overlap ) overlap = tmp ;
    }
    
    // calcolo smush se possibile
    if ( charPosition > 0 ) {
      bool do_smush = true ;
      for ( unsigned i = 0 ; i < Height && do_smush ; ++i ) {
        short tmp = rspaces[i] + f->lspaces[i] ;
        if ( tmp == overlap ) {
          char * pline = lines[i]+charPosition-rspaces[i] ;
          smush[i] = smushingRules( pline[-1], f->rows[i][f->lspaces[i]] ) ;
          do_smush = smush[i] != '\0' ;
        }
      }
      if ( do_smush ) ++overlap ;
    }

    // controllo che il carattere stia nel buffer
    if ( charPosition+cw > maxLenght+overlap ) return false ;

    for ( unsigned i = 0 ; i < Height ; ++i ) {
      char * pline = lines[i]+charPosition ;
      short tmp = rspaces[i] + f->lspaces[i] ;
      if ( tmp < overlap ) {
        pline -= rspaces[i]+1 ;
        *pline++ = smush[i] ;
        strcpy( pline, f->rows[i]+f->lspaces[i]+1 ) ;
      } else {
        short dd = overlap - f->lspaces[i] ;
        // copio porzione di stringa
        if ( dd > 0 ) strcpy( pline-dd, f->rows[i]+f->lspaces[i] ) ;
        else          strcpy( pline,    f->rows[i]+overlap ) ;      
      }
    }
    charPosition += cw-overlap ;

    // aggiorno spazi liberi a destra
    std::copy( f -> rspaces, f -> rspaces + Height, rspaces ) ;
    return true ;
  }

  // ---------------------------------------------------------------------------

  void
  Banner::fillForPrint( char const message[] ) {
    init() ;
    switch ( printMode ) {
    case FIGLET_SMUSHED:
      for ( char const * p = message ; *p != '\0' ; ++p ) pushSmushed(*p) ;
      break ;
    case FIGLET_PACKED:
      for ( char const * p = message ; *p != '\0' ; ++p ) pushPacked(*p) ;
      break ;
    case FIGLET_FULLWIDTH:
      for ( char const * p = message ; *p != '\0' ; ++p ) pushFullWidth(*p) ;
      break ;
    case FIGLET_MONOSPACED:
      for ( char const * p = message ; *p != '\0' ; ++p ) pushMonospaced(*p) ;
      break ;
    }

    // replace Hardblank
    for ( unsigned i = 0 ; i < Height ; ++i ) {
      char *p = lines[i] ;
      do { if ( *p == Hardblank ) *p = ' ' ; } while ( *p++ != '\0' ) ;
    }
  }

  // ---------------------------------------------------------------------------

  unsigned
  Banner::print( char const message[], 
                 ostream & s, 
                 char const top[], 
                 char const bottom[]  ) {

    fillForPrint(message) ;

    for ( unsigned i = 0 ; i < strlen(top) ; ++i ) {
      for ( unsigned j = 0 ; j < charPosition ; ++j ) s << top[i] ;
      s << '\n' ;
    }   
    for ( unsigned i = 0 ; i < Height ; ++i ) s << lines[i] << '\n' ;
    for ( unsigned i = 0 ; i < strlen(bottom) ; ++i ) {
      for ( unsigned j = 0 ; j < charPosition ; ++j ) s << bottom[i] ;
      s << '\n' ;
    }
    return charPosition ;
  }

  // ---------------------------------------------------------------------------

  void
  Banner:: printFramed( char const message[],
                        ostream & s,
                        FrameMode fm ) {

    fillForPrint(message) ;

    switch ( fm ) {
    case FIGLET_SINGLE:
      s << '+' ;
      for ( unsigned j = 0 ; j < charPosition+2 ; ++j ) s << '-' ;
      s << "+\n" ;
      for ( unsigned i = 0 ; i < Height ; ++i ) s << "| " << lines[i] << " |\n" ;
      s << '+' ;
      for ( unsigned j = 0 ; j < charPosition+2 ; ++j ) s << '-' ;
      s << "+\n" ;
      break ;
    case FIGLET_DOUBLE:
      s << '@' ;
      for ( unsigned j = 0 ; j < charPosition+2 ; ++j ) s << '=' ;
      s << "@\n" ;
      for ( unsigned i = 0 ; i < Height ; ++i ) s << "# " << lines[i] << " #\n" ;
      s << '@' ;
      for ( unsigned j = 0 ; j < charPosition+2 ; ++j ) s << '=' ;
      s << "@\n" ;
      break ;
    }
  }


}

//
// eof: Figlet.cc
//
