brasero_dvdcss_create_scrambled_sectors_map (BraseroDvdcss *self,
					     BraseroDrive *drive,
                                             GQueue *map,
					     dvdcss_handle *handle,
					     BraseroVolFile *parent,
					     GError **error)
{
	GList *iter;


	for (iter = parent->specific.dir.children; iter; iter = iter->next) {
		BraseroVolFile *file;

		file = iter->data;
		if (!file->isdir) {
			if (!strncmp (file->name + strlen (file->name) - 6, ".VOB", 4)) {
				BraseroScrambledSectorRange *range;
				gsize current_extent;
				GSList *extents;

				BRASERO_JOB_LOG (self, "Retrieving keys for %s", file->name);


				if (!file->specific.file.extents) {
					BRASERO_JOB_LOG (self, "Problem: file has no extents");
					return FALSE;
				}

				range = g_new0 (BraseroScrambledSectorRange, 1);
				for (extents = file->specific.file.extents; extents; extents = extents->next) {
					BraseroVolFileExtent *extent;

					extent = extents->data;

					range->start = extent->block;
					range->end = extent->block + BRASERO_BYTES_TO_SECTORS (extent->size, DVDCSS_BLOCK_SIZE);

					BRASERO_JOB_LOG (self, "From 0x%llx to 0x%llx", range->start, range->end);
					g_queue_push_head (map, range);

					if (extent->size == 0) {
						BRASERO_JOB_LOG (self, "0 size extent");
						continue;
					}

					current_extent = dvdcss_seek (handle, range->start, DVDCSS_SEEK_KEY);
					if (current_extent != range->start) {
						BRASERO_JOB_LOG (self, "Problem: could not retrieve key");
						g_set_error (error,
							     BRASERO_BURN_ERROR,
							     BRASERO_BURN_ERROR_GENERAL,


							     _("Error while retrieving a key used for encryption. You may solve such a problem with one of the following methods: in a terminal either set the proper DVD region code for your CD/DVD player with the \"regionset %s\" command or run the \"DVDCSS_METHOD=title brasero --no-existing-session\" command"),
							     brasero_drive_get_device (drive));
						return FALSE;
					}
				}
			}
		}
		else if (!brasero_dvdcss_create_scrambled_sectors_map (self, drive, map, handle, file, error))
			return FALSE;
	}

	return TRUE;
}
