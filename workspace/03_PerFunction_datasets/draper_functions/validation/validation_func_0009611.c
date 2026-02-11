drawCurrentEstimationToImage( utils::CCanvas *img )
{
	using mrpt::utils::round;

	unsigned int			i, M = mapPDF.particlesCount();
	std::deque<TPose3D>		path;
	unsigned int			imgHeight=0;

	MRPT_START


	currentMetricMapEstimation = mapPDF.getCurrentMostLikelyMetricMap( );

	ASSERT_( currentMetricMapEstimation->m_gridMaps.size()>0 );


	unsigned int	bestPath = 0;
	double			bestPathLik = -1;
	for (i=0;i<M;i++)
	{
		if (mapPDF.getW(i)>bestPathLik)
		{
			bestPathLik = mapPDF.getW(i);
			bestPath = i;
		}
	}


	mapPDF.getPath(0, path);


	bool   alreadyCopiedImage = false;
	{
		CImage *obj = dynamic_cast<CImage*>( img );
		if (obj)
			obj->resize(
				currentMetricMapEstimation->m_gridMaps[0]->getSizeX(),
				currentMetricMapEstimation->m_gridMaps[0]->getSizeY(),
				1,
				true);
	}
	if (!alreadyCopiedImage)
	{
		CImage imgGrid;


		currentMetricMapEstimation->m_gridMaps[0]->getAsImage( imgGrid );

		img->drawImage( 0,0, imgGrid );
		imgHeight = imgGrid.getHeight();
	}

	int		x1=0,x2=0,y1=0,y2=0;
	float	x_min = currentMetricMapEstimation->m_gridMaps[0]->getXMin();
	float	y_min = currentMetricMapEstimation->m_gridMaps[0]->getYMin();
	float   resolution = currentMetricMapEstimation->m_gridMaps[0]->getResolution();


	for (i=0;i<=M;i++)
	{
		if (i!=bestPath || i==M)
		{
			mapPDF.getPath(i==M ? bestPath:i, path);

			size_t	nPoses = path.size();


			x2 = round( ( path[0].x - x_min) / resolution);
			y2 = round( ( path[0].y - y_min) / resolution );


			for (size_t j=0;j<nPoses;j++)
			{

				x1 = x2;
				y1 = y2;


				x2 = round( ( path[j].x - x_min) / resolution );
				y2 = round( ( path[j].y - y_min) / resolution );


				img->line(
					x1, round( (imgHeight-1)-y1 ),
					x2, round( (imgHeight-1)-y2 ),
					i==M ? TColor(0,0,0) : TColor(0x50,0x50,0x50),
					i==M ? 3 : 1
					);
			}
		}
	}

	MRPT_END
}
