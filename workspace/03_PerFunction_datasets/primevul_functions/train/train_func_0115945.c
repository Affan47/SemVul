MrwImage::MrwImage(BasicIo::UniquePtr io, bool )
        : Image(ImageType::mrw, mdExif | mdIptc | mdXmp, std::move(io))
    {
    }
