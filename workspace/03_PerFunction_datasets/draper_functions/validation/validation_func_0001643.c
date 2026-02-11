rmtdir(Void)
{
	char *s;
	if (*(s = tmpdir)) {
		tmpdir = "";
		rmdir(s);
		}
	}
