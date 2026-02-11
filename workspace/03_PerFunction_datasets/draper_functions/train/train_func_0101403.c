unused()
{

  for( unsigned i = 0; i < data.size(); i++ )
    if( data[i] == Avail )
      return i;


  unsigned block = data.size();
  resize( data.size()+10 );
  return block;
}
