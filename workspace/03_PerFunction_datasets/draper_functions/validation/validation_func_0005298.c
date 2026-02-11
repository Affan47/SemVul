Realise(Surface &surface, int zoomLevel, int technology, const FontSpecification &fs) {
	PLATFORM_ASSERT(fs.fontName);
	sizeZoomed = fs.size + zoomLevel * SC_FONT_SIZE_MULTIPLIER;
	if (sizeZoomed <= 2 * SC_FONT_SIZE_MULTIPLIER)
		sizeZoomed = 2 * SC_FONT_SIZE_MULTIPLIER;

	float deviceHeight = surface.DeviceHeightFont(sizeZoomed);
	FontParameters fp(fs.fontName, deviceHeight / SC_FONT_SIZE_MULTIPLIER, fs.weight, fs.italic, fs.extraFontFlag, technology, fs.characterSet);
	font.Create(fp);

	ascent = surface.Ascent(font);
	descent = surface.Descent(font);
	aveCharWidth = surface.AverageCharWidth(font);
	spaceWidth = surface.WidthChar(font, ' ');
}
