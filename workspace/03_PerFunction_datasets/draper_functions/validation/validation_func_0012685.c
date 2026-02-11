vector_argmax_float (float* v,size_t n)
{
	size_t i,j = 0;
	float x = v[0];
	for (i=1;i<n;i++)
		if (x < v[i]) { x = v[i]; j = i; }
	return j;
}
