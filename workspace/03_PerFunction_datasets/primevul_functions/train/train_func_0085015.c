static void CheckMergedImageAlpha(const PSDInfo *psd_info,Image *image)
{


  if (((psd_info->mode == GrayscaleMode) && (psd_info->channels > 1)) ||
      ((psd_info->mode == RGBMode) && (psd_info->channels > 3)) ||
      ((psd_info->mode == CMYKMode) && (psd_info->channels > 4)))
    image->alpha_trait=BlendPixelTrait;
}
