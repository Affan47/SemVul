mmc_get_disc_last_lsn ( const CdIo_t *p_cdio )
{
  mmc_cdb_t cdb = {{0, }};
  uint8_t buf[12] = { 0, };

  lsn_t retval = 0;
  int i_status;


  CDIO_MMC_SET_COMMAND(cdb.field, CDIO_MMC_GPCMD_READ_TOC);

  cdb.field[1] = 0;


  cdb.field[2] = CDIO_MMC_READTOC_FMT_TOC;

  CDIO_MMC_SET_START_TRACK(cdb.field, CDIO_CDROM_LEADOUT_TRACK);

  CDIO_MMC_SET_READ_LENGTH16(cdb.field, sizeof(buf));

  i_status = mmc_run_cmd(p_cdio, mmc_timeout_ms, &cdb, SCSI_MMC_DATA_READ,
                         sizeof(buf), buf);

  if (i_status) return CDIO_INVALID_LSN;

  {
    int i;
    for (i = 8; i < 12; i++) {
      retval <<= 8;
      retval += buf[i];
    }
  }

  return retval;
}
