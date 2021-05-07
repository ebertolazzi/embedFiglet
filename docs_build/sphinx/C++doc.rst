C++ usage
=========

This library implement a subset of Figlet capability, i.e. print large
letters out of ordinary text

.. code-block:: text

      _ _ _          _   _     _
     | (_) | _____  | |_| |__ (_)___
     | | | |/ / _ \ | __| '_ \| / __|
     | | |   <  __/ | |_| | | | \__ \_
     |_|_|_|\_\___|  \__|_| |_|_|___(_)


Differently of standard FIGlet command (http://www.figlet.org/) this
print can be done inside a user program using run time generated string
as follows

.. code-block:: cpp

   #include "Figlet.hh"
   #include <sstream>
   using namespace std;

   int
   main() {
     Figlet::standard.print("Fractions");
     for ( int i = 2; i <= 4; ++i ) {
       ostringstream ss;
       ss << "5/" << i << " = " << 5.0/i;
       Figlet::small.print(ss.str().c_str());
     }
     cout << "ALL DONE!\n";
     return 0;
   }

which output is the following

.. code-block:: text

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

No initialization files are necessary. The fonts are hardware embedded
in the library.

.. list-table:: Available fonts

  * -  banner
    -  big
    -  doom
  * -  larry3d
    -  mini
    -  script
  * -  small
    -  standard
    -  straight

A simple ruby script permits to convert figlet .flf files to structures
which can be embedded in the library.

Available printing mode
-----------------------

Only four mode of print the same string:

.. list-table:: Printing mode

   * - FIGLET_SMUSHED
     - standard way of figlet print
   * - FIGLET_PACKED
     - letters are moved left but no overlapping are permitted
   * - FIGLET_FULLWIDTH
     - letters are printed at width defined in the font
   * - FIGLET_MONOSPACED
     - letters are printed with equal width

The effect are the following

.. code-block:: text

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

Available framing mode
----------------------

Only two framing are available:

.. list-table:: Framing mode

  * - FIGLET_SINGLE
    - single frame around a string
  * - FIGLET_DOUBLE
    - double frame around a string

The effect are the following


.. code-block:: text

     Figlet::small.printFramed("SINGLE",cout,Figlet::FIGLET_SINGLE);
     +------------------------------+
     |  ___ ___ _  _  ___ _    ___  |
     | / __|_ _| \| |/ __| |  | __| |
     | \__ \| || .` | (_ | |__| _|  |
     | |___/___|_|\_|\___|____|___| |
     |                              |
     +------------------------------+

and


.. code-block:: text

     Figlet::small.printFramed("DOUBLE",cout,Figlet::FIGLET_DOUBLE);
     @=================================@
     #  ___   ___  _   _ ___ _    ___  #
     # |   \ / _ \| | | | _ ) |  | __| #
     # | |) | (_) | |_| | _ \ |__| _|  #
     # |___/ \___/ \___/|___/____|___| #
     #                                 #
     @=================================@

Compile and test
----------------

Edit makefile file to match compiler of your OS and do:

.. code-block:: bash

  make

To run the test

.. code-block:: bash

  make run

or use rakefile


.. code-block:: bash

  # on linux os
  rake build_linux

  # on mac
  rake build_osx

  # on windows
  rake build_win
