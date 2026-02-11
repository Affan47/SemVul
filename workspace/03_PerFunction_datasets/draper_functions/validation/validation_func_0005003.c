ToValueSelection(
  vtkSelection* input,
  vtkDataObject* data,
  const char* arrayName)
{
  VTK_CREATE(vtkStringArray, names);
  names->InsertNextValue(arrayName);
  return vtkConvertSelection::ToSelectionType(input, data, vtkSelectionNode::VALUES, names);
}
