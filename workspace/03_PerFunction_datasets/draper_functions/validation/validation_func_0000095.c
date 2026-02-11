botan_secure_alloc(int bytes)
{
	try
	{
		return alloc->allocate((Botan::u32bit)bytes);
	}
	catch(std::exception &)
	{
		botan_throw_abort();
	}
	return 0;
}
