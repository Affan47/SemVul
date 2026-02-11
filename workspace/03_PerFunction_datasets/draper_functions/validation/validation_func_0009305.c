_KEYVALUEs(CTX ctx, kStmtExpr *stmt, tkitr_t *itr)
{
	int p = ITR_indexKEY(itr, +0), p_next;
	while(p < itr->e) {
		tkitr_t ebuf, *eitr = ITR_copy(itr, &ebuf, 0);
		eitr->c = p;
		p_next = ITR_indexKEY(eitr, +2);
		eitr->e = p_next;
		ITR_chop(eitr, TT_SEMICOLON);
		ITR_chop(eitr, TT_COMMA);
		if(ITR_size(eitr) > 2) {
			kTerm *tk = ITR_nextTK(eitr);
			TT_(tk) = TT_STR;
			knh_Stmt_add(ctx, stmt, tk);
			DBG_ASSERT(ITR_is(eitr, TT_COLON));
			ITR_next(eitr);
			if(!ITR_hasNext(eitr)) {
				knh_Stmt_add(ctx, stmt, new_Term(ctx, TT_NULL));
				return;
			}
			if(ITR_count(eitr, TT_COMMA) == 0) {
				_EXPR(ctx, stmt, eitr);
			}
			else {
				kStmtExpr *stmtARRAY = Stmt_addNewStmt(ctx, stmt, STT_NEW);
				_ARRAY(ctx, stmtARRAY, MN_newLIST, CLASS_Array, eitr);
			}
		}
		p = p_next;
	}
}
