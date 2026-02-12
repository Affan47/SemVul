cmsUInt32Number GetInputPixelType(void)
{
     int space, bps, extra, ColorChannels, Flavor;

     lIsITUFax         = IsITUFax(Decompressor.marker_list);
     lIsPhotoshopApp13 = HandlePhotoshopAPP13(Decompressor.marker_list);
     lIsEXIF           = HandleEXIF(&Decompressor);

     ColorChannels = Decompressor.num_components;
     extra  = 0;
     bps    = 1;
     Flavor = 0;

     if (lIsITUFax) {

        space = PT_Lab;
        Decompressor.out_color_space = JCS_YCbCr;
     }
     else
     switch (Decompressor.jpeg_color_space) {

     case JCS_GRAYSCALE:
              space = PT_GRAY;
              Decompressor.out_color_space = JCS_GRAYSCALE;
              break;

     case JCS_RGB:
              space = PT_RGB;
              Decompressor.out_color_space = JCS_RGB;
              break;

     case JCS_YCbCr:
              space = PT_RGB;
              Decompressor.out_color_space = JCS_RGB;
              break;

     case JCS_CMYK:
              space = PT_CMYK;
              Decompressor.out_color_space = JCS_CMYK;
              if (Decompressor.saw_Adobe_marker)
                                Flavor = 1;
              break;

     case JCS_YCCK:
              space = PT_CMYK;
              Decompressor.out_color_space = JCS_CMYK;
              if (Decompressor.saw_Adobe_marker)
                                Flavor = 1;
              break;

     default:
              FatalError("Unsupported color space (0x%x)", Decompressor.jpeg_color_space);
              return 0;
     }

     return (EXTRA_SH(extra)|CHANNELS_SH(ColorChannels)|BYTES_SH(bps)|COLORSPACE_SH(space)|FLAVOR_SH(Flavor));
}
