e_color_class_instance_set(E_Color_Class *cc, int r, int g, int b, int a, int r2, int b2, int g2, int a2, int r3, int g3, int b3, int a3)
{
   if (!cc) return;

   if (r != -1) cc->r = E_CLAMP(r, 0, 255);
   if (g != -1) cc->g = E_CLAMP(g, 0, 255);
   if (b != -1) cc->b = E_CLAMP(b, 0, 255);
   if (a != -1) cc->a = E_CLAMP(a, 0, 255);
   if (r2 != -1) cc->r2 = E_CLAMP(r2, 0, 255);
   if (g2 != -1) cc->g2 = E_CLAMP(g2, 0, 255);
   if (b2 != -1) cc->b2 = E_CLAMP(b2, 0, 255);
   if (a2 != -1) cc->a2 = E_CLAMP(a2, 0, 255);
   if (r3 != -1) cc->r3 = E_CLAMP(r3, 0, 255);
   if (g3 != -1) cc->g3 = E_CLAMP(g3, 0, 255);
   if (b3 != -1) cc->b3 = E_CLAMP(b3, 0, 255);
   if (a3 != -1) cc->a3 = E_CLAMP(a3, 0, 255);

   edje_color_class_set(cc->name,
			cc->r, cc->g, cc->b, cc->a,
			cc->r2, cc->g2, cc->b2, cc->a2,
			cc->r3, cc->g3, cc->b3, cc->a3);
   e_config_save_queue();
}
