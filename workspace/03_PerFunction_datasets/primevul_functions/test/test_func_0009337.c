static mp_sint32 convertS3MPattern(TXMPattern* XMPattern,
							 const mp_ubyte* srcPattern,
							 mp_uint32 maxChannels,
							 mp_sint32 patCnt)
{

	XMPattern->channum = maxChannels;
	XMPattern->effnum = 2;
	XMPattern->rows = 64;
	XMPattern->patternData = new mp_ubyte[maxChannels*6*64];

	if (XMPattern->patternData == NULL)
	{
		return MP_OUT_OF_MEMORY;
	}

	memset(XMPattern->patternData,0,maxChannels*6*64);

	mp_ubyte* dstSlot = XMPattern->patternData;
	for (mp_sint32 row = 0; row < 64; row++)
		for (mp_uint32 c = 0; c < maxChannels; c++)
		{
			const mp_ubyte* srcSlot = srcPattern+row*32*5+c*5;

			mp_ubyte note = srcSlot[0];

			mp_ubyte finalNote = 0;
			if (note<254)
			{
				finalNote = ((note>>4)*12+(note&0x0f))+1;

				if (finalNote>120)
				{
#ifdef VERBOSE
					printf("Wrong note: %i",finalNote);
#endif
					finalNote = 0;
				}
			}
			else if (note==254)
			{
				finalNote = 122;
			}

			dstSlot[0] = finalNote;

			dstSlot[1] = srcSlot[1];

			if (srcSlot[2]<=64)
			{


					dstSlot[2] = 0xC;
					dstSlot[3] = XModule::vol64to255(srcSlot[2]);

			}

			mp_ubyte eff = srcSlot[3];
			mp_ubyte op = srcSlot[4];


			mp_ubyte nEff = 0;
			mp_ubyte nOp = 0;

			switch (eff)
			{

				case 0x01:
					nEff = 0x1C;
					nOp = op;
					break;


				case 0x02:
					nEff = 0x0B;
					nOp = op;
					break;


				case 0x03:
					nEff = 0x0D;
					nOp = op;
					break;


				case 0x04:
					nEff = 0x49;
					nOp = op;
					break;


				case 0x05:
					nEff = 0x48;
					nOp = op;
					break;


				case 0x06:
					nEff = 0x47;
					nOp = op;
					break;


				case 0x07:
					nEff = 0x03;
					nOp = op;
					break;


				case 0x08:
					nEff = 0x04;
					nOp = op;
					break;


				case 0x09:
					nEff = 0x1D;
					nOp = op;
					break;


				case 0x0A:
					nEff = 0x20;
					nOp = op;
					break;


				case 0x0B:
					nEff = 0x06;
					nOp = op;
					break;


				case 0x0C:
					nEff = 0x05;
					nOp = op;
					break;


				case 0x0F:
					nEff = 0x09;
					nOp = op;
					break;


				case 0x11:
					nEff = 0x1B;
					nOp = op;
					break;


				case 0x12:
					nEff = 0x07;
					nOp = op;
					break;


				case 0x13:
					eff = op>>4;
					op&=0xf;
					switch (eff)
					{

						case 0x8:
							nEff = 0x08;
							nOp = XModule::pan15to255(op);
							break;

						case 0xB:
							nEff = 0x36;
							nOp = op;
							break;

						case 0xC:
							nEff = 0x3C;
							nOp = op;
							break;

						case 0xD:
							nEff = 0x3D;
							nOp = op;
							break;


						case 0xE:
							nEff = 0x3E;
							nOp = op;
							break;

						default:
#ifdef VERBOSE
							printf("Unsupported subcommand in Pattern %i, Channel %i, Row %i: %x,%x\n",patCnt,c,row,eff,op);
#endif
							break;

					}
						break;


				case 0x14:
					nEff = 0x16;
					nOp = op;
					break;


				case 0x15:
					nEff = 0x4A;
					nOp = op;
					break;


				case 0x16:
					if (op>64) op = 64;
					nEff = 0x10;
					nOp = XModule::vol64to255(op);
					break;


				case 0x17:
					nEff = 0x59;
					nOp = op;
					break;

				default:
#ifdef VERBOSE
					if (eff!=255)
					{
						printf("Unsupported command: %x,%x\n",eff,op);
					}
#endif
					break;
			}


			dstSlot[4] = nEff;
			dstSlot[5] = nOp;

			dstSlot+=6;
		}

	return MP_OK;
}
