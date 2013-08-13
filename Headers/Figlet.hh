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

///
/// file: Figlet.hh
///
   
/// http://ruletheweb.co.uk/figlet/

#ifndef FIGLET_HH
#define FIGLET_HH

#include <iostream>
#include <stdint.h>

//! Collects structures and classes for banner generation
namespace Figlet {

  using namespace std ;
  
  static unsigned const maxHeight    = 10  ; //!< maximum allowed (lines) height of the font 
  static unsigned const maxLenght    = 256 ; //!< maximum number of characters x line of the banner
  static unsigned const maxTableSize = 256 ; //!< maximum number of allowed character x font

  //! Structure used to store a charater of the font
  typedef struct {
    short        nchar              ; //!< character (ascii) number
    uint8_t      lspaces[maxHeight] ; //!< number of spaces on the left side x line 
    uint8_t      rspaces[maxHeight] ; //!< number of spaces on the right side x line
    char const * rows[maxHeight]    ; //!< charater definition
  } FontFiglet ;

  typedef enum { SMUSHED=0, PACKED, FULLWIDTH, MONOSPACED } PrintMode ;
  typedef enum { SINGLE=0, DOUBLE } FrameMode ;

  //! Class implementing the "figlet" algorithm
  class Banner {

    FontFiglet const * characters ; //!< pointer to the font structures
    char       const   Hardblank  ; //!< character used for the "hardblank" in the font definition
    unsigned   const   Height     ; //!< vertical dimension (lines) of the font
    unsigned           Width      ; //!< width of the charater M used in Monospaced print
    unsigned   const   FontMaxLen ; //!< maximum width of the letters of the font
    unsigned   const   FontSize   ; //!< total number of characters in the font
    uint8_t            rspaces[maxHeight]          ; //!< extra right spaces availables after the last insertion
    char               lines[maxHeight][maxLenght] ; //!< lines buffer 
    char               smush[maxHeight]            ; //!< charater used in the "smushing" algorithm
    unsigned short     charToTable[maxTableSize]   ; //!< map ascii character to font structure
    unsigned short     charWidth[maxTableSize]     ; //!< size width of each charater of the font
    unsigned           charPosition                ; //!< position of last inserted character

    PrintMode          printMode ; //!< the type of printing mode used

    Banner const & operator = ( Banner const & ) ;  
    Banner( Banner const & ) ;
    
    //! evaluate smushing rules for 2 characters, return '\0' if no rules apply
    char smushingRules( char left, char right ) const ;

    bool pushMonospaced( unsigned c ) ;
    bool pushFullWidth( unsigned c ) ;
    bool pushPacked( unsigned c ) ;
    bool pushSmushed( unsigned c ) ;
    void fillForPrint( char const message[] ) ;

  public:

    explicit Banner( FontFiglet const * characters,
                     char               Hardblank,
                     unsigned           Height,
                     unsigned           FontMaxLen,
                     unsigned           FontSize ) ;  
    void init() ;
    
    void setMonospaced() { printMode = MONOSPACED ; }
    void setFullWidth()  { printMode = FULLWIDTH  ; }
    void setPacked()     { printMode = PACKED     ; }
    void setSmushed()    { printMode = SMUSHED    ; }

    unsigned print( char const message[],
                    ostream & s = cout,
                    char const top[] = "",
                    char const bottom[] = "" ) ;

    void printFramed( char const message[],
                      ostream & s = cout,
                      FrameMode fm = SINGLE ) ;
  } ;

  extern Banner big ;
  extern Banner banner ;
  extern Banner doom ;
  extern Banner larry3d ;
  extern Banner mini ;
  extern Banner script ;
  extern Banner small ;
  extern Banner standard ;
  extern Banner straight ;

}

#endif

///
/// eof: Figlet.hh
///
