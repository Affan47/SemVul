inline const char *GetDirA(int index)
    {
	char *ptr = dirTableA[index];
	if (!ptr) {

	    ptr = szLocalBufferA;
	    ptr[0] = 'A' + index;
	    ptr[1] = ':';
	    ptr[2] = '\\';
	    ptr[3] = 0;
	}
	return ptr;
    };
