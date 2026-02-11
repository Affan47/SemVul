pkcs12()
{
	char *arg, *file = NULL, *outform = NULL;
	pkcs12_t *p12 = NULL;
	int res = 1, index = 0;
	enum {
		OP_NONE,
		OP_LIST,
		OP_EXPORT,
	} op = OP_NONE;

	while (TRUE)
	{
		switch (command_getopt(&arg))
		{
			case 'h':
				return command_usage(NULL);
			case 'i':
				file = arg;
				continue;
			case 'l':
				if (op != OP_NONE)
				{
					goto invalid;
				}
				op = OP_LIST;
				continue;
			case 'e':
				if (op != OP_NONE)
				{
					goto invalid;
				}
				op = OP_EXPORT;
				index = atoi(arg);
				continue;
			case 'f':
				outform = arg;
				continue;
			case EOF:
				break;
			default:
			invalid:
				return command_usage("invalid --pkcs12 option");
		}
		break;
	}

	if (file)
	{
		p12 = lib->creds->create(lib->creds, CRED_CONTAINER, CONTAINER_PKCS12,
								  BUILD_FROM_FILE, file, BUILD_END);
	}
	else
	{
		chunk_t chunk;

		set_file_mode(stdin, CERT_ASN1_DER);
		if (!chunk_from_fd(0, &chunk))
		{
			fprintf(stderr, "reading input failed: %s\n", strerror(errno));
			return 1;
		}
		p12 = lib->creds->create(lib->creds, CRED_CONTAINER, CONTAINER_PKCS12,
								  BUILD_BLOB, chunk, BUILD_END);
		free(chunk.ptr);
	}

	if (!p12)
	{
		fprintf(stderr, "reading input failed!\n");
		goto end;
	}

	switch (op)
	{
		case OP_LIST:
			res = show(p12);
			break;
		case OP_EXPORT:
			res = export(p12, index, outform);
			break;
		default:
			p12->container.destroy(&p12->container);
			return command_usage(NULL);
	}

end:
	if (p12)
	{
		p12->container.destroy(&p12->container);
	}
	return res;
}
