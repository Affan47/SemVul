toCBuffer2(OutBuffer *buf, HdrGenState *hgs, int mod)
{
    if (mod != this->mod)
    {   toCBuffer3(buf, hgs, mod);
        return;
    }

    functionToCBuffer2((TypeFunction *)next, buf, hgs, mod, "delegate");
}
