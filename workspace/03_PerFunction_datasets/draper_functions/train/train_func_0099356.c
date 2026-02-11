dgap_ports_digi_flag_show(struct device *p,
					 struct device_attribute *attr,
					 char *buf)
{
	struct board_t *bd;
	int count = 0;
	unsigned int i;

	bd = dgap_verify_board(p);
	if (!bd)
		return 0;

	for (i = 0; i < bd->nasync; i++)
		count += snprintf(buf + count, PAGE_SIZE - count, "%d %x\n",
				  bd->channels[i]->ch_portnum,
				  bd->channels[i]->ch_digi.digi_flags);
	return count;
}
