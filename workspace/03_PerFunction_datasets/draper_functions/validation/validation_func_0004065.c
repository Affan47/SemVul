LoadFile(char *filename,NA_Alignment *dataset,int type,int format)
{

    if (DataType != type)
        fprintf(stderr,"Warning, datatypes do not match.\n");


    switch(format)
    {
        case NA_FLAT:
            ReadNA_Flat(filename,(char*)dataset,type);
            ((NA_Alignment*)dataset)->format = GDE;
            break;

        case GENBANK:
            ReadGen(filename,dataset,type);
            ((NA_Alignment*)dataset)->format = GENBANK;
            break;

        case ARBDB:
            ReadArbdb_plain(filename,dataset,type);
            ((NA_Alignment*)dataset)->format = ARBDB;
            break;

        case GDE:
            ReadGDE(filename,dataset,type);
            ((NA_Alignment*)dataset)->format = GDE;
            break;
        case COLORMASK:
            ReadCMask(filename);

        default:
            break;
    }
    return;
}
