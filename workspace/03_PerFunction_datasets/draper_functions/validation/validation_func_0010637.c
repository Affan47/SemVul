psit_write(void)
{
  int short_length;

  if (snlen) {
    short_length = atoi(snlen);
  } else {
    short_length = 10;
  }

  mkshort_handle = mkshort_new_handle();

  setshort_length(mkshort_handle, short_length);
  setshort_whitespace_ok(mkshort_handle, 0);

  psit_track_state = 2;

  if (global_opts.objective == wptdata) {
    waypt_disp_all(psit_waypoint_w_wrapper);
  }
  if (global_opts.objective == rtedata) {
    route_disp_all(psit_routehdr_w_wrapper, psit_noop, psit_waypoint_w_wrapper);
  }
  if (global_opts.objective == trkdata) {
    track_disp_all(psit_trackhdr_w_wrapper, psit_noop, psit_trackdatapoint_w_wrapper);
  }

  mkshort_del_handle(&mkshort_handle);

}
