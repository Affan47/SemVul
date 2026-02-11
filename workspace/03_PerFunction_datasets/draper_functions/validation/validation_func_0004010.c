Java_com_sun_grid_jgdi_jni_JGDIBaseImpl_nativeShowDetachedSettingsAllWithAnswer(JNIEnv *env, jobject jgdi, jobject answers) {

   jstring jdetachedStr = NULL;

   DENTER(TOP_LAYER, "Java_com_sun_grid_jgdi_jni_JGDIBaseImpl_nativeShowDetachedSettingsAllWithAnswer");

   jgdi_detached_settings(env, jgdi, NULL, &jdetachedStr, answers);

   DRETURN(jdetachedStr);
}
