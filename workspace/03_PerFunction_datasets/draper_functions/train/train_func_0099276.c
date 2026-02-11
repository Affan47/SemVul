get_reload_before_node(struct compilation_unit *cu,
		       struct live_interval *interval,
		       unsigned long *bc_offset)
{
	unsigned long start;
	struct insn *insn;

	start = interval_start(interval);

	if (start & 1) {


		if (first_use_pos(interval) == interval_start(interval))
			error("interval begins with a def-use and is marked for reload");

		insn = radix_tree_lookup(cu->lir_insn_map, start - 1);
		*bc_offset = insn_get_bc_offset(insn);
		return insn->insn_list_node.next;
	}

	insn = radix_tree_lookup(cu->lir_insn_map, start);
	*bc_offset = insn_get_bc_offset(insn);
	return &insn->insn_list_node;
}
