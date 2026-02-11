_dxfSimplifiedStarNormals(Face *sface, Vertex *svert, Vertex *snor,
			       float *sarea, float *scomp, Vertex simpvert,
			       u_short first_face, u_short last_face)


{
  register u_short i,i1;
  register u_char j,k;

  static VertexD triVert[3];
  static double n[4];


  CopyType2Type(float, double, simpvert, triVert[0], 3);

  for(i=first_face, i1=0; i < last_face; i++, i1++)
    {
      double sum_lengths_sq = 0.0;


      u_short v1  = sface[i][1],
              v2  = sface[i][2];


      CopyType2Type(float, double, svert[v1], triVert[1], 3);

      CopyType2Type(float, double, svert[v2], triVert[2], 3);


      _dxfTriangleNormalQR2D(triVert, n);


      CopyType2Type(double, float, n, snor[i1], 3);

      sarea[i1] = n[3];


       for(j=0;j<3;j++)
	 {
	   double len_edg_sq = 0, tmp;

	   for(k=0;k<3;k++)
	     {
	       tmp         = triVert[(j+1)%3][k] - triVert[j][k];
	       len_edg_sq += tmp * tmp;
	     }

	   sum_lengths_sq += len_edg_sq;

	 }

       scomp[i1] = FOUR_SQRT_3 * sarea[i1] / sum_lengths_sq;

    }

  return;
}
