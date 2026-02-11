get_scrollbar_height (StScrollView *scroll,
                      gfloat        for_width)
{
  StScrollViewPrivate *priv = scroll->priv;

  if (CLUTTER_ACTOR_IS_VISIBLE (priv->hscroll))
    {
      gfloat min_size;

      clutter_actor_get_preferred_height (CLUTTER_ACTOR (priv->hscroll), for_width,
                                          &min_size, NULL);

      return min_size;
    }
  else
    return 0;
}
