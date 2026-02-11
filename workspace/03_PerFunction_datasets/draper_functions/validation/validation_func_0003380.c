mfwrite(int format, int ntracks, int division, FILE *fp) {

  int i;
  void mf_w_track_chunk(), mf_w_header_chunk();

  if (Mf_putc == NULLFUNC)
    mferror("mfmf_write() called without setting Mf_putc");
  if (Mf_wtrack == NULLFUNC)
    mferror("mfmf_write() called without setting Mf_mf_writetrack");
  mf_w_header_chunk(format, ntracks, division);
  if (format == 1 && ( Mf_wtempotrack )) {
    mf_w_track_chunk(-1, fp, Mf_wtempotrack);
    ntracks--;
  }
  for(i = 0; i < ntracks; i++)
    mf_w_track_chunk(i, fp, Mf_wtrack);
}
