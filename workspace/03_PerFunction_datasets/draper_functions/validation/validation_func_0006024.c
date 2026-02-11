bounds(const Transform &transform, const CharstringContext &g, int bb[4], int &width)
{
    CharstringBounds b(transform);
    b.char_bounds(g, false);
    return b.output(bb, width, true);
}
