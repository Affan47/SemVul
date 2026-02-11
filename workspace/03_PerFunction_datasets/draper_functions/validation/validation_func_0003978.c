Lset_dispatch_macro_character()
{
# line 2395 "read.d"

	int narg;
	register object *DPPbase=vs_base;
#define	dspchr	DPPbase[0]
#define	subchr	DPPbase[1]
#define	fnc	DPPbase[2]
#define	rdtbl	DPPbase[3+0]

	narg = vs_top - vs_base;
	if (narg < 3)
		too_few_arguments();
	if (narg <= 3 + 0) {
		vs_push(current_readtable());
		narg++;
	}
	if (narg > 3 + 1)
		too_many_arguments();

# line 2396 "read.d"

	check_type_character(&dspchr);
	check_type_character(&subchr);
	check_type_readtable(&rdtbl);
	if (rdtbl->rt.rt_self[char_code(dspchr)].rte_macro != dispatch_reader
	    || rdtbl->rt.rt_self[char_code(dspchr)].rte_dtab == NULL)
		FEerror("~S is not a dispatch character.", 1, dspchr);
	rdtbl->rt.rt_self[char_code(dspchr)]
	.rte_dtab[char_code(subchr)] = fnc;
	if ('a' <= char_code(subchr) && char_code(subchr) <= 'z')
		rdtbl->rt.rt_self[char_code(dspchr)]
		.rte_dtab[char_code(subchr) - ('a' - 'A')] = fnc;

	{
		vs_base[0] = Ct;
		vs_top = vs_base + 1;
		return;
	}
# line 2409 "read.d"

#undef dspchr
#undef subchr
#undef fnc
#undef rdtbl
}
