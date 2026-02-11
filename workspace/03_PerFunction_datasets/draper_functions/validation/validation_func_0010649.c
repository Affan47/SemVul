gt_hpol_processor_process_hpol_end(GtHpolProcessor *hpp,
    GtUchar c, unsigned long endpos, unsigned long hlen)
{
  bool edited = false;
  gt_disc_distri_add(hpp->hdist, hlen);
  hpp->nof_h++;
  if (hlen > hpp->hlen_max)
    hpp->hlen_max = hlen;
  if (hpp->adjust_s_hlen)
  {
    char ch = gt_alphabet_decode(hpp->alpha, c);
    unsigned long a_supp_max = ULONG_MAX, a_supp = 0, piled, r_supp = 0, a_hlen,
                  r_supp_min = 0;
    gt_aligned_segments_pile_move_over_position(hpp->asp, endpos + 1UL);
    piled = gt_aligned_segments_pile_size(hpp->asp);
    if (piled >= hpp->covmin)
    {
      gt_hpol_processor_determine_alternative_consensus(hpp, ch,
          endpos + 1UL - hlen, hlen, &a_hlen, &a_supp, &piled,
          &r_supp);
      a_supp_max = (unsigned long)(hpp->altmax * (double)piled);
      r_supp_min = (unsigned long)(hpp->refmin * (double)piled);
      if (r_supp < piled && r_supp >= r_supp_min && a_supp <= a_supp_max)
      {
        edited = gt_hpol_processor_adjust_hlen_of_all_segments(hpp->asp, ch,
            endpos + 1UL - hlen, piled, hlen, r_supp, a_hlen, a_supp,
            hpp->clenmax, hpp->allow_partial, hpp->allow_multiple,
            hpp->read_hmin, hpp->mapqmin, hpp->output_stats, hpp->outfp_stats,
            hpp->processed_segments, hpp->output_multihit_stats);
      }
    }
  }
  if (edited)
  {
    hpp->nof_h_e++;
    gt_disc_distri_add(hpp->hdist_e, hlen);
  }
}
