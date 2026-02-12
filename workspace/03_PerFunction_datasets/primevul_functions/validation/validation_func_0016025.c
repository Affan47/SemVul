static BOOL rdp_write_rfx_client_capability_container(wStream* s, const rdpSettings* settings)
{
	UINT32 captureFlags;
	BYTE codecMode;

	if (!Stream_EnsureRemainingCapacity(s, 64))
		return FALSE;

	captureFlags = settings->RemoteFxOnly ? 0 : CARDP_CAPS_CAPTURE_NON_CAC;
	codecMode = settings->RemoteFxCodecMode;
	Stream_Write_UINT16(s, 49);

	Stream_Write_UINT32(s, 49);
	Stream_Write_UINT32(s, captureFlags);
	Stream_Write_UINT32(s, 37);

	Stream_Write_UINT16(s, CBY_CAPS);
	Stream_Write_UINT32(s, 8);
	Stream_Write_UINT16(s, 1);

	Stream_Write_UINT16(s, CBY_CAPSET);
	Stream_Write_UINT32(s, 29);
	Stream_Write_UINT8(s, 0x01);
	Stream_Write_UINT16(s, CLY_CAPSET);
	Stream_Write_UINT16(s, 2);
	Stream_Write_UINT16(s, 8);

	Stream_Write_UINT16(s, CLW_VERSION_1_0);
	Stream_Write_UINT16(s, CT_TILE_64x64);
	Stream_Write_UINT8(s, codecMode);
	Stream_Write_UINT8(s, CLW_COL_CONV_ICT);
	Stream_Write_UINT8(s, CLW_XFORM_DWT_53_A);
	Stream_Write_UINT8(s, CLW_ENTROPY_RLGR1);

	Stream_Write_UINT16(s, CLW_VERSION_1_0);
	Stream_Write_UINT16(s, CT_TILE_64x64);
	Stream_Write_UINT8(s, codecMode);
	Stream_Write_UINT8(s, CLW_COL_CONV_ICT);
	Stream_Write_UINT8(s, CLW_XFORM_DWT_53_A);
	Stream_Write_UINT8(s, CLW_ENTROPY_RLGR3);
	return TRUE;
}
