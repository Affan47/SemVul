giggle_revision_add_tag (GiggleRevision *revision,
			 GiggleRef      *tag)
{
	GiggleRevisionPriv *priv;

	g_return_if_fail (GIGGLE_IS_REVISION (revision));
	g_return_if_fail (GIGGLE_IS_REF (tag));

	priv = revision->priv;

	priv->tags = g_list_prepend (priv->tags,
				     g_object_ref (tag));
}
