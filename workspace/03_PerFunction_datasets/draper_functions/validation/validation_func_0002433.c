add_bit(CByteArray *data, unsigned long *bit_pos, unsigned char bit_value)
{
	if(((*bit_pos)&7)==0)
	{
		unsigned char v=0;

		data->Append(&v,1);
	}


	if(bit_value!=0)
	{
		data->Data()[(*bit_pos)/8]|= (1<<((*bit_pos)&7));
	}

	(*bit_pos)++;

	return data;
}
