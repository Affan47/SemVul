ompfbe_upgrade_temp_var_statement(Statement *stm)
{
    Module_table *module = stm->pe_stm->block->module;
    Quadruple *quad;


    for (quad = get_qr_with_tmp_before_sync(stm->qr_head);
	 quad != NULL;
	 quad = get_qr_with_tmp_before_sync(get_next_sync_qr(quad->next))) {

        if (quad->op[0] != NULL && quad->op[0]->kind == KIND_TEMP) {
            Temp_table *temp = quad->op[0]->tbl.t;
            Operand *new_op;
            Var_table *new_var;


            new_var = get_new_var(&module->var_head);
            new_var->name = create_new_name(new_var->entry, KIND_VAR);
            new_var->type = temp->type;
	    new_var->type_entry = temp->type_entry;
            new_var->size = temp->size;
            new_var->length_dummy = temp->length_dummy;
            new_var->node = NULL;
            new_var->kind = MEM_LM;
            new_var->save = FALSE;
            new_var->next = NULL;

            new_op = alloc_operand();
            new_op->entry = new_var->entry;
            new_op->kind = KIND_VAR;
            new_op->tbl.v = new_var;


            replace_temp_operand_by_copy(quad->next, temp, new_op);


            insert_qr(stm, quad, OPE_ASSIGN, new_op, quad->op[0], NULL, NULL);
	}
    }
}
