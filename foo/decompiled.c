#include <foo.h>

ulong foo_decompiled(uint *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  param_1[param_2[1]] = param_1[*param_2] >> 3;
  param_1[param_2[3]] = uVar2 + param_1[param_1[param_2[2]]];
  if (uVar1 == param_1[param_2[1]]) {
    param_1[param_2[1]] = 0x2a;
  }
  return (ulong)*param_1;
}
