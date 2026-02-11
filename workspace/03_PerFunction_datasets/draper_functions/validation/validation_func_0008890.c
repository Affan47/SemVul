copy_pe_statement_with_mpt(Module_table *mpt, Pe_statement *ppt)
{
    Pe_statement *new_ppt = NULL;

    if (ppt != NULL) {
	new_ppt = alloc_pe_statement();
	new_ppt->vpe_no = ppt->vpe_no;
	new_ppt->dt_init = NULL;
	new_ppt->dt_head = NULL;
	new_ppt->prev = NULL;
	new_ppt->next = NULL;

	new_ppt->stm_head = copy_stm_list_with_mpt(mpt, ppt->stm_head);
	fit_link_pe_statement_and_statement(new_ppt,new_ppt->stm_head);
    }
    return(new_ppt);
}
