WriteLevelLocals (FILE * f)
{
	field_t *field;
	level_locals_t temp;


	temp = level;


	for (field = levelfields; field->name; field++)
	{
		WriteField1 (f, field, (byte *) & temp);
	}


	fwrite (&temp, sizeof (temp), 1, f);


	for (field = levelfields; field->name; field++)
	{
		WriteField2 (f, field, (byte *) & level);
	}
}
