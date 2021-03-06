#ifndef HAL_ENGINE_NATIVE_NATIVEMETHOD_H_
#define HAL_ENGINE_NATIVE_NATIVEMETHOD_H_

#include "INativeProcess_Graphics.h"
#include "INativeProcess_IO.h"
#include "INativeProcess_Time.h"

//このあたりなんか全体的に微妙
//SetInstance,DeleteInstanceが常に露出しているところとか
namespace NativeMethod
{

INativeProcess_Graphics& Graphics();
void Graphics_SetInstance(INativeProcess_Graphics* process);
void Graphics_DeleteInstance();

INativeProcess_IO& IO();
void IO_SetInstance(INativeProcess_IO* process);
void IO_DeleteInstance();

INativeProcess_Time& Time();
void Time_SetInstance(INativeProcess_Time* process);
void Time_DeleteInstance();

} // namespace NativeMethod

#endif//HAL_ENGINE_NATIVE_NATIVEMETHOD_H_
