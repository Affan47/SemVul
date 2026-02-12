GetQualifiedName(
		 TPMI_DH_OBJECT   handle,
		 TPM2B_NAME      *qualifiedName
		 )
{
    OBJECT      *object;
    switch(HandleGetType(handle))
	{
	  case TPM_HT_PERMANENT:
	    qualifiedName->t.size = sizeof(TPM_HANDLE);
	    UINT32_TO_BYTE_ARRAY(handle, qualifiedName->t.name);
	    break;
	  case TPM_HT_TRANSIENT:
	    object = HandleToObject(handle);
	    if(object == NULL || object->publicArea.nameAlg == TPM_ALG_NULL)
		qualifiedName->t.size = 0;
	    else

		*qualifiedName = object->qualifiedName;
	    break;
	  default:
	    FAIL(FATAL_ERROR_INTERNAL);
	}
    return;
}
