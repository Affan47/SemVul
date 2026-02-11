button_release_cb (GtkWidget * w, GdkEventButton * event, splotd * sp)
{
  gboolean retval = true;
  ggobid *gg = GGobiFromSPlot (sp);
  GdkModifierType state;
  displayd *dsp = sp->displayptr;
  cpaneld *cpanel = &dsp->cpanel;

  gg->buttondown = 0;

  gdk_window_get_pointer (w->window, &sp->mousepos.x, &sp->mousepos.y,
                          &state);

  gdk_pointer_ungrab (event->time);
  disconnect_motion_signal (sp);

  if (!cpanel->scale.updateAlways_p) {
    displayd *display = sp->displayptr;

    splot_plane_to_screen (display, &display->cpanel, sp, gg);
    ruler_ranges_set (false, gg->current_display, sp, gg);
    splot_redraw (sp, FULL, gg);
  }
  else {
    splot_redraw (sp, QUICK, gg);
  }

  return retval;
}
