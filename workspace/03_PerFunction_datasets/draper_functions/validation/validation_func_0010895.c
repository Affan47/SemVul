get_f(int symbol)
{
	if(check_symbol(symbol) < 0)
		return 0.0;
	switch(table[symbol]->typecode)
	{
	  case CFG_NONE:
		return 0.0;
	  case CFG_BOOL:
		{
			cfg_switch_t *k = (cfg_switch_t *)table[symbol];
			return *(k->value) ? 1.0 : 0.0;
		}
	  case CFG_INT:
		{
			cfg_key_int_t *k = (cfg_key_int_t *)table[symbol];
			return (float)*(k->value);
		}
	  case CFG_FLOAT:
		{
			cfg_key_float_t *k = (cfg_key_float_t *)table[symbol];
			return *(k->value);
		}
	  case CFG_STRING:
		{
			cfg_key_string_t *k = (cfg_key_string_t *)table[symbol];
			return atof(*(k->value));
		}
	}
	return 0.0;
}
