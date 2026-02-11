FillFromDataPointer(int nb, double *ptr)
{
  if (nb <= 0 || !ptr)
    {
    return;
    }

  this->RemoveAllPoints();

  double *inPtr = ptr;

  int i;
  for (i=0; i < nb; i++)
    {
    vtkPiecewiseFunctionNode *node = new vtkPiecewiseFunctionNode;
    node->X  = inPtr[0];
    node->Y  = inPtr[1];
    node->Sharpness = 0.0;
    node->Midpoint  = 0.5;

    this->Internal->Nodes.push_back(node);
    inPtr += 2;
    }

  this->SortAndUpdateRange();
}
