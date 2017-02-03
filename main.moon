--requires
fs = require 'lib.fs'
lpeg = require 'lpeg'

--caching functions
import P,R,C,S,V from lpeg

--patterns
white = (S ' \t\r\n') ^ 0

open_file = (path) ->
  base_path = tostring(path)\match('^%.?/?([%w%s%-_]+)')
