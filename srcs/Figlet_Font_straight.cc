// Converted FLF file: original_fonts/straight.flf
#include "Figlet.hh"

namespace Figlet {

  //! \cond NODOC

  static char     const Hardblank  = '$' ;
  static unsigned const FontHeight = 4 ;
  static unsigned const FontMaxLen = 10 ;
  static FontFiglet characters[] = {

    // letter "space"
    { 32,
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 },
      {
        "$$",
        "$$",
        "$$",
        "$$"
      }
    },

    // letter N. 33 " ! "
    { 33,
      { 2, 0, 0, 2 },
      { 2, 1, 1, 2 },
      {
        "  ",
        "| ",
        ". ",
        "  "
      }
    },

    // letter N. 34 " " "
    { 34,
      { 0, 0, 3, 3 },
      { 1, 1, 3, 3 },
      {
        "// ",
        "$$ ",
        "   ",
        "   "
      }
    },

    // letter N. 35 " # "
    { 35,
      { 6, 0, 0, 6 },
      { 6, 1, 1, 6 },
      {
        "      ",
        "_|_|_ ",
        "-|-|- ",
        "      "
      }
    },

    // letter N. 36 " $ "
    { 36,
      { 1, 0, 0, 1 },
      { 1, 1, 1, 2 },
      {
        " ||_ ",
        "(||$ ",
        "_||) ",
        " ||  "
      }
    },

    // letter N. 37 " % "
    { 37,
      { 3, 0, 0, 3 },
      { 3, 1, 1, 3 },
      {
        "   ",
        "0/ ",
        "/0 ",
        "   "
      }
    },

    // letter N. 38 " & "
    { 38,
      { 4, 0, 0, 4 },
      { 4, 1, 2, 4 },
      {
        "    ",
        "()/ ",
        "(X  ",
        "    "
      }
    },

    // letter N. 39 " ' "
    { 39,
      { 0, 0, 0, 2 },
      { 1, 1, 1, 2 },
      {
        "/ ",
        "$ ",
        "$ ",
        "  "
      }
    },

    // letter N. 40 " ( "
    { 40,
      { 0, 0, 0, 3 },
      { 1, 1, 1, 3 },
      {
        "$/ ",
        "($ ",
        "$\\ ",
        "   "
      }
    },

    // letter N. 41 " ) "
    { 41,
      { 0, 0, 0, 3 },
      { 1, 1, 1, 3 },
      {
        "\\$ ",
        "$) ",
        "/$ ",
        "   "
      }
    },

    // letter N. 42 " * "
    { 42,
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 },
      {
        "$  $",
        "$\\/$",
        "$/\\$",
        "$  $"
      }
    },

    // letter N. 43 " + "
    { 43,
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 },
      {
        "$   $",
        "$_|_$",
        "$ | $",
        "$   $"
      }
    },

    // letter N. 44 " , "
    { 44,
      { 1, 0, 0, 1 },
      { 0, 0, 0, 0 },
      {
        " $",
        "$$",
        ",$",
        " $"
      }
    },

    // letter N. 45 " - "
    { 45,
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 },
      {
        "$  $",
        "$__$",
        "$  $",
        "$  $"
      }
    },

    // letter N. 46 " . "
    { 46,
      { 2, 0, 0, 2 },
      { 0, 0, 0, 0 },
      {
        "  $",
        "$ $",
        ". $",
        "  $"
      }
    },

    // letter N. 47 " / "
    { 47,
      { 3, 0, 0, 3 },
      { 3, 1, 1, 3 },
      {
        "   ",
        "$/ ",
        "/$ ",
        "   "
      }
    },

    // letter N. 48 " 0 "
    { 48,
      { 0, 0, 0, 0 },
      { 2, 1, 1, 5 },
      {
        "$ __  ",
        "$/  \\ ",
        "$\\__/ ",
        "$     "
      }
    },

    // letter N. 49 " 1 "
    { 49,
      { 0, 0, 0, 0 },
      { 3, 1, 1, 3 },
      {
        "$   ",
        "$/| ",
        "$ | ",
        "$   "
      }
    },

    // letter N. 50 " 2 "
    { 50,
      { 0, 0, 0, 0 },
      { 2, 1, 1, 4 },
      {
        "$__  ",
        "$ _) ",
        "$/__ ",
        "$    "
      }
    },

    // letter N. 51 " 3 "
    { 51,
      { 0, 0, 0, 0 },
      { 2, 1, 1, 4 },
      {
        "$__  ",
        "$ _) ",
        "$__) ",
        "$    "
      }
    },

    // letter N. 52 " 4 "
    { 52,
      { 0, 0, 0, 0 },
      { 5, 1, 1, 5 },
      {
        "$     ",
        "$|__| ",
        "$   | ",
        "$     "
      }
    },

    // letter N. 53 " 5 "
    { 53,
      { 0, 0, 0, 0 },
      { 1, 2, 1, 4 },
      {
        "$ __ ",
        "$|_  ",
        "$__) ",
        "$    "
      }
    },

    // letter N. 54 " 6 "
    { 54,
      { 0, 0, 0, 0 },
      { 2, 2, 1, 5 },
      {
        "$ __  ",
        "$/__  ",
        "$\\__) ",
        "$     "
      }
    },

    // letter N. 55 " 7 "
    { 55,
      { 0, 0, 0, 0 },
      { 1, 1, 2, 4 },
      {
        "$___ ",
        "$  / ",
        "$ /  ",
        "$    "
      }
    },

    // letter N. 56 " 8 "
    { 56,
      { 0, 0, 0, 0 },
      { 2, 1, 1, 5 },
      {
        "$ __  ",
        "$(__) ",
        "$(__) ",
        "$     "
      }
    },

    // letter N. 57 " 9 "
    { 57,
      { 0, 0, 0, 0 },
      { 2, 1, 1, 5 },
      {
        "$ __  ",
        "$(__\\ ",
        "$ __/ ",
        "$     "
      }
    },

    // letter N. 58 " : "
    { 58,
      { 2, 0, 0, 2 },
      { 2, 1, 1, 2 },
      {
        "  ",
        ". ",
        ". ",
        "  "
      }
    },

    // letter N. 59 " ; "
    { 59,
      { 2, 0, 0, 2 },
      { 2, 1, 1, 2 },
      {
        "  ",
        ". ",
        ", ",
        "  "
      }
    },

    // letter N. 60 " < "
    { 60,
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 },
      {
        "$ $",
        "$/$",
        "$\\$",
        "$ $"
      }
    },

    // letter N. 61 " = "
    { 61,
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 },
      {
        "$  $",
        "$__$",
        "$--$",
        "$  $"
      }
    },

    // letter N. 62 " > "
    { 62,
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 },
      {
        "$ $",
        "$\\$",
        "$/$",
        "$ $"
      }
    },

    // letter N. 63 " ? "
    { 63,
      { 0, 0, 0, 0 },
      { 1, 0, 1, 3 },
      {
        "$ _ ",
        "$  )",
        "$ . ",
        "$   "
      }
    },

    // letter N. 64 " @ "
    { 64,
      { 1, 1, 1, 1 },
      { 1, 1, 1, 1 },
      {
        " ",
        " ",
        " ",
        " "
      }
    },

    // letter N. 65 " A "
    { 65,
      { 5, 0, 0, 5 },
      { 5, 2, 1, 5 },
      {
        "     ",
        "$/\\  ",
        "/--\\ ",
        "     "
      }
    },

    // letter N. 66 " B "
    { 66,
      { 0, 0, 0, 5 },
      { 2, 1, 1, 5 },
      {
        "$__  ",
        "|__) ",
        "|__) ",
        "     "
      }
    },

    // letter N. 67 " C "
    { 67,
      { 0, 0, 0, 4 },
      { 1, 3, 1, 4 },
      {
        "$__ ",
        "/   ",
        "\\__ ",
        "    "
      }
    },

    // letter N. 68 " D "
    { 68,
      { 0, 0, 0, 5 },
      { 2, 1, 1, 5 },
      {
        "$__  ",
        "|  \\ ",
        "|__/ ",
        "     "
      }
    },

    // letter N. 69 " E "
    { 69,
      { 0, 0, 0, 4 },
      { 1, 2, 1, 4 },
      {
        "$__ ",
        "|_  ",
        "|__ ",
        "    "
      }
    },

    // letter N. 70 " F "
    { 70,
      { 0, 0, 0, 4 },
      { 1, 2, 3, 4 },
      {
        "$__ ",
        "|_  ",
        "|   ",
        "    "
      }
    },

    // letter N. 71 " G "
    { 71,
      { 0, 0, 0, 5 },
      { 2, 2, 1, 5 },
      {
        "$__  ",
        "/ _  ",
        "\\__) ",
        "     "
      }
    },

    // letter N. 72 " H "
    { 72,
      { 0, 0, 0, 5 },
      { 4, 1, 1, 5 },
      {
        "$    ",
        "|__| ",
        "|  | ",
        "     "
      }
    },

    // letter N. 73 " I "
    { 73,
      { 0, 0, 0, 2 },
      { 1, 1, 1, 2 },
      {
        "$ ",
        "| ",
        "| ",
        "  "
      }
    },

    // letter N. 74 " J "
    { 74,
      { 1, 1, 0, 4 },
      { 2, 1, 1, 4 },
      {
        " $  ",
        " $| ",
        "__) ",
        "    "
      }
    },

    // letter N. 75 " K "
    { 75,
      { 0, 0, 0, 4 },
      { 3, 1, 1, 4 },
      {
        "$   ",
        "|_/ ",
        "| \\ ",
        "    "
      }
    },

    // letter N. 76 " L "
    { 76,
      { 0, 0, 0, 4 },
      { 3, 3, 1, 4 },
      {
        "$   ",
        "|   ",
        "|__ ",
        "    "
      }
    },

    // letter N. 77 " M "
    { 77,
      { 0, 0, 0, 5 },
      { 4, 1, 1, 5 },
      {
        "$    ",
        "|\\/| ",
        "|  | ",
        "     "
      }
    },

    // letter N. 78 " N "
    { 78,
      { 0, 0, 0, 5 },
      { 4, 1, 1, 5 },
      {
        "$    ",
        "|\\ | ",
        "| \\| ",
        "     "
      }
    },

    // letter N. 79 " O "
    { 79,
      { 0, 0, 0, 5 },
      { 2, 1, 1, 5 },
      {
        "$__  ",
        "/  \\ ",
        "\\__/ ",
        "     "
      }
    },

    // letter N. 80 " P "
    { 80,
      { 0, 0, 0, 5 },
      { 2, 1, 2, 5 },
      {
        "$__  ",
        "|__) ",
        "| $  ",
        "     "
      }
    },

    // letter N. 81 " Q "
    { 81,
      { 0, 0, 0, 5 },
      { 2, 1, 1, 5 },
      {
        "$__  ",
        "/  \\ ",
        "\\_\\/ ",
        "     "
      }
    },

    // letter N. 82 " R "
    { 82,
      { 0, 0, 0, 5 },
      { 2, 1, 2, 5 },
      {
        "$__  ",
        "|__) ",
        "| \\  ",
        "     "
      }
    },

    // letter N. 83 " S "
    { 83,
      { 0, 0, 0, 4 },
      { 1, 2, 1, 4 },
      {
        "$__ ",
        "(_  ",
        "__) ",
        "    "
      }
    },

    // letter N. 84 " T "
    { 84,
      { 0, 0, 1, 4 },
      { 1, 1, 2, 4 },
      {
        "___ ",
        "$|$ ",
        " |  ",
        "    "
      }
    },

    // letter N. 85 " U "
    { 85,
      { 0, 0, 0, 5 },
      { 4, 1, 1, 5 },
      {
        "$    ",
        "/  \\ ",
        "\\__/ ",
        "     "
      }
    },

    // letter N. 86 " V "
    { 86,
      { 0, 0, 1, 5 },
      { 4, 1, 2, 5 },
      {
        "$    ",
        "\\  / ",
        " \\/  ",
        "     "
      }
    },

    // letter N. 87 " W "
    { 87,
      { 0, 0, 0, 5 },
      { 4, 1, 1, 5 },
      {
        "$    ",
        "|  | ",
        "|/\\| ",
        "     "
      }
    },

    // letter N. 88 " X "
    { 88,
      { 0, 0, 0, 4 },
      { 3, 1, 1, 4 },
      {
        "$   ",
        "\\_/ ",
        "/ \\ ",
        "    "
      }
    },

    // letter N. 89 " Y "
    { 89,
      { 0, 0, 1, 4 },
      { 3, 1, 2, 4 },
      {
        "$   ",
        "\\_/ ",
        " |  ",
        "    "
      }
    },

    // letter N. 90 " Z "
    { 90,
      { 0, 0, 0, 4 },
      { 1, 1, 1, 4 },
      {
        "___ ",
        "$_/ ",
        "/__ ",
        "    "
      }
    },

    // letter N. 91 " [ "
    { 91,
      { 1, 0, 0, 3 },
      { 1, 1, 1, 3 },
      {
        " _ ",
        "|$ ",
        "|_ ",
        "   "
      }
    },

    // letter N. 92 " \ "
    { 92,
      { 3, 0, 1, 3 },
      { 3, 2, 1, 3 },
      {
        "   ",
        "\\  ",
        " \\ ",
        "   "
      }
    },

    // letter N. 93 " ] "
    { 93,
      { 0, 0, 0, 3 },
      { 2, 1, 1, 3 },
      {
        "_  ",
        "$| ",
        "_| ",
        "   "
      }
    },

    // letter N. 94 " ^ "
    { 94,
      { 3, 0, 0, 3 },
      { 3, 1, 1, 3 },
      {
        "   ",
        "/\\ ",
        "$$ ",
        "   "
      }
    },

    // letter N. 95 " _ "
    { 95,
      { 3, 3, 0, 3 },
      { 3, 3, 1, 3 },
      {
        "   ",
        "   ",
        "__ ",
        "   "
      }
    },

    // letter N. 96 " ` "
    { 96,
      { 0, 0, 0, 2 },
      { 1, 1, 1, 2 },
      {
        "\\ ",
        "$ ",
        "$ ",
        "  "
      }
    },

    // letter N. 97 " a "
    { 97,
      { 4, 1, 0, 4 },
      { 4, 1, 1, 4 },
      {
        "    ",
        " _$ ",
        "(_| ",
        "    "
      }
    },

    // letter N. 98 " b "
    { 98,
      { 4, 0, 0, 4 },
      { 4, 2, 1, 4 },
      {
        "    ",
        "|_  ",
        "|_) ",
        "    "
      }
    },

    // letter N. 99 " c "
    { 99,
      { 3, 1, 0, 3 },
      { 3, 1, 1, 3 },
      {
        "   ",
        " _ ",
        "(_ ",
        "   "
      }
    },

    // letter N. 100 " d "
    { 100,
      { 4, 1, 0, 4 },
      { 4, 1, 1, 4 },
      {
        "    ",
        " _| ",
        "(_| ",
        "    "
      }
    },

    // letter N. 101 " e "
    { 101,
      { 3, 1, 0, 3 },
      { 3, 1, 1, 3 },
      {
        "   ",
        " _ ",
        "(- ",
        "   "
      }
    },

    // letter N. 102 " f "
    { 102,
      { 1, 0, 0, 3 },
      { 1, 1, 1, 3 },
      {
        " _ ",
        "(_ ",
        "|$ ",
        "   "
      }
    },

    // letter N. 103 " g "
    { 103,
      { 4, 1, 0, 0 },
      { 4, 2, 1, 2 },
      {
        "    ",
        " _  ",
        "(_) ",
        "_/  "
      }
    },

    // letter N. 104 " h "
    { 104,
      { 4, 0, 0, 4 },
      { 4, 2, 1, 4 },
      {
        "    ",
        "|_  ",
        "| ) ",
        "    "
      }
    },

    // letter N. 105 " i "
    { 105,
      { 1, 0, 0, 1 },
      { 2, 1, 1, 2 },
      {
        "  ",
        ". ",
        "| ",
        "  "
      }
    },

    // letter N. 106 " j "
    { 106,
      { 2, 0, 0, 0 },
      { 2, 1, 1, 1 },
      {
        "  ",
        ". ",
        "| ",
        "/ "
      }
    },

    // letter N. 107 " k "
    { 107,
      { 3, 0, 0, 3 },
      { 3, 1, 1, 3 },
      {
        "   ",
        "|$ ",
        "|( ",
        "   "
      }
    },

    // letter N. 108 " l "
    { 108,
      { 2, 0, 0, 2 },
      { 2, 1, 1, 2 },
      {
        "  ",
        "| ",
        "| ",
        "  "
      }
    },

    // letter N. 109 " m "
    { 109,
      { 4, 1, 0, 4 },
      { 4, 2, 1, 4 },
      {
        "    ",
        " _  ",
        "||| ",
        "    "
      }
    },

    // letter N. 110 " n "
    { 110,
      { 4, 1, 0, 4 },
      { 4, 2, 1, 4 },
      {
        "    ",
        " _  ",
        "| ) ",
        "    "
      }
    },

    // letter N. 111 " o "
    { 111,
      { 4, 1, 0, 4 },
      { 4, 2, 1, 4 },
      {
        "    ",
        " _  ",
        "(_) ",
        "    "
      }
    },

    // letter N. 112 " p "
    { 112,
      { 4, 1, 0, 0 },
      { 4, 2, 1, 3 },
      {
        "    ",
        " _  ",
        "|_) ",
        "|   "
      }
    },

    // letter N. 113 " q "
    { 113,
      { 4, 1, 0, 2 },
      { 4, 2, 1, 1 },
      {
        "    ",
        " _  ",
        "(_| ",
        "  | "
      }
    },

    // letter N. 114 " r "
    { 114,
      { 3, 1, 0, 3 },
      { 3, 1, 1, 3 },
      {
        "   ",
        " _ ",
        "|$ ",
        "   "
      }
    },

    // letter N. 115 " s "
    { 115,
      { 3, 1, 0, 3 },
      { 3, 1, 1, 3 },
      {
        "   ",
        " _ ",
        "_) ",
        "   "
      }
    },

    // letter N. 116 " t "
    { 116,
      { 3, 0, 0, 3 },
      { 3, 1, 1, 3 },
      {
        "   ",
        "|_ ",
        "|_ ",
        "   "
      }
    },

    // letter N. 117 " u "
    { 117,
      { 4, 0, 0, 4 },
      { 4, 1, 1, 4 },
      {
        "    ",
        "$ $ ",
        "|_| ",
        "    "
      }
    },

    // letter N. 118 " v "
    { 118,
      { 3, 0, 0, 3 },
      { 3, 1, 1, 3 },
      {
        "   ",
        "$$ ",
        "\\/ ",
        "   "
      }
    },

    // letter N. 119 " w "
    { 119,
      { 4, 0, 0, 4 },
      { 4, 1, 1, 4 },
      {
        "    ",
        "$ $ ",
        "\\)/ ",
        "    "
      }
    },

    // letter N. 120 " x "
    { 120,
      { 3, 0, 0, 3 },
      { 3, 1, 1, 3 },
      {
        "   ",
        "$$ ",
        ")( ",
        "   "
      }
    },

    // letter N. 121 " y "
    { 121,
      { 3, 0, 0, 0 },
      { 3, 1, 1, 2 },
      {
        "   ",
        "$$ ",
        "\\/ ",
        "/  "
      }
    },

    // letter N. 122 " z "
    { 122,
      { 3, 0, 0, 3 },
      { 3, 2, 1, 3 },
      {
        "   ",
        "_  ",
        "/_ ",
        "   "
      }
    },

    // letter N. 123 " { "
    { 123,
      { 0, 0, 0, 2 },
      { 1, 1, 1, 2 },
      {
        "( ",
        "< ",
        "( ",
        "  "
      }
    },

    // letter N. 124 " | "
    { 124,
      { 0, 0, 0, 2 },
      { 1, 1, 1, 2 },
      {
        "| ",
        "| ",
        "| ",
        "  "
      }
    },

    // letter N. 125 " } "
    { 125,
      { 0, 0, 0, 2 },
      { 1, 1, 1, 2 },
      {
        ") ",
        "> ",
        ") ",
        "  "
      }
    },

    // letter N. 126 " ~ "
    { 126,
      { 4, 0, 4, 4 },
      { 4, 1, 4, 4 },
      {
        "    ",
        "/\\/ ",
        "    ",
        "    "
      }
    },

    // letter N. 127 "  "
    { 127,
      { 0, 1, 0, 5 },
      { 1, 2, 1, 5 },
      {
        "o  o ",
        " /\\  ",
        "/--\\ ",
        "     "
      }
    },

    // letter N. 127 "  "
    { 128,
      { 0, 0, 0, 5 },
      { 1, 1, 1, 5 },
      {
        "o__o ",
        "/  \\ ",
        "\\__/ ",
        "     "
      }
    },

    // letter N. 127 "  "
    { 129,
      { 0, 0, 0, 5 },
      { 1, 1, 1, 5 },
      {
        "o  o ",
        "/  \\ ",
        "\\__/ ",
        "     "
      }
    },

    // letter N. 127 "  "
    { 130,
      { 4, 0, 0, 4 },
      { 4, 1, 1, 4 },
      {
        "    ",
        "-_- ",
        "(_| ",
        "    "
      }
    },

    // letter N. 127 "  "
    { 131,
      { 4, 0, 0, 4 },
      { 4, 1, 1, 4 },
      {
        "    ",
        "-_- ",
        "(_) ",
        "    "
      }
    },

    // letter N. 127 "  "
    { 132,
      { 4, 0, 0, 4 },
      { 4, 1, 1, 4 },
      {
        "    ",
        "- - ",
        "|_| ",
        "    "
      }
    },

    // letter N. 127 "  "
    { 133,
      { 1, 0, 0, 0 },
      { 2, 1, 1, 4 },
      {
        " __  ",
        "|__) ",
        "|__) ",
        "|    "
      }
    }
  };

  static unsigned const FontSize   = sizeof(characters)/sizeof(characters[0]) ;
  Banner straight(characters, Hardblank, FontHeight, FontMaxLen, FontSize ) ;

  //! \endcond
  
}
// EOF file font
