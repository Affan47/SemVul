output_rule_group(FILE *f_out, int n_rules, char **rules, char *name)
{
	int ix;
	int len1;
	int len2;
	int len_name;
	char *p;
	char *p2, *p3;
	const char *common;

	short nextchar_count[256];
	memset(nextchar_count,0,sizeof(nextchar_count));

	len_name = strlen(name);

#ifdef OUTPUT_FORMAT
	print_rule_group(f_log,n_rules,rules,name);
#endif


	common = "";
	qsort((void *)rules,n_rules,sizeof(char *),(int (__cdecl *)(const void *,const void *))string_sorter);

	if(strcmp(name,"9")==0)
		len_name = 0;

	for(ix=0; ix<n_rules; ix++)
	{
		p = rules[ix];
		len1 = strlen(p) + 1;
		p3 = &p[len1];
		p2 = p3 + len_name;
		len2 = strlen(p2);

		nextchar_count[(unsigned char)(p2[0])]++;

		if((common[0] != 0) && (strcmp(p,common)==0))
		{
			fwrite(p2,len2,1,f_out);
			fputc(0,f_out);
		}
		else
		{
			if((ix < n_rules-1) && (strcmp(p,rules[ix+1])==0))
			{
				common = rules[ix];
				fputc(RULE_PH_COMMON,f_out);
			}

			fwrite(p2,len2,1,f_out);
			fputc(RULE_PHONEMES,f_out);
			fwrite(p,len1,1,f_out);
		}
	}

#ifdef LIST_GROUP_INFO
	for(ix=32; ix<256; ix++)
	{
		if(nextchar_count[ix] > 30)
			printf("Group %s   %c  %d\n",name,ix,nextchar_count[ix]);
	}
#endif
}
