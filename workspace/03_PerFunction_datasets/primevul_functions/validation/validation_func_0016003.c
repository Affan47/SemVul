static BOOL rdp_read_bitmap_codecs_capability_set(wStream* s, UINT16 length, rdpSettings* settings)
{
	BYTE codecId;
	GUID codecGuid;
	RPC_STATUS rpc_status;
	BYTE bitmapCodecCount;
	UINT16 codecPropertiesLength;
	UINT16 remainingLength;
	BOOL guidNSCodec = FALSE;
	BOOL guidRemoteFx = FALSE;
	BOOL guidRemoteFxImage = FALSE;

	if (length < 5)
		return FALSE;

	Stream_Read_UINT8(s, bitmapCodecCount);
	remainingLength = length - 5;

	while (bitmapCodecCount > 0)
	{
		if (remainingLength < 19)
			return FALSE;

		rdp_read_bitmap_codec_guid(s, &codecGuid);
		Stream_Read_UINT8(s, codecId);
		Stream_Read_UINT16(s, codecPropertiesLength);
		remainingLength -= 19;

		if (remainingLength < codecPropertiesLength)
			return FALSE;

		if (settings->ServerMode)
		{
			UINT32 beg;
			UINT32 end;
			beg = (UINT32)Stream_GetPosition(s);
			end = beg + codecPropertiesLength;

			if (UuidEqual(&codecGuid, &CODEC_GUID_REMOTEFX, &rpc_status))
			{
				UINT32 rfxCapsLength;
				UINT32 rfxPropsLength;
				UINT32 captureFlags;
				guidRemoteFx = TRUE;
				settings->RemoteFxCodecId = codecId;
				Stream_Read_UINT32(s, rfxPropsLength);
				Stream_Read_UINT32(s, captureFlags);
				Stream_Read_UINT32(s, rfxCapsLength);
				settings->RemoteFxCaptureFlags = captureFlags;
				settings->RemoteFxOnly = (captureFlags & CARDP_CAPS_CAPTURE_NON_CAC) ? TRUE : FALSE;

				if (rfxCapsLength)
				{
					UINT16 blockType;
					UINT32 blockLen;
					UINT16 numCapsets;
					BYTE rfxCodecId;
					UINT16 capsetType;
					UINT16 numIcaps;
					UINT16 icapLen;

					Stream_Read_UINT16(s, blockType);
					Stream_Read_UINT32(s, blockLen);
					Stream_Read_UINT16(s, numCapsets);

					if (blockType != 0xCBC0)
						return FALSE;

					if (blockLen != 8)
						return FALSE;

					if (numCapsets != 1)
						return FALSE;


					Stream_Read_UINT16(s, blockType);
					Stream_Read_UINT32(s, blockLen);
					Stream_Read_UINT8(s, rfxCodecId);
					Stream_Read_UINT16(s, capsetType);
					Stream_Read_UINT16(s, numIcaps);
					Stream_Read_UINT16(s, icapLen);

					if (blockType != 0xCBC1)
						return FALSE;

					if (rfxCodecId != 1)
						return FALSE;

					if (capsetType != 0xCFC0)
						return FALSE;

					while (numIcaps--)
					{
						UINT16 version;
						UINT16 tileSize;
						BYTE codecFlags;
						BYTE colConvBits;
						BYTE transformBits;
						BYTE entropyBits;

						Stream_Read_UINT16(s, version);
						Stream_Read_UINT16(s, tileSize);
						Stream_Read_UINT8(s, codecFlags);
						Stream_Read_UINT8(s, colConvBits);
						Stream_Read_UINT8(s, transformBits);
						Stream_Read_UINT8(s, entropyBits);

						if (version == 0x0009)
						{

							if (tileSize != 0x0080)
								return FALSE;
						}
						else if (version == 0x0100)
						{

							if (tileSize != 0x0040)
								return FALSE;
						}
						else
							return FALSE;

						if (colConvBits != 1)
							return FALSE;

						if (transformBits != 1)
							return FALSE;
					}
				}
			}
			else if (UuidEqual(&codecGuid, &CODEC_GUID_IMAGE_REMOTEFX, &rpc_status))
			{

				guidRemoteFxImage = TRUE;
				Stream_Seek(s, codecPropertiesLength);
			}
			else if (UuidEqual(&codecGuid, &CODEC_GUID_NSCODEC, &rpc_status))
			{
				BYTE colorLossLevel;
				BYTE fAllowSubsampling;
				BYTE fAllowDynamicFidelity;
				guidNSCodec = TRUE;
				settings->NSCodecId = codecId;
				Stream_Read_UINT8(s, fAllowDynamicFidelity);
				Stream_Read_UINT8(s, fAllowSubsampling);
				Stream_Read_UINT8(s, colorLossLevel);

				if (colorLossLevel < 1)
					colorLossLevel = 1;

				if (colorLossLevel > 7)
					colorLossLevel = 7;

				settings->NSCodecAllowDynamicColorFidelity = fAllowDynamicFidelity;
				settings->NSCodecAllowSubsampling = fAllowSubsampling;
				settings->NSCodecColorLossLevel = colorLossLevel;
			}
			else if (UuidEqual(&codecGuid, &CODEC_GUID_IGNORE, &rpc_status))
			{
				Stream_Seek(s, codecPropertiesLength);
			}
			else
			{
				Stream_Seek(s, codecPropertiesLength);
			}

			if (Stream_GetPosition(s) != end)
			{
				WLog_ERR(TAG,
				         "error while reading codec properties: actual offset: %" PRIuz
				         " expected offset: %" PRIu32 "",
				         Stream_GetPosition(s), end);
				Stream_SetPosition(s, end);
			}

			remainingLength -= codecPropertiesLength;
		}
		else
		{
			Stream_Seek(s, codecPropertiesLength);
			remainingLength -= codecPropertiesLength;
		}

		bitmapCodecCount--;
	}

	if (settings->ServerMode)
	{

		settings->RemoteFxCodec = settings->RemoteFxCodec && guidRemoteFx;
		settings->RemoteFxImageCodec = settings->RemoteFxImageCodec && guidRemoteFxImage;
		settings->NSCodec = settings->NSCodec && guidNSCodec;
		settings->JpegCodec = FALSE;
	}

	return TRUE;
}
