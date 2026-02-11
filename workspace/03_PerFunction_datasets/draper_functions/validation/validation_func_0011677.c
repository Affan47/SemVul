Java_org_gdal_osr_osrJNI_GetProjectionMethodParameterList(JNIEnv *jenv, jclass jcls, jstring jarg1, jobjectArray jarg2) {
  jobjectArray jresult = 0 ;
  char *arg1 = (char *) 0 ;
  char **arg2 = (char **) 0 ;
  char *ret2 ;
  char **result = 0 ;

  (void)jenv;
  (void)jcls;
  arg1 = 0;
  if (jarg1) {
    arg1 = (char *)jenv->GetStringUTFChars(jarg1, 0);
    if (!arg1) return 0;
  }
  {

    if (!jarg2) {
      SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "array null");
      return 0;
    }
    if (jenv->GetArrayLength(jarg2) == 0) {
      SWIG_JavaThrowException(jenv, SWIG_JavaIndexOutOfBoundsException, "Array must contain at least 1 element");
      return 0;
    }
    arg2 = &ret2;
  }
  result = (char **)OPTGetParameterList(arg1,arg2);
  {

    char **stringarray = result;
    int i;
    int len=CSLCount(result);
    jstring temp_string;
    const jclass clazz = jenv->FindClass("java/lang/String");

    jresult = jenv->NewObjectArray(len, clazz, NULL);


    for (i=0; i<len; i++) {
      temp_string = jenv->NewStringUTF(*stringarray++);
      jenv->SetObjectArrayElement(jresult, i, temp_string);
      jenv->DeleteLocalRef(temp_string);
    }

    CSLDestroy(result);
  }
  {

    jstring temp_string = jenv->NewStringUTF(ret2);
    jenv->SetObjectArrayElement(jarg2, 0, temp_string);
    jenv->DeleteLocalRef(temp_string);
  }
  if (arg1) jenv->ReleaseStringUTFChars(jarg1, (const char *)arg1);
  return jresult;
}
