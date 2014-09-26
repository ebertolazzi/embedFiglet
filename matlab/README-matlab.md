Figlet
===========

`Figlet` is a MATLAB command which implement a 
subset of Figlet capability (http://www.figlet.org).
No configuration or font file are necessary, moveover, 
the fonts are stored in structure initalized at compile time.

Details
-------

This library implement a subset of Figlet capability, i.e.
print large letters out of ordinary text
 
~~~~~~~~~~~~~
 _  _  _           _   _     _      
| |(_)| | __ ___  | |_| |__ (_) ___ 
| || || |/ // _ \ | __| '_ \| |/ __|
| || ||   <|  __/ | |_| | | | |\__ \
|_||_||_|\_\\___|  \__|_| |_|_||___/
                                    
~~~~~~~~~~~~~

No initialization files are necessary. The fonts are
hardware embedded in the library.

Usage
-----
To print a banner

~~~~~~~~~~~~~
>> Figlet('text');
 _               _   
| |_  ___ __  __| |_ 
| __|/ _ \\ \/ /| __|
| |_|  __/ >  < | |_ 
 \__|\___|/_/\_\ \__|
~~~~~~~~~~~~~

banner can be saved in a cell array of strings

~~~~~~~~~~~~~
>> A = Figlet('text in cells');
>> A

A = 

    ' _               _     _                    _ _      '
    '| |_  ___ __  __| |_  (_)_ __     ___  ___ | | | ___ '
    '| __|/ _ \\ \/ /| __| | | '_ \   / __|/ _ \| | |/ __|'
    '| |_|  __/ >  < | |_  | | | | | | (__|  __/| | |\__ \'
    ' \__|\___|/_/\_\ \__| |_|_| |_|  \___|\___||_|_||___/'
    '                                                     '
~~~~~~~~~~~~~

Fonts
-----

To select a font

~~~~~~~~~~~~~
  Figlet('font','name_of_the_font');
~~~~~~~~~~~~~

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
 
Printing mode
-------------

To select a printing mode

~~~~~~~~~~~~~
  Figlet('mode','name_of_printing_mode');
~~~~~~~~~~~~~

The available modes are:

 - 'smushed'    standard way of figlet print
 - 'packed'     letters are moved left but no overlapping are permitted
 - 'fullwidth'  letters are printed at width defined in the font
 - 'monospaced' letters are printed with equal width
 
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

Framing
-------

To frame a text

~~~~~~~~~~~~~
  Figlet('frame','name_of_frame_mode','text');
~~~~~~~~~~~~~

Only two framing are available:
 
 - 'single'  single frame around a string
 - 'double'  double frame around a string
 - 'none'    write lines on the top and bottom of the string
 
The effect are the following

`single` mode

~~~~~~~~~~~~~~~~~~
>> Figlet('frame','single','amazing')
+---------------------------------------------+
|                              _              |
|   __ _ _ __ ___   __ _  ____(_)_ __   __ _  |
|  / _` | '_ ` _ \ / _` ||_  /| | '_ \ / _` | |
| | (_| | | | | | | (_| | / / | | | | | (_| | |
|  \__,_|_| |_| |_|\__,_|/___||_|_| |_|\__, | |
|                                      |___/  |
+---------------------------------------------+
~~~~~~~~~~~~~~~~~~

`double` mode
 
~~~~~~~~~~~~~~~~~~
>> Figlet('frame','double','stories')
@==================================@
#       _              _           #
#  ___ | |_  ___  _ __(_) ___ ___  #
# / __|| __|/ _ \| '__| |/ _ Y __| #
# \__ \| |_| (_) | |  | |  __|__ \ #
# |___/ \__|\___/|_|  |_|\___|___/ #
#                                  #
@==================================@
~~~~~~~~~~~~~~~~~~

`none` mode

~~~~~~~~~~~~~~~~~~
>> Figlet('frame','none','two lines','=','-.')
===========================================
 _                     _  _                
| |_ __      __ ___   | |(_)_ __   ___ ___ 
| __|\ \ /\ / // _ \  | || | '_ \ / _ Y __|
| |_  \ V  V /| (_) | | || | | | |  __|__ \
 \__|  \_/\_/  \___/  |_||_|_| |_|\___|___/
                                           
-------------------------------------------
...........................................
~~~~~~~~~~~~~~~~~~

* * *

Enrico Bertolazzi<br>
Dipartimento di Ingegneria Industriale<br>
Universita` degli Studi di Trento<br>
