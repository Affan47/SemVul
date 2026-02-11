csevl(const float x, const ColumnVector& cs, const int n)
  {

    float b0 = 0;
    float b1 = 0;
    float b2 = 0;
    const float twox=2*x;

    for(int i=1; i<=n; i++)
      {
	b2=b1;
	b1=b0;
	b0=twox*b1-b2+cs(n+1-i);
      }

    return 0.5*(b0-b2);
  }
