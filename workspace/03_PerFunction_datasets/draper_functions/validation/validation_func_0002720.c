unparse_automatics(Vector<Positioning> &v, ErrorHandler *errh) const
{
    uint32_t ntables = this->ntables();
    uint32_t off = first_offset();
    int success = 0;
    if (_error < 0)
	return false;

    for (uint16_t i = 0; i < ntables; ++i) {
	Data subt = _d.subtable(off);
	uint16_t coverage = subt.u16(4);

	if (_version == 0) {
	    if ((coverage & COV_V0_HORIZONTAL) == 0
		|| (coverage & (COV_V0_MINIMUM | COV_V0_CROSS_STREAM
				| COV_V0_OVERRIDE)) != 0
		|| (coverage & COV_V0_FORMAT) != COV_V0_FORMAT0)
		continue;
	} else {
	    if ((coverage & (COV_V1_VERTICAL | COV_V1_CROSS_STREAM
			     | COV_V1_VARIATION)) != 0
		|| (coverage & COV_V1_FORMAT) != COV_V1_FORMAT0)
		continue;
	}

	try {
	    uint32_t off = (_version ? 16 : 14);
	    uint16_t npairs = subt.u16(off - 8);
	    for (uint16_t j = 0; j < npairs; ++j, off += 6) {
		v.push_back(Positioning(Position(subt.u16(off), 0, 0, subt.s16(off + 4), 0),
					Position(subt.u16(off + 2), 0, 0, 0, 0)));
		++success;
	    }
	} catch (Error e) {
	    if (errh)
		errh->warning("%s, continuing", e.description.c_str());
	}
    }

    return success > 0;
}

}}
