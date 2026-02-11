buildin_csvwrite(struct script_state *st)
{
	char *file = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int  row   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int  col   = conv_num(st,& (st->stack->stack_data[st->start+4]));
	struct csvdb_data *csv;

	if( !script_csvfilename_check(file, "buildin_csvwrite") )
		return 0;
	csv = script_csvload( file );

	if( isstr(&st->stack->stack_data[st->start+5]) ) {
		char *str = conv_str(st,& (st->stack->stack_data[st->start+5]));
		csvdb_set_str(csv, row, col, str);
	} else {
		int   val = conv_num(st,& (st->stack->stack_data[st->start+5]));
		csvdb_set_num(csv, row, col, val);
	}
	return 0;
}
