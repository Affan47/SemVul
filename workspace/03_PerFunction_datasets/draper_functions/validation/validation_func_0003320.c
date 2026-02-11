GetHelp(const char* arg)
{
  CommandLineArguments::Internal::CallbacksMap::iterator it
    = this->Internals->Callbacks.find(arg);
  if ( it == this->Internals->Callbacks.end() )
    {
    return 0;
    }


  CommandLineArgumentsCallbackStructure *cs = &(it->second);
  for(;;)
    {
    CommandLineArguments::Internal::CallbacksMap::iterator hit
      = this->Internals->Callbacks.find(cs->Help);
    if ( hit == this->Internals->Callbacks.end() )
      {
      break;
      }
    cs = &(hit->second);
    }
  return cs->Help;
}
