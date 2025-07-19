
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef char *sds;

// sds: simple dynamic string (Redis database)
struct sdshdr {
    int len;
    int free;
    char buf[];
//中括号里面没有数字，结构体的最后一个成员可以是一个长度为01的数组
//这种数组成为柔性数组，通常就放在结构体的最后一个成员
//为什么要这样做？为什么不直接放一个char *buf; 指针
//处于内存和性能的考虑，char *buf是一个指针，内存布局带来性能的差别
//*buf要访问字符串，要解引用一次，性能有损失
//buf[]紧跟在free后面，访问时也可以通过偏移访问，不需要指针
};



//int names[0] = {};

static inline size_t sdslen(const sds s) {
  struct sdshdr *sh = (void *) (s - sizeof(struct sdshdr));
    return sh->len;
}

static inline size_t sdsavail(const sds s) {
  struct sdshdr *sh = (void *) (s - sizeof(struct sdshdr));
    return sh->free;
}

sds sdsnewlen(const void *init, size_t initlen);
// sds sdsnew(const char *init);

void sdsfree(sds s);

sds sdsMakeRoomFor(sds s, size_t addlen);
sds sdscatlen(sds s, const void *t, size_t len);
sds sdscpylen(sds s, const char *t, size_t len);

int main(void) {
    sds x = sdsnewlen("foo", 3);
    assert(sdslen(x) == 3);

  // adding test-case for sdscatlen
    x = sdscatlen(x, "bar", 3);
    assert(sdslen(x) == 6);
    assert(strcmp(x, "foobar") == 0);

  // adding test-case for sdscpylen
    x = sdscpylen(x, "a", 1);
    assert(sdslen(x) == 1);
    assert(strcmp(x, "a") == 0);

    return 0;
}

sds sdsnewlen(const void *init, size_t initlen) {
  struct sdshdr *sh;

    sh = malloc(sizeof(struct sdshdr) + initlen + 1);
    //用malloc对柔性数组来初始化，用sizeof求struct大小的时候柔性数组是不算的
    
    if (sh == NULL) {
    return NULL;
    }

    sh->len = initlen;
    sh->free = 0;

    if (initlen && init) {
    memcpy(sh->buf, init, initlen);
    }

    sh->buf[initlen] = '\0';

  return (char *) sh->buf;
}

void sdsfree(sds s) {
    if (s == NULL) {
    return;
    }

    free(s - sizeof(struct sdshdr));
}

sds sdsMakeRoomFor(sds s, size_t addlen) {
  struct sdshdr *sh, *newsh;
  size_t free = sdsavail(s);
  size_t len, newlen;

  if (free >= addlen) {
    return s;
  }

  len = sdslen(s);
  sh = (void *) (s - sizeof(struct sdshdr));
  newlen = (len + addlen) * 2;
  newsh = realloc(sh, sizeof(struct sdshdr) + newlen + 1);
  if (newsh == NULL) {
    return NULL;
  }

  newsh->free = newlen - len;
  return newsh->buf;
}

sds sdscatlen(sds s, const void *t, size_t len) {
  struct sdshdr *sh;
  size_t curlen = sdslen(s);

  s = sdsMakeRoomFor(s, len);
  if (s == NULL) {
    return NULL;
  }

  sh = (void *) (s - sizeof(struct sdshdr));
  memcpy(s + curlen, t, len);
  sh->len = curlen + len;
  sh->free = sh->free - len;
  s[curlen + len] = '\0';

  return s;
}

sds sdscpylen(sds s, const char *t, size_t len) {
  struct sdshdr *sh = (void *) (s - sizeof(struct sdshdr));
  size_t totlen = sh->free + sh->len;

  if (totlen < len) {
    s = sdsMakeRoomFor(s, len - sh->len);
    if (s == NULL) {
      return NULL;
    }
    sh = (void *) (s - sizeof(struct sdshdr));
    totlen = sh->free + sh->len;
  }

  memcpy(s, t, len);
  s[len] = '\0';
  sh->len = len;
  sh->free = totlen - len;

  return s;
}