getSpatialRoD(OfxImageEffectHandle effect, OfxPropertySetHandle inArgs, OfxPropertySetHandle outArgs)
{

  MyInstanceData *myData = getMyInstanceData(effect);

  OfxTime time;
  gPropHost->propGetDouble(inArgs, kOfxPropTime, 0, &time);


  OfxRectD rod;
  getCannonicalRect(effect, time, rod);

  if(myData->context != eIsGenerator){

    OfxRectD sourceRoD;
    gEffectHost->clipGetRegionOfDefinition(myData->sourceClip, time, &sourceRoD);


    if(ofxuInfiniteRectInX(sourceRoD)) {
      rod.x1 = kOfxFlagInfiniteMin;
      rod.x2 = kOfxFlagInfiniteMax;
    }
    else {

      rod.x1 = Minimum(rod.x1, sourceRoD.x1);
      rod.x2 = Maximum(rod.x2, sourceRoD.x2);
    }


    if(ofxuInfiniteRectInY(sourceRoD)) {
      rod.y1 = kOfxFlagInfiniteMin;
      rod.y2 = kOfxFlagInfiniteMax;
    }
    else {

      rod.y1 = Minimum(rod.y1, sourceRoD.y1);
      rod.y2 = Maximum(rod.y2, sourceRoD.y2);
    }
  }


  gPropHost->propSetDoubleN(outArgs, kOfxImageEffectPropRegionOfDefinition, 4, &rod.x1);

  return kOfxStatOK;
}
