SetSelection(SelectionPosition currentPos_, SelectionPosition anchor_) {
	currentPos_ = ClampPositionIntoDocument(currentPos_);
	anchor_ = ClampPositionIntoDocument(anchor_);
	int currentLine = pdoc->LineFromPosition(currentPos_.Position());


	if (sel.selType == Selection::selLines) {
		if (currentPos_ > anchor_) {
			anchor_ = SelectionPosition(pdoc->LineStart(pdoc->LineFromPosition(anchor_.Position())));
			currentPos_ = SelectionPosition(pdoc->LineEnd(pdoc->LineFromPosition(currentPos_.Position())));
		} else {
			currentPos_ = SelectionPosition(pdoc->LineStart(pdoc->LineFromPosition(currentPos_.Position())));
			anchor_ = SelectionPosition(pdoc->LineEnd(pdoc->LineFromPosition(anchor_.Position())));
		}
	}
	SelectionRange rangeNew(currentPos_, anchor_);
	if (sel.Count() > 1 || !(sel.RangeMain() == rangeNew)) {
		InvalidateSelection(rangeNew);
	}
	sel.RangeMain() = rangeNew;
	SetRectangularRange();
	ClaimSelection();

	if (highlightDelimiter.NeedsDrawing(currentLine)) {
		RedrawSelMargin();
	}
}
