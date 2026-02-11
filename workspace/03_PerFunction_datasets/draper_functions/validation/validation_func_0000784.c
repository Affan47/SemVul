dfb_gfxcard_calc_buffer_size( CoreGraphicsDevice *device,
                              CoreSurfaceBuffer  *buffer,
                              int                *ret_pitch,
                              int                *ret_length )
{
     int          pitch;
     int          length;
     CoreSurface *surface;

     D_ASSERT( device != NULL );
     D_MAGIC_ASSERT( buffer, CoreSurfaceBuffer );

     surface = buffer->surface;
     D_MAGIC_ASSERT( surface, CoreSurface );


     pitch = MAX( surface->config.size.w, surface->config.min_size.w );

     if (pitch < device->limits.surface_max_power_of_two_pixelpitch &&
         surface->config.size.h < device->limits.surface_max_power_of_two_height)
          pitch = 1 << direct_log2( pitch );

     if (device->limits.surface_pixelpitch_alignment > 1) {
          pitch += device->limits.surface_pixelpitch_alignment - 1;
          pitch -= pitch % device->limits.surface_pixelpitch_alignment;
     }

     pitch = DFB_BYTES_PER_LINE( buffer->format, pitch );

     if (pitch < device->limits.surface_max_power_of_two_bytepitch &&
         surface->config.size.h < device->limits.surface_max_power_of_two_height)
          pitch = 1 << direct_log2( pitch );

     if (device->limits.surface_bytepitch_alignment > 1) {
          pitch += device->limits.surface_bytepitch_alignment - 1;
          pitch -= pitch % device->limits.surface_bytepitch_alignment;
     }

     length = DFB_PLANE_MULTIPLY( buffer->format,
                                  MAX( surface->config.size.h, surface->config.min_size.h ) * pitch );


     length += 16;

     if (device->limits.surface_byteoffset_alignment > 1) {
          length += device->limits.surface_byteoffset_alignment - 1;
          length -= length % device->limits.surface_byteoffset_alignment;
     }

     if (ret_pitch)
          *ret_pitch = pitch;

     if (ret_length)
          *ret_length = length;
}
