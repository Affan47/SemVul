insert_tobeinserted(int position, int ph_len, struct statement * stmt, char *tobeinserted)
{
	char	   *newcopy;

	if (!(newcopy = (char *) ecpg_alloc(strlen(stmt->command)
										+ strlen(tobeinserted)
										+ 1, stmt->lineno)))
	{
		ecpg_free(tobeinserted);
		return false;
	}

	strcpy(newcopy, stmt->command);
	strcpy(newcopy + position - 1, tobeinserted);


	strcat(newcopy,
		   stmt->command
		   + position
		   + ph_len - 1);

	ecpg_free(stmt->command);
	stmt->command = newcopy;

	ecpg_free((char *) tobeinserted);
	return true;
}
