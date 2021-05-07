MATLAB toolbox
==============

This library implement a subset of Figlet capability, i.e. print large
letters out of ordinary text

.. code-block:: none

    _  _  _           _   _     _
   | |(_)| | __ ___  | |_| |__ (_) ___
   | || || |/ // _ \ | __| '_ \| |/ __|
   | || ||   <|  __/ | |_| | | | |\__ \
   |_||_||_|\_\\___|  \__|_| |_|_||___/


No initialization files are necessary. The fonts are hardware embedded
in the library.

Installation
------------

Install the toolbox that you find
`here <https://github.com/ebertolazzi/embedFiglet/releases>`__.
After the installation run ``CompileFiglet`` on the Matlab console
to compile the *mex* interface.

Usage
-----

To print a banner

.. code-block:: matlab

   >> Figlet('text');
    _               _
   | |_  ___ __  __| |_
   | __|/ _ \\ \/ /| __|
   | |_|  __/ >  < | |_
    \__|\___|/_/\_\ \__|

banner can be saved in a cell array of strings

.. code-block:: matlab

   >> A = Figlet('text in cells');

so that

.. code-block:: text

   >> A
   A =

       ' _               _     _                    _ _      '
       '| |_  ___ __  __| |_  (_)_ __     ___  ___ | | | ___ '
       '| __|/ _ \\ \/ /| __| | | '_ \   / __|/ _ \| | |/ __|'
       '| |_|  __/ >  < | |_  | | | | | | (__|  __/| | |\__ \'
       ' \__|\___|/_/\_\ \__| |_|_| |_|  \___|\___||_|_||___/'
       '                                                     '

Fonts
-----

To select a font

.. code-block:: matlab

     Figlet('font','name_of_the_font');


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

Printing mode
-------------

To select a printing mode

.. code-block:: matlab

     Figlet('mode','name_of_printing_mode');

The available modes are:

-  ‘smushed’ standard way of figlet print
-  ‘packed’ letters are moved left but no overlapping are permitted
-  ‘fullwidth’ letters are printed at width defined in the font
-  ‘monospaced’ letters are printed with equal width

The effect are the following

.. code-block:: none

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

Framing
-------

To frame a text

.. code-block:: matlab

     Figlet('frame','name_of_frame_mode','text');

Only two framing are available:

.. list-table:: framing mode
   :header-rows: 1

  * -  single
    -  double
    -  none

  * -  single frame around a string
    -  double frame around a string
    -  write lines on the top and bottom of the string

The effect are the following

**single** mode

.. code-block:: matlab

   >> Figlet('frame','single','amazing')
   +---------------------------------------------+
   |                              _              |
   |   __ _ _ __ ___   __ _  ____(_)_ __   __ _  |
   |  / _` | '_ ` _ \ / _` ||_  /| | '_ \ / _` | |
   | | (_| | | | | | | (_| | / / | | | | | (_| | |
   |  \__,_|_| |_| |_|\__,_|/___||_|_| |_|\__, | |
   |                                      |___/  |
   +---------------------------------------------+

**double** mode

.. code-block:: none

   >> Figlet('frame','double','stories')
   @==================================@
   #       _              _           #
   #  ___ | |_  ___  _ __(_) ___ ___  #
   # / __|| __|/ _ \| '__| |/ _ Y __| #
   # \__ \| |_| (_) | |  | |  __|__ \ #
   # |___/ \__|\___/|_|  |_|\___|___/ #
   #                                  #
   @==================================@

**none** mode

.. code-block:: none

   >> Figlet('frame','none','two lines','=','-.')
   ===========================================
    _                     _  _
   | |_ __      __ ___   | |(_)_ __   ___ ___
   | __|\ \ /\ / // _ \  | || | '_ \ / _ Y __|
   | |_  \ V  V /| (_) | | || | | | |  __|__ \
    \__|  \_/\_/  \___/  |_||_|_| |_|\___|___/

   -------------------------------------------
   ...........................................
