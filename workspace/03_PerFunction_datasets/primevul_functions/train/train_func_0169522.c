JPEGPreDecode(TIFF* tif, uint16 s)
{
	JPEGState *sp = JState(tif);
	TIFFDirectory *td = &tif->tif_dir;
	static const char module[] = "JPEGPreDecode";
	uint32 segment_width, segment_height;
	int downsampled_output;
	int ci;

	assert(sp != NULL);

	if (sp->cinfo.comm.is_decompressor == 0)
	{
		tif->tif_setupdecode( tif );
	}

	assert(sp->cinfo.comm.is_decompressor);


	if (!TIFFjpeg_abort(sp))
		return (0);


	if (TIFFjpeg_read_header(sp, TRUE) != JPEG_HEADER_OK)
		return (0);

        tif->tif_rawcp = (uint8*) sp->src.next_input_byte;
        tif->tif_rawcc = sp->src.bytes_in_buffer;


	segment_width = td->td_imagewidth;
	segment_height = td->td_imagelength - tif->tif_row;
	if (isTiled(tif)) {
                segment_width = td->td_tilewidth;
                segment_height = td->td_tilelength;
		sp->bytesperline = TIFFTileRowSize(tif);
	} else {
		if (segment_height > td->td_rowsperstrip)
			segment_height = td->td_rowsperstrip;
		sp->bytesperline = TIFFScanlineSize(tif);
	}
	if (td->td_planarconfig == PLANARCONFIG_SEPARATE && s > 0) {


		segment_width = TIFFhowmany_32(segment_width, sp->h_sampling);
		segment_height = TIFFhowmany_32(segment_height, sp->v_sampling);
	}
	if (sp->cinfo.d.image_width < segment_width ||
	    sp->cinfo.d.image_height < segment_height) {
		TIFFWarningExt(tif->tif_clientdata, module,
			       "Improper JPEG strip/tile size, "
			       "expected %dx%d, got %dx%d",
			       segment_width, segment_height,
			       sp->cinfo.d.image_width,
			       sp->cinfo.d.image_height);
	}
	if (sp->cinfo.d.image_width > segment_width ||
	    sp->cinfo.d.image_height > segment_height) {


		TIFFErrorExt(tif->tif_clientdata, module,
			     "JPEG strip/tile size exceeds expected dimensions,"
			     " expected %dx%d, got %dx%d",
			     segment_width, segment_height,
			     sp->cinfo.d.image_width, sp->cinfo.d.image_height);
		return (0);
	}
	if (sp->cinfo.d.num_components !=
	    (td->td_planarconfig == PLANARCONFIG_CONTIG ?
	     td->td_samplesperpixel : 1)) {
		TIFFErrorExt(tif->tif_clientdata, module, "Improper JPEG component count");
		return (0);
	}
#ifdef JPEG_LIB_MK1
	if (12 != td->td_bitspersample && 8 != td->td_bitspersample) {
		TIFFErrorExt(tif->tif_clientdata, module, "Improper JPEG data precision");
		return (0);
	}
	sp->cinfo.d.data_precision = td->td_bitspersample;
	sp->cinfo.d.bits_in_jsample = td->td_bitspersample;
#else
	if (sp->cinfo.d.data_precision != td->td_bitspersample) {
		TIFFErrorExt(tif->tif_clientdata, module, "Improper JPEG data precision");
		return (0);
	}
#endif
	if (td->td_planarconfig == PLANARCONFIG_CONTIG) {

		if (sp->cinfo.d.comp_info[0].h_samp_factor != sp->h_sampling ||
		    sp->cinfo.d.comp_info[0].v_samp_factor != sp->v_sampling) {
			TIFFErrorExt(tif->tif_clientdata, module,
				       "Improper JPEG sampling factors %d,%d\n"
				       "Apparently should be %d,%d.",
				       sp->cinfo.d.comp_info[0].h_samp_factor,
				       sp->cinfo.d.comp_info[0].v_samp_factor,
				       sp->h_sampling, sp->v_sampling);
			return (0);
		}

		for (ci = 1; ci < sp->cinfo.d.num_components; ci++) {
			if (sp->cinfo.d.comp_info[ci].h_samp_factor != 1 ||
			    sp->cinfo.d.comp_info[ci].v_samp_factor != 1) {
				TIFFErrorExt(tif->tif_clientdata, module, "Improper JPEG sampling factors");
				return (0);
			}
		}
	} else {

		if (sp->cinfo.d.comp_info[0].h_samp_factor != 1 ||
		    sp->cinfo.d.comp_info[0].v_samp_factor != 1) {
			TIFFErrorExt(tif->tif_clientdata, module, "Improper JPEG sampling factors");
			return (0);
		}
	}
	downsampled_output = FALSE;
	if (td->td_planarconfig == PLANARCONFIG_CONTIG &&
	    sp->photometric == PHOTOMETRIC_YCBCR &&
	    sp->jpegcolormode == JPEGCOLORMODE_RGB) {

		sp->cinfo.d.jpeg_color_space = JCS_YCbCr;
		sp->cinfo.d.out_color_space = JCS_RGB;
	} else {

		sp->cinfo.d.jpeg_color_space = JCS_UNKNOWN;
		sp->cinfo.d.out_color_space = JCS_UNKNOWN;
		if (td->td_planarconfig == PLANARCONFIG_CONTIG &&
		    (sp->h_sampling != 1 || sp->v_sampling != 1))
			downsampled_output = TRUE;

	}
	if (downsampled_output) {

		sp->cinfo.d.raw_data_out = TRUE;
#if JPEG_LIB_VERSION >= 70
		sp->cinfo.d.do_fancy_upsampling = FALSE;
#endif
		tif->tif_decoderow = DecodeRowError;
		tif->tif_decodestrip = JPEGDecodeRaw;
		tif->tif_decodetile = JPEGDecodeRaw;
	} else {

		sp->cinfo.d.raw_data_out = FALSE;
		tif->tif_decoderow = JPEGDecode;
		tif->tif_decodestrip = JPEGDecode;
		tif->tif_decodetile = JPEGDecode;
	}

	if (!TIFFjpeg_start_decompress(sp))
		return (0);

	if (downsampled_output) {
		if (!alloc_downsampled_buffers(tif, sp->cinfo.d.comp_info,
					       sp->cinfo.d.num_components))
			return (0);
		sp->scancount = DCTSIZE;
	}
	return (1);
}
