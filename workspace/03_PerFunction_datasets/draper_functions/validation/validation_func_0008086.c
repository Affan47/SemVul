IsDocCommentEnd(StyleContext &sc) {
	return sc.ch == '#' && sc.chNext == 'e';
}
