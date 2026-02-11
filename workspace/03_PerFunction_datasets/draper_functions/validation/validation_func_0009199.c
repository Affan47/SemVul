pixelIsOn(int value, DiscretizeSettings settings) const
{
  switch (settings.discretizeMethod)
  {
  case DiscretizeNone:
    ASSERT_ENGAUGE(0);
    break;
  case DiscretizeIntensity:
    return pixelIsOn(value, settings.intensityThresholdLow, settings.intensityThresholdHigh);
  case DiscretizeForeground:
    return pixelIsOn(value, settings.foregroundThresholdLow, settings.foregroundThresholdHigh);
  case DiscretizeHue:
    return pixelIsOn(value, settings.hueThresholdLow, settings.hueThresholdHigh);
  case DiscretizeSaturation:
    return pixelIsOn(value, settings.saturationThresholdLow, settings.saturationThresholdHigh);
  case DiscretizeValue:
    return pixelIsOn(value, settings.valueThresholdLow, settings.valueThresholdHigh);
  }

  return false;
}
