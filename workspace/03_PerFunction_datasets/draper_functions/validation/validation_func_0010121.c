gtk_plot_get_axis (GtkPlot *plot, GtkPlotAxisPos axis)
{
  GtkPlotAxis *aux = NULL;

  switch(axis){
    case GTK_PLOT_AXIS_LEFT:
         aux = plot->left;
         break;
    case GTK_PLOT_AXIS_RIGHT:
         aux = plot->right;
         break;
    case GTK_PLOT_AXIS_TOP:
         aux = plot->top;
         break;
    case GTK_PLOT_AXIS_BOTTOM:
         aux = plot->bottom;
         break;
  }
  return aux;
}
