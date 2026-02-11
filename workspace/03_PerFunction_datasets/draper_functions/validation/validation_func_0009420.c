IoMessage_foreachArgs(IoMessage *self,
						   IoObject *receiver,
						   IoSymbol **indexSlotName,
						   IoSymbol **valueSlotName,
						   IoMessage **doMessage)
{
	int offset;

	IoMessage_assertArgCount_receiver_(self, 2, receiver);

	if (IoMessage_argCount(self) > 2)
	{
		*indexSlotName = IoMessage_name(IoMessage_rawArgAt_(self, 0));
		offset = 1;
	}
	else
	{
		*indexSlotName = NULL;
		offset = 0;
	}

	*valueSlotName = IoMessage_name(IoMessage_rawArgAt_(self, 0 + offset));
	*doMessage = IoMessage_rawArgAt_(self, 1 + offset);
}
