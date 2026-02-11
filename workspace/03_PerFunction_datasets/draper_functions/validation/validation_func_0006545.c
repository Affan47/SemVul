saveg_write8(byte value)
{
    if (fwrite(&value, 1, 1, save_stream) < 1)
    {
        if (!savegame_error)
        {
            fprintf(stderr, "saveg_write8: Error while writing save game\n");

            savegame_error = true;
        }
    }
}
