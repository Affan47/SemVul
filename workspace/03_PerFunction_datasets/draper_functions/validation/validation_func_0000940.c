mx_kinetic_scroll_view_set_use_captured (MxKineticScrollView *scroll,
                                         gboolean             use_captured)
{
  MxKineticScrollViewPrivate *priv;

  g_return_if_fail (MX_IS_KINETIC_SCROLL_VIEW (scroll));

  priv = scroll->priv;
  if (priv->use_captured != use_captured)
    {
      priv->use_captured = use_captured;

      g_signal_handlers_disconnect_by_func (scroll,
                                            button_press_event_cb,
                                            scroll);

      g_signal_connect (scroll,
                        use_captured ? "captured-event" : "button-press-event",
                        G_CALLBACK (button_press_event_cb),
                        scroll);

      g_object_notify (G_OBJECT (scroll), "use-captured");
    }
}
