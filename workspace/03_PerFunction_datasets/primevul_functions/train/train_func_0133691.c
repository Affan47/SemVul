Image::AutoPtr newPsdInstance(BasicIo::AutoPtr io, bool )
    {
        Image::AutoPtr image(new PsdImage(io));
        if (!image->good())
        {
            image.reset();
        }
        return image;
    }
