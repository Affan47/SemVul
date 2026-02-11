zend_do_begin_qm_op(const znode *cond, znode *qm_token TSRMLS_DC)
{
	int jmpz_op_number = get_next_op_number(CG(active_op_array));
	zend_op *opline;

	opline = get_next_op(CG(active_op_array) TSRMLS_CC);

	opline->opcode = ZEND_JMPZ;
	opline->op1 = *cond;
	SET_UNUSED(opline->op2);
	opline->op2.u.opline_num = jmpz_op_number;
	*qm_token = opline->op2;

	INC_BPC(CG(active_op_array));
}
