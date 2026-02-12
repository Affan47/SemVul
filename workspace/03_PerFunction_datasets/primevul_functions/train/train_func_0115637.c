Image::UniquePtr newPsdInstance(BasicIo::UniquePtr io, bool )
    {
        Image::UniquePtr image(new PsdImage(std::move(io)));
        if (!image->good())
        {
            image.reset();
        }
        return image;
    }
