mx_label_set_y_align (MxLabel *label,
                      MxAlign  align)
{
  g_return_if_fail (MX_IS_LABEL (label));


  if (align != label->priv->y_align)
    {
      label->priv->y_align = align;

      clutter_actor_queue_relayout (CLUTTER_ACTOR (label));

      g_object_notify (G_OBJECT (label), "y-align");
    }
}
