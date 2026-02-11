gf_odf_dump_com_list(GF_List *commandList, FILE *trace, u32 indent, Bool XMTDump)
{
	GF_ODCom *com;
	u32 i;
	i=0;
	while ((com = (GF_ODCom *)gf_list_enum(commandList, &i))) {
		gf_odf_dump_com(com, trace, indent, XMTDump);
	}
	return GF_OK;
}
