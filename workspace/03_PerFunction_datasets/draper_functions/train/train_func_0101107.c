FindEdge(vtkIdType endpoint1, vtkIdType endpoint2) {
    if (endpoint1 > endpoint2) std::swap(endpoint1, endpoint2);
    MapType::iterator iter = Map.find(std::make_pair(endpoint1, endpoint2));
    if (iter != Map.end())
      {
      return iter->second;
      }
    else
      {
      return -1;
      }
  }
