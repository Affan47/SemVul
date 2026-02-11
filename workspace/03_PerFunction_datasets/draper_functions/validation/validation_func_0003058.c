dfb_clipboard_set( DFBClipboardCore *core,
                   const char       *mime_type,
                   const void       *data,
                   unsigned int      size,
                   struct timeval   *timestamp )
{
     DFBClipboardCoreShared *shared;

     char *new_mime;
     void *new_data;

     D_MAGIC_ASSERT( core, DFBClipboardCore );
     D_ASSERT( mime_type != NULL );
     D_ASSERT( data != NULL );
     D_ASSERT( size > 0 );

     shared = core->shared;

     D_MAGIC_ASSERT( shared, DFBClipboardCoreShared );

     new_mime = SHSTRDUP( shared->shmpool, mime_type );
     if (!new_mime)
          return D_OOSHM();

     new_data = SHMALLOC( shared->shmpool, size );
     if (!new_data) {
          SHFREE( shared->shmpool, new_mime );
          return D_OOSHM();
     }

     direct_memcpy( new_data, data, size );

     if (fusion_skirmish_prevail( &shared->lock )) {
          SHFREE( shared->shmpool, new_data );
          SHFREE( shared->shmpool, new_mime );
          return DFB_FUSION;
     }

     if (shared->data)
          SHFREE( shared->shmpool, shared->data );

     if (shared->mime_type)
          SHFREE( shared->shmpool, shared->mime_type );

     shared->mime_type = new_mime;
     shared->data      = new_data;
     shared->size      = size;

     gettimeofday( &shared->timestamp, NULL );

     if (timestamp)
          *timestamp = shared->timestamp;

     fusion_skirmish_dismiss( &shared->lock );

     return DFB_OK;
}
