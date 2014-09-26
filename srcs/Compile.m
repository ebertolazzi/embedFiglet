clc;

NAMES = { 'Figlet' } ;

disp('---------------------------------------------------------');
for k=1:1
  N=NAMES{k} ;
  fprintf(1,'Compiling: %s\n',N) ;

  CMD = ['mex -output ../matlab/',N,' -largeArrayDims mex_',N,'.cc ', ...
          'Figlet.cc Figlet_Font_big.cc Figlet_Font_larry3d.cc Figlet_Font_script.cc ', ...
          'Figlet_Font_standard.cc Figlet_Font_banner.cc Figlet_Font_doom.cc ', ...
          'Figlet_Font_mini.cc Figlet_Font_small.cc Figlet_Font_straight.cc' ] ;
  if isunix
    if ismac
      CMD = [CMD, ' -lstdc++ CXXFLAGS="\$CXXFLAGS -Wall -O2 -g0"'] ;
    else
      CMD = [CMD, ' -lstdc++ CXXFLAGS="\$CXXFLAGS -Wall -O2 -g0"'] ;
    end
  elseif ispc
  end
  disp(CMD);
  eval(CMD);
end
disp('----------------------- DONE ----------------------------');
