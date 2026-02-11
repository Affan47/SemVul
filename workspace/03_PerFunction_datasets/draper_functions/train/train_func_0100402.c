upd_4color_rgb(gx_device *pdev, gx_color_index color, gx_color_value prgb[3])
{
   const upd_p     upd = ((upd_device *)pdev)->upd;


   prgb[0] = upd_expand(upd,1,color);
   prgb[1] = upd_expand(upd,2,color);
   prgb[2] = upd_expand(upd,3,color);


   if(!(prgb[0] || prgb[1] || prgb[2]))
      prgb[0] = prgb[1] = prgb[2] = upd_expand(upd,0,color);

#if UPD_MESSAGES & UPD_M_MAPCALLS
   errprintf(pdev->memory,
    "4color_rgb: 0x%0*lx -> (%5.1f,%5.1f,%5.1f,%5.1f) -> (%5.1f,%5.1f,%5.1f)\n",
    (pdev->color_info.depth + 3)>>2,color,
    255.0 * (double) ((color >> upd->cmap[1].bitshf) & upd->cmap[1].bitmsk)
                     / (double) upd->cmap[1].bitmsk,
    255.0 * (double) ((color >> upd->cmap[2].bitshf) & upd->cmap[2].bitmsk)
                     / (double) upd->cmap[2].bitmsk,
    255.0 * (double) ((color >> upd->cmap[3].bitshf) & upd->cmap[3].bitmsk)
                     / (double) upd->cmap[3].bitmsk,
    255.0 * (double) ((color >> upd->cmap[0].bitshf) & upd->cmap[0].bitmsk)
                     / (double) upd->cmap[0].bitmsk,
    255.0 * (double) prgb[0] / (double) gx_max_color_value,
    255.0 * (double) prgb[1] / (double) gx_max_color_value,
    255.0 * (double) prgb[2] / (double) gx_max_color_value);
#endif

   return 0;
}
