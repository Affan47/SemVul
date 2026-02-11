Float (DBObjRecord *record,DBFloat value)

	{
	if (record == (DBObjRecord *) NULL) return;
	switch (Type ())
		{
		case DBTableFieldInt:
			Int (record,(DBInt) value);
			break;
		case DBTableFieldFloat:
			switch (Length ())
				{
				case sizeof (DBFloat):
					memcpy ((char *) record->Data () + StartByte (),&value,		Length ());
					break;
				case sizeof (DBFloat4):
					{
					DBFloat4 float4VAR = (DBFloat4) value;
					memcpy ((char *) record->Data () + StartByte (),&float4VAR,	Length ());
					} break;
				default:
					CMmsgPrint (CMmsgAppError, "Invalid Data length [%s %d] in: %s %d",Name (),Length (),__FILE__,__LINE__);
					break;
				}
			break;
		default:
			CMmsgPrint (CMmsgAppError, "Invalid Data Type [%s] in: %s %d",Name (),__FILE__,__LINE__);
			break;
		}
	}
