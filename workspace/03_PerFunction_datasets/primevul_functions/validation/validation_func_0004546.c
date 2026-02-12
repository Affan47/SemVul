void WriteJpegFile(const char * FileName)
{
    FILE * outfile;
    int a;

    if (!HaveAll){
        ErrFatal("Can't write back - didn't read all");
    }

    outfile = fopen(FileName,"wb");
    if (outfile == NULL){
        ErrFatal("Could not open file for write");
    }


    fputc(0xff,outfile);
    fputc(0xd8,outfile);

    if (Sections[0].Type != M_EXIF && Sections[0].Type != M_JFIF){

        static uchar JfifHead[18] = {
            0xff, M_JFIF,
            0x00, 0x10, 'J' , 'F' , 'I' , 'F' , 0x00, 0x01,
            0x01, 0x01, 0x01, 0x2C, 0x01, 0x2C, 0x00, 0x00
        };

        if (ImageInfo.ResolutionUnit == 2 || ImageInfo.ResolutionUnit == 3){


            ImageInfo.JfifHeader.ResolutionUnits = (char)(ImageInfo.ResolutionUnit-1);

            ImageInfo.JfifHeader.XDensity = (int)ImageInfo.xResolution;
            ImageInfo.JfifHeader.YDensity = (int)ImageInfo.yResolution;
        }

        JfifHead[11] = ImageInfo.JfifHeader.ResolutionUnits;
        JfifHead[12] = (uchar)(ImageInfo.JfifHeader.XDensity >> 8);
        JfifHead[13] = (uchar)ImageInfo.JfifHeader.XDensity;
        JfifHead[14] = (uchar)(ImageInfo.JfifHeader.YDensity >> 8);
        JfifHead[15] = (uchar)ImageInfo.JfifHeader.YDensity;


        fwrite(JfifHead, 18, 1, outfile);


        if (ImageInfo.ResolutionUnit != 0) {

            JfifHead[11] = (uchar)ImageInfo.ResolutionUnit - 1;
        }
        if (ImageInfo.xResolution > 0.0 && ImageInfo.yResolution > 0.0) {
            JfifHead[12] = (uchar)((int)ImageInfo.xResolution>>8);
            JfifHead[13] = (uchar)((int)ImageInfo.xResolution);

            JfifHead[14] = (uchar)((int)ImageInfo.yResolution>>8);
            JfifHead[15] = (uchar)((int)ImageInfo.yResolution);
        }
    }


    for (a=0;a<SectionsRead-1;a++){
        fputc(0xff,outfile);
        fputc((unsigned char)Sections[a].Type, outfile);
        fwrite(Sections[a].Data, Sections[a].Size, 1, outfile);
    }


    fwrite(Sections[a].Data, Sections[a].Size, 1, outfile);

    fclose(outfile);
}
