dfb_state_init( CardState *state, CoreDFB *core )
{
     D_ASSERT( state != NULL );

     memset( state, 0, sizeof(CardState) );

     state->core           = core;
     state->fusion_id      = fusion_id( dfb_core_world(core) );
     state->modified       = SMF_ALL;
     state->src_blend      = DSBF_SRCALPHA;
     state->dst_blend      = DSBF_INVSRCALPHA;
     state->render_options = dfb_config->render_options;

     state->matrix[0] = 0x10000;
     state->matrix[1] = 0x00000;
     state->matrix[2] = 0x00000;
     state->matrix[3] = 0x00000;
     state->matrix[4] = 0x10000;
     state->matrix[5] = 0x00000;
     state->matrix[6] = 0x00000;
     state->matrix[7] = 0x00000;
     state->matrix[8] = 0x10000;
     state->affine_matrix = DFB_TRUE;

     state->from      = CSBR_FRONT;
     state->to        = CSBR_BACK;

     direct_util_recursive_pthread_mutex_init( &state->lock );

     direct_serial_init( &state->dst_serial );
     direct_serial_init( &state->src_serial );
     direct_serial_init( &state->src_mask_serial );

     D_MAGIC_SET( state, CardState );

     return 0;
}
