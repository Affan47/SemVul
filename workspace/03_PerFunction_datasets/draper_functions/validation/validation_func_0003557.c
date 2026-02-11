gt_contfinder_write_sorted_seqnums(GtContfinder *contfinder, char* path,
    GtError *err)
{
  int had_err = 0;
  GtFile *file;
  file = gt_file_new(path, "wb", err);
  if (file == NULL)
    had_err = -1;
  if (!had_err)
  {
    had_err = gt_contfinder_write_seqnums(contfinder, true, file, err);
  }
  gt_file_delete(file);
  return had_err;
}
