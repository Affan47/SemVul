static void set_default_parameters(opj_decompress_parameters* parameters)
{
    if (parameters) {
        memset(parameters, 0, sizeof(opj_decompress_parameters));


        parameters->decod_format = -1;
        parameters->cod_format = -1;


        opj_set_default_decoder_parameters(&(parameters->core));
    }
}
