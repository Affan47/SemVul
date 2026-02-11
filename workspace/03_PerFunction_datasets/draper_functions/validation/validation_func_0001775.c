CloseRNG(const rng rngx, rngcontext * rngctx)
{


    switch (rngx) {
    case RNG_FILE:

        CloseDiceFile(rngctx);

    default:

        ;

    }
}
