ifoFree_PGC(pgc_t **pgc) {
  if(pgc && *pgc && (--(*pgc)->ref_count) <= 0) {
    ifoFree_PGC_COMMAND_TBL((*pgc)->command_tbl);
    if((*pgc)->program_map)
      free((*pgc)->program_map);
    if((*pgc)->cell_playback)
      free((*pgc)->cell_playback);
    if((*pgc)->cell_position)
      free((*pgc)->cell_position);
    free(*pgc);
  }
  if (pgc) {
    *pgc = NULL;
  }
}
