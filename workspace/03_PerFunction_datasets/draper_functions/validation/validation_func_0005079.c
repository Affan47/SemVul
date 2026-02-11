CombineOps(OpRcPtrVec & opVec)
        {
            int count = 0;
            int firstindex = 0;

            OpRcPtrVec tmpops;

            while(firstindex < static_cast<int>(opVec.size()-1))
            {
                const OpRcPtr & first = opVec[firstindex];
                const OpRcPtr & second = opVec[firstindex+1];

                if(first->canCombineWith(second))
                {
                    tmpops.clear();
                    first->combineWith(tmpops, second);


                    opVec.erase(opVec.begin() + firstindex,
                        opVec.begin() + firstindex + 2);


                    std::copy(tmpops.begin(), tmpops.end(),
                        std::inserter(opVec, opVec.begin() + firstindex));


                    firstindex = std::max(0, firstindex-1);


                    ++count;
                }
                else
                {
                    ++firstindex;
                }
            }

            return count;
        }
