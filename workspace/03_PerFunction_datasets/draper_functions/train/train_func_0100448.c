trace(const Ray &ray)
{

    Hit min_hit(std::numeric_limits<double>::infinity(),Vector());
    Object *obj = NULL;
    for (unsigned int i = 0; i < objects.size(); ++i) {
        Hit hit(objects[i]->intersect(ray));
        if (hit.t<min_hit.t) {
            min_hit = hit;
            obj = objects[i];
        }
    }


    if (!obj) return Color(0.0, 0.0, 0.0);

    Material *material = obj->material;
    Point hit = ray.at(min_hit.t);
    Vector N = min_hit.N;
    Vector V = -ray.D;

    switch (mode) {
    case PHONG:
        return renderPhong(material, hit, N, V);
    case ZBUFFER:
        return renderZBuffer(hit);
    case NORMAL:
        return renderNormal(N);
    }
    return Color(0.0, 0.0, 0.0);
}
