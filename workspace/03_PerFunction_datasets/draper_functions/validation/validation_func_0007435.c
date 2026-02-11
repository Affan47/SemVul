XTestInitExtension(


register Display	*dpy)
{


	int			i;


	XExtCodes		*ret;


	ret = XInitExtension(dpy, XTestEXTENSION_NAME);


	if (ret == NULL)
	{
		return (-1);
	}


	XTestReqCode = ret->major_opcode;


	for (i = 0; i < XTestEVENT_COUNT; i++)
	{
		XESetWireToEvent(dpy,
				 ret->first_event+i,
				 XTestWireToEvent);
	}


	XTestInputActionType += ret->first_event;
	XTestFakeAckType += ret->first_event;


	return(0);
}
