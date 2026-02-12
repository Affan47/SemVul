Image::UniquePtr ImageFactory::create(ImageType type, BasicIo::UniquePtr io)
    {

        const Registry* r = find(registry, type);

        if (r == nullptr || type == ImageType::none) {
            return Image::UniquePtr();
        }

        return r->newInstance_(std::move(io), true);
    }
