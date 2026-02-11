format3(struct fmtargs *args)
{
  struct fts3rec_offsets fo;
  struct fopd32 cur;
  struct ftchash *ftch;
  struct ftchash_rec_c32 ftch_recc32, *ftch_recc32p;
  struct ftver ftv;
  struct fopd total;
  char *rec;
  u_int32 hash;

  ftio_get_ver(&args->ftio, &ftv);

  if (ftio_check_xfield(&args->ftio, FT_XFIELD_DPKTS |
    FT_XFIELD_DOCTETS | FT_XFIELD_FIRST | FT_XFIELD_LAST)) {
    fterr_warnx("Flow record missing required field for format.");
    return -1;
  }

  fts3rec_compute_offsets(&fo, &ftv);

  bzero(&ftch_recc32, sizeof ftch_recc32);

  bzero(&total, sizeof total);

  if (!(ftch = ftchash_new(65536, sizeof (struct ftchash_rec_c32), 4, 65536))) {
    fterr_warnx("ftchash_new(): failed");
    return -1;
  }

  cur.flows = 1;

  while ((rec = ftio_read(&args->ftio))) {

    CUR_GET_PLUS_FLOWS;

    TOTAL_INC;

    ftch_recc32.c32 = cur.octets;

    hash = (ftch_recc32.c32>>16) ^ (ftch_recc32.c32 & 0xFFFF);

    if (!(ftch_recc32p = ftchash_update(ftch, &ftch_recc32, hash))) {
      fterr_warnx("ftch_update(): failed");
      ftchash_free(ftch);
      return -1;
    }

    STAT_INCP(ftch_recc32p);

  }

  chash_c32_dump(ftch, args->cc, args->sort_order, args->options, &total,
    "Octets  ", (char*)0L);

  ftchash_free(ftch);

  return 0;

}
