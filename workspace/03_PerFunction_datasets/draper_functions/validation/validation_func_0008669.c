gt_graphics_get_text_width(GtGraphics *g, const char *text)
{
  double ret;
  gt_assert(g && g->c_class && text);
  gt_rwlock_rdlock(g->pvt->lock);
  ret = g->c_class->get_text_width(g, text);
  gt_rwlock_unlock(g->pvt->lock);
  return ret;
}
