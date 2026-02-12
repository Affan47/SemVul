rfbScreenInfoPtr rfbScaledScreenAllocate(rfbClientPtr cl, int width, int height)
{
    rfbScreenInfoPtr ptr;
    ptr = malloc(sizeof(rfbScreenInfo));
    if (ptr!=NULL)
    {
        int allocSize;


        memcpy(ptr, cl->screen, sizeof(rfbScreenInfo));


        allocSize = pad4(width * (ptr->bitsPerPixel/8));
        if (height == 0 || allocSize >= SIZE_MAX / height)
        {
          free(ptr);
          return NULL;
        }


        ptr->width = width;
        ptr->height = height;
        ptr->paddedWidthInBytes = (ptr->bitsPerPixel/8)*ptr->width;


        ptr->paddedWidthInBytes = pad4(ptr->paddedWidthInBytes);


        ptr->scaledScreenRefCount = 0;

        ptr->sizeInBytes = ptr->paddedWidthInBytes * ptr->height;
        ptr->serverFormat = cl->screen->serverFormat;

        ptr->frameBuffer = malloc(ptr->sizeInBytes);
        if (ptr->frameBuffer!=NULL)
        {

            rfbScaledScreenUpdateRect(cl->screen, ptr, 0, 0, cl->screen->width, cl->screen->height);

            LOCK(cl->updateMutex);
            ptr->scaledScreenNext = cl->screen->scaledScreenNext;
            cl->screen->scaledScreenNext = ptr;
            UNLOCK(cl->updateMutex);
        }
        else
        {

            free(ptr);
            ptr=NULL;
        }
    }
    return ptr;
}
