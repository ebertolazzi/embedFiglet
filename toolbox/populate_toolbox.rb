#!/usr/bin/ruby -w

require 'fileutils'

FileUtils.rm_rf   "src"
FileUtils.mkdir_p "src"

FileUtils.rm_rf   "bin"
FileUtils.mkdir_p "bin"

lst = Dir["../src/*.cc"]
lst.each do |filename|
  FileUtils.cp filename, "./src/" + File.basename(filename);
end
lst = Dir["../src/*.h*"]
lst.each do |filename|
  FileUtils.cp filename, "./src/" + File.basename(filename);
end

FileUtils.cp "../license.txt", "license.txt"
