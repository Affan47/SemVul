populate_field(struct field * f, unsigned int p)
{
    unsigned int x, y;

    for (x = 0; x < f->width; x++) {
	for (y = 0; y < f->height; y++) {
	    *cell_at(f, x, y) = random_cell(p);
	}
    }
}
