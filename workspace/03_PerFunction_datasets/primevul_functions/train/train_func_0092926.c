ALG_Encrypt(ALGobject *self, PyObject *args)
{
	unsigned char *buffer, *str;
	unsigned char temp[BLOCK_SIZE];
	int i, j, len;
	PyObject *result;

	if (!PyArg_Parse(args, "s#", &str, &len))
		return NULL;
	if (len==0)
	{
		return PyBytes_FromStringAndSize(NULL, 0);
	}
	if ( (len % BLOCK_SIZE) !=0 &&
	     (self->mode!=MODE_CFB) &&
	     (self->mode!=MODE_OFB) &&
	     (self->mode!=MODE_CTR))
	{
		PyErr_Format(PyExc_ValueError,
			     "Input strings must be "
			     "a multiple of %i in length",
			     BLOCK_SIZE);
		return NULL;
	}
	if (self->mode == MODE_CFB &&
	    (len % (self->segment_size/8) !=0)) {
		PyErr_Format(PyExc_ValueError,
			     "Input strings must be a multiple of "
			     "the segment size %i in length",
			     self->segment_size/8);
		return NULL;
	}

	buffer=malloc(len);
	if (buffer==NULL)
	{
		PyErr_SetString(PyExc_MemoryError,
				"No memory available in "
				_MODULE_STRING " encrypt");
		return NULL;
	}
	Py_BEGIN_ALLOW_THREADS;
	switch(self->mode)
	{
	case(MODE_ECB):
		for(i=0; i<len; i+=BLOCK_SIZE)
		{
			block_encrypt(&(self->st), str+i, buffer+i);
		}
		break;

	case(MODE_CBC):
		for(i=0; i<len; i+=BLOCK_SIZE)
		{
			for(j=0; j<BLOCK_SIZE; j++)
			{
				temp[j]=str[i+j]^self->IV[j];
			}
			block_encrypt(&(self->st), temp, buffer+i);
			memcpy(self->IV, buffer+i, BLOCK_SIZE);
		}
		break;

	case(MODE_CFB):
		for(i=0; i<len; i+=self->segment_size/8)
		{
			block_encrypt(&(self->st), self->IV, temp);
			for (j=0; j<self->segment_size/8; j++) {
				buffer[i+j] = str[i+j] ^ temp[j];
			}
			if (self->segment_size == BLOCK_SIZE * 8) {


				memcpy(self->IV, buffer + i, BLOCK_SIZE);
			}
			else if ((self->segment_size % 8) == 0) {
				int sz = self->segment_size/8;
				memmove(self->IV, self->IV + sz,
					BLOCK_SIZE-sz);
				memcpy(self->IV + BLOCK_SIZE - sz, buffer + i,
				       sz);
			}
			else {


			}
		}
		break;

	case(MODE_OFB):


		i = 0;
		while(i < len)
		{

			if (len-i <= BLOCK_SIZE-self->count) {

				for(j=0; j<(len-i); j++) {
					assert(i+j < len);
					assert(self->count+j < BLOCK_SIZE);
					buffer[i+j] = self->IV[self->count+j] ^ str[i+j];
				}
				self->count += len-i;
				i = len;
				continue;
			}


			for(j=0; j<BLOCK_SIZE-self->count; j++) {
				assert(i+j < len);
				assert(self->count+j < BLOCK_SIZE);
				buffer[i+j] = self->IV[self->count+j] ^ str[i+j];
			}
			i += BLOCK_SIZE-self->count;
			self->count = BLOCK_SIZE;


			block_encrypt(&(self->st), self->IV, temp);
			memcpy(self->IV, temp, BLOCK_SIZE);


			self->count = 0;
		}
		break;

	case(MODE_CTR):


		i = 0;
		while (i < len) {

			if (len-i <= BLOCK_SIZE-self->count) {

				for(j=0; j<(len-i); j++) {
					assert(i+j < len);
					assert(self->count+j < BLOCK_SIZE);
					buffer[i+j] = (self->IV[self->count+j] ^= str[i+j]);
				}
				self->count += len-i;
				i = len;
				continue;
			}


			for(j=0; j<BLOCK_SIZE-self->count; j++) {
				assert(i+j < len);
				assert(self->count+j < BLOCK_SIZE);
				buffer[i+j] = (self->IV[self->count+j] ^= str[i+j]);
			}
			i += BLOCK_SIZE-self->count;
			self->count = BLOCK_SIZE;


			if (self->counter_shortcut) {


				PCT_CounterObject *ctr = (PCT_CounterObject *)(self->counter);
				if (ctr->carry && !ctr->allow_wraparound) {
					Py_BLOCK_THREADS;
					PyErr_SetString(PyExc_OverflowError,
							"counter wrapped without allow_wraparound");
					free(buffer);
					return NULL;
				}
				if (ctr->buf_size != BLOCK_SIZE) {
					Py_BLOCK_THREADS;
					PyErr_Format(PyExc_TypeError,
						     "CTR counter function returned "
						     "string of length %zi, not %i",
						     ctr->buf_size, BLOCK_SIZE);
					free(buffer);
					return NULL;
				}
				block_encrypt(&(self->st),
					      (unsigned char *)ctr->val,
					      self->IV);
				ctr->inc_func(ctr);
			} else {
				PyObject *ctr;
				Py_BLOCK_THREADS;
				ctr = PyObject_CallObject(self->counter, NULL);
				if (ctr == NULL) {
					free(buffer);
					return NULL;
				}
				if (!PyBytes_Check(ctr))
				{
					PyErr_SetString(PyExc_TypeError,
							"CTR counter function didn't return a bytestring");
					Py_DECREF(ctr);
					free(buffer);
					return NULL;
				}
				if (PyBytes_Size(ctr) != BLOCK_SIZE) {
					PyErr_Format(PyExc_TypeError,
						     "CTR counter function returned "
						     "bytestring not of length %i",
						     BLOCK_SIZE);
					Py_DECREF(ctr);
					free(buffer);
					return NULL;
				}
				Py_UNBLOCK_THREADS;
				block_encrypt(&(self->st), (unsigned char *)PyBytes_AsString(ctr),
					      self->IV);
				Py_BLOCK_THREADS;
				Py_DECREF(ctr);
				Py_UNBLOCK_THREADS;
			}


			self->count = 0;
		}
		break;

	default:
		Py_BLOCK_THREADS;
		PyErr_Format(PyExc_SystemError,
			     "Unknown ciphertext feedback mode %i; "
			     "this shouldn't happen",
			     self->mode);
		free(buffer);
		return NULL;
	}
	Py_END_ALLOW_THREADS;
	result=PyBytes_FromStringAndSize((char *) buffer, len);
	free(buffer);
	return(result);
}
