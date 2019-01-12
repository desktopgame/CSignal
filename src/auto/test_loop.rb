require "open3"
require "fileutils"
require "date"
require 'fileutils'
require_relative "cmd"
require 'rbconfig'

def os
  @os ||= (
    host_os = RbConfig::CONFIG['host_os']
    case host_os
    when /mswin|msys|mingw|cygwin|bccwin|wince|emc/
      :windows
    when /darwin|mac os/
      :macosx
    when /linux/
      :linux
    when /solaris|bsd/
      :unix
    else
      :unknown
    end
  )
end

def say(str)
	if(os == :macosx) then
		system("say " + str)
	end
end

loops = 10
if(ARGV.length > 0) then
	loops = ARGV[0].to_i
end
puts ("loops..." + loops.to_s)
puts "make..."
o, e, s = Open3.capture3("make")
o.lines {|i| puts "    " + i}
e.lines {|i| puts "    " + i}

puts "test..."
o_list = []
e_list = []
loops.times do |i|
	puts ("run test..." + i.to_s)
	Dir.chdir("../bin") do
		Cmd.timeout = 10;
		begin
			res = Cmd.run("./beacon --test");
			o = res.stdout;
			e = res.stderr;
			s = res.status;
			if(e.include?("AddressSanitizer") ||
				e.include?("FAIL.")) then
				puts o
				puts e
				puts "----- FAIL -----"
				exit
			end
			o_list << o
			e_list << e
		rescue Cmd::Exception => e
			while line = Cmd.stdout_file_last.gets
				puts "o: " + line
			end
			while line = Cmd.stderr_file_last.gets
				puts "e: " + line
			end
			puts("----FAIL")
			say("テストがエラーで終わりました")
			abort()
		end
	end
end
puts "----- SUCCESS -----"
say("テストが正常に終わりました")