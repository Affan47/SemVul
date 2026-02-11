RefreshPixMaps(Surface *surfaceWindow) {
	if (!pixmapSelPattern->Initialised()) {
		const int patternSize = 8;
		pixmapSelPattern->InitPixMap(patternSize, patternSize, surfaceWindow, wMain.GetID());


		PRectangle rcPattern(0, 0, patternSize, patternSize);


		ColourDesired colourFMFill = vs.selbar;
		ColourDesired colourFMStripes = vs.selbarlight;

		if (!(vs.selbarlight == ColourDesired(0xff, 0xff, 0xff))) {


			colourFMFill = vs.selbarlight;
		}

		if (vs.foldmarginColourSet) {

			colourFMFill = vs.foldmarginColour;
		}
		if (vs.foldmarginHighlightColourSet) {

			colourFMStripes = vs.foldmarginHighlightColour;
		}

		pixmapSelPattern->FillRectangle(rcPattern, colourFMFill);
		for (int y = 0; y < patternSize; y++) {
			for (int x = y % 2; x < patternSize; x+=2) {
				PRectangle rcPixel(x, y, x+1, y+1);
				pixmapSelPattern->FillRectangle(rcPixel, colourFMStripes);
			}
		}
	}

	if (!pixmapIndentGuide->Initialised()) {

		pixmapIndentGuide->InitPixMap(1, vs.lineHeight + 1, surfaceWindow, wMain.GetID());
		pixmapIndentGuideHighlight->InitPixMap(1, vs.lineHeight + 1, surfaceWindow, wMain.GetID());
		PRectangle rcIG(0, 0, 1, vs.lineHeight);
		pixmapIndentGuide->FillRectangle(rcIG, vs.styles[STYLE_INDENTGUIDE].back);
		pixmapIndentGuide->PenColour(vs.styles[STYLE_INDENTGUIDE].fore);
		pixmapIndentGuideHighlight->FillRectangle(rcIG, vs.styles[STYLE_BRACELIGHT].back);
		pixmapIndentGuideHighlight->PenColour(vs.styles[STYLE_BRACELIGHT].fore);
		for (int stripe = 1; stripe < vs.lineHeight + 1; stripe += 2) {
			PRectangle rcPixel(0, stripe, 1, stripe+1);
			pixmapIndentGuide->FillRectangle(rcPixel, vs.styles[STYLE_INDENTGUIDE].fore);
			pixmapIndentGuideHighlight->FillRectangle(rcPixel, vs.styles[STYLE_BRACELIGHT].fore);
		}
	}

	if (bufferedDraw) {
		if (!pixmapLine->Initialised()) {
			PRectangle rcClient = GetClientRectangle();
			pixmapLine->InitPixMap(rcClient.Width(), vs.lineHeight,
			        surfaceWindow, wMain.GetID());
			pixmapSelMargin->InitPixMap(vs.fixedColumnWidth,
			        rcClient.Height(), surfaceWindow, wMain.GetID());
		}
	}
}
