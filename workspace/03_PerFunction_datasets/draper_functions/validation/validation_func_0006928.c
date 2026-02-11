on_currently_loading_frame (GdkPixbufAnimationIter *anim_iter)
{
  GdkPixbufSimpleAnimIter *iter;

  iter = GDK_PIXBUF_SIMPLE_ANIM_ITER (anim_iter);

  return iter->current_frame == NULL || iter->current_frame->next == NULL;
}
