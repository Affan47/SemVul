mDIGITS(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = DIGITS;
	std::string::size_type _saveIndex;

	{
	int _cnt123=0;
	for (;;) {
		if (((LA(1) >= 0x30   && LA(1) <= 0x39  ))) {
			matchRange('0','9');
		}
		else {
			if ( _cnt123>=1 ) { goto _loop123; } else {throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());}
		}

		_cnt123++;
	}
	_loop123:;
	}
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}
