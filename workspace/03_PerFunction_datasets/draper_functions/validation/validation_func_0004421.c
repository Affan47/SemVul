update(int gap)
{
  int a, x;
  static int cnt = 80;

  if (_w.gc == NULL)
    return;

  x = gap / 5;
  if (x >= WINDOW_WIDTH)
    return;

  gdk_image_put_pixel(_image, x, _image_y, 0);
  gdk_image_put_pixel(_image, x, _image_y + WINDOW_HEIGHT, 0);

  if (--cnt >= 0)
    return;

  cnt = 80;

  _image_y++;

  for (a = 0;a < WINDOW_WIDTH;a++)
    {
      gdk_image_put_pixel(_image, a, _image_y, 0xffffffff);
      gdk_image_put_pixel(_image, a, _image_y + WINDOW_HEIGHT, 0xffffffff);
    }
  gdk_image_put_pixel(_image,  550 / 5, _image_y, 0xff0000);
  gdk_image_put_pixel(_image,  550 / 5, _image_y + WINDOW_HEIGHT, 0xff0000);
  gdk_image_put_pixel(_image, 1000 / 5, _image_y, 0x00ff00);
  gdk_image_put_pixel(_image, 1000 / 5, _image_y + WINDOW_HEIGHT, 0x00ff00);

  expose();

  if (_image_y >= WINDOW_HEIGHT)
    _image_y = 0;
}
