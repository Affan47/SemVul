on_timer_poll(gpointer   user_data)
{
  t_global_stb *gstb;
  GapCmeGlobalParams *gpp;

  if(gap_debug) printf("\non_timer_poll: START\n");

  gstb = (t_global_stb *)user_data;
  gpp = gap_cme_main_get_global_params();

  if(gstb)
  {
     g_source_remove(gstb->poll_timertag);
     if(gstb->stb_job_done)
     {
       gstb->poll_timertag = -1;
       gstb->stb_job_done = FALSE;
       p_storybord_job_finished(gpp, gstb);
     }
     else
     {
       if(gstb->poll_timertag >= 0)
       {


          p_status_progress(gpp, gstb);

          gstb->poll_timertag =
            (gint32) g_timeout_add (500, (GSourceFunc)on_timer_poll, gstb);
       }
     }
  }
}
