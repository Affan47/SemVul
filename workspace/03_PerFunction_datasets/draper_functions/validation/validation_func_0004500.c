get_required_for_output (GeglOperation        *operation,
                         const gchar         *input_pad,
                         const GeglRectangle *region)
{
  GeglOperationAreaFilter *area = GEGL_OPERATION_AREA_FILTER (operation);
  GeglRectangle            rect;
  GeglRectangle            defined;

  defined = get_bounding_box (operation);
  gegl_rectangle_intersect (&rect, region, &defined);

  if (rect.width  != 0 &&
      rect.height != 0)
    {
      rect.x -= area->left;
      rect.y -= area->top;
      rect.width  += area->left + area->right;
      rect.height  += area->top + area->bottom;
    }

  return rect;
}
