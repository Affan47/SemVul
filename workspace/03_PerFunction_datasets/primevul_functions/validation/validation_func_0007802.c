static BOOL _update_read_pointer_large(wStream* s, POINTER_LARGE_UPDATE* pointer)
{
	BYTE* newMask;
	UINT32 scanlineSize;

	if (!pointer)
		goto fail;

	if (Stream_GetRemainingLength(s) < 20)
		goto fail;

	Stream_Read_UINT16(s, pointer->xorBpp);
	Stream_Read_UINT16(s, pointer->cacheIndex);
	Stream_Read_UINT16(s, pointer->hotSpotX);
	Stream_Read_UINT16(s, pointer->hotSpotY);

	Stream_Read_UINT16(s, pointer->width);
	Stream_Read_UINT16(s, pointer->height);

	if ((pointer->width > 384) || (pointer->height > 384))
		goto fail;

	Stream_Read_UINT32(s, pointer->lengthAndMask);
	Stream_Read_UINT32(s, pointer->lengthXorMask);

	if (pointer->hotSpotX >= pointer->width)
		pointer->hotSpotX = 0;

	if (pointer->hotSpotY >= pointer->height)
		pointer->hotSpotY = 0;

	if (pointer->lengthXorMask > 0)
	{


		if (Stream_GetRemainingLength(s) < pointer->lengthXorMask)
			goto fail;

		scanlineSize = (7 + pointer->xorBpp * pointer->width) / 8;
		scanlineSize = ((scanlineSize + 1) / 2) * 2;

		if (scanlineSize * pointer->height != pointer->lengthXorMask)
		{
			WLog_ERR(TAG,
			         "invalid lengthXorMask: width=%" PRIu32 " height=%" PRIu32 ", %" PRIu32
			         " instead of %" PRIu32 "",
			         pointer->width, pointer->height, pointer->lengthXorMask,
			         scanlineSize * pointer->height);
			goto fail;
		}

		newMask = realloc(pointer->xorMaskData, pointer->lengthXorMask);

		if (!newMask)
			goto fail;

		pointer->xorMaskData = newMask;
		Stream_Read(s, pointer->xorMaskData, pointer->lengthXorMask);
	}

	if (pointer->lengthAndMask > 0)
	{


		if (Stream_GetRemainingLength(s) < pointer->lengthAndMask)
			goto fail;

		scanlineSize = ((7 + pointer->width) / 8);
		scanlineSize = ((1 + scanlineSize) / 2) * 2;

		if (scanlineSize * pointer->height != pointer->lengthAndMask)
		{
			WLog_ERR(TAG, "invalid lengthAndMask: %" PRIu32 " instead of %" PRIu32 "",
			         pointer->lengthAndMask, scanlineSize * pointer->height);
			goto fail;
		}

		newMask = realloc(pointer->andMaskData, pointer->lengthAndMask);

		if (!newMask)
			goto fail;

		pointer->andMaskData = newMask;
		Stream_Read(s, pointer->andMaskData, pointer->lengthAndMask);
	}

	if (Stream_GetRemainingLength(s) > 0)
		Stream_Seek_UINT8(s);

	return TRUE;
fail:
	return FALSE;
}
