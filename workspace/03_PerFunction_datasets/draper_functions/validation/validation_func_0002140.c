Initialise(const vector<Real>& X, const vector<Complex>& Y)
{
    int i, k;
    Real sig;
    Complex p;
    Complex *u;

    D2 = new Complex[n];
    u = new Complex[n];
    D2[0] = 0.0;
    u[0] = 0.0;
    for (i=1; i<n-1; i++)
    {


	sig = (X[i]-X[i-1]) / (X[i+1]-X[i-1]);
	p = sig * D2[i-1] + Real(2);
	D2[i] = (sig - Real(1)) / p;
	u[i] = (Real(6)*((Y[i+1]-Y[i]) / (X[i+1]-X[i]) -
		     (Y[i]-Y[i-1]) / (X[i]-X[i-1])) / (X[i+1]-X[i-1]) -
		sig*u[i-1]) / p;
    }
    D2[n-1] = 0.0;
    for (k=n-2; k>=0; k--)
    {

	D2[k] = D2[k]*D2[k+1] + u[k];
    }
    delete[] u;
}
