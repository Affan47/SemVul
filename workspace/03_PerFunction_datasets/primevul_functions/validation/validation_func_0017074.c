get_cmdline_cipher_suite_priv_data(char * arg, uint8_t * buf)
{
	int i, ret = 0;

	if (strlen(arg) != 15)
	{
		lprintf(LOG_ERR, "Invalid privilege specification length: %d",
			strlen(arg));
		return -1;
	}


	memset(buf, 0, 9);
	for (i = 0; i < 15; ++i)
	{
		unsigned char priv_level = IPMI_SESSION_PRIV_ADMIN;

		switch (arg[i])
		{
		case 'X':
			priv_level = IPMI_SESSION_PRIV_UNSPECIFIED;
			break;
		case 'c':
			priv_level = IPMI_SESSION_PRIV_CALLBACK;
			break;
		case 'u':
			priv_level = IPMI_SESSION_PRIV_USER;
			break;
		case 'o':
			priv_level = IPMI_SESSION_PRIV_OPERATOR;
			break;
		case 'a':
			priv_level = IPMI_SESSION_PRIV_ADMIN;
			break;
		case 'O':
			priv_level = IPMI_SESSION_PRIV_OEM;
			break;
		default:
			lprintf(LOG_ERR, "Invalid privilege specification char: %c",
				arg[i]);
			ret = -1;
			break;
		}

		if (ret != 0)
			break;
		else
		{
			if ((i + 1) % 2)
			{

				buf[1 + (i / 2)] += priv_level;
			}
			else
			{

				buf[1 + (i / 2)] += (priv_level << 4);
			}
		}
	}

	return ret;
}
