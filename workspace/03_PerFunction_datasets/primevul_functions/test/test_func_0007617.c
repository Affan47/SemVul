void HierarchicalBitmapRequester::AddImageScale(class Frame *frame,bool expandh,bool expandv)
{
#if ACCUSOFT_CODE
  if (m_pLargestScale == NULL) {
    assert(m_pSmallestScale == NULL);
    assert(expandh == false && expandv == false);

    m_pLargestScale  = frame->BuildLineAdapter();
    m_pSmallestScale = m_pLargestScale;
    frame->SetImageBuffer(m_pLargestScale);
  } else {
    class LineMerger *merger;


    assert(m_pTempAdapter == NULL);

    m_pTempAdapter   = frame->BuildLineAdapter();

    merger           = new(m_pEnviron) class LineMerger(frame,m_pLargestScale,m_pTempAdapter,
                                                        expandh,expandv);


    m_pLargestScale  = merger;

    frame->SetImageBuffer(m_pTempAdapter);
    m_pTempAdapter   = NULL;
  }
#else
  NOREF(frame);
  NOREF(expandh);
  NOREF(expandv);
#endif
}
