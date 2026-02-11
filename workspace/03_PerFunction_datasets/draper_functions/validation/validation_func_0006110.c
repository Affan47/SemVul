x264_frame_delete( x264_frame_t *frame )
{


    if( !frame->b_duplicate )
    {
        for( int i = 0; i < 4; i++ )
        {
            x264_free( frame->buffer[i] );
            x264_free( frame->buffer_fld[i] );
        }
        for( int i = 0; i < 4; i++ )
            x264_free( frame->buffer_lowres[i] );
        for( int i = 0; i < X264_BFRAME_MAX+2; i++ )
            for( int j = 0; j < X264_BFRAME_MAX+2; j++ )
                x264_free( frame->i_row_satds[i][j] );
        for( int j = 0; j < 2; j++ )
            for( int i = 0; i <= X264_BFRAME_MAX; i++ )
            {
                x264_free( frame->lowres_mvs[j][i] );
                x264_free( frame->lowres_mv_costs[j][i] );
            }
        x264_free( frame->i_propagate_cost );
        for( int j = 0; j <= X264_BFRAME_MAX+1; j++ )
            for( int i = 0; i <= X264_BFRAME_MAX+1; i++ )
                x264_free( frame->lowres_costs[j][i] );
        x264_free( frame->f_qp_offset );
        x264_free( frame->f_qp_offset_aq );
        x264_free( frame->i_inv_qscale_factor );
        x264_free( frame->i_row_bits );
        x264_free( frame->f_row_qp );
        x264_free( frame->f_row_qscale );
        x264_free( frame->field );
        x264_free( frame->mb_type );
        x264_free( frame->mb_partition );
        x264_free( frame->mv[0] );
        x264_free( frame->mv[1] );
        if( frame->mv16x16 )
            x264_free( frame->mv16x16-1 );
        x264_free( frame->ref[0] );
        x264_free( frame->ref[1] );
        x264_pthread_mutex_destroy( &frame->mutex );
        x264_pthread_cond_destroy( &frame->cv );
    }
    x264_free( frame );
}
