make_passign(SemiBlockRec* sbp)
{
    while (sbp != NULL) {
	Statement*  head_stm;
	SemiBlockRec*  tail;
	Statement*  tail_stm;

	if ((head_stm = is_pheader(sbp)) != NULL) {
	    tail = search_tail(sbp, head_stm, &tail_stm);
	    if (tail != NULL
#ifdef  LIMIT_PASSIGN_LINE
		&& (tail_stm->line_no - head_stm->line_no
		    <= PSEUDO_ASSIGN_LINES)
#endif
		&& check_do_pseudo(sbp, tail, head_stm, tail_stm)) {
		sbp = fusion_statement(sbp, tail, head_stm, tail_stm);
	    } else {
		sbp = sbp->next;
	    }
	} else {
	    sbp = sbp->next;
	}
    }
}
