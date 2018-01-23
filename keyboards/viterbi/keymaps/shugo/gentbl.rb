require_relative "tc_tbl"

puts "/* Generated by gentbl.rb; DO NOT EDIT! */"
puts
puts "const uint16_t PROGMEM tcode_table[] = {" + TC_TBL.flat_map { |row|
  row.gsub(" ", "").each_char.map { |ch|
    "0x%04X" % ch.ord
  }
}.join(", ") + "};"
