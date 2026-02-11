GMT_shore_path_shift2old (double *lon, double *lat, GMT_LONG n, double west, double east)
{
	GMT_LONG i;


	for (i = 0; i < n; i++) if (lon[i] > east && (lon[i]-360.0) >= west) lon[i] -= 360.0;
}
