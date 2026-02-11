getDisplayedAreaSelection()
{
  if (currentImage==NULL) return NULL;
  DVPSDisplayedArea * area = displayedAreaSelectionList.findDisplayedArea(currentImageSOPInstanceUID, currentImageSelectedFrame);
  if (area==NULL)
  {
      DCMPSTAT_INFO("no displayed area selection item for current image found, creating default.");
      if ((currentImageDataset)&&(EC_Normal == createDefaultDisplayedArea(*currentImageDataset)))
      {
        area = displayedAreaSelectionList.findDisplayedArea(currentImageSOPInstanceUID, currentImageSelectedFrame);
      }
  }
  return area;
}
