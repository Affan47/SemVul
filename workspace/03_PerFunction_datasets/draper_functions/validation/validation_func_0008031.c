main()
{
	PrecisionModel pm;
	GeometryFactory gf(&pm);
	WKTReader rdr(&gf);

	string inputWKT =
        "POLYGON ((110 320, 190 220, 60 200, 180 120, 120 40, 290 150, 410 40, 410 230, 500 340, 320 310, 260 370, 220 310, 110 320), (220 260, 250 180, 290 220, 360 150, 350 250, 260 280, 220 260))";

        GeomPtr base ( rdr.read(inputWKT) );
	run(base.get());
}
