header_enumeration(TRANS_DECL *decl)
{
	PATTERN *look = JOB->current;
	bool is_public;
	int value = 0;

	check_public_private(&look, &is_public);

	if (!PATTERN_is(*look, RS_ENUM))
		return FALSE;
	look++;

	JOB->current = look;

	for(;;)
	{
		TRANS_newline();

		if (!PATTERN_is_identifier(*JOB->current))
			THROW("Syntax error. Identifier expected.");

		CLEAR(decl);

		decl->index = PATTERN_index(*JOB->current);
		JOB->current++;

		decl->type = TYPE_make(T_INTEGER, -1, 0);

		if (is_public) TYPE_set_flag(&decl->type, TF_PUBLIC);
		TYPE_set_kind(&decl->type, TK_CONST);

		if (TRANS_is(RS_EQUAL))
		{
			JOB->current = TRANS_get_constant_value(decl, JOB->current);
			value = decl->value + 1;
		}
		else
		{
			decl->value = value;
			value++;
		}

		CLASS_add_declaration(JOB->class, decl);

		if (TRANS_newline())
			break;

		if (!PATTERN_is(*JOB->current, RS_COMMA))
			THROW_UNEXPECTED(JOB->current);
		JOB->current++;
	}

	return TRUE;
}
