local open_file

package.cpath = package.cpath .. ';./fs/?.so;'
start = os.clock!

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
inf = {}

main = () ->
  if arg.h
    print usage
    os.exit!
  fs.setWritePath(arg[1])
  fs.mount(arg[1])
  print "no romp file" unless fs.exists 'romp'
  data  = fs.read 'romp'
  for line in data\gmatch '[^\n]+'
    inf = ps.parse data
    os.execute inf.exec\gsub '%%f', fs.info('wrkdir') .. '/' .. open_file(arg[1]) .. '/' .. inf.name
    print '[compiled: %s]'\format inf.name
    print '[time: %0.2fs]'\format os.clock! - start

open_file = (path) ->
  print path
  base_path = tostring(path)\match('^%.-/-([%w%s%-_]+)')
  print base_path
  return base_path

main()
