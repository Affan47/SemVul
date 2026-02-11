vtkXMLWriterC_NewDataArray(const char* method, const char* name, int dataType,
                           void* data, vtkIdType numTuples, int numComponents)
{

  vtkSmartPointer<vtkDataArray> array =
    vtkDataArray::CreateDataArray(dataType);
  if(array)
    {
    array->Delete();
    }
  if(!array || array->GetDataType() != dataType)
    {
    vtkGenericWarningMacro("vtkXMLWriterC_" << method
                           << " could not allocate array of type "
                           << dataType << ".");
    return 0;
    }


  array->SetNumberOfComponents(numComponents);


  array->SetName(name);


  array->SetVoidArray(data, numTuples*numComponents, 1);


  return array;
}
