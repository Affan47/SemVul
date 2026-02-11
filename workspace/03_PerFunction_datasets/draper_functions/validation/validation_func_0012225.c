GetColorInterpretation()

{
    AIGDataset	*poODS = (AIGDataset *) poDS;

    if( poODS->poCT != NULL )
        return GCI_PaletteIndex;
    else
        return GDALPamRasterBand::GetColorInterpretation();
}
