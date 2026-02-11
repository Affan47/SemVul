run (const cmplx &in, cmplx &out) {
	ibuffer[pointer] = in.real();
	qbuffer[pointer] = in.imag();
	counter++;
	if (counter == decimateratio)
		out = cmplx (	mac(&ibuffer[pointer - length], ifilter, length),
						mac(&qbuffer[pointer - length], qfilter, length) );
	pointer++;
	if (pointer == FIRBufferLen) {

		memmove (ibuffer, ibuffer + FIRBufferLen - length, length * sizeof (double) );
		memmove (qbuffer, qbuffer + FIRBufferLen - length, length * sizeof (double) );
		pointer = length;
	}
	if (counter == decimateratio) {
		counter = 0;
		return 1;
	}
	return 0;
}
