generatePublicKey()
{
    dhCtx* tmpCtx = static_cast<dhCtx*>(ctx);

    bnBegin(&tmpCtx->pubKey);
    switch (pkType) {
    case DH2K:
        bnExpMod(&tmpCtx->pubKey, &two, &tmpCtx->privKey, &bnP2048);
        break;

    case DH3K:
        bnExpMod(&tmpCtx->pubKey, &two, &tmpCtx->privKey, &bnP3072);
        break;

    case EC25:
    case EC38:
    case E255:
    case E414:
        while (!ecdhGeneratePublic(&tmpCtx->curve, &tmpCtx->pubPoint, &tmpCtx->privKey))
            ecGenerateRandomNumber(&tmpCtx->curve, &tmpCtx->privKey);
    }
    return 0;
}
