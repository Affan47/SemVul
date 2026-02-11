InsertSpace(int position, int insertLength) {
	const bool atEnd = position == lengthDocument;
	lengthDocument += insertLength;
	for (Decoration *deco=root; deco; deco = deco->next) {
		deco->rs.InsertSpace(position, insertLength);
		if (atEnd) {
			deco->rs.FillRange(position, 0, insertLength);
		}
	}
}
