ffi = require 'ffi'
for cdef in *require 'cdef'
  ffi.cdef cdef
fs = ffi.load('fs.so')



open_file = (path) ->
  base_path = tostring(path)\match('^%.?/?([%w%s%-_]+)')
  fs.fs_setWritePath(base_path)
  tin = ffi.new('ffs_listDir('..base_path..')')

open_file('example/test.lang')
