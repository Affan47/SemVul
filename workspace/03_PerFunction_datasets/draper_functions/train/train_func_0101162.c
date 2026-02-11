Java_org_gdal_ogr_ogrJNI_Layer_1Identity_1_1SWIG_13(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jlong jarg2, jobject jarg2_, jlong jarg3, jobject jarg3_) {
  jint jresult = 0 ;
  OGRLayerShadow *arg1 = (OGRLayerShadow *) 0 ;
  OGRLayerShadow *arg2 = (OGRLayerShadow *) 0 ;
  OGRLayerShadow *arg3 = (OGRLayerShadow *) 0 ;
  OGRErr result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg2_;
  (void)jarg3_;
  arg1 = *(OGRLayerShadow **)&jarg1;
  arg2 = *(OGRLayerShadow **)&jarg2;
  arg3 = *(OGRLayerShadow **)&jarg3;
  result = (OGRErr)OGRLayerShadow_Identity__SWIG_0(arg1,arg2,arg3);
  {

    if (result != 0 && bUseExceptions) {
      SWIG_JavaThrowException(jenv, SWIG_JavaRuntimeException,
        OGRErrMessages(result));
      return 0;
    }
    jresult = (jint)result;
  }
  {


  }
  return jresult;
}
