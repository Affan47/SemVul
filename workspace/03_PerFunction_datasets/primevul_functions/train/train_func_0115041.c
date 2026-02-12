void Image::printTiffStructure(BasicIo& io, std::ostream& out, Exiv2::PrintStructureOption option,int depth,size_t offset )
    {
        if ( option == kpsBasic || option == kpsXMP || option == kpsRecursive || option == kpsIccProfile ) {

            const size_t dirSize = 32;
            DataBuf  dir(dirSize);


            io.read(dir.pData_,  8);
            char c = (char) dir.pData_[0] ;
            bool bSwap   = ( c == 'M' && isLittleEndianPlatform() )
                        || ( c == 'I' && isBigEndianPlatform()    )
                        ;
            uint32_t start = byteSwap4(dir,4,bSwap);
            printIFDStructure(io,out,option,start+(uint32_t)offset,bSwap,c,depth);
        }
    }
