ObjectLoadEvict(
		TPM_HANDLE      *handle,

		COMMAND_INDEX    commandIndex
		)
{
    TPM_RC          result;
    TPM_HANDLE      evictHandle = *handle;
    OBJECT          *object;


    if(*handle >= PLATFORM_PERSISTENT)
	{

	    if(g_phEnable == CLEAR)
		return TPM_RC_HANDLE;
	}

    else if(gc.shEnable == CLEAR)
	return TPM_RC_HANDLE;

    object = ObjectAllocateSlot(handle);
    if(object == NULL)
	return TPM_RC_OBJECT_MEMORY;


    result = NvGetEvictObject(evictHandle, object);

    if(result != TPM_RC_SUCCESS)
	return result;


    if(ObjectGetHierarchy(object) == TPM_RH_ENDORSEMENT
       && gc.ehEnable == CLEAR
       && GetCommandCode(commandIndex) != TPM_CC_EvictControl)
	return TPM_RC_HANDLE;
    return result;
}
