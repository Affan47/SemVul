append(double *x, double *y, int count)
{
    int newSize = ((d_count + count) / 1000 + 1 ) * 1000;
    if (newSize > size()) {
        d_x.resize(newSize);
        d_y.resize(newSize);
    }

    for (register int i = 0; i < count; i++) {
        d_x[d_count + i] = x[i];
        d_y[d_count + i] = y[i];
    }
    d_count += count;
}
