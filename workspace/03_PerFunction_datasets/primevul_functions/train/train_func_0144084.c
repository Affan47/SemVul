void JpegBase::printStructure(std::ostream& out, PrintStructureOption option,int depth)
    {
        if (io_->open() != 0) throw Error(9, io_->path(), strError());

        if (!isThisType(*io_, false)) {
            if (io_->error() || io_->eof()) throw Error(14);
            throw Error(15);
        }

        bool bPrint = option==kpsBasic || option==kpsRecursive;
        Exiv2::Uint32Vector iptcDataSegs;

        if ( bPrint || option == kpsXMP || option == kpsIccProfile || option == kpsIptcErase ) {


            std::string nm[256] ;
            nm[0xd8]="SOI"  ;
            nm[0xd9]="EOI"  ;
            nm[0xda]="SOS"  ;
            nm[0xdb]="DQT"  ;
            nm[0xdd]="DRI"  ;
            nm[0xfe]="COM"  ;


            nm[0xc4]="DHT"  ;
            for ( int i = 0 ; i <= 15 ; i++ ) {
                char MN[10];
                sprintf(MN,"APP%d",i);
                nm[0xe0+i] = MN;
                if ( i != 4 ) {
                    sprintf(MN,"SOF%d",i);
                    nm[0xc0+i] = MN;
                }
            }


            bool        bExtXMP    = false;
            long        bufRead    =  0;
            const long  bufMinSize = 36;
            DataBuf     buf(bufMinSize);


            int marker = advanceToMarker();
            if (marker < 0) throw Error(15);

            bool    done = false;
            bool    first= true;
            while (!done) {

                if ( first && bPrint ) {
                    out << "STRUCTURE OF JPEG FILE: " << io_->path() << std::endl;
                    out << " address | marker     | length  | data" << std::endl ;
                    REPORT_MARKER;
                }
                first    = false;
                bool bLF = bPrint;


                std::memset(buf.pData_, 0x0, buf.size_);
                bufRead = io_->read(buf.pData_, bufMinSize);
                if (io_->error()) throw Error(14);
                if (bufRead < 2) throw Error(15);
                uint16_t size = 0;


                if( ( marker >= sof0_ && marker <= sof15_)
                ||  ( marker >= app0_ && marker <= (app0_ | 0x0F))
                ||    marker == dht_
                ||    marker == dqt_
                ||    marker == dri_
                ||    marker == com_
                ||    marker == sos_
                ){
                    size = getUShort(buf.pData_, bigEndian);
                }
                if ( bPrint ) out << Internal::stringFormat(" | %7d ", size);


                if (marker >= app0_ && marker <= (app0_ | 0x0F)) {

                    const char* signature = (const char*) buf.pData_+2;


                    if ( option == kpsXMP && std::string(signature).find("http://ns.adobe.com/x")== 0 ) {

                        if ( size > 0 ) {
                            io_->seek(-bufRead , BasicIo::cur);
                            byte* xmp  = new byte[size+1];
                            io_->read(xmp,size);
                            int start = 0 ;


                            if ( ! bExtXMP ) {
                                while (xmp[start]) start++; start++;
                                if ( ::strstr((char*)xmp+start,"HasExtendedXMP") ) {
                                    start  = size ;
                                    bExtXMP = true;
                                }
                            } else {
                                start = 2+35+32+4+4;
                            }
                            xmp[size]=0;

                            out << xmp + start;
                            delete [] xmp;
                            bufRead = size;
                        }
                    } else if ( option == kpsIccProfile && std::strcmp(signature,"ICC_PROFILE") == 0 ) {

                        if ( size > 0 ) {
                            io_->seek(-bufRead , BasicIo::cur);
                            byte* icc  = new byte[size];
                            io_->read(icc,size);
                            std::size_t start=16;
                            out.write( ((const char*)icc)+start,size-start);
                            bufRead = size;
                            delete [] icc;
                        }
                    } else if ( option == kpsIptcErase && std::strcmp(signature,"Photoshop 3.0") == 0 ) {

                        if ( size > 0 ) {
                            io_->seek(-bufRead , BasicIo::cur);
                            iptcDataSegs.push_back(io_->tell());
                            iptcDataSegs.push_back(size);
                        }
                    } else if ( bPrint ) {
                        out << "| " << Internal::binaryToString(buf,size>32?32:size,size>0?2:0);
                    }


                    bool bFlir = option == kpsRecursive && marker == (app0_+1) && std::strcmp(signature,"FLIR")==0;
                    bool bExif = option == kpsRecursive && marker == (app0_+1) && std::strcmp(signature,"Exif")==0;
                    bool bMPF  = option == kpsRecursive && marker == (app0_+2) && std::strcmp(signature,"MPF")==0;
                    bool bPS   = option == kpsRecursive                        && std::strcmp(signature,"Photoshop 3.0")==0;
                    if( bFlir || bExif || bMPF || bPS ) {

                        if ( size > 0 ) {
                            out << std::endl;


                            byte*    exif      = new byte[size];
                            uint32_t restore   = io_->tell();


                            io_->seek(-bufRead , BasicIo::cur);
                            io_->read(exif,size);
                            uint32_t start     = std::strcmp(signature,"Exif")==0 ? 8 : 6;
                            uint32_t max       = (uint32_t) size -1;


                            if ( bFlir ) {
                                start = 0 ;
                                bFlir = false;
                                while ( start < max ) {
                                    if ( std::strcmp((const char*)(exif+start),"FFF")==0 ) {
                                        bFlir = true ;
                                        break;
                                    }
                                    start++;
                                }
                            }


                            if ( bFlir ) {

                                while ( start < max ) {
                                    if ( exif[start] == 'I' && exif[start+1] == 'I' ) break;
                                    if ( exif[start] == 'M' && exif[start+1] == 'M' ) break;
                                    start++;
                                }
                                if ( start < max ) std::cout << "  FFF start = " << start << std::endl ;

                            }

                            if ( bPS ) {
                                IptcData::printStructure(out,exif,size,depth);
                            } else {

    	                        BasicIo::AutoPtr p = BasicIo::AutoPtr(new MemIo(exif+start,size-start));
        	                    if ( start < max ) TiffImage::printTiffStructure(*p,out,option,depth);
        	                }


                            io_->seek(restore,Exiv2::BasicIo::beg);
                            delete [] exif;
                            bLF    = false;

                        }
                    }
                }


                if (io_->seek(size - bufRead, BasicIo::cur)) throw Error(14);

                if ( bLF ) out << std::endl;

                if (marker == sos_)

                    done = true;
                else {

                    marker = advanceToMarker();
                    REPORT_MARKER;
                    if ( marker == eoi_ ) {
                        if ( option == kpsBasic ) out << std::endl;
                        done = true;
                    }
                }
            }
        }
        if ( option == kpsIptcErase ) {
        	std::cout << "iptc data blocks: " << (iptcDataSegs.size() ? "FOUND" : "none") << std::endl;
        	uint32_t toggle = 0 ;
        	for ( Uint32Vector_i it = iptcDataSegs.begin(); it != iptcDataSegs.end() ; it++ ) {
        		std::cout << *it ;
        		if ( toggle++ % 2 ) std::cout << std::endl; else std::cout << ' ' ;
        	}
        }
    }
