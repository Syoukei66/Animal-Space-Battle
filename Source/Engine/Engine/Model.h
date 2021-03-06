#pragma once

#include "ModelNode.h"
#include "FbxResource.h"

class Model : public ModelNode
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Model(const FbxResource& data);
  ~Model();

  // =================================================================
  // Method
  // =================================================================
public:

  // =================================================================
  // Data Member
  // =================================================================
private:
  const FbxResource& data_;

};