aclutil_gen_signature ( short c_signature )
{
	short	o_signature = 0;
	short   randval = (short)slapi_rand();
	o_signature = c_signature ^ (randval % 32768);
	if (!o_signature) {
		randval = (short)slapi_rand();
		o_signature = c_signature ^ (randval % 32768);
	}

	return o_signature;
}
