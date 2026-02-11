gst_a2dp_sink_init_fakesink(GstA2dpSink *self)
{
	if (self->fakesink != NULL)
		return TRUE;

	g_mutex_lock(self->cb_mutex);
	self->fakesink = gst_a2dp_sink_init_element(self, "fakesink",
			"fakesink", self->capsfilter);
	g_mutex_unlock(self->cb_mutex);

	if (!self->fakesink)
		return FALSE;

	return TRUE;
}
