ftfile_add_tail(struct ftfile_entries *fte, char *fname, off_t size,
  u_int32 start)
{
  struct ftfile_entry *n1;

  if (!(n1 = ftfile_entry_new(strlen(fname)))) {
    fterr_warnx("ftfile_entry_new(): failed");
    return -1;
  }

  n1->size = size;
  n1->start = start;
  strcpy(n1->name, fname);

  FT_TAILQ_INSERT_TAIL(&fte->head, n1, chain);
  fte->num_files ++;
  fte->num_bytes += size;

  return 0;

}
