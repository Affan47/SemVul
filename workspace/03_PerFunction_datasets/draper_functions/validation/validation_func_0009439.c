goo_canvas_text_update  (GooCanvasItemSimple *simple,
			 cairo_t             *cr)
{
  GooCanvasText *text = (GooCanvasText*) simple;
  GooCanvasTextPrivate *priv = goo_canvas_text_get_private (text);
  PangoLayout *layout;


  text->layout_width = text->text_data->width;


  layout = goo_canvas_text_create_layout (simple->simple_data, text->text_data,
					  text->layout_width, cr,
					  &simple->bounds, NULL, NULL);
  g_object_unref (layout);


  if (priv->height > 0.0)
    simple->bounds.y2 = simple->bounds.y1 + priv->height;
}
