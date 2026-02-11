Synthesize (el_sample_t **bufs, el_nframes_t len) {
  if (bufs == 0)
    return 0;

  if (combirateshift != 1.0) {


    double endpos = tempbuf_pos + combirateshift * len;


    el_nframes_t endpos_withpad = (el_nframes_t) endpos + 1;
    if (tempbufs == 0 || endpos_withpad >= tempbufslen) {
      fprintf(stderr,"ELASTIN: ERROR: Tempbufs not allocated or not big enough"
	      " for synthesize: combirateshift: %.2f tempbufslen: %d "
	      "tempbufs: %p!\n",
	      combirateshift,tempbufslen,tempbufs);


      return Synthesize_TS(bufs,len);
    }


    el_sample_t *tempbufs_tmp[d->numch];
    for (int ch = 0; ch < d->numch; ch++)
      tempbufs_tmp[ch] = &(tempbufs[ch][tempbuf_filled]);
    el_nframes_t tofill = endpos_withpad - tempbuf_filled + 1;

    if (tofill < 0)
      tofill = 0;

    el_nframes_t ts_outlen = Synthesize_TS(tempbufs_tmp,tofill);


    char end = 0;
    el_nframes_t ret;
    if (ts_outlen != tofill) {


      end = 1;
      ret = Synthesize_RT(tempbufs,bufs,len,1,ts_outlen + tempbuf_filled);
    } else

      ret = Synthesize_RT(tempbufs,bufs,len);

    if (end) {
      tempbuf_pos = 0.0;
      tempbuf_filled = 0;
    } else {


      el_nframes_t endpos_d1 = (el_nframes_t) endpos;
      tempbuf_pos = endpos - endpos_d1;


      tempbuf_filled = endpos_withpad - endpos_d1 + 1;
      for (el_nframes_t n = 0; n < tempbuf_filled; n++)
	for (int ch = 0; ch < d->numch; ch++)
	  tempbufs[ch][n] = tempbufs[ch][endpos_d1 + n];


    }

    return ret;
  } else {
    if (tempbufs != 0 && tempbuf_filled != 0) {


      el_sample_t *bufs_tmp[d->numch];
      for (int ch = 0; ch < d->numch; ch++) {
	memcpy(&(bufs[ch][0]),&(tempbufs[ch][0]),
	       tempbuf_filled*sizeof(el_sample_t));
	bufs_tmp[ch] = &(bufs[ch][tempbuf_filled]);
      }


      el_nframes_t ret = Synthesize_TS(bufs_tmp,len - tempbuf_filled)
	+ tempbuf_filled;


      tempbuf_filled = 0;

      return ret;
    } else

      return Synthesize_TS(bufs,len);
  }
}
