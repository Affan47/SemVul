ObjectCapGetTransientAvail(
			   void
			   )
{
    UINT32      i;
    UINT32      num = 0;

    for(i = 0; i < MAX_LOADED_OBJECTS; i++)
	{
	    if(s_objects[i].attributes.occupied == FALSE) num++;
	}
    return num;
}
