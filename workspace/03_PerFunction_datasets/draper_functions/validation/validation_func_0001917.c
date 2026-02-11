vol_reply_print(register const u_char *bp, int length, int32_t opcode)
{
	struct rx_header *rxh;

	if (length <= (int)sizeof(struct rx_header))
		return;

	rxh = (struct rx_header *) bp;


	printf(" vol reply %s", tok2str(vol_req, "op#%d", opcode));

	bp += sizeof(struct rx_header);


	if (rxh->type == RX_PACKET_TYPE_DATA) {
		switch (opcode) {
			case 100:
				printf(" volid");
				UINTOUT();
				printf(" trans");
				UINTOUT();
				break;
			case 104:
				UINTOUT();
				break;
			case 105:
				printf(" newvol");
				UINTOUT();
				break;
			case 107:
				UINTOUT();
				break;
			case 108:
				printf(" trans");
				UINTOUT();
				break;
			case 110:
				printf(" volume");
				UINTOUT();
				printf(" partition");
				UINTOUT();
				break;
			case 112:
				STROUT(AFSNAMEMAX);
				break;
			case 113:
				printf(" volid");
				UINTOUT();
				printf(" nextuniq");
				UINTOUT();
				printf(" type");
				UINTOUT();
				printf(" parentid");
				UINTOUT();
				printf(" clone");
				UINTOUT();
				printf(" backup");
				UINTOUT();
				printf(" restore");
				UINTOUT();
				printf(" maxquota");
				UINTOUT();
				printf(" minquota");
				UINTOUT();
				printf(" owner");
				UINTOUT();
				printf(" create");
				DATEOUT();
				printf(" access");
				DATEOUT();
				printf(" update");
				DATEOUT();
				printf(" expire");
				DATEOUT();
				printf(" backup");
				DATEOUT();
				printf(" copy");
				DATEOUT();
				break;
			case 115:
				break;
			case 116:
			case 121:
				{
					unsigned long i, j;
					TCHECK2(bp[0], 4);
					j = EXTRACT_32BITS(bp);
					bp += sizeof(int32_t);
					for (i = 0; i < j; i++) {
						printf(" name");
						VECOUT(32);
						printf(" volid");
						UINTOUT();
						printf(" type");
						bp += sizeof(int32_t) * 21;
						if (i != j - 1)
							printf(",");
					}
					if (j == 0)
						printf(" <none!>");
				}
				break;


			default:
				;
		}
	} else {


		printf(" errcode");
		INTOUT();
	}

	return;

trunc:
	printf(" [|vol]");
}
