decFontSize(const int stepping[], int count)
{
    int zoomFactor = d->m_fontScaleFactor;
    if (zoomFactor > minZoom) {

      for (int i = count-1; i >= 0; --i)
        if (stepping[i] < zoomFactor) {
          zoomFactor = stepping[i];
          break;
        }
      setFontScaleFactor(zoomFactor);
    }
}
