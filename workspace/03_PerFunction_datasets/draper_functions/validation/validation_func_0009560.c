ClearSelection() {
	if (!sel.IsRectangular())
		FilterSelections();
	UndoGroup ug(pdoc);
	for (size_t r=0; r<sel.Count(); r++) {
		if (!sel.Range(r).Empty()) {
			if (!RangeContainsProtected(sel.Range(r).Start().Position(),
				sel.Range(r).End().Position())) {
				pdoc->DeleteChars(sel.Range(r).Start().Position(),
					sel.Range(r).Length());
				sel.Range(r) = sel.Range(r).Start();
			}
		}
	}
	ThinRectangularRange();
	sel.RemoveDuplicates();
	ClaimSelection();
}
