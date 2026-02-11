Java_org_gdal_gdal_gdalJNI_Dataset_1WriteRaster_1Direct_1_1SWIG_12(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jint jarg2, jint jarg3, jint jarg4, jint jarg5, jint jarg6, jint jarg7, jint jarg8, jobject jarg9, jintArray jarg11, jint jarg13) {
  jint jresult = 0 ;
  GDALDatasetShadow *arg1 = (GDALDatasetShadow *) 0 ;
  int arg2 ;
  int arg3 ;
  int arg4 ;
  int arg5 ;
  int arg6 ;
  int arg7 ;
  GDALDataType arg8 ;
  void *arg9 = (void *) 0 ;
  long arg10 ;
  int arg11 ;
  int *arg12 = (int *) 0 ;
  int arg13 ;
  CPLErr result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(GDALDatasetShadow **)&jarg1;
  arg2 = (int)jarg2;
  arg3 = (int)jarg3;
  arg4 = (int)jarg4;
  arg5 = (int)jarg5;
  arg6 = (int)jarg6;
  arg7 = (int)jarg7;
  arg8 = (GDALDataType)jarg8;
  {

    if (jarg9 == 0)
    {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
      return 0;
    }
    arg9 = jenv->GetDirectBufferAddress(jarg9);
    if (arg9 == NULL)
    {
      SWIG_JavaThrowException(jenv, SWIG_JavaRuntimeException,
        "Unable to get address of direct buffer. Buffer must be allocated direct.");
      return 0;
    }


    arg10 = (long) ((jenv->GetDirectBufferCapacity(jarg9) > INT_MAX) ? INT_MAX : jenv->GetDirectBufferCapacity(jarg9));
  }
  {


    if (jarg11)
    {
      arg11 = jenv->GetArrayLength(jarg11);
      if (arg11 == 0)
      arg12 = NULL;
      else
      arg12 = (int *)jenv->GetIntArrayElements(jarg11, NULL);
    }
    else
    {
      arg11 = 0;
      arg12 = NULL;
    }
  }
  arg13 = (int)jarg13;
  result = (CPLErr)GDALDatasetShadow_WriteRaster_Direct__SWIG_0(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13);
  jresult = (jint)result;
  {

  }
  {

    if (arg12) {
      jenv->ReleaseIntArrayElements(jarg11, (jint*)arg12, JNI_ABORT);
    }
  }
  return jresult;
}
