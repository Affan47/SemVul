getseqdimsize(NCDAPCOMMON* nccomm, CDFnode* seq, size_t* sizep)
{
    NCerror ncstat = NC_NOERR;
    OCerror ocstat = OC_NOERR;
    OCconnection conn = nccomm->oc.conn;
    OCdata rootcontent = OCNULL;
    OCobject ocroot;
    CDFnode* dxdroot;
    CDFnode* xseq;
    NCbytes* minconstraints = ncbytesnew();
    size_t seqsize;


    computeminconstraints3(nccomm,seq,minconstraints);
#ifdef DEBUG
fprintf(stderr,"minconstraints: %s\n",ncbytescontents(minconstraints));
#endif

    if(FLAGSET(nccomm->controls,NCF_UNCONSTRAINABLE))
        ocstat = dap_oc_fetch(nccomm,conn,NULL,OCDATADDS,&ocroot);
    else
        ocstat = dap_oc_fetch(nccomm,conn,ncbytescontents(minconstraints),OCDATADDS,&ocroot);
    if(ocstat) goto fail;
    ncstat = buildcdftree34(nccomm,ocroot,OCDATA,&dxdroot);
    if(ncstat) goto fail;

    ncstat = attach34(dxdroot,seq);
    if(ncstat) goto fail;

    xseq = seq->attachment;
    ncstat = countsequence(nccomm,xseq,&seqsize);
    if(ncstat) goto fail;
#ifdef DEBUG
fprintf(stderr,"sequencesize: %s = %lu\n",seq->name,(unsigned long)seqsize);
#endif

    unattach34(nccomm->cdf.ddsroot);
    freecdfroot34(dxdroot);
    if(ncstat != NC_NOERR) {

	char* code;
	char* msg;
	long httperr;
	oc_svcerrordata(nccomm->oc.conn,&code,&msg,&httperr);
	if(code != NULL) {
	    nclog(NCLOGERR,"oc_fetch_datadds failed: %s %s %l",
			code,msg,httperr);
	}
	ocstat = OC_NOERR;
    }
    if(sizep) *sizep = seqsize;

fail:
    ncbytesfree(minconstraints);
    oc_data_free(conn,rootcontent);
    if(ocstat) ncstat = ocerrtoncerr(ocstat);
    return ncstat;
}
