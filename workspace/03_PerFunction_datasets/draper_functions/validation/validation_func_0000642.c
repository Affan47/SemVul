test_parsing_media_group_ratings (void)
{
	GDataYouTubeVideo *video;
	GError *error = NULL;


	video = GDATA_YOUTUBE_VIDEO (gdata_parsable_new_from_xml (GDATA_TYPE_YOUTUBE_VIDEO,
		"<entry xmlns='http://www.w3.org/2005/Atom' "
		       "xmlns:media='http://search.yahoo.com/mrss/' "
		       "xmlns:yt='http://gdata.youtube.com/schemas/2007' "
		       "xmlns:gd='http://schemas.google.com/g/2005'>"
			"<id>tag:youtube.com,2008:video:JAagedeKdcQ</id>"
			"<published>2006-05-16T14:06:37.000Z</published>"
			"<updated>2009-03-23T12:46:58.000Z</updated>"
			"<category scheme='http://schemas.google.com/g/2005#kind' term='http://gdata.youtube.com/schemas/2007#video'/>"
			"<title>Some video somewhere</title>"
			"<media:group>"
				"<media:rating scheme='urn:simple'>nonadult</media:rating>"
				"<media:rating scheme='urn:mpaa'>pg</media:rating>"
				"<media:rating scheme='urn:v-chip'>tv-pg</media:rating>"
			"</media:group>"
		"</entry>", -1, &error));
	g_assert_no_error (error);
	g_assert (GDATA_IS_YOUTUBE_VIDEO (video));
	g_clear_error (&error);


	g_assert_cmpstr (gdata_youtube_video_get_media_rating (video, GDATA_YOUTUBE_RATING_TYPE_SIMPLE), ==, "nonadult");
	g_assert_cmpstr (gdata_youtube_video_get_media_rating (video, GDATA_YOUTUBE_RATING_TYPE_MPAA), ==, "pg");
	g_assert_cmpstr (gdata_youtube_video_get_media_rating (video, GDATA_YOUTUBE_RATING_TYPE_V_CHIP), ==, "tv-pg");

	g_assert (gdata_youtube_video_is_restricted_in_country (video, "US") == FALSE);

	g_object_unref (video);


	video = GDATA_YOUTUBE_VIDEO (gdata_parsable_new_from_xml (GDATA_TYPE_YOUTUBE_VIDEO,
		"<entry xmlns='http://www.w3.org/2005/Atom' "
		       "xmlns:media='http://search.yahoo.com/mrss/' "
		       "xmlns:yt='http://gdata.youtube.com/schemas/2007' "
		       "xmlns:gd='http://schemas.google.com/g/2005'>"
			"<id>tag:youtube.com,2008:video:JAagedeKdcQ</id>"
			"<published>2006-05-16T14:06:37.000Z</published>"
			"<updated>2009-03-23T12:46:58.000Z</updated>"
			"<category scheme='http://schemas.google.com/g/2005#kind' term='http://gdata.youtube.com/schemas/2007#video'/>"
			"<title>Some video somewhere</title>"
			"<media:group>"
				"<media:rating scheme='urn:v-chip'>tv-y7-fv</media:rating>"
				"<media:rating>adult</media:rating>"
			"</media:group>"
		"</entry>", -1, &error));
	g_assert_no_error (error);
	g_assert (GDATA_IS_YOUTUBE_VIDEO (video));
	g_clear_error (&error);


	g_assert_cmpstr (gdata_youtube_video_get_media_rating (video, GDATA_YOUTUBE_RATING_TYPE_SIMPLE), ==, "adult");
	g_assert_cmpstr (gdata_youtube_video_get_media_rating (video, GDATA_YOUTUBE_RATING_TYPE_MPAA), ==, NULL);
	g_assert_cmpstr (gdata_youtube_video_get_media_rating (video, GDATA_YOUTUBE_RATING_TYPE_V_CHIP), ==, "tv-y7-fv");


	g_assert_cmpstr (gdata_youtube_video_get_media_rating (video, "fooish bar"), ==, NULL);

	g_object_unref (video);
}
