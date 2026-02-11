logonfail(UPSINFO *ups, int ok)
{
   int lgnfd;

   unlink(ups->nologinpath);

   if (ok == 0 &&
       ((lgnfd = open(ups->nologinpath, O_CREAT | O_WRONLY, 0644)) >= 0)) {
      write(lgnfd, POWERFAIL, strlen(POWERFAIL));
      close(lgnfd);
   }
}
