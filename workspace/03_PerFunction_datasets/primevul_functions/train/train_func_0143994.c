int DIVERT_REG_NAME(isdn_divert_if *i_div)
{
	if (i_div->if_magic != DIVERT_IF_MAGIC)
		return (DIVERT_VER_ERR);
	switch (i_div->cmd)
	{
	case DIVERT_CMD_REL:
		if (divert_if != i_div)
			return (DIVERT_REL_ERR);
		divert_if = NULL;
		return (DIVERT_NO_ERR);

	case DIVERT_CMD_REG:
		if (divert_if)
			return (DIVERT_REG_ERR);
		i_div->ll_cmd = isdn_command;
		i_div->drv_to_name = map_drvname;
		i_div->name_to_drv = map_namedrv;
		divert_if = i_div;
		return (DIVERT_NO_ERR);

	default:
		return (DIVERT_CMD_ERR);
	}
}
