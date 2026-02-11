message_from_server(CALL *call, int chan)
{
	int Cnt;
	int RetCode;
	char *String = Build_Call_Info(call,chan);

	if ((RetCode = String_For_Output(String)) < 0)
		return RetCode;

	if ((RetCode = save_messages(String,chan,call->stat)) < 0)
		return RetCode;

	for(Cnt = first_descr; Cnt < socket_size(sockets); Cnt++)
	{
		if (sockets[Cnt].fp == NULL                &&
		    sockets[Cnt].waitstatus == WF_NOTHING &&
		    User_Get_Message(sockets[Cnt].f_username,sockets[Cnt].f_hostname,call->num[_ME(call)],0) == 0)
		{
			sockets[Cnt].msg = MSG_CALL_INFO;
			msgcpy(&(sockets[Cnt]),String,strlen(String)+1);

			if (Write(&(sockets[Cnt])) < 1)
 				disconnect_client(Cnt);
 			else
 			if (Write_Caller_Message(Cnt,call) < 0)
 				disconnect_client(Cnt);
 		}
	}

	return 0;
}
