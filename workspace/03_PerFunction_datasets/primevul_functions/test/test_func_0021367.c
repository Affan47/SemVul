ObjectStartup(
	      void
	      )
{
    UINT32      i;

    for(i = 0; i < MAX_LOADED_OBJECTS; i++)
	{

	    ObjectFlush(&s_objects[i]);
	}
    return;
}
