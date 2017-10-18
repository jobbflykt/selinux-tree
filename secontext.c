#include "tree.h"

#if defined(LINUX)
#include <sys/xattr.h>
#endif

char *get_secontext(const char *path)
{
  char *buf;
  ssize_t len;
  const size_t maxlen = 255;

  buf = xmalloc(maxlen + 1);
#if defined(LINUX)
  len = getxattr(path, "security.selinux", buf, maxlen);
  if(len >= 0)
  {
    buf[len] = '\0';
  }
  else
#endif
  {
    strcpy(buf, "[Error reading selinux context]");
  }
  return buf;
}
