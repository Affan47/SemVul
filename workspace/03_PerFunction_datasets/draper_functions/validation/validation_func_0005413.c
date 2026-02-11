blockExit(bool mustNotThrow)
{
    if (mustNotThrow)
        error("asm statements are assumed to throw", toChars());

    return BEfallthru | BEthrow | BEreturn | BEgoto | BEhalt;
}
