%w(colorize rake fileutils).each do |gem|
  begin
    require gem
  rescue LoadError
    warn "Install the #{gem} gem:\n $ (sudo) gem install #{gem}".magenta
    exit 1
  end
end

require_relative "./Rakefile_common.rb"

task :default => [:build]

task :mkl, [:year, :bits] do |t, args|
  args.with_defaults(:year => "2017", :bits => "x64" )
  sh "'C:/Program Files (x86)/IntelSWTools/compilers_and_libraries/windows/bin/compilervars.bat' -arch #{args.bits} vs#{args.year}shell"
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
  args.with_defaults( :year => "2017", :bits => "x64" )

  dir = "vs_#{args.year}_#{args.bits}"

  FileUtils.rm_rf   dir
  FileUtils.mkdir_p dir
  FileUtils.cd      dir

  cmake_cmd = win_vs(args.bits,args.year)
  if COMPILE_EXECUTABLE then
    cmake_cmd += ' -DBUILD_EXECUTABLE:VAR=true '
  else
    cmake_cmd += ' -DBUILD_EXECUTABLE:VAR=false '
  end
  if COMPILE_DYNAMIC then
    cmake_cmd += ' -DBUILD_SHARED:VAR=true '
  else
    cmake_cmd += ' -DBUILD_SHARED:VAR=false '
  end

  FileUtils.mkdir_p "../lib/lib"
  FileUtils.mkdir_p "../lib/bin"
  FileUtils.mkdir_p "../lib/bin/"+args.bits
  FileUtils.mkdir_p "../lib/dll"
  FileUtils.mkdir_p "../lib/include"

  if COMPILE_DEBUG then
    sh cmake_cmd + ' -DCMAKE_BUILD_TYPE:VAR=Debug ..'
    sh 'cmake --build . --config Debug --target install '+PARALLEL
    FileUtils.cp_r './lib/dll', '../lib/' if Dir.exist?('./lib/dll')
    Dir['./lib/bin/*'].each do |f|
      FileUtils.cp f, '../lib/bin/'+args.bits+'/'+File.basename(f)
    end
    Dir['./lib/lib/*'].each do |f|
      if /\_static.*\.lib$/.match(f) then
        FileUtils.cp f, '../lib/lib/'+File.basename(f)
      else
        FileUtils.cp f, '../lib/dll/'+File.basename(f)
      end
    end
  end

  sh cmake_cmd + ' -DCMAKE_BUILD_TYPE:VAR=Release ..'
  sh 'cmake  --build . --config Release  --target install '+PARALLEL
  FileUtils.cp_r './lib/dll', '../lib/' if Dir.exist?('./lib/dll')
  Dir['./lib/bin/*'].each do |f|
    FileUtils.cp f, '../lib/bin/'+args.bits+'/'+File.basename(f)
  end
  Dir['./lib/lib/*'].each do |f|
    if /\_static.*\.lib$/.match(f) then
      FileUtils.cp f, '../lib/lib/'+File.basename(f)
    else
      FileUtils.cp f, '../lib/dll/'+File.basename(f)
    end
  end
  FileUtils.cp_r './lib/include', '../lib/' if Dir.exist?('./lib/include')
  FileUtils.cd '..'

end

desc 'compile for OSX'
task :build_osx do

  dir = "build"

  FileUtils.rm_rf   dir
  FileUtils.mkdir_p dir
  FileUtils.cd      dir

  cmake_cmd = 'cmake '

  if COMPILE_EXECUTABLE then
    cmake_cmd += ' -DBUILD_EXECUTABLE:VAR=true '
  else
    cmake_cmd += ' -DBUILD_EXECUTABLE:VAR=false '
  end
  if COMPILE_DYNAMIC then
    cmake_cmd += ' -DBUILD_SHARED:VAR=true '
  else
    cmake_cmd += ' -DBUILD_SHARED:VAR=false '
  end

  if COMPILE_DEBUG then
    sh cmake_cmd + ' -DCMAKE_BUILD_TYPE:VAR=Debug ..'
    sh 'cmake --build . --config Debug --target install '+PARALLEL
  end
  sh cmake_cmd + ' -DCMAKE_BUILD_TYPE:VAR=Release ..'
  sh 'cmake --build . --config Release --target install '+PARALLEL
  FileUtils.cd '..'
end

desc 'compile for LINUX'
task :build_linux => [ :build_osx ] do
end

desc "clean for OSX"
task :clean_osx do
end

desc "clean for LINUX"
task :clean_linux do
end

desc "clean for WINDOWS"
task :clean_win do
end
