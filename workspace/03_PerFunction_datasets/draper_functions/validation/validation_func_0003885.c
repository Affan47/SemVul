Keyak_ProcessForget(Keccak_ParallelDuplexInstances* duplex)
{
    unsigned int rhoInBytes = (duplex->rate-4)/8;
    unsigned int i;

    Keccak_ParallelDuplexingAll(duplex, 0x01);
    for(i=0; i<NumberOfParallelInstances; i++)
        Keccak_ParallelDuplexingOverwriteWithZeroes(duplex, i, rhoInBytes);
    Keccak_ParallelDuplexingAll(duplex, 0x01);
}
