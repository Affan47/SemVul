setTopLeft( off_t offset )
{
  static bool inTopLeft;
  if( inTopLeft ) {

     return;
  }
  inTopLeft = true;
  try {
     if( offset < 0 ) {
	_topLeft = 0;
     } else if( offset > _reader.size() ) {
	_topLeft = _reader.size();
     } else {
	_topLeft = offset;
     }

     _topLeft = (_topLeft/bytesPerLine()) * bytesPerLine();


     const Delta * delta;

     _reader.seek(_topLeft);
     _reader.read(_data,bytesPerPage());


     for( offset = _delta.lower_bound(_topLeft);
	  (offset != -1) && (offset < _topLeft + bytesPerPage());
	  offset = _delta.lower_bound(offset) ) {
	delta = _delta.search(offset);
	_data[offset++-_topLeft] = delta->newData()[0];
     }

     repaint();
     emit topLeftChanged(_topLeft);
  } catch( const exception &e ) {
     inTopLeft = false;
     throw e;
  }
  inTopLeft = false;
}
