output_report(const char *fmt, ...)
{
    int myrank;

    MPI_Comm_rank(pio_comm_g, &myrank);

    if (myrank == 0) {
        va_list ap;

        va_start(ap, fmt);
        vfprintf(output, fmt, ap);
        va_end(ap);
    }
}
