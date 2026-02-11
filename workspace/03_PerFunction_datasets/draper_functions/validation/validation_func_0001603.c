WriteCoordinatesAppendedData(vtkDataArray* xc, vtkDataArray* yc,
                                                vtkDataArray* zc, int timestep,
                                                OffsetsManagerGroup *coordManager)
{

  if(xc && yc && zc)
    {
    vtkDataArray* oxc = this->CreateExactCoordinates(xc, 0);
    vtkDataArray* oyc = this->CreateExactCoordinates(yc, 1);
    vtkDataArray* ozc = this->CreateExactCoordinates(zc, 2);


    vtkIdType total = (oxc->GetNumberOfTuples()+
                       oyc->GetNumberOfTuples()+
                       ozc->GetNumberOfTuples());
    if(total == 0)
      {
      total = 1;
      }
    float fractions[4] =
      {
        0,
        float(oxc->GetNumberOfTuples()) / total,
        float(oxc->GetNumberOfTuples()+oyc->GetNumberOfTuples()) / total,
        1
      };
    float progressRange[2] = {0,0};
    this->GetProgressRange(progressRange);


    vtkDataArray *allcoords[3];
    allcoords[0] = oxc;
    allcoords[1] = oyc;
    allcoords[2] = ozc;

    for(int i=0; i<3; ++i)
      {
      this->SetProgressRange(progressRange, i, fractions);
      unsigned long mtime = allcoords[i]->GetMTime();

      unsigned long &coordMTime = coordManager->GetElement(i).GetLastMTime();
      if( coordMTime != mtime )
        {
        coordMTime = mtime;
        this->WriteArrayAppendedData(allcoords[i],
          coordManager->GetElement(i).GetPosition(timestep),
          coordManager->GetElement(i).GetOffsetValue(timestep));
        if (this->ErrorCode != vtkErrorCode::NoError)
          {
          oxc->Delete();
          oyc->Delete();
          ozc->Delete();
          return;
          }
        }
      else
        {
        }
      }

    oxc->Delete();
    oyc->Delete();
    ozc->Delete();
    }
}
