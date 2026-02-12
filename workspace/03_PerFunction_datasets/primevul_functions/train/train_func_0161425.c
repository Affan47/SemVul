void Dispatcher::newparamchar( const Parser::Param *act )
{
  assert( act->char_present );
  assert( (act->ch == ';') || ( (act->ch >= '0') && (act->ch <= '9') ) );
  if ( params.length() < 100 ) {

    params.push_back( act->ch );
    act->handled = true;
  }
  parsed = false;
}
