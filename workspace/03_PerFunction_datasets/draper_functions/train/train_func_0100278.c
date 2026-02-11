GetBounds()
{
  if (this->ImageActor)
    {


    this->UpdateImageActor();
    return this->ImageActor->GetBounds();
    }

  return NULL;
}
