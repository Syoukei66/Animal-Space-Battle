#pragma once

#include "GachaData.h"
#include "DataTable.h"

class GachaTable : public DataTable<GachaData>
{
public:
  static GachaTable& GetInstance()
  {
    static GachaTable self;
    return self;
  }

private:
  GachaTable()
    : DataTable<GachaData>("Asset/data/gacha/gachaTable.csv")
  {}
  GachaTable(const GachaTable& b) = delete;

public:
  ~GachaTable() {}

};