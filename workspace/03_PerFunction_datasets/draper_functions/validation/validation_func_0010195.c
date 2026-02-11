gtextfield_destroy(GGadget *g) {
    GTextField *gt = (GTextField *) g;

    if ( gt==NULL )
return;
    if ( gt->listfield ) {
	GListField *glf = (GListField *) g;
	if ( glf->popup ) {
	    GDrawDestroyWindow(glf->popup);
	    GDrawSync(NULL);
	    GDrawProcessWindowEvents(glf->popup);
	}
	GTextInfoArrayFree(glf->ti);
    }
    if ( gt->completionfield )
	GCompletionDestroy((GCompletionField *) g);

    if ( gt->vsb!=NULL )
	(gt->vsb->g.funcs->destroy)(&gt->vsb->g);
    if ( gt->hsb!=NULL )
	(gt->hsb->g.funcs->destroy)(&gt->hsb->g);
    GDrawCancelTimer(gt->numeric_scroll);
    GDrawCancelTimer(gt->pressed);
    GDrawCancelTimer(gt->cursor);
    free(gt->lines);
    free(gt->oldtext);
    free(gt->text);
    free(gt->bidata.text);
    free(gt->bidata.level);
    free(gt->bidata.override);
    free(gt->bidata.type);
    free(gt->bidata.original);
    _ggadget_destroy(g);
}
