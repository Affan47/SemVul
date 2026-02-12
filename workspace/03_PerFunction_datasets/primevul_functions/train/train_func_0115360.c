Image::UniquePtr ImageFactory::open(const std::string& path, bool useCurl)
    {
        Image::UniquePtr image = open(ImageFactory::createIo(path, useCurl));
        if (image.get() == 0)
            throw Error(kerFileContainsUnknownImageType, path);
        return image;
    }
