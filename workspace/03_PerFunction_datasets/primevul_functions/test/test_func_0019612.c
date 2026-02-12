fr_archive_libarchive_get_capabilities (FrArchive  *archive,
					const char *mime_type,
					gboolean    check_command)
{
	FrArchiveCap capabilities;

	capabilities = FR_ARCHIVE_CAN_STORE_MANY_FILES;


	if (strcmp (mime_type, "application/x-7z-compressed") == 0) {
		capabilities |= FR_ARCHIVE_CAN_WRITE;
		return capabilities;
	}


	if ((strcmp (mime_type, "application/vnd.ms-cab-compressed") == 0)
	    && _g_program_is_available ("7za", check_command))
	{
		return capabilities;
	}

	capabilities |= FR_ARCHIVE_CAN_READ;


	if ((strcmp (mime_type, "application/vnd.ms-cab-compressed") == 0)
	    || (strcmp (mime_type, "application/x-lha") == 0)
	    || (strcmp (mime_type, "application/x-xar") == 0))
	{
		return capabilities;
	}


	capabilities |= FR_ARCHIVE_CAN_WRITE;

	return capabilities;
}
