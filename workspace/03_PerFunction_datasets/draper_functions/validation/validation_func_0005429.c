Highlight(int highlight)
{
  if ( highlight )
    {
    this->SliderActor->SetProperty(this->SelectedProperty);
    }
  else
    {
    this->SliderActor->SetProperty(this->SliderProperty);
    }
}
