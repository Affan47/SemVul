ObjectAllocateSlot(
		   TPMI_DH_OBJECT  *handle
		   )
{
    OBJECT          *object = FindEmptyObjectSlot(handle);
    if(object != NULL)
	{

	    ObjectSetInUse(object);
	}
    return object;
}
