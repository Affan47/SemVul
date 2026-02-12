void Image::printStructure(std::ostream&, PrintStructureOption,int )
    {
        throw Error(kerUnsupportedImageType, io_->path());
    }
