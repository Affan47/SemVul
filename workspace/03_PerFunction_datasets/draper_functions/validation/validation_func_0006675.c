rb_gst_encoding_profile_get_media_type (GstEncodingProfile *profile)
{
	if (GST_IS_ENCODING_CONTAINER_PROFILE (profile)) {
		const GList *cl = gst_encoding_container_profile_get_profiles (GST_ENCODING_CONTAINER_PROFILE (profile));
		for (; cl != NULL; cl = cl->next) {
			GstEncodingProfile *p = cl->data;
			if (GST_IS_ENCODING_AUDIO_PROFILE (p)) {
				return rb_gst_caps_to_media_type (gst_encoding_profile_get_format (p));
			}

		}


		return NULL;
	} else {
		return rb_gst_caps_to_media_type (gst_encoding_profile_get_format (profile));
	}
}
