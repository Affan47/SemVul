pr_arg_table(FILE *fp, Operand *argument_head)
{
    Operand	*op_ptr;

    op_ptr = argument_head;

    if (op_ptr != NULL) {
	fputs(" %% *** Argument Table ***\n", fp);
	fputs(" argument {\n", fp);

	while (op_ptr != NULL) {
	    fputs("  ", fp);
	    pr_operand(fp, op_ptr);
	    fputs(";\n", fp);
	    op_ptr = op_ptr->next;
	}

	fputs(" } %% argument\n\n", fp);
    }
}
