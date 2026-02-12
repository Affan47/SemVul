ObjectContextLoad(
		  ANY_OBJECT_BUFFER   *object,

		  TPMI_DH_OBJECT      *handle
		  )
{
    OBJECT      *newObject = ObjectAllocateSlot(handle);

    if(newObject != NULL)
	{

	    MemoryCopy(newObject, object, offsetof(HASH_OBJECT, state));

	    if(ObjectIsSequence(newObject))
		{

		    SequenceDataImport((HASH_OBJECT *)newObject,
				       (HASH_OBJECT_BUFFER *)object);
		}
	    else
		{

		    MemoryCopy(newObject, object, sizeof(OBJECT));
		}
	}
    return newObject;
}
