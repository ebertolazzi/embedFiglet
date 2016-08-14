/*--------------------------------------------------------------------------*\
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
/*
Copyright (c) 2014, Enrico Bertolazzi 
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are 
met:

    * Redistributions of source code must retain the above copyright 
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright 
      notice, this list of conditions and the following disclaimer in 
      the documentation and/or other materials provided with the distribution
      
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
POSSIBILITY OF SUCH DAMAGE.
*/
          
//
// file: Figlet.hh
//

// check for bugged compiler
#ifdef _MSC_VER
  #define EMBED_FIGLET_USE_VISUAL_STUDIO
#endif

// http://ruletheweb.co.uk/figlet/

/*!
  \mainpage  Embeddable Figlet Library
  \author    Enrico Bertolazzi (enrico.bertolazzi@unitn.it), homepage: http://www.ing.unitn.it/~bertolaz
  \version   1.0.2
  \date      2013
 
  \details

  This library available at
  
  - https://github.com/ebertolazzi/embedFiglet
  - https://bitbucket.org/ebertolazzi/embedfiglet
  
  implement a subset of Figlet capability, i.e.
  print large letters out of ordinary text
 
  ~~~~~~~~~~~~~
   _ _ _          _   _     _
  | (_) | _____  | |_| |__ (_)___
  | | | |/ / _ \ | __| '_ \| / __|
  | | |   <  __/ | |_| | | | \__ \_
  |_|_|_|\_\___|  \__|_| |_|_|___(_)
 
  ~~~~~~~~~~~~~
 
  Differently of standard FIGlet command (http://www.figlet.org/)
  this print can be done inside a user program using run time
  generated string as follows
  
  ~~~~~~~~~~~~~{.c++}
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
    cout << "ALL DONE!\n" ;
    return 0;
  }
  ~~~~~~~~~~~~~
  
  which output is the following
  
  ~~~~~~~~~~~~~
   _____               _   _
  |  ___| __ __ _  ___| |_(_) ___  _ __  ___
  | |_ | '__/ _` |/ __| __| |/ _ \| '_ \/ __|
  |  _|| | | (_| | (__| |_| | (_) | | | \__ \
  |_|  |_|  \__,_|\___|\__|_|\___/|_| |_|___/
                                           
   ___   _____         ___   ___   
  | __| / /_  )  ___  |_  ) | __|
  |__ \/ / / /  |___|  / / _|__ \
  |___/_/ /___| |___| /___(_)___/
                               
   ___   ______        _    __  __  __  ______
  | __| / /__ /  ___  / |  / / / / / / / /__  |
  |__ \/ / |_ \ |___| | |_/ _ Y _ Y _ Y _ \/ /
  |___/_/ |___/ |___| |_(_)___|___|___|___/_/
                                             
   ___   ___ _          _   ___ ___
  | __| / / | |   ___  / | |_  ) __|
  |__ \/ /|_  _| |___| | |_ / /|__ \
  |___/_/   |_|  |___| |_(_)___|___/
  ~~~~~~~~~~~~~

  No initialization files are necessary. The fonts are
  hardware embedded in the library. 
  The available fonts are:

  - banner
  - big
  - doom
  - larry3d
  - mini
  - script
  - small
  - standard
  - straight
  
  A simple ruby script permits to convert figlet .flf files
  to structures which can be embedded in the library.
 
  - \ref printmode
  - \ref framemode

 */

/*!
  \page printmode Available printing mode
 
  Only four mode of print the same string:

    - FIGLET_SMUSHED     standard way of figlet print
    - FIGLET_PACKED      letters are moved left but no overlapping are permitted
    - FIGLET_FULLWIDTH   letters are printed at width defined in the font
    - FIGLET_MONOSPACED  letters are printed with equal width

  The effect are the following
  ~~~~~~~~~~~~~~~~~~
   ____                      _              _
  / ___| _ __ ___  _   _ ___| |__   ___  __| |
  \___ \| '_ ` _ \| | | / __| '_ \ / _ \/ _` |
   ___) | | | | | | |_| \__ \ | | |  __/ (_| |
  |____/|_| |_| |_|\__,_|___/_| |_|\___|\__,_|
   ____               _              _
  |  _ \  __ _   ___ | | __ ___   __| |
  | |_) |/ _` | / __|| |/ // _ \ / _` |
  |  __/| (_| || (__ |   <|  __/| (_| |
  |_|    \__,_| \___||_|\_\\___| \__,_|
   _____           _   _  __        __  _       _   _     _
  |  ___|  _   _  | | | | \ \      / / (_)   __| | | |_  | |__
  | |_    | | | | | | | |  \ \ /\ / /  | |  / _` | | __| | '_ \
  |  _|   | |_| | | | | |   \ V  V /   | | | (_| | | |_  | | | |
  |_|      \__,_| |_| |_|    \_/\_/    |_|  \__,_|  \__| |_| |_|
   __  __                                                                       _
  |  \/  |   ___    _ __     ___     ___    _ __     __ _     ___     ___    __| |
  | |\/| |  / _ \  | '_ \   / _ \   / __|  | '_ \   / _` |   / __|   / _ \  / _` |
  | |  | | | (_) | | | | | | (_) |  \__ \  | |_) | | (_| |  | (__   |  __/ | (_| |
  |_|  |_|  \___/  |_| |_|  \___/   |___/  | .__/   \__,_|   \___|   \___|  \__,_|
                                           |_|
  ~~~~~~~~~~~~~~~~~~
 */

/*!
  \page framemode Available framing mode
 
  Only two framing are available:
 
   - FIGLET_SINGLE  single frame around a string
   - FIGLET_DOUBLE  double frame around a string
 
  The effect are the following

  ~~~~~~~~~~~~~~~~~~
  Figlet::small.printFramed("SINGLE",cout,Figlet::FIGLET_SINGLE);
  +------------------------------+
  |  ___ ___ _  _  ___ _    ___  |
  | / __|_ _| \| |/ __| |  | __| |
  | \__ \| || .` | (_ | |__| _|  |
  | |___/___|_|\_|\___|____|___| |
  |                              |
  +------------------------------+
  ~~~~~~~~~~~~~~~~~~
  and
  ~~~~~~~~~~~~~~~~~~
  Figlet::small.printFramed("DOUBLE",cout,Figlet::FIGLET_DOUBLE);
  @=================================@
  #  ___   ___  _   _ ___ _    ___  #
  # |   \ / _ \| | | | _ ) |  | __| #
  # | |) | (_) | |_| | _ \ |__| _|  #
  # |___/ \___/ \___/|___/____|___| #
  #                                 #
  @=================================@
  ~~~~~~~~~~~~~~~~~~
 */

#ifndef FIGLET_HH
#define FIGLET_HH

#include <iostream>
#include <stdint.h>

/*! \brief
 * Collects structures and classes for banner generation
 */
namespace Figlet {

  using namespace std ;
  
  static unsigned const maxHeight    = 10  ; //!< maximum allowed (lines) height of the font 
  static unsigned const maxLenght    = 256 ; //!< maximum number of characters x line of the banner
  static unsigned const maxTableSize = 256 ; //!< maximum number of allowed character x font

  //! Structure used to store a charater of the font
  typedef struct {
    unsigned short nchar              ; //!< character (ascii) number
    uint8_t        lspaces[maxHeight] ; //!< number of spaces on the left side x line
    uint8_t        rspaces[maxHeight] ; //!< number of spaces on the right side x line
    char const *   rows[maxHeight]    ; //!< charater definition
  } FontFiglet ;

  //! Available way to print a string, see \ref printmode
  typedef enum { FIGLET_SMUSHED=0,
                 FIGLET_PACKED,
                 FIGLET_FULLWIDTH,
                 FIGLET_MONOSPACED } PrintMode ;

  //! Available way to print a frames string, see \ref framemode
  typedef enum { FIGLET_SINGLE=0, FIGLET_DOUBLE } FrameMode ;

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

    //! Constructor of `Banner` class
    /*!
       \param characters none
       \param Hardblank  none
       \param Height     none
       \param FontMaxLen none
       \param FontSize   none
     */
    explicit
    Banner( FontFiglet const * characters,
            char               Hardblank,
            unsigned           Height,
            unsigned           FontMaxLen,
            unsigned           FontSize ) ;

    //! initialize Banner class
    void init() ;

    //! Set print mode to `monospaced`, see \ref printmode
    void setMonospaced() { printMode = FIGLET_MONOSPACED ; }

    //! Set print mode to `full width`, see \ref printmode
    void setFullWidth() { printMode = FIGLET_FULLWIDTH  ; }

    //! Set print mode to `packed`, see \ref printmode
    void setPacked() { printMode = FIGLET_PACKED     ; }

    //! Set print mode to `smushed` (figlet default), see \ref printmode
    void setSmushed() { printMode = FIGLET_SMUSHED    ; }

    //! Print large letters of string `message` on stream `s`, see \ref printmode
    unsigned
    print( char const message[],
           std::basic_ostream<char> & s = cout,
           char const top[] = "",
           char const bottom[] = "" ) ;

    //! \ref framemode
    void
    printFramed( char const message[],
                 std::basic_ostream<char> & s = cout,
                 FrameMode fm = FIGLET_SINGLE ) ;
  } ;

  extern Banner big      ; //!< instance `Banner` class using figlet font `big`
  extern Banner banner   ; //!< instance `Banner` class using figlet font `banner`
  extern Banner doom     ; //!< instance `Banner` class using figlet font `doom`
  extern Banner larry3d  ; //!< instance `Banner` class using figlet font `larry3d`
  extern Banner mini     ; //!< instance `Banner` class using figlet font `mini`
  extern Banner script   ; //!< instance `Banner` class using figlet font `script`
  extern Banner small    ; //!< instance `Banner` class using figlet font `small`
  extern Banner standard ; //!< instance `Banner` class using figlet font `standard`
  extern Banner straight ; //!< instance `Banner` class using figlet font `straight`

}

#endif

//
// eof: Figlet.hh
//
