Image::AutoPtr newWebPInstance(BasicIo::AutoPtr io, bool )
    {
        Image::AutoPtr image(new WebPImage(io));
        if (!image->good()) {
            image.reset();
        }
        return image;
    }
