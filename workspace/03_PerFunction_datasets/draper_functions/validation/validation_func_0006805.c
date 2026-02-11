_filter_repeats(MPLS_PL *pl, unsigned repeats)
{
    unsigned ii;

    for (ii = 0; ii < pl->list_count; ii++) {
      MPLS_PI *pi;

      pi = &pl->play_item[ii];

      if (_find_repeats(pl, pi->clip[0].clip_id, pi->in_time, pi->out_time) > repeats) {
        return 0;
      }
    }
    return 1;
}
