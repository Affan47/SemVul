stripTrailing(std::string& buffer)
{
	int bufferLength = static_cast<int>(buffer.size());

	locale loc;

	for (int x = bufferLength - 1; x >= 0; x--)
	{
		char c = buffer[x];

		if (isspace(c, loc))
		{
			buffer.erase(x);
		}
		else
		{
			break;
		}
	}
}
