compileSetExprFactor(void){
	Token::Type t=lexer->skipWS(ID_MODE);
	if (t==(int)'('){
		lexer->skip();
		TKVMSetCode_base *c=compileSetExpr0();
		if (!c) return NULL;
		t=lexer->skipWS(ID_MODE);
		if (t!=(int)')'){
			lexer->error(RC.S(ERR_COMPILER_SETEXPR_BLOCK_NOT_CLOSED));
		}else{
			lexer->skip();
		}
		return c;
	}else{
		return compileSetExprWord();
	}
}
