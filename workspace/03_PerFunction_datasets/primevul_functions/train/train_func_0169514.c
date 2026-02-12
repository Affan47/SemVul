std_empty_output_buffer(j_compress_ptr cinfo)
{
	JPEGState* sp = (JPEGState*) cinfo;
	TIFF* tif = sp->tif;


	tif->tif_rawcc = tif->tif_rawdatasize;

#ifdef IPPJ_HUFF


       if ( sp->dest.free_in_buffer >= 0 ) {
               tif->tif_rawcc = tif->tif_rawdatasize - sp->dest.free_in_buffer;
       }
#endif

	TIFFFlushData1(tif);
	sp->dest.next_output_byte = (JOCTET*) tif->tif_rawdata;
	sp->dest.free_in_buffer = (size_t) tif->tif_rawdatasize;

	return (TRUE);
}
