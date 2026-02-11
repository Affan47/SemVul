AddPoint
  ( int ap1, int ap2, double apercent )
{
  int    p1, p2;
  double percent;

  if ( ap2 < ap1 )
    {
    p1      = ap2;
    p2      = ap1;
    percent = 1.0 - apercent;
    }
  else
    {
    p1      = ap1;
    p2      = ap2;
    percent = apercent;
    }

  int key = GetKey( p1, p2 );


  vtkTableBasedClipperEdgeHashEntry * cur = hashes[ key ];
  while ( cur != NULL )
    {
    if (  cur->IsMatch( p1, p2 )  )
      {


      return cur->GetPointId();
      }

    cur = cur->GetNext();
    }


  vtkTableBasedClipperEdgeHashEntry * new_one = emm.GetFreeEdgeHashEntry();

  int newPt = pointlist.AddPoint( p1, p2, percent );
  new_one->SetInfo( p1, p2, newPt );
  new_one->SetNext(  hashes[ key ]  );
  hashes[key] = new_one;

  return newPt;
}
