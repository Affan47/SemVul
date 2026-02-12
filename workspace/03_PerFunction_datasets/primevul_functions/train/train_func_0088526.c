void rom_transaction_begin(void)
{
    Rom *rom;


    QTAILQ_FOREACH(rom, &roms, next) {
        rom->committed = true;
    }
}
