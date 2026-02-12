Image::AutoPtr ImageFactory::open(const std::string& path, bool useCurl)
    {
        Image::AutoPtr image = open(ImageFactory::createIo(path, useCurl));
        if (image.get() == 0) throw Error(11, path);
        return image;
    }
