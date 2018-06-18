#pragma once

#include "BulletEmitter.h"

class BulletEmitter_Self : public BulletEmitter
{
public:
  BulletEmitter_Self(T_FLOAT speed);
  ~BulletEmitter_Self();

public:
  virtual T_UINT32 EmissionProcess() override;
  virtual void UpdateProcess() override;

private:
  const T_FLOAT speed_;
 
}; 
