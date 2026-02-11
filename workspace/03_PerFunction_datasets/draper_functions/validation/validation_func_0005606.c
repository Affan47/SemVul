cdio_read_audio_sectors (const CdIo_t *p_cdio, void *p_buf, lsn_t i_lsn,
                         uint32_t i_blocks)
{
  check_lsn_blocks(i_lsn, i_blocks);

  if (0 == i_blocks) return DRIVER_OP_SUCCESS;

  if (p_cdio->op.read_audio_sectors)
    return (p_cdio->op.read_audio_sectors) (p_cdio->env, p_buf, i_lsn,
                                            i_blocks);
  return DRIVER_OP_UNSUPPORTED;
}
