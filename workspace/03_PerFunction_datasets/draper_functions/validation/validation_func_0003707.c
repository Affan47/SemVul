CharSize(FT_Face* face, unsigned int pointSize, unsigned int xRes, unsigned int yRes)
{
    if(size != pointSize || xResolution != xRes || yResolution != yRes)
    {
        err = FT_Set_Char_Size(*face, 0L, pointSize * 64, xResolution, yResolution);

        if(!err)
        {
            ftFace = face;
            size = pointSize;
            xResolution = xRes;
            yResolution = yRes;
            ftSize = (*ftFace)->size;
        }
    }

    return !err;
}
