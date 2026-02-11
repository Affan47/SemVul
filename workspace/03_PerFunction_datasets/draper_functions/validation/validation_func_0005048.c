gt_flushfmindex2file(FILE *fp,
                         Fmindex *fmindex,
                         bool storeindexpos,
                         GtError *err)
{
  Fmindexwithoptions fmwithoptions;

  gt_error_check(err);
  fmwithoptions.fmptr = fmindex;
  fmwithoptions.storeindexpos = storeindexpos;
  return gt_mapspec_write(assignfmmapspecification,fp,
                          (void *) &fmwithoptions,fmindex->sizeofindex,err);
}
