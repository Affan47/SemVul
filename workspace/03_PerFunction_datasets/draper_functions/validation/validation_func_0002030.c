contour_point_free(Contours contours)
{
	gint i;
	gint j;

	if(!contours.pointscontour) return;
	for(i=0;i<contours.N[0];i++)
	{

		if(contours.pointscontour[i])
		{
			for( j = 0; j<contours.N[1];j++)
			{

				if(contours.pointscontour[i][j].N>0 && contours.pointscontour[i][j].point)
					g_free(contours.pointscontour[i][j].point);
			}
			g_free(contours.pointscontour[i]);
		}
	}
	g_free(contours.pointscontour);

}
