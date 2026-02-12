void printIFD(std::ostream& out, PrintStructureOption option, uint64_t dir_offset, int depth)
                {
                    BasicIo& io = Image::io();

                    depth++;
                    bool bFirst  = true;


                    bool bPrint = true;

                    do
                    {

                        io.seek(dir_offset, BasicIo::beg);

                        const uint64_t entries = readData(header_.format() == Header::StandardTiff? 2: 8);
                        const bool tooBig = entries > 500;

                        if ( bFirst && bPrint )
                        {
                            out << Internal::indent(depth) << Internal::stringFormat("STRUCTURE OF BIGTIFF FILE ") << io.path() << std::endl;
                            if (tooBig)
                                out << Internal::indent(depth) << "entries = " << entries << std::endl;
                        }

                        if (tooBig)
                            break;


                        for ( uint64_t i = 0; i < entries; i ++ )
                        {
                            if ( bFirst && bPrint )
                                out << Internal::indent(depth)
                                    << " address |    tag                           |     "
                                    << " type |    count |    offset | value\n";

                            bFirst = false;

                            const uint16_t tag   = (uint16_t) readData(2);
                            const uint16_t type  = (uint16_t) readData(2);
                            const uint64_t count = readData(dataSize_);
                            const DataBuf  data  = io.read(dataSize_);

                            std::string sp = "" ;


                            const uint64_t kount  = isStringType(type)? (count > 32 ? 32 : count)
                                                            : count > 5              ? 5
                                                            : count
                                                            ;
                            const uint32_t pad    = isStringType(type) ? 1 : 0;
                            const uint32_t size   = isStringType(type) ? 1
                                                  : is2ByteType(type)  ? 2
                                                  : is4ByteType(type)  ? 4
                                                  : is8ByteType(type)  ? 8
                                                  : 1;


                			long long allocate = (long long) size*count + pad;
                			if ( allocate > (long long) io.size() ) {
                    			throw Error(57);
                			}

                            DataBuf buf((long)allocate);

                            const uint64_t offset = header_.format() == Header::StandardTiff?
                                    byteSwap4(data, 0, doSwap_):
                                    byteSwap8(data, 0, doSwap_);


                            const bool usePointer = (size_t) count*size > (size_t) dataSize_;

                            if ( usePointer )
                            {
                                size_t   restore = io.tell();
                                io.seek(offset, BasicIo::beg);
                                io.read(buf.pData_, (long) count * size);
                                io.seek(restore, BasicIo::beg);
                            }
                            else
                                std::memcpy(buf.pData_, data.pData_, (size_t) count * size);

                            if ( bPrint )
                            {
                                const uint64_t entrySize = header_.format() == Header::StandardTiff? 12: 20;
                                const uint64_t address = dir_offset + 2 + i * entrySize;
                                const std::string offsetString = usePointer?
                                    Internal::stringFormat("%10u", offset):
                                    "";

                                out << Internal::indent(depth)
                                    << Internal::stringFormat("%8u | %#06x %-25s |%10s |%9u |%10s | ",
                                        address, tag, tagName(tag).c_str(), typeName(type), count, offsetString.c_str());

                                if ( isShortType(type) )
                                {
                                    for ( size_t k = 0 ; k < kount ; k++ )
                                    {
                                        out << sp << byteSwap2(buf, k*size, doSwap_);
                                        sp = " ";
                                    }
                                }
                                else if ( isLongType(type) )
                                {
                                    for ( size_t k = 0 ; k < kount ; k++ )
                                    {
                                        out << sp << byteSwap4(buf, k*size, doSwap_);
                                        sp = " ";
                                    }
                                }
                                else if ( isLongLongType(type) )
                                {
                                    for ( size_t k = 0 ; k < kount ; k++ )
                                    {
                                        out << sp << byteSwap8(buf, k*size, doSwap_);
                                        sp = " ";
                                    }
                                }
                                else if ( isRationalType(type) )
                                {
                                    for ( size_t k = 0 ; k < kount ; k++ )
                                    {
                                        uint32_t a = byteSwap4(buf, k*size+0, doSwap_);
                                        uint32_t b = byteSwap4(buf, k*size+4, doSwap_);
                                        out << sp << a << "/" << b;
                                        sp = " ";
                                    }
                                }
                                else if ( isStringType(type) )
                                    out << sp << Internal::binaryToString(buf, (size_t) kount);

                                sp = kount == count ? "" : " ...";
                                out << sp << std::endl;

                                if ( option == kpsRecursive &&
                                        (tag == 0x8769  || tag == 0x014a || type == tiffIfd || type == tiffIfd8) )
                                {
                                    for ( size_t k = 0 ; k < count ; k++ )
                                    {
                                        const size_t restore = io.tell();
                                        const uint64_t ifdOffset = type == tiffIfd8?
                                            byteSwap8(buf, k*size, doSwap_):
                                            byteSwap4(buf, k*size, doSwap_);

                                        std::cerr << "tag = " << Internal::stringFormat("%#x",tag) << std::endl;
                                        printIFD(out, option, ifdOffset, depth);
                                        io.seek(restore, BasicIo::beg);
                                    }
                                }
                                else if ( option == kpsRecursive && tag == 0x83bb  )
                                {
                                    const size_t restore = io.tell();
                                    io.seek(offset, BasicIo::beg);
                                    byte* bytes=new byte[(size_t)count] ;
                                    io.read(bytes,(long)count)        ;
                                    io.seek(restore, BasicIo::beg);
                                    IptcData::printStructure(out,bytes,(size_t)count,depth);
                                    delete[] bytes;
                                }
                                else if ( option == kpsRecursive && tag == 0x927c  && count > 10)
                                {
                                    size_t   restore = io.tell();

                                    uint32_t jump= 10           ;
                                    byte     bytes[20]          ;
                                    const char* chars = (const char*) &bytes[0] ;
                                    io.seek(dir_offset, BasicIo::beg);
                                    io.read(bytes,jump    )     ;
                                    bytes[jump]=0               ;
                                    if ( ::strcmp("Nikon",chars) == 0 )
                                    {

                                        byte* bytes=new byte[(size_t)count-jump] ;
                                        io.read(bytes,(long)  count-jump)        ;
                                        MemIo memIo(bytes,(long)count-jump)      ;
                                        std::cerr << "Nikon makernote" << std::endl;

                                        delete[] bytes                   ;
                                    }
                                    else
                                    {

                                        io.seek(0, BasicIo::beg);
                                        std::cerr << "makernote" << std::endl;
                                        printIFD(out,option,offset,depth);
                                    }

                                    io.seek(restore,BasicIo::beg);
                                }
                            }
                        }

                        const uint64_t nextDirOffset = readData(dataSize_);

                        dir_offset = tooBig ? 0 : nextDirOffset;
                        out.flush();
                    } while (dir_offset != 0);

                    if ( bPrint )
                        out << Internal::indent(depth) << "END " << io.path() << std::endl;

                    depth--;
                }
