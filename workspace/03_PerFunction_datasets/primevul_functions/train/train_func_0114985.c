RafImage::RafImage(BasicIo::UniquePtr io, bool )
        : Image(ImageType::raf, mdExif | mdIptc | mdXmp, std::move(io))
    {
    }
