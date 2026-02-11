copySubImage(fipImage& dst, int left, int top, int right, int bottom) const {
	if(_dib) {
		dst = FreeImage_Copy(_dib, left, top, right, bottom);
		return dst.isValid();
	}
	return FALSE;
}
