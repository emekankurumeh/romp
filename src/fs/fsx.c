/* Build me with:
   gcc -shared -o fs.so -undefined dynamic_lookup fsx.c
*/

/* Copyright (C) 2012 Ross Andrews
-- This program is free software: you can redistribute it and/or modify
-- it under the terms of the GNU Lesser General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU Lesser General Public License
-- along with this program.  If not, see <http://www.gnu.org/licenses/lgpl.txt>. */

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
#include "fs.c"
#include "util.h"

#if _WIN32
  #include <windows.h>
  #include <direct.h>
  #define getcwd _getcwd
#elif __linux__
  #include <unistd.h>
#elif __APPLE__
  #include <mach-o/dyld.h>
#endif

#ifndef LUA
#define LUA 51
#endif

static void checkError(lua_State *L, int err, const char *str);
static char *dirname(char *str);
static int l_fs_mount(lua_State *L);
static int l_fs_unmount(lua_State *L);
static int l_fs_setWritePath(lua_State *L);
static int l_fs_exists(lua_State *L);
static int l_fs_getSize(lua_State *L);
static int l_fs_getModified(lua_State *L);
static int l_fs_read(lua_State *L);
static int l_fs_isDir(lua_State *L);
static int l_fs_listDir(lua_State *L);
static int l_fs_write(lua_State *L);
static int l_fs_append(lua_State *L);
static int l_fs_delete(lua_State *L);
static int l_fs_chdir(lua_State *L);
static int l_fs_makeDirs(lua_State *L);
static int l_fs_info(lua_State *L);

int luaopen_fs(lua_State *L){
  luaL_Reg reg[] = {
    { "mount",        l_fs_mount        },
    { "unmount",      l_fs_unmount      },
    { "setWritePath", l_fs_setWritePath },
    { "exists",       l_fs_exists       },
    { "getSize",      l_fs_getSize      },
    { "getModified",  l_fs_getModified  },
    { "read",         l_fs_read         },
    { "isDir",        l_fs_isDir        },
    { "listDir",      l_fs_listDir      },
    { "write",        l_fs_write        },
    { "append",       l_fs_append       },
    { "delete",       l_fs_delete       },
    { "chdir",        l_fs_chdir       },
    { "makeDirs",     l_fs_makeDirs     },
    { "info",         l_fs_info         },
    { NULL, NULL }
  };

  #if LUA <= 51 || JIT
    luaL_openlib(L, "fs", reg, 0);
  #elif LUA > 51
    luaL_newlib(L, reg);
  #endif

  atexit(fs_deinit);
  return 0;
}

static void checkError(lua_State *L, int err, const char *str) {
  if (!err) return;
  if (err == FS_ENOWRITEPATH || !str) {
    luaL_error(L, "%s", fs_errorStr(err));
  }
  luaL_error(L, "%s '%s'", fs_errorStr(err), str);
}

static char *dirname(char *str) {
  char *p = str + strlen(str);
  while (p != str) {
    if (*p == '/' || *p == '\\') {
      *p = '\0';
      break;
    }
    p--;
  }
  return str;
}

static int l_fs_mount(lua_State *L) {
  const char *path = luaL_checkstring(L, 1);
  int res = fs_mount(path);
  if (res != FS_ESUCCESS) {
    lua_pushnil(L);
    lua_pushfstring(L, "%s '%s'", fs_errorStr(res), path);
    return 2;
  }
  lua_pushboolean(L, 1);
  return 1;
}


static int l_fs_unmount(lua_State *L) {
  const char *path = luaL_checkstring(L, 1);
  fs_unmount(path);
  return 0;
}


static int l_fs_setWritePath(lua_State *L) {
  const char *path = luaL_checkstring(L, 1);
  int res = fs_setWritePath(path);
  checkError(L, res, path);
  return 0;
}


static int l_fs_exists(lua_State *L) {
  const char *filename = luaL_checkstring(L, 1);
  lua_pushboolean(L, fs_exists(filename));
  return 1;
}


static int l_fs_getSize(lua_State *L) {
  const char *filename = luaL_checkstring(L, 1);
  size_t sz;
  int res = fs_size(filename, &sz);
  checkError(L, res, filename);
  lua_pushnumber(L, sz);
  return 1;
}


static int l_fs_getModified(lua_State *L) {
  const char *filename = luaL_checkstring(L, 1);
  unsigned t;
  int res = fs_modified(filename, &t);
  checkError(L, res, filename);
  lua_pushnumber(L, t);
  return 1;
}


static int l_fs_read(lua_State *L) {
  const char *filename = luaL_checkstring(L, 1);
  size_t len;
  char *data = fs_read(filename, &len);
  if (!data) {
    luaL_error(L, "could not read file '%s'", filename);
  }
  lua_pushlstring(L, data, len);
  free(data);
  return 1;
}


static int l_fs_isDir(lua_State *L) {
  const char *filename = luaL_checkstring(L, 1);
  lua_pushboolean(L, fs_isDir(filename));
  return 1;
}


static int l_fs_listDir(lua_State *L) {
  const char *path = luaL_checkstring(L, 1);
  fs_FileListNode *list = fs_listDir(path);
  lua_newtable(L);
  int i = 1;
  fs_FileListNode *n = list;
  while (n) {
    lua_pushstring(L, n->name);
    lua_rawseti(L, -2, i);
    i++;
    n = n->next;
  }
  fs_freeFileList(list);
  return 1;
}


static int l_fs_write(lua_State *L) {
  const char *filename = luaL_checkstring(L, 1);
  size_t len;
  const char *data = luaL_checklstring(L, 2, &len);
  int res = fs_write(filename, data, len);
  checkError(L, res, filename);
  return 0;
}


static int l_fs_append(lua_State *L) {
  const char *filename = luaL_checkstring(L, 1);
  size_t len;
  const char *data = luaL_checklstring(L, 2, &len);
  int res = fs_append(filename, data, len);
  checkError(L, res, filename);
  return 0;
}


static int l_fs_delete(lua_State *L) {
  const char *filename = luaL_checkstring(L, 1);
  int res = fs_delete(filename);
  if (res != FS_ESUCCESS) {
    lua_pushnil(L);
    lua_pushfstring(L, "%s", fs_errorStr(res));
    return 2;
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int l_fs_delete(lua_State *L) {
  const char *filename = luaL_checkstring(L, 1);
  int res = fs_delete(filename);
  if (res != FS_ESUCCESS) {
    lua_pushnil(L);
    lua_pushfstring(L, "%s", fs_errorStr(res));
    return 2;
  }
  lua_pushboolean(L, 1);
  return 1;
}

static int l_fs_makeDirs(lua_State *L) {
  const char *path = luaL_checkstring(L, 1);
  int res = fs_makeDirs(path);
  if (res != FS_ESUCCESS) {
    luaL_error(L, "%s '%s'", fs_errorStr(res), path);
  }
  return 0;
}

static int l_fs_info(lua_State *L) {
  const char *str = luaL_checkstring(L, 1);
  if (!strcmp(str, "os")) {
#if _WIN32
    lua_pushstring(L, "windows");
#elif __linux__
    lua_pushstring(L, "linux");
#elif __FreeBSD__
    lua_pushstring(L, "bsd");
#elif __APPLE__
    lua_pushstring(L, "osx");
#else
    lua_pushstring(L, "?");
#endif

  } else if (!strcmp(str, "exedir")) {
    UNUSED(dirname);
#if _WIN32
    char buf[1024];
    int len = GetModuleFileName(NULL, buf, sizeof(buf) - 1);
    buf[len] = '\0';
    dirname(buf);
    lua_pushfstring(L, "%s", buf);
#elif __linux__
    char path[128];
    char buf[1024];
    sprintf(path, "/proc/%d/exe", getpid());
    int len = readlink(path, buf, sizeof(buf) - 1);
    ASSERT( len != -1 );
    buf[len] = '\0';
    dirname(buf);
    lua_pushfstring(L, "%s", buf);
#elif __FreeBSD__
    /* TODO : Implement this */
    lua_pushfstring(L, ".");
#elif __APPLE__
    char buf[1024];
    uint32_t size = sizeof(buf);
    ASSERT( _NSGetExecutablePath(buf, &size) == 0 );
    dirname(buf);
    lua_pushfstring(L, "%s", buf);
#else
    lua_pushfstring(L, ".");
#endif

  } else if (!strcmp(str, "wrkdir")) {
    UNUSED(dirname);
#if _WIN32
    char buf[1024];
    size_t size = sizeof(buf);
    ASSERT( getcwd(buf, &size) != NULL );
    dirname(buf);
    lua_pushfstring(L, "%s", buf);
#elif __linux__
    char buf[1024];
    size_t size = sizeof(buf);
    ASSERT( getcwd(buf, &size) != NULL );
    dirname(buf);
    lua_pushfstring(L, "%s", buf);
#elif __FreeBSD__
    /* TODO : Implement this */
    lua_pushfstring(L, ".");
#elif __APPLE__
    char buf[1024];
    size_t size = sizeof(buf);
    ASSERT( getcwd(buf, &size) != NULL );
    dirname(buf);
    lua_pushfstring(L, "%s", buf);
#else
    lua_pushfstring(L, ".");
#endif

  } else if (!strcmp(str, "appdata")) {
#if _WIN32
    lua_pushfstring(L, "%s", getenv("APPDATA"));
#elif __APPLE__
    lua_pushfstring(L, "%s/Library/Application Support", getenv("HOME"));
#else
    lua_pushfstring(L, "%s/.local/share", getenv("HOME"));
#endif
  } else {
    luaL_argerror(L, 1, "invalid string");
  }
  return 1;
}
