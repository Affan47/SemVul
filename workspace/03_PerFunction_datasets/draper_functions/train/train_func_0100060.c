UpdateLookup()
{
  if (!this->Lookup)
    {
    this->Lookup = new vtkStringArrayLookup();
    this->Lookup->SortedArray = vtkStringArray::New();
    this->Lookup->IndexArray = vtkIdList::New();
    }
  if (this->Lookup->Rebuild)
    {
    int numComps = this->GetNumberOfComponents();
    vtkIdType numTuples = this->GetNumberOfTuples();
    this->Lookup->SortedArray->Initialize();
    this->Lookup->SortedArray->SetNumberOfComponents(numComps);
    this->Lookup->SortedArray->SetNumberOfTuples(numTuples);
    this->Lookup->IndexArray->SetNumberOfIds(numComps*numTuples);
    std::vector<std::pair<vtkStdString, vtkIdType> > v;
    for (vtkIdType i = 0; i < numComps*numTuples; i++)
      {
      v.push_back(std::pair<vtkStdString, vtkIdType>(this->Array[i], i));
      }
    std::sort(v.begin(), v.end());
    for (vtkIdType i = 0; i < numComps*numTuples; i++)
      {
      this->Lookup->SortedArray->SetValue(i, v[i].first);
      this->Lookup->IndexArray->SetId(i, v[i].second);
      }
    this->Lookup->Rebuild = false;
    this->Lookup->CachedUpdates.clear();
    }
}
