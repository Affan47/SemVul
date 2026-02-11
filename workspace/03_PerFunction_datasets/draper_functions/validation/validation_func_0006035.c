gimp_ruler_style_updated (GtkWidget *widget)
{
  GimpRulerPrivate *priv = GIMP_RULER_GET_PRIVATE (widget);

  GTK_WIDGET_CLASS (gimp_ruler_parent_class)->style_updated (widget);

  gtk_widget_style_get (widget,
                        "font-scale", &priv->font_scale,
                        NULL);

  if (priv->layout)
    {
      g_object_unref (priv->layout);
      priv->layout = NULL;
    }
}
