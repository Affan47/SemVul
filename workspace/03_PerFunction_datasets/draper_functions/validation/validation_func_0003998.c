fast_sqrt(int n)
{
	int guess = n / 4;
	int result = -1;
	int oldguess = -1, oldresult = -1;
	do {
		oldguess = guess;
		oldresult = result;

		result = n / guess;
		guess = (guess + result) / 2;
	} while (guess != result && (oldguess != guess && oldresult != result));

	return result;
}
