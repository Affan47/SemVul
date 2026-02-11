dfb_gfxcard_state_release( CardState *state )
{
     D_ASSERT( card != NULL );
     D_ASSERT( card->shared != NULL );
     D_MAGIC_ASSERT( state, CardState );
     D_ASSERT( state->destination != NULL );


     if (card->funcs.EmitCommands)
          card->funcs.EmitCommands( card->driver_data, card->device_data );


#if FIXME_SC_2
     if (card->funcs.GetSerial) {
          card->funcs.GetSerial( card->driver_data, card->device_data, &state->serial );

          state->destination->back_buffer->video.serial = state->serial;
     }
#endif


     dfb_gfxcard_unlock();


     dfb_surface_unlock_buffer( state->destination, &state->dst );


     if (state->flags & CSF_SOURCE_LOCKED) {
          dfb_surface_unlock_buffer( state->source, &state->src );

          state->flags &= ~CSF_SOURCE_LOCKED;
     }


     if (state->flags & CSF_SOURCE_MASK_LOCKED) {
          dfb_surface_unlock_buffer( state->source_mask, &state->src_mask );

          state->flags &= ~CSF_SOURCE_MASK_LOCKED;
     }
}
