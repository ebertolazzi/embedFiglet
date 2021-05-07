clc;
clear functions;

old_dir = cd(fileparts(which(mfilename)));

NAMES = { ...
  'Figlet', ...
};
 
LIB_NAMES = { ...
  'Figlet.cc', ...
  'Figlet_Font_banner.cc', ...
  'Figlet_Font_big.cc', ...
  'Figlet_Font_doom.cc', ...
  'Figlet_Font_larry3d.cc', ...
  'Figlet_Font_mini.cc', ...
  'Figlet_Font_script.cc', ...
  'Figlet_Font_small.cc', ...
  'Figlet_Font_standard.cc', ...
  'Figlet_Font_straight.cc', ...
};

MROOT = matlabroot;

CMDBASE = 'mex -c -largeArrayDims -Isrc -Isrc/Utils ';
if isunix
  CMDBASE = [CMDBASE, 'CXXFLAGS="\$CXXFLAGS -Wall -O2 -g" '];
elseif ispc
end

LIB_OBJS = '';
for k=1:length(LIB_NAMES)
  [filepath,bname,ext] = fileparts(LIB_NAMES{k});
  NAME = [' src/', filepath, '/', bname, ext ];
  if isunix
    LIB_OBJS = [ LIB_OBJS, bname, '.o ' ];
  elseif ispc
    LIB_OBJS = [ LIB_OBJS, bname, '.obj ' ];
  end
  CMD = [CMDBASE ' -c ' NAME];
  disp('---------------------------------------------------------');
  disp(CMD);
  eval(CMD);
end

for k=1:length(NAMES)
  N=NAMES{k};
  disp('---------------------------------------------------------');
  fprintf(1,'Compiling: %s\n',N);

  CMD = [ 'while mislocked(''' N '''); munlock(''' N '''); end;'];
  eval(CMD);

  CMD = [ 'mex -Isrc -output lib/', N ];
  CMD = [ CMD, ' -largeArrayDims src_mex/mex_', N ];
  CMD = [ CMD, '.cc ', LIB_OBJS ];

  if ismac
    CMD = [CMD, ' CXXFLAGS="\$CXXFLAGS -Wall -O2 -g"'];
  elseif isunix
    % Workaround for MATLAB 2020 that force dynamic link with old libstdc++
    % solution: link with static libstdc++
    % ARCH  = computer('arch');
    % PATH1 = [MROOT, '/bin/', ARCH];
    % PATH2 = [MROOT, '/extern/bin/', ARCH];
    CMD = [ CMD, ...
      ' CXXFLAGS="\$CXXFLAGS -Wall -O2 -g"' ...
      ' LDFLAGS="\$LDFLAGS -static-libgcc -static-libstdc++"' ...
      ' LINKLIBS="-ldl -L\$MATLABROOT/bin/\$ARCH -L\$MATLABROOT/extern/bin/\$ARCH -lMatlabDataArray -lmx -lmex -lmat -lm "' ...
    ];
  elseif ispc
  end

  disp(CMD);
  eval(CMD);
end

if isunix
  delete *.o
else
  delete *.obj
end

cd(old_dir);

disp('----------------------- DONE ----------------------------');
