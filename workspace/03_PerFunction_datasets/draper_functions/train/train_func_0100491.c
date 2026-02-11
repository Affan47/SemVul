gf_dump_config_flags (int fd)
{
        int ret = 0;

        ret = write (fd, "configuration details:\n", 23);
        if (ret == -1)
                goto out;


#ifdef HAVE_ARGP
        ret = write (fd, "argp 1\n", 7);
        if (ret == -1)
                goto out;
#endif


#ifdef HAVE_BACKTRACE
        ret = write (fd, "backtrace 1\n", 12);
        if (ret == -1)
                goto out;
#endif


#ifdef HAVE_BDB_CURSOR_GET
        ret = write (fd, "bdb->cursor->get 1\n", 19);
        if (ret == -1)
                goto out;
#endif


#ifdef HAVE_DB_H
        ret = write (fd, "db.h 1\n", 7);
        if (ret == -1)
                goto out;
#endif


#ifdef HAVE_DLFCN_H
        ret = write (fd, "dlfcn 1\n", 8);
        if (ret == -1)
                goto out;
#endif


#ifdef HAVE_FDATASYNC
        ret = write (fd, "fdatasync 1\n", 12);
        if (ret == -1)
                goto out;
#endif


#ifdef HAVE_LIBPTHREAD
        ret = write (fd, "libpthread 1\n", 13);
        if (ret == -1)
                goto out;
#endif


#ifdef HAVE_LLISTXATTR
        ret = write (fd, "llistxattr 1\n", 13);
        if (ret == -1)
                goto out;
#endif


#ifdef HAVE_SET_FSID
        ret = write (fd, "setfsid 1\n", 10);
        if (ret == -1)
                goto out;
#endif


#ifdef HAVE_SPINLOCK
        ret = write (fd, "spinlock 1\n", 11);
        if (ret == -1)
                goto out;
#endif


#ifdef HAVE_SYS_EPOLL_H
        ret = write (fd, "epoll.h 1\n", 10);
        if (ret == -1)
                goto out;
#endif


#ifdef HAVE_SYS_EXTATTR_H
        ret = write (fd, "extattr.h 1\n", 12);
        if (ret == -1)
                goto out;
#endif


#ifdef HAVE_SYS_XATTR_H
        ret = write (fd, "xattr.h 1\n", 10);
        if (ret == -1)
                goto out;
#endif


#ifdef HAVE_STRUCT_STAT_ST_ATIM_TV_NSEC
        ret = write (fd, "st_atim.tv_nsec 1\n", 18);
        if (ret == -1)
                goto out;
#endif


#ifdef HAVE_STRUCT_STAT_ST_ATIMESPEC_TV_NSEC
        ret = write (fd, "st_atimespec.tv_nsec 1\n",23);
        if (ret == -1)
                goto out;
#endif


#ifdef PACKAGE_STRING
        {
                char msg[128];
                sprintf (msg, "package-string: %s\n", PACKAGE_STRING);
                ret = write (fd, msg, strlen (msg));
                if (ret == -1)
                        goto out;
        }
#endif

out:
        return;
}
