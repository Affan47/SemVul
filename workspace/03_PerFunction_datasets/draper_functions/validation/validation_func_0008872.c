SetDataArraySelectionSetsFromVariables()
{
  int numPointArrays = (this->NumberOfScalarsPerNode +
                        this->NumberOfVectorsPerNode +
                        this->NumberOfTensorsSymmPerNode +
                        this->NumberOfScalarsPerMeasuredNode +
                        this->NumberOfVectorsPerMeasuredNode +
                        this->NumberOfComplexScalarsPerNode +
                        this->NumberOfComplexVectorsPerNode);
  int numCellArrays = (this->NumberOfScalarsPerElement +
                       this->NumberOfVectorsPerElement +
                       this->NumberOfTensorsSymmPerElement +
                       this->NumberOfComplexScalarsPerElement +
                       this->NumberOfComplexVectorsPerElement);

  char** pointNames = this->CreateStringArray(numPointArrays);
  char** cellNames = this->CreateStringArray(numCellArrays);
  int pointArrayCount = 0;
  int cellArrayCount = 0;

  int i;
  for(i=0; i < this->NumberOfVariables; ++i)
    {
    switch (this->VariableTypes[i])
      {
      case vtkEnSightReader::SCALAR_PER_NODE:
      case vtkEnSightReader::VECTOR_PER_NODE:
      case vtkEnSightReader::TENSOR_SYMM_PER_NODE:
      case vtkEnSightReader::SCALAR_PER_MEASURED_NODE:
      case vtkEnSightReader::VECTOR_PER_MEASURED_NODE:
        pointNames[pointArrayCount] =
          new char[strlen(this->VariableDescriptions[i])+1];
        strcpy(pointNames[pointArrayCount], this->VariableDescriptions[i]);
        ++pointArrayCount;
        break;
      case vtkEnSightReader::SCALAR_PER_ELEMENT:
      case vtkEnSightReader::VECTOR_PER_ELEMENT:
      case vtkEnSightReader::TENSOR_SYMM_PER_ELEMENT:
        cellNames[cellArrayCount] =
          new char[strlen(this->VariableDescriptions[i])+1];
        strcpy(cellNames[cellArrayCount], this->VariableDescriptions[i]);
        ++cellArrayCount;
        break;
      }
    }
  for(i=0; i < this->NumberOfComplexVariables; ++i)
    {
    switch(this->ComplexVariableTypes[i])
      {
      case vtkEnSightReader::COMPLEX_SCALAR_PER_NODE:
      case vtkEnSightReader::COMPLEX_VECTOR_PER_NODE:
        pointNames[pointArrayCount] =
          new char[strlen(this->ComplexVariableDescriptions[i])+1];
        strcpy(pointNames[pointArrayCount],
               this->ComplexVariableDescriptions[i]);
        ++pointArrayCount;
        break;
      case vtkEnSightReader::COMPLEX_SCALAR_PER_ELEMENT:
      case vtkEnSightReader::COMPLEX_VECTOR_PER_ELEMENT:
        cellNames[cellArrayCount] =
          new char[strlen(this->ComplexVariableDescriptions[i])+1];
        strcpy(cellNames[cellArrayCount],
               this->ComplexVariableDescriptions[i]);
        ++cellArrayCount;
        break;
      }
    }

  this->PointDataArraySelection->SetArraysWithDefault(pointNames,
                                                      numPointArrays,
                                                      this->ReadAllVariables);
  this->CellDataArraySelection->SetArraysWithDefault(cellNames,
                                                     numCellArrays,
                                                     this->ReadAllVariables);
  this->DestroyStringArray(numPointArrays, pointNames);
  this->DestroyStringArray(numCellArrays, cellNames);
}
