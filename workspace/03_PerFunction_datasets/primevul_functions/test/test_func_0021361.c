FlushObject(
	    TPMI_DH_OBJECT   handle
	    )
{
    UINT32      index = handle - TRANSIENT_FIRST;
    pAssert(index < MAX_LOADED_OBJECTS);

    MemorySet((BYTE*)&(s_objects[index].attributes),
	      0, sizeof(OBJECT_ATTRIBUTES));
    return;
}
