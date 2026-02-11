t_src_conflict(struct rc_src_register a, struct rc_src_register b)
{
	unsigned long aclass = t_src_class(a.File);
	unsigned long bclass = t_src_class(b.File);

	if (aclass != bclass)
		return 0;
	if (aclass == PVS_SRC_REG_TEMPORARY)
		return 0;

	if (a.RelAddr || b.RelAddr)
		return 1;
	if (a.Index != b.Index)
		return 1;

	return 0;
}
