rfbSetTranslateFunction(rfbClientPtr cl)
{
    rfbLog("Pixel format for client %s:\n",cl->host);
    PrintPixelFormat(&cl->format);


    if ((cl->screen->serverFormat.bitsPerPixel != 8) &&
        (cl->screen->serverFormat.bitsPerPixel != 16) &&
#ifdef LIBVNCSERVER_ALLOW24BPP
	(cl->screen->serverFormat.bitsPerPixel != 24) &&
#endif
        (cl->screen->serverFormat.bitsPerPixel != 32))
    {
        rfbErr("%s: server bits per pixel not 8, 16 or 32 (is %d)\n",
	       "rfbSetTranslateFunction",
	       cl->screen->serverFormat.bitsPerPixel);
        rfbCloseClient(cl);
        return FALSE;
    }

    if ((cl->format.bitsPerPixel != 8) &&
        (cl->format.bitsPerPixel != 16) &&
#ifdef LIBVNCSERVER_ALLOW24BPP
	(cl->format.bitsPerPixel != 24) &&
#endif
        (cl->format.bitsPerPixel != 32))
    {
        rfbErr("%s: client bits per pixel not 8, 16 or 32\n",
                "rfbSetTranslateFunction");
        rfbCloseClient(cl);
        return FALSE;
    }

    if (!cl->format.trueColour && (cl->format.bitsPerPixel != 8)) {
        rfbErr("rfbSetTranslateFunction: client has colour map "
                "but %d-bit - can only cope with 8-bit colour maps\n",
                cl->format.bitsPerPixel);
        rfbCloseClient(cl);
        return FALSE;
    }


    if (!cl->format.trueColour) {


        if (!rfbSetClientColourMapBGR233(cl))
            return FALSE;

        cl->format = BGR233Format;
    }


    if (PF_EQ(cl->format,cl->screen->serverFormat)) {


        rfbLog("no translation needed\n");
        cl->translateFn = rfbTranslateNone;
        return TRUE;
    }

    if ((cl->screen->serverFormat.bitsPerPixel < 16) ||
        ((!cl->screen->serverFormat.trueColour || !rfbEconomicTranslate) &&
	   (cl->screen->serverFormat.bitsPerPixel == 16))) {


        cl->translateFn = rfbTranslateWithSingleTableFns
                              [BPP2OFFSET(cl->screen->serverFormat.bitsPerPixel)]
                                  [BPP2OFFSET(cl->format.bitsPerPixel)];

	if(cl->screen->serverFormat.trueColour)
	  (*rfbInitTrueColourSingleTableFns
	   [BPP2OFFSET(cl->format.bitsPerPixel)]) (&cl->translateLookupTable,
						   &(cl->screen->serverFormat), &cl->format);
	else
	  (*rfbInitColourMapSingleTableFns
	   [BPP2OFFSET(cl->format.bitsPerPixel)]) (&cl->translateLookupTable,
						   &(cl->screen->serverFormat), &cl->format,&cl->screen->colourMap);

    } else {


        cl->translateFn = rfbTranslateWithRGBTablesFns
                              [BPP2OFFSET(cl->screen->serverFormat.bitsPerPixel)]
                                  [BPP2OFFSET(cl->format.bitsPerPixel)];

        (*rfbInitTrueColourRGBTablesFns
            [BPP2OFFSET(cl->format.bitsPerPixel)]) (&cl->translateLookupTable,
                                             &(cl->screen->serverFormat), &cl->format);
    }

    return TRUE;
}
