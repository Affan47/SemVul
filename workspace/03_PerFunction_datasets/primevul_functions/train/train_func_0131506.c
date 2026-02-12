void WriteOutputFields(int OutputColorSpace)
{
    J_COLOR_SPACE in_space, jpeg_space;
    int components;

    switch (OutputColorSpace) {

    case PT_GRAY: in_space = jpeg_space = JCS_GRAYSCALE;
                  components = 1;
                  break;

    case PT_RGB:  in_space = JCS_RGB;
                  jpeg_space = JCS_YCbCr;
                  components = 3;
                  break;

    case PT_YCbCr: in_space = jpeg_space = JCS_YCbCr;
                   components = 3;
                   break;

    case PT_CMYK: in_space = JCS_CMYK;
                  jpeg_space = JCS_YCCK;
                  components = 4;
                  break;

    case PT_Lab:  in_space = jpeg_space = JCS_YCbCr;
                  components = 3;
                  break;
    default:
                 FatalError("Unsupported output color space");
                 return;
    }


    if (jpegQuality >= 100) {


        jpeg_space = in_space;
    }

    Compressor.in_color_space =  in_space;
    Compressor.jpeg_color_space = jpeg_space;
    Compressor.input_components = Compressor.num_components = components;
    jpeg_set_defaults(&Compressor);
    jpeg_set_colorspace(&Compressor, jpeg_space);


    if (OutputColorSpace == PT_CMYK)
        Compressor.write_JFIF_header = 1;


    jpeg_set_quality(&Compressor, jpegQuality, 1);
    if (jpegQuality >= 70) {

      int i;
      for(i=0; i < Compressor.num_components; i++) {

	        Compressor.comp_info[i].h_samp_factor = 1;
            Compressor.comp_info[i].v_samp_factor = 1;
      }

    }

}
