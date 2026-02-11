sqrtButtonClicked(bool value)
{
  char str[600];

  if(value == FALSE)
  {
    sqrt_powerspectrum = 0;

    sprintf(str, "Power Spectral Density %s", signallabel);

    dock->setWindowTitle(str);

    sprintf(str, "(%s)^2/Hz", physdimension);

    curve1->setV_label(str);
  }
  else
  {
    sqrt_powerspectrum = 1;

    sprintf(str, "Amplitude Spectrum %s", signallabel);

    curve1->setV_label(physdimension);

    dock->setWindowTitle(str);
  }

  sliderMoved(0);
}
