void rfbScalingSetup(rfbClientPtr cl, int width, int height)
{
    rfbScreenInfoPtr ptr;

    ptr = rfbScalingFind(cl,width,height);
    if (ptr==NULL)
        ptr = rfbScaledScreenAllocate(cl,width,height);

    if (ptr!=NULL)
    {

        if (ptr->scaledScreenRefCount<1)
            rfbScaledScreenUpdateRect(cl->screen, ptr, 0, 0, cl->screen->width, cl->screen->height);


        LOCK(cl->updateMutex);
        cl->scaledScreen->scaledScreenRefCount--;
        ptr->scaledScreenRefCount++;
        cl->scaledScreen=ptr;
        cl->newFBSizePending = TRUE;
        UNLOCK(cl->updateMutex);

        rfbLog("Scaling to %dx%d (refcount=%d)\n",width,height,ptr->scaledScreenRefCount);
    }
    else
        rfbLog("Scaling to %dx%d failed, leaving things alone\n",width,height);
}
