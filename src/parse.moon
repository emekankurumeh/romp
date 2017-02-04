lpeg = require 'lpeg'
import P, R, C, S, V from lpeg

ps = {}

spc = S(" \t\n")^0
digit = R('09')
letter = R('AZ', 'az')
name = (letter * (digit + letter + '_')^0) * spc
filename = C(name * '.' * name) * spc
build = (name * '.' * name) * spc * '|' * spc * C(name * spc) * spc * '->'

ps.parse = (data) ->
  for line in data\gmatch '[^\n]+'
    print filename\match line
    print build\match line

ps
