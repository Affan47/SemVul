loadColorMap(const c8 *filename, s32 w, s32 h)
{
    video::IVideoDriver* driver = SceneManager->getVideoDriver();
    if(!driver) return;

    video::IImage *image = driver->createImageFromFile(filename);
    if(!image) return;

    s32 tw = image->getDimension().Width;
    s32 th = image->getDimension().Height;

    s32 we = w + tw;
    if(we > Size.Width+1) we = Size.Width+1;
    s32 he = h + th;
    if(he > Size.Height+1) he = Size.Height+1;

    tw = 0;
    th = 0;

    for(s32 j=h; j<he; j++)
    {
        for(s32 i=w; i<we; i++)
        {
            video::SColor color = image->getPixel(tw, th);

            setColor(i,j, color);

            tw++;
        }
        tw = 0;
        th++;
    }

    image->drop();
}
