package.cpath = package.cpath .. ';./fs/?.so;'

fs = require 'fs'
fl = require 'flags'
ps = require 'parse'
import p from require 'moon'

usage = [[usage: romp [dir]
    -w <d> watch directory for changes
    -h print this message
]]

arg = fl.parse usage
arg[1] or= fs.info 'exedir'

main = () ->
  if arg.h
    print usage
    os.exit!
  fs.setWritePath(arg[1])
  fs.mount(arg[1])
  print "no romp file" unless fs.exists('romp')
  data  = fs.read('romp')
  ps.parse data

open_file = (path) ->
  base_path = tostring(path)\match('^%.?/?([%w%s%-_]+)')

main()
