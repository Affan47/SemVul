RegenerateOverview( GDALRasterBandShadow *srcBand,
                          GDALRasterBandShadow *overviewBand,
                          const char *resampling = "average",
                          GDALProgressFunc callback=NULL,
                          void* callback_data=NULL) {

    CPLErrorReset();

    return GDALRegenerateOverviews( srcBand, 1, &overviewBand,
    	   			    resampling ? resampling : "average", callback, callback_data );
}
