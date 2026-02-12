void CiffHeader::decode(Image& image) const
    {

        if (pRootDir_) pRootDir_->decode(image, byteOrder_);
    }
