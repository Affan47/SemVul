JVM_CurrentLoadedClass(JNIEnv *env)
{
	jobject result;

	Trc_SC_CurrentLoadedClass_Entry(env);

	result = (*env)->CallStaticObjectMethod(env, jlClass, currentLoadedClassMID);


	if ((*env)->ExceptionCheck(env)) {
		result = NULL;
	}

	Trc_SC_CurrentLoadedClass_Exit(env, result);

	return result;
}
