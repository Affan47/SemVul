newTileBufferTask
    (TaskGroup *group,
     InputStreamMutex *streamData,
     TiledInputFile::Data *ifd,
     int number,
     int dx, int dy,
     int lx, int ly)
{


    TileBuffer *tileBuffer = ifd->getTileBuffer (number);

    try
    {
	tileBuffer->wait();

	tileBuffer->dx = dx;
	tileBuffer->dy = dy;
	tileBuffer->lx = lx;
	tileBuffer->ly = ly;

	tileBuffer->uncompressedData = 0;

	readTileData (streamData, ifd, dx, dy, lx, ly,
		      tileBuffer->buffer,
		      tileBuffer->dataSize);
    }
    catch (...)
    {


	tileBuffer->post();
	throw;
    }

    return new TileBufferTask (group, ifd, tileBuffer);
}
