%w(colorize rake fileutils).each do |gem|
  begin
    require gem
  rescue LoadError
    warn "Install the #{gem} gem:\n $ (sudo) gem install #{gem}".magenta
    exit 1
  end
end

require_relative "./Rakefile_common.rb"

file_base = File.expand_path(File.dirname(__FILE__)).to_s+'/lib'

cmd_cmake_build = ""
if COMPILE_EXECUTABLE then
  cmd_cmake_build += ' -DBUILD_EXECUTABLE:VAR=true '
else
  cmd_cmake_build += ' -DBUILD_EXECUTABLE:VAR=false '
end
if COMPILE_DYNAMIC then
  cmd_cmake_build += ' -DBUILD_SHARED:VAR=true '
else
  cmd_cmake_build += ' -DBUILD_SHARED:VAR=false '
end
if COMPILE_DEBUG then
  cmd_cmake_build += ' -DCMAKE_BUILD_TYPE:VAR=Debug --loglevel=WARNING '
else
  cmd_cmake_build += ' -DCMAKE_BUILD_TYPE:VAR=Release --loglevel=WARNING '
end
cmd_cmake_build += " -DINSTALL_LOCAL=ON "


task :default => [:build]

task :mkl, [:year, :bits] do |t, args|
  args.with_defaults(:year => "2017", :bits => "x64" )
  sh "'C:/Program Files (x86)/IntelSWTools/compilers_and_libraries/windows/bin/compilervars.bat' -arch #{args.bits} vs#{args.year}shell"
end

desc "run tests"
task :test do
  FileUtils.cd "build"
  sh 'ctest --output-on-failure'
  FileUtils.cd '..'
end

TESTS = [
  "example",
  "test"
]

"run tests on linux/osx"
task :run do
  TESTS.each do |cmd|
    sh "./bin/#{cmd}"
  end
end

desc "run tests (Release) on windows"
task :run_win do
  TESTS.each do |cmd|
    sh "bin\\Release\\#{cmd}.exe"
  end
end

desc "run tests (Debug) on windows"
task :run_win_debug do
  TESTS.each do |cmd|
    sh "bin\\Debug\\#{cmd}.exe"
  end
end

desc "compile for Visual Studio [default year=2017, bits=x64]"
task :build_win, [:year, :bits] do |t, args|
  FileUtils.rm_rf 'lib'
  FileUtils.rm_rf 'lib3rd'

  args.with_defaults( :year => "2017", :bits => "x64" )

  dir = "vs_#{args.year}_#{args.bits}"

  FileUtils.rm_rf   dir
  FileUtils.mkdir_p dir
  FileUtils.cd      dir

  cmd_cmake = win_vs(args.bits,args.year) + cmd_cmake_build

  puts "run CMAKE for CLOTHOIDS".yellow
  sh cmd_cmake + ' ..'
  puts "compile with CMAKE for CLOTHOIDS".yellow
  if COMPILE_DEBUG then
    sh 'cmake --build . --config Debug --target install '+PARALLEL+QUIET
  else
    sh 'cmake --build . --config Release --target install '+PARALLEL+QUIET
  end

end

desc 'compile for OSX'
task :build_osx do
  FileUtils.rm_rf 'lib'
  FileUtils.rm_rf 'lib3rd'

  dir = "build"

  FileUtils.rm_rf   dir
  FileUtils.mkdir_p dir
  FileUtils.cd      dir

  cmd_cmake = "cmake " + cmd_cmake_build

  puts "run CMAKE for CLOTHOIDS".yellow
  sh cmd_cmake + ' ..'
  puts "compile with CMAKE for CLOTHOIDS".yellow
  if COMPILE_DEBUG then
    sh 'cmake --build . --config Debug --target install '+PARALLEL+QUIET
  else
    sh 'cmake  --build . --config Release  --target install '+PARALLEL+QUIET
  end

  FileUtils.cd '..'
end

desc 'compile for LINUX'
task :build_linux => [ :build_osx ] do
end

desc 'pack for OSX/LINUX/WINDOWS'
task :cpack do
  FileUtils.cd "build"
  puts "run CPACK for ROOTS".yellow
  sh 'cpack -C CPackConfig.cmake'
  sh 'cpack -C CPackSourceConfig.cmake'
  FileUtils.cd ".."
end

desc "clean for OSX"
task :clean_osx do
  FileUtils.rm_rf 'lib'
  FileUtils.rm_rf 'lib3rd'
end

desc "clean for LINUX"
task :clean_linux do
  FileUtils.rm_rf 'lib'
  FileUtils.rm_rf 'lib3rd'
end

desc "clean for WINDOWS"
task :clean_win do
  FileUtils.rm_rf 'lib'
  FileUtils.rm_rf 'lib3rd'
end
