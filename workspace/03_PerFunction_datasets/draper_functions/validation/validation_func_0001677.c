ReadPointDataArray(int ncFD,
                                                                int varId)
{

  int numDims;
  CALL_NETCDF(nc_inq_varndims(ncFD, varId, &numDims));
  if (numDims > 2)
    {
    vtkErrorMacro(<< "Sanity check failed.  "
                  << "Encountered array with too many dimensions.");
    return 0;
    }
  if (numDims < 1)
    {
    vtkErrorMacro(<< "Sanity check failed.  "
                  << "Encountered array no dimensions.");
    return 0;
    }
  int dimIds[2];
  CALL_NETCDF(nc_inq_vardimid(ncFD, varId, dimIds));
  size_t numCoords;
  CALL_NETCDF(nc_inq_dimlen(ncFD, dimIds[0], &numCoords));
  size_t numComponents = 1;
  if (numDims > 1)
    {
    CALL_NETCDF(nc_inq_dimlen(ncFD, dimIds[1], &numComponents));
    }


  nc_type ncType;
  CALL_NETCDF(nc_inq_vartype(ncFD, varId, &ncType));
  int vtkType = NetCDFTypeToVTKType(ncType);
  if (vtkType < 1) return 0;
  vtkSmartPointer<vtkDataArray> dataArray;
  dataArray.TakeReference(vtkDataArray::CreateDataArray(vtkType));
  dataArray->SetNumberOfComponents(static_cast<int>(numComponents));
  dataArray->SetNumberOfTuples(static_cast<vtkIdType>(numCoords));


  size_t start[2], count[2];
  start[0] = start[1] = 0;
  count[0] = numCoords;  count[1] = numComponents;
  CALL_NETCDF(nc_get_vars(ncFD, varId, start, count, NULL,
                          dataArray->GetVoidPointer(0)));

  return dataArray;
}
