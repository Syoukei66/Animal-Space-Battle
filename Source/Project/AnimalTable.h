#pragma once

#include "AnimalData.h"
#include "DataTable.h"

class AnimalTable : public DataTable<AnimalData>
{
public:
  static AnimalTable& GetInstance()
  {
    static AnimalTable self;
    return self;
  }

private:
  AnimalTable()
    : DataTable<AnimalData>("Asset/data/animal/animalTable.csv")
  {}
  AnimalTable(const AnimalTable& b) = delete;

public:
  ~AnimalTable() {}

};
