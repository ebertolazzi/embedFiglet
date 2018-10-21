#
#
#

%w( colorize rake fileutils ).each do |gem|
  begin
    require gem
  rescue LoadError
    warn "Install the #{gem} gem:\n $ (sudo) gem install #{gem}".magenta
    exit 1
  end
end

task :default => [:build]

LIB_NAME="embedFiglet"

desc "run tests"
task :run do
	sh "./test"
end

desc "run tests"
task :run_win do
	sh "./Release/test"
end

desc "compile for Visual Studio [default year=2017 bits=x64]"
task :build do

  FileUtils.rm_rf   "lib"
  FileUtils.mkdir_p "lib"
  FileUtils.rm_rf   "build"
  FileUtils.mkdir_p "build"
  FileUtils.cd      "build"

  puts "\n\nPrepare #{LIB_NAME} project".green
  sh 'cmake -DCMAKE_INSTALL_PREFIX:PATH=lib ..'

  puts "\n\nCompile #{LIB_NAME} Debug".green
  sh 'cmake --build . --config Debug  --target install'
  FileList["*#{LIB_NAME}*.*"].each do |f|
    puts "Copying #{f}".yellow
    ext = File.extname(f);
    FileUtils.cp f, "../lib/#{File.basename(f,ext)}_debug#{ext}"
  end

  puts "\n\nCompile Splines Release".green
  sh 'cmake --build . --config Release --target install'
  FileList["*#{LIB_NAME}*.*"].each do |f|
    puts "Copying #{f}".yellow
    FileUtils.cp f, "../lib/#{File.basename(f)}"
  end

  puts "\n\nCopy include".green
  FileUtils.cp_r "lib/lib/include", "../lib/include"

  FileUtils.cd '..'

end

desc "compile for Visual Studio [default year=2017 bits=x64]"
task :build_win, [:year, :bits] do |t, args|
  args.with_defaults( :year => "2017", :bits => "x64" )

  puts "\n\nPrepare #{LIB_NAME} project".green
  dir = "vs_#{args.year}_#{args.bits}"

  FileUtils.rm_rf   "lib"
  FileUtils.mkdir_p "lib"

  FileUtils.rm_rf   dir
  FileUtils.mkdir_p dir
  FileUtils.cd      dir

  tmp = " -DBITS=#{args.bits} -DYEAR=#{args.year} " + ' -DCMAKE_INSTALL_PREFIX:PATH=lib ..'

  win32_64 = ''
  case args.bits
  when /x64/
    win32_64 = ' Win64'
  end

  case args.year
  when "2010"
    sh 'cmake -G "Visual Studio 10 2010' + win32_64 +'" ' + tmp
  when "2012"
    sh 'cmake -G "Visual Studio 11 2012' + win32_64 +'" ' + tmp
  when "2013"
    sh 'cmake -G "Visual Studio 12 2013' + win32_64 +'" ' + tmp
  when "2015"
    sh 'cmake -G "Visual Studio 14 2015' + win32_64 +'" ' + tmp
  when "2017"
    sh 'cmake -G "Visual Studio 15 2017' + win32_64 +'" ' + tmp
  else
    puts "Visual Studio year #{year} not supported!\n";
  end

  puts "\n\nCompile #{LIB_NAME} Debug".green
  sh 'cmake --build . --config Debug --target install'
  FileUtils.cp "Debug/#{LIB_NAME}.lib", "../lib/#{LIB_NAME}_vs#{args.year}_#{args.bits}_debug.lib"

  puts "\n\nCompile #{LIB_NAME} Release".green
  sh 'cmake --build . --config Release  --target install'
  FileUtils.cp "Release/#{LIB_NAME}.lib", "../lib/#{LIB_NAME}_vs#{args.year}_#{args.bits}.lib"  

  puts "\n\nCopy include".green
  FileUtils.cp_r "lib/lib/include", "../lib/include"

  FileUtils.cd '..'

end
