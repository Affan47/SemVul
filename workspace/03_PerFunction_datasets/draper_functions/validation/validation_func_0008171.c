exp_i_remove(
    Tcl_Interp *interp,
    struct exp_i **ei,
    struct exp_i *exp_i)
{

	for (;*ei; ei = &(*ei)->next) {
		if (*ei == exp_i) {
			*ei = exp_i->next;
			exp_i->next = 0;
			exp_free_i(interp,exp_i,exp_indirect_update2);
			break;
		}
	}
}
