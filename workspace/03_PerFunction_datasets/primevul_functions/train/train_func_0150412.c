checkZOSThrWeightEnvVar(void)
{
	UDATA retVal = ZOS_THR_WEIGHT_NOT_FOUND;
#pragma convlit(suspend)
#undef getenv
	const char * const val = getenv("JAVA_THREAD_MODEL");

	if (NULL != val) {


		if (0 == strcmp(val, "HEAVY")) {
#pragma convlit(resume)
			retVal = ZOS_THR_WEIGHT_HEAVY;
		} else {
			retVal = ZOS_THR_WEIGHT_MEDIUM;
		}
	}

	return retVal;
}
