require 'fileutils'
require 'rbconfig'
require 'rake'

class String
  def green  = "\e[32m#{self}\e[0m"
  def yellow = "\e[33m#{self}\e[0m"
  def red    = "\e[31m#{self}\e[0m"
end

ROOT      = File.expand_path(__dir__)
BUILD_DIR = File.join(ROOT, 'build')
BUILD_TYPE = ENV.fetch('BUILD_TYPE', 'Release')
GENERATOR  = ENV.fetch('CMAKE_GENERATOR', 'Ninja')
PARALLEL   = ENV['JOBS'] ? "--parallel #{ENV['JOBS']}" : '--parallel'

HOST_OS = RbConfig::CONFIG['host_os']
PLATFORM = case HOST_OS
           when /darwin/i then 'osx'
           when /linux/i  then 'linux'
           when /mingw|mswin/i then 'windows'
           else HOST_OS
           end

def bool_env(name, default)
  value = ENV[name]
  return default if value.nil? || value.empty?
  %w[1 true yes on].include?(value.downcase)
end

def cmake_bool(value)
  value ? 'ON' : 'OFF'
end

def configure_args(enable_tests:)
  shared = bool_env('BUILD_SHARED', false)
  install_local = bool_env('UTILS_INSTALL_LOCAL', true)

  [
    '-S', ROOT,
    '-B', BUILD_DIR,
    '-G', GENERATOR,
    "-DCMAKE_BUILD_TYPE=#{BUILD_TYPE}",
    "-DCMAKE_INSTALL_PREFIX=#{File.join(ROOT, 'lib')}",
    '-DCMAKE_INSTALL_LIBDIR=lib',
    '-DCMAKE_INSTALL_INCLUDEDIR=include',
    '-DCMAKE_INSTALL_BINDIR=bin',
    "-DUTILS_BUILD_SHARED:BOOL=#{cmake_bool(shared)}",
    "-DUTILS_INSTALL_LOCAL:BOOL=#{cmake_bool(install_local)}",
    "-DUTILS_ENABLE_TESTS:BOOL=#{cmake_bool(enable_tests)}",
    "-DBUILD_EXECUTABLE:BOOL=#{cmake_bool(enable_tests)}"
  ]
end

def configure(enable_tests:)
  FileUtils.mkdir_p BUILD_DIR
  puts "Configurazione CMake in #{BUILD_DIR} per #{PLATFORM}...".yellow
  sh 'cmake', *configure_args(enable_tests: enable_tests)
end

def build_target(target)
  sh 'cmake', '--build', BUILD_DIR, '--config', BUILD_TYPE, '--target', target, PARALLEL
end

def run_ctest
  sh 'ctest', '--test-dir', BUILD_DIR, '--build-config', BUILD_TYPE, '--output-on-failure'
end

desc 'Configure, compile and install only the library'
task :build do
  configure(enable_tests: false)
  puts 'Compilazione e installazione della sola libreria...'.yellow
  build_target('install')
end

desc 'Configure, compile tests and run them'
task :run do
  configure(enable_tests: true)
  puts 'Compilazione dei test...'.yellow
  build_target('embedFiglet_all_tests')
  puts 'Esecuzione dei test...'.yellow
  run_ctest
end

desc 'Remove build and generated artifacts'
task :clean do
  FileUtils.rm_rf BUILD_DIR
  FileUtils.rm_rf File.join(ROOT, 'lib')
  FileUtils.rm_rf File.join(ROOT, 'bin')
end

desc 'Create CPack packages from the existing build directory'
task :cpack do
  Dir.chdir(BUILD_DIR) do
    puts 'run CPACK for embedFiglet'.yellow
    sh 'cpack', '-C', BUILD_TYPE
  end
end

task :build_osx   => :build
task :build_linux => :build
task :build_mingw => :build
task :build_win   => :build

task :clean_osx   => :clean
task :clean_linux => :clean
task :clean_mingw => :clean
task :clean_win   => :clean

task :default => :build
