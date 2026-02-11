GdipGetMetafileDownLevelRasterizationLimit (GpMetafile *metafile, UINT *metafileRasterizationLimitDpi)
{
	if (!metafile || !metafileRasterizationLimitDpi)
		return InvalidParameter;

	switch (metafile->metafile_header.Type) {
	case METAFILETYPE_EMF:
	case METAFILETYPE_EMFPLUSDUAL:

		*metafileRasterizationLimitDpi = 0;
		return Ok;
	case METAFILETYPE_WMFPLACEABLE:
	case METAFILETYPE_WMF:
	case METAFILETYPE_EMFPLUSONLY:
	default:
		return WrongState;
	}
}
