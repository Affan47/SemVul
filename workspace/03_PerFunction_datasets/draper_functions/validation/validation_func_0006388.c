daap_record_init (DAAPRecordIface * iface)
{
	static gboolean is_initialized = FALSE;

	daap_record_init_count++;

	if (!is_initialized) {
		g_object_interface_install_property (iface,
						     g_param_spec_string
						     ("location",
						      "URI pointing to song data",
						      "URI pointing to song data",
						      NULL,
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_pointer
						     ("hash",
						      "Hash of media file contents",
						      "Hash of media file contents",
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_string
						     ("title", "Song title",
						      "Song title", "Unknown",
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_enum
						     ("mediakind",
						      "Media kind",
						      "Media kind",
						      DMAP_TYPE_DMAP_MEDIA_KIND,
						      DMAP_MEDIA_KIND_MUSIC,
						      G_PARAM_READWRITE));


		g_object_interface_install_property (iface,
						     g_param_spec_string
						     ("songalbum",
						      "Album name",
						      "Album name", "Unknown",
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_int64
						     ("songalbumid",
						      "Album id", "Album id",
						      G_MININT64, G_MAXINT64,
						      0, G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_string
						     ("sort-album",
						      "Album sort name",
						      "Album sort name",
						      "Unknown",
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_string
						     ("songartist",
						      "Song artist",
						      "Song artist",
						      "Unknown",
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_string
						     ("sort-artist",
						      "Song artist sort name",
						      "Song artist sort name",
						      "Unknown",
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_string
						     ("songgenre",
						      "Song genre",
						      "Song genre", "Unknown",
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_string
						     ("format",
						      "Song data format",
						      "Song data format",
						      "Unknown",
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_int
						     ("rating", "Song rating",
						      "Song rating", 0, 5, 0,
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_uint64
						     ("filesize",
						      "Song data size in bytes",
						      "Song data size in bytes",
						      0, G_MAXINT, 0,
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_int
						     ("duration",
						      "Song duration in seconds",
						      "Song duration in seconds",
						      0, G_MAXINT, 0,
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_int
						     ("track",
						      "Song track number",
						      "Song track number", 0,
						      G_MAXINT, 0,
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_int ("year",
								       "Song publication year",
								       "Song publication year",
								       0,
								       G_MAXINT,
								       0,
								       G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_int
						     ("firstseen", "FIXME",
						      "FIXME", 0, G_MAXINT, 0,
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_int
						     ("mtime",
						      "Song modification time",
						      "Song modification time",
						      0, G_MAXINT, 0,
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_int ("disc",
								       "Song disc number",
								       "Song disc number",
								       0,
								       G_MAXINT,
								       0,
								       G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_int
						     ("bitrate",
						      "Song data bitrate in Kb/s",
						      "Song data bitrate in Kb/s",
						      0, G_MAXINT, 0,
						      G_PARAM_READWRITE));

		g_object_interface_install_property (iface,
						     g_param_spec_boolean
						     ("has-video",
						      "Song has video component",
						      "Song has video component",
						      FALSE,
						      G_PARAM_READWRITE));

		is_initialized = TRUE;
	}
}
