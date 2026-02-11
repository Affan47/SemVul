IMStartConversion(icp)
IMIC *icp;
{
    IMIM *imp = icp->im;
    Widget proto = imp->connection->proto_widget;
    Widget converter;
    WidgetClass class;
    unsigned long attrmask;
    ConversionAttributes attrs;

    TRACE(("IMStartConversion()\n"));

    if (icp->state & IC_CONVERTING) return 0;


    if (!(icp->common_attr.set_mask & ATTR_MASK_CLIENT)) {
	IMSendError(icp->im->connection, IMBadSomething, icp->im->id, icp->id,
		    "client window required");
	return -1;
    }


    fillDefaultAttributesForStartup(icp);


    if (icp->style == IMSTYLE_OVER_THE_SPOT) {
	class = overTheSpotConversionWidgetClass;
    } else if (icp->style == IMSTYLE_OFF_THE_SPOT) {
	class = offTheSpotConversionWidgetClass;
    } else if (icp->style == IMSTYLE_ON_THE_SPOT) {
	class = onTheSpotConversionWidgetClass;
    } else {
	class = separateConversionWidgetClass;
    }


    attrmask = makeConvAttributesForStartup(icp, &attrs);

    icp->state &= ~IC_RESETTING;


    converter = CMGetConverter(XtParent(proto),
			       icp->common_attr.client, class,
			       imp->converter->input_object_class,
			       imp->converter->display_object_class);
    if (converter == NULL) {
	IMSendError(imp->connection, IMBadSomething, imp->id, icp->id,
		    "can't attach converter to this IC");
	return -1;
    }
    icp->conversion = converter;


    XtAddCallback(converter, XtNtextCallback, fixCallback, (XtPointer)icp);
    XtAddCallback(converter, XtNendCallback, endCallback, (XtPointer)icp);
    XtAddCallback(converter, XtNunusedEventCallback, unusedEventCallback, (XtPointer)icp);
    if (icp->style == IMSTYLE_ON_THE_SPOT) {
	XtAddCallback(converter, XtNpreeditStartCallback, preeditStartCallback,
		      (XtPointer)icp);
	XtAddCallback(converter, XtNpreeditDoneCallback, preeditDoneCallback,
		      (XtPointer)icp);
	XtAddCallback(converter, XtNpreeditDrawCallback, preeditDrawCallback,
		      (XtPointer)icp);
	XtAddCallback(converter, XtNpreeditCaretCallback, preeditCaretCallback,
		      (XtPointer)icp);
	XtAddCallback(converter, XtNstatusStartCallback, statusStartCallback,
		      (XtPointer)icp);
	XtAddCallback(converter, XtNstatusDoneCallback, statusDoneCallback,
		      (XtPointer)icp);
	XtAddCallback(converter, XtNstatusDrawCallback, statusDrawCallback,
		      (XtPointer)icp);
    }


    XtVaSetValues(converter, XtNeventSelectMethod, ESMethodNone, NULL);
    CControlStartConversion(converter, icp->common_attr.client,
			    attrmask, &attrs);

    icp->state |= IC_CONVERTING;

    if (icp->common_attr.input_style & XIMPreeditCallbacks)
	preeditStart(icp);


    IMStartForwarding(icp);

    return 0;
}
