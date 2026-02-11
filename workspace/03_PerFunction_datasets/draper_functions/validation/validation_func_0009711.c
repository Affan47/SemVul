lotus_value (gnm_float v)
{
	if (v == gnm_floor (v) &&
	    v >= G_MININT &&
	    v <= G_MAXINT)
		return value_new_int ((int)v);
	else
		return value_new_float (v);
}
