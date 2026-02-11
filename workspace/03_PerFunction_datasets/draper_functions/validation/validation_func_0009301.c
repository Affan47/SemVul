vg_error_get_state (VgErrorParser *parser, pid_t pid)
{
	VgErrorListNode *n;

	if (!(n = g_hash_table_lookup (parser->pid_hash, GINT_TO_POINTER (pid))))
		return VG_ERROR_PARSER_STATE_INIT;

	return n->state;
}
