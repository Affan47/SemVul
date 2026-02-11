finalize (GObject *object)
{
	NautilusSearchEngineModel *model;

	model = NAUTILUS_SEARCH_ENGINE_MODEL (object);

	if (model->details->hits != NULL) {
		g_list_free_full (model->details->hits, g_object_unref);
		model->details->hits = NULL;
	}

	if (model->details->finished_id != 0) {
		g_source_remove (model->details->finished_id);
		model->details->finished_id = 0;
	}

	g_clear_object (&model->details->directory);
	g_clear_object (&model->details->query);

	G_OBJECT_CLASS (nautilus_search_engine_model_parent_class)->finalize (object);
}
