IsObjectPresent(
		TPMI_DH_OBJECT   handle
		)
{
    UINT32          slotIndex = handle - TRANSIENT_FIRST;


    if(slotIndex >= MAX_LOADED_OBJECTS)
	return FALSE;

    return (s_objects[slotIndex].attributes.occupied == TRUE);
}
