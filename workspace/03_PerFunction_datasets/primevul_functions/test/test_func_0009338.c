const char* LoaderS3M::identifyModule(const mp_ubyte* buffer)
{

	if (!memcmp(buffer+0x2C,"SCRM",4))
	{
		return "S3M";
	}


	return NULL;
}
