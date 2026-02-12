void LibRaw::parse_exif_interop(int base)
{
	unsigned entries, tag, type, len, save;
	char value[4] = { 0,0,0,0 };
	entries = get2();
	INT64 fsize = ifp->size();
	while (entries--)
	{
		tiff_get(base, &tag, &type, &len, &save);

		INT64 savepos = ftell(ifp);
		if (len > 8 && savepos + len > fsize * 2)
		{
			fseek(ifp, save, SEEK_SET);
			continue;
		}

		switch (tag)
		{
		case 0x0001:
			fread(value, 1, MIN(4, len), ifp);
			if (strncmp(value, "R98", 3) == 0 &&


				imgdata.color.ExifColorSpace == LIBRAW_COLORSPACE_Unknown)
				imgdata.color.ExifColorSpace = LIBRAW_COLORSPACE_sRGB;
			else if (strncmp(value, "R03", 3) == 0)
				imgdata.color.ExifColorSpace = LIBRAW_COLORSPACE_AdobeRGB;
			break;
		}
		fseek(ifp, save, SEEK_SET);
	}
}
