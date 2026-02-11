Java_org_gdal_ogr_ogrJNI_new_1Geometry_1_1SWIG_10(JNIEnv *jenv, jclass jcls, jint jarg1, jstring jarg2, jbyteArray jarg3, jstring jarg5) {
  jlong jresult = 0 ;
  OGRwkbGeometryType arg1 ;
  char *arg2 = (char *) 0 ;
  int arg3 ;
  unsigned char *arg4 = (unsigned char *) 0 ;
  char *arg5 = (char *) 0 ;
  OGRGeometryShadow *result = 0 ;

  (void)jenv;
  (void)jcls;
  arg1 = (OGRwkbGeometryType)jarg1;
  arg2 = 0;
  if (jarg2) {
    arg2 = (char *)jenv->GetStringUTFChars(jarg2, 0);
    if (!arg2) return 0;
  }
  {

    arg3 = 0;
    arg4 = NULL;
    if (jarg3)
    {
      arg3 = jenv->GetArrayLength(jarg3);
      arg4 = (unsigned char *)jenv->GetByteArrayElements(jarg3, NULL);
    }
  }
  arg5 = 0;
  if (jarg5) {
    arg5 = (char *)jenv->GetStringUTFChars(jarg5, 0);
    if (!arg5) return 0;
  }
  result = (OGRGeometryShadow *)new_OGRGeometryShadow__SWIG_0(arg1,arg2,arg3,arg4,(char const *)arg5);
  *(OGRGeometryShadow **)&jresult = result;
  {

  }
  if (arg2) jenv->ReleaseStringUTFChars(jarg2, (const char *)arg2);
  {


    if(arg4) {
      jenv->ReleaseByteArrayElements(jarg3, (jbyte *)arg4, JNI_ABORT);
    }
  }
  if (arg5) jenv->ReleaseStringUTFChars(jarg5, (const char *)arg5);
  return jresult;
}
