collect_statement(Pe_statement *pe_head, Statement *spt)
{
    Statement *rpt = NULL, *tpt;

    if (pe_head != NULL) {
	for (rpt = pe_head->stm_head;
	     rpt != spt && rpt != NULL;
	     rpt = rpt->next);

	if (rpt->prev == NULL) {
	    if (rpt->next == NULL) {
		pe_head->stm_head = NULL;
	    } else {
		rpt->next->prev = NULL;
		pe_head->stm_head = rpt->next;
	    }
	} else {
	    if (rpt->next == NULL) {
		rpt->prev->next = NULL;
		for (tpt = rpt->prev; tpt != NULL && tpt->prev != NULL; tpt = tpt->prev);
		pe_head->stm_head = tpt;
	    } else {
		rpt->prev->next = rpt->next;
		rpt->next->prev = rpt->prev;
		for (tpt = spt->next; tpt != NULL && tpt->prev != NULL; tpt = tpt->prev);
		pe_head->stm_head = tpt;
		rpt->prev = NULL;
		rpt->next = NULL;
	    }
	}
    }
    return rpt;
}
