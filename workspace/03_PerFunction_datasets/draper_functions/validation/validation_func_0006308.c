__dbj_panic(DB_ENV *dbenv, int ret)
{
	int detach;
	JNIEnv *jenv = __dbj_get_jnienv(&detach);
	jobject jdbenv = (jobject)DB_ENV_INTERNAL(dbenv);

	if (jdbenv != NULL)
		(*jenv)->CallNonvirtualVoidMethod(jenv, jdbenv, dbenv_class,
		    paniccall_method,
		    __dbj_get_except(jenv, ret, NULL, NULL, jdbenv));

	if (detach)
		__dbj_detach();
}
