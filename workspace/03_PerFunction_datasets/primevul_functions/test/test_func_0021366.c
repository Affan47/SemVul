ObjectCapGetLoaded(
		   TPMI_DH_OBJECT   handle,
		   UINT32           count,
		   TPML_HANDLE     *handleList
		   )
{
    TPMI_YES_NO          more = NO;
    UINT32               i;
    pAssert(HandleGetType(handle) == TPM_HT_TRANSIENT);

    handleList->count = 0;

    if(count > MAX_CAP_HANDLES) count = MAX_CAP_HANDLES;

    for(i = handle - TRANSIENT_FIRST; i < MAX_LOADED_OBJECTS; i++)
	{
	    if(s_objects[i].attributes.occupied == TRUE)
		{

		    pAssert(s_objects[i].attributes.evict == CLEAR);
		    if(handleList->count < count)
			{


			    handleList->handle[handleList->count] = i + TRANSIENT_FIRST;
			    handleList->count++;
			}
		    else
			{


			    more = YES;
			    break;
			}
		}
	}
    return more;
}
