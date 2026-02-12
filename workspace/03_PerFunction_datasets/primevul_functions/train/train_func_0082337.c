int main(int argc, char **argv)
{
    opj_decompress_parameters parameters;

    OPJ_INT32 num_images, imageno;
    img_fol_t img_fol;
    dircnt_t *dirptr = NULL;
    int failed = 0;
    OPJ_FLOAT64 t, tCumulative = 0;
    OPJ_UINT32 numDecompressedImages = 0;
    OPJ_UINT32 cp_reduce;


    set_default_parameters(&parameters);


    memset(&img_fol, 0, sizeof(img_fol_t));


    if (parse_cmdline_decoder(argc, argv, &parameters, &img_fol) == 1) {
        failed = 1;
        goto fin;
    }

    cp_reduce = parameters.core.cp_reduce;
    if (getenv("USE_OPJ_SET_DECODED_RESOLUTION_FACTOR") != NULL) {


        parameters.core.cp_reduce = 0;
    }


    if (img_fol.set_imgdir == 1) {
        int it_image;
        num_images = get_num_images(img_fol.imgdirpath);

        dirptr = (dircnt_t*)malloc(sizeof(dircnt_t));
        if (!dirptr) {
            destroy_parameters(&parameters);
            return EXIT_FAILURE;
        }

        dirptr->filename_buf = (char*)malloc(sizeof(char) *
                                             (size_t)num_images * OPJ_PATH_LEN);
        if (!dirptr->filename_buf) {
            failed = 1;
            goto fin;
        }

        dirptr->filename = (char**) malloc((size_t)num_images * sizeof(char*));

        if (!dirptr->filename) {
            failed = 1;
            goto fin;
        }
        for (it_image = 0; it_image < num_images; it_image++) {
            dirptr->filename[it_image] = dirptr->filename_buf + it_image * OPJ_PATH_LEN;
        }

        if (load_images(dirptr, img_fol.imgdirpath) == 1) {
            failed = 1;
            goto fin;
        }
        if (num_images == 0) {
            fprintf(stderr, "Folder is empty\n");
            failed = 1;
            goto fin;
        }
    } else {
        num_images = 1;
    }


    for (imageno = 0; imageno < num_images ; imageno++)  {
        opj_image_t* image = NULL;
        opj_stream_t *l_stream = NULL;
        opj_codec_t* l_codec = NULL;
        opj_codestream_index_t* cstr_index = NULL;

        if (!parameters.quiet) {
            fprintf(stderr, "\n");
        }

        if (img_fol.set_imgdir == 1) {
            if (get_next_file(imageno, dirptr, &img_fol, &parameters)) {
                fprintf(stderr, "skipping file...\n");
                destroy_parameters(&parameters);
                continue;
            }
        }


        l_stream = opj_stream_create_default_file_stream(parameters.infile, 1);
        if (!l_stream) {
            fprintf(stderr, "ERROR -> failed to create the stream from the file %s\n",
                    parameters.infile);
            failed = 1;
            goto fin;
        }


        switch (parameters.decod_format) {
        case J2K_CFMT: {

            l_codec = opj_create_decompress(OPJ_CODEC_J2K);
            break;
        }
        case JP2_CFMT: {

            l_codec = opj_create_decompress(OPJ_CODEC_JP2);
            break;
        }
        case JPT_CFMT: {

            l_codec = opj_create_decompress(OPJ_CODEC_JPT);
            break;
        }
        default:
            fprintf(stderr, "skipping file..\n");
            destroy_parameters(&parameters);
            opj_stream_destroy(l_stream);
            continue;
        }

        if (parameters.quiet) {

            opj_set_info_handler(l_codec, quiet_callback, 00);
            opj_set_warning_handler(l_codec, quiet_callback, 00);
            opj_set_error_handler(l_codec, quiet_callback, 00);
        } else {

            opj_set_info_handler(l_codec, info_callback, 00);
            opj_set_warning_handler(l_codec, warning_callback, 00);
            opj_set_error_handler(l_codec, error_callback, 00);
        }


        t = opj_clock();


        if (!opj_setup_decoder(l_codec, &(parameters.core))) {
            fprintf(stderr, "ERROR -> opj_decompress: failed to setup the decoder\n");
            opj_stream_destroy(l_stream);
            opj_destroy_codec(l_codec);
            failed = 1;
            goto fin;
        }

        if (parameters.num_threads >= 1 &&
                !opj_codec_set_threads(l_codec, parameters.num_threads)) {
            fprintf(stderr, "ERROR -> opj_decompress: failed to set number of threads\n");
            opj_stream_destroy(l_stream);
            opj_destroy_codec(l_codec);
            failed = 1;
            goto fin;
        }


        if (! opj_read_header(l_stream, l_codec, &image)) {
            fprintf(stderr, "ERROR -> opj_decompress: failed to read the header\n");
            opj_stream_destroy(l_stream);
            opj_destroy_codec(l_codec);
            opj_image_destroy(image);
            failed = 1;
            goto fin;
        }

        if (parameters.numcomps) {
            if (! opj_set_decoded_components(l_codec,
                                             parameters.numcomps,
                                             parameters.comps_indices,
                                             OPJ_FALSE)) {
                fprintf(stderr,
                        "ERROR -> opj_decompress: failed to set the component indices!\n");
                opj_destroy_codec(l_codec);
                opj_stream_destroy(l_stream);
                opj_image_destroy(image);
                failed = 1;
                goto fin;
            }
        }

        if (getenv("USE_OPJ_SET_DECODED_RESOLUTION_FACTOR") != NULL) {


            if (! opj_set_decoded_resolution_factor(l_codec, cp_reduce)) {
                fprintf(stderr,
                        "ERROR -> opj_decompress: failed to set the resolution factor tile!\n");
                opj_destroy_codec(l_codec);
                opj_stream_destroy(l_stream);
                opj_image_destroy(image);
                failed = 1;
                goto fin;
            }
        }

        if (!parameters.nb_tile_to_decode) {
            if (getenv("SKIP_OPJ_SET_DECODE_AREA") != NULL &&
                    parameters.DA_x0 == 0 &&
                    parameters.DA_y0 == 0 &&
                    parameters.DA_x1 == 0 &&
                    parameters.DA_y1 == 0) {


            }

            else if (!opj_set_decode_area(l_codec, image, (OPJ_INT32)parameters.DA_x0,
                                          (OPJ_INT32)parameters.DA_y0, (OPJ_INT32)parameters.DA_x1,
                                          (OPJ_INT32)parameters.DA_y1)) {
                fprintf(stderr, "ERROR -> opj_decompress: failed to set the decoded area\n");
                opj_stream_destroy(l_stream);
                opj_destroy_codec(l_codec);
                opj_image_destroy(image);
                failed = 1;
                goto fin;
            }


            if (!(opj_decode(l_codec, l_stream, image) &&
                    opj_end_decompress(l_codec,   l_stream))) {
                fprintf(stderr, "ERROR -> opj_decompress: failed to decode image!\n");
                opj_destroy_codec(l_codec);
                opj_stream_destroy(l_stream);
                opj_image_destroy(image);
                failed = 1;
                goto fin;
            }
        } else {
            if (!(parameters.DA_x0 == 0 &&
                    parameters.DA_y0 == 0 &&
                    parameters.DA_x1 == 0 &&
                    parameters.DA_y1 == 0)) {
                if (!(parameters.quiet)) {
                    fprintf(stderr, "WARNING: -d option ignored when used together with -t\n");
                }
            }

            if (!opj_get_decoded_tile(l_codec, l_stream, image, parameters.tile_index)) {
                fprintf(stderr, "ERROR -> opj_decompress: failed to decode tile!\n");
                opj_destroy_codec(l_codec);
                opj_stream_destroy(l_stream);
                opj_image_destroy(image);
                failed = 1;
                goto fin;
            }
            if (!(parameters.quiet)) {
                fprintf(stdout, "tile %d is decoded!\n\n", parameters.tile_index);
            }
        }

        tCumulative += opj_clock() - t;
        numDecompressedImages++;


        opj_stream_destroy(l_stream);

        if (image->color_space != OPJ_CLRSPC_SYCC
                && image->numcomps == 3 && image->comps[0].dx == image->comps[0].dy
                && image->comps[1].dx != 1) {
            image->color_space = OPJ_CLRSPC_SYCC;
        } else if (image->numcomps <= 2) {
            image->color_space = OPJ_CLRSPC_GRAY;
        }

        if (image->color_space == OPJ_CLRSPC_SYCC) {
            color_sycc_to_rgb(image);
        } else if ((image->color_space == OPJ_CLRSPC_CMYK) &&
                   (parameters.cod_format != TIF_DFMT)) {
            color_cmyk_to_rgb(image);
        } else if (image->color_space == OPJ_CLRSPC_EYCC) {
            color_esycc_to_rgb(image);
        }

        if (image->icc_profile_buf) {
#if defined(OPJ_HAVE_LIBLCMS1) || defined(OPJ_HAVE_LIBLCMS2)
            if (image->icc_profile_len) {
                color_apply_icc_profile(image);
            } else {
                color_cielab_to_rgb(image);
            }
#endif
            free(image->icc_profile_buf);
            image->icc_profile_buf = NULL;
            image->icc_profile_len = 0;
        }


        if (parameters.precision != NULL) {
            OPJ_UINT32 compno;
            for (compno = 0; compno < image->numcomps; ++compno) {
                OPJ_UINT32 precno = compno;
                OPJ_UINT32 prec;

                if (precno >= parameters.nb_precision) {
                    precno = parameters.nb_precision - 1U;
                }

                prec = parameters.precision[precno].prec;
                if (prec == 0) {
                    prec = image->comps[compno].prec;
                }

                switch (parameters.precision[precno].mode) {
                case OPJ_PREC_MODE_CLIP:
                    clip_component(&(image->comps[compno]), prec);
                    break;
                case OPJ_PREC_MODE_SCALE:
                    scale_component(&(image->comps[compno]), prec);
                    break;
                default:
                    break;
                }

            }
        }


        if (parameters.upsample) {
            image = upsample_image_components(image);
            if (image == NULL) {
                fprintf(stderr,
                        "ERROR -> opj_decompress: failed to upsample image components!\n");
                opj_destroy_codec(l_codec);
                failed = 1;
                goto fin;
            }
        }


        if (parameters.force_rgb) {
            switch (image->color_space) {
            case OPJ_CLRSPC_SRGB:
                break;
            case OPJ_CLRSPC_GRAY:
                image = convert_gray_to_rgb(image);
                break;
            default:
                fprintf(stderr,
                        "ERROR -> opj_decompress: don't know how to convert image to RGB colorspace!\n");
                opj_image_destroy(image);
                image = NULL;
                break;
            }
            if (image == NULL) {
                fprintf(stderr, "ERROR -> opj_decompress: failed to convert to RGB image!\n");
                opj_destroy_codec(l_codec);
                failed = 1;
                goto fin;
            }
        }


        switch (parameters.cod_format) {
        case PXM_DFMT:
            if (imagetopnm(image, parameters.outfile, parameters.split_pnm)) {
                fprintf(stderr, "[ERROR] Outfile %s not generated\n", parameters.outfile);
                failed = 1;
            } else if (!(parameters.quiet)) {
                fprintf(stdout, "[INFO] Generated Outfile %s\n", parameters.outfile);
            }
            break;

        case PGX_DFMT:
            if (imagetopgx(image, parameters.outfile)) {
                fprintf(stderr, "[ERROR] Outfile %s not generated\n", parameters.outfile);
                failed = 1;
            } else if (!(parameters.quiet)) {
                fprintf(stdout, "[INFO] Generated Outfile %s\n", parameters.outfile);
            }
            break;

        case BMP_DFMT:
            if (imagetobmp(image, parameters.outfile)) {
                fprintf(stderr, "[ERROR] Outfile %s not generated\n", parameters.outfile);
                failed = 1;
            } else if (!(parameters.quiet)) {
                fprintf(stdout, "[INFO] Generated Outfile %s\n", parameters.outfile);
            }
            break;
#ifdef OPJ_HAVE_LIBTIFF
        case TIF_DFMT:
            if (imagetotif(image, parameters.outfile)) {
                fprintf(stderr, "[ERROR] Outfile %s not generated\n", parameters.outfile);
                failed = 1;
            } else if (!(parameters.quiet)) {
                fprintf(stdout, "[INFO] Generated Outfile %s\n", parameters.outfile);
            }
            break;
#endif
        case RAW_DFMT:
            if (imagetoraw(image, parameters.outfile)) {
                fprintf(stderr,
                        "[ERROR] Error generating raw or yuv file. Outfile %s not generated\n",
                        parameters.outfile);
                failed = 1;
            } else if (!(parameters.quiet)) {
                fprintf(stdout, "[INFO] Generated Outfile %s\n", parameters.outfile);
            }
            break;

        case RAWL_DFMT:
            if (imagetorawl(image, parameters.outfile)) {
                fprintf(stderr,
                        "[ERROR] Error generating rawl file. Outfile %s not generated\n",
                        parameters.outfile);
                failed = 1;
            } else if (!(parameters.quiet)) {
                fprintf(stdout, "[INFO] Generated Outfile %s\n", parameters.outfile);
            }
            break;

        case TGA_DFMT:
            if (imagetotga(image, parameters.outfile)) {
                fprintf(stderr, "[ERROR] Error generating tga file. Outfile %s not generated\n",
                        parameters.outfile);
                failed = 1;
            } else if (!(parameters.quiet)) {
                fprintf(stdout, "[INFO] Generated Outfile %s\n", parameters.outfile);
            }
            break;
#ifdef OPJ_HAVE_LIBPNG
        case PNG_DFMT:
            if (imagetopng(image, parameters.outfile)) {
                fprintf(stderr, "[ERROR] Error generating png file. Outfile %s not generated\n",
                        parameters.outfile);
                failed = 1;
            } else if (!(parameters.quiet)) {
                fprintf(stdout, "[INFO] Generated Outfile %s\n", parameters.outfile);
            }
            break;
#endif


        default:
            fprintf(stderr, "[ERROR] Outfile %s not generated\n", parameters.outfile);
            failed = 1;
        }


        if (l_codec) {
            opj_destroy_codec(l_codec);
        }


        opj_image_destroy(image);


        opj_destroy_cstr_index(&cstr_index);

        if (failed) {
            (void)remove(parameters.outfile);
        }
    }
fin:
    destroy_parameters(&parameters);
    if (failed && img_fol.imgdirpath) {
        free(img_fol.imgdirpath);
    }
    if (dirptr) {
        if (dirptr->filename) {
            free(dirptr->filename);
        }
        if (dirptr->filename_buf) {
            free(dirptr->filename_buf);
        }
        free(dirptr);
    }
    if (numDecompressedImages && !failed && !(parameters.quiet)) {
        fprintf(stdout, "decode time: %d ms\n",
                (int)((tCumulative * 1000.0) / (OPJ_FLOAT64)numDecompressedImages));
    }
    return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
