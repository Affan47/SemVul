calc_calibration(uint8_t *caldata, uint8_t *scanline[],
			     int pixels)
{
  int i,j;
  int sorted[STRIPS];

  DBG(23, ".calc_calibration...\n");
  for (i=0; i<pixels; i++) {
    int q1, q3;
    int bot, top;
    int sum = 0;
    int count = 0;

    sort_values(sorted, scanline, i);
    q1 = sorted[STRIPS / 4];
    q3 = sorted[STRIPS * 3 / 4];
    bot = q1 - 3 * (q3 - q1) / 2;
    top = q3 + 3 * (q3 - q1) / 2;

    for (j=0; j<STRIPS; j++) {
      if ((sorted[j] >= bot) && (sorted[j] <= top)) {
	sum += sorted[j];
	count++;
      }
    }
    if (count)
      caldata[i] = (sum + (count / 2)) / count;
    else {
      DBG(23, "zero: i=%d b/t=%d/%d ", i, bot, top);
      if (DBG_LEVEL >= 23) {
	MDBG_INIT("");
	for (j=0; j<STRIPS; j++) MDBG_ADD(" %3d", sorted[j]);
	MDBG_FINISH(23);
      }
      caldata[i] = 0;
    }
  }
}
