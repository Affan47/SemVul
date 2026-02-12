rfbScreenInfoPtr rfbScalingFind(rfbClientPtr cl, int width, int height)
{
    rfbScreenInfoPtr ptr;

    for (ptr=cl->screen; ptr!=NULL; ptr=ptr->scaledScreenNext)
    {
        if ((ptr->width==width) && (ptr->height==height))
            return ptr;
    }
    return NULL;
}
