CopySelectionRange(SelectionText *ss, bool allowLineCopy) {
	if (sel.Empty()) {
		if (allowLineCopy) {
			int currentLine = pdoc->LineFromPosition(sel.MainCaret());
			int start = pdoc->LineStart(currentLine);
			int end = pdoc->LineEnd(currentLine);

			char *text = CopyRange(start, end);
			int textLen = text ? strlen(text) : 0;

			textLen += 3;
			char *textWithEndl = new char[textLen];
			textWithEndl[0] = '\0';
			if (text)
				strncat(textWithEndl, text, textLen);
			if (pdoc->eolMode != SC_EOL_LF)
				strncat(textWithEndl, "\r", textLen);
			if (pdoc->eolMode != SC_EOL_CR)
				strncat(textWithEndl, "\n", textLen);
			ss->Set(textWithEndl, strlen(textWithEndl) + 1,
				pdoc->dbcsCodePage, vs.styles[STYLE_DEFAULT].characterSet, false, true);
			delete []text;
		}
	} else {
		int delimiterLength = 0;
		if (sel.selType == Selection::selRectangle) {
			if (pdoc->eolMode == SC_EOL_CRLF) {
				delimiterLength = 2;
			} else {
				delimiterLength = 1;
			}
		}
		int size = sel.Length() + delimiterLength * sel.Count();
		char *text = new char[size + 1];
		int j = 0;
		std::vector<SelectionRange> rangesInOrder = sel.RangesCopy();
		if (sel.selType == Selection::selRectangle)
			std::sort(rangesInOrder.begin(), rangesInOrder.end());
		for (size_t r=0; r<rangesInOrder.size(); r++) {
			SelectionRange current = rangesInOrder[r];
			for (int i = current.Start().Position();
			        i < current.End().Position();
			        i++) {
				text[j++] = pdoc->CharAt(i);
			}
			if (sel.selType == Selection::selRectangle) {
				if (pdoc->eolMode != SC_EOL_LF) {
					text[j++] = '\r';
				}
				if (pdoc->eolMode != SC_EOL_CR) {
					text[j++] = '\n';
				}
			}
		}
		text[size] = '\0';
		ss->Set(text, size + 1, pdoc->dbcsCodePage,
			vs.styles[STYLE_DEFAULT].characterSet, sel.IsRectangular(), sel.selType == Selection::selLines);
	}
}
