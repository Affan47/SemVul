vec_dot_prodf(const float x[], const float y[], int n)
{
    int i;
    float z;
    __m128 n1;
    __m128 n2;
    __m128 n3;
    __m128 n4;

    z = 0.0f;
    if ((i = n & ~3))
    {
        n4 = _mm_setzero_ps();
        for (i -= 4;  i >= 0;  i -= 4)
        {
            n1 = _mm_loadu_ps(x + i);
            n2 = _mm_loadu_ps(y + i);
            n3 = _mm_mul_ps(n1, n2);
            n4 = _mm_add_ps(n4, n3);
        }
        n4 = _mm_add_ps(_mm_movehl_ps(n4, n4), n4);
        n4 = _mm_add_ss(_mm_shuffle_ps(n4, n4, 1), n4);
        _mm_store_ss(&z, n4);
    }

    switch (n & 3)
    {
    case 3:
        z += x[n - 3]*y[n - 3];
    case 2:
        z += x[n - 2]*y[n - 2];
    case 1:
        z += x[n - 1]*y[n - 1];
    }
    return z;
}
