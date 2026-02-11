compile(VStateless_class* aclass,
					const char* source, const String* main_alias,
					uint file_no,
					int line_no_offset) {

	Parse_control pc(*this, aclass, source, main_alias, file_no, line_no_offset);


	if(yyparse(&pc)) {
		pc.pos_prev_c();
		if(!pc.explicit_result)
			if(pc.pos.col==0)
				pc.pos_prev_c();

		throw Exception("parser.compile",
			0,
			"%s(%d:%d): %s",  file_list[file_no].cstr(), 1+pc.pos.line, 1+pc.pos.col,  pc.error);
	}


	return *pc.cclasses;
}
