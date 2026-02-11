splot_add_plot_labels (splotd *sp, GdkDrawable *drawable, ggobid *gg)
{
  displayd *display = (displayd *) sp->displayptr;
  cpaneld *cpanel = &display->cpanel;
  GGobiData *d = display->d;
  colorschemed *scheme = gg->activeColorScheme;

  gboolean proceed = (cpanel->pmode == XYPLOT ||
                      cpanel->pmode == P1PLOT ||
                      cpanel->pmode == EXTENDED_DISPLAY_PMODE);
  if (!proceed)
    return;

  gdk_gc_set_foreground (gg->plot_GC, &scheme->rgb_accent);

  if(GGOBI_IS_EXTENDED_SPLOT(sp)) {
    void (*f)(splotd *, GdkDrawable*, ggobid*);
    f =  GGOBI_EXTENDED_SPLOT_GET_CLASS(sp)->add_plot_labels;
    if(f) {
      f(sp, drawable, gg);
      return;
    }

  }


  if(GGOBI_IS_EXTENDED_DISPLAY(display)) {
    void (*f)(displayd *, splotd *, GdkDrawable*, GGobiData *, ggobid*);
    f =  GGOBI_EXTENDED_DISPLAY_GET_CLASS(display)->add_plot_labels;
    if(f)
      f(display, sp, drawable, d, gg);
  }

}
