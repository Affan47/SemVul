create_buf(double floor, long lookahead)
{
    sample_type *buf = (sample_type *) malloc(lookahead * sizeof(sample_type));
    int i;

    for (i = 0; i < lookahead; i++) buf[i] = (sample_type) floor;
    return buf;
}
