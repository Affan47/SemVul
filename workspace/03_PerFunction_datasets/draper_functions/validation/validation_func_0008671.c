PixelAt(int x, int y, ColourDesired &colour, bool &transparent) const {
	if (pixels.empty() || (x<0) || (x >= width) || (y<0) || (y >= height)) {
		colour = 0;
		transparent = true;
		return;
	}
	int code = pixels[y * width + x];
	transparent = code == codeTransparent;
	if (transparent) {
		colour = 0;
	} else {
		colour = ColourFromCode(code).AsLong();
	}
}
