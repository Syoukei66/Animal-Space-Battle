#include "stdafx.h"
#include "BulletEmitterData.h"
#include "BulletEmitterFactory.h"

const BulletEmitterData* BulletEmitterData::Create(CSVTokenizer& tokenizer)
{
  BulletEmitterData* ret = new BulletEmitterData();
  ret->id_ = tokenizer.NextToken().ToInt32();
  ret->name_id_ = tokenizer.NextToken().ToString();
  ret->name_ = tokenizer.NextToken().ToString();
  ret->comment_ = tokenizer.NextToken().ToString();
  return ret;
}

BulletEmitterData::BulletEmitterData()
{
}

BaseBulletEmitter* BulletEmitterData::CreateBulletEmitter() const
{
  return BulletEmitterFactory::Create(this->name_id_);
}
