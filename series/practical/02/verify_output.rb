#!/usr/bin/env ruby

avail = 5

ARGF.each_with_index do |line, i|
  if line =~ /^(Freed|Locked) (\d) resources, now available: (\d)$/
    if $1 == 'Freed'
      expected = avail + $2.to_i
      avail = $3.to_i

      if (expected != avail)
        puts "Oh no!"
        puts "Expected: #{ expected }"
        puts "Available: #{ avail}"
        puts "Line ##{ i }: #{ line }"
      end
    elsif $1 == 'Locked'
      expected = avail - $2.to_i
      avail = $3.to_i

      if (expected != avail)
        puts "Oh no!"
        puts "Expected: #{ expected }"
        puts "Available: #{ avail}"
        puts "Line ##{ i }: #{ line }"
      end
    end
  end
end

puts "All good"
