Java_org_gdal_osr_osrJNI_SpatialReference_1ImportFromESRI(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jobject jarg2) {
  jint jresult = 0 ;
  OSRSpatialReferenceShadow *arg1 = (OSRSpatialReferenceShadow *) 0 ;
  char **arg2 = (char **) 0 ;
  OGRErr result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(OSRSpatialReferenceShadow **)&jarg1;
  {

    arg2 = NULL;
    if(jarg2 != 0) {
      const jclass vector = jenv->FindClass("java/util/Vector");
      const jclass enumeration = jenv->FindClass("java/util/Enumeration");
      const jclass stringClass = jenv->FindClass("java/lang/String");
      const jmethodID elements = jenv->GetMethodID(vector, "elements",
        "()Ljava/util/Enumeration;");
      const jmethodID hasMoreElements = jenv->GetMethodID(enumeration,
        "hasMoreElements", "()Z");
      const jmethodID getNextElement = jenv->GetMethodID(enumeration,
        "nextElement", "()Ljava/lang/Object;");
      if(vector == NULL || enumeration == NULL || elements == NULL ||
        hasMoreElements == NULL || getNextElement == NULL) {
        fprintf(stderr, "Could not load (options **) jni types.\n");
        return 0;
      }
      for (jobject keys = jenv->CallObjectMethod(jarg2, elements);
        jenv->CallBooleanMethod(keys, hasMoreElements) == JNI_TRUE;) {
        jstring value = (jstring)jenv->CallObjectMethod(keys, getNextElement);
        if (value == NULL || !jenv->IsInstanceOf(value, stringClass))
        {
          CSLDestroy(arg2);
          SWIG_JavaThrowException(jenv, SWIG_JavaIllegalArgumentException, "an element in the vector is not a string");
          return 0;
        }
        const char *valptr = jenv->GetStringUTFChars(value, 0);
        arg2 = CSLAddString(arg2,  valptr);
        jenv->ReleaseStringUTFChars(value, valptr);
      }
    }
  }
  result = (OGRErr)OSRSpatialReferenceShadow_ImportFromESRI(arg1,arg2);
  {

    if (result != 0 && bUseExceptions) {
      SWIG_JavaThrowException(jenv, SWIG_JavaRuntimeException,
        OGRErrMessages(result));
      return 0;
    }
    jresult = (jint)result;
  }
  {

    CSLDestroy( arg2 );
  }
  {


  }
  return jresult;
}
