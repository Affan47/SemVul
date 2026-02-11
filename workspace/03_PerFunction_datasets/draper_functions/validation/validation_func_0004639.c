validString(string s)
{
	string::iterator b=s.begin(), e=s.end();

	while (b != e)
	{
		if ((int)(unsigned char)*b <= ' ' || *b == '>' || *b == '<')
		{
			messageProcessed(500, "500 Invalid character in message sender, recipient, or options.");
			return false;
		}
		b++;
	}
	return true;
}
