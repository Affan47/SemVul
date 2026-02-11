expect(int kind, bool report_error)
{


    if (_tpos != _tfull) {
	if (_tcircle[_tpos].is(kind)) {
	    _tpos = (_tpos + 1) % TCIRCLE_SIZE;
	    return true;
	}
	if (report_error)
	    lerror(_tcircle[_tpos], "expected %s", lexeme_string(kind).c_str());
    } else {
	String old_filename = _filename;
	unsigned old_lineno = _lineno;
	const char *old_pos = _pos;
	if (next_lexeme().is(kind))
	    return true;
	_filename = old_filename;
	_lineno = old_lineno;
	if (report_error)
	    lerror(old_pos, _pos, "expected %s", lexeme_string(kind).c_str());
	_pos = old_pos;
    }
    return false;
}
