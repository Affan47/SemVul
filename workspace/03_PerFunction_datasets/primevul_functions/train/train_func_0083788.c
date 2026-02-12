rfbSendFramebufferUpdate(rfbClientPtr cl,
                         sraRegionPtr givenUpdateRegion)
{
    sraRectangleIterator* i=NULL;
    sraRect rect;
    int nUpdateRegionRects;
    rfbFramebufferUpdateMsg *fu = (rfbFramebufferUpdateMsg *)cl->updateBuf;
    sraRegionPtr updateRegion, updateCopyRegion, tmpRegion, cursorRegion;
    sraRect cursorBounds = { 0, 0, 0, 0 };
    int dx, dy;
    rfbBool sendCursorShape = FALSE;
    rfbBool sendCursorPos = FALSE;
    rfbBool cursorIsDrawn = FALSE;


    if (cl->useNewFBSize && cl->newFBSizePending) {
      LOCK(cl->updateMutex);
      cl->newFBSizePending = FALSE;
      UNLOCK(cl->updateMutex);
      cl->rfbFramebufferUpdateMessagesSent++;
      fu->type = rfbFramebufferUpdate;
      fu->nRects = Swap16IfLE(1);
      cl->ublen = sz_rfbFramebufferUpdateMsg;
      if (!rfbSendNewFBSize(cl, cl->screen->width, cl->screen->height)) {
        return FALSE;
      }
      return rfbSendUpdateBuf(cl);
    }

    LOCK(cl->updateMutex);


    sraRgnSubtract(cl->copyRegion,cl->modifiedRegion);

    updateRegion = sraRgnCreateRgn(givenUpdateRegion);
    sraRgnOr(updateRegion,cl->copyRegion);


    LOCK(cl->screen->cursorMutex);

    cursorRegion = NULL;
    if (cl->enableCursorUpdates) {
	sendCursorShape = cl->cursorWasChanged;
	sendCursorPos   = cl->cursorWasMoved;
    } else {
	sraRegionPtr lastDrawnCursorRegion;

	if (rfbGetCursorBounds(cl->screen, &cursorBounds)) {
	    cursorRegion = sraRgnCreateRect(cursorBounds.x1, cursorBounds.y1,
					    cursorBounds.x2, cursorBounds.y2);
	}

	lastDrawnCursorRegion = sraRgnCreateRect(cl->lastDrawnCursorBounds.x1,
						 cl->lastDrawnCursorBounds.y1,
						 cl->lastDrawnCursorBounds.x2,
						 cl->lastDrawnCursorBounds.y2);

	if (cursorRegion) {
	    sraRgnOr(cursorRegion, lastDrawnCursorRegion);
	    sraRgnDestroy(lastDrawnCursorRegion);
	} else {
	    cursorRegion = lastDrawnCursorRegion;
	}

	if (cl->cursorWasChanged || cl->cursorWasMoved)
	    sraRgnOr(updateRegion, cursorRegion);
    }


    if (!sraRgnAnd(updateRegion, cl->requestedRegion) &&
	!sendCursorShape && !sendCursorPos) {
	sraRgnDestroy(updateRegion);
	if (cursorRegion)
	    sraRgnDestroy(cursorRegion);
	UNLOCK(cl->updateMutex);
	UNLOCK(cl->cursorMutex);
	return TRUE;
    }


    if (cursorRegion) {
	tmpRegion = sraRgnCreateRgn(cursorRegion);

	if (sraRgnAnd(tmpRegion, updateRegion)) {
	    rfbDrawCursor(cl->screen, &cursorBounds);
	    cursorIsDrawn = TRUE;

	    cl->cursorWasMoved = FALSE;
	    cl->cursorWasChanged = FALSE;
	    cl->lastDrawnCursorBounds = cursorBounds;

	    sraRgnOr(cl->modifiedRegion, cursorRegion);

	    sraRgnOr(updateRegion, cursorRegion);
	    sraRgnAnd(updateRegion, cl->requestedRegion);
	}

	sraRgnDestroy(tmpRegion);
	sraRgnDestroy(cursorRegion);
    }


    updateCopyRegion = sraRgnCreateRgn(cl->copyRegion);
    sraRgnAnd(updateCopyRegion,cl->requestedRegion);
    tmpRegion = sraRgnCreateRgn(cl->requestedRegion);
    sraRgnOffset(tmpRegion,cl->copyDX,cl->copyDY);
    sraRgnAnd(updateCopyRegion,tmpRegion);
    sraRgnDestroy(tmpRegion);
    dx = cl->copyDX;
    dy = cl->copyDY;


    sraRgnSubtract(updateRegion,updateCopyRegion);


     sraRgnOr(cl->modifiedRegion,cl->copyRegion);
     sraRgnSubtract(cl->modifiedRegion,updateRegion);
     sraRgnSubtract(cl->modifiedRegion,updateCopyRegion);

     sraRgnMakeEmpty(cl->requestedRegion);
     sraRgnMakeEmpty(cl->copyRegion);
     cl->copyDX = 0;
     cl->copyDY = 0;

     UNLOCK(cl->updateMutex);


    cl->rfbFramebufferUpdateMessagesSent++;

    if (cl->preferredEncoding == rfbEncodingCoRRE) {
        nUpdateRegionRects = 0;

        for(i = sraRgnGetIterator(updateRegion); sraRgnIteratorNext(i,&rect);){
            int x = rect.x1;
            int y = rect.y1;
            int w = rect.x2 - x;
            int h = rect.y2 - y;
            nUpdateRegionRects += (((w-1) / cl->correMaxWidth + 1)
                                     * ((h-1) / cl->correMaxHeight + 1));
        }
	sraRgnReleaseIterator(i);
#ifdef HAVE_LIBZ
    } else if (cl->preferredEncoding == rfbEncodingZlib) {
	nUpdateRegionRects = 0;

        for(i = sraRgnGetIterator(updateRegion); sraRgnIteratorNext(i,&rect);){
            int x = rect.x1;
            int y = rect.y1;
            int w = rect.x2 - x;
            int h = rect.y2 - y;
	    nUpdateRegionRects += (((h-1) / (ZLIB_MAX_SIZE( w ) / w)) + 1);
	}
#ifdef HAVE_LIBJPEG
    } else if (cl->preferredEncoding == rfbEncodingTight) {
	nUpdateRegionRects = 0;

        for(i = sraRgnGetIterator(updateRegion); sraRgnIteratorNext(i,&rect);){
            int x = rect.x1;
            int y = rect.y1;
            int w = rect.x2 - x;
            int h = rect.y2 - y;
	    int n = rfbNumCodedRectsTight(cl, x, y, w, h);
	    if (n == 0) {
		nUpdateRegionRects = 0xFFFF;
		break;
	    }
	    nUpdateRegionRects += n;
	}
	sraRgnReleaseIterator(i);
#endif
#endif
    } else {
        nUpdateRegionRects = sraRgnCountRects(updateRegion);
    }

    fu->type = rfbFramebufferUpdate;
    if (nUpdateRegionRects != 0xFFFF) {
	if(cl->screen->maxRectsPerUpdate>0

	   && cl->preferredEncoding != rfbEncodingCoRRE
#ifdef HAVE_LIBZ

	   && cl->preferredEncoding != rfbEncodingZlib
#ifdef HAVE_LIBJPEG

	   && cl->preferredEncoding != rfbEncodingTight
#endif
#endif
	   && nUpdateRegionRects>cl->screen->maxRectsPerUpdate) {
	    sraRegion* newUpdateRegion = sraRgnBBox(updateRegion);
	    sraRgnDestroy(updateRegion);
	    updateRegion = newUpdateRegion;
	    nUpdateRegionRects = sraRgnCountRects(updateRegion);
	}
	fu->nRects = Swap16IfLE((uint16_t)(sraRgnCountRects(updateCopyRegion) +
					   nUpdateRegionRects +
					   !!sendCursorShape + !!sendCursorPos));
    } else {
	fu->nRects = 0xFFFF;
    }
    cl->ublen = sz_rfbFramebufferUpdateMsg;

    UNLOCK(cl->cursorMutex);

   if (sendCursorShape) {
	cl->cursorWasChanged = FALSE;
	if (!rfbSendCursorShape(cl))
	    goto tx_error;
    }

   if (sendCursorPos) {
	cl->cursorWasMoved = FALSE;
	if (!rfbSendCursorPos(cl))
	    goto tx_error;
    }

    if (!sraRgnEmpty(updateCopyRegion)) {
	if (!rfbSendCopyRegion(cl,updateCopyRegion,dx,dy))
	    goto tx_error;
    }

    for(i = sraRgnGetIterator(updateRegion); sraRgnIteratorNext(i,&rect);){
        int x = rect.x1;
        int y = rect.y1;
        int w = rect.x2 - x;
        int h = rect.y2 - y;

        cl->rfbRawBytesEquivalent += (sz_rfbFramebufferUpdateRectHeader
                                      + w * (cl->format.bitsPerPixel / 8) * h);

        switch (cl->preferredEncoding) {
        case rfbEncodingRaw:
            if (!rfbSendRectEncodingRaw(cl, x, y, w, h))
		goto tx_error;
            break;
        case rfbEncodingRRE:
            if (!rfbSendRectEncodingRRE(cl, x, y, w, h))
		goto tx_error;
            break;
        case rfbEncodingCoRRE:
            if (!rfbSendRectEncodingCoRRE(cl, x, y, w, h))
		goto tx_error;
            break;
        case rfbEncodingHextile:
            if (!rfbSendRectEncodingHextile(cl, x, y, w, h))
		goto tx_error;
            break;
#ifdef HAVE_LIBZ
	case rfbEncodingZlib:
	    if (!rfbSendRectEncodingZlib(cl, x, y, w, h))
		goto tx_error;
	    break;
#ifdef HAVE_LIBJPEG
	case rfbEncodingTight:
	    if (!rfbSendRectEncodingTight(cl, x, y, w, h))
		goto tx_error;
	    break;
#endif
#endif
#ifdef HAVE_LIBZ
       case rfbEncodingZRLE:
           if (!rfbSendRectEncodingZRLE(cl, x, y, w, h))
	       goto tx_error;
           break;
#endif
        }
    }

    if (cursorIsDrawn)
	rfbUndrawCursor(cl->screen, &cursorBounds);

    if ( nUpdateRegionRects == 0xFFFF &&
	 !rfbSendLastRectMarker(cl) )
	goto tx_error;

    if (!rfbSendUpdateBuf(cl))
	goto tx_error;

    sraRgnReleaseIterator(i);
    sraRgnDestroy(updateCopyRegion);
    sraRgnDestroy(updateRegion);

    return TRUE;

 tx_error:
    if (cursorIsDrawn)
	rfbUndrawCursor(cl->screen, &cursorBounds);
    if (i)
	sraRgnReleaseIterator(i);

    sraRgnDestroy(updateCopyRegion);
    sraRgnDestroy(updateRegion);

    return FALSE;
}
