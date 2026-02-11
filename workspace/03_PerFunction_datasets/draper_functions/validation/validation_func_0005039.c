sinfo_print_mx(
    Matrix    M,
    const char *    name
)
{
    int    i, j ;

    fprintf(stdout, "# sinfo_eclipse_matrix %s is [%d x %d]\n",
        name, M->nr, M->nc) ;
    for (j=0 ; j<M->nr ; j++) {
        for (i=0 ; i<M->nc ; i++) {
            fprintf(stdout, "%g\t", M->m[i+j*M->nc]) ;
        }
        fprintf(stdout, "\n") ;
    }
    fprintf(stdout, "\n") ;
}
