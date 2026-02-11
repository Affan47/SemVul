ColouriseMakeDoc(unsigned int startPos, int length, int, WordList *[], Accessor &styler) {
	char lineBuffer[1024];
	styler.StartAt(startPos);
	styler.StartSegment(startPos);
	unsigned int linePos = 0;
	unsigned int startLine = startPos;
	for (unsigned int i = startPos; i < startPos + length; i++) {
		lineBuffer[linePos++] = styler[i];
		if (AtEOL(styler, i) || (linePos >= sizeof(lineBuffer) - 1)) {

			lineBuffer[linePos] = '\0';
			ColouriseMakeLine(lineBuffer, linePos, startLine, i, styler);
			linePos = 0;
			startLine = i + 1;
		}
	}
	if (linePos > 0) {
		ColouriseMakeLine(lineBuffer, linePos, startLine, startPos + length - 1, styler);
	}
}
