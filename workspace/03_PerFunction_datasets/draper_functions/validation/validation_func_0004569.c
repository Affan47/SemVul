read_tuning(filename)
char *filename;
{
    int index, pit, lineno = 0;
    float bend;
    FILE *fpp;

    user_scale = TRUE;
    set_pitch_default();

    fpp = fileopen(filename, "tun", "r", "Tuning definition file");
    while ((fscanf(fpp, "%d %d %f\n", &index, &pit, &bend) > 2) &&
    (lineno < 128)) {
    lineno++;
    if (index >= 0 && index <= 127) {
        pit_tab[index].pbend = (int)(8192 * bend/100 + 8192);
        pit_tab[index].ppitch = pit;
    }
    }
}
