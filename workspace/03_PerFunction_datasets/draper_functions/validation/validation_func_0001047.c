dglMinimumSpanning(dglGraph_s * pgraphInput,
		       dglGraph_s * pgraphOutput,
		       dglInt32_t nVertexNode,
		       dglSpanClip_fn fnClip, void *pvClipArg)
{
    int nRet;

    if (dglGet_EdgeCount(pgraphInput) == 0) {
	pgraphInput->iErrno = 0;
	return 0;
    }

    nRet = dglInitialize(pgraphOutput,
			 dglGet_Version(pgraphInput),
			 dglGet_NodeAttrSize(pgraphInput),
			 dglGet_EdgeAttrSize(pgraphInput),
			 dglGet_Opaque(pgraphInput));

    if (nRet < 0)
	return nRet;

    switch (pgraphInput->Version) {
    case 1:
	nRet =
	    dgl_minimum_spanning_V1(pgraphInput, pgraphOutput, nVertexNode,
				    fnClip, pvClipArg);
	break;
#ifdef DGL_V2
    case 2:
    case 3:
	nRet =
	    dgl_minimum_spanning_V2(pgraphInput, pgraphOutput, nVertexNode,
				    fnClip, pvClipArg);
	break;
#endif
    default:
	pgraphInput->iErrno = DGL_ERR_BadVersion;
	nRet = -pgraphInput->iErrno;
	break;
    }
    if (nRet < 0) {
	dglRelease(pgraphOutput);
    }
    return nRet;
}
