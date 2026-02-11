init()
{
  _self = 0.0;
  _incl  = 0.0;
  _callCount = 0.0;

  _firstPercentage = 1.0;
  _minDistance = 9999;
  _maxDistance = 0;
  _active = false;
  _inRecursion = false;
  for (int i = 0;i<maxHistogramDepth;i++) {
    _selfHisto[i] = 0.0;
    _inclHisto[i] = 0.0;
  }

  _valid = true;
}
