ObjectCleanupEvict(
		   void
		   )
{
    UINT32      i;


    for(i = 0; i < MAX_LOADED_OBJECTS; i++)
	{

	    OBJECT      *object = &s_objects[i];
	    if(object->attributes.evict == SET)
		ObjectFlush(object);
	}
    return;
}
