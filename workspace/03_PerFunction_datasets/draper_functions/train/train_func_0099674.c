vtkUpdateFastPathIDsInternal(
  vtkSelection* selection, int piece,
  std::vector<vtkIdType>& ids,
  std::vector<unsigned int>& cids)
{
  if (!selection)
    {
    return true;
    }

  for (unsigned int n = 0; n < selection->GetNumberOfNodes(); n++)
    {
    vtkSelectionNode* node = selection->GetNode(n);
    vtkInformation* selProperties = node->GetProperties();

    if (selProperties->Has(vtkSelectionNode::PROCESS_ID()) &&
      piece != selProperties->Get(vtkSelectionNode::PROCESS_ID()) &&
      selProperties->Get(vtkSelectionNode::PROCESS_ID()) != -1)
      {

      continue;
      }

    unsigned int composite_index = 0;
    if (selProperties->Has(vtkSelectionNode::COMPOSITE_INDEX()))
      {
      composite_index = static_cast<unsigned int>(
        selProperties->Get(vtkSelectionNode::COMPOSITE_INDEX()));
      }

    vtkIdTypeArray* idArray = vtkIdTypeArray::SafeDownCast(
      node->GetSelectionList());
    if (!idArray || idArray->GetNumberOfTuples() == 0)
      {

      continue;
      }

    vtkIdType numValues = idArray->GetNumberOfTuples();
    for (vtkIdType cc=0; cc < numValues; cc++)
      {
      vtkIdType selectedId = idArray->GetValue(cc);
      ids.push_back(selectedId);
      cids.push_back(composite_index);
      }
    }

  return true;
}
