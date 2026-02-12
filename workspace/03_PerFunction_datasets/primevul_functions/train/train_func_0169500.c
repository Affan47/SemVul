JPEGCleanup(TIFF* tif)
{
	JPEGState *sp = JState(tif);

	assert(sp != 0);

	tif->tif_tagmethods.vgetfield = sp->vgetparent;
	tif->tif_tagmethods.vsetfield = sp->vsetparent;
	tif->tif_tagmethods.printdir = sp->printdir;
        if( sp->cinfo_initialized )
                TIFFjpeg_destroy(sp);
        if (sp->jpegtables)
                _TIFFfree(sp->jpegtables);
	_TIFFfree(tif->tif_data);
	tif->tif_data = NULL;

	_TIFFSetDefaultCompressionState(tif);
}
