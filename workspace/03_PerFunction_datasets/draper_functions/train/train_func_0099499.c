dma_sparse_view_set_property (GObject *object,guint prop_id, const GValue *value, GParamSpec *pspec)
{
	DmaSparseView *view;

	g_return_if_fail (DMA_IS_SPARSE_VIEW (object));

	view = DMA_SPARSE_VIEW (object);

	switch (prop_id)
	{
		case PROP_BUFFER:
			dma_sparse_view_set_sparse_buffer (view, g_value_get_object (value));
			break;
		case PROP_SHOW_LINE_NUMBERS:
			dma_sparse_view_set_show_line_numbers (view, g_value_get_boolean (value));
			break;
		case PROP_SHOW_LINE_MARKERS:
			dma_sparse_view_set_show_line_markers (view, g_value_get_boolean (value));
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}
