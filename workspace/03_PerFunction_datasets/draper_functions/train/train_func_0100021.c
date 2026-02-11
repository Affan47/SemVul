pdata_print(register const u_char * pptr, register u_int len,
	    u_int16_t op_msk, int indent)
{
	const struct pathdata_h *pdh = (struct pathdata_h *)pptr;
	char *ib = indent_pr(indent, 0);
	u_int minsize = 0;

	TCHECK(*pdh);
	if (len < sizeof(struct pathdata_h))
		goto trunc;
	if (vflag >= 3) {
		printf("\n%sPathdata: Flags 0x%x ID count %d\n",
		       ib, EXTRACT_16BITS(&pdh->pflags), EXTRACT_16BITS(&pdh->pIDcnt));
	}

	if (EXTRACT_16BITS(&pdh->pflags) & F_SELKEY) {
		op_msk |= B_KEYIN;
	}
	pptr += sizeof(struct pathdata_h);
	len -= sizeof(struct pathdata_h);
	minsize = EXTRACT_16BITS(&pdh->pIDcnt) * 4;
	if (len < minsize) {
		printf("\t\t\ttruncated IDs expected %uB got %uB\n", minsize,
		       len);
		hex_print_with_offset("\t\t\tID Data[", pptr, len, 0);
		printf("]\n");
		return -1;
	}
	return pdatacnt_print(pptr, len, EXTRACT_16BITS(&pdh->pIDcnt), op_msk, indent);

trunc:
	fputs("[|forces]", stdout);
	return -1;
}
