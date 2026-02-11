sampleHighToLow(int upper_end, double ran, double const *pi, int N)
{


    for (int i = upper_end; i >= 0; --i) {
	if (ran <= pi[i]) {
	    return i;
	}
	ran -= pi[i];
    }
    return 0;
}
