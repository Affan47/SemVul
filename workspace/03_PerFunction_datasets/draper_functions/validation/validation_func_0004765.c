RemoveLabelSuffix(domainlabel *name, mDNSBool RichText)
	{
	mDNSu32 val = 0, multiplier = 1;


	if (RichText && name->c[0] >= 1 && name->c[name->c[0]] == ')') name->c[0]--;


	while (mdnsIsDigit(name->c[name->c[0]]))
		{ val += (name->c[name->c[0]] - '0') * multiplier; multiplier *= 10; name->c[0]--; }


	if (RichText)
		{
		if (name->c[0] >= 2 && name->c[name->c[0]] == '(' && name->c[name->c[0]-1] == ' ') name->c[0] -= 2;
		}
	else
		{
		if (name->c[0] >= 1 && name->c[name->c[0]] == '-') name->c[0] -= 1;
		}

	return(val);
	}
