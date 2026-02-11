RequestData(vtkInformation *vtkNotUsed(request),
                                   vtkInformationVector **inputVector,
                                   vtkInformationVector *outputVector)
{


  vtkPolyData *output = vtkPolyData::GetData(outputVector, 0);

  int numInputs = inputVector[0]->GetNumberOfInformationObjects();
  if (numInputs == 1)
    {
    output->ShallowCopy(vtkPolyData::GetData(inputVector[0], 0));
    return 1;
    }

  vtkPolyData** inputs = new vtkPolyData*[numInputs];
  for (int idx = 0; idx < numInputs; ++idx)
    {
    inputs[idx] = vtkPolyData::GetData(inputVector[0], idx);
    }
  int retVal = this->ExecuteAppend(output, inputs, numInputs);
  delete [] inputs;
  return retVal;
}
