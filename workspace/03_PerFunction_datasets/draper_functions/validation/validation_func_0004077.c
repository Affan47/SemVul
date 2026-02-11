printSummary(int files, mt_size_t bytes)
{
	if(!filesInDir)
		printf("No files\n");
	else {
		char *s1 = NULL;
		printf("      %3d file", files);
		if(files == 1)
			putchar(' ');
		else
			putchar('s');
		printf("       %s bytes\n",
		       dotted_num(bytes, 13, &s1));
		if(s1)
			free(s1);
	}
}
