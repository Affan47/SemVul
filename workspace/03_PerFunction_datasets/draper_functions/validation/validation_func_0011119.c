focusblur_brush_destroy (FblurBrush **brush)
{
  g_return_if_fail (brush != NULL);

  if (*brush)
    {
      g_free ((*brush)->name);
      g_free ((*brush)->data);
      g_free (*brush);
      *brush = NULL;
    }
}
