TiffImage::TiffImage(BasicIo::AutoPtr io, bool )
        : Image(ImageType::tiff, mdExif | mdIptc | mdXmp, io),
          pixelWidth_(0), pixelHeight_(0)
    {
    }
