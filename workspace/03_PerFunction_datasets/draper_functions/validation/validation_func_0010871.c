thumb_app_setup_play (ThumbApp *app)
{
	GstElement *play;
	GstElement *audio_sink, *video_sink;
	GstRegistry *registry;
	GstPluginFeature *feature;

	play = gst_element_factory_make ("playbin", "play");
	audio_sink = gst_element_factory_make ("fakesink", "audio-fake-sink");
	video_sink = gst_element_factory_make ("fakesink", "video-fake-sink");
	g_object_set (video_sink, "sync", TRUE, NULL);

	g_object_set (play,
		      "audio-sink", audio_sink,
		      "video-sink", video_sink,
		      "flags", GST_PLAY_FLAG_VIDEO | GST_PLAY_FLAG_AUDIO,
		      NULL);

	app->play = play;


	registry = gst_registry_get ();
	feature = gst_registry_find_feature (registry,
					     "vaapidecode",
					     GST_TYPE_ELEMENT_FACTORY);
	if (!feature)
		return;
	gst_registry_remove_feature (registry, feature);
}
