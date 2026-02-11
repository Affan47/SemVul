getClipPreferences(OfxImageEffectHandle effect, OfxPropertySetHandle , OfxPropertySetHandle outArgs)
{

  MyInstanceData *myData = getMyInstanceData(effect);

  if(myData->context == eIsGenerator) {

    gPropHost->propSetString(outArgs, kOfxImageEffectPropPreMultiplication, 0, kOfxImagePreMultiplied);
  }
  else {
    OfxPropertySetHandle clipProps;
    gEffectHost->clipGetPropertySet(myData->sourceClip, &clipProps);


    char *premult;
    gPropHost->propGetString(clipProps, kOfxImageEffectPropPreMultiplication, 0, &premult);

    gPropHost->propSetString(outArgs, kOfxImageEffectPropPreMultiplication, 0, premult);
  }

  return kOfxStatOK;
}
