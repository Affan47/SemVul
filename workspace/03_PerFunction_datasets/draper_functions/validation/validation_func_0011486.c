unparse(Vector<Substitution> &v, bool is_alternate) const
{
    Vector<Glyph> result;
    for (Coverage::iterator i = coverage().begin(); i; i++) {
	Data seq = _d.offset_subtable(HEADERSIZE + i.coverage_index()*RECSIZE);
	result.clear();
	for (int j = 0; j < seq.u16(0); j++)
	    result.push_back(seq.u16(SEQ_HEADERSIZE + j*SEQ_RECSIZE));
	v.push_back(Substitution(*i, result, is_alternate));
    }
}
