showHierarchy()
{
    int
        index;
    int
        index2;
    CONDITION
	cond;
    LST_NODE
	* lstNode;
    BFB_NODE
	* bfbNode;
    BIB_NODE
	* bibNode;

    printf("PRINT MANAGEMENT SOP CLASS HIERARCHY\n");
    printf("------------------------------------\n\n");

    if (strcmp(bfsInstance.bfsInstanceUID, "\0") == 0) {
	printf("Hierarchy Doesnot exists\n");
	return;
    }
    printf("Basic Film Session SOP Instance UID : %s\n",
	   bfsInstance.bfsInstanceUID);
    printf("  Attributes : \n");
    cond = DCM_DumpElements(&bfsInstance.bfsAttrib, 0);
    if (cond != DCM_NORMAL) {
	COND_DumpConditions();
	return;
    }
    printf("\n\n");

    printf("\tChildren Basic Film Box Instances : \n");
    printf("\t---------------------------------\n");
    lstNode = LST_Head(&bfsInstance.bfbList);
    if (lstNode == NULL) {
	printf("\tChildren Basic Film Boxes do not exist currently\n\n");
	return;
    }
    if ((bfbNode = LST_Position(&bfsInstance.bfbList, lstNode)) ==
	NULL) {
	printf("LST_Position failed in showHierarchy\n");
	COND_DumpConditions();
    }
    for (index = 0; index < (int) LST_Count(&bfsInstance.bfbList); index++) {
	if (strlen(bfbNode->bfbInstanceUID) == 0) {
	    printf("Hierarchy Doesnot exists\n");
	    continue;
	}
	printf("\tBasic Film Box SOP instance UID : %s\n",
	       bfbNode->bfbInstanceUID);
	printf("\t  Attributes : \n");
	cond = DCM_DumpElements(&bfbNode->bfbAttrib, 0);
	if (cond != DCM_NORMAL) {
	    COND_DumpConditions();
	    return;
	}
	printf("\n\t\tChildren Basic Image Boxes\n");
	printf("\t\t--------------------------\n");
	bibNode = (BIB_NODE *) LST_Position(&bfbNode->bibList,
					    LST_Head(&bfbNode->bibList));
	if (bibNode == NULL) {
	    printf("LST_Position returned NULL for bibNode\n");
	    return;
	}
	for (index2 = 0; index2 < (int) LST_Count(&bfbNode->bibList); index2++) {
	    printf("\t\tBasic Image Box SOP instance UID : %s\n",
		   bibNode->bibInstanceUID);
	    printf("\t\t  Attributes :\n\n");
	    cond = DCM_DumpElements(&bibNode->bibAttrib, 0);
	    if (cond != DCM_NORMAL)
		if (cond == DCM_NULLOBJECT)
		    printf("\t\t\tCurrently No Attributes present\n");
		else {
		    COND_DumpConditions();
		    return;
		}
	    bibNode = (BIB_NODE *) LST_Next(&bfbNode->bibList);
	}
	printf("\n");
	bfbNode = (BFB_NODE *) LST_Next(&bfsInstance.bfbList);
    }
    printf("\n\n###############################################################################\n\n");
}
