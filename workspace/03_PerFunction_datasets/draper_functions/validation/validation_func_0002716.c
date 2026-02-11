canvas_fiducial_mark_changed_cb(AmitkFiducialMark * fm, gpointer data) {

  AmitkCanvas * canvas = data;

  g_return_if_fail(AMITK_IS_CANVAS(canvas));
  g_return_if_fail(AMITK_IS_FIDUCIAL_MARK(fm));
  canvas_add_object_update(canvas, AMITK_OBJECT(fm));

  return;
}
