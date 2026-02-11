render(Image &img)
{
    switch (renderMode)
    {
        case PHONG:
            renderPixels(&Scene::tracePhong, img);
            break;

        case ZBUFFER:
            renderZBuffer(img);
            break;

        case NORMAL:
            renderPixels(&Scene::traceNormal, img);
            break;

        case GOOCH:
            renderPixels(&Scene::traceGooch, img);
            break;
    }
}
