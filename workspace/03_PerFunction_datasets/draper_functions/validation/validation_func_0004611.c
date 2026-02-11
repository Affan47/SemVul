d(char x) const {

		if ( s[0] != x ) return fail_expr::make();


		if ( s.size() == 2 ) return char_expr::make(s[1]);

		std::string t(s, 1);
		return expr::make_ptr<str_expr>(t);
	}
