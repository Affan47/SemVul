gs_pixel_image_t_init(gs_pixel_image_t * pim,
                      gs_color_space * color_space)
{
    int num_components;

    if (color_space == 0 ||
        (num_components =
         gs_color_space_num_components(color_space)) < 0
        )
        num_components = 0;
    gs_data_image_t_init((gs_data_image_t *) pim, num_components);
    pim->format = gs_image_format_chunky;
    pim->ColorSpace = color_space;
    pim->CombineWithColor = false;
}
