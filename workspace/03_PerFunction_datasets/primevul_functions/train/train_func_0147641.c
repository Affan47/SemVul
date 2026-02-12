shell_gtk_embed_window_created_cb (MetaDisplay   *display,
                                   MetaWindow    *window,
                                   ShellGtkEmbed *embed)
{
  ShellGtkEmbedPrivate *priv = shell_gtk_embed_get_instance_private (embed);
  Window xwindow = meta_window_get_xwindow (window);
  GdkWindow *gdk_window = gtk_widget_get_window (GTK_WIDGET (priv->window));

  if (gdk_window && xwindow == gdk_x11_window_get_xid (gdk_window))
    {
      ClutterActor *window_actor =
        CLUTTER_ACTOR (meta_window_get_compositor_private (window));
      GCallback remove_cb = G_CALLBACK (shell_gtk_embed_remove_window_actor);
      cairo_region_t *empty_region;

      clutter_clone_set_source (CLUTTER_CLONE (embed), window_actor);


      priv->window_actor = g_object_ref (window_actor);
      priv->window_actor_destroyed_handler =
        g_signal_connect_swapped (window_actor,
                                  "destroy",
                                  remove_cb,
                                  embed);


      clutter_actor_set_opacity (window_actor, 0);


      empty_region = cairo_region_create ();
      gdk_window_input_shape_combine_region (gdk_window,
                                             empty_region,
                                             0, 0 );
      cairo_region_destroy (empty_region);

      gdk_window_lower (gdk_window);


      g_signal_handler_disconnect (display,
                                   priv->window_created_handler);
      priv->window_created_handler = 0;
    }
}
