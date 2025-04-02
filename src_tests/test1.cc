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
 |      Università degli Studi di Trento                                    |
 |      email: enrico.bertolazzi@unitn.it                                   |
 |                                                                          |
\*--------------------------------------------------------------------------*/

#include "Figlet.hh"

using namespace std;
 
static char const msg1[] = "Converged \"Yes/NO\"";
static char const msg2[] = "#$%@ pippo *&()";
static char const msg3[] = "Precipitevolissimevolmente";

#define DO_TEST(FONT) \
Figlet::FONT.print(msg1); \
Figlet::FONT.setPacked(); \
Figlet::FONT.print(msg1); \
Figlet::FONT.printFramed(msg2); \
Figlet::FONT.printFramed(msg3,cout,Figlet::FIGLET_DOUBLE)

int
main() {

  Figlet::standard.print("like this.");

  DO_TEST(banner);
  DO_TEST(big);
  DO_TEST(doom);
  DO_TEST(larry3d);
  DO_TEST(mini);
  DO_TEST(script);
  DO_TEST(small);
  DO_TEST(standard);
  DO_TEST(straight);

  cout << "ALL DONE!\n";
}
