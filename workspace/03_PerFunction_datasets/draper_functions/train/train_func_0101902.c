pack( char *& buffer, const VT_MPI_INT & bufferSize,
                          VT_MPI_INT & bufferPos )
{
   DefRec_BaseS::pack( buffer, bufferSize, bufferPos );


   uint32_t creator_length = creator.length();
   CALL_MPI( MPI_Pack( &creator_length, 1, MPI_UNSIGNED, buffer, bufferSize,
                       &bufferPos, MPI_COMM_WORLD ) );


   char * c_creator = new char[creator_length+1];
   vt_assert( c_creator );
   strcpy( c_creator, creator.c_str() );
   CALL_MPI( MPI_Pack( c_creator, creator_length + 1, MPI_CHAR, buffer,
                       bufferSize, &bufferPos, MPI_COMM_WORLD ) );
   delete [] c_creator;
}
