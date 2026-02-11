set(struct intel_mipmap_tree *mt,
                        unsigned int level, unsigned int layer)
{


   if (mt->msaa_layout == INTEL_MSAA_LAYOUT_UMS ||
       mt->msaa_layout == INTEL_MSAA_LAYOUT_CMS) {
      assert(layer % mt->num_samples == 0);
   }

   intel_miptree_check_level_layer(mt, level, layer);

   this->mt = mt;
   this->level = level;
   this->layer = layer;
   this->width = mt->level[level].width;
   this->height = mt->level[level].height;

   intel_miptree_get_image_offset(mt, level, layer, &x_offset, &y_offset);
}
