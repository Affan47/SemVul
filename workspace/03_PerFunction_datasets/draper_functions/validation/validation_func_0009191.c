ifoFree_VTS_ATRT(ifo_handle_t *ifofile) {
  if(!ifofile)
    return;

  if(ifofile->vts_atrt) {
    free(ifofile->vts_atrt->vts);
    free(ifofile->vts_atrt->vts_atrt_offsets);
    free(ifofile->vts_atrt);
    ifofile->vts_atrt = 0;
  }
}
