operator==(vtkEvent *e)
{
  if ( this->EventId != e->EventId )
    {
    return 0;
    }
  if ( this->Modifier != vtkEvent::AnyModifier &&
       e->Modifier != vtkEvent::AnyModifier &&
       this->Modifier != e->Modifier )
    {
    return 0;
    }
  if ( this->KeyCode != '\0' && e->KeyCode != '\0' &&
       this->KeyCode != e->KeyCode )
    {
    return 0;
    }
  if ( this->RepeatCount != 0 && e->RepeatCount != 0 &&
       this->RepeatCount != e->RepeatCount )
    {
    return 0;
    }
  if ( this->KeySym != NULL && e->KeySym != NULL &&
       strcmp(this->KeySym,e->KeySym) != 0 )
    {
    return 0;
    }

  return 1;
}
