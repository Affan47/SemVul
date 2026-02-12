void Dispatcher::OSC_put( const Parser::OSC_Put *act )
{
  assert( act->char_present );
  if ( OSC_string.size() < 256 ) {
    OSC_string.push_back( act->ch );
    act->handled = true;
  }
}
