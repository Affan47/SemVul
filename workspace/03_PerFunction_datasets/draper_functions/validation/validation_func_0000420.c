Xform_Format (Xform xform, struct fmt_info *p)
{
    Matrix tm;
    Object subo;
    int rc;

    DXGetXformInfo(xform, &subo, &tm);
    rc = _dxfObject_Format(subo, p);
    if (rc != OK)
	return ERROR;

    fprintf(p->fp, "object %s class transform ", objid(p, (Object)xform));
    fprintf(p->fp, "of %s\n", objid(p, subo));
    fprintf(p->fp, " times %13.7g %13.7g %13.7g\n       %13.7g %13.7g %13.7g\n       %13.7g %13.7g %13.7g\n",
	    (double)tm.A[0][0], (double)tm.A[0][1], (double)tm.A[0][2],
	    (double)tm.A[1][0], (double)tm.A[1][1], (double)tm.A[1][2],
	    (double)tm.A[2][0], (double)tm.A[2][1], (double)tm.A[2][2]);

    fprintf(p->fp, " plus  %13.7g %13.7g %13.7g\n",
	    (double)tm.b[0], (double)tm.b[1], (double)tm.b[2]);

    return OK;
}
