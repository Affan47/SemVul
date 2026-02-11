ComputeRange(double inRange[2],
                                  double outRange[2],
                                  int vtkNotUsed(inNumTicks),
                                  int &numTicks,
                                  double &interval)
{

  double sRange[2];
  if ( inRange[0] < inRange[1] )
    {
    sRange[0] = inRange[0];
    sRange[1] = inRange[1];
    }
  else if ( inRange[0] > inRange[1] )
    {
    sRange[1] = inRange[0];
    sRange[0] = inRange[1];
    }
  else
    {
    double perturb = 100.;
    if (inRange[0] == 0.0)
      {
      sRange[0] = -1/perturb;
      sRange[1] = 1/perturb;
      }
    else
      {
      sRange[0] = inRange[0] - inRange[0]/perturb;
      sRange[1] = inRange[0] + inRange[0]/perturb;
      }
    }

  double root;
  numTicks = vtkAxisActor2DComputeTicks(sRange, interval, root);


  if (fabs(sRange[0]/root - floor(sRange[0]/root)) < 0.01)
    {
    outRange[0] = sRange[0];
    outRange[1] = outRange[0] + (numTicks-1.0)*interval;
    }
  else
    {


    outRange[0] = floor(sRange[0]/root)*root;
    if (outRange[0]+(numTicks-1.0)*interval <= sRange[1])
      {
      outRange[1] = outRange[0] + (numTicks-1.0)*interval;
      }
    else
      {


      sRange[0] = outRange[0];
      numTicks = vtkAxisActor2DComputeTicks(sRange, interval, root);
      outRange[1] = outRange[0] + (numTicks-1.0)*interval;
      }
    }


  if ( inRange[0] > inRange[1] )
    {
    sRange[0] = outRange[1];
    outRange[1] = outRange[0];
    outRange[0] = sRange[0];
    interval = -interval;
    }

}
