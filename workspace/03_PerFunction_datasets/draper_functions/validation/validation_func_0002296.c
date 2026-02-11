determineAGSscore(GthAGS *ags, double sortagswf)
{
  GthDbl average_exon_score              = 0.0,
         average_splice_site_probability = 0.0;
  unsigned long i, numofexons = gt_array_size(ags->exons);
  GthSpliceSiteProb *splicesiteprob;
  gt_assert(numofexons > 0);

  if (numofexons == 1) {


    ags->overallscore = ((GthExonAGS*) gt_array_get_first(ags->exons))->score;
  }
  else {


    for (i = 0; i < numofexons; i++) {

      average_exon_score += ((GthExonAGS*) gt_array_get(ags->exons, i))->score;
      if (i > 0) {
        splicesiteprob = gt_array_get(ags->splicesiteprobs, i-1);
        average_splice_site_probability += splicesiteprob->donorsiteprob;
        average_splice_site_probability += splicesiteprob->acceptorsiteprob;
      }
    }

    average_exon_score              /= numofexons;
    average_splice_site_probability /= (2 * (numofexons - 1));


    ags->overallscore = (sortagswf * average_exon_score +
                         average_splice_site_probability) /
                        (sortagswf + 1.0);

  }
}
