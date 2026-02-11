opal_convertor_pack( opal_convertor_t* pConv,
                             struct iovec* iov, uint32_t* out_size,
                             size_t* max_data )
{
    OPAL_CONVERTOR_SET_STATUS_BEFORE_PACK_UNPACK( pConv, iov, out_size, max_data );

    if( OPAL_LIKELY(pConv->flags & CONVERTOR_NO_OP) ) {


        uint32_t i;
        unsigned char* base_pointer;
        size_t pending_length = pConv->local_size - pConv->bConverted;

        *max_data = pending_length;
        opal_convertor_get_current_pointer( pConv, (void**)&base_pointer );

        for( i = 0; i < *out_size; i++ ) {
            if( iov[i].iov_len >= pending_length ) {
                goto complete_contiguous_data_pack;
            }
            if( OPAL_LIKELY(NULL == iov[i].iov_base) )
                iov[i].iov_base = (IOVBASE_TYPE *) base_pointer;
            else
#if OPAL_CUDA_SUPPORT
                MEMCPY_CUDA( iov[i].iov_base, base_pointer, iov[i].iov_len, pConv );
#else
                MEMCPY( iov[i].iov_base, base_pointer, iov[i].iov_len );
#endif
            pending_length -= iov[i].iov_len;
            base_pointer += iov[i].iov_len;
        }
        *max_data -= pending_length;
        pConv->bConverted += (*max_data);
        return 0;

complete_contiguous_data_pack:
        iov[i].iov_len = pending_length;
        if( OPAL_LIKELY(NULL == iov[i].iov_base) )
            iov[i].iov_base = (IOVBASE_TYPE *) base_pointer;
        else
#if OPAL_CUDA_SUPPORT
            MEMCPY_CUDA( iov[i].iov_base, base_pointer, iov[i].iov_len, pConv );
#else
            MEMCPY( iov[i].iov_base, base_pointer, iov[i].iov_len );
#endif
        pConv->bConverted = pConv->local_size;
        *out_size = i + 1;
        pConv->flags |= CONVERTOR_COMPLETED;
        return 1;
    }

    return pConv->fAdvance( pConv, iov, out_size, max_data );
}
