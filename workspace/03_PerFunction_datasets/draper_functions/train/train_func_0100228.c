computeexonscore(Exonnode *node)
{
  unsigned long i, maxlength = 0;
  GthDbl maxscore = DBL_MIN;
  Exonscoreinfo *exonscoreinfo;


  for (i = 0; i < gt_array_size(node->exonscores); i++) {
    exonscoreinfo = gt_array_get(node->exonscores, i);
    if (exonscoreinfo->lengthofscoringexon > maxlength)
      maxlength = exonscoreinfo->lengthofscoringexon;
  }


  for (i = 0; i < gt_array_size(node->exonscores); i++) {
    exonscoreinfo = gt_array_get(node->exonscores, i);
    if ((exonscoreinfo->lengthofscoringexon
        + SAVE_EXONSCORE_ALLOWED_DIFFERENCE >= maxlength) &&
        (exonscoreinfo->exonscore > maxscore)) {
      maxscore = exonscoreinfo->exonscore;
    }
  }

  return maxscore;
}
