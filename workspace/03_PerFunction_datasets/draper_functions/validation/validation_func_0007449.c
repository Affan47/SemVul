chk_get_mcd_or_fd(struct expr_t *fdxp, int32 *is_mcd)
{
 word32 fd;
 struct xstk_t *xsp;


 *is_mcd = FALSE;
 xsp = __eval_xpr(fdxp);
 if (xsp->bp[0] != 0L) { errno = EBADF; __pop_xstk(); return(-1); }

 fd = xsp->ap[0];
 __pop_xstk();


 if ((fd & FIO_MSB) == 0)
  {
   *is_mcd = TRUE;
   return(fd);
  }

 fd &= ~(FIO_FD);
 if (fd >= FOPEN_MAX) { errno = EBADF; return(-1); }
 if (__fio_fdtab[fd] == NULL) { errno = EBADF; return(-1); }
 return(fd);
}
