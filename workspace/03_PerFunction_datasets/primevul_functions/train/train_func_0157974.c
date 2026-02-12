fill4 (unsigned short data[], int n)
{
    for (int i = 0; i < n; ++i)
	data[i] = i & USHRT_MAX;
}
