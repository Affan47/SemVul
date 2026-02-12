static blkid_partition new_partition(blkid_partlist ls, blkid_parttable tab)
{
	blkid_partition par;

	if (ls->nparts + 1 > ls->nparts_max) {


		void *tmp = realloc(ls->parts, (ls->nparts_max + 32) *
					sizeof(struct blkid_struct_partition));
		if (!tmp)
			return NULL;
		ls->parts = tmp;
		ls->nparts_max += 32;
	}

	par = &ls->parts[ls->nparts++];
	memset(par, 0, sizeof(struct blkid_struct_partition));

	ref_parttable(tab);
	par->tab = tab;
	par->partno = blkid_partlist_increment_partno(ls);

	return par;
}
