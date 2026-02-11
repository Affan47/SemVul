Init(trpgr_Archive *archive, int myLod, double scale, int freeListDivider)
{
    Clean();

    lod = myLod;


    if (scale < 0)  scale = 0.0;

    tileTable = archive->GetTileTable();


    const trpgHeader *head = archive->GetHeader();
    head->GetTileSize(lod,cellSize);
    head->GetLodRange(lod,pageDist);
    head->GetLodSize(lod,lodSize);
    pageDist *= scale;

    head->GetVersion(majorVersion, minorVersion);


    aoiSize.x = (int)(pageDist/cellSize.x);
    aoiSize.y = (int)(pageDist/cellSize.y);


    maxNumTiles = (int)(1.15*(2*aoiSize.x+1)*(2*aoiSize.y+1));
    if(majorVersion == 2 && minorVersion >= 1)
        maxNumTiles = (int)(1.15*(2*aoiSize.x+1)*(2*aoiSize.y+1)/freeListDivider);
    else
        maxNumTiles = (int)(1.15*(2*aoiSize.x+1)*(2*aoiSize.y+1));


    for (int i=0;i<maxNumTiles;i++) {
        trpgManagedTile *tile = new trpgManagedTile();
        freeList.push_back(tile);
    }


    valid = true;

    return true;
}
