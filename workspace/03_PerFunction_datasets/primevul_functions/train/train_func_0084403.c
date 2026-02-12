static void TIFFReadDirEntryCheckedShort(TIFF* tif, TIFFDirEntry* direntry, uint16* value)
{
	*value = direntry->tdir_offset.toff_short;

	if (tif->tif_flags&TIFF_SWAB)
		TIFFSwabShort(value);
}
