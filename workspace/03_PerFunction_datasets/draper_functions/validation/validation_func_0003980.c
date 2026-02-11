get_value(eel_data_t *arg, int types, int stypes)
{
	eel_data_t *dat;

	dat = arg;


#if 0
	while(EDT_SYMREF == dat->type)
#else
	if(EDT_SYMREF == dat->type)
#endif
	{
		switch(dat->value.sym->type)
		{
		  case EST_ENUM:

			if(types & EDTM_SYMREF)
				break;
		  case EST_CONSTANT:
		  case EST_VARIABLE:
			dat = &dat->value.sym->data;
			break;
		  default:
			eel_error("Invalid argument!");
			return NULL;
		}
	}

	if((EDT_SYMREF == dat->type) && (types & EDTM_SYMREF))
	{

		if(!(stypes & (1<<dat->value.sym->type)))
		{
			eel_error("Wrong symbol type! (%s)",
					eel_data_is(dat));
			return NULL;
		}
		return arg;
	}
	else
	{

		if(!(types & (1<<dat->type)))
		{
			eel_error("Wrong data type! (%s)",
					eel_data_is(dat));
			return NULL;
		}
		return dat;
	}
}
