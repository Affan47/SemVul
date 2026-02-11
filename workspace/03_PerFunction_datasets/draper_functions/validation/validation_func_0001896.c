gdkwindow_gdk_window_get_pointer(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj window_scm;
  GdkDrawable* window;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("gdk-window-get-pointer");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  window_scm = SCM_SUBRARGS[0];
  if (!SCM_GDK_DRAWABLE_P(window_scm)) Scm_Error("<gdk-drawable> required, but got %S", window_scm);
  window = SCM_GDK_DRAWABLE(window_scm);
  {
gint x, y; GdkModifierType mask; GdkDrawable *win;
  win = gdk_window_get_pointer(window, &x, &y, &mask);
  if (win) {
    SCM_RETURN4(SCM_MAKE_GDK_DRAWABLE(win),
                Scm_MakeInteger(x), Scm_MakeInteger(y),
                Scm_MakeInteger(mask));
  } else {
    SCM_RETURN4(SCM_FALSE, SCM_FALSE, SCM_FALSE, SCM_FALSE);
  }
  }
}
