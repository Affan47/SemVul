getmac(char * macAddress, int strict, unsigned char * mac)
{
	char byte[3];
	int i, nbElem, n;

	if (macAddress == NULL)
		return 1;


	if ((int)strlen(macAddress) < 12)
		return 1;

	memset(mac, 0, 6);
	byte[2] = 0;
	i = nbElem = 0;

	while (macAddress[i] != 0)
	{
		if (macAddress[i] == '\n' || macAddress[i] == '\r')
			break;

		byte[0] = macAddress[i];
		byte[1] = macAddress[i+1];

		if (sscanf( byte, "%x", &n ) != 1
			&& strlen(byte) == 2)
			return 1;

		if (hexCharToInt(byte[1]) < 0)
			return 1;

		mac[nbElem] = n;

		i+=2;
		nbElem++;

		if (macAddress[i] == ':' || macAddress[i] == '-'  || macAddress[i] == '_')
			i++;
	}

	if ((strict && nbElem != 6)
		|| (!strict && nbElem > 6))
		return 1;

	return 0;
}
