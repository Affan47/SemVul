ReleaseGraphicsResources(vtkWindow *w)
{
  for (this->ShaderCollectionIterator->InitTraversal();
    !this->ShaderCollectionIterator->IsDoneWithTraversal();
    this->ShaderCollectionIterator->GoToNextItem())
    {
    vtkShader* shader = vtkShader::SafeDownCast(
      this->ShaderCollectionIterator->GetCurrentObject());
    shader->ReleaseGraphicsResources(w);
    }
}
