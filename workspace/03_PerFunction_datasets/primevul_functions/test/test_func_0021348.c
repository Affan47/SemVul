GetHeriarchy(
	     TPMI_DH_OBJECT   handle
	     )
{
    OBJECT          *object = HandleToObject(handle);
    return ObjectGetHierarchy(object);
}
