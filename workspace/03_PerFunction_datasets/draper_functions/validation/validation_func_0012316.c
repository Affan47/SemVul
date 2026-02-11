Class_getDeclaredMethod(JNIEnv *env, jobject obj , const char* p0 , jobject* p1 , jobject* result, lList **alpp) {
   jgdi_result_t ret = JGDI_SUCCESS;
   static jmethodID mid = NULL;

   jstring p0_obj = NULL;
   jobject temp = NULL;

   DENTER(BASIS_LAYER, "Class_getDeclaredMethod");

   if (result == NULL ) {
      answer_list_add(alpp, "result is NULL", STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
      DRETURN(JGDI_ILLEGAL_STATE);
   }

   *result = NULL;

  if (mid == NULL) {
     if (JGDI_SUCCESS != get_method_id_for_fullClassname(env, obj, &mid, "java/lang/Class", "getDeclaredMethod", "(Ljava/lang/String;[Ljava/lang/Class;)Ljava/lang/reflect/Method;", alpp)) {
        DRETURN(JGDI_ILLEGAL_STATE);
     }
   }

   if (p0 != NULL) {
      p0_obj = (*env)->NewStringUTF(env, p0 );
   }
   temp = (*env)->CallObjectMethod(env, obj, mid, p0_obj, p1);
   if (test_jni_error(env, "Class_getDeclaredMethod failed", alpp)) {
      ret = JGDI_ILLEGAL_STATE;
      temp = NULL;

   }
      *result = temp;

   DRETURN(ret);
}
