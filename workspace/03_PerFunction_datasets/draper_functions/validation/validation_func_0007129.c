probe2Arrival()
{
   m_CurrArrTime = CTimer::getTime();


   *(m_piProbeWindow + m_iProbeWindowPtr) = int(m_CurrArrTime - m_ProbeTime);

   ++ m_iProbeWindowPtr;
   if (m_iProbeWindowPtr == m_iPWSize)
      m_iProbeWindowPtr = 0;
}
