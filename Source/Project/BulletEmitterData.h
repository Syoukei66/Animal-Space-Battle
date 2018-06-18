#pragma once

#include "BaseBulletEmitter.h"

class BulletEmitterData
{
public:
  static const BulletEmitterData* Create(CSVTokenizer& tokenizer);

private:
  BulletEmitterData();

public:
  BaseBulletEmitter* CreateBulletEmitter() const;
  
public:
  inline T_UINT8 GetId() const
  {
    return this->id_;
  }
  inline const std::string& GetNameId() const
  {
    return this->name_id_;
  }
  inline const std::string& GetName() const
  {
    return this->name_;
  }
  inline const std::string& GetComment() const
  {
    return this->comment_;
  }

private:
  T_UINT8 id_;
  std::string name_id_;
  std::string name_;
  std::string comment_;

};