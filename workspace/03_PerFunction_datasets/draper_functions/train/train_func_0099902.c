gtkwidget_gtk_widget_render_icon(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj widget_scm;
  GtkWidget* widget;
  ScmObj stock_id_scm;
  const gchar * stock_id;
  ScmObj size_scm;
  int size;
  ScmObj detail_scm;
  const gchar * detail;
  ScmObj SCM_SUBRARGS[4];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-widget-render-icon");
  for (SCM_i=0; SCM_i<4; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  widget_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_WIDGET_P(widget_scm)) Scm_Error("<gtk-widget> required, but got %S", widget_scm);
  widget = SCM_GTK_WIDGET(widget_scm);
  stock_id_scm = SCM_SUBRARGS[1];
  if (!SCM_STRINGP(stock_id_scm)) Scm_Error("<const-gchar*> required, but got %S", stock_id_scm);
  stock_id = CONST_GCHAR_PTR(stock_id_scm);
  size_scm = SCM_SUBRARGS[2];
  if (!SCM_INTEGERP(size_scm)) Scm_Error("C integer required, but got %S", size_scm);
  size = Scm_GetInteger(size_scm);
  detail_scm = SCM_SUBRARGS[3];
  if (!SCM_STRINGP(detail_scm)) Scm_Error("<const-gchar*> required, but got %S", detail_scm);
  detail = CONST_GCHAR_PTR(detail_scm);
  {
{
GdkPixbuf* SCM_RESULT;
SCM_RESULT = gtk_widget_render_icon(widget, stock_id, size, detail);
SCM_RETURN(SCM_MAKE_GDK_PIXBUF(SCM_RESULT));
}
  }
}
