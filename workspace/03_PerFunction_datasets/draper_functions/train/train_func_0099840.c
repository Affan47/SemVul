zRender(Image &img){
    int w = img.width();
    int h = img.height();

    zmin = std::numeric_limits<double>::infinity();
    zmax = 0.0;

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			Point pixel(x+0.5, h-1-y+0.5, 0);
			Ray ray(eye, (pixel-eye).normalized());

			double dist = trace(ray, NULL).t;

			if (dist >= 0){
				if(dist < zmin) zmin = dist;
				if(dist > zmax) zmax = dist;
			}
		}
	}
}
