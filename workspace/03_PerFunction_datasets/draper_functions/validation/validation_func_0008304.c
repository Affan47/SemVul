check_seq_header(Token *t)
#else
check_seq_header(t)
     Token *t;
#endif
{
	if(stmt_sequence_no >= SEQ_HEADER) {
	   syntax_error( (t == (Token *) NULL? line_num: t->line_num),
			NO_COL_NUM,
			"missing END statement inserted");
	   msg_tail( (t == (Token *) NULL? "at end of file":
		      "prior to statement") );

	   if( t != (Token *) NULL )
	     pop_block(t,tok_END,(char *)NULL,NO_LABEL);

	   END_processing(t);
	}
	stmt_sequence_no = SEQ_HEADER;
	f90_stmt_sequence_no = F90_SEQ_HEADER;
}
