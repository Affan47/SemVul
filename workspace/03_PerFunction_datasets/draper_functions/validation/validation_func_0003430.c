doit() {

	FILE *alifile;

	char line[MAXSTRING];
	char *ptr;


	if ((alifile = fopen(infile, "r")) == NULL) {fprintf(stderr,"Error: Unable to input file %s\n",infile);exit(2);}


	if ((ptr = fgets(line,sizeof(line),alifile)) == NULL) wrongFormatError(infile);


 	if (strstr(line,"#:lav") == ptr) {
 		processSimfile();
 	}

	else if (strstr(line,"Consistent matches")) {
		processMumfile();
	}

	else {
		if (!strcmp(xName,"SEQ1")) {
			while (((ptr = fgets(line,sizeof(line),alifile)) != NULL) && *ptr == '#');
			if (sscanf(line,"%[^: \t\n\r]:%[^: \t\n\r]", xName,yName) < 2) wrongFormatError(infile);
		}
		if (fclose(alifile)) fprintf(stderr,"Error: Unable to close file %s\n%s\n",infile,line);
		processGFFfile();
	}

	return;
}
