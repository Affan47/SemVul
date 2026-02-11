hashcode() const
{
    int l = length();
    const char *d = data();
    if (!l)
	return 0;
    else if (l == 1)
	return d[0] | (d[0] << 8);
    else if (l < 4)
	return d[0] + (d[1] << 3) + (l << 12);
    else
	return d[0] + (d[1] << 8) + (d[2] << 16) + (d[3] << 24)
	    + (l << 12) + (d[l-1] << 10);
}
