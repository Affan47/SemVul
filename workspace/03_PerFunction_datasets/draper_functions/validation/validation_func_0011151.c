ips_poll_for_flush_complete(ips_ha_t * ha)
{
	IPS_STATUS cstatus;

	while (TRUE) {
	    cstatus.value = (*ha->func.statupd) (ha);

	    if (cstatus.value == 0xffffffff)
			break;


	    if (cstatus.fields.command_id == IPS_MAX_CMDS)
	        return 1;
	 }

	return 0;
}
