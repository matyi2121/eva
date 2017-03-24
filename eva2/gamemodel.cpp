#include "gamemodel.h"

GameModel::GameModel(int Height, int Width)
    :height(Height),
      width(Width)
{
    fields.resize(height);
    for(int i = 0; i < height; ++i)
    {
        fields[i].resize(width);
        for(int j = 0; j < width; ++j)
        {
            fields[i][j] = Field::empty;
        }
    }
}

