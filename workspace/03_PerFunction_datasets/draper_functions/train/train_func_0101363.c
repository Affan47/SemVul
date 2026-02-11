closeAll()
{
	while (!bstore.empty())
		release(bstore.front());
}
