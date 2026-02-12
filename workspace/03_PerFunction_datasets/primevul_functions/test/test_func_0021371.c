HandleToObject(
	       TPMI_DH_OBJECT   handle
	       )
{
    UINT32              index;


    if(HandleGetType(handle) == TPM_HT_PERMANENT)
	return NULL;


    index = handle - TRANSIENT_FIRST;
    pAssert(index < MAX_LOADED_OBJECTS);
    pAssert(s_objects[index].attributes.occupied);
    return &s_objects[index];
}
