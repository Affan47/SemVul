absoluteFilename (const char *file)
{
	char *slashp, *cp;
	char *res = NULL;
	if (isAbsolutePath (file))
	{
#ifdef MSDOS_STYLE_PATH
		if (file [1] == ':')
			res = eStrdup (file);
		else
		{
			char drive [3];
			sprintf (drive, "%c:", currentdrive ());
			res = concat (drive, file, "");
		}
#else
		res = eStrdup (file);
#endif
	}
	else
		res = concat (CurrentDirectory, file, "");


	slashp = strchr (res, PATH_SEPARATOR);
	while (slashp != NULL  &&  slashp [0] != '\0')
	{
		if (slashp[1] == '.')
		{
			if (slashp [2] == '.' &&
				(slashp [3] == PATH_SEPARATOR || slashp [3] == '\0'))
			{
				cp = slashp;
				do
					cp--;
				while (cp >= res  &&  ! isAbsolutePath (cp));
				if (cp < res)
					cp = slashp;
#ifdef MSDOS_STYLE_PATH


				else if (cp [0] != PATH_SEPARATOR)
					cp = slashp;
#endif
				strcpy (cp, slashp + 3);
				slashp = cp;
				continue;
			}
			else if (slashp [2] == PATH_SEPARATOR  ||  slashp [2] == '\0')
			{
				strcpy (slashp, slashp + 2);
				continue;
			}
		}
		slashp = strchr (slashp + 1, PATH_SEPARATOR);
	}

	if (res [0] == '\0')
		return eStrdup ("/");
	else
	{
#ifdef MSDOS_STYLE_PATH

		if (res [1] == ':'  &&  islower (res [0]))
			res [0] = toupper (res [0]);
#endif

		return res;
	}
}
