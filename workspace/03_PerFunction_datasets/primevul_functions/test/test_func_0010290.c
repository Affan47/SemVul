const char* LoaderXM::identifyModule(const mp_ubyte* buffer)
{

	if (!memcmp(buffer,"Extended Module:",16))
	{
		return "XM";
	}


	return NULL;
}
