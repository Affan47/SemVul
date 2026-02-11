presentity_view_set_presentity (PresentityView* self,
				Ekiga::Presentity* presentity)
{
  g_return_if_fail ( !self->priv->presentity);

  self->priv->presentity = presentity;
  self->priv->updated_conn = self->priv->presentity->updated.connect (boost::bind (&on_presentity_updated, self));
  self->priv->removed_conn = self->priv->presentity->removed.connect (boost::bind (&on_presentity_removed, self));

  on_presentity_updated (self);
}
