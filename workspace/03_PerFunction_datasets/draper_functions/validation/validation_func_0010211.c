ydstatCreate(int vlistID)
{
  int dayoy;

  YDAY_STATS *stats = (YDAY_STATS *) malloc(sizeof(YDAY_STATS));

  for ( dayoy = 0; dayoy < NDAY; dayoy++ )
    {
      stats->vdate[dayoy] = 0;
      stats->vtime[dayoy] = 0;
      stats->vars1[dayoy] = NULL;
      stats->vars2[dayoy] = NULL;
      stats->nsets[dayoy] = 0;
    }
  stats->vlist = vlistID;

  return stats;
}
