extractor_apply_video_metadata (MetadataExtractor    *extractor,
                                GstTagList           *tag_list,
                                TrackerSparqlBuilder *metadata,
                                const gchar          *performer_uri,
                                const gchar          *composer_uri)
{
	add_string_gst_tag (metadata, "dc:source", tag_list, GST_TAG_CLASSIFICATION);

	if (performer_uri) {
		tracker_sparql_builder_predicate (metadata, "nmm:leadActor");
		tracker_sparql_builder_object_iri (metadata, performer_uri);
	}

	if (composer_uri) {
		tracker_sparql_builder_predicate (metadata, "nmm:director");
		tracker_sparql_builder_object_iri (metadata, composer_uri);
	}

	add_keywords_gst_tag (metadata, tag_list);
}
