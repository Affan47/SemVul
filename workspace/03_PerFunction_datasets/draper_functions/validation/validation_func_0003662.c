output_comment(int adrs)
{
	COMMENT_PTR	cmt;
	char			*str;

	cmt = comment_list;

	while (cmt)
	{
		if (cmt->adrs == adrs)
		{
			str = cmt->str;
			fprintf(fp, "\n;");

			if (strlen(str) > 3 && str[2] == '\\' && str[3] == 'n')
			{
				fprintf(fp, "\n; ");
				str += 4;
			}
			else
				str++;

			while (*str)
			{
				if (*str == '\\' && *(str + 1) && (*(str + 1) == 'n'))
				{
					str++;
					fprintf(fp, "\n;");

					if (*(str + 1))
						fputc(' ', fp);
				}
				else
					fputc(*str, fp);

				str++;
			}
		}

		cmt = cmt->next;
	}
}
