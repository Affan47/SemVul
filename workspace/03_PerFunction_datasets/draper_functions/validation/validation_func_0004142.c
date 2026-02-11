factory_type_store_get_factory_type(int type)
{
    if(type>=0 && type<number_of_types)
	{
	    return factory_type_store[type];
	}
	else
	{
	    return NULL;
	}
}
