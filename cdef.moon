fs = [[
  typedef struct fs_FileListNode {
    char *name;
    struct fs_FileListNode *next;
  } fs_FileListNode;
  typedef unsigned long size_t;
  const char *fs_errorStr(int err);
  void fs_deinit(void);
  int fs_mount(const char *path);
  int fs_unmount(const char *path);
  int fs_setWritePath(const char *path);
  int fs_exists(const char *filename);
  int fs_modified(const char *filename, unsigned *mtime);
  int fs_size(const char *filename, size_t *size);
  void *fs_read(const char *filename, size_t *size);
  int fs_isDir(const char *filename);
  fs_FileListNode *fs_listDir(const char *path);
  void fs_freeFileList(fs_FileListNode *list);
  int fs_write(const char *filename, const void *data, int size);
  int fs_append(const char *filename, const void *data, int size);
  int fs_delete(const char *filename);
  int fs_makeDirs(const char *path);
]]

{fs}
