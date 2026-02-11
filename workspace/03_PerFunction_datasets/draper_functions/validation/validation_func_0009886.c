fixPolygonalTopology(const geom::Geometry& geom )
{


  auto_ptr<Geometry> tmp;
  auto_ptr<GeometryFactory> tmpFactory;

  const Geometry* geomToBuffer = &geom;

  if ( ! newFactory ) {
    tmpFactory = createFactory(*geom.getFactory(), targetPM);
    tmp.reset( tmpFactory->createGeometry(&geom) );
    geomToBuffer = tmp.get();
  }

  auto_ptr<Geometry> bufGeom ( geomToBuffer->buffer(0) );

  if ( ! newFactory ) {

    bufGeom.reset( geom.getFactory()->createGeometry(bufGeom.get()) );
  }

  return bufGeom;
}
