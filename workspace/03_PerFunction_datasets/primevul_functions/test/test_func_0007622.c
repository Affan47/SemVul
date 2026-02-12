void HierarchicalBitmapRequester::GenerateDifferentialImage(class Frame *target,
                                                            bool &hexp,bool &vexp)
{
#if ACCUSOFT_CODE
  class LineAdapter *lap = m_pLargestScale;

  while(lap) {


    if (lap->HighPassOf()->FrameOf() == target) {
      class LineMerger *lm = (class LineMerger *)lap;
      lm->GenerateDifferentialImage();
      hexp = lm->isHorizontallyExpanding();
      vexp = lm->isVerticallyExpanding();
      return;
    }
    lap = lap->LowPassOf();
  }
  assert(!"target band not found");
#else
  NOREF(target);
  NOREF(hexp);
  NOREF(vexp);
  JPG_THROW(NOT_IMPLEMENTED,"HierarchicalBitmapRequester::GenerateDifferentialImage",
            "Lossless JPEG not available in your code release, please contact Accusoft for a full version");
#endif
}
