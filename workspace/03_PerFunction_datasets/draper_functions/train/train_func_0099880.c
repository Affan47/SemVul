sigframp_dsp(t_sigframp *x, t_signal **sp)
{
    int n = sp[0]->s_n, n2 = (n>>1);
    if (n < 4)
    {
        error("framp: minimum 4 points");
        return;
    }
    dsp_add(sigframp_perform, 5, sp[0]->s_vec, sp[1]->s_vec,
        sp[2]->s_vec, sp[3]->s_vec, n2);
    dsp_add(sigsqrt_perform, 3, sp[3]->s_vec, sp[3]->s_vec, n2);
}
