gxps_zip_archive_destroy (ZipArchive *zip)
{
G_GNUC_BEGIN_IGNORE_DEPRECATIONS


	archive_read_finish (zip->archive);
G_GNUC_END_IGNORE_DEPRECATIONS
	g_slice_free (ZipArchive, zip);
}
