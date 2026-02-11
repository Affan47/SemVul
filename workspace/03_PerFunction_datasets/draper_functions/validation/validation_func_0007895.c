on_find(const gar_fstat_t *fstat, void *ud, jmp_buf env) {
  const gar_zstat_t *zstat = (const gar_zstat_t *)fstat;
  find_ud_t *fud = (find_ud_t *)ud;
  ((void)env);

  if (strcmp(fud->fname, zstat->fstat.fname) == 0) {
    *(fud->zstat) = *zstat;
    fud->zstat->fstat.fname = NULL;
    return 1;
  } else {
    return 0;
  }
}
