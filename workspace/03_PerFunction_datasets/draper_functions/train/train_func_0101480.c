refreshRenderer()
{
  if ( modelInfo->dimension == ECIF_ND ) {
    return;
  }

  Renderer* renderer = theControlCenter->getRenderer();

  if ( renderer != NULL && renderer->isVisible() )
    renderer->refresh();
}
