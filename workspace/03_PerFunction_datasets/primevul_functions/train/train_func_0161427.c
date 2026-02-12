void Dispatcher::collect( const Parser::Collect *act )
{
  assert( act->char_present );
  if ( ( dispatch_chars.length() < 8 )
       && ( act->ch <= 255 ) ) {
    dispatch_chars.push_back( act->ch );
    act->handled = true;
  }
}
