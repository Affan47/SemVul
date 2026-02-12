avifResult avifDecoderNthImage(avifDecoder * decoder, uint32_t frameIndex)
{
    int requestedIndex = (int)frameIndex;
    if (requestedIndex == decoder->imageIndex) {

        return AVIF_RESULT_OK;
    }

    if (requestedIndex == (decoder->imageIndex + 1)) {

        return avifDecoderNextImage(decoder);
    }

    if (requestedIndex >= decoder->imageCount) {

        return AVIF_RESULT_NO_IMAGES_REMAINING;
    }


    decoder->imageIndex = ((int)avifDecoderNearestKeyframe(decoder, frameIndex)) - 1;
    avifDecoderFlush(decoder);
    for (;;) {
        avifResult result = avifDecoderNextImage(decoder);
        if (result != AVIF_RESULT_OK) {
            return result;
        }

        if (requestedIndex == decoder->imageIndex) {
            break;
        }
    }
    return AVIF_RESULT_OK;
}
