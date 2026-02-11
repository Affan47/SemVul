draw(PainterInfo & pi, int x, int y) const
{
	FontSetChanger dummy(pi.base, "textnormal");
	InsetMathGrid::drawWithMargin(pi, x, y, 4, 2);
}
