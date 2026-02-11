zend_do_end_function_call(znode *function_name, znode *result, const znode *argument_list, int is_method, int is_dynamic_fcall TSRMLS_DC)
{
	zend_op *opline;

	if (is_method && function_name && function_name->op_type == IS_UNUSED) {

		if (Z_LVAL(argument_list->u.constant) != 0) {
			zend_error(E_WARNING, "Clone method does not require arguments");
		}
		opline = &CG(active_op_array)->opcodes[Z_LVAL(function_name->u.constant)];
	} else {
		opline = get_next_op(CG(active_op_array) TSRMLS_CC);
		if (!is_method && !is_dynamic_fcall && function_name->op_type==IS_CONST) {
			opline->opcode = ZEND_DO_FCALL;
			SET_NODE(opline->op1, function_name);
			CALCULATE_LITERAL_HASH(opline->op1.constant);
			GET_CACHE_SLOT(opline->op1.constant);
		} else {
			opline->opcode = ZEND_DO_FCALL_BY_NAME;
			SET_UNUSED(opline->op1);
		}
	}

	opline->result.var = get_temporary_variable(CG(active_op_array));
	opline->result_type = IS_VAR;
	GET_NODE(result, opline->result)	;
	SET_UNUSED(opline->op2);

	zend_stack_del_top(&CG(function_call_stack));
	opline->extended_value = Z_LVAL(argument_list->u.constant);
}
