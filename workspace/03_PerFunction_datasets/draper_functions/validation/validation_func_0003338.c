RenderOverlay(vtkViewport *viewport)
{
  int renderedSomething=0;
  if ( this->RightAxisVisibility )
    {
    renderedSomething = this->RightAxis->RenderOverlay(viewport);
    }
  if ( this->TopAxisVisibility )
    {
    renderedSomething += this->TopAxis->RenderOverlay(viewport);
    }
  if ( this->LeftAxisVisibility )
    {
    renderedSomething += this->LeftAxis->RenderOverlay(viewport);
    }
  if ( this->BottomAxisVisibility )
    {
    renderedSomething += this->BottomAxis->RenderOverlay(viewport);
    }
  if ( this->LegendVisibility )
    {
    renderedSomething += this->LegendActor->RenderOverlay(viewport);
    renderedSomething += this->LabelActors[0]->RenderOverlay(viewport);
    renderedSomething += this->LabelActors[1]->RenderOverlay(viewport);
    renderedSomething += this->LabelActors[2]->RenderOverlay(viewport);
    renderedSomething += this->LabelActors[3]->RenderOverlay(viewport);
    renderedSomething += this->LabelActors[4]->RenderOverlay(viewport);
    renderedSomething += this->LabelActors[5]->RenderOverlay(viewport);
    }

  return renderedSomething;
}
