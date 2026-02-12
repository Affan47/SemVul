TIFFFillStrip(TIFF* tif, uint32 strip)
{
	static const char module[] = "TIFFFillStrip";
	TIFFDirectory *td = &tif->tif_dir;

        if (!_TIFFFillStriles( tif ) || !tif->tif_dir.td_stripbytecount)
            return 0;

	if ((tif->tif_flags&TIFF_NOREADRAW)==0)
	{
		uint64 bytecount = td->td_stripbytecount[strip];
		if ((int64)bytecount <= 0) {
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
			TIFFErrorExt(tif->tif_clientdata, module,
				"Invalid strip byte count %I64u, strip %lu",
				     (unsigned __int64) bytecount,
				     (unsigned long) strip);
#else
			TIFFErrorExt(tif->tif_clientdata, module,
				"Invalid strip byte count %llu, strip %lu",
				     (unsigned long long) bytecount,
				     (unsigned long) strip);
#endif
			return (0);
		}


                if( bytecount > 1024 * 1024 )
                {


			tmsize_t stripsize = TIFFStripSize(tif);
			if( stripsize != 0 &&
			    (bytecount - 4096) / 10 > (uint64)stripsize  )
			{
				uint64 newbytecount = (uint64)stripsize * 10 + 4096;
				if( (int64)newbytecount >= 0 )
				{
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
					TIFFWarningExt(tif->tif_clientdata, module,
					  "Too large strip byte count %I64u, strip %lu. Limiting to %I64u",
					     (unsigned __int64) bytecount,
					     (unsigned long) strip,
					     (unsigned __int64) newbytecount);
#else
					TIFFErrorExt(tif->tif_clientdata, module,
					  "Too large strip byte count %llu, strip %lu. Limiting to %llu",
					     (unsigned long long) bytecount,
					     (unsigned long) strip,
					     (unsigned long long) newbytecount);
#endif
					bytecount = newbytecount;
				}
			}
		}

		if (isMapped(tif)) {


			if (bytecount > (uint64)tif->tif_size ||
			    td->td_stripoffset[strip] > (uint64)tif->tif_size - bytecount) {


#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
				TIFFErrorExt(tif->tif_clientdata, module,

					"Read error on strip %lu; "
					"got %I64u bytes, expected %I64u",
					(unsigned long) strip,
					(unsigned __int64) tif->tif_size - td->td_stripoffset[strip],
					(unsigned __int64) bytecount);
#else
				TIFFErrorExt(tif->tif_clientdata, module,

					"Read error on strip %lu; "
					"got %llu bytes, expected %llu",
					(unsigned long) strip,
					(unsigned long long) tif->tif_size - td->td_stripoffset[strip],
					(unsigned long long) bytecount);
#endif
				tif->tif_curstrip = NOSTRIP;
				return (0);
			}
		}

		if (isMapped(tif) &&
		    (isFillOrder(tif, td->td_fillorder)
		    || (tif->tif_flags & TIFF_NOBITREV))) {


			if ((tif->tif_flags & TIFF_MYBUFFER) && tif->tif_rawdata) {
				_TIFFfree(tif->tif_rawdata);
				tif->tif_rawdata = NULL;
				tif->tif_rawdatasize = 0;
			}
			tif->tif_flags &= ~TIFF_MYBUFFER;
			tif->tif_rawdatasize = (tmsize_t)bytecount;
			tif->tif_rawdata = tif->tif_base + (tmsize_t)td->td_stripoffset[strip];
                        tif->tif_rawdataoff = 0;
                        tif->tif_rawdataloaded = (tmsize_t) bytecount;


			tif->tif_flags |= TIFF_BUFFERMMAP;
		} else {


			tmsize_t bytecountm;
			bytecountm=(tmsize_t)bytecount;
			if ((uint64)bytecountm!=bytecount)
			{
				TIFFErrorExt(tif->tif_clientdata,module,"Integer overflow");
				return(0);
			}
			if (bytecountm > tif->tif_rawdatasize) {
				tif->tif_curstrip = NOSTRIP;
				if ((tif->tif_flags & TIFF_MYBUFFER) == 0) {
					TIFFErrorExt(tif->tif_clientdata, module,
					    "Data buffer too small to hold strip %lu",
					    (unsigned long) strip);
					return (0);
				}
			}
			if (tif->tif_flags&TIFF_BUFFERMMAP) {
				tif->tif_curstrip = NOSTRIP;
				tif->tif_rawdata = NULL;
				tif->tif_rawdatasize = 0;
				tif->tif_flags &= ~TIFF_BUFFERMMAP;
			}

			if( isMapped(tif) )
			{
				if (bytecountm > tif->tif_rawdatasize &&
				    !TIFFReadBufferSetup(tif, 0, bytecountm))
				{
					return (0);
				}
				if (TIFFReadRawStrip1(tif, strip, tif->tif_rawdata,
				    bytecountm, module) != bytecountm)
				{
					return (0);
				}
			}
			else
			{
				if (TIFFReadRawStripOrTile2(tif, strip, 1,
				    bytecountm, module) != bytecountm)
				{
					return (0);
				}
			}


                        tif->tif_rawdataoff = 0;
                        tif->tif_rawdataloaded = bytecountm;

			if (!isFillOrder(tif, td->td_fillorder) &&
			    (tif->tif_flags & TIFF_NOBITREV) == 0)
				TIFFReverseBits(tif->tif_rawdata, bytecountm);
                }
	}
	return (TIFFStartStrip(tif, strip));
}
