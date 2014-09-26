/****************************************************************************\
  Copyright (c) Enrico Bertolazzi 2014
  All Rights Reserved.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation;

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
\****************************************************************************/

#include "Figlet.hh"
#include "mex.h"

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#define ERROR(MSG)                   \
  std::ostringstream ost ;           \
  ost << "Figlet: " << MSG << '\n' ; \
  mexErrMsgTxt(ost.str().c_str()) ;  \

#define INFO_MESSAGE \
"%%======================================================================%%\n" \
"%%  Figlet: Write banner or setup parameters                            %%\n" \
"%%                                                                      %%\n" \
"%%  USAGE:                                                              %%\n" \
"%%    1) Figlet() ;                                                     %%\n" \
"%%    2) Figlet('') ;                                                   %%\n" \
"%%    3) Figlet( command, parameter ) ;                                 %%\n" \
"%%    4) banner = Figlet( msg ) ;                                       %%\n" \
"%%    5) banner = Figlet( 'frame', parameter, msg [, top, bottom] ) ;   %%\n" \
"%%                                                                      %%\n" \
"%%  mode 1: Print this message                                          %%\n" \
"%%                                                                      %%\n" \
"%%  mode 2: Reset Figlet to default font and mode                       %%\n" \
"%%                                                                      %%\n" \
"%%  mode 3: Change Figlet output mode                                   %%\n" \
"%%                                                                      %%\n" \
"%%  command:   'font' change font used                                  %%\n" \
"%%  parameter: `big`, `larry3d`, `script`, `standard`, `banner`,        %%\n" \
"%%             `doom`, `mini`, `small`, `straight`                      %%\n" \
"%%                                                                      %%\n" \
"%%  command:   'mode' change mode font is printed                       %%\n" \
"%%  parameter: `smushed`, `packed`, `fullwidth`, `monospaced`           %%\n" \
"%%                                                                      %%\n" \
"%%  mode 4: Convert string `msg` to a banner stored in a cell array     %%\n" \
"%%          of strings `banner`. If `banner` is missing print result    %%\n" \
"%%          to command window                                           %%\n" \
"%%                                                                      %%\n" \
"%%  mode 5: Convert string `msg` to a banner stored in a cell array     %%\n" \
"%%          of strings `banner`. If `banner` is missing print result    %%\n" \
"%%          to command window.                                          %%\n" \
"%%                                                                      %%\n" \
"%%          parameter: `none`, `single`, `double`                       %%\n" \
"%%                                                                      %%\n" \
"%%          if parameter == `none` then strings top, bottom must        %%\n" \
"%%          be set and are used to set top and bottom line              %%\n" \
"%%          of the banner                                               %%\n" \
"%%                                                                      %%\n" \
"%%                                                                      %%\n" \
"%%======================================================================%%\n" \
"%%                                                                      %%\n" \
"%%  Autor: Enrico Bertolazzi                                            %%\n" \
"%%         Department of Industrial Engineering                         %%\n" \
"%%         University of Trento                                         %%\n" \
"%%         enrico.bertolazzi@unitn.it                                   %%\n" \
"%%                                                                      %%\n" \
"%%======================================================================%%\n"

#define arg_command   prhs[0]
#define arg_parameter prhs[1]
#define arg_msg       prhs[2]
#define arg_top       prhs[3]
#define arg_bottom    prhs[4]
#define arg_output    plhs[0]

extern "C"
void
mexFunction( int nlhs, mxArray       *plhs[],
             int nrhs, mxArray const *prhs[] ) {

  static Figlet::PrintMode printMode = Figlet::FIGLET_SMUSHED ;
  static Figlet::Banner *    pBanner = &Figlet::standard ;


  // Check for proper number of arguments, etc
  if ( nrhs == 0 ) {
    mexPrintf( INFO_MESSAGE ) ;
    return ;
  }

  // check arg_command be a string
  if ( ! (mxIsChar(arg_command) && mxGetM(arg_command) == 1) ) {
    if ( mxIsChar(arg_command) ) {
      printMode = Figlet::FIGLET_SMUSHED ;
      pBanner   = &Figlet::standard ;
    } else {
      mexErrMsgTxt("First argument must be a string") ;
    }
  }
  
  if ( nrhs > 1 && ! (mxIsChar(arg_parameter) && mxGetM(arg_parameter) == 1) )
    mexErrMsgTxt("Second argument must be a string") ;
  
  mwSize buflen = mxGetN(arg_command)*sizeof(mxChar)+1;
  #ifdef _MSC_VER
  char * command = (char*)alloca( buflen*sizeof(char) ) ;
  #else
  char command[buflen] ;
  #endif
  mxGetString(arg_command, command, buflen) ;

  std::ostringstream ost ;
  
  if ( nrhs == 2 ) {
    buflen = mxGetN(arg_parameter)*sizeof(char)+1;
    #ifdef _MSC_VER
    char * parameter = (char*)alloca( buflen*sizeof(char) ) ;
    #else
    char parameter[buflen] ;
    #endif
    mxGetString(arg_parameter, parameter, buflen) ;

    if ( 0 == strcmp(command,"font") ) {
      if      ( 0 == strcmp(parameter,"big")      ) pBanner = &Figlet::big ;
      else if ( 0 == strcmp(parameter,"banner")   ) pBanner = &Figlet::banner ;
      else if ( 0 == strcmp(parameter,"doom")     ) pBanner = &Figlet::doom ;
      else if ( 0 == strcmp(parameter,"larry3d")  ) pBanner = &Figlet::larry3d ;
      else if ( 0 == strcmp(parameter,"mini")     ) pBanner = &Figlet::mini ;
      else if ( 0 == strcmp(parameter,"script")   ) pBanner = &Figlet::script ;
      else if ( 0 == strcmp(parameter,"small")    ) pBanner = &Figlet::small ;
      else if ( 0 == strcmp(parameter,"standard") ) pBanner = &Figlet::standard ;
      else if ( 0 == strcmp(parameter,"straight") ) pBanner = &Figlet::straight ;
      else {
        ERROR( "Unknown font: `" << parameter << "`" ) ;
      }
    } else if ( 0 == strcmp(command,"mode") ) {
      if      ( 0 == strcmp(parameter,"smushed")    ) printMode = Figlet::FIGLET_SMUSHED ;
      else if ( 0 == strcmp(parameter,"packed")     ) printMode = Figlet::FIGLET_PACKED ;
      else if ( 0 == strcmp(parameter,"fullwidth")  ) printMode = Figlet::FIGLET_FULLWIDTH ;
      else if ( 0 == strcmp(parameter,"monospaced") ) printMode = Figlet::FIGLET_MONOSPACED ;
      else {
        ERROR( "Unknown mode: `" << parameter << "`" ) ;
      }
    } else {
      ERROR( "Unknown command: `" << command << "`" ) ;
    }

  } if ( nrhs > 2 ) {

    buflen = mxGetN(arg_parameter)*sizeof(mxChar)+1;
    #ifdef _MSC_VER
    char * parameter = (char*)alloca( buflen*sizeof(char) ) ;
    #else
    char parameter[buflen] ;
    #endif
    mxGetString(arg_parameter, parameter, buflen) ;

    buflen = mxGetN(arg_msg)*sizeof(mxChar)+1;
    #ifdef _MSC_VER
    char * msg = (char*)alloca( buflen*sizeof(char) ) ;
    #else
    char msg[buflen] ;
    #endif
    mxGetString(arg_msg, msg, buflen) ;

    switch ( printMode ) {
      case Figlet::FIGLET_SMUSHED:    pBanner->setSmushed()    ; break ;
      case Figlet::FIGLET_PACKED:     pBanner->setPacked()     ; break ;
      case Figlet::FIGLET_FULLWIDTH:  pBanner->setFullWidth()  ; break ;
      case Figlet::FIGLET_MONOSPACED: pBanner->setMonospaced() ; break ;
      break ;
    }

    if ( 0 == strcmp(command,"frame") ) {
      if ( 0 == strcmp(parameter,"none")   ) {
      
        if ( nrhs != 5 ) {
          ERROR( "With Figlet('frame','none',...) expect 5 parameters, found " << nrhs ) ;
        }

        buflen = mxGetN(arg_top)*sizeof(mxChar)+1;
        #ifdef _MSC_VER
        char * top = (char*)alloca( buflen*sizeof(char) ) ;
        #else
        char top[buflen] ;
        #endif
        mxGetString(arg_top, top, buflen) ;

        buflen = mxGetN(arg_bottom)*sizeof(mxChar)+1;
        #ifdef _MSC_VER
        char * bottom = (char*)alloca( buflen*sizeof(char) ) ;
        #else
        char bottom[buflen] ;
        #endif
        mxGetString(arg_bottom, bottom, buflen) ;
      
        pBanner->print( msg, ost, top, bottom ) ;
      } else if ( 0 == strcmp(parameter,"single") ) {
        pBanner->printFramed( msg, ost, Figlet::FIGLET_SINGLE ) ;
      } else if ( 0 == strcmp(parameter,"double") ) {
        pBanner->printFramed( msg, ost, Figlet::FIGLET_DOUBLE ) ;
      } else {
        ERROR( "Unknown frame mode: `" << command << "`" ) ;
      }
    } else {
      ERROR( "Unknown command: `" << command << "`" ) ;
    }

  } else {
    switch ( printMode ) {
      case Figlet::FIGLET_SMUSHED:    pBanner->setSmushed()    ; break ;
      case Figlet::FIGLET_PACKED:     pBanner->setPacked()     ; break ;
      case Figlet::FIGLET_FULLWIDTH:  pBanner->setFullWidth()  ; break ;
      case Figlet::FIGLET_MONOSPACED: pBanner->setMonospaced() ; break ;
      break ;
    }
    pBanner->print( command, ost ) ;
  }

  if ( nrhs != 2 ) {
    if ( nlhs == 0 ) {
      mexPrintf(ost.str().c_str()) ;
    } else {
      std::string              line ;
      std::stringstream        stream(ost.str());
      std::vector<std::string> lines ;
      while( getline(stream, line, '\n') ) lines.push_back( line ) ;
    
      arg_output = mxCreateCellMatrix( lines.size(), 1 ) ;
      for ( mwIndex i = 0 ; i < lines.size() ; ++i ) {
        mxSetCell(arg_output, i, mxCreateString(lines[i].c_str()) ) ;
      }
    }
  }
}
