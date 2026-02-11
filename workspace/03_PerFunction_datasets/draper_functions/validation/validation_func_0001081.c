move_begin(unsigned i)
{
	struct pte *pe = &ptes[i];
	struct partition *p = pe->part_table;
	sector_t new, first, nr_sects;

	if (warn_geometry())
		return;
	nr_sects = get_nr_sects(p);
	if (!p->sys_ind || !nr_sects || IS_EXTENDED(p->sys_ind)) {
		printf("Partition %u has no data area\n", i + 1);
		return;
	}
	first = get_partition_start_from_dev_start(pe);
	new = read_int(0 , first, first + nr_sects - 1, first, "New beginning of data");
	if (new != first) {
		sector_t new_relative = new - pe->offset_from_dev_start;
		nr_sects += (get_start_sect(p) - new_relative);
		set_start_sect(p, new_relative);
		set_nr_sects(p, nr_sects);
		read_nonempty("Recalculate C/H/S values? (Y/N): ");
		if ((line_ptr[0] | 0x20) == 'y')
			set_hsc_start_end(p, new, new + nr_sects - 1);
		pe->changed = 1;
	}
}
