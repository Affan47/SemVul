readString(core::stringc &str)
	{
		str = "";
		c8 c;
		readBuffer(&c,sizeof(char));
		while(c != 0)
		{
			str += c;
			readBuffer(&c,sizeof(char));
		}
	}
