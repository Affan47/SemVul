GDdiminfo(int32 gridID, char *dimname)

{
    intn            status;

    int32           fid;
    int32           sdInterfaceID;
    int32           gdVgrpID;
    int32           size;
    int32           idOffset = GDIDOFFSET;


    char           *metabuf;
    char           *metaptrs[2];
    char            gridname[80];
    char           *utlstr;


    utlstr = (char *) calloc(UTLSTR_MAX_SIZE, sizeof(char));
    if(utlstr == NULL)
    {
	HEpush(DFE_NOSPACE,"GDdiminfo", __FILE__, __LINE__);
	return(-1);
    }


    size = -1;


    status = GDchkgdid(gridID, "GDdiminfo", &fid, &sdInterfaceID, &gdVgrpID);


    if (status == 0)
    {


	Vgetname(GDXGrid[gridID % idOffset].IDTable, gridname);


	metabuf = (char *) EHmetagroup(sdInterfaceID, gridname, "g",
				       "Dimension", metaptrs);

	if(metabuf == NULL)
	{
	    free(utlstr);
	    return(-1);
	}


	sprintf(utlstr, "%s%s%s", "\"", dimname, "\"\n");
	metaptrs[0] = strstr(metaptrs[0], utlstr);


	if (metaptrs[0] < metaptrs[1] && metaptrs[0] != NULL)
	{


	    metaptrs[1] = strstr(metaptrs[0], "\t\t\tEND_OBJECT");

	    status = EHgetmetavalue(metaptrs, "Size", utlstr);

	    if (status == 0)
	    {
		size = atol(utlstr);
	    }
	    else
	    {
		HEpush(DFE_GENAPP, "GDdiminfo", __FILE__, __LINE__);
		HEreport("\"Size\" string not found in metadata.\n");
	    }
	}
	else
	{
	    HEpush(DFE_GENAPP, "GDdiminfo", __FILE__, __LINE__);
	    HEreport("Dimension \"%s\" not found.\n", dimname);
	}

	free(metabuf);
    }
    free(utlstr);
    return (size);
}
