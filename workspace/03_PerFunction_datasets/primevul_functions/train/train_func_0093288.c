int encode_dc_prg_sa( abitwriter* huffw, short* block )
{

    huffw->write( block[ 0 ], 1 );


    return 0;
}
