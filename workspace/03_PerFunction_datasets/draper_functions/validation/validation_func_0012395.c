gkm_object_finalize (GObject *obj)
{
	GkmObject *self = GKM_OBJECT (obj);

	g_assert (self->pv->manager == NULL);
	g_free (self->pv->unique);


	g_object_weak_unref (G_OBJECT (self->pv->module), module_went_away, self);
	self->pv->module = NULL;

	if (self->pv->transient) {
		g_slice_free (GkmObjectTransient, self->pv->transient);
		self->pv->transient = NULL;
	}

	G_OBJECT_CLASS (gkm_object_parent_class)->finalize (obj);
}
