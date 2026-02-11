sum_proper_divisors(int n) {
	int sum = 0;
	int i;
	for (i = 1; i < n; i++) {
		if (n % i == 0) {
			sum += i;
		}
	}
	return sum;
}
