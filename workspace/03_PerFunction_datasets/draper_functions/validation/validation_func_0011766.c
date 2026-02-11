main()
{
    F<long double> rng(2.0,3.0);
    rng.seed((unsigned int)time(0),(unsigned int)time(0));

    long double sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;

    const int N = 10000;

    for (int i=0; i < N; ++i)
    {
        long double x = rng.random();
        sum1 += x;
        sum2 += x*x;
        sum3 += x*x*x;
        sum4 += x*x*x*x;
    }

    cout << "k1 = " << LD_HACK(sum1/N) << endl
         << "k2 = " << LD_HACK(sum2/N) << endl
         << "k3 = " << LD_HACK(sum3/N) << endl
         << "k4 = " << LD_HACK(sum4/N) << endl;

    return 0;
}
