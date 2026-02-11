WriteGridTransform(
  ostream &outfile, vtkGridTransform *transform)
{

  if (transform->GetInverseFlag())
    {
    outfile << "Invert_Flag = True;\n";
    }


  std::vector<std::string> xfmpath;
  vtksys::SystemTools::SplitPath(this->FileName, xfmpath);
  if (xfmpath.size() < 1)
    {
    vtkErrorMacro("Can't split filename " << this->FileName);
    return 0;
    }


  size_t i = xfmpath.size() - 1;
  std::string filename =
    vtksys::SystemTools::GetFilenameWithoutLastExtension(xfmpath[i]);
  filename.append("_grid.mnc");
  xfmpath[i] = filename;


  outfile << "Displacement_Volume = " << filename << ";\n";


  vtkMINCImageWriter *writer = vtkMINCImageWriter::New();
  writer->SetFileName(vtksys::SystemTools::JoinPath(xfmpath).c_str());
  writer->SetInput(transform->GetDisplacementGrid());
  if (transform->GetDisplacementShift() != 0.0 ||
      transform->GetDisplacementScale() != 1.0)
    {
    writer->SetRescaleIntercept(transform->GetDisplacementShift());
    writer->SetRescaleSlope(transform->GetDisplacementScale());
    }


  writer->Write();
  writer->Delete();

  return 1;
}
