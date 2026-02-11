IntersectP(const Ray &ray) const {
    PBRT_GRID_INTERSECTIONP_TEST(const_cast<GridAccel *>(this), const_cast<Ray *>(&ray));
    RWMutexLock lock(*rwMutex, READ);

    float rayT;
    if (bounds.Inside(ray(ray.mint)))
        rayT = ray.mint;
    else if (!bounds.IntersectP(ray, &rayT))
    {
        PBRT_GRID_RAY_MISSED_BOUNDS();
        return false;
    }
    Point gridIntersect = ray(rayT);


    float NextCrossingT[3], DeltaT[3];
    int Step[3], Out[3], Pos[3];
    for (int axis = 0; axis < 3; ++axis) {

        Pos[axis] = posToVoxel(gridIntersect, axis);
        if (ray.d[axis] >= 0) {

            NextCrossingT[axis] = rayT +
                (voxelToPos(Pos[axis]+1, axis) - gridIntersect[axis]) / ray.d[axis];
            DeltaT[axis] = width[axis] / ray.d[axis];
            Step[axis] = 1;
            Out[axis] = nVoxels[axis];
        }
        else {

            NextCrossingT[axis] = rayT +
                (voxelToPos(Pos[axis], axis) - gridIntersect[axis]) / ray.d[axis];
            DeltaT[axis] = -width[axis] / ray.d[axis];
            Step[axis] = -1;
            Out[axis] = -1;
        }
    }


    for (;;) {
        int o = offset(Pos[0], Pos[1], Pos[2]);
        Voxel *voxel = voxels[o];
        PBRT_GRID_RAY_TRAVERSED_VOXEL(Pos, voxel ? voxel->size() : 0);
        if (voxel && voxel->IntersectP(ray, lock))
            return true;


        int bits = ((NextCrossingT[0] < NextCrossingT[1]) << 2) +
                   ((NextCrossingT[0] < NextCrossingT[2]) << 1) +
                   ((NextCrossingT[1] < NextCrossingT[2]));
        const int cmpToAxis[8] = { 2, 1, 2, 1, 2, 2, 0, 0 };
        int stepAxis = cmpToAxis[bits];
        if (ray.maxt < NextCrossingT[stepAxis])
            break;
        Pos[stepAxis] += Step[stepAxis];
        if (Pos[stepAxis] == Out[stepAxis])
            break;
        NextCrossingT[stepAxis] += DeltaT[stepAxis];
    }
    return false;
}
