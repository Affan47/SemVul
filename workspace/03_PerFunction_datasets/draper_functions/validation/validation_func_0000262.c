_CODE(CTX ctx, kStmtExpr *stmt, tkitr_t *itr)
{
	size_t i, hasCODE = 0;;
	for(i = 0; i < DP(stmt)->size; i++) {
		if(TT_(tkNN(stmt, i)) == TT_DOC) {
			hasCODE = 1; break;
		}
	}
	if(ITR_is(itr, TT_CODE)) {
		if(hasCODE) {
			WARN_Ignored(ctx, "block", CLASS_unknown, S_totext(ITR_nextTK(itr)->text));
		}
		else {
			_CODEDOC(ctx, stmt, itr);
			knh_Stmt_add(ctx, stmt, ITR_nextTK(itr));
		}
	}
	else if(ITR_is(itr, TT_DARROW) || ITR_is(itr, TT_COLON)) {
		tkitr_t stmtbuf, *stmtitr = ITR_stmt(ctx, itr, +1, &stmtbuf, 1);
		if(hasCODE) {
			WARN_Ignored(ctx, "=>", CLASS_unknown, NULL);
		}
		else {
			_CODEDOC(ctx, stmt, stmtitr);
			stmtitr->c += 1;
			_RETURNEXPR(ctx, stmt, stmtitr);
		}
	}
	else if(ITR_is(itr, TT_WITH)) {
		tkitr_t stmtbuf, *stmtitr = ITR_stmt(ctx, itr, +1, &stmtbuf, 1);
		if(hasCODE) {
			WARN_Ignored(ctx, "with", CLASS_unknown, NULL);
		}
		else {
			StmtMETHOD_setFFI(stmt, 1);
			stmtitr->c += 1;
			_EXPR(ctx, stmt, stmtitr);
			DBG_P("WITH DP(stmt)->size=%d", DP(stmt)->size);
		}
	}
	else {
		_SEMICOLON(ctx, stmt, itr);
	}
}
