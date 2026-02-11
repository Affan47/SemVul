update(RNG *rng)
{
    double logdensity = -_gv->logFullConditional(_chain);
    double step = exp(_lstep);

    double const *xold = _gv->nodes()[0]->value(_chain);
    unsigned int N = _gv->length();

    double *eps = new double[N];
    DMNorm::randomsample(eps, 0, _var, false, N, rng);
    vector<double> xnew(N);
    for (unsigned int i = 0; i < N; ++i) {
	xnew[i] = xold[i] + eps[i] * step;
    }
    delete [] eps;

    setValue(xnew);
    logdensity += _gv->logFullConditional(_chain);
    accept(rng, exp(logdensity));
}
