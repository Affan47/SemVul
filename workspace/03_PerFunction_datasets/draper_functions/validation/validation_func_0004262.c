f0r_get_param_value(f0r_instance_t instance,
                         f0r_param_t param, int param_index)
{
	letterb0xed_instance_t* inst = (letterb0xed_instance_t*)instance;
	switch ( param_index ) {
		case 0:
			*((double*)param) = inst->value;
			break;
		case 1:
			*((double*)param) = inst->bg_transparent;
			break;
	}
}
