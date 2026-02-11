calculate(const Grid &grid)
{
    grid_ = grid;
    const Dimensions dimensions = ensure_grid_is_square();
    size = static_cast<int>(grid_.size());
#ifdef USE_STL
    row_covered.resize(size, false);
    column_covered.resize(size, false);
#else
    row_covered.fill(false, size);
    column_covered.fill(false, size);
#endif
    z0_row = 0;
    z0_column = 0;
    path = make_grid(size * 2, static_cast<int>(ZERO));
    marked = make_grid(size, static_cast<int>(ZERO));

    int step = 1;
    while (step) {
        switch (step) {
            case 1: step = step1(); break;
            case 2: step = step2(); break;
            case 3: step = step3(); break;
            case 4: step = step4(); break;
            case 5: step = step5(); break;
            case 6: step = step6(); break;
            default: break;
        }
    }

    Indexes indexes;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if ((row < dimensions.first) &&
                (column < dimensions.second) &&
                marked.at(row).at(column) == STAR)
#ifdef USE_STL
                indexes.push_back(std::make_pair(row, column));
#else
                indexes.push_back(qMakePair(row, column));
#endif
        }
    }
    return indexes;
}
