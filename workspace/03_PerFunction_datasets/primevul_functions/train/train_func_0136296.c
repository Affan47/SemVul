Image::AutoPtr ImageFactory::create(int type,
                                        BasicIo::AutoPtr io)
    {

        const Registry* r = find(registry, type);
        if (0 != r) {
            return r->newInstance_(io, true);
        }
        return Image::AutoPtr();
    }
