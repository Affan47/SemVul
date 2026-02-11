__dbj_dbt_release(
    JNIEnv *jenv, jobject jdbt, DBT *dbt, DBT_LOCKED *ldbt) {
	jthrowable t;

	if (dbt == NULL)
		return;

	if (dbt->size != ldbt->orig_size)
		(*jenv)->SetIntField(jenv, jdbt, dbt_size_fid, (jint)dbt->size);

	if (F_ISSET(dbt, DB_DBT_USERMEM)) {
		if (ldbt->jarr != NULL)
			(*jenv)->ReleaseByteArrayElements(jenv, ldbt->jarr,
			    (jbyte *)dbt->data - ldbt->offset, 0);

		if (dbt->size > dbt->ulen &&
		    (t = (*jenv)->ExceptionOccurred(jenv)) != NULL &&
		    (*jenv)->IsInstanceOf(jenv, t, memex_class)) {
			(*jenv)->CallNonvirtualVoidMethod(jenv, t, memex_class,
			    memex_update_method, jdbt);


			(*jenv)->Throw(jenv, t);
		}
	}
}
