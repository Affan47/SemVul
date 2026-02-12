void rfbScaledScreenUpdate(rfbScreenInfoPtr screen, int x1, int y1, int x2, int y2)
{


    rfbScreenInfoPtr ptr;
    int count=0;


    for (ptr=screen->scaledScreenNext;ptr!=NULL;ptr=ptr->scaledScreenNext)
    {

        if (ptr->scaledScreenRefCount>0)
        {
          rfbScaledScreenUpdateRect(screen, ptr, x1, y1, x2-x1, y2-y1);
          count++;
        }
    }
}
