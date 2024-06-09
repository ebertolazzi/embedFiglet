if File.exist?(File.expand_path('./cmake_utils/Rakefile_common.rb', File.dirname(__FILE__))) then
  require_relative "./cmake_utils/Rakefile_common.rb"
else
  require_relative "../Rakefile_common.rb"
end

task :build_common, [:bits] do |t, args|
  args.with_defaults( :bits => "" )

  puts "FIGLET build (osx/linux/mingw/windows)".green

  FileUtils.rm_rf   'lib'
  FileUtils.rm_rf   'build'
  FileUtils.mkdir_p 'build'
  FileUtils.cd      'build'

  puts "run CMAKE for FIGLET".yellow

  if args.bits.size > 0 then
    sh "cmake -G Ninja -DBITS:VAR=#{args.bits} " + cmd_cmake_build() + ' ..'
  else
    sh "cmake -G Ninja " + cmd_cmake_build() + ' ..'
  end

  puts "compile with CMAKE for UTILS".yellow
  if COMPILE_DEBUG then
    sh 'cmake --build . --config Debug --target install '+PARALLEL
  else
    sh 'cmake --build . --config Release --target install '+PARALLEL
  end

  FileUtils.cd '..'
end

task :build_osx   => :build_common do end
task :build_linux => :build_common do end
task :build_mingw => :build_common do end

desc 'compile for WINDOWS'
task :build_win do
  # check architecture
  case `where cl.exe`.chop
  when /x64\\cl\.exe/
    VS_ARCH = 'x64'
  when /amd64\\cl\.exe/
    VS_ARCH = 'x64'
  when /bin\\cl\.exe/
    VS_ARCH = 'x86'
  else
    raise RuntimeError, "Cannot determine architecture for Visual Studio".red
  end
  Rake::Task[:build_common].invoke(VS_ARCH)
end

task :clean do
  FileUtils.rm_rf 'build'
  FileUtils.rm_rf 'lib'
  FileUtils.rm_rf 'lib3rd'
end

task :clean_osx   => :clean do end
task :clean_linux => :clean do end
task :clean_mingw => :clean do end
task :clean_win   => :clean do end

desc 'pack for OSX/LINUX/MINTGW/WINDOWS'
task :cpack do
  FileUtils.cd "build"
  puts "run CPACK for Embed Figlet".yellow
  sh 'cpack -C CPackConfig.cmake'
  sh 'cpack -C CPackSourceConfig.cmake'
  FileUtils.cd ".."
end
