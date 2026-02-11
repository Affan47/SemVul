zend_do_binary_assign_op(zend_uchar op, znode *result, const znode *op1, const znode *op2 TSRMLS_DC)
{
	int last_op_number = get_next_op_number(CG(active_op_array));
	zend_op *opline = get_next_op(CG(active_op_array) TSRMLS_CC);

	if (last_op_number > 0) {
		zend_op *last_op = &CG(active_op_array)->opcodes[last_op_number-1];

		switch (last_op->opcode) {
			case ZEND_FETCH_OBJ_RW:
				last_op->opcode = op;
				last_op->extended_value = ZEND_ASSIGN_OBJ;

				zend_do_op_data(opline, op2 TSRMLS_CC);
				SET_UNUSED(opline->result);
				*result = last_op->result;
				return;
			case ZEND_FETCH_DIM_RW:
				last_op->opcode = op;
				last_op->extended_value = ZEND_ASSIGN_DIM;

				zend_do_op_data(opline, op2 TSRMLS_CC);
				opline->op2.u.var = get_temporary_variable(CG(active_op_array));
				opline->op2.u.EA.type = 0;
				opline->op2.op_type = IS_VAR;
				SET_UNUSED(opline->result);
				*result = last_op->result;
				return;
			default:
				break;
		}
	}

	opline->opcode = op;
	opline->op1 = *op1;
	opline->op2 = *op2;
	opline->result.op_type = IS_VAR;
	opline->result.u.EA.type = 0;
	opline->result.u.var = get_temporary_variable(CG(active_op_array));
	*result = opline->result;
}
