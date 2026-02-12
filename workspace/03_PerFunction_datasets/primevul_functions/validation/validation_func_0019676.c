ScanLineInputFile::Data::Data (int numThreads):
        partNumber(-1),
        memoryMapped(false)
{


    lineBuffers.resize (max (1, 2 * numThreads));
}
