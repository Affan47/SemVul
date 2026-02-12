int ReadJpegSections (FILE * infile, ReadMode_t ReadMode)
{
    int a;
    int HaveCom = FALSE;

    a = fgetc(infile);

    if (a != 0xff || fgetc(infile) != M_SOI){
        return FALSE;
    }

    ImageInfo.JfifHeader.XDensity = ImageInfo.JfifHeader.YDensity = 300;
    ImageInfo.JfifHeader.ResolutionUnits = 1;

    for(;;){
        int itemlen;
        int prev;
        int marker = 0;
        int ll,lh, got;
        uchar * Data;

        CheckSectionsAllocated();

        prev = 0;
        for (a=0;;a++){
            marker = fgetc(infile);
            if (marker != 0xff && prev == 0xff) break;
            if (marker == EOF){
                ErrFatal("Unexpected end of file");
            }
            prev = marker;
        }

        if (a > 10){
            ErrNonfatal("Extraneous %d padding bytes before section %02X",a-1,marker);
        }

        Sections[SectionsRead].Type = marker;


        lh = fgetc(infile);
        ll = fgetc(infile);
        if (lh == EOF || ll == EOF){
            ErrFatal("Unexpected end of file");
        }

        itemlen = (lh << 8) | ll;

        if (itemlen < 2){
            ErrFatal("invalid marker");
        }

        Sections[SectionsRead].Size = itemlen;


        Data = (uchar *)malloc(itemlen+20);
        if (Data == NULL){
            ErrFatal("Could not allocate memory");
        }
        Sections[SectionsRead].Data = Data;


        Data[0] = (uchar)lh;
        Data[1] = (uchar)ll;

        got = fread(Data+2, 1, itemlen-2, infile);
        if (got != itemlen-2){
            ErrFatal("Premature end of file?");
        }
        SectionsRead += 1;

        switch(marker){

            case M_SOS:

                if (ReadMode & READ_IMAGE){
                    int cp, ep, size;

                    cp = ftell(infile);
                    fseek(infile, 0, SEEK_END);
                    ep = ftell(infile);
                    fseek(infile, cp, SEEK_SET);

                    size = ep-cp;
                    Data = (uchar *)malloc(size);
                    if (Data == NULL){
                        ErrFatal("could not allocate data for entire image");
                    }

                    got = fread(Data, 1, size, infile);
                    if (got != size){
                        ErrFatal("could not read the rest of the image");
                    }

                    CheckSectionsAllocated();
                    Sections[SectionsRead].Data = Data;
                    Sections[SectionsRead].Size = size;
                    Sections[SectionsRead].Type = PSEUDO_IMAGE_MARKER;
                    SectionsRead ++;
                    HaveAll = 1;
                }
                return TRUE;

            case M_DQT:

                process_DQT(Data, itemlen);
                break;

            case M_DHT:

                process_DHT(Data, itemlen);
                break;


            case M_EOI:
                fprintf(stderr,"No image in jpeg!\n");
                return FALSE;

            case M_COM:
                if (HaveCom || ((ReadMode & READ_METADATA) == 0)){

                    free(Sections[--SectionsRead].Data);
                }else{
                    process_COM(Data, itemlen);
                    HaveCom = TRUE;
                }
                break;

            case M_JFIF:


                if (itemlen < 16){
                    fprintf(stderr,"Jfif header too short\n");
                    goto ignore;
                }
                if (memcmp(Data+2, "JFIF\0",5)){
                    fprintf(stderr,"Header missing JFIF marker\n");
                }

                ImageInfo.JfifHeader.Present = TRUE;
                ImageInfo.JfifHeader.ResolutionUnits = Data[9];
                ImageInfo.JfifHeader.XDensity = (Data[10]<<8) | Data[11];
                ImageInfo.JfifHeader.YDensity = (Data[12]<<8) | Data[13];
                if (ShowTags){
                    printf("JFIF SOI marker: Units: %d ",ImageInfo.JfifHeader.ResolutionUnits);
                    switch(ImageInfo.JfifHeader.ResolutionUnits){
                        case 0: printf("(aspect ratio)"); break;
                        case 1: printf("(dots per inch)"); break;
                        case 2: printf("(dots per cm)"); break;
                        default: printf("(unknown)"); break;
                    }
                    printf("  X-density=%d Y-density=%d\n",ImageInfo.JfifHeader.XDensity, ImageInfo.JfifHeader.YDensity);

                    if (Data[14] || Data[15]){
                        fprintf(stderr,"Ignoring jfif header thumbnail\n");
                    }
                }

                ignore:

                free(Sections[--SectionsRead].Data);
                break;

            case M_EXIF:

                if (ReadMode & READ_METADATA){
                    if (memcmp(Data+2, "Exif", 4) == 0){
                        process_EXIF(Data, itemlen);
                        break;
                    }else if (memcmp(Data+2, "http:", 5) == 0){
                        Sections[SectionsRead-1].Type = M_XMP;
                        if (ShowTags){
                            printf("Image contains XMP section, %d bytes long\n", itemlen);
                            if (ShowTags){
                                ShowXmp(Sections[SectionsRead-1]);
                            }
                        }
                        break;
                    }
                }

                free(Sections[--SectionsRead].Data);
                break;

            case M_IPTC:
                if (ReadMode & READ_METADATA){
                    if (ShowTags){
                        printf("Image contains IPTC section, %d bytes long\n", itemlen);
                    }


                }else{
                    free(Sections[--SectionsRead].Data);
                }
                break;

            case M_SOF0:
            case M_SOF1:
            case M_SOF2:
            case M_SOF3:
            case M_SOF5:
            case M_SOF6:
            case M_SOF7:
            case M_SOF9:
            case M_SOF10:
            case M_SOF11:
            case M_SOF13:
            case M_SOF14:
            case M_SOF15:
                if (itemlen < 8){
                    fprintf(stderr,"Section too short\n");
                    break;
                }
                process_SOFn(Data, marker);
                break;
            default:

                if (ShowTags){
                    printf("Jpeg section marker 0x%02x size %d\n",marker, itemlen);
                }
                break;
        }
    }
    return TRUE;
}
