SV_EmitPacketEntities (client_frame_t *from, client_frame_t *to, sizebuf_t *msg)
{
	entity_state_t	*oldent=NULL, *newent=NULL;
	int		oldindex, newindex;
	int		oldnum, newnum;
	int		from_num_entities;
	int		bits;

#if 0
	if (numprojs)
		MSG_WriteByte (msg, svc_packetentities2);
	else
#endif
		MSG_WriteByte (msg, svc_packetentities);

	if (!from)
		from_num_entities = 0;
	else
		from_num_entities = from->num_entities;

	newindex = 0;
	oldindex = 0;
	while (newindex < to->num_entities || oldindex < from_num_entities)
	{
		if (newindex >= to->num_entities)
			newnum = 9999;
		else
		{
			newent = &svs.client_entities[(to->first_entity+newindex)%svs.num_client_entities];
			newnum = newent->number;
		}

		if (oldindex >= from_num_entities)
			oldnum = 9999;
		else
		{
			oldent = &svs.client_entities[(from->first_entity+oldindex)%svs.num_client_entities];
			oldnum = oldent->number;
		}

		if (newnum == oldnum)
		{


			MSG_WriteDeltaEntity (oldent, newent, msg, false, newent->number <= maxclients->value);
			oldindex++;
			newindex++;
			continue;
		}

		if (newnum < oldnum)
		{
			MSG_WriteDeltaEntity (&sv.baselines[newnum], newent, msg, true, true);
			newindex++;
			continue;
		}

		if (newnum > oldnum)
		{
			bits = U_REMOVE;
			if (oldnum >= 256)
				bits |= U_NUMBER16 | U_MOREBITS1;

			MSG_WriteByte (msg,	bits&255 );
			if (bits & 0x0000ff00)
				MSG_WriteByte (msg,	(bits>>8)&255 );

			if (bits & U_NUMBER16)
				MSG_WriteShort (msg, oldnum);
			else
				MSG_WriteByte (msg, oldnum);

			oldindex++;
			continue;
		}
	}

	MSG_WriteShort (msg, 0);
}
