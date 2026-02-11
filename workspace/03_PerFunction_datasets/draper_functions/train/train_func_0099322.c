equalizer_get(v29_rx_state_t *s)
{
    int i;
    int p;
    complexf_t z;
    complexf_t z1;


    z = complex_setf(0.0f, 0.0f);
    p = s->eq_step - 1;
    for (i = 0;  i < V29_EQUALIZER_PRE_LEN + 1 + V29_EQUALIZER_POST_LEN;  i++)
    {
        p = (p - 1) & V29_EQUALIZER_MASK;
        z1 = complex_mulf(&s->eq_coeff[i], &s->eq_buf[p]);
        z = complex_addf(&z, &z1);
    }
    return z;
}
