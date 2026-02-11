DoTheTalk(struct ProgramInfo *PI)
	{
	int ok = False;
	unsigned char SerBuff[3];

	SerWriteByte(PI->Ser, 'T');
	SerWriteByte(PI->Ser, (unsigned char)PI->SelectedChipNode->Code);
	if((SerReadData(PI->Ser, SerBuff, 1)) && (SerBuff[0] == 13))
		{
		SerWriteByte(PI->Ser, 'P');
		if((SerReadData(PI->Ser, SerBuff, 1)) && (SerBuff[0] == 13))
			{
			SerWriteByte(PI->Ser, 's');
			if(SerReadData(PI->Ser, SerBuff, 3))
				{
				if((SerBuff[0] != 0xFF) || (SerBuff[1] != 0xFF) || (SerBuff[2] != 0xFF) || GET_ARG(PI->args, ARG_IGNORESIG))
					{
					if(CheckLockAndErase(PI, SerBuff))
						{
						if(CheckSig(PI, SerBuff))
							{
							if(GET_ARG(PI->args, ARG_PROG)|| GET_ARG(PI->args, ARG_READ)
							   || GET_ARG(PI->args, ARG_VERIFY)|| GET_ARG(PI->args, ARG_LOCKMODE)
							   || GET_ARG(PI->args, ARG_ENABLE) || GET_ARG(PI->args, ARG_DISABLE))
								{
								ok = DoMoreTalk(PI);
								}
							else
								printf("Missing argument: No action argument specified\n"
								       "   -p : Program\n"
								       "   -r : Read\n"
								       "   -v : Verify (can be used standalone or together with -p or -r)\n"
								       "   -l : Lockmode (use '-l list' to get a list of modes)\n"
								       "   --enable  : Fuses to enable\n"
								       "   --disable : Fuses to disable\n");
							}
						}
					}
				else
					printf("Error: There seems to be no chip inserted in the programmer\n"
					       "       Use -I to ignore this signaturecheck\n");
				}
			else
				print_comm_err('s');
			}
		else
			print_comm_err('P');
		SerWriteByte(PI->Ser, 'L');
		if(!((SerReadData(PI->Ser, SerBuff, 1)) && (SerBuff[0] == 13)))
			print_comm_err('L');
		}
	else
		print_comm_err('T');
	return(ok);
	}
