gen
	(
	vector<char>& out,
	Uc_function *fun
	)
	{
	if (!stmt)
		return;
	out.push_back((char) UC_LOOP);
	int top = out.size();
	out.push_back((char) UC_LOOPTOP);
	Write2(out, index->get_offset());
	Write2(out, array_size->get_offset());
	Write2(out, var->get_offset());
	Write2(out, array->get_offset());

	int testlen = out.size() + 2 - top;
	vector<char> stmt_code;
	stmt_code.reserve(4000);
	fun->start_breakable(this);
	fun->adjust_reloffset(out.size() + 2);
	stmt->gen(stmt_code, fun);
	fun->adjust_reloffset(-out.size() - 2);

	int dist = testlen + stmt_code.size() + 3;
	stmt_code.push_back((char) UC_JMP);
	Write2(stmt_code, -dist);
	int stmtlen = stmt_code.size();
	Write2(out, stmtlen);
	fun->end_breakable(this, stmt_code);

	out.insert(out.end(), stmt_code.begin(), stmt_code.end());
	}
