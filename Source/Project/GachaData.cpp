#include "stdafx.h"
#include "GachaData.h"

const GachaData* GachaData::Create(CSVTokenizer& tokenizer)
{
  GachaData* ret = new GachaData();
  ret->id_ = tokenizer.NextToken().ToInt32();
  ret->rare1_ = tokenizer.NextToken().ToInt32();
  ret->rare2_ = tokenizer.NextToken().ToInt32();
  ret->rare3_ = tokenizer.NextToken().ToInt32();
  ret->rare4_ = tokenizer.NextToken().ToInt32();
  ret->rare5_ = tokenizer.NextToken().ToInt32();
  return ret;
}

GachaData::GachaData()
{
}

Model* GachaData::CreateModel()
{
  return new Model(*this->model_);
}

VehicleData* GachaData::CreateVehicle()
{
  return nullptr;
}
