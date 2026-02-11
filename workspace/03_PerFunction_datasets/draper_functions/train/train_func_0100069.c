recvPPM(TIFF* tif, int& ppr)
{
    for (;;) {
	switch (atResponse(rbuf, conf.pageDoneTimeout)) {
	case AT_OK:
	    protoTrace("MODEM protocol botch: OK without +FPTS:");

	case AT_TIMEOUT:
	case AT_EMPTYLINE:
	case AT_NOCARRIER:
	case AT_NODIALTONE:
	case AT_NOANSWER:
	case AT_ERROR:
	    processHangup("50");
	    return (false);
	case AT_FPTS:
	    return parseFPTS(tif, skipStatus(rbuf), ppr);
	case AT_FET:
	    protoTrace("MODEM protocol botch: +FET: without +FPTS:");
	    processHangup("100");
	    return (false);
	case AT_FHNG:
	    waitFor(AT_OK);
	    return (false);
	}
    }
}
