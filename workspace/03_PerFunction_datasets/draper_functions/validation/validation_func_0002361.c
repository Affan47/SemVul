write ( tnstream& stream ) const
{
   stream.writeInt( packageDataStreamVersion );
   stream.writeInt( packages.size() );
   for ( Packages::const_iterator i = packages.begin(); i != packages.end(); ++i ) {
      stream.writeString( i->first );
      i->second->write( stream );
   }
}
