GetBoundingBlock() const
{
    register int n, count = m_blocks.GetCount();
    if (count == 0) return wxEmptyBlockInt;
    wxBlockInt bound = m_blocks[0];
    for (n=1; n<count; n++) bound.Union(m_blocks[n]);
    return bound;
}
