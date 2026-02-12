mp_sint32 PlayerGeneric::setBufferSize(mp_uint32 bufferSize)
{
	mp_sint32 res = 0;

	this->bufferSize = bufferSize;

	if (mixer)
	{


		if (compensateBufferFlag)
		{
			for (mp_uint32 i = 0; i < 16; i++)
			{
				if ((unsigned)(1 << i) >= (unsigned)bufferSize)
				{
					bufferSize = 1 << i;
					break;
				}
			}
		}

		res = mixer->setBufferSize(bufferSize);
	}

	return res;
}
