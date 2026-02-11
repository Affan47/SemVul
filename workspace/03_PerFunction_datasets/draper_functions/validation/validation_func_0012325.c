InstantiateNewItem(int itemType)
  {
  vtkvmtkNeighborhood* newItem;

  switch(itemType)
    {
    case VTK_VMTK_EMPTY_NEIGHBORHOOD:
      newItem = vtkvmtkEmptyNeighborhood::New();
      break;
    case VTK_VMTK_POLYDATA_NEIGHBORHOOD:
      newItem = vtkvmtkPolyDataNeighborhood::New();
      break;
    case VTK_VMTK_POLYDATA_MANIFOLD_NEIGHBORHOOD:
      newItem = vtkvmtkPolyDataManifoldNeighborhood::New();
      break;
    case VTK_VMTK_POLYDATA_MANIFOLD_EXTENDED_NEIGHBORHOOD:
      newItem = vtkvmtkPolyDataManifoldExtendedNeighborhood::New();
      break;
    case VTK_VMTK_UNSTRUCTUREDGRID_NEIGHBORHOOD:
      newItem = vtkvmtkUnstructuredGridNeighborhood::New();
      break;
    default:
      vtkErrorMacro(<<"Invalid neighborhood type");
      return NULL;
    }

  newItem->SetReallocateOnBuild(this->ReallocateOnBuild);

  newItem->Register(this);
  newItem->Delete();

  return newItem;
  }
