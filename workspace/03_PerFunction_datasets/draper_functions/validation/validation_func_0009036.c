sge_ls_status(lListElem *this_ls)
{
   fd_set writefds;
   int ret;
   int higest_fd;

   DENTER(TOP_LAYER, "sge_ls_status");

   if (sge_ls_get_pid(this_ls) == -1) {
      DRETURN(LS_NOT_STARTED);
   }


   FD_ZERO(&writefds);
   higest_fd = fileno((FILE *) lGetRef(this_ls, LS_in));
   FD_SET(higest_fd, &writefds);


   ret = select(higest_fd + 1, NULL, &writefds, NULL, NULL);

   if (ret <= 0) {
      DRETURN(LS_BROKEN_PIPE);
   }

   DRETURN(LS_OK);
}
