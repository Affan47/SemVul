static void amd_k7_smp_check(struct cpuinfo_x86 *c)
{

	if (!c->cpu_index)
		return;


	if ((c->x86_model == 6) && ((c->x86_mask == 0) ||
	    (c->x86_mask == 1)))
		return;


	if ((c->x86_model == 7) && (c->x86_mask == 0))
		return;


	if (((c->x86_model == 6) && (c->x86_mask >= 2)) ||
	    ((c->x86_model == 7) && (c->x86_mask >= 1)) ||
	     (c->x86_model > 7))
		if (cpu_has_mp)
			return;


	WARN_ONCE(1, "WARNING: This combination of AMD"
		" processors is not suitable for SMP.\n");
	add_taint(TAINT_UNSAFE_SMP, LOCKDEP_NOW_UNRELIABLE);
}
