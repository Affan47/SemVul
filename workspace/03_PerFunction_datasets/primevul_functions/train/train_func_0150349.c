JVM_CurrentClassLoader(JNIEnv *env)
{
	jobject result;

	Trc_SC_CurrentClassLoader_Entry(env);

	result = (*env)->CallStaticObjectMethod(env, jlClass, currentClassLoaderMID);


	if ((*env)->ExceptionCheck(env)) {
		result = NULL;
	}

	Trc_SC_CurrentClassLoader_Exit(env, result);

	return result;
}
