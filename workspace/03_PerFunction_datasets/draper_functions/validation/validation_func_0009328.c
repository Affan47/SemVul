_dxfPositionVertexLSConstraints2(Plane *star_plane, u_short star_val, Vertex simplified_vertex)


{
  int retval = 1;

  double
    A1[SIMPLIFY_VALENCE_MAX4],
    A2[SIMPLIFY_VALENCE_MAX4],
    B [SIMPLIFY_VALENCE_MAX4];

  register int i;


  double


    delta =
    star_plane[star_val][3] *
    star_plane[star_val][2];


  for (i = 0; i < star_val; i++)
    {
      A1[i] = star_plane[i][0];
      A2[i] = star_plane[i][1];
      B [i] = delta * star_plane[i][2] - star_plane[i][3] ;
    }


  A1[star_val    ] = 1;
  A1[star_val + 1] = 0;
  A2[star_val    ] = 0;
  A2[star_val + 1] = 1;
  B[star_val     ] =
    B[star_val+1] = 0.;

  {

    static double a,b,c,d,e,x,y;

    for (a=b=c=d=e=0.,i=0;i<star_val+2 ;i++)
      {
	a += A1[i] * A1[i];
	b += A1[i] * A2[i];
	c += A2[i] * A2[i];
	d += A1[i] * B [i];
	e += A2[i] * B [i];
      }


    _dxfSolveSymmetric2x2Eqn(a,b,c,d,e, &x, &y);

    simplified_vertex[0] = (float)  x;

    simplified_vertex[1] = (float)  y;

    simplified_vertex[2] = (float) -delta;

  }

  return retval;
}
