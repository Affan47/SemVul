UpdateContour()
{
  this->PointPlacer->UpdateInternalState();


  if ( this->Locator->GetMTime() < this->Renderer->GetActiveCamera()->GetMTime())
    {
    this->RebuildLocator = true;
    }

  if ( this->ContourBuildTime > this->PointPlacer->GetMTime())
    {

    return 0;
    }

  unsigned int i;
  for(i=0; i<this->Internal->Nodes.size(); i++)
    {
    this->PointPlacer->
      UpdateWorldPosition( this->Renderer,
                           this->Internal->Nodes[i]->WorldPosition,
                           this->Internal->Nodes[i]->WorldOrientation );
    }

  for(i=0; (i+1)<this->Internal->Nodes.size(); i++)
    {
    this->UpdateLine(i, i+1);
    }

  if ( this->ClosedLoop )
    {
    this->UpdateLine( static_cast<int>(this->Internal->Nodes.size())-1, 0);
    }
  this->BuildLines();
  this->RebuildLocator = true;

  this->ContourBuildTime.Modified();

  return 1;
}
