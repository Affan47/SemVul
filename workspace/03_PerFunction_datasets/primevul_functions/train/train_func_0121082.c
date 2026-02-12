TiledInputFile::readTiles (int dx1, int dx2, int dy1, int dy2, int lx, int ly)
{


    try
    {
        Lock lock (*_data->_streamData);

        if (_data->slices.size() == 0)
            throw IEX_NAMESPACE::ArgExc ("No frame buffer specified "
			       "as pixel data destination.");

        if (!isValidLevel (lx, ly))
            THROW (IEX_NAMESPACE::ArgExc,
                   "Level coordinate "
                   "(" << lx << ", " << ly << ") "
                   "is invalid.");


        if (dx1 > dx2)
            std::swap (dx1, dx2);

        if (dy1 > dy2)
            std::swap (dy1, dy2);

        int dyStart = dy1;
	int dyStop  = dy2 + 1;
	int dY      = 1;

        if (_data->lineOrder == DECREASING_Y)
        {
            dyStart = dy2;
            dyStop  = dy1 - 1;
            dY      = -1;
        }


        {
            TaskGroup taskGroup;
            int tileNumber = 0;

            for (int dy = dyStart; dy != dyStop; dy += dY)
            {
                for (int dx = dx1; dx <= dx2; dx++)
                {
                    if (!isValidTile (dx, dy, lx, ly))
                        THROW (IEX_NAMESPACE::ArgExc,
			       "Tile (" << dx << ", " << dy << ", " <<
			       lx << "," << ly << ") is not a valid tile.");

                    ThreadPool::addGlobalTask (newTileBufferTask (&taskGroup,
                                                                  _data->_streamData,
                                                                  _data,
                                                                  tileNumber++,
                                                                  dx, dy,
                                                                  lx, ly));
                }
            }


        }


	const string *exception = 0;

        for (size_t i = 0; i < _data->tileBuffers.size(); ++i)
	{
            TileBuffer *tileBuffer = _data->tileBuffers[i];

	    if (tileBuffer->hasException && !exception)
		exception = &tileBuffer->exception;

	    tileBuffer->hasException = false;
	}

	if (exception)
	    throw IEX_NAMESPACE::IoExc (*exception);
    }
    catch (IEX_NAMESPACE::BaseExc &e)
    {
        REPLACE_EXC (e, "Error reading pixel data from image "
                     "file \"" << fileName() << "\". " << e.what());
        throw;
    }
}
