BYTE* freerdp_bitmap_compress_planar(BITMAP_PLANAR_CONTEXT* context, const BYTE* data,
                                     UINT32 format, UINT32 width, UINT32 height, UINT32 scanline,
                                     BYTE* dstData, UINT32* pDstSize)
{
	UINT32 size;
	BYTE* dstp;
	UINT32 planeSize;
	UINT32 dstSizes[4] = { 0 };
	BYTE FormatHeader = 0;

	if (!context || !context->rlePlanesBuffer)
		return NULL;

	if (context->AllowSkipAlpha)
		FormatHeader |= PLANAR_FORMAT_HEADER_NA;

	planeSize = width * height;

	if (!freerdp_split_color_planes(data, format, width, height, scanline, context->planes))
		return NULL;

	if (context->AllowRunLengthEncoding)
	{
		if (!freerdp_bitmap_planar_delta_encode_planes(context->planes, width, height,
		                                               context->deltaPlanes))
			return NULL;

		if (!freerdp_bitmap_planar_compress_planes_rle(context->deltaPlanes, width, height,
		                                               context->rlePlanesBuffer, dstSizes,
		                                               context->AllowSkipAlpha))
			return NULL;

		{
			int offset = 0;
			FormatHeader |= PLANAR_FORMAT_HEADER_RLE;
			context->rlePlanes[0] = &context->rlePlanesBuffer[offset];
			offset += dstSizes[0];
			context->rlePlanes[1] = &context->rlePlanesBuffer[offset];
			offset += dstSizes[1];
			context->rlePlanes[2] = &context->rlePlanesBuffer[offset];
			offset += dstSizes[2];
			context->rlePlanes[3] = &context->rlePlanesBuffer[offset];


		}
	}

	if (FormatHeader & PLANAR_FORMAT_HEADER_RLE)
	{
		if (!context->AllowRunLengthEncoding)
			return NULL;

		if (context->rlePlanes[0] == NULL)
			return NULL;

		if (context->rlePlanes[1] == NULL)
			return NULL;

		if (context->rlePlanes[2] == NULL)
			return NULL;

		if (context->rlePlanes[3] == NULL)
			return NULL;
	}

	if (!dstData)
	{
		size = 1;

		if (!(FormatHeader & PLANAR_FORMAT_HEADER_NA))
		{
			if (FormatHeader & PLANAR_FORMAT_HEADER_RLE)
				size += dstSizes[0];
			else
				size += planeSize;
		}

		if (FormatHeader & PLANAR_FORMAT_HEADER_RLE)
			size += (dstSizes[1] + dstSizes[2] + dstSizes[3]);
		else
			size += (planeSize * 3);

		if (!(FormatHeader & PLANAR_FORMAT_HEADER_RLE))
			size++;

		dstData = malloc(size);

		if (!dstData)
			return NULL;

		*pDstSize = size;
	}

	dstp = dstData;
	*dstp = FormatHeader;
	dstp++;


	if (!(FormatHeader & PLANAR_FORMAT_HEADER_NA))
	{
		if (FormatHeader & PLANAR_FORMAT_HEADER_RLE)
		{
			CopyMemory(dstp, context->rlePlanes[0], dstSizes[0]);
			dstp += dstSizes[0];
		}
		else
		{
			CopyMemory(dstp, context->planes[0], planeSize);
			dstp += planeSize;
		}
	}


	if (FormatHeader & PLANAR_FORMAT_HEADER_RLE)
	{
		CopyMemory(dstp, context->rlePlanes[1], dstSizes[1]);
		dstp += dstSizes[1];
	}
	else
	{
		CopyMemory(dstp, context->planes[1], planeSize);
		dstp += planeSize;
	}


	if (FormatHeader & PLANAR_FORMAT_HEADER_RLE)
	{
		CopyMemory(dstp, context->rlePlanes[2], dstSizes[2]);
		dstp += dstSizes[2];
	}
	else
	{
		CopyMemory(dstp, context->planes[2], planeSize);
		dstp += planeSize;
	}


	if (FormatHeader & PLANAR_FORMAT_HEADER_RLE)
	{
		CopyMemory(dstp, context->rlePlanes[3], dstSizes[3]);
		dstp += dstSizes[3];
	}
	else
	{
		CopyMemory(dstp, context->planes[3], planeSize);
		dstp += planeSize;
	}


	if (!(FormatHeader & PLANAR_FORMAT_HEADER_RLE))
	{
		*dstp = 0;
		dstp++;
	}

	size = (dstp - dstData);
	*pDstSize = size;
	return dstData;
}
