--requires
package.cpath = package.cpath .. ';./fs/?.so;'
fs = require 'fs'
lpeg = require 'lpeg'

--caching functions
import P, R, C, S, V from lpeg

--patterns
spc = S(" \t\n")^0
digit = R('09')
letter = R('AZ', 'az')
name = (letter * (digit + letter + '_')^0) * spc
filename = C(name * '.' * name) * spc

main = () ->
  print filename\match 'jasj9s90ask.sa'
  

open_file = (path) ->
  base_path = tostring(path)\match('^%.?/?([%w%s%-_]+)')

main()