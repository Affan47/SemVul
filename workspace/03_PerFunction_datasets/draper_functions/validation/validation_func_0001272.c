pdf_rdx(U_CHAR *x, long nitems, PDFstrm *pdfs)
{
    int i, result = 0;

    if (pdfs->file != NULL) {
	result = fread(x, 1, nitems, pdfs->file);
	pdfs->bp += nitems;
#ifdef PLPLOT_USE_TCL_CHANNELS
    } else if (pdfs->tclChan != NULL) {
	result = Tcl_ReadRaw(pdfs->tclChan, x, nitems);
	pdfs->bp += nitems;
#endif
    } else if (pdfs->buffer != NULL) {
	for (i = 0; i < nitems; i++) {
	    if (pdfs->bp > pdfs->bufmax)
		break;
	    x[i] = pdfs->buffer[pdfs->bp++];
	}
	result = i;
    }

    return result;
}
