static int stbi__bmp_set_mask_defaults(stbi__bmp_data *info, int compress)
{

   if (compress == 3)
      return 1;

   if (compress == 0) {
      if (info->bpp == 16) {
         info->mr = 31u << 10;
         info->mg = 31u <<  5;
         info->mb = 31u <<  0;
      } else if (info->bpp == 32) {
         info->mr = 0xffu << 16;
         info->mg = 0xffu <<  8;
         info->mb = 0xffu <<  0;
         info->ma = 0xffu << 24;
         info->all_a = 0;
      } else {

         info->mr = info->mg = info->mb = info->ma = 0;
      }
      return 1;
   }
   return 0;
}
