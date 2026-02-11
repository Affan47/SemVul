AddEventsToInteractor(vtkRenderWindowInteractor *i,
                                                     vtkCallbackCommand *command,
                                                     float priority)
{
  EventMapIterator iter = this->EventMap->begin();
  for ( ; iter != this->EventMap->end(); ++iter )
    {
    i->AddObserver((*iter).first, command, priority);
    }
}
