//
// Created by sarsa on 02-07-2025.
//

#ifndef CORNERPATTERNDATABASE_H
#define CORNERPATTERNDATABASE_H

#include "../Models/GenericRubiksCubeModel.h"
#include "PatternDatabase.h"
#include "PermutationIndexer.h"
using namespace std;

class CornerPatternDatabase : public PatternDatabase {

    typedef GenericRubiksCubeModel::FACE F;

    PermutationIndexer<8> permIndexer;

public:
    CornerPatternDatabase();
    CornerPatternDatabase(uint8_t init_val);
    uint32_t getDatabaseIndex(const GenericRubiksCubeModel& cube) const;

};


#endif //CORNERPATTERNDATABASE_H
