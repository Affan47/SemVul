sqstd_rex_free(SQRex *exp)
{
	if(exp)	{
		if(exp->_nodes) sq_free(exp->_nodes,exp->_nallocated * sizeof(SQRexNode));
		if(exp->_jmpbuf) sq_free(exp->_jmpbuf,sizeof(jmp_buf));
		if(exp->_matches) sq_free(exp->_matches,exp->_nsubexpr * sizeof(SQRexMatch));
		sq_free(exp,sizeof(SQRex));
	}
}
