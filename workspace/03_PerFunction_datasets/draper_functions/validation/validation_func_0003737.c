allow(Efont::OpenType::Glyph glyph, const Vector<PermString>& glyph_names, uint32_t unicode, int ptype) const
{

    if (glyph < 0 || glyph >= glyph_names.size())
	return false;

    String glyph_name = glyph_names[glyph];
    int uniprop = -1;
    bool any_includes = false;
    bool included = false;


    for (const Pattern* p = _patterns.begin(); p < _patterns.end(); p++) {

	if ((p->type & ~T_TYPEMASK) != ptype)
	    continue;

	if ((p->type & T_EXCLUDE) == 0) {
	    if (included)
		continue;
	    any_includes = true;
	}

	bool match;
	if (p->data == D_NAME)
	    match = glob_match(glyph_name, p->pattern);
	else if (p->data == D_UNIPROP) {
	    if (uniprop < 0)
		uniprop = UnicodeProperty::property(unicode);
	    match = ((uniprop & p->u.uniprop.mask) == p->u.uniprop.value);
	} else
	    match = (unicode >= p->u.unirange.low && unicode <= p->u.unirange.high);

	if (match == ((p->type & T_NEGATE) == 0)) {
	    if ((p->type & T_EXCLUDE) == 0)
		included = true;
	    else
		return false;
	}
    }

    return !any_includes || included;
}
