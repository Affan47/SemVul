pathIntegrityCheck(){
    for(vector<Path>::iterator itr = gatherer.begin();itr < gatherer.end(); itr++){

        if(!grid[itr->end.row][itr->end.col].isFood){
            bug << "revmoving path because gathered?" << itr->end.row << "," << itr->end.col << endl;
            gatherer.erase(itr);
            continue;
        }

        if(grid[itr->start.row][itr->start.col].ant != 0){
            bug << "revmoving because ant died?" << itr->start.row << "," << itr->start.col << endl;
            gatherer.erase(itr);
            continue;
        }
        if(itr->steps.size() < 1 ){
            bug << "Removing because out of steps" << itr->steps.front() << " " <<itr->steps.back() << endl;
            gatherer.erase(itr);
        }
        grid[itr->start.row][itr->start.col].marked = 1;

    }

}
