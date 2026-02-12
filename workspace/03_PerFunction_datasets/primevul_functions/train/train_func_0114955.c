CrwImage::CrwImage(BasicIo::UniquePtr io, bool )
        : Image(ImageType::crw, mdExif | mdComment, std::move(io))
    {
    }
