gen_hints(const unsigned char *data, int nhints) const
{
    _hint_csgen.clear();
    unsigned char mask = 0x80;
    for (int i = 0; i < nhints; i++) {
	if (*data & mask) {
	    double offset = (_stem_hstem[i] ? left_sidebearing().y : left_sidebearing().x);
	    _hint_csgen.gen_number(_stem_pos[i] - offset);
	    _hint_csgen.gen_number(_stem_width[i]);
	    _hint_csgen.gen_command(_stem_hstem[i] ? Cs::cHstem : Cs::cVstem);
	}
	if ((mask >>= 1) == 0)
	    data++, mask = 0x80;
    }
    return _hint_csgen.take_string();
}
