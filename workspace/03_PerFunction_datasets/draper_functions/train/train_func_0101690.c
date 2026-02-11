c_backtrace(state_t *s)
{
	int i;

	if (!_debugstate_valid) {
		sciprintf("Not in debug state\n");
		return 1;
	}

	sciprintf("Call stack (current base: 0x%x):\n", s->execution_stack_base);
	for (i = 0; i <= s->execution_stack_pos; i++) {
		exec_stack_t *call = &(s->execution_stack[i]);
		const char *objname = obj_get_name(s, call->sendp);
		int paramc, totalparamc;

		switch (call->type) {

		case EXEC_STACK_TYPE_CALL: {
			sciprintf(" %x:[%x]  %s::%s(", i, call->origin,
				  objname, (call->selector == -1)? "<call[be]?>":
				  selector_name(s,call->selector));
		}
			break;

		case EXEC_STACK_TYPE_KERNEL:
			sciprintf(" %x:[%x]  k%s(", i, call->origin, s->kernel_names[-(call->selector)-42]);
			break;

		case EXEC_STACK_TYPE_VARSELECTOR:
			sciprintf(" %x:[%x] vs%s %s::%s (", i, call->origin, (call->argc)? "write" : "read",
				  objname, s->selector_names[call->selector]);
			break;
		}

		totalparamc = call->argc;

		if (totalparamc > 16)
			totalparamc = 16;

		for (paramc = 1; paramc <= totalparamc; paramc++) {
			sciprintf(PREG, PRINT_REG(call->variables_argp[paramc]));

			if (paramc < call->argc)
				sciprintf(", ");
		}

		if (call->argc > 16)
			sciprintf("...");

		sciprintf(")\n    obj@"PREG,
			  PRINT_REG(call->objp));
		if (call->type == EXEC_STACK_TYPE_CALL) {
			sciprintf(" pc="PREG,
				  PRINT_REG(call->addr.pc));
			if (call->sp == CALL_SP_CARRY)
				sciprintf(" sp,fp:carry");
			else {
				sciprintf(" sp="PSTK,
					  PRINT_STK(call->sp));
				sciprintf(" fp="PSTK,
					  PRINT_STK(call->fp));
			}
		} else
			sciprintf(" pc:none");

		sciprintf(" argp:"PSTK, PRINT_STK(call->variables_argp));
		if (call->type == EXEC_STACK_TYPE_CALL)
			sciprintf(" script: %d", s->seg_manager.heap[call->addr.pc.segment]->data.script.nr);
		sciprintf("\n");
	}
	return 0;
}
