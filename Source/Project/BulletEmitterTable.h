#pragma once

#include "BulletEmitterData.h"
#include "DataTable.h"

class BulletEmitterTable : public DataTable<BulletEmitterData>
{
public:
  static BulletEmitterTable& GetInstance()
  {
    static BulletEmitterTable self;
    return self;
  }

private:
  BulletEmitterTable()
    : DataTable<BulletEmitterData>("Asset/data/bulletEmitter/bulletEmitterTable.csv")
  {}
  BulletEmitterTable(const BulletEmitterTable& b) = delete;

public:
  ~BulletEmitterTable() {}

};