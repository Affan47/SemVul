generateConfigDAG(uchar *pszDAGFile)
{

	FILE *fp;
	int iActUnit = 1;


	struct dag_info dagInfo;

	char szConnectingNode[64];
	DEFiRet;

	assert(pszDAGFile != NULL);

	if((fp = fopen((char*) pszDAGFile, "w")) == NULL) {
		logmsgInternal(NO_ERRCODE, LOG_SYSLOG|LOG_INFO, (uchar*)
			"configuraton graph output file could not be opened, none generated", 0);
		ABORT_FINALIZE(RS_RET_FILENAME_INVALID);
	}

	dagInfo.fp = fp;


	fprintf(fp, "# graph created by rsyslog " VERSION "\n\n"
	 	    "# use the dot tool from http://www.graphviz.org to visualize!\n"
		    "digraph rsyslogConfig {\n"
		    "\tinputs [shape=tripleoctagon]\n"
		    "\tinputs -> act0_0\n"
		    "\tact0_0 [label=\"main\\nqueue\" shape=hexagon]\n"

		    );
	strcpy(szConnectingNode, "act0_0");
	dagInfo.bDiscarded = 0;


#if 0
	for(f = Files; f != NULL ; f = f->f_next) {

		bHadFilter = bHasFilter;
		if(f->f_filter_type == FILTER_PRI) {
			bHasFilter = 0;
			for (i = 0; i <= LOG_NFACILITIES; i++)
				if (f->f_filterData.f_pmask[i] != 0xff) {
					bHasFilter = 1;
					break;
				}
		} else {
			bHasFilter = 1;
		}


		switch(f->f_filter_type) {
			case FILTER_PRI:
				pszFilterName = "pri filter";
				break;
			case FILTER_PROP:
				pszFilterName = "property filter";
				break;
			case FILTER_EXPR:
				pszFilterName = "script filter";
				break;
		}


		if(bHasFilter) {
			fprintf(fp, "\t%s -> act%d_end\t[label=\"%s:\\nfalse\"]\n",
				szConnectingNode, iActUnit, pszFilterName);
			fprintf(fp, "\t%s -> act%d_0\t[label=\"%s:\\ntrue\"]\n",
				szConnectingNode, iActUnit, pszFilterName);
			fprintf(fp, "\tact%d_end\t\t\t\t[shape=point]\n", iActUnit);
			snprintf(szConnectingNode, sizeof(szConnectingNode), "act%d_end", iActUnit);
		} else {
			fprintf(fp, "\t%s -> act%d_0\t[label=\"no filter\"]\n",
				szConnectingNode, iActUnit);
			snprintf(szConnectingNode, sizeof(szConnectingNode), "act%d_0", iActUnit);
		}


		dagInfo.iActUnit = iActUnit;
		dagInfo.iAct = 0;
		dagInfo.bDiscarded = 0;
		llExecFunc(&f->llActList, generateConfigDAGAction, &dagInfo);


		if(bHasFilter && !dagInfo.bDiscarded) {
			fprintf(fp, "\tact%d_%d -> %s\n",
				iActUnit, dagInfo.iAct - 1, szConnectingNode);
		}

		++iActUnit;
	}
#endif

	fprintf(fp, "\t%s -> act%d_0\n", szConnectingNode, iActUnit);
	fprintf(fp, "\tact%d_0\t\t[label=discard shape=box]\n"
		    "}\n", iActUnit);
	fclose(fp);

finalize_it:
	RETiRet;
}
