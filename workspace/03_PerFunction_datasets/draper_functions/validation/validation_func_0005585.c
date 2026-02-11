_read_mode2_sector_cdrdao (void *user_data, void *data, lsn_t lsn,
			 bool b_form2)
{
  _img_private_t *env = user_data;
  int ret;
  char buf[CDIO_CD_FRAMESIZE_RAW] = { 0, };
  long unsigned int i_off = lsn * CDIO_CD_FRAMESIZE_RAW;


  ret = cdio_stream_seek (env->tocent[0].data_source, i_off, SEEK_SET);
  if (ret!=0) return ret;

  ret = cdio_stream_read (env->tocent[0].data_source, buf,
			  CDIO_CD_FRAMESIZE_RAW, 1);
  if (ret==0) return ret;


  if (b_form2)
    memcpy (data, buf + CDIO_CD_SYNC_SIZE + CDIO_CD_HEADER_SIZE,
	    M2RAW_SECTOR_SIZE);
  else
    memcpy (data, buf + CDIO_CD_XA_SYNC_HEADER, CDIO_CD_FRAMESIZE);

  return DRIVER_OP_SUCCESS;
}
