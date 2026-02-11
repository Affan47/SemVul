ftglue_free( FT_Memory   memory,
             FT_Pointer  block )
{
  if ( block )
    memory->free( memory, block );
}
