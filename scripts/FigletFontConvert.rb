#!/usr/bin/env ruby -w

# *--------------------------------------------------------------------------*
# |                                                                          |
# |  Copyright (C) 2013                                                      |
# |                                                                          |
# |         , __                 , __                                        |
# |        /|/  \               /|/  \                                       |
# |         | __/ _   ,_         | __/ _   ,_                                | 
# |         |   \|/  /  |  |   | |   \|/  /  |  |   |                        |
# |         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       |
# |                           /|                   /|                        |
# |                           \|                   \|                        |
# |                                                                          |
# |      Enrico Bertolazzi                                                   |
# |      Dipartimento di Ingegneria Industriale (DII)                        |
# |      Universita` degli Studi di Trento                                   |
# |      email: enrico.bertolazzi@unitn.it                                   |
# |                                                                          |
# *--------------------------------------------------------------------------*
#
# Convert a figet file .flf to a C++ code which initialize a static structure
# that contains the description of the font.
#
#
# USAGE: ruby FigletFontConvert.rb infile.flf > outfile.cc
#
require 'fileUtils'

#            flf2a$ 6 5 20 15 3 0 143 229
#              |  | | | |  |  | |  |   |
#             /  /  | | |  |  | |  |   \
#    Signature  /  /  | |  |  | |   \   Codetag_Count
#      Hardblank  /  /  |  |  |  \   Full_Layout
#           Height  /   |  |   \  Print_Direction
#           Baseline   /    \   Comment_Lines
#            Max_Length      Old_Layout

nline        = 0
$char_number = 32
$char_lines  = []
$char_name   = "letter \"space\""
$indent      = "    "
$outstr      = "// Figlet font converted for use with Figlet class"
$outstr      = "// Converted FLF file: #{ARGV[0]}\n"
$outstr     += "#include \"Figlet.hh\"\n\n"
$outstr     += "namespace Figlet {\n\n"
$outstr     += "  //! \\cond NODOC\n\n" ;

begin
  
  def print_char
    # numero di carattere
    $outstr += "\n#{$indent}// #{$char_name}\n#{$indent}{ #{$char_number},\n" ;
    # vettore spazi a sinistra
    $outstr += "#{$indent}  { "
    $char_lines.each { |line|
      if line =~ /^( +)/ then
        $outstr += "#{$1.length}, "
      elsif line[0..0] != " " then
        $outstr += "0, "
      else
        $outstr += "#{line.length}, "
      end
    }
    $outstr.chop!
    $outstr.chop!
    $outstr += " },\n"

    # vettore spazi a destra
    $outstr += "#{$indent}  { "
    $char_lines.each { |line|
      if line =~ /( +)$/ then
        $outstr += "#{$1.length}, "
      elsif line[-1..-1] != " " then
        $outstr += "0, "
      else
        $outstr += "#{line.length}, "
      end
    }
    $outstr.chop!
    $outstr.chop!
    $outstr += " },\n"

    # stringhe carattere
    $outstr += "#{$indent}  {\n"
    $char_lines.each { |str|
      $outstr += "#{$indent}    \"" # inizio stringa
      str.each_char { |c|
        $outstr += c ;
        $outstr += c if c == "\\" ; # escape per carattere \
      }
      $outstr += "\",\n" # fine stringa
    }
    $outstr.chomp! # tolgo new line
    $outstr.chop!
    $outstr += "\n#{$indent}  }\n#{$indent}},\n"
  end

  $state = :signature
  File.open(ARGV[0],"r").each do |line|
    nline = nline + 1
    case $state
    when :signature then
      if line =~ /^flf2a(.)\s(\d+)\s(\d+)\s(\d+)\s([-+]?\d+)\s(\d+)/ then # (\d+) (\d+) (\d+)/ then
        $Hardblank       = $1
        $Height          = $2.to_i
        $Baseline        = $3.to_i
        $Max_Length      = $4.to_i
        $Old_Layout      = $5.to_i
        $Comment_Lines   = $6.to_i
        #$Print_Direction = $7.to_i
        #$Full_Layout     = $8.to_i
        #$Codetag_Count   = $9.to_i
        $state           = $Comment_Lines == 0 ? :char : :header ;

        $outstr += "  static char     const Hardblank  = '#{$Hardblank}' ;\n" ;
        $outstr += "  static unsigned const FontHeight = #{$Height} ;\n" ;
        $outstr += "  static unsigned const FontMaxLen = #{$Max_Length} ;\n" ;
        #$outstr += "  unsigned Baseline  = #{$Baseline} ;\n" ;
        $outstr += "  static FontFiglet characters[] = {\n" ;
      else
        print "Bad header line: #{line}\n"
        raise "Bad flf file"
      end
    when :header then
      #print "Skip line: #{line}" ;
      $state = :char if nline > $Comment_Lines ;
    when :char then
      #print "Char: #{line}" ;
      if line =~ /^(.*)@@$/ then # fine carattere
        $char_lines << $1
        print_char()
        $char_number = $char_number + 1
        $char_lines = []
        $char_name  = "letter N. #{$char_number} \" #{$char_number.chr} \"" if $char_number < 128
      elsif line =~ /^(.*)@$/ then # altra linea
        $char_lines << $1
      elsif line =~ /^[ \t]*0x([0-9a-fA-F]+)(.*)/ then # numero del carattere
        $char_number = $1.hex
        $char_name   = $2
      elsif line =~ /^[ \t]*(\d+)(.*)/ then # numero del carattere
        $char_number = $1.to_i
        $char_name   = $2
      end
    end
  end
rescue
  p "Trovato errore"
end
$outstr.chomp! # tolgo new line
$outstr.chop!  # tolgo ,
$outstr += "\n  };\n" ;
$outstr += "\n  static unsigned const FontSize   = sizeof(characters)/sizeof(characters[0]) ;" ;
$outstr += "\n  Banner #{File.basename(ARGV[0],'.*')}(characters, Hardblank, FontHeight, FontMaxLen, FontSize ) ;" ;
$outstr += "\n\n  //! \\endcond\n" ;
$outstr += "\n}\n// EOF file font\n" ;

print $outstr

#p "$char_number = #{$char_number}"

