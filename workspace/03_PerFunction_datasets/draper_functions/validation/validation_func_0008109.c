get_descriptor_for_property(JNIEnv *env, jobject property_descr, lDescr **descr, lList **alpp) {

   jstring   cull_type_name_obj;
   const char* cull_type_name;
   jgdi_result_t  ret = JGDI_SUCCESS;

   DENTER(BASIS_LAYER, "get_descriptor_for_property");

   ret = PropertyDescriptor_getCullType(env, property_descr, &cull_type_name_obj, alpp);
   if (ret != JGDI_SUCCESS) {
      DRETURN(ret);
   }
   if (cull_type_name_obj == NULL) {
      answer_list_add(alpp, "get_descriptor_for_property: cull_type_name_obj is NULL.", STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
      DRETURN(JGDI_ILLEGAL_STATE);
   }

   cull_type_name = (*env)->GetStringUTFChars(env, cull_type_name_obj, 0);
   if (cull_type_name == NULL) {
      answer_list_add(alpp, "get_descriptor_for_property: GetStringUTFChars failed. Out of memory.", STATUS_EMALLOC, ANSWER_QUALITY_ERROR);
      DRETURN(JGDI_ERROR);
   }

   *descr = get_descr(cull_type_name);
   if (*descr == NULL) {
      answer_list_add_sprintf(alpp, STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR,
                              "get_descriptor_for_property: no descr for cull type %s found",  cull_type_name);
      ret = JGDI_ERROR;
   }
   (*env)->ReleaseStringUTFChars(env, cull_type_name_obj, cull_type_name);

   DRETURN(ret);
}
