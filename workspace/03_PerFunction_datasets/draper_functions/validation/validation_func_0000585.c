is_variable_in_operand( int target_entry, symbol_kind target_kind,
                        Operand *opt, Quadruple *qpt, Boolean do_next )
{
    Quadruple *def_qpt;
    int i;

    if( opt->kind == KIND_VAR || opt->kind == KIND_ARRAY ){
        if( opt->kind == target_kind
            && (opt->entry == target_entry || target_entry == -1) )
            return TRUE;

        if( opt->inner != NULL
            && is_variable_in_operand(target_entry, target_kind, opt->inner, qpt, TRUE) )
            return TRUE;

    }else if( opt->kind == KIND_TEMP ){
        for( def_qpt = qpt->prev; def_qpt != NULL; def_qpt = def_qpt->prev ) {
            if( def_qpt->op[0]->kind == KIND_TEMP
                && def_qpt->op[0]->entry == opt->entry )
                break;
        }

        if( def_qpt != NULL && def_qpt->ope != OPE_DEREF ) {
	    for( i = 1; i < 4; i++ ){
		Operand *op = def_qpt->op[i];
		if( op != NULL
		    && is_variable_in_operand(target_entry, target_kind, op, def_qpt, TRUE) )
		    return TRUE;
	    }
	}
    }

    if( do_next && opt->next != NULL
        && is_variable_in_operand(target_entry, target_kind, opt->next, qpt, TRUE) )
        return TRUE;

    return FALSE;
}
