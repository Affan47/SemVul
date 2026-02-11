TRANS_affectation(bool dup)
{
	static TRANS_STATEMENT statement[] = {

		{ RS_OPEN, TRANS_open },
		{ RS_SHELL, TRANS_shell },
		{ RS_EXEC, TRANS_exec },
		{ RS_RAISE, TRANS_raise },
		{ RS_PIPE, TRANS_pipe },
		{ RS_LOCK, TRANS_lock },
		{ RS_MEMORY, TRANS_memory },

		{ RS_NONE, NULL }
	};

	TRANS_STATEMENT *st;
	PATTERN *look = JOB->current;
	PATTERN *left, *expr, *after;
	int niv = 0;
	bool equal = FALSE;
	bool stat = FALSE;
	int op;

	for(;;)
	{
		if (PATTERN_is_newline(*look))
			break;

		if (PATTERN_is(*look, RS_LBRA) || PATTERN_is(*look, RS_LSQR))
		{
			niv++;
		}
		else if (PATTERN_is(*look, RS_RBRA) || PATTERN_is(*look, RS_RSQR))
		{
			if (niv > 0)
				niv--;
		}
		else if (niv == 0)
		{
			if (PATTERN_is(*look, RS_EQUAL))
			{
				equal = TRUE;
				op = RS_NONE;
				break;
			}
			else if (PATTERN_is_reserved(*look) && RES_is_assignment(PATTERN_index(*look)))
			{
				equal = TRUE;
				op = RES_get_assignment_operator(PATTERN_index(*look));
				break;
			}
		}

		look++;
	}

	if (!equal)
		return FALSE;

	left = JOB->current;
	*look++ = PATTERN_make(RT_NEWLINE, 0);
	expr = look;

	JOB->current = expr;

	if (op == RS_NONE && (PATTERN_is_reserved(*JOB->current)))
	{
		if (TRANS_is(RS_NEW))
		{
			TRANS_in_affectation++;
			TRANS_new();
			TRANS_in_affectation--;
			stat = TRUE;
		}
		else
		{
			for (st = statement; st->id; st++)
			{
				if (TRANS_is(st->id))
				{
					TRANS_in_affectation++;
					(*st->func)();
					TRANS_in_affectation--;
					stat = TRUE;
				}
			}
		}
	}

	if (!stat)
	{
		if (op != RS_NONE)
		{
			JOB->current = left;
			TRANS_expression(FALSE);
		}

		JOB->current = expr;
		TRANS_expression(FALSE);
		after = JOB->current;

		if (op != RS_NONE)
			trans_operation(op, 2, NULL_PATTERN);
	}

	after = JOB->current;

	if (dup)
		CODE_dup();

	JOB->current = left;
	TRANS_reference();

	JOB->current = after;

	return TRUE;
}
