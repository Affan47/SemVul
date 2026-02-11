ecdh_free( ecdh_context *ctx )
{
    if( ctx == NULL )
        return;

    ecp_group_free( &ctx->grp );
    mpi_free      ( &ctx->d   );
    ecp_point_free( &ctx->Q   );
    ecp_point_free( &ctx->Qp  );
    mpi_free      ( &ctx->z   );
    ecp_point_free( &ctx->Vi  );
    ecp_point_free( &ctx->Vf  );
    mpi_free      ( &ctx->_d  );
}
