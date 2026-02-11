ConvertToInterpolationCoefficients(double *c, long DataLength, double *z, long NbPoles,	double Tolerance) {
	double	Lambda = 1;
	long	n, k;


	if(DataLength == 1L) {
		return;
	}

	for(k = 0L; k < NbPoles; k++) {
		Lambda = Lambda * (1.0 - z[k]) * (1.0 - 1.0 / z[k]);
	}

	for (n = 0L; n < DataLength; n++) {
		c[n] *= Lambda;
	}

	for (k = 0L; k < NbPoles; k++) {

		c[0] = InitialCausalCoefficient(c, DataLength, z[k], Tolerance);

		for (n = 1L; n < DataLength; n++) {
			c[n] += z[k] * c[n - 1L];
		}

		c[DataLength - 1L] = InitialAntiCausalCoefficient(c, DataLength, z[k]);

		for (n = DataLength - 2L; 0 <= n; n--) {
			c[n] = z[k] * (c[n + 1L] - c[n]);
		}
	}
}
