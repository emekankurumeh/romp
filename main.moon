local open_file
require 'moonscript'
package.cpath = package.cpath .. ';./src/fs/?.so;'
start = os.clock!

fs = require 'fs'
fl = require 'src.flags'
ps = require 'src.parse'
cl = require 'src.color'
import p from require 'moon'

usage = [[usage: romp [dir]
    -w <d> watch directory for changes
    -h print this message
]]
ar = fl.parse usage
ar[1] or= fs.info('wrkdir')
inf = {}

base_path = (path) ->
  base_path = tostring(path)\match('^%.-/-([%w%s%-_]+)')
  return base_path

do_file = (data) ->
  fs.chdir(fs.info('wrkdir') .. '/'..open_file(ar[1]) .. '/')
  os.execute inf.exec\gsub '%%f', inf.name

main = () ->
  if ar.h
    print usage
    os.exit!
  fs.mount(ar[1])
  unless fs.exists 'romp'
    print "no romp file"
    os.exit!
  fs.setWritePath(ar[1])
  data  = fs.read 'romp'
  for line in data\gmatch '[^\n]+'
    inf = ps.parse data

    print cl.reset .. cl.fore.green .. '[compiled: %s]'\format(inf.name) .. cl.reset
    print '[time: %0.2fs]'\format os.clock! - start



main()
