_tempfile_new(int size)
{
#ifdef HAVE_MMAN_H
   Tmp_Info *info;
   const char *tmppath;
   mode_t cur_umask;
   int len;

   info = malloc(sizeof(Tmp_Info));
   if (!info) return NULL;
   tmppath = getenv("TMP");
   if (!tmppath) tmppath = P_tmpdir;
   len = snprintf(NULL, 0, "%s/%sXXXXXX", tmppath, "elmcnpitem-");
   if (len < 0) goto on_error;
   len++;
   info->filename = malloc(len);
   if (!info->filename) goto on_error;
   snprintf(info->filename,len,"%s/%sXXXXXX", tmppath, "elmcnpitem-");
   cur_umask = umask(S_IRWXO | S_IRWXG);
   info->fd = mkstemp(info->filename);
   umask(cur_umask);
   if (info->fd < 0) goto on_error;
# ifdef __linux__
     {
        char *tmp;

        long pid;

        pid = (long)getpid();

        len = snprintf(NULL,0,"/proc/%li/fd/%i", pid, info->fd);
        len++;
        tmp = malloc(len);
        if (tmp)
          {
             snprintf(tmp,len, "/proc/%li/fd/%i", pid, info->fd);
             unlink(info->filename);
             free(info->filename);
             info->filename = tmp;
          }
     }
# endif
   cnp_debug("filename is %s\n", info->filename);
   if (size < 1) goto on_error;

   if (ftruncate(info->fd, size))
     {
        perror("ftruncate");
        goto on_error;
     }
   eina_mmap_safety_enabled_set(EINA_TRUE);
   info->map = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, info->fd, 0);
   if (info->map == MAP_FAILED)
     {
        perror("mmap");
        goto on_error;
     }
   return info;

 on_error:
   if (info->fd >= 0) close(info->fd);
   info->fd = -1;

   info->map = NULL;
   info->len = 0;
   free(info);
   return NULL;
#else
   (void) size;
   return NULL;
#endif
}
