find_header_v1(u_long va)
{
	struct map_hdr_v1 *hdr;
	int found = 0;

	for(hdr = vas_map_base_v1; hdr; hdr = hdr->next)
		if((va >= hdr->start_va) && (va < hdr->end_va)) {
			found = 1;
			break;
		}
	if(found)
		return  hdr;
	else
		return (struct map_hdr_v1 *)0;
}
