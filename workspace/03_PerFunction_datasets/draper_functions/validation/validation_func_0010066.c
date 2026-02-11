ecp_copy( ecp_point *P, const ecp_point *Q )
{
    int ret;

    MPI_CHK( mpi_copy( &P->X, &Q->X ) );
    MPI_CHK( mpi_copy( &P->Y, &Q->Y ) );
    MPI_CHK( mpi_copy( &P->Z, &Q->Z ) );

cleanup:
    return( ret );
}
