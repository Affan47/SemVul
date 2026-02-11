printtup_startup(DestReceiver *self, int operation, TupleDesc typeinfo)
{
	DR_printtup *myState = (DR_printtup *) self;
	Portal		portal = myState->portal;

	if (PG_PROTOCOL_MAJOR(FrontendProtocol) < 3)
	{


		const char *portalName = portal->name;

		if (portalName == NULL || portalName[0] == '\0')
			portalName = "blank";

		pq_puttextmessage('P', portalName);
	}


	if (myState->sendDescrip)
		SendRowDescriptionMessage(typeinfo,
								  FetchPortalTargetList(portal),
								  portal->formats);


}
