static BOOL rdp_print_bitmap_capability_set(wStream* s, UINT16 length)
{
	UINT16 preferredBitsPerPixel;
	UINT16 receive1BitPerPixel;
	UINT16 receive4BitsPerPixel;
	UINT16 receive8BitsPerPixel;
	UINT16 desktopWidth;
	UINT16 desktopHeight;
	UINT16 pad2Octets;
	UINT16 desktopResizeFlag;
	UINT16 bitmapCompressionFlag;
	BYTE highColorFlags;
	BYTE drawingFlags;
	UINT16 multipleRectangleSupport;
	UINT16 pad2OctetsB;
	WLog_INFO(TAG, "BitmapCapabilitySet (length %" PRIu16 "):", length);

	if (length < 28)
		return FALSE;

	Stream_Read_UINT16(s, preferredBitsPerPixel);
	Stream_Read_UINT16(s, receive1BitPerPixel);
	Stream_Read_UINT16(s, receive4BitsPerPixel);
	Stream_Read_UINT16(s, receive8BitsPerPixel);
	Stream_Read_UINT16(s, desktopWidth);
	Stream_Read_UINT16(s, desktopHeight);
	Stream_Read_UINT16(s, pad2Octets);
	Stream_Read_UINT16(s, desktopResizeFlag);
	Stream_Read_UINT16(s, bitmapCompressionFlag);
	Stream_Read_UINT8(s, highColorFlags);
	Stream_Read_UINT8(s, drawingFlags);
	Stream_Read_UINT16(s, multipleRectangleSupport);
	Stream_Read_UINT16(s, pad2OctetsB);
	WLog_INFO(TAG, "\tpreferredBitsPerPixel: 0x%04" PRIX16 "", preferredBitsPerPixel);
	WLog_INFO(TAG, "\treceive1BitPerPixel: 0x%04" PRIX16 "", receive1BitPerPixel);
	WLog_INFO(TAG, "\treceive4BitsPerPixel: 0x%04" PRIX16 "", receive4BitsPerPixel);
	WLog_INFO(TAG, "\treceive8BitsPerPixel: 0x%04" PRIX16 "", receive8BitsPerPixel);
	WLog_INFO(TAG, "\tdesktopWidth: 0x%04" PRIX16 "", desktopWidth);
	WLog_INFO(TAG, "\tdesktopHeight: 0x%04" PRIX16 "", desktopHeight);
	WLog_INFO(TAG, "\tpad2Octets: 0x%04" PRIX16 "", pad2Octets);
	WLog_INFO(TAG, "\tdesktopResizeFlag: 0x%04" PRIX16 "", desktopResizeFlag);
	WLog_INFO(TAG, "\tbitmapCompressionFlag: 0x%04" PRIX16 "", bitmapCompressionFlag);
	WLog_INFO(TAG, "\thighColorFlags: 0x%02" PRIX8 "", highColorFlags);
	WLog_INFO(TAG, "\tdrawingFlags: 0x%02" PRIX8 "", drawingFlags);
	WLog_INFO(TAG, "\tmultipleRectangleSupport: 0x%04" PRIX16 "", multipleRectangleSupport);
	WLog_INFO(TAG, "\tpad2OctetsB: 0x%04" PRIX16 "", pad2OctetsB);
	return TRUE;
}
