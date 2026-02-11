final_check_s(const struct ebt_u_entry *entry,
   const struct ebt_entry_target *target, const char *name,
   unsigned int hookmask, unsigned int time)
{
	struct ebt_nat_info *natinfo = (struct ebt_nat_info *)target->data;

	if (BASE_CHAIN && (natinfo->target | ~EBT_VERDICT_BITS) == EBT_RETURN) {
		ebt_print_error("--snat-target RETURN not allowed on base chain");
		return;
	}
	CLEAR_BASE_CHAIN_BIT;
	if ((hookmask & ~(1 << NF_BR_POST_ROUTING)) || strcmp(name, "nat")) {
		ebt_print_error("Wrong chain for snat");
	} else if (time == 0 && to_source_supplied == 0)
		ebt_print_error("No snat address supplied");
}
