lpeg = require 'lpeg'
import P, R, C, S, V, Ct from lpeg

ps = {}

spc = S(" \t\n")^0
digit = R '09'
letter = R('AZ', 'az') + '/'

alpha = digit + letter
letter = (letter * (alpha + '_')^0) * spc

info = C(letter * '.' * letter) * spc
info = info * '|' * spc * C (letter * spc + '%' * spc)^0
-- info = info * spc * '->' * spc * C ('%' + letter * spc )^0
info = Ct info

ps.parse = (data) ->
  ret = {}
  for line in data\gmatch '[^\n]+'
    tmp = info\match line
    ret.name = tmp[1]
    ret.exec = tmp[2]
    -- ret.outp = tmp[3]\gsub '%%b', tmp[1]\match '^([%w%s%-_]+)'
  ret

ps
