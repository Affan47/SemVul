DumpResourceMaps(char *filename) {
    FILE *restemp = tmpfile(), *real;
    int i;
    char *pt, *dot, *new;


    for ( i=0; i<0x100; ++i )
	putc('\0',restemp);


    ResCopy(restemp);


    DumpResourceMap(restemp,global_types);

    pt = strrchr(filename,'/');
    if ( pt==NULL ) pt=filename;
    dot = strrchr(pt,'.');
    if ( dot==NULL ) dot = pt+strlen(pt);
    new = malloc(strlen(pt)+strlen(".dfont")+2);
    strcpy(new,pt);
    strcpy(new+(dot-pt),".dfont");

    real = fopen(new,"w");
    if ( real==NULL ) {
	fprintf( stderr, "Can't open %s for output\n", new);
exit(1);
    }
    CopyFile(real,restemp);
    fclose(restemp);
    fclose(real);
}
