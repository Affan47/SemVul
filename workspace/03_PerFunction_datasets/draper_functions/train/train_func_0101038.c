ParsePIN(const Data &data, uint32_t &pin)
{

	const unsigned char *pd = data.GetData();

	if( !CheckSize(data, 0x14) )
		return false;


	memcpy(&pin, &pd[16], sizeof(pin));
	pin = btohl(pin);

	return true;
}
