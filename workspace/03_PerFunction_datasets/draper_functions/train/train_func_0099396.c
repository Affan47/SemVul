deletePixelRegion(VimosPixelRegion *aPixelRegion)
{

  VimosPixelRegion *tmpPRegion, *nextPRegion;
  if (aPixelRegion == NULL)
    {
     return;
    }


  tmpPRegion = aPixelRegion;


  while (tmpPRegion)
    {

     deletePixelList(tmpPRegion->pixelList);

     nextPRegion = tmpPRegion->next;

     pil_free(tmpPRegion);

     tmpPRegion = nextPRegion;
    }

}
