_dxf_MAKE_PROJECTION_MATRIX (int projection, float width,
					 float aspect, float Near, float Far,
					 register float M[4][4])
{


  ENTRY(("_dxf_MAKE_PROJECTION_MATRIX (%d, %f, %f, %f, %f, 0x%x)",
	 projection, width, aspect, Near, Far, M));

  Far = -Far ;
  Near = -Near ;

  M[0][0]=1/(width/2) ; M[0][1]=0 ;              M[0][2]=0 ; M[0][3]=0 ;
  M[1][0]=0 ;           M[1][1]=M[0][0]/aspect ; M[1][2]=0 ; M[1][3]=0 ;
  M[2][0]=0 ;           M[2][1]=0 ;
  M[3][0]=0 ;           M[3][1]=0 ;

  if (projection)
    {

      M[2][2] =  1 - (2*Far) / (Far-Near) ;
      M[3][2] = (2*Far*Near) / (Far-Near) ;
      M[2][3] = -1 ;
      M[3][3] =  0 ;
    }
  else
    {

      M[2][2] = 1 / ((Far-Near) / 2) ;
      M[3][2] = -Near*M[2][2] - 1 ;
      M[2][3] = 0 ;
      M[3][3] = 1 ;
    }

  MPRINT(M);
  EXIT((""));
}
