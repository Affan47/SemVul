__zzip_fetch_disk_trailer(int fd, zzip_off_t filesize,
                          struct _disk_trailer *_zzip_restrict trailer,
                          zzip_plugin_io_t io)
{
#ifdef DEBUG
#define return(val) { e=val; HINT2("%s", zzip_strerror(e)); goto cleanup; }
#else
#define return(val) { e=val; goto cleanup; }
#endif
    register int e;

#ifndef _LOWSTK
    auto char buffer[2 * ZZIP_BUFSIZ];
    char *buf = buffer;
#else
    char *buf = malloc(2 * ZZIP_BUFSIZ);
#endif
    zzip_off_t offset = 0;
    zzip_ssize_t maplen = 0;
    char *fd_map = 0;

    if (! trailer)
        { return(EINVAL); }

    if (filesize < __sizeof(struct zzip_disk_trailer))
          { return(ZZIP_DIR_TOO_SHORT); }

    if (! buf)
        { return(ZZIP_OUTOFMEM); }

    offset = filesize;
    while (1)
    {
        register unsigned char *mapped;

        if (offset <= 0)
            { return(ZZIP_DIR_EDH_MISSING); }


        if (filesize - offset > 64 * 1024)
            { return(ZZIP_DIR_EDH_MISSING); }


        if (USE_MMAP && io->fd.sys)
        {
            zzip_off_t mapoff = offset;
            {
                zzip_ssize_t pagesize = _zzip_getpagesize(io->fd.sys);
                if (pagesize < ZZIP_BUFSIZ)
                    goto non_mmap;
                if (mapoff == filesize && filesize > pagesize)
                    mapoff -= pagesize;
                if (mapoff < pagesize)
                {
                    maplen = (zzip_ssize_t) mapoff + pagesize;
                    mapoff = 0;
                } else
                {
                    mapoff -= pagesize;
                    maplen = 2 * pagesize;
                    if ((zzip_ssize_t) mapoff & (pagesize - 1))
                    {
                        pagesize -= (zzip_ssize_t) mapoff & (pagesize - 1);
                        mapoff += pagesize;
                        maplen -= pagesize;
                    }
                }
                if (mapoff + maplen > filesize)
                    maplen = filesize - mapoff;
            }

            fd_map = _zzip_mmap(io->fd.sys, fd, mapoff, (zzip_size_t) maplen);
            if (fd_map == MAP_FAILED)
                goto non_mmap;
            mapped = (unsigned char *) fd_map;
            offset = mapoff;
            HINT3("mapped *%p len=%li", fd_map, (long) maplen);
        } else
        {
          non_mmap:
            fd_map = 0;
            {
                zzip_off_t pagesize = ZZIP_BUFSIZ;
                if (offset == filesize && filesize > pagesize)
                    offset -= pagesize;
                if (offset < pagesize)
                {
                    maplen = (zzip_ssize_t) offset + pagesize;
                    offset = 0;
                } else
                {
                    offset -= pagesize;
                    maplen = 2 * pagesize;
                    if ((zzip_ssize_t) offset & (pagesize - 1))
                    {
                        pagesize -= (zzip_ssize_t) offset & (pagesize - 1);
                        offset += pagesize;
                        maplen -= pagesize;
                    }
                }
                if (offset + maplen > filesize)
                    maplen = filesize - offset;
            }

            if (io->fd.seeks(fd, offset, SEEK_SET) < 0)
                { return(ZZIP_DIR_SEEK); }
            if (io->fd.read(fd, buf, (zzip_size_t) maplen) < maplen)
                { return(ZZIP_DIR_READ); }
            mapped = (unsigned char *) buf;
            HINT5("offs=$%lx len=%li filesize=%li pagesize=%i",
                  (long) offset, (long) maplen, (long) filesize, ZZIP_BUFSIZ);
        }

        {
            register unsigned char *end = mapped + maplen;
            register unsigned char *tail;
            for (tail = end - 1; (tail >= mapped); tail--)
            {
                if ((*tail == 'P') &&
                    end - tail >= __sizeof(struct zzip_disk_trailer) - 2 &&
                    zzip_disk_trailer_check_magic(tail))
                {
#                  ifndef ZZIP_DISK64_TRAILER


                    if (end - tail >= __sizeof(*trailer))
                    {
                        memcpy(trailer, tail, sizeof(*trailer));
                    } else
                    {
                        memcpy(trailer, tail, sizeof(*trailer) - 2);
                        trailer->z_comment[0] = 0;
                        trailer->z_comment[1] = 0;
                    }
#                  else
                    struct zzip_disk_trailer *orig =
                        (struct zzip_disk_trailer *) tail;
                    trailer->zz_tail = tail;
                    trailer->zz_entries = zzip_disk_trailer_localentries(orig);
                    trailer->zz_finalentries =
                        zzip_disk_trailer_finalentries(orig);
                    trailer->zz_rootseek = zzip_disk_trailer_rootseek(orig);
                    trailer->zz_rootsize = zzip_disk_trailer_rootsize(orig);
#                  endif

                    __fixup_rootseek(offset + tail - mapped, trailer);
                    { return(0); }
                } else if ((*tail == 'P') &&
                           end - tail >=
                           __sizeof(struct zzip_disk64_trailer) - 2
                           && zzip_disk64_trailer_check_magic(tail))
                {
#                  ifndef ZZIP_DISK64_TRAILER
                    return (ZZIP_DIR_LARGEFILE);
#                  else
                    struct zzip_disk64_trailer *orig =
                        (struct zzip_disk64_trailer *) tail;
                    trailer->zz_tail = tail;
                    trailer->zz_entries =
                        zzip_disk64_trailer_localentries(orig);
                    trailer->zz_finalentries =
                        zzip_disk64_trailer_finalentries(orig);
                    trailer->zz_rootseek = zzip_disk64_trailer_rootseek(orig);
                    trailer->zz_rootsize = zzip_disk64_trailer_rootsize(orig);
                    { return(0); }
#                  endif
                }
            }
        }

        if (USE_MMAP && fd_map)
        {
            HINT3("unmap *%p len=%li", fd_map, (long) maplen);
            _zzip_munmap(io->fd.sys, fd_map, (zzip_size_t) maplen);
            fd_map = 0;
        }
    }

  cleanup:
    if (USE_MMAP && fd_map)
    {
        HINT3("unmap *%p len=%li", fd_map, (long) maplen);
        _zzip_munmap(io->fd.sys, fd_map, (zzip_size_t) maplen);
    }
#   ifdef _LOWSTK
    free(buf);
#   endif
#   undef return
    return e;
}
