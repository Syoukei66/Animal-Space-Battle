#pragma once

#include "BaseBulletEmitter.h"

namespace BulletEmitterFactory
{

BaseBulletEmitter* Create(const std::string& name_id);

}