run_spiro(const spiro_cp *src, int n)
{
    int nseg = src[0].ty == '{' ? n - 1 : n;
    spiro_seg *s = setup_path(src, n);
    if (nseg > 1)
	solve_spiro(s, nseg);
    return s;
}
