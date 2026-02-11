bgav_rmff_header_destroy(bgav_rmff_header_t * h)
  {
  int i;
  if(h->streams)
    {
    for(i = 0; i < h->num_streams; i++)
      {
      bgav_rmff_indx_free(&h->streams[i].indx);
      bgav_rmff_mdpr_free(&h->streams[i].mdpr);
      }
    free(h->streams);
    }
  bgav_rmff_cont_free(&h->cont);
  free(h);
  }
