/* pno0001.exe (.kkrieger, 2004) - Ghidra decompilation of the unpacked image */

/* ---- operator_new @ 00801000 ---- */

void operator_new(SIZE_T param_1)

{
  HANDLE hHeap;
  DWORD dwFlags;
  
  dwFlags = 1;
  hHeap = GetProcessHeap();
  HeapAlloc(hHeap,dwFlags,param_1);
  return;
}


/* ---- operator_delete @ 00801017 ---- */

void operator_delete(LPVOID param_1)

{
  HANDLE hHeap;
  DWORD dwFlags;
  
  dwFlags = 1;
  hHeap = GetProcessHeap();
  HeapFree(hHeap,dwFlags,param_1);
  return;
}


/* ---- FUN_0080102e @ 0080102e ---- */

void FUN_0080102e(void)

{
  PostQuitMessage(0);
  return;
}


/* ---- FUN_00801037 @ 00801037 ---- */

void __thiscall FUN_00801037(int param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int *piVar5;
  int local_40 [3];
  int local_34;
  undefined4 local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  int local_20;
  int *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  int *local_c;
  int *local_8;
  
  piVar4 = param_2;
  piVar5 = (int *)(param_1 + 0x20c);
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar5 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  }
  local_10 = *param_2;
  if (param_2[1] == -1) {
    *(int *)(param_1 + 0x200) = local_10;
    iVar2 = local_10 * 0x68 + param_1;
    *(int *)(param_1 + 0x1fc) = iVar2 + 0x5c;
    local_20 = *(int *)(iVar2 + 0x70);
    local_c = *(int **)(iVar2 + 0x74);
    piVar4 = param_2;
  }
  else {
    piVar4 = (int *)(param_2[1] * 0x1c + 0x2c0 + param_1);
    local_20 = piVar4[1];
    local_c = (int *)piVar4[2];
  }
  if ((param_2[4] == param_2[2]) || (param_2[5] == param_2[3])) {
    local_28 = 0;
    local_24 = 0;
    *(undefined4 *)(param_1 + 0x214) = 0;
    *(undefined4 *)(param_1 + 0x218) = 0;
    *(int *)(param_1 + 0x21c) = local_20;
    *(int **)(param_1 + 0x220) = local_c;
    local_1c = local_c;
  }
  else {
    local_28 = param_2[2];
    local_24 = param_2[3];
    local_20 = param_2[4] - local_28;
    local_1c = (int *)(param_2[5] - local_24);
  }
  *(int *)(param_1 + 0x204) = local_20;
  local_18 = 0;
  *(int **)(param_1 + 0x208) = local_1c;
  local_14 = 0x3f800000;
  if (param_2[1] == -1) {
    iVar2 = (**(code **)(**(int **)(param_1 + 0x441fc) + 0x38))
                      (*(int **)(param_1 + 0x441fc),local_10,&local_c);
    if (iVar2 < 0) {
      (**(code **)(**(int **)(param_1 + 0x441fc) + 0x38))
                (*(int **)(param_1 + 0x441fc),local_10,&local_c);
      (**(code **)(**(int **)(param_1 + 0x441fc) + 0x38))
                (*(int **)(param_1 + 0x441fc),local_10,&local_c);
    }
    iVar2 = (**(code **)(*local_c + 0x14))(local_c,0,0,&local_8);
    if (iVar2 < 0) {
      (**(code **)(*local_c + 0x14))(local_c,0,0,&local_8);
      (**(code **)(*local_c + 0x14))(local_c,0,0,&local_8);
    }
    (**(code **)(*local_c + 8))(local_c);
  }
  else {
    iVar2 = (**(code **)(*(int *)piVar4[5] + 0x48))((int *)piVar4[5],0,&local_8);
    if (iVar2 < 0) {
      (**(code **)(*(int *)piVar4[5] + 0x48))((int *)piVar4[5],0,&local_8);
      (**(code **)(*(int *)piVar4[5] + 0x48))((int *)piVar4[5],0,&local_8);
    }
  }
  iVar2 = (**(code **)(**(int **)(param_1 + 0x441fc) + 0x94))
                    (*(int **)(param_1 + 0x441fc),0,local_8);
  if (iVar2 < 0) {
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0x94))(*(int **)(param_1 + 0x441fc),0,local_8);
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0x94))(*(int **)(param_1 + 0x441fc),0,local_8);
  }
  (**(code **)(*local_8 + 8))(local_8);
  if ((local_10 == -1) && ((*(byte *)(param_2 + 6) & 4) == 0)) {
    local_40[0] = 0;
    local_40[1] = 0;
    local_40[2] = piVar4[1];
    local_34 = piVar4[2];
    local_30 = 0;
    local_2c = 0x3f800000;
    piVar4 = local_40;
  }
  else {
    piVar4 = &local_28;
  }
  (**(code **)(**(int **)(param_1 + 0x441fc) + 0xbc))(*(int **)(param_1 + 0x441fc),piVar4);
  if ((*(int *)(param_1 + 0x44210) == 0x4b) || (*(int *)(param_1 + 0x44210) == 0x49)) {
    uVar3 = 4;
  }
  else {
    uVar3 = 0;
  }
  uVar1 = param_2[6] & 3;
  if (((uVar1 != 1) && (uVar1 != 2)) && (uVar1 == 3)) {
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0xac))
              (*(int **)(param_1 + 0x441fc),0,0,uVar3 | 3,param_2[7],0x3f800000,0);
  }
  if (local_10 == -1) {
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0xbc))(*(int **)(param_1 + 0x441fc),&local_28);
  }
  iVar2 = (**(code **)(**(int **)(param_1 + 0x441fc) + 0xa4))(*(int **)(param_1 + 0x441fc));
  if (iVar2 < 0) {
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0xa4))(*(int **)(param_1 + 0x441fc));
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0xa4))(*(int **)(param_1 + 0x441fc));
  }
  return;
}


/* ---- FUN_008012d2 @ 008012d2 ---- */

void __fastcall FUN_008012d2(int param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(**(int **)(param_1 + 0x441fc) + 0xa8))(*(int **)(param_1 + 0x441fc));
  if (iVar1 < 0) {
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0xa8))(*(int **)(param_1 + 0x441fc));
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0xa8))(*(int **)(param_1 + 0x441fc));
  }
  return;
}


/* ---- FUN_00801308 @ 00801308 ---- */

void __thiscall FUN_00801308(int param_1,int param_2)

{
  int *piVar1;
  
  if (param_2 != -1) {
    piVar1 = (int *)(param_2 * 0x1c + 0x2c0 + param_1);
    *piVar1 = *piVar1 + 1;
  }
  return;
}


/* ---- FUN_00801323 @ 00801323 ---- */

void __thiscall FUN_00801323(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)(param_2 * 0x1c + 0x2c0 + param_1);
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    (**(code **)(*(int *)piVar1[5] + 8))((int *)piVar1[5]);
    piVar1[3] = 0;
    piVar1[5] = 0;
  }
  return;
}


/* ---- FUN_0080134e @ 0080134e ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0080134e(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  float local_34;
  float local_30;
  float local_2c;
  int local_24;
  int local_20;
  float local_1c;
  float local_18;
  int local_14;
  int local_10;
  undefined *local_c;
  int local_8;
  
  puVar1 = (undefined4 *)(param_1 + 0x4422c);
  iVar2 = (**(code **)(**(int **)(param_1 + 0x441fc) + 100))
                    (*(int **)(param_1 + 0x441fc),0x40,1,0,0x15,1,puVar1,0);
  if (iVar2 < 0) {
    (**(code **)(**(int **)(param_1 + 0x441fc) + 100))
              (*(int **)(param_1 + 0x441fc),0x40,1,0,0x15,1,puVar1,0);
    (**(code **)(**(int **)(param_1 + 0x441fc) + 100))
              (*(int **)(param_1 + 0x441fc),0x40,1,0,0x15,1,puVar1,0);
  }
  local_8 = 0;
  local_c = &DAT_00821548;
  do {
    iVar2 = (**(code **)(*(int *)*puVar1 + 0x4c))((int *)*puVar1,local_8,0,&local_24,0,0);
    if (iVar2 < 0) {
      (**(code **)(*(int *)*puVar1 + 0x4c))((int *)*puVar1,local_8,0,&local_24,0,0);
      (**(code **)(*(int *)*puVar1 + 0x4c))((int *)*puVar1,local_8,0,&local_24,0,0);
    }
    local_10 = 0;
    do {
      local_18 = _DAT_0081f0f4 - (float)local_10;
      puVar3 = (undefined1 *)(local_24 * local_10 + local_20);
      local_14 = 0;
      do {
        FUN_0080598d(local_c + -0x10,local_c);
        FUN_0080600c(_DAT_0081f0f4);
        FUN_0080604f(local_c + -0x10,(float)local_14 - _DAT_0081f0f4);
        FUN_0080604f(local_c,local_18);
        FUN_0080620b();
        *puVar3 = (char)(int)ROUND(local_2c * _DAT_0081f0f0 + _DAT_0081f0ec);
        puVar3[1] = (char)(int)ROUND(local_30 * _DAT_0081f0f0 + _DAT_0081f0ec);
        local_1c = local_34 * _DAT_0081f0f0 + _DAT_0081f0ec;
        puVar3[2] = (char)(int)ROUND(local_1c);
        puVar3[3] = 0;
        puVar3 = puVar3 + 4;
        local_14 = local_14 + 1;
      } while (local_14 < 0x40);
      local_10 = local_10 + 1;
    } while (local_10 < 0x40);
    iVar2 = (**(code **)(*(int *)*puVar1 + 0x50))((int *)*puVar1,local_8,0);
    if (iVar2 < 0) {
      (**(code **)(*(int *)*puVar1 + 0x50))((int *)*puVar1,local_8,0);
      (**(code **)(*(int *)*puVar1 + 0x50))((int *)*puVar1,local_8,0);
    }
    local_c = local_c + 0x20;
    local_8 = local_8 + 1;
  } while ((int)local_c < 0x821608);
  return;
}


/* ---- FUN_00801519 @ 00801519 ---- */

void __thiscall FUN_00801519(int param_1,uint param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)(param_1 + 0x441fc);
  iVar2 = *piVar1;
  if (param_2 < 0x100) {
    (**(code **)(iVar2 + 0xe4))(piVar1,param_2,param_3);
  }
  else if (param_2 < 0x200) {
    (**(code **)(iVar2 + 0x10c))(piVar1,param_2 >> 5 & 7,param_2 & 0x1f);
  }
  else {
    (**(code **)(iVar2 + 0x114))(piVar1,param_2 >> 4 & 0xf,param_2 & 0xf,param_3);
  }
  return;
}


/* ---- FUN_00801573 @ 00801573 ---- */

void __thiscall FUN_00801573(int param_1,int param_2,int param_3,int param_4,undefined4 param_5)

{
  undefined4 *puVar1;
  int *piVar2;
  bool bVar3;
  int iVar4;
  undefined4 local_8;
  
  iVar4 = param_2 * 0x14 + param_1;
  *(char *)(iVar4 + 0xa068) = (char)param_4 + '\x01';
  puVar1 = (undefined4 *)((param_2 + 0x806) * 0x14 + param_1);
  *(undefined4 *)(iVar4 + 0xa06c) = param_5;
  *(undefined4 *)(iVar4 + 0xa070) = 0;
  *(undefined4 *)(iVar4 + 0xa074) = 0;
  *puVar1 = 0;
  local_8 = 8;
  if (param_3 != 0) {
    local_8 = 0x208;
  }
  bVar3 = param_3 == 0;
  piVar2 = *(int **)(param_1 + 0x441fc);
  if (param_4 == 0) {
    iVar4 = (**(code **)(*piVar2 + 0x68))(piVar2,param_5,local_8,0);
    if (iVar4 < 0) {
      (**(code **)(**(int **)(param_1 + 0x441fc) + 0x68))
                (*(int **)(param_1 + 0x441fc),param_5,local_8,0,bVar3,puVar1,0);
      (**(code **)(**(int **)(param_1 + 0x441fc) + 0x68))
                (*(int **)(param_1 + 0x441fc),param_5,local_8,0,bVar3,puVar1,0);
    }
  }
  else {
    iVar4 = (**(code **)(*piVar2 + 0x6c))(piVar2,param_5,local_8,0x65,bVar3,puVar1,0);
    if (iVar4 < 0) {
      (**(code **)(**(int **)(param_1 + 0x441fc) + 0x6c))
                (*(int **)(param_1 + 0x441fc),param_5,local_8,0x65,bVar3,puVar1,0);
      (**(code **)(**(int **)(param_1 + 0x441fc) + 0x6c))
                (*(int **)(param_1 + 0x441fc),param_5,local_8,0x65,bVar3,puVar1,0);
    }
  }
  return;
}


/* ---- FUN_0080166b @ 0080166b ---- */

int __thiscall FUN_0080166b(int param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  iVar3 = 1;
  piVar2 = (int *)(param_1 + 0x14098);
  do {
    if (*piVar2 == 0) {
      piVar4 = piVar2;
      for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
        *piVar4 = 0;
        piVar4 = piVar4 + 1;
      }
      iVar1 = *(int *)(&DAT_008210e0 + param_2 * 0xc);
      piVar2[3] = 0;
      piVar2[1] = param_2;
      *piVar2 = param_3;
      piVar2[2] = iVar1;
      return iVar3;
    }
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 0xc;
  } while (iVar3 < 0x1000);
  return 0;
}


/* ---- FUN_008016bc @ 008016bc ---- */

void __thiscall FUN_008016bc(int param_1,int param_2)

{
  *(undefined4 *)(param_2 * 0x30 + 0x14094 + param_1) = 0;
  return;
}


/* ---- FUN_008016d1 @ 008016d1 ---- */

uint __thiscall FUN_008016d1(int param_1,int *param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  
  puVar1 = (uint *)(*param_2 * 0x30 + 0x14068 + param_1);
  uVar2 = 0;
  if (puVar1[6] == 0) {
    uVar2 = 3;
  }
  if ((puVar1[4] == 0) && (puVar1[7] != *(uint *)(param_1 + 0x44068))) {
    uVar2 = uVar2 | 1;
  }
  if ((puVar1[8] == 1) && (puVar1[0xb] != *(uint *)(param_1 + 0x4406c))) {
    uVar2 = uVar2 | 2;
  }
  if (uVar2 == 0) {
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0x15c))
              (*(int **)(param_1 + 0x441fc),*(undefined4 *)(&DAT_008210e8 + puVar1[1] * 0xc));
    if ((puVar1[10] != 0) && (*(uint *)(param_1 + 0x44078) != puVar1[8])) {
      (**(code **)(**(int **)(param_1 + 0x441fc) + 0x1a0))
                (*(int **)(param_1 + 0x441fc),*(undefined4 *)((puVar1[8] + 0x806) * 0x14 + param_1))
      ;
      *(uint *)(param_1 + 0x44078) = puVar1[8];
    }
    if ((*(uint *)(param_1 + 0x44070) != puVar1[4]) || (*(uint *)(param_1 + 0x44074) != puVar1[2]))
    {
      (**(code **)(**(int **)(param_1 + 0x441fc) + 400))
                (*(int **)(param_1 + 0x441fc),0,
                 *(undefined4 *)((puVar1[4] + 0x806) * 0x14 + param_1),0,puVar1[2]);
      *(uint *)(param_1 + 0x44070) = puVar1[4];
      *(uint *)(param_1 + 0x44074) = puVar1[2];
    }
    uVar2 = puVar1[10];
    if (uVar2 == 0) {
      uVar2 = puVar1[6];
    }
    uVar3 = *puVar1 & 7;
    if ((uVar3 != 1) && (uVar3 != 2)) {
      if (uVar3 == 3) {
        uVar2 = (int)uVar2 / 3;
        param_2 = (int *)0x4;
      }
      else if (((uVar3 != 4) && (uVar3 != 5)) && (uVar3 == 6)) {
        *(undefined4 *)(param_1 + 0x44078) = 2;
        (**(code **)(**(int **)(param_1 + 0x441fc) + 0x1a0))
                  (*(int **)(param_1 + 0x441fc),*(undefined4 *)(param_1 + 0xa0a0));
        (**(code **)(**(int **)(param_1 + 0x441fc) + 0x148))
                  (*(int **)(param_1 + 0x441fc),4,puVar1[5],0,puVar1[6],0,((int)uVar2 / 4) * 2);
        return 0;
      }
    }
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0x148))
              (*(int **)(param_1 + 0x441fc),param_2,puVar1[5],0,puVar1[6],puVar1[9],uVar2);
    return 0;
  }
  return uVar2;
}


/* ---- FUN_00801856 @ 00801856 ---- */

void __thiscall FUN_00801856(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = param_2 * 0x30 + 0x14068 + param_1;
  if ((*(byte *)(iVar1 + 0xc) & 1) != 0) {
    piVar2 = *(int **)((*(int *)(iVar1 + 0x10) + 0x806) * 0x14 + param_1);
    (**(code **)(*piVar2 + 0x30))(piVar2);
    *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffffffe;
  }
  if ((*(byte *)(iVar1 + 0xc) & 2) != 0) {
    piVar2 = *(int **)((*(int *)(iVar1 + 0x20) + 0x806) * 0x14 + param_1);
    (**(code **)(*piVar2 + 0x30))(piVar2);
    *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffffffd;
  }
  if (param_3 != -1) {
    *(int *)(iVar1 + 0x18) = param_3;
  }
  if (param_4 != -1) {
    *(int *)(iVar1 + 0x28) = param_4;
  }
  return;
}


/* ---- FUN_008018c3 @ 008018c3 ---- */

void __thiscall FUN_008018c3(int param_1,int param_2,undefined4 param_3,uint param_4)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  int local_3c;
  int local_38;
  uint local_34;
  int *local_30;
  int local_2c;
  int local_28;
  int local_24;
  ushort *local_20;
  uint local_1c;
  int local_18;
  ushort *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_34 = param_4 & 0x10;
  local_10 = 0;
  param_1 = param_2 * 0x1c + 0x2c0 + param_1;
  param_2 = *(int *)(param_1 + 4);
  local_c = *(int *)(param_1 + 8);
  piVar5 = *(int **)(param_1 + 0x14);
  iVar7 = local_c * param_2;
  local_30 = piVar5;
  local_24 = param_2;
  local_20 = (ushort *)operator_new(iVar7 * 8);
  FUN_0080574a(iVar7 * 2);
  while( true ) {
    (**(code **)(*piVar5 + 0x4c))(piVar5,local_10,&local_3c,0,0);
    param_3 = local_20;
    if (0 < local_c) {
      uVar6 = 0;
      local_2c = (local_3c / 4) * 4;
      local_1c = local_c;
      iVar7 = local_38;
      do {
        local_8 = 0;
        if (*(int *)(param_1 + 0x10) == 5) {
          if (0 < param_2) {
            puVar2 = param_3 + 1;
            do {
              iVar4 = (int)(puVar2[2] - 0x4000) >> 7;
              uVar6 = ((CONCAT22((short)(uVar6 >> 0x10),puVar2[-1]) + -0x4000 >> 7 & 0xffU |
                       iVar4 << 8) << 8 |
                      CONCAT22((short)((uint)iVar4 >> 8),*puVar2) + -0x4000 >> 7 & 0xffU) << 8 |
                      (int)(puVar2[1] - 0x4000) >> 7 & 0xffU;
              *(uint *)(iVar7 + local_8 * 4) = uVar6;
              local_8 = local_8 + 1;
              puVar2 = puVar2 + 4;
            } while (local_8 < param_2);
          }
        }
        else if (0 < param_2) {
          puVar2 = param_3 + 3;
          do {
            uVar6 = ((puVar2[-1] & 0x7f80 | (*puVar2 & 0xffffff80) << 8) << 8 | puVar2[-2] & 0x7f80)
                    * 2 | puVar2[-3] >> 7 & 0xff;
            *(uint *)(iVar7 + local_8 * 4) = uVar6;
            local_8 = local_8 + 1;
            puVar2 = puVar2 + 4;
          } while (local_8 < param_2);
        }
        iVar7 = iVar7 + local_2c;
        param_3 = param_3 + local_24 * 4;
        local_1c = local_1c + -1;
      } while (local_1c != 0);
      local_1c = 0;
      piVar5 = local_30;
    }
    (**(code **)(*piVar5 + 0x50))(piVar5,local_10);
    if ((param_2 < 2) || (local_c < 2)) break;
    local_1c = (uint)((int)(param_4 & 0xf) <= local_10);
    if (local_34 != 0) {
      local_1c = (uint)(local_1c == 0);
    }
    param_3 = local_20;
    local_14 = local_20;
    if (0 < local_c / 2) {
      local_8 = local_24 * 0x10;
      local_18 = param_2 / 2;
      local_2c = local_c / 2;
      do {
        puVar2 = local_14 + local_24 * 4;
        puVar3 = param_3 + local_24 * 8;
        iVar7 = local_18;
        if (0 < local_18) {
          do {
            local_28 = iVar7;
            if (local_1c == 0) {
              *local_14 = *param_3;
              local_14[1] = param_3[1];
              local_14[2] = param_3[2];
              uVar1 = param_3[3];
            }
            else {
              *local_14 = (ushort)((int)((uint)param_3[local_24 * 4 + 4] +
                                         (uint)param_3[local_24 * 4] + (uint)param_3[4] + 2 +
                                        (uint)*param_3) >> 2);
              local_14[1] = (ushort)((int)((uint)param_3[local_24 * 4 + 5] +
                                           (uint)param_3[local_24 * 4 + 1] + (uint)param_3[5] + 2 +
                                          (uint)param_3[1]) >> 2);
              local_14[2] = (ushort)((int)((uint)param_3[local_24 * 4 + 6] +
                                           (uint)param_3[local_24 * 4 + 2] + (uint)param_3[6] + 2 +
                                          (uint)param_3[2]) >> 2);
              uVar1 = (ushort)((int)((uint)param_3[local_24 * 4 + 7] +
                                     (uint)param_3[local_24 * 4 + 3] + (uint)param_3[7] + 2 +
                                    (uint)param_3[3]) >> 2);
            }
            local_14[3] = uVar1;
            local_14 = local_14 + 4;
            param_3 = param_3 + 8;
            local_28 = local_28 + -1;
            iVar7 = local_28;
          } while (local_28 != 0);
        }
        local_2c = local_2c + -1;
        param_3 = puVar3;
        local_14 = puVar2;
      } while (local_2c != 0);
      local_2c = 0;
    }
    param_2 = param_2 >> 1;
    local_c = local_c >> 1;
    local_10 = local_10 + 1;
    piVar5 = local_30;
  }
  operator_delete(local_20);
  return;
}


/* ---- FUN_00801bae @ 00801bae ---- */

void FUN_00801bae(undefined4 param_1,int param_2)

{
  int iVar1;
  tagPOINT local_c;
  
  GetCursorPos(&local_c);
  DAT_0083f8dc = DAT_0083f8dc + -400 + local_c.x;
  iVar1 = DAT_0083f8d8 + -300 + local_c.y;
  DAT_0083f8d8 = iVar1;
  *(int *)(param_2 + 4) = DAT_0083f8dc;
  *(int *)(param_2 + 8) = iVar1;
  SetCursorPos(400,300);
  return;
}


/* ---- FUN_00801c05 @ 00801c05 ---- */

int __fastcall FUN_00801c05(int param_1)

{
  DWORD DVar1;
  
  DVar1 = timeGetTime();
  return DVar1 - *(int *)(param_1 + 0x54);
}


/* ---- FUN_00801c13 @ 00801c13 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00801c13(void)

{
  int iVar1;
  undefined1 local_c [4];
  int local_8;
  
  SetEvent(DAT_0083f850);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0083f8a4);
  iVar1 = (**(code **)(*DAT_0083f890 + 0x10))(DAT_0083f890,&local_8,local_c);
  if (-1 < iVar1) {
    local_8 = local_8 - _DAT_0083f870;
    if (local_8 < 0) {
      local_8 = local_8 + 0x80000;
    }
    if (0 < local_8) {
      _DAT_0083f8d0 = local_8 / 4 + _DAT_0083f8c0;
    }
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0083f8a4);
  return;
}


/* ---- FUN_00801c77 @ 00801c77 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00801c77(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  while (DAT_0083f844 == 0) {
    WaitForSingleObject(DAT_0083f850,0x2e7);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0083f8a4);
    iVar2 = (**(code **)(*DAT_0083f890 + 0x10))(DAT_0083f890,&local_8,&local_14);
    uVar1 = local_8;
    if (-1 < iVar2) {
      local_8 = (int)local_8 / 4;
      local_14 = local_14 / 4;
      if ((int)local_8 < DAT_0083f8e0) {
        local_8 = local_8 + 0x20000;
      }
      uVar3 = local_8 - DAT_0083f8e0 & ~(DAT_0083f858 - 1U);
      if (0 < (int)uVar3) {
        local_10 = 0;
        local_c = 0;
        iVar2 = (**(code **)(*DAT_0083f890 + 0x2c))
                          (DAT_0083f890,DAT_0083f8e0 << 2,uVar3 << 2,&local_1c,&local_10,&local_18,
                           &local_c,0);
        if (-1 < iVar2) {
          DAT_0083f8e0 = DAT_0083f8e0 + uVar3;
          if (0x1ffff < DAT_0083f8e0) {
            DAT_0083f8e0 = DAT_0083f8e0 + -0x20000;
          }
          _DAT_0083f8c0 = _DAT_0083f8c0 + uVar3;
          _DAT_0083f870 = ~(DAT_0083f858 - 1U) & uVar1;
          if (DAT_0083f898 != (code *)0x0) {
            if (local_10 != 0) {
              (*DAT_0083f898)(DAT_0083f8c4);
            }
            if (local_c != 0) {
              (*DAT_0083f898)(DAT_0083f8c4);
            }
          }
          (**(code **)(*DAT_0083f890 + 0x4c))(DAT_0083f890,local_1c,local_10,local_18,local_c);
        }
      }
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0083f8a4);
  }
  DAT_0083f844 = 0;
  return 0;
}


/* ---- FUN_00801dea @ 00801dea ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00801dea(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0083f8a4);
  _DAT_0083f83c = 0;
  DAT_0083f858 = param_2;
  DAT_0083f898 = FUN_0081e80f;
  DAT_0083f8c4 = param_3;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0083f8a4);
  return;
}


/* ---- FUN_00801e27 @ 00801e27 ---- */

int __thiscall FUN_00801e27(int param_1,undefined4 *param_2,int *param_3,int param_4,int param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  undefined4 *puVar7;
  int local_44 [4];
  undefined4 *local_34;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined2 uStack_10;
  undefined4 local_c;
  undefined4 *local_8;
  
  piVar1 = param_3;
  uStack_10 = 0;
  piVar6 = local_44;
  for (iVar4 = 9; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  local_34 = &local_20;
  local_44[2] = (int)param_3 << 2;
  local_44[0] = 0x24;
  local_20 = 0x20001;
  local_1c = 0xac44;
  local_18 = 0x2b110;
  local_14 = 0x100004;
  local_44[1] = 0xe0;
  iVar4 = (**(code **)(*DAT_0083f894 + 0xc))(DAT_0083f894,local_44,&param_3,0);
  if ((-1 < iVar4) &&
     (iVar4 = (**(code **)(*param_3 + 0x2c))(param_3,0,0,&local_8,&local_c,0,0,2), -1 < iVar4)) {
    puVar7 = local_8;
    for (uVar5 = (uint)piVar1 & 0x3fffffff; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar7 = *param_2;
      param_2 = param_2 + 1;
      puVar7 = puVar7 + 1;
    }
    for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined1 *)puVar7 = *(undefined1 *)param_2;
      param_2 = (undefined4 *)((int)param_2 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
    iVar2 = (**(code **)(*param_3 + 0x4c))(param_3,local_8,local_c,0,0);
    iVar4 = param_4;
    if (-1 < iVar2) {
      param_1 = param_5 * 0x28 + param_1;
      *(int **)(param_1 + 0x7724) = param_3;
      param_2 = (undefined4 *)0x1;
      if (1 < param_4) {
        iVar2 = param_1 + 0x7728;
        do {
          iVar3 = (**(code **)(*DAT_0083f894 + 0x14))(DAT_0083f894,param_3,iVar2);
          if (iVar3 < 0) {
            return -1;
          }
          param_2 = (undefined4 *)((int)param_2 + 1);
          iVar2 = iVar2 + 4;
        } while ((int)param_2 < iVar4);
      }
      *(undefined4 *)(param_1 + 0x7748) = 0;
      *(int *)(param_1 + 0x7744) = iVar4;
      return param_5;
    }
  }
  return -1;
}


/* ---- FUN_00801f53 @ 00801f53 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

LONG __thiscall
FUN_00801f53(int param_1,int param_2,UINT param_3,LPCSTR param_4,int param_5,int param_6,
            uint param_7)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  tagTEXTMETRICA local_3c;
  
  *(int *)(param_1 + 0x2d627c) = param_2;
  *(UINT *)(param_1 + 0x2d6280) = param_3;
  puVar1 = (undefined4 *)operator_new(param_2 * param_3 * 4);
  *(undefined4 **)(param_1 + 0x2d6284) = puVar1;
  for (uVar2 = param_2 * param_3 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined1 *)puVar1 = 0;
    puVar1 = (undefined4 *)((int)puVar1 + 1);
  }
  DAT_0083f88c = CreateCompatibleBitmap(DAT_0083f880,param_2,param_3);
  SelectObject(DAT_0083f874,DAT_0083f88c);
  _DAT_0083f814 = param_2;
  _DAT_0083f818 = -param_3;
  _DAT_0083f810 = 0x28;
  _DAT_0083f81c = 1;
  _DAT_0083f81e = 0x20;
  _DAT_0083f820 = 0;
  SetDIBits(DAT_0083f874,DAT_0083f88c,0,param_3,*(void **)(param_1 + 0x2d6284),
            (BITMAPINFO *)&DAT_0083f810,0);
  if (*param_4 == '\0') {
    param_4 = "arial";
  }
  DAT_0083f8a0 = CreateFontA(-param_6,param_5,0,0,(-(uint)((param_7 & 2) != 0) & 300) + 400,
                             param_7 & 1,0,0,1,4,0,((param_7 & 4) != 0) + 3,0,param_4);
  SetBkMode(DAT_0083f874,1);
  SelectObject(DAT_0083f880,DAT_0083f8a0);
  SelectObject(DAT_0083f874,DAT_0083f8a0);
  SelectObject(DAT_0083f874,DAT_0083f88c);
  SetTextColor(DAT_0083f874,0xffffff);
  GetTextMetricsA(DAT_0083f874,&local_3c);
  return local_3c.tmHeight;
}


/* ---- FUN_008020cf @ 008020cf ---- */

LONG FUN_008020cf(LPCSTR param_1,int param_2)

{
  char cVar1;
  tagSIZE local_c;
  
  if (param_2 == -1) {
    param_2 = 0;
    cVar1 = *param_1;
    while (cVar1 != '\0') {
      param_2 = param_2 + 1;
      cVar1 = param_1[param_2];
    }
  }
  GetTextExtentPoint32A(DAT_0083f874,param_1,param_2,&local_c);
  return local_c.cx;
}


/* ---- FUN_00802105 @ 00802105 ---- */

void FUN_00802105(int param_1,int param_2,LPCSTR param_3,UINT param_4)

{
  char cVar1;
  
  if (param_4 == 0xffffffff) {
    param_4 = 0;
    cVar1 = *param_3;
    while (cVar1 != '\0') {
      param_4 = param_4 + 1;
      cVar1 = param_3[param_4];
    }
  }
  ExtTextOutA(DAT_0083f874,param_1,param_2,0,(RECT *)0x0,param_3,param_4,(INT *)0x0);
  return;
}


/* ---- FUN_0080213c @ 0080213c ---- */

undefined4 __fastcall FUN_0080213c(int param_1)

{
  GetDIBits(DAT_0083f874,DAT_0083f88c,0,*(UINT *)(param_1 + 0x2d6280),
            *(LPVOID *)(param_1 + 0x2d6284),(LPBITMAPINFO)&DAT_0083f810,0);
  SelectObject(DAT_0083f874,DAT_0083f8bc);
  DeleteObject(DAT_0083f88c);
  return *(undefined4 *)(param_1 + 0x2d6284);
}


/* ---- FUN_0080218c @ 0080218c ---- */

uint __thiscall FUN_0080218c(char *param_1,int param_2,int param_3,uint *param_4,uint param_5)

{
  uint uVar1;
  
  uVar1 = (uint)*param_1;
  if (uVar1 == param_5) {
    uVar1 = (param_3 + -1 + *(int *)(param_1 + 8)) / param_3;
    param_3 = (param_2 + uVar1) * param_3;
    if (param_3 - *(int *)(param_1 + 4) == 0 || param_3 < *(int *)(param_1 + 4)) {
      *(int *)(param_1 + 8) = param_3;
      *param_4 = uVar1;
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
      return CONCAT31((int3)(uVar1 >> 8),1);
    }
  }
  return uVar1 & 0xffffff00;
}


/* ---- FUN_008021c8 @ 008021c8 ---- */

void __fastcall FUN_008021c8(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0x3c; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[0x3a] = 0x3f800000;
  param_1[0x3b] = 0x3f800000;
  param_1[0x35] = 0xffffffff;
  iVar1 = 4;
  *param_1 = 0x300;
  param_1[0x39] = 1;
  param_1 = param_1 + 0x1c;
  do {
    *param_1 = 0xffffffff;
    param_1[0x14] = 0xffffffff;
    param_1[-4] = 0;
    param_1[-0x18] = 2;
    param_1 = param_1 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


/* ---- FUN_0080221c @ 0080221c ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0080221c(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = param_1;
  for (iVar2 = 0x5e; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  param_1[0xb] = 0x3f800000;
  param_1[9] = 0xffffffff;
  param_1[8] = 0x40a00000;
  param_1[10] = 0xff000000;
  FUN_00805a4d();
  FUN_00805a4d();
  uVar1 = _DAT_0081f100;
  param_1[0x5c] = _DAT_0081f100;
  param_1[0x5b] = 0x3e000000;
  param_1[0x36] = 0xff808080;
  param_1[0x57] = 0x3f800000;
  param_1[0x58] = 0x3f800000;
  param_1[0x59] = 0;
  param_1[0x5a] = 0;
  param_1[0x34] = 0;
  param_1[0x35] = uVar1;
  return;
}


/* ---- FUN_008022a7 @ 008022a7 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_008022a7(int param_1,float *param_2)

{
  float fVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x174);
  if (iVar2 == 0) {
    *param_2 = *(float *)(param_1 + 0x15c);
    param_2[1] = 0.0;
    param_2[2] = 0.0;
    param_2[3] = 0.0;
    fVar1 = *(float *)(param_1 + 0x160);
    param_2[4] = 0.0;
    param_2[5] = fVar1;
    param_2[6] = 0.0;
    param_2[7] = 0.0;
    fVar1 = *(float *)(param_1 + 0x164);
    param_2[9] = *(float *)(param_1 + 0x168);
    param_2[8] = fVar1;
    param_2[10] = 1.0;
    param_2[0xb] = 1.0;
    fVar1 = *(float *)(param_1 + 0x16c);
    param_2[0xc] = 0.0;
    param_2[0xd] = 0.0;
    param_2[0xe] = -fVar1;
    fVar1 = 0.0;
  }
  else {
    if (iVar2 == 1) {
      return;
    }
    if (iVar2 != 2) {
      return;
    }
    *param_2 = _DAT_0081f108 / (float)*(int *)(DAT_0083f868 + 0x204);
    param_2[1] = 0.0;
    param_2[2] = 0.0;
    param_2[3] = 0.0;
    fVar1 = _DAT_0081f104 / (float)*(int *)(DAT_0083f868 + 0x208);
    param_2[4] = 0.0;
    param_2[5] = fVar1;
    param_2[6] = 0.0;
    param_2[7] = 0.0;
    param_2[8] = 0.0;
    param_2[9] = 0.0;
    param_2[10] = 1.0;
    param_2[0xb] = 0.0;
    param_2[0xc] = -1.0;
    param_2[0xd] = 1.0;
    param_2[0xe] = 0.0;
    fVar1 = 1.0;
  }
  param_2[0xf] = fVar1;
  return;
}


/* ---- FUN_008023a5 @ 008023a5 ---- */

void __thiscall FUN_008023a5(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  param_1[1] = -1;
  *param_1 = param_2;
  iVar2 = param_2 * 0x68 + DAT_0083f868;
  iVar1 = *(int *)(iVar2 + 0x74);
  iVar2 = *(int *)(iVar2 + 0x70);
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = iVar2;
  param_1[5] = iVar1;
  param_1[6] = 3;
  param_1[7] = 0xff00000;
  return;
}


/* ---- FUN_008023e2 @ 008023e2 ---- */

void __thiscall FUN_008023e2(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = 0xffffffff;
  param_1[1] = param_2;
  param_1[6] = 3;
  param_1[7] = 0xff000000;
  param_1[5] = 0;
  param_1[4] = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  return;
}


/* ---- FUN_0080240e @ 0080240e ---- */

void __thiscall FUN_0080240e(int *param_1,uint param_2)

{
  int *in_EAX;
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = *param_1;
  piVar1 = param_1 + 2;
  *(uint *)*in_EAX = param_1[1] | param_2;
  *in_EAX = *in_EAX + 4;
  piVar2 = (int *)*in_EAX;
  if (1 < iVar3) {
    iVar3 = iVar3 + -1;
    do {
      *piVar2 = *piVar1;
      *in_EAX = *in_EAX + 4;
      piVar2 = (int *)*in_EAX;
      piVar1 = piVar1 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}


/* ---- FUN_00802444 @ 00802444 ---- */

void __fastcall FUN_00802444(uint param_1)

{
  undefined4 *puVar1;
  undefined4 *unaff_EBX;
  undefined4 unaff_ESI;
  
  puVar1 = (undefined4 *)*unaff_EBX;
  *puVar1 = 8;
  puVar1[1] = param_1 | 0x80010000;
  puVar1[2] = unaff_ESI;
  puVar1[3] = unaff_ESI;
  puVar1[4] = 7;
  puVar1[5] = param_1 | 0x80010000;
  puVar1[6] = param_1 | 0x80000000;
  puVar1[7] = 5;
  puVar1[8] = param_1 | 0x80070000;
  puVar1[9] = param_1 | 0x80000000;
  puVar1[10] = unaff_ESI;
  *unaff_EBX = puVar1 + 0xb;
  return;
}


/* ---- FUN_0080249c @ 0080249c ---- */

void FUN_0080249c(uint param_1)

{
  undefined4 *puVar1;
  undefined *puVar2;
  undefined4 uVar3;
  undefined4 *unaff_EDI;
  
  puVar1 = (undefined4 *)*unaff_EDI;
  puVar2 = (undefined *)(param_1 & 0xf00000);
  if (puVar2 < (undefined *)0x500001) {
    if (puVar2 == (undefined *)0x500000) {
LAB_00802547:
      *puVar1 = 0x16;
      uVar3 = 1;
      puVar1[1] = 1;
      puVar1[2] = 0x34;
      puVar1[3] = 1;
      puVar1[4] = 0xb9;
      puVar1[5] = 1;
      puVar1[6] = 0x38;
      puVar1[7] = 8;
      puVar1[8] = 0xbd;
      puVar1[9] = 8;
      puVar1[10] = 0x35;
      puVar1[0xb] = 1;
      puVar1[0xc] = 0xba;
      puVar1[0xd] = 1;
      puVar1[0xe] = 0x36;
      if ((param_1 & 0x800000) != 0) {
        puVar1[0xf] = 8;
        puVar1[0x10] = 0xbb;
        puVar1[0x11] = 7;
        puVar1[0x12] = 0x37;
        puVar1[0x13] = 1;
        puVar1 = puVar1 + 0x14;
        *puVar1 = 0xbc;
        goto LAB_00802657;
      }
      puVar1[0xf] = 1;
      puVar1[0x10] = 0xbb;
      puVar1[0x11] = 1;
      puVar1[0x12] = 0x37;
      puVar1[0x13] = 7;
      puVar1[0x14] = 0xbc;
      puVar1 = puVar1 + 0x15;
      *puVar1 = 8;
    }
    else {
      if ((((puVar2 == (undefined *)0x100000) || (puVar2 == (undefined *)0x200000)) ||
          (puVar2 == (undefined *)0x300000)) || (puVar2 == (undefined *)0x400000))
      goto LAB_0080265d;
LAB_00802517:
      *puVar1 = 0x34;
      puVar1[1] = 0;
      puVar1[2] = 0xb9;
      puVar1[3] = 0;
      puVar1[4] = 0x38;
      puVar1 = puVar1 + 5;
      *puVar1 = 8;
    }
  }
  else {
    if (puVar2 != (undefined *)0x600000) {
      if ((puVar2 == &DAT_00900000) || (puVar2 == &DAT_00a00000)) goto LAB_0080265d;
      if (puVar2 == &DAT_00d00000) goto LAB_00802547;
      goto LAB_00802517;
    }
    *puVar1 = 0x34;
    puVar1[1] = 1;
    puVar1[2] = 0xb9;
    puVar1[3] = 0;
    puVar1[4] = 0x38;
    puVar1[5] = 3;
    puVar1[6] = 0x35;
    uVar3 = 2;
    puVar1[7] = 2;
    puVar1[8] = 0x36;
    puVar1[9] = 2;
    puVar1 = puVar1 + 10;
    *puVar1 = 0x37;
LAB_00802657:
    puVar1 = puVar1 + 1;
    *puVar1 = uVar3;
  }
  puVar1 = puVar1 + 1;
LAB_0080265d:
  *unaff_EDI = puVar1;
  return;
}


/* ---- FUN_00802664 @ 00802664 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall FUN_00802664(int param_1,uint *param_2)

{
  float fVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  int iVar9;
  undefined4 *puVar10;
  uint *puVar11;
  bool bVar12;
  undefined4 local_27c;
  undefined4 local_278;
  undefined4 local_274;
  undefined4 local_270;
  uint local_26c [24];
  undefined4 local_20c [8];
  float local_1ec;
  int local_1ac [5];
  undefined4 local_198;
  undefined4 local_194;
  undefined4 local_18c;
  undefined4 local_184;
  undefined4 local_180;
  uint local_17c [4];
  uint auStack_16c [4];
  uint auStack_15c [15];
  uint local_120;
  float local_fc;
  int aiStack_bc [12];
  uint local_8c [11];
  uint *local_60;
  int local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c [4];
  uint *local_3c;
  uint local_38;
  uint *local_34;
  uint local_30;
  uint local_2c;
  int local_28;
  uint *local_24;
  uint *local_20;
  uint *local_1c;
  uint *local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  undefined4 *local_8;
  
  puVar3 = local_17c;
  for (iVar4 = 0x3c; fVar1 = local_fc, iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar3 = *param_2;
    param_2 = param_2 + 1;
    puVar3 = puVar3 + 1;
  }
  local_5c = param_1;
  local_30 = local_17c[2] & 7;
  if ((local_17c[2] & 7) == 6) {
    if (_DAT_0081f2a8 <= local_fc) {
      local_fc = 16.0;
      if (_DAT_0081f2a4 <= fVar1) {
        local_fc = 32.0;
      }
    }
    else {
      local_fc = 8.0;
    }
  }
  puVar3 = local_17c;
  puVar11 = local_26c;
  for (iVar4 = 0x3c; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar11 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar11 = puVar11 + 1;
  }
  iVar4 = 0;
  do {
    piVar5 = local_1ac + iVar4;
    iVar4 = iVar4 + 1;
    *piVar5 = (*piVar5 == -1) - 2;
  } while (iVar4 < 4);
  puVar10 = local_20c;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  local_184 = 0;
  local_180 = 0;
  local_198 = 0;
  local_194 = 0;
  local_18c = 0;
  local_1ec = local_fc;
  local_28 = 0;
  puVar3 = (uint *)(param_1 + 0x50280);
  do {
    if (0 < (int)puVar3[-1]) {
      iVar4 = 0x3c;
      bVar12 = true;
      puVar11 = puVar3;
      puVar8 = local_26c;
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        bVar12 = *puVar11 == *puVar8;
        puVar11 = puVar11 + 1;
        puVar8 = puVar8 + 1;
      } while (bVar12);
      if (bVar12) {
        piVar5 = (int *)(local_28 * 0x50c + 0x5027c + param_1);
        *piVar5 = *piVar5 + 1;
        return local_28;
      }
    }
    local_28 = local_28 + 1;
    puVar3 = puVar3 + 0x143;
  } while (local_28 < 0x800);
  local_24 = (uint *)0x0;
  local_28 = 0;
  piVar5 = (int *)(param_1 + 0x5027c);
  do {
    if (*piVar5 == 0) {
      local_24 = (uint *)(local_28 * 0x50c + 0x5027c + param_1);
      break;
    }
    local_28 = local_28 + 1;
    piVar5 = piVar5 + 0x143;
  } while (local_28 < 0x800);
  puVar11 = local_24;
  local_24[0x142] = 0;
  local_3c = local_24 + 0x142;
  local_60 = local_24 + 0x141;
  *local_60 = 0;
  puVar8 = local_26c;
  puVar3 = local_24;
  for (iVar4 = 0x3c; puVar3 = puVar3 + 1, iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar3 = *puVar8;
    puVar8 = puVar8 + 1;
  }
  local_24[0x3e] = 0xffffffff;
  local_24[0x3f] = 0xffffffff;
  local_24[0x40] = 0xffffffff;
  local_20 = local_24 + 0x3d;
  *local_20 = 0xffffffff;
  puVar3 = local_8c;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar3 = 0xffffffff;
    puVar3 = puVar3 + 1;
  }
  uVar7 = 1;
  *puVar11 = 1;
  puVar11[0x41] = 0xf;
  local_10 = 0;
  local_8 = (undefined4 *)0x0;
  local_c = 0;
  puVar11[0x42] = local_17c[0] & 1;
  puVar11[0x43] = 0x19;
  puVar11[0x44] = ~(local_17c[0] >> 7) & 1 | 4;
  puVar11[0x45] = 0x18;
  puVar11[0x46] = 0x80;
  puVar11[0x47] = 7;
  puVar11[0x48] = 1;
  puVar11[0x49] = 0xe;
  puVar11[0x4a] = local_17c[0] >> 8 & 1;
  puVar11[0x4b] = 0x17;
  if ((local_17c[0] & 0x200) == 0) {
    uVar6 = 8;
  }
  else {
    uVar6 = (-(uint)((local_17c[0] & 0x40000) != 0) & 0xfffffffe) + 4;
  }
  puVar11[0x4c] = uVar6;
  puVar11[0x4d] = 0x16;
  if ((local_17c[0] & 2) == 0) {
    uVar7 = ~(local_17c[0] >> 2) & 1 | 2;
  }
  puVar11[0x4e] = uVar7;
  puVar11[0x4f] = 0xa8;
  puVar11[0x50] = (-(uint)((local_17c[0] & 0x20) != 0) & 0xfffffff1) + 0xf;
  puVar11[0x51] = 0xaf;
  puVar11[0x52] = 0;
  puVar11[0x53] = 0xc3;
  puVar11[0x54] = 0;
  puVar11[0x55] = 0x1c;
  uVar7 = 0;
  puVar11[0x56] = 0;
  puVar11[0x57] = 0x88;
  puVar11[0x58] = 1;
  puVar11[0x59] = 0x10b;
  puVar11[0x5a] = 0;
  puVar11[0x5b] = 299;
  puVar11[0x5c] = 1;
  puVar11[0x5d] = 0x14b;
  puVar11[0x5e] = 2;
  puVar11[0x5f] = 0x16b;
  puVar11[0x60] = 3;
  puVar11[0x61] = 0x1b;
  local_34 = puVar11 + 0x62;
  if ((local_17c[0] & 0xf000) != 0) {
    *local_34 = 1;
    puVar11[99] = 0x13;
    iVar4 = (local_17c[0] >> 0xc & 0xf) * 4;
    puVar11[100] = *(uint *)(&DAT_0081f280 + iVar4);
    puVar11[0x65] = 0x14;
    puVar11[0x66] = *(uint *)(&DAT_0081f25c + iVar4);
    puVar11[0x67] = 0xab;
    uVar7 = *(uint *)(&DAT_0081f238 + iVar4);
    local_34 = puVar11 + 0x68;
  }
  *local_34 = uVar7;
  local_34 = local_34 + 1;
  FUN_0080249c(local_17c[0]);
  local_14 = 0;
  param_2 = (uint *)0x0;
  local_1c = local_20;
  puVar3 = local_34;
  do {
    puVar11 = local_4c + (int)param_2;
    *puVar11 = 0xffffffff;
    puVar10 = local_8;
    local_20 = puVar11;
    if (aiStack_bc[(int)param_2] != -1) {
      uVar7 = auStack_16c[(int)param_2];
      local_2c = (int)local_8 << 5;
      *local_1c = (uint)param_2;
      *puVar11 = (uint)local_8;
      iVar9 = (int)puVar10 * 0x10;
      *puVar3 = iVar9 + 0x205;
      iVar4 = (uVar7 & 7) * 0x10;
      puVar3[1] = *(uint *)(&DAT_0081f1b8 + iVar4);
      puVar3[2] = iVar9 + 0x206;
      puVar3[3] = *(uint *)(&DAT_0081f1bc + iVar4);
      local_8 = (undefined4 *)((int)local_8 + 1);
      local_1c = local_1c + 1;
      puVar3[4] = iVar9 + 0x207;
      puVar3[5] = *(uint *)(&DAT_0081f1c0 + iVar4);
      puVar3[6] = iVar9 + 0x201;
      uVar6 = CONCAT31((uint3)(uVar7 >> 8) & 1,0x80) >> 7;
      puVar3[7] = uVar6;
      puVar3[8] = iVar9 + 0x202;
      puVar3[9] = uVar6;
      if ((uVar7 & 0x10) != 0) {
        local_14 = 1;
      }
      puVar3[10] = local_2c + 0x118;
      puVar3[0xb] = uVar7 >> 6 & 0x100;
      puVar3 = puVar3 + 0xc;
    }
    param_2 = (uint *)((int)param_2 + 1);
  } while ((int)param_2 < 4);
  local_34 = puVar3;
  iVar4 = 0;
  do {
    local_c = local_c | *(uint *)(&DAT_0081f178 + (auStack_15c[iVar4] & 0xf) * 4);
    if ((auStack_15c[iVar4] & 0xff0) != 0) {
      local_c = local_c | 1 << ((byte)iVar4 & 0x1f);
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0xd);
  local_38 = (local_120 & 0xf) * 4;
  local_c = local_c | *(uint *)(&DAT_0081f178 + (local_120 >> 4 & 0xf) * 4) |
                      *(uint *)(&DAT_0081f178 + local_38);
  if ((((local_30 == 3) || (local_30 == 5)) || (local_30 == 6)) &&
     ((local_30 == 3 || (local_4c[1] != 0xffffffff)))) {
    local_c = local_c | 0x10;
  }
  _DAT_008400e8 = 0xfffe0101;
  _DAT_008400ec = 0x1f;
  _DAT_008400f0 = 0x80000000;
  _DAT_008400f4 = 0x900f0000;
  puVar10 = &DAT_008400f8;
  if ((local_17c[0] & 0x40000) == 0) {
    uVar7 = 1;
    if ((local_17c[0] & 0x10000) == 0) {
      uVar7 = 2;
      DAT_008400f8 = 0x1f;
      DAT_008400fc = 0x80000005;
      DAT_00840100 = 0x900f0001;
      puVar10 = &DAT_00840104;
    }
    if ((local_17c[0] & 0x20000) == 0) {
      *puVar10 = 0x1f;
      puVar10[1] = 0x80000003;
      puVar10[2] = 0x900f0002;
      puVar10[3] = 0x1f;
      puVar10[4] = 0x80000006;
      puVar10[5] = 0x900f0003;
      puVar10 = puVar10 + 6;
      uVar7 = 4;
    }
    if (local_14 != 0) {
      *puVar10 = 0x1f;
      puVar10[1] = 0x80010005;
      puVar10[2] = uVar7 | 0x900f0000;
      puVar10 = puVar10 + 3;
      local_14 = uVar7;
      uVar7 = uVar7 + 1;
    }
    if ((local_c & 0x800) != 0) {
      *puVar10 = 0x1f;
      puVar10[1] = 0x80000003;
      puVar10[2] = uVar7 | 0x900f0000;
      puVar10[3] = 5;
      puVar10[4] = 0xd00f0000;
      puVar10[5] = uVar7 | 0x90e40000;
      puVar10[6] = 0xa0ff0013;
      puVar10 = puVar10 + 7;
    }
    *puVar10 = 1;
    puVar10[1] = 0x800f0003;
    puVar10[2] = 0x90e40000;
    puVar10 = puVar10 + 3;
  }
  else {
    DAT_00840100 = 0x90e40000;
    DAT_00840120 = 0x90e40000;
    DAT_008400f8 = 5;
    DAT_008400fc = 0x800f0003;
    DAT_00840104 = 0x90ff0000;
    DAT_00840108 = 2;
    DAT_0084010c = 0x800f0000;
    DAT_00840110 = 0xa0ff0014;
    DAT_00840114 = 0x91ff0000;
    DAT_00840118 = 2;
    DAT_0084011c = 0x800f0001;
    DAT_00840124 = 0xa1e40018;
    DAT_00840128 = 4;
    DAT_0084012c = 0x800f0003;
    DAT_00840130 = 0x80e40001;
    DAT_00840134 = 0x80e40000;
    DAT_00840138 = 0x80e40003;
    puVar10 = &DAT_0084013c;
  }
  *puVar10 = 0x14;
  puVar10[1] = 0xc00f0000;
  puVar10[2] = 0x80e40003;
  puVar10[3] = 0xa0e40008;
  puVar3 = puVar10 + 4;
  if ((local_17c[0] & 0x20000) == 0) {
    *puVar3 = 5;
    puVar10[5] = 0x80070008;
    puVar10[6] = 0x90e40002;
    puVar10[7] = 0xa0ff0013;
    puVar10[8] = 5;
    puVar10[9] = 0x8004000a;
    puVar10[10] = 0x90ff0002;
    puVar10[0xb] = 0xa0ff0013;
    puVar10[0xc] = 5;
    puVar10[0xd] = 0x8003000a;
    puVar10[0xe] = 0x90e40003;
    puVar10[0xf] = 0xa0ff0013;
    puVar10[0x10] = 5;
    puVar10[0x11] = 0x80070009;
    puVar10[0x12] = 0x80c90008;
    puVar10[0x13] = 0x80d2000a;
    puVar10[0x14] = 4;
    puVar10[0x15] = 0x80070009;
    puVar10[0x16] = 0x81d20008;
    puVar10[0x17] = 0x80c9000a;
    puVar10[0x18] = 0x80e40009;
    puVar3 = puVar10 + 0x19;
  }
  param_2 = (uint *)0x0;
  do {
    uVar7 = local_10;
    if (((&DAT_0081f168)[(int)param_2] & local_c) != 0) {
      local_10 = local_10 + 1;
      local_8c[(int)param_2] = uVar7;
      local_20 = (uint *)auStack_16c[(int)param_2];
      uVar7 = 0x90e40001;
      if (((uint)local_20 & 0x10) != 0) {
        uVar7 = local_14 | 0x90e40000;
      }
      if (param_2 == (uint *)0x2) {
        if ((local_17c[1] & 0x30) == 0x10) {
          *puVar3 = 0x18;
          puVar3[1] = 0x80030001;
          puVar3[2] = 0x80e40008;
          puVar3[3] = 0xa0e40004;
          puVar3 = puVar3 + 4;
LAB_00802edc:
          *puVar3 = 4;
          puVar3[1] = 0x80030001;
          puVar3[2] = 0x80e40001;
          puVar3[3] = 0xa0e40014;
          puVar3[4] = 0xa0000014;
          puVar3 = puVar3 + 5;
          uVar7 = 0x80e40001;
          goto LAB_00802f01;
        }
        if ((local_17c[1] & 0x30) == 0x20) {
          *puVar3 = 0x15;
          puVar3[1] = 0x80070001;
          puVar3[2] = 0x80e40003;
          puVar3[3] = 0xa0e40004;
          local_18 = puVar3 + 4;
          FUN_00802444();
          *local_18 = 0x17;
          local_18[1] = 0x80070001;
          local_18[2] = 0x80e40008;
          local_18[3] = 0xa0e40004;
          local_18[4] = 8;
          local_18[5] = 0x80080002;
          local_18[6] = 0x80e40000;
          local_18[7] = 0x80e40001;
          local_18[8] = 2;
          local_18[9] = 0x80080002;
          local_18[10] = 0x80ff0002;
          local_18[0xb] = 0x80ff0002;
          local_18[0xc] = 4;
          local_18[0xd] = 0x80070002;
          local_18[0xe] = 0x80ff0002;
          local_18[0xf] = 0x80e40001;
          local_18[0x10] = 0x81e40000;
          local_18 = local_18 + 0x11;
          FUN_00802444();
          puVar3 = local_18;
          goto LAB_00802edc;
        }
      }
      else {
LAB_00802f01:
        if (((param_2 == (uint *)0x3) && (uVar6 = local_17c[1] & 0x700, uVar6 != 0x100)) &&
           ((uVar6 != 0x200 && ((uVar6 != 0x300 && (uVar6 == 0x400)))))) {
          *puVar3 = 0x14;
          puVar3[1] = 0x800f0001;
          puVar3[2] = 0x80e40003;
          puVar3[3] = 0xa0e4001c;
          uVar7 = 0x80e40001;
          puVar3 = puVar3 + 4;
        }
      }
      uVar6 = (uint)local_20 & 0x3000;
      if (uVar6 == 0) {
        *puVar3 = 1;
        puVar3[1] = (-(uint)(((uint)local_20 & 0x4000) != 0) & 0xc0000) + 0x30000 |
                    local_8c[(int)param_2] | 0xe0000000;
        puVar3 = puVar3 + 2;
        *puVar3 = uVar7;
      }
      else if (uVar6 == 0x1000) {
        uVar6 = local_8c[(int)param_2];
        *puVar3 = 5;
        puVar3[1] = uVar6 | 0xe0030000;
        puVar3[2] = uVar7;
        puVar3 = puVar3 + 3;
        *puVar3 = *(uint *)(&DAT_0081f158 + (int)param_2 * 4) | 0xa000000d;
      }
      else {
        if (uVar6 != 0x2000) goto LAB_0080302d;
        *puVar3 = 9;
        puVar3[1] = 0x80010000;
        puVar3[2] = uVar7;
        puVar3[3] = 0xa0e40010;
        puVar3[4] = 9;
        uVar6 = local_8c[(int)param_2];
        puVar3[5] = 0x80020000;
        puVar3[6] = uVar7;
        puVar3[7] = 0xa0e40011;
        puVar3[8] = 1;
        puVar3[9] = uVar6 | 0xe0030000;
        puVar3 = puVar3 + 10;
        *puVar3 = 0x80e40000;
      }
      puVar3 = puVar3 + 1;
    }
LAB_0080302d:
    param_2 = (uint *)((int)param_2 + 1);
  } while ((int)param_2 < 4);
  _DAT_00821624 = local_4c[0] | 0xb0e40000;
  _DAT_00821628 = local_4c[1] | 0xb0e40000;
  local_2c = _DAT_00821628;
  _DAT_0082163c = local_4c[2] | 0xb0e40000;
  _DAT_00821640 = local_4c[3] | 0xb0e40000;
  local_20 = (uint *)_DAT_00821640;
  iVar4 = 0;
  puVar11 = &DAT_0083f8ec;
  local_10 = 0;
  _DAT_0083f8e8 = 0xffff0103;
  do {
    if ((*(uint *)((int)&DAT_0081f168 + iVar4) & local_c) != 0) {
      uVar7 = *(uint *)((int)local_4c + iVar4);
      *puVar11 = 0x42;
      puVar11[1] = uVar7 | 0xb00f0000;
      puVar11 = puVar11 + 2;
    }
    iVar4 = iVar4 + 4;
  } while (iVar4 < 0x10);
  if (local_30 != 0) {
    *puVar11 = 0x42;
    puVar11[1] = (uint)local_8 | 0xb00f0000;
    local_24[(int)local_8 + 0x3d] = 0xfffffffe;
    iVar4 = (int)local_8 * 0x10;
    *local_34 = iVar4 + 0x205;
    local_34[1] = 2;
    local_34[2] = iVar4 + 0x206;
    local_34[3] = 2;
    local_34[4] = iVar4 + 0x207;
    local_34[5] = 0;
    local_34[6] = iVar4 + 0x201;
    local_34[7] = 1;
    local_34[8] = iVar4 + 0x202;
    local_34[9] = 1;
    local_34[10] = (int)local_8 * 0x20 + 0x118;
    local_34[0xb] = 0;
    puVar11 = puVar11 + 2;
    local_34 = local_34 + 0xc;
  }
  local_14 = 0;
  local_c = 0;
  if ((local_30 == 5) || (param_2 = puVar11, local_30 == 6)) {
    local_18 = puVar3;
    if (local_30 == 6) {
      *puVar3 = 2;
      puVar3[1] = 0x80070003;
      puVar3[2] = 0xa0e40013;
      puVar3[3] = 0x91e40000;
      local_18 = puVar3 + 4;
      FUN_00802444();
    }
    param_2 = (uint *)0x0;
    do {
      *local_18 = 2;
      local_58 = (uint)param_2 | 0x80070000;
      local_18[1] = local_58;
      local_18[2] = (int)param_2 + 0x15U | 0xa0e40000;
      local_18[3] = 0x91e40000;
      local_18[4] = 8;
      local_50 = (uint)param_2 | 0x80080000;
      local_18[5] = local_50;
      uVar7 = (uint)param_2 | 0x80e40000;
      local_18[6] = uVar7;
      local_18[7] = uVar7;
      local_18[8] = 7;
      local_18[9] = 0x80080004;
      local_24 = (uint *)((uint)param_2 | 0x80ff0000);
      local_18[10] = (uint)local_24;
      local_18[0xb] = 5;
      local_54 = (uint)param_2 | 0x800f0000;
      local_18[0xc] = local_54;
      local_18[0xd] = uVar7;
      local_18[0xe] = 0x80ff0004;
      local_18[0xf] = 4;
      puVar8 = (uint *)(0x10000 << ((byte)param_2 & 0x1f));
      local_18[0x10] = (uint)puVar8 | 0x80000006;
      local_18[0x11] = (uint)local_24;
      local_18[0x12] = *(uint *)(&DAT_008215f8 + (int)param_2 * 8);
      local_18[0x13] = *(uint *)(&DAT_008215fc + (int)param_2 * 8);
      puVar3 = local_18 + 0x14;
      if (local_30 == 6) {
        *puVar3 = 2;
        local_18[0x15] = local_58;
        local_18[0x16] = uVar7;
        local_18[0x17] = 0x80e40007;
        local_18[0x18] = 8;
        local_18[0x19] = local_50;
        local_18[0x1a] = uVar7;
        local_18[0x1b] = uVar7;
        local_18[0x1c] = 7;
        local_18[0x1d] = local_50;
        local_18[0x1e] = (uint)local_24;
        local_18[0x1f] = 5;
        local_18[0x20] = local_54;
        local_18[0x21] = uVar7;
        local_18[0x22] = (uint)local_24;
        puVar3 = local_18 + 0x23;
      }
      *puVar3 = 8;
      puVar3[1] = (uint)puVar8 | 0x80000005;
      puVar3[2] = uVar7;
      puVar3[3] = 0x80e40008;
      local_18 = puVar3 + 4;
      param_2 = (uint *)((int)param_2 + 1);
    } while ((int)param_2 < 4);
    *local_18 = 4;
    puVar3[5] = 0x800f0005;
    puVar3[6] = 0x80e40005;
    puVar3[7] = 0xa0000014;
    puVar3[8] = 0xa0000014;
    puVar3[9] = 0xb;
    puVar3[10] = 0x800f0006;
    puVar3[0xb] = 0x80e40006;
    puVar3[0xc] = 0xa0aa0014;
    puVar3[0xd] = 5;
    puVar3[0xe] = 0x800f0005;
    puVar3[0xf] = 0x80e40005;
    puVar3[0x10] = 0x80e40006;
    puVar3[0x11] = 5;
    puVar3[0x12] = 0x800f0005;
    puVar3[0x13] = 0x80e40005;
    puVar3[0x14] = 0xa0e40019;
    puVar3[0x15] = 5;
    puVar3[0x16] = 0x80070000;
    puVar3[0x17] = 0x80e40000;
    puVar3[0x18] = 0x80000005;
    param_2 = (uint *)0x1;
    local_1c = (uint *)0x550000;
    puVar2 = puVar3 + 0x19;
    do {
      puVar3 = puVar2;
      puVar2 = local_1c;
      *puVar3 = 4;
      puVar3[1] = 0x80070000;
      puVar3[2] = (uint)param_2 | 0x80e40000;
      local_1c = local_1c + 0x154000;
      puVar3[3] = (uint)puVar2 | 0x80000005;
      puVar3[4] = 0x80e40000;
      param_2 = (uint *)((int)param_2 + 1);
      puVar2 = puVar3 + 5;
    } while ((int)local_1c < 0x1540000);
    puVar3[5] = 8;
    puVar3[6] = 0x80080000;
    puVar3[7] = 0x80e40000;
    puVar3[8] = 0x80e40000;
    puVar3[9] = 7;
    puVar3[10] = 0x80080000;
    puVar3[0xb] = 0x80ff0000;
    puVar3[0xc] = 5;
    puVar3[0xd] = 0x800f0000;
    puVar3[0xe] = 0x80e40000;
    puVar3[0xf] = 0x80ff0000;
    puVar3[0x10] = 0x17;
    puVar3[0x11] = (uint)(local_8 + -0x8000000) | 0x70000;
    puVar3[0x12] = 0x80e40000;
    puVar3[0x13] = 0x80e40008;
    puVar3[0x14] = 1;
    puVar3[0x15] = 0xd00f0000;
    puVar3[0x16] = 0x801b0006;
    puVar3[0x17] = 5;
    puVar3[0x18] = 0xd00f0001;
    puVar3[0x19] = 0x80ff0006;
    puVar3[0x1a] = 0xa0e40012;
    puVar3 = puVar3 + 0x1b;
    local_18 = puVar8;
    if (local_30 == 5) {
      *puVar11 = 1;
      puVar11[1] = 0x80070000;
      puVar11[2] = 0x90e40001;
      puVar11[3] = 0x40000005;
      puVar11[4] = 0x80080000;
      puVar11[5] = (uint)local_20;
      puVar11[6] = 0x90e40000;
      puVar11[7] = 5;
      puVar11[8] = 0x80070001;
      puVar11[9] = (uint)local_20;
      puVar11[10] = 0x90e40000;
      puVar11[0xb] = 0x40000005;
      puVar11[0xc] = 0x80080001;
      puVar11[0xd] = local_4c[3] | 0xb0aa0000;
      puVar11[0xe] = 0x90aa0000;
      puVar11[0xf] = 4;
      puVar11[0x10] = 0x80070000;
      puVar11[0x11] = 0xa0e40000;
      puVar11[0x12] = 0x80ff0000;
      puVar11[0x13] = 0x80e40000;
      puVar11[0x14] = 8;
      puVar11[0x15] = 0x80070001;
      puVar11[0x16] = 0x80e40001;
      puVar11[0x17] = 0xa0e40004;
      puVar11[0x18] = 4;
      puVar11[0x19] = 0x80070000;
      puVar11[0x1a] = 0xa0e40001;
      puVar11[0x1b] = 0x80ff0001;
      puVar11[0x1c] = 0x80e40000;
      puVar11[0x1d] = 0x40000001;
      puVar11[0x1e] = 0x80080000;
      puVar11[0x1f] = 0x80aa0001;
      puVar11[0x20] = 4;
      puVar11[0x21] = 0x80070000;
      puVar11[0x22] = 0xa0e40002;
      puVar11[0x23] = 0x80ff0000;
      puVar11[0x24] = 0x80e40000;
      puVar11[0x25] = 8;
      puVar11[0x26] = 0x80170001;
      if (local_4c[1] == 0xffffffff) {
        puVar11[0x27] = 0xa0e40003;
      }
      else {
        puVar11[0x27] = local_2c;
      }
      puVar11[0x28] = (uint)local_8 | 0xb4e40000;
      puVar11[0x29] = 5;
      puVar11[0x2a] = 0x80070000;
      puVar11[0x2b] = 0x80e40000;
      puVar11[0x2c] = 0x80e40001;
      param_2 = puVar11 + 0x2d;
    }
    else {
      *puVar11 = 8;
      puVar11[1] = 0x80170000;
      if (local_4c[1] == 0xffffffff) {
        puVar11[2] = 0xa0e40003;
      }
      else {
        puVar11[2] = local_2c;
      }
      fVar1 = _DAT_0081f154;
      puVar11[3] = (uint)local_8 | 0xb4e40000;
      puVar11[4] = 0x40000005;
      puVar11[5] = 0x80080001;
      puVar11[6] = (uint)local_20;
      puVar11[7] = 0x90e40000;
      puVar11[8] = 5;
      puVar11[9] = 0x80070001;
      puVar11[10] = (uint)local_20;
      puVar11[0xb] = 0x90e40000;
      puVar11[0xc] = 0x40000005;
      puVar11[0xd] = 0x80080000;
      puVar11[0xe] = 0x80aa0000;
      puVar11[0xf] = 0x80aa0000;
      puVar11[0x10] = 8;
      puVar11[0x11] = 0x80070000;
      puVar11[0x12] = 0x80e40001;
      puVar11[0x13] = 0xa0e40000;
      puVar8 = puVar11 + 0x14;
      if (fVar1 < local_fc) {
        *puVar8 = 0x40000005;
        puVar11[0x15] = 0x80080000;
        puVar11[0x16] = 0x80e40000;
        puVar11[0x17] = 0x80e40000;
        puVar8 = puVar11 + 0x18;
      }
      *puVar8 = 5;
      puVar8[1] = 0x80070001;
      puVar8[2] = 0x80ff0000;
      puVar8[3] = 0x80ff0000;
      puVar8[4] = 0x40000004;
      puVar8[5] = 0x80080001;
      puVar8[6] = 0x80e40001;
      puVar8[7] = 0xa0e40000;
      puVar8[8] = 0x80aa0000;
      puVar8[9] = 5;
      puVar8[10] = 0x80070001;
      puVar8[0xb] = 0x80e40001;
      puVar8[0xc] = 0x80e40001;
      puVar11 = puVar8 + 0xd;
      if ((local_4c[1] != 0xffffffff) && ((local_17c[1] & 0x80) != 0)) {
        *puVar11 = 0x40000005;
        puVar8[0xe] = 0x80080001;
        puVar8[0xf] = 0x80e40001;
        puVar8[0x10] = local_2c;
        puVar11 = puVar8 + 0x11;
      }
      if (local_fc <= _DAT_0081f150) {
        *puVar11 = 1;
        puVar11 = puVar11 + 1;
        *puVar11 = 0x80070000;
      }
      else {
        *puVar11 = 5;
        puVar11[1] = 0x80070000;
        puVar11 = puVar11 + 2;
        *puVar11 = 0x80e40001;
      }
      puVar11[1] = 0x80e40001;
      puVar11[2] = 5;
      puVar11[3] = 0x80070000;
      puVar11[4] = 0x80e40000;
      puVar11[5] = 0x80ff0001;
      param_2 = puVar11 + 6;
    }
  }
  local_270 = *(undefined4 *)(&DAT_0081f110 + local_38);
  local_20 = (uint *)local_270;
  local_38 = (int)local_120 >> 4 & 0xf;
  local_274 = 0x80080000;
  if (local_38 == 0) {
    local_27c = 3;
    local_278 = 1;
  }
  else {
    local_27c = 4;
    local_278 = 5;
    local_26c[0] = *(uint *)(&DAT_0081f110 + local_38 * 4);
  }
  puVar11 = param_2;
  if (((local_30 == 5) || (local_30 == 6)) || ((local_17c[1] & 0x2000) != 0)) {
    FUN_0080240e(0x40000000);
  }
  else {
    local_18 = (uint *)0x0;
    local_8 = &local_27c;
    do {
      if (7 < (int)local_c) break;
      param_2 = (uint *)local_18[0x208586];
      if (param_2 != (uint *)0xffffffff) {
        local_24 = (uint *)((int)auStack_15c + (int)local_18);
        local_2c = *local_24 & 0xf;
        if ((local_2c != 0) && (((byte)*local_24 & 0xf0) != 0x90)) {
          param_2 = (uint *)(uint)(local_14 != 0x80e40001);
          *puVar11 = 5;
          puVar11[1] = (uint)param_2 | 0x80070000;
          puVar11[2] = local_18[0x208586];
          puVar11[3] = *(uint *)(&DAT_0081f110 + local_2c * 4);
          puVar11 = puVar11 + 4;
          param_2 = (uint *)((uint)param_2 | 0x80e40000);
        }
        uVar7 = *local_24 & 0xf0;
        if (uVar7 < 0x71) {
          if (uVar7 != 0x70) {
            if (uVar7 != 0x10) {
              if (uVar7 == 0x20) {
                *puVar11 = 2;
              }
              else {
                if (uVar7 != 0x30) {
                  if (((uVar7 == 0x40) || (uVar7 == 0x50)) || (uVar7 == 0x60)) {
                    *puVar11 = 5;
                    puVar11[1] = (uVar7 - 0x31 >> 4) << 0x18 | 0x80070000;
                    puVar11[2] = local_14;
                    goto LAB_0080398a;
                  }
                  goto LAB_00803a32;
                }
                *puVar11 = 3;
              }
              puVar11[1] = 0x80070000;
              puVar8 = puVar11 + 2;
LAB_008039d3:
              *puVar8 = local_14;
              goto LAB_008039fd;
            }
            local_14 = (uint)param_2;
          }
        }
        else if (uVar7 == 0x80) {
          *puVar11 = 4;
          puVar11[1] = 0x80070000;
          puVar11[2] = local_14;
          puVar8 = puVar11 + 3;
          *puVar8 = (uint)param_2 | 0x6000000;
LAB_008039fd:
          puVar8[1] = (uint)param_2;
          param_2 = puVar8 + 2;
          local_c = local_c + 1;
LAB_00803a10:
          local_14 = 0x80e40000;
          FUN_0080240e(0x40000000);
          local_10 = local_10 + 1;
          local_8 = local_8 + 8;
          puVar11 = param_2;
        }
        else {
          if (uVar7 == 0x90) {
            uVar7 = *local_24;
            *puVar11 = 0x12;
            puVar11[1] = 0x80070000;
            puVar11[2] = *(uint *)(&DAT_0081f110 + (uVar7 & 0xf) * 4);
            puVar8 = puVar11 + 3;
            if ((uVar7 & 0x100) != 0) {
              *(byte *)((int)puVar11 + 0xb) = *(byte *)((int)puVar11 + 0xb) | 6;
            }
            goto LAB_008039d3;
          }
          if (uVar7 == 0xa0) {
            *puVar11 = 3;
            puVar11[1] = 0x80070000;
            puVar11[2] = (uint)param_2;
            param_2 = (uint *)local_14;
LAB_0080398a:
            puVar11[3] = (uint)param_2;
            param_2 = puVar11 + 4;
            local_c = local_c + 1;
            local_14 = 0x80e40000;
            puVar11 = param_2;
            if ((int)local_10 < 1) goto LAB_00803a10;
          }
          else if (uVar7 == 0xb0) {
            *puVar11 = 8;
            puVar11[1] = 0x80070000;
            puVar8 = puVar11 + 2;
            *puVar8 = (uint)param_2;
            param_2 = (uint *)local_14;
            goto LAB_008039fd;
          }
        }
      }
LAB_00803a32:
      local_18 = local_18 + 1;
    } while ((int)local_18 < 0x34);
    if (local_14 != 0x80e40000) {
      *puVar11 = 1;
      puVar11[1] = 0x80070000;
      puVar11[2] = local_14;
      puVar11 = puVar11 + 3;
      FUN_0080240e(0x40000000);
      local_10 = local_10 + 1;
    }
    do {
    } while ((int)local_10 < 1);
  }
  *local_34 = 0xffffffff;
  local_34[1] = 0xffffffff;
  *local_60 = 0;
  *local_3c = 0;
  *puVar3 = 0xffff;
  puVar10 = (undefined4 *)(local_5c + 0x441fc);
  piVar5 = (int *)*puVar10;
  (**(code **)(*piVar5 + 0x16c))(piVar5,&DAT_008400e8,local_60);
  *puVar11 = 0xffff;
  piVar5 = (int *)*puVar10;
  (**(code **)(*piVar5 + 0x1a8))(piVar5,&DAT_0083f8e8,local_3c);
  return local_28;
}


/* ---- FUN_00803af3 @ 00803af3 ---- */

void FUN_00803af3(void)

{
  return;
}


/* ---- FUN_00803af6 @ 00803af6 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

LRESULT FUN_00803af6(HWND param_1,UINT param_2,WPARAM param_3,LPARAM param_4)

{
  uint uVar1;
  LRESULT LVar2;
  WPARAM WVar3;
  
  _DAT_0083f84c = param_1;
  if (param_2 == 0xf) {
    ValidateRect(param_1,(RECT *)0x0);
  }
  else if (param_2 != 0x10) {
    if (param_2 == 0x20) {
      SetCursor((HCURSOR)0x0);
      return 0;
    }
    if (param_2 == 0x100) {
      WVar3 = *(WPARAM *)(&DAT_00821138 + param_3 * 4);
      if (*(WPARAM *)(&DAT_00821138 + param_3 * 4) == 1) {
        WVar3 = param_3;
      }
      *(WPARAM *)(DAT_0083f868 + 0x23c + *(int *)(DAT_0083f868 + 0x238) * 4) = WVar3;
    }
    else if (param_2 == 0x101) {
      uVar1 = *(uint *)(&DAT_00821138 + param_3 * 4);
      if (*(uint *)(&DAT_00821138 + param_3 * 4) == 1) {
        uVar1 = param_3;
      }
      *(uint *)(DAT_0083f868 + 0x23c + *(int *)(DAT_0083f868 + 0x238) * 4) = uVar1 | 0x80000000;
    }
    else if (param_2 == 0x201) {
      *(uint *)(DAT_0083f868 + 700) = *(uint *)(DAT_0083f868 + 700) | 1;
      *(undefined4 *)(DAT_0083f868 + 0x23c + *(int *)(DAT_0083f868 + 0x238) * 4) = 0x10028;
    }
    else {
      if (param_2 != 0x202) goto LAB_00803bf1;
      *(uint *)(DAT_0083f868 + 700) = *(uint *)(DAT_0083f868 + 700) & 0xfffffffe;
      *(undefined4 *)(DAT_0083f868 + 0x23c + *(int *)(DAT_0083f868 + 0x238) * 4) = 0x80010028;
    }
    *(int *)(DAT_0083f868 + 0x238) = *(int *)(DAT_0083f868 + 0x238) + 1;
  }
LAB_00803bf1:
  LVar2 = DefWindowProcA(param_1,param_2,param_3,param_4);
  return LVar2;
}


/* ---- FUN_00803c05 @ 00803c05 ---- */

void __fastcall FUN_00803c05(int param_1)

{
  int *piVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined8 uVar7;
  undefined1 local_178 [137];
  byte local_ef;
  undefined4 local_48 [6];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_1c;
  undefined4 local_14;
  short *local_10;
  int *local_c;
  undefined4 *local_8;
  
  if (*(int *)(param_1 + 0x441f8) == 0) {
    uVar3 = (*DAT_0083f884)(0x1f);
    *(undefined4 *)(param_1 + 0x441f8) = uVar3;
  }
  *(undefined4 *)(param_1 + 0x44210) = 0x4b;
  *(undefined4 *)(param_1 + 0x68) = 0x4b;
  *(undefined4 *)(param_1 + 0x6c) = 0x15;
  puVar5 = local_48;
  for (iVar6 = 0xe; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  local_2c = *(undefined4 *)(param_1 + 0x5c);
  local_48[1] = *(undefined4 *)(param_1 + 0x230);
  local_48[2] = 0x15;
  local_48[0] = *(undefined4 *)(param_1 + 0x22c);
  *(undefined4 *)(param_1 + 0x70) = local_48[0];
  local_24 = 0;
  local_30 = 1;
  local_48[3] = 1;
  local_14 = 0x80000000;
  local_1c = 0;
  local_28 = 0;
  *(undefined4 *)(param_1 + 0x74) = local_48[1];
  (**(code **)(**(int **)(param_1 + 0x441f8) + 0x38))(*(int **)(param_1 + 0x441f8),0,1,local_178);
  piVar1 = (int *)(param_1 + 0x441fc);
  if (*piVar1 == 0) {
    local_8 = (undefined4 *)0x40;
    if ((*(byte *)(param_1 + 0x234) & 0x10) != 0) {
      local_8 = (undefined4 *)0x240;
    }
    (**(code **)(**(int **)(param_1 + 0x441f8) + 0x40))
              (*(int **)(param_1 + 0x441f8),0,1,*(undefined4 *)(param_1 + 0x5c),local_8,local_48,
               piVar1);
    local_8 = (undefined4 *)0xc;
    do {
      (**(code **)(*(int *)*piVar1 + 0x158))(*piVar1,local_8[0x208439],local_8 + 0x20843a);
      local_8 = local_8 + 3;
    } while (local_8 < (undefined4 *)0x54);
  }
  else {
    piVar4 = *(int **)(param_1 + 0x4422c);
    if (piVar4 != (int *)0x0) {
      (**(code **)(*piVar4 + 8))(piVar4);
      *(undefined4 *)(param_1 + 0x4422c) = 0;
    }
    piVar4 = *(int **)(param_1 + 0x44214);
    if (piVar4 != (int *)0x0) {
      (**(code **)(*piVar4 + 8))(piVar4);
      *(undefined4 *)(param_1 + 0x44214) = 0;
    }
    local_c = (int *)0x2;
    local_8 = (undefined4 *)(param_1 + 0x44218);
    do {
      (**(code **)(*(int *)*local_8 + 8))((int *)*local_8);
      puVar5 = local_8 + 1;
      local_c = (int *)((int)local_c + -1);
      *local_8 = 0;
      local_8 = puVar5;
    } while (local_c != (int *)0x0);
    piVar4 = (int *)(param_1 + 0x14078);
    iVar6 = 0x1000;
    local_c = (int *)0x0;
    do {
      uVar7 = CONCAT44(iVar6,piVar4);
      if (piVar4[-4] != 0) {
        if (2 < *piVar4) {
          uVar7 = Material_Add();
        }
        if (2 < *(int *)((int)uVar7 + 0x10)) {
          uVar7 = Material_Add();
        }
      }
      puVar5 = (undefined4 *)uVar7;
      puVar5[2] = 0;
      *puVar5 = 0;
      puVar5[6] = 0;
      puVar5[4] = 0;
      piVar4 = puVar5 + 0xc;
      iVar6 = (int)((ulonglong)uVar7 >> 0x20) + -1;
    } while (iVar6 != 0);
    local_c = (int *)(param_1 + 0xa078);
    local_8 = (undefined4 *)0x800;
    do {
      if (*local_c != 0) {
        (**(code **)(*(int *)*local_c + 8))((int *)*local_c);
      }
      iVar6 = Material_Add();
      local_c = (int *)(iVar6 + 0x14);
      local_8 = (undefined4 *)((int)local_8 + -1);
    } while (local_8 != (undefined4 *)0x0);
    local_8 = (undefined4 *)(param_1 + 0x2d4);
    local_c = (int *)0x400;
    do {
      if ((*(byte *)(local_8 + -2) & 1) != 0) {
        (**(code **)(*(int *)*local_8 + 8))((int *)*local_8);
        *local_8 = 0;
      }
      local_8 = local_8 + 7;
      local_c = (int *)((int)local_c + -1);
    } while (local_c != (int *)0x0);
    iVar6 = (**(code **)(*(int *)*piVar1 + 0x40))((int *)*piVar1,local_48);
    if (iVar6 < 0) {
      (**(code **)(*(int *)*piVar1 + 0x40))((int *)*piVar1,local_48);
      (**(code **)(*(int *)*piVar1 + 0x40))((int *)*piVar1,local_48);
    }
  }
  iVar6 = (**(code **)(*(int *)*piVar1 + 0x74))
                    ((int *)*piVar1,0x400,0x300,*(undefined4 *)(param_1 + 0x44210),0,0,0,
                     param_1 + 0x44214,0);
  if (iVar6 < 0) {
    (**(code **)(*(int *)*piVar1 + 0x74))
              ((int *)*piVar1,0x400,0x300,*(undefined4 *)(param_1 + 0x44210),0,0,0,param_1 + 0x44214
               ,0);
    (**(code **)(*(int *)*piVar1 + 0x74))
              ((int *)*piVar1,0x400,0x300,*(undefined4 *)(param_1 + 0x44210),0,0,0,param_1 + 0x44214
               ,0);
  }
  iVar6 = (**(code **)(*(int *)*piVar1 + 0x9c))((int *)*piVar1,*(undefined4 *)(param_1 + 0x44214));
  if (iVar6 < 0) {
    (**(code **)(*(int *)*piVar1 + 0x9c))((int *)*piVar1,*(undefined4 *)(param_1 + 0x44214));
    (**(code **)(*(int *)*piVar1 + 0x9c))((int *)*piVar1,*(undefined4 *)(param_1 + 0x44214));
  }
  if ((local_ef & 1) != 0) {
    *(uint *)(param_1 + 0x50) = *(uint *)(param_1 + 0x50) | 1;
  }
  FUN_00801573(0,1,0,0x200000);
  FUN_00801573(1,1,1,0x40000);
  FUN_00801573(2,0,1,0x18000);
  iVar6 = (**(code **)(**(int **)(param_1 + 0xa0a0) + 0x2c))
                    (*(int **)(param_1 + 0xa0a0),0,0x18000,&local_10,0);
  if (iVar6 < 0) {
    (**(code **)(**(int **)(param_1 + 0xa0a0) + 0x2c))
              (*(int **)(param_1 + 0xa0a0),0,0x18000,&local_10,0);
    (**(code **)(**(int **)(param_1 + 0xa0a0) + 0x2c))
              (*(int **)(param_1 + 0xa0a0),0,0x18000,&local_10,0);
  }
  local_8 = (undefined4 *)0x0;
  do {
    sVar2 = (short)((int)local_8 << 2);
    *local_10 = sVar2;
    local_10[1] = sVar2 + 1;
    local_10[2] = sVar2 + 2;
    local_10[3] = sVar2;
    local_10[4] = sVar2 + 2;
    local_10[5] = sVar2 + 3;
    local_10 = local_10 + 6;
    local_8 = (undefined4 *)((int)local_8 + 1);
  } while ((int)local_8 < 0x1555);
  iVar6 = (**(code **)(**(int **)(param_1 + 0xa0a0) + 0x30))(*(int **)(param_1 + 0xa0a0));
  if (iVar6 < 0) {
    (**(code **)(**(int **)(param_1 + 0xa0a0) + 0x30))(*(int **)(param_1 + 0xa0a0));
    (**(code **)(**(int **)(param_1 + 0xa0a0) + 0x30))(*(int **)(param_1 + 0xa0a0));
  }
  FUN_0080134e();
  (**(code **)(*(int *)*piVar1 + 0x10c))((int *)*piVar1,0,1,2);
  (**(code **)(*(int *)*piVar1 + 0x10c))((int *)*piVar1,0,2,2);
  (**(code **)(*(int *)*piVar1 + 0xe4))((int *)*piVar1,0x89,0);
  local_8 = (undefined4 *)(param_1 + 0x2c8);
  *(undefined4 *)(param_1 + 0x14) = 0;
  local_c = (int *)0x400;
  do {
    if (((*(byte *)(local_8 + 1) & 1) != 0) &&
       (iVar6 = (**(code **)(*(int *)*piVar1 + 0x5c))
                          (*piVar1,local_8[-1],*local_8,1,1,0x15,0,local_8 + 3,0), iVar6 < 0)) {
      (**(code **)(*(int *)*piVar1 + 0x5c))
                ((int *)*piVar1,local_8[-1],*local_8,1,1,0x15,0,local_8 + 3,0);
      (**(code **)(*(int *)*piVar1 + 0x5c))
                ((int *)*piVar1,local_8[-1],*local_8,1,1,0x15,0,local_8 + 3,0);
    }
    local_8 = local_8 + 7;
    local_c = (int *)((int)local_c + -1);
  } while (local_c != (int *)0x0);
  local_8 = (undefined4 *)(param_1 + 0x44218);
  local_c = (int *)0x2;
  do {
    (**(code **)(*(int *)*piVar1 + 0x90))((int *)*piVar1,0x10,0x10,0x15,0,local_8,0);
    local_8 = (undefined4 *)((int)local_8 + 4);
    local_c = (int *)((int)local_c + -1);
  } while (local_c != (int *)0x0);
  *(undefined4 *)(param_1 + 0x44070) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x44078) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x44074) = 0;
  *(undefined4 *)(param_1 + 0x2d6298) = 0;
  return;
}


/* ---- FUN_008040d8 @ 008040d8 ---- */

void __thiscall FUN_008040d8(int param_1,int param_2,int param_3)

{
  SHORT SVar1;
  DWORD DVar2;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  undefined4 local_10;
  int *local_c;
  int *local_8;
  
  DVar2 = timeGetTime();
  if (((int)(DAT_008408e8 + 0x1c2) < (int)DVar2) || (param_2 == param_3)) {
    DAT_008408e8 = DVar2;
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0xac))
              (*(int **)(param_1 + 0x441fc),0,0,1,0xff000000,0,0);
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0x38))(*(int **)(param_1 + 0x441fc),0,&local_c);
    (**(code **)(*local_c + 0x14))(local_c,0,0,&local_8);
    local_1c = 0x14;
    local_18 = 0x16c;
    local_14 = 0x3ec;
    local_10 = 0x194;
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0x8c))
              (*(int **)(param_1 + 0x441fc),local_8,&local_1c,0xffffffff);
    local_1c = 0x17;
    local_18 = 0x16f;
    local_14 = 0x3e9;
    local_10 = 0x191;
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0x8c))
              (*(int **)(param_1 + 0x441fc),local_8,&local_1c,0xff000000);
    local_1c = 0x1a;
    local_18 = 0x172;
    local_10 = 0x18e;
    if (param_3 < param_2) {
      param_2 = param_3;
    }
    local_14 = (param_2 * 0x3cb) / param_3 + 0x1b;
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0x8c))
              (*(int **)(param_1 + 0x441fc),local_8,&local_1c,0xffffffff);
    (**(code **)(*local_c + 8))(local_c);
    (**(code **)(*local_8 + 8))(local_8);
    (**(code **)(**(int **)(param_1 + 0x441fc) + 0x44))(*(int **)(param_1 + 0x441fc),0,0,0,0);
    SVar1 = GetAsyncKeyState(0x1b);
    if (SVar1 < 0) {
      (**(code **)(**(int **)(param_1 + 0x441fc) + 8))(*(int **)(param_1 + 0x441fc));
                    /* WARNING: Subroutine does not return */
      ExitProcess(0);
    }
  }
  return;
}


/* ---- FUN_00804243 @ 00804243 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00804243(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int local_c;
  int iStack_8;
  
  *(undefined1 *)(param_1 + 0xa064) = 1;
  local_c = param_1;
  iStack_8 = param_1;
  FUN_00805a4d();
  FUN_00805a4d();
  FUN_00805a4d();
  uVar3 = _DAT_0081f2ac;
  *(undefined4 *)(param_1 + 0x72c0) = _DAT_0081f2ac;
  *(undefined4 *)(param_1 + 0x72c4) = 0;
  *(undefined4 *)(param_1 + 0x72c8) = 0;
  *(undefined4 *)(param_1 + 0x72cc) = 0;
  *(undefined4 *)(param_1 + 0x72d0) = 0;
  *(undefined4 *)(param_1 + 0x72d4) = uVar3;
  *(undefined4 *)(param_1 + 0x72d8) = 0;
  *(undefined4 *)(param_1 + 0x72dc) = 0;
  *(undefined4 *)(param_1 + 0x72e0) = 0;
  *(undefined4 *)(param_1 + 0x72e4) = 0;
  *(undefined4 *)(param_1 + 0x72e8) = uVar3;
  *(undefined4 *)(param_1 + 0x72ec) = 0;
  *(undefined4 *)(param_1 + 0x72f0) = uVar3;
  *(undefined4 *)(param_1 + 0x72f4) = uVar3;
  *(undefined4 *)(param_1 + 0x72f8) = uVar3;
  *(undefined4 *)(param_1 + 0x72fc) = 0x3f800000;
  *(undefined1 *)(param_1 + 0x7300) = 0;
  *(undefined4 *)(param_1 + 0x7300) = 0;
  *(undefined4 *)(param_1 + 0x7304) = 0;
  if (*(int *)(param_1 + 0x14) != 0) {
    Sleep(100);
    iVar2 = (**(code **)(**(int **)(param_1 + 0x441fc) + 0xc))(*(int **)(param_1 + 0x441fc));
    if (iVar2 != -0x7789f797) {
      return;
    }
    FUN_00803c05();
    if (*(int *)(param_1 + 0x14) != 0) {
      return;
    }
  }
  iVar2 = FUN_00801c05();
  if (DAT_0082164c == -1) {
    DAT_0082164c = iVar2;
  }
  if (DAT_0082164c < iVar2) {
    DAT_0082164c = DAT_0082164c + (((iVar2 - DAT_0082164c) - 1U) / 10 + 1) * 10;
  }
  FUN_0081e8cb();
  FUN_0081e8cb();
  FUN_0081e8cb();
  (**(code **)(**(int **)(param_1 + 0x441fc) + 0x8c))
            (*(int **)(param_1 + 0x441fc),*(undefined4 *)(param_1 + 0x44218 + DAT_008408ec * 4),0,0)
  ;
  piVar1 = *(int **)(param_1 + 0x44218 + DAT_008408ec * 4);
  iVar2 = (**(code **)(*piVar1 + 0x34))(piVar1,&local_c,0,0x10);
  if (iVar2 < 0) {
    piVar1 = *(int **)(param_1 + 0x44218 + DAT_008408ec * 4);
    (**(code **)(*piVar1 + 0x34))(piVar1,&local_c,0,0x10);
    piVar1 = *(int **)(param_1 + 0x44218 + DAT_008408ec * 4);
    (**(code **)(*piVar1 + 0x34))(piVar1,&local_c,0,0x10);
  }
  piVar1 = *(int **)(param_1 + 0x44218 + DAT_008408ec * 4);
  (**(code **)(*piVar1 + 0x38))(piVar1);
  (**(code **)(**(int **)(param_1 + 0x441fc) + 0x44))(*(int **)(param_1 + 0x441fc),0,0,0,0);
  uVar3 = FUN_00801c05();
  *(undefined4 *)(param_1 + 0x2d6298) = uVar3;
  puVar4 = (undefined4 *)(param_1 + 0x140c4);
  iVar2 = 0xfff;
  do {
    puVar4[-4] = 0;
    *puVar4 = 0;
    puVar4 = puVar4 + 0xc;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  *(undefined4 *)(param_1 + 0x44068) = 1;
  *(undefined4 *)(param_1 + 0x4406c) = 1;
  *(undefined4 *)(param_1 + 0xa070) = *(undefined4 *)(param_1 + 0xa06c);
  *(undefined4 *)(param_1 + 0xa084) = *(undefined4 *)(param_1 + 0xa080);
  return;
}


/* ---- FUN_0080445b @ 0080445b ---- */

int __thiscall
FUN_0080445b(int param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5,
            undefined4 param_6,undefined4 param_7)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_8;
  
  puVar3 = (undefined4 *)(param_1 + 0x2c0);
  local_8 = 0;
  while (puVar3[3] != 0) {
    puVar3 = puVar3 + 7;
    local_8 = local_8 + 1;
    if (0x3ff < local_8) {
      return -1;
    }
  }
  puVar3[1] = param_2;
  puVar3[2] = param_3;
  puVar3[4] = param_4;
  puVar1 = (undefined4 *)(&DAT_00821650 + param_4 * 4);
  puVar3[5] = 0;
  *puVar3 = 1;
  puVar3[3] = 0x80;
  puVar3[6] = 0;
  if (param_5 != 0) {
    iVar2 = (**(code **)(**(int **)(param_1 + 0x441fc) + 0x5c))
                      (*(int **)(param_1 + 0x441fc),param_2,param_3,param_6,0,*puVar1,1,puVar3 + 5,0
                      );
    if (iVar2 < 0) {
      (**(code **)(**(int **)(param_1 + 0x441fc) + 0x5c))
                (*(int **)(param_1 + 0x441fc),puVar3[1],puVar3[2],param_6,0,*puVar1,1,puVar3 + 5,0);
      (**(code **)(**(int **)(param_1 + 0x441fc) + 0x5c))
                (*(int **)(param_1 + 0x441fc),puVar3[1],puVar3[2],param_6,0,*puVar1,1,puVar3 + 5,0);
    }
    FUN_008018c3(local_8,param_5,param_7);
    return local_8;
  }
  puVar3[3] = 0x81;
  iVar2 = (**(code **)(**(int **)(param_1 + 0x441fc) + 0x5c))
                    (*(int **)(param_1 + 0x441fc),param_2,param_3,1,1,*puVar1,0);
  if (-1 < iVar2) {
    return local_8;
  }
  (**(code **)(**(int **)(param_1 + 0x441fc) + 0x5c))
            (*(int **)(param_1 + 0x441fc),puVar3[1],puVar3[2],1,1,*puVar1,0,puVar3 + 5,0);
  (**(code **)(**(int **)(param_1 + 0x441fc) + 0x5c))
            (*(int **)(param_1 + 0x441fc),puVar3[1],puVar3[2],1,1,*puVar1,0,puVar3 + 5,0);
  return local_8;
}


/* ---- FUN_008045ad @ 008045ad ---- */

void FUN_008045ad(int *param_1)

{
  for (; *param_1 != -1; param_1 = param_1 + 2) {
    FUN_00801519(*param_1,param_1[1]);
  }
  return;
}


/* ---- FUN_008045d4 @ 008045d4 ---- */

void __thiscall FUN_008045d4(int param_1,int param_2)

{
  *(undefined4 *)(param_2 * 0x30 + 0x14068 + param_1) = 0;
  return;
}


/* ---- FUN_008045e9 @ 008045e9 ---- */

void __thiscall
FUN_008045e9(int param_1,int *param_2,int param_3,char param_4,int param_5,undefined4 param_6)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  
  piVar1 = param_2 + 1;
  if (param_4 == '\0') {
    cVar3 = FUN_0080218c(param_2[2],param_3,piVar1,param_5 + 1);
    *param_2 = param_5;
    if (cVar3 == '\0') {
      *(undefined4 *)(param_5 * 0x14 + param_1 + 0xa070) = 0;
      piVar2 = (int *)(param_1 + 0x44068 + param_5 * 4);
      *piVar2 = *piVar2 + 1;
      FUN_0080218c(param_2[2],param_3,piVar1,param_5 + 1);
    }
    param_2[3] = *(int *)(param_1 + 0x44068 + param_5 * 4);
    _param_4 = (-(uint)(*piVar1 != 0) & 0xfffff000) + 0x2000;
  }
  else {
    _param_4 = 3;
    do {
      cVar3 = FUN_0080218c(param_2[2],param_3,piVar1,param_5 + 1);
      if (cVar3 != '\0') break;
      _param_4 = _param_4 + 1;
    } while (_param_4 < 0x800);
    if (_param_4 == 0x800) {
      _param_4 = 3;
      pcVar4 = (char *)(param_1 + 0xa0a4);
      do {
        if (*pcVar4 == '\0') {
          FUN_00801573(_param_4,0,param_5,(-(uint)(param_5 != 0) & 0xffe40000) + 0x200000);
          FUN_0080218c(param_2[2],param_3,piVar1,param_5 + 1);
          break;
        }
        _param_4 = _param_4 + 1;
        pcVar4 = pcVar4 + 0x14;
      } while (_param_4 < 0x800);
    }
    iVar5 = _param_4;
    _param_4 = 0;
    *param_2 = iVar5;
  }
  piVar2 = *(int **)((*param_2 + 0x806) * 0x14 + param_1);
  iVar5 = (**(code **)(*piVar2 + 0x2c))
                    (piVar2,*piVar1 * param_3,param_2[2] * param_3,param_6,_param_4);
  if (iVar5 < 0) {
    piVar2 = *(int **)((*param_2 + 0x806) * 0x14 + param_1);
    (**(code **)(*piVar2 + 0x2c))(piVar2,*piVar1 * param_3,param_2[2] * param_3,param_6,_param_4);
    piVar2 = *(int **)((*param_2 + 0x806) * 0x14 + param_1);
    (**(code **)(*piVar2 + 0x2c))(piVar2,*piVar1 * param_3,param_2[2] * param_3,param_6,_param_4);
  }
  return;
}


/* ---- FUN_0080479f @ 0080479f ---- */

void __thiscall
FUN_0080479f(int param_1,int param_2,undefined4 param_3,int param_4,undefined4 *param_5,
            undefined4 *param_6,byte param_7)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)(param_2 * 0x30 + 0x14068 + param_1);
  *param_5 = 0;
  if (param_6 != (undefined4 *)0x0) {
    *param_6 = 0;
  }
  if ((param_7 & 1) != 0) {
    *(undefined4 *)(puVar1 + 0x10) = 0;
    *(undefined4 *)(puVar1 + 0x14) = 0;
    *(undefined4 *)(puVar1 + 0x18) = param_3;
    FUN_008045e9(puVar1 + 0x10,*(undefined4 *)(puVar1 + 8),
                 CONCAT31((int3)((uint)param_5 >> 8),*puVar1) & 0xffffff08,0,param_5);
    *(uint *)(puVar1 + 0xc) = *(uint *)(puVar1 + 0xc) | 1;
  }
  *(undefined4 *)(puVar1 + 0x20) = 0;
  *(undefined4 *)(puVar1 + 0x24) = 0;
  *(int *)(puVar1 + 0x28) = param_4;
  if (param_4 != 0) {
    FUN_008045e9(puVar1 + 0x20,2,CONCAT31((int3)((uint)param_4 >> 8),*puVar1) & 0xffffff10,1,param_6
                );
    *(uint *)(puVar1 + 0xc) = *(uint *)(puVar1 + 0xc) | 2;
  }
  return;
}


/* ---- FUN_00804821 @ 00804821 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __fastcall FUN_00804821(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 local_50 [4];
  undefined4 *local_40;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined2 uStack_1c;
  undefined4 *local_18;
  uint local_14;
  undefined4 *local_10;
  uint local_c;
  int *local_8;
  
  iVar1 = (*DAT_0083f840)(0,&DAT_0083f894,0);
  if ((-1 < iVar1) &&
     (iVar1 = (**(code **)(*DAT_0083f894 + 0x18))(DAT_0083f894,*(undefined4 *)(param_1 + 0x5c),2),
     -1 < iVar1)) {
    puVar3 = local_50;
    for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_50[0] = 0x24;
    local_50[1] = 1;
    local_50[2] = 0;
    local_40 = (undefined4 *)0x0;
    iVar1 = (**(code **)(*DAT_0083f894 + 0xc))(DAT_0083f894,local_50,&DAT_0083f8c8,0);
    if (-1 < iVar1) {
      uStack_1c = 0;
      local_24 = 0x2b110;
      local_28 = 0xac44;
      local_20 = 0x100004;
      local_2c = 0x20001;
      (**(code **)(*DAT_0083f8c8 + 0x38))(DAT_0083f8c8,&local_2c);
      puVar3 = local_50;
      for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      local_40 = &local_2c;
      local_50[0] = 0x24;
      local_50[1] = 0x18000;
      local_50[2] = 0x80000;
      iVar1 = (**(code **)(*DAT_0083f894 + 0xc))(DAT_0083f894,local_50,&local_8,0);
      if (-1 < iVar1) {
        iVar1 = (**(code **)*local_8)(local_8,&DAT_0081f0dc,&DAT_0083f890);
        (**(code **)(*local_8 + 8))(local_8);
        if (-1 < iVar1) {
          iVar1 = (**(code **)(*DAT_0083f890 + 0x2c))
                            (DAT_0083f890,0,0x80000,&local_18,&local_14,&local_10,&local_c,0);
          if (-1 < iVar1) {
            puVar3 = local_18;
            for (uVar2 = local_14 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
              *puVar3 = 0;
              puVar3 = puVar3 + 1;
            }
            for (uVar2 = local_14 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
              *(undefined1 *)puVar3 = 0;
              puVar3 = (undefined4 *)((int)puVar3 + 1);
            }
            puVar3 = local_10;
            for (uVar2 = local_c >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
              *puVar3 = 0;
              puVar3 = puVar3 + 1;
            }
            for (uVar2 = local_c & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
              *(undefined1 *)puVar3 = 0;
              puVar3 = (undefined4 *)((int)puVar3 + 1);
            }
            (**(code **)(*DAT_0083f890 + 0x4c))(DAT_0083f890,local_18,local_14,local_10,local_c);
          }
          DAT_0083f850 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
          if (DAT_0083f850 != (HANDLE)0x0) {
            InitializeCriticalSection((LPCRITICAL_SECTION)&DAT_0083f8a4);
            (**(code **)(*DAT_0083f890 + 0x30))(DAT_0083f890,0,0,1);
            DAT_0083f844 = 0;
            _DAT_0083f87c =
                 CreateThread((LPSECURITY_ATTRIBUTES)0x0,0x4000,FUN_00801c77,(LPVOID)0x0,0,
                              (LPDWORD)&DAT_0083f8d4);
            return _DAT_0083f87c != (HANDLE)0x0;
          }
        }
      }
    }
  }
  return false;
}


/* ---- FUN_008049fd @ 008049fd ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_008049fd(float param_1)

{
  undefined4 local_c;
  
  if (param_1 < _DAT_0081f2bc) {
    if ((!NAN(param_1) && !NAN(_DAT_0081f2b8)) &&
        param_1 < _DAT_0081f2b8 != (param_1 == _DAT_0081f2b8)) {
      param_1 = _DAT_0081f2b8;
    }
  }
  else {
    param_1 = 1.0;
  }
  local_c = (undefined4)(longlong)ROUND(param_1 * 0.6931472 * (float)_DAT_0081f2b0);
  return local_c;
}


/* ---- FUN_00804a47 @ 00804a47 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00804a47(int param_1,int param_2,undefined4 param_3,float param_4)

{
  int *piVar1;
  undefined4 uVar2;
  int extraout_ECX;
  int iVar3;
  int iVar4;
  undefined4 local_c;
  
  param_1 = param_2 * 0x28 + 0x7724 + param_1;
  if (0 < *(int *)(param_1 + 0x20)) {
    uVar2 = FUN_008049fd(param_3);
    local_c = (int)(longlong)ROUND(param_4 * _DAT_0081f2c0);
    if (local_c < 10000) {
      iVar4 = -10000;
      if (-10000 < local_c) {
        iVar4 = local_c;
      }
    }
    else {
      iVar4 = 10000;
    }
    iVar3 = (*(int *)(param_1 + 0x24) + 1) % extraout_ECX;
    *(int *)(param_1 + 0x24) = iVar3;
    piVar1 = *(int **)(param_1 + iVar3 * 4);
    (**(code **)(*piVar1 + 0x48))(piVar1);
    piVar1 = *(int **)(param_1 + *(int *)(param_1 + 0x24) * 4);
    (**(code **)(*piVar1 + 0x34))(piVar1,0);
    piVar1 = *(int **)(param_1 + *(int *)(param_1 + 0x24) * 4);
    (**(code **)(*piVar1 + 0x3c))(piVar1,uVar2);
    piVar1 = *(int **)(param_1 + *(int *)(param_1 + 0x24) * 4);
    (**(code **)(*piVar1 + 0x40))(piVar1,iVar4);
    piVar1 = *(int **)(param_1 + *(int *)(param_1 + 0x24) * 4);
    (**(code **)(*piVar1 + 0x30))(piVar1,0,0,0);
  }
  return;
}


/* ---- FUN_00804af1 @ 00804af1 ---- */

void __fastcall FUN_00804af1(int param_1)

{
  int extraout_EDX;
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)(param_1 + 0xc0);
  iVar2 = 4;
  do {
    FUN_00801308(*puVar1);
    puVar1 = (undefined4 *)(extraout_EDX + 4);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  FUN_00803af3(*(undefined4 *)(param_1 + 0xd4));
  return;
}


/* ---- FUN_00804b25 @ 00804b25 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00804b25(int param_1,int *param_2,int param_3,undefined4 *param_4,char param_5)

{
  float fVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  float *pfVar7;
  undefined4 *puVar8;
  undefined4 uVar9;
  float10 fVar10;
  float10 fVar11;
  undefined4 local_3a0 [16];
  undefined4 local_360 [16];
  undefined4 local_320 [16];
  undefined4 local_2e0 [16];
  undefined1 local_2a0 [64];
  undefined1 local_260 [80];
  undefined4 local_210;
  undefined4 local_20c;
  undefined4 local_208;
  undefined4 local_204;
  float local_200;
  float local_1fc;
  undefined4 local_1f8;
  undefined4 local_1f4;
  float local_1f0;
  float local_1ec;
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined4 local_19c;
  undefined4 local_198;
  undefined4 local_194;
  undefined4 local_190;
  undefined4 uStack_18c;
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined4 local_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  undefined4 local_154;
  float afStack_150 [4];
  float afStack_140 [24];
  undefined4 local_e0 [5];
  undefined4 local_cc;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a0 [7];
  undefined4 local_84;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined1 local_20 [16];
  int local_10;
  float local_c;
  int local_8;
  
  local_8 = param_1;
  if (param_4 == (undefined4 *)0x0) {
    param_4 = (undefined4 *)(param_1 + 0x44080);
  }
  else {
    FUN_008022a7(local_3a0);
    puVar6 = param_4 + 0x47;
    puVar8 = local_360;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
    FUN_008064d6();
    puVar6 = param_4 + 0x37;
    puVar8 = local_320;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
    FUN_008064d6();
    puVar6 = local_3a0;
    puVar8 = (undefined4 *)(param_1 + 0x9fe4);
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar6 = local_360;
    puVar8 = (undefined4 *)(param_1 + 0x9f24);
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar6 = local_320;
    puVar8 = (undefined4 *)(param_1 + 0x9f64);
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar6 = param_4;
    puVar8 = (undefined4 *)(param_1 + 0x44080);
    for (iVar5 = 0x5e; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
    FUN_00805c2c((undefined4 *)(param_1 + 0x9f64),(undefined4 *)(param_1 + 0x9f24));
  }
  if (param_2 != (int *)0xffffffff) {
    local_10 = (int)param_2 * 0x50c + 0x5027c + param_1;
    iVar5 = 0x80;
    fVar10 = (float10)fsin((float10)*(float *)(param_3 + 0xb4));
    fVar11 = (float10)fcos((float10)*(float *)(param_3 + 0xb4));
    puVar6 = local_2e0;
    for (; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    puVar6 = local_a0;
    for (iVar5 = 0x20; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    uVar4 = *(uint *)(param_3 + 8) & 7;
    puVar6 = param_4 + 0x37;
    puVar8 = local_2e0;
    for (iVar5 = 0x10; iVar3 = local_8, iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
    local_c = (float)fVar11;
    FUN_00805c2c(param_4 + 0x37,local_8 + 0x9f24);
    FUN_00805c2c(local_2a0,iVar3 + 0x9fe4);
    local_200 = local_c * *(float *)(param_3 + 0xac);
    local_210 = *(undefined4 *)(param_3 + 0x60);
    local_20c = *(undefined4 *)(param_3 + 100);
    local_208 = *(undefined4 *)(param_3 + 0x68);
    local_1fc = (float)fVar10 * *(float *)(param_3 + 0xb0);
    local_204 = *(undefined4 *)(param_3 + 0x6c);
    local_1f4 = *(undefined4 *)(param_3 + 0xb8);
    local_1e4 = *(undefined4 *)(param_3 + 0xbc);
    local_1f8 = 0;
    local_1f0 = -((float)fVar10 * *(float *)(param_3 + 0xac));
    local_1ec = local_c * *(float *)(param_3 + 0xb0);
    local_1e8 = 0;
    FUN_008063b2(param_3 + 0x88);
    FUN_0080648d();
    FUN_00806305(iVar3 + 0x9f24,param_4);
    FUN_00806305(iVar3 + 0x9f64,param_4 + 0x53);
    local_198 = 0;
    local_1a4 = 0x38000100;
    local_1a0 = 0x3f000000;
    local_194 = 0x3f800000;
    local_19c = 0xbf000000;
    local_190 = *param_4;
    uStack_18c = param_4[1];
    uStack_188 = param_4[2];
    uStack_184 = param_4[3];
    FUN_0080620b();
    FUN_008061df(local_8 + 0x9f64);
    FUN_00805cf1(*(undefined4 *)(param_3 + 0x70));
    FUN_00805cf1(*(undefined4 *)(param_3 + 0x74));
    local_160 = param_4[4];
    uStack_15c = param_4[5];
    uStack_158 = param_4[6];
    local_154 = 0;
    FUN_00805a4d();
    local_e0[0] = _DAT_0081f2ac;
    local_b0 = _DAT_0081f2ac;
    local_ac = _DAT_0081f2ac;
    local_cc = 0xbf000000;
    FUN_00805c2c(local_260,local_e0);
    if ((uVar4 == 5) || (uVar4 == 6)) {
      iVar5 = 0;
      pfVar7 = (float *)(param_4 + 0x15);
      do {
        FUN_00806305(local_8 + 0x9f64,pfVar7 + -9);
        if (pfVar7[-1] <= _DAT_0081f2c4) {
          fVar1 = 0.0;
        }
        else {
          fVar1 = -(*pfVar7 / pfVar7[-1]);
        }
        afStack_140[iVar5 * 2] = fVar1;
        afStack_140[iVar5 * 2 + 1] = *pfVar7;
        if (uVar4 == 5) {
          fVar1 = pfVar7[-3];
          if (pfVar7[-3] < pfVar7[-4]) {
            fVar1 = pfVar7[-4];
          }
          local_c = pfVar7[-5];
          if (fVar1 < local_c) {
            fVar1 = local_c;
          }
        }
        else {
          fVar1 = pfVar7[-2];
        }
        afStack_150[iVar5] = fVar1;
        iVar5 = iVar5 + 1;
        pfVar7 = pfVar7 + 10;
      } while (iVar5 < 4);
      FUN_00805cf1(*(undefined4 *)(param_3 + 0x70));
      FUN_00805da0(param_4 + 0x2e,local_20);
    }
    if ((uVar4 == 5) || (uVar4 == 6)) {
      FUN_00805cf1(*(undefined4 *)(param_3 + 0x70));
      FUN_00805da0(param_4 + 0x10,local_20);
      FUN_00805da0(param_4 + 0x1a,local_20);
      FUN_00805da0(param_4 + 0x24,local_20);
      if (uVar4 == 6) {
        local_a0[2] = local_84;
        local_a0[1] = local_74;
      }
      local_70 = 0x3f800000;
      local_6c = 0;
      local_68 = 0;
      local_64 = 0;
      local_60 = 0;
      local_5c = 0x3f800000;
      local_58 = 0;
      local_54 = 0;
    }
    else {
      FUN_00805cf1(*(undefined4 *)(param_3 + 0x70));
      FUN_00805cf1(*(undefined4 *)(param_3 + 0x74));
      FUN_00805cf1(*(undefined4 *)(param_3 + 0x78));
      FUN_00805cf1(*(undefined4 *)(param_3 + 0x7c));
    }
    local_40 = _DAT_0081f2ac;
    local_3c = 0xbf000000;
    local_38 = 0;
    local_34 = 0x3f800000;
    local_30 = 0x3f800000;
    local_2c = 0;
    local_28 = 0;
    local_24 = _DAT_0081f2ac;
    FUN_0080648d();
    FUN_0080648d();
    FUN_0080648d();
    FUN_0080648d();
    if (param_5 == '\0') {
      param_4 = (undefined4 *)0x0;
      param_2 = (int *)(local_10 + 0xf4);
      do {
        iVar3 = local_8;
        iVar5 = *param_2;
        uVar9 = 0;
        if (iVar5 == -2) {
          uVar9 = *(undefined4 *)(local_8 + 0x4422c);
        }
        else if ((((iVar5 == 0) || (iVar5 == 1)) || (iVar5 == 2)) || (iVar5 == 3)) {
          uVar9 = *(undefined4 *)(*(int *)(param_3 + 0xc0 + iVar5 * 4) * 0x1c + 0x2d4 + local_8);
        }
        iVar5 = (**(code **)(**(int **)(local_8 + 0x441fc) + 0x104))
                          (*(int **)(local_8 + 0x441fc),param_4,uVar9);
        if (iVar5 < 0) {
          piVar2 = *(int **)(iVar3 + 0x441fc);
          (**(code **)(*piVar2 + 0x104))(piVar2,param_4,uVar9);
          piVar2 = *(int **)(iVar3 + 0x441fc);
          (**(code **)(*piVar2 + 0x104))(piVar2,param_4,uVar9);
        }
        param_4 = (undefined4 *)((int)param_4 + 1);
        param_2 = param_2 + 1;
      } while ((int)param_4 < 4);
    }
    iVar3 = local_8;
    (**(code **)(**(int **)(local_8 + 0x441fc) + 0x178))
              (*(int **)(local_8 + 0x441fc),0,local_2e0,
               (-((*(uint *)(param_3 + 4) & 0x400) != 0) & 6U) + 0x1a);
    (**(code **)(**(int **)(iVar3 + 0x441fc) + 0x1b4))(*(int **)(iVar3 + 0x441fc),0,local_a0,8);
    iVar5 = local_10;
    if (param_5 == '\0') {
      FUN_008045ad(local_10 + 0x104);
      (**(code **)(**(int **)(iVar3 + 0x441fc) + 0x170))
                (*(int **)(iVar3 + 0x441fc),*(undefined4 *)(iVar5 + 0x504));
      (**(code **)(**(int **)(iVar3 + 0x441fc) + 0x1ac))
                (*(int **)(iVar3 + 0x441fc),*(undefined4 *)(iVar5 + 0x508));
    }
    *(undefined4 *)(iVar3 + 0x44238) = 1;
  }
  return;
}


/* ---- FUN_00805162 @ 00805162 ---- */

void FUN_00805162(uint param_1)

{
  undefined4 *puVar1;
  undefined4 local_408;
  uint local_404;
  undefined4 local_400 [254];
  undefined4 *local_8;
  
  local_408 = 0x16;
  if ((param_1 & 2) == 0) {
    local_404 = (uint)(~(byte)(param_1 >> 2) & 1 | 2);
  }
  else {
    local_404 = 1;
  }
  local_8 = local_400;
  FUN_0080249c(param_1);
  puVar1 = local_8;
  *local_8 = 0xffffffff;
  puVar1[1] = 0xffffffff;
  FUN_008045ad(&local_408);
  return;
}


/* ---- sSystem_InitX @ 008051c9 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall sSystem_InitX(int param_1)

{
  DWORD DVar1;
  HWND pHVar2;
  undefined4 *puVar3;
  BOOL BVar4;
  int iVar5;
  WNDCLASSA local_4c;
  tagMSG local_24;
  int local_8;
  
  *(undefined4 *)(DAT_0083f868 + 0x234) = 1;
  *(undefined4 *)(DAT_0083f868 + 0x22c) = 0x400;
  *(undefined4 *)(DAT_0083f868 + 0x230) = 0x300;
  _DAT_0083f888 = LoadLibraryA("d3d9.dll");
  DAT_0083f884 = GetProcAddress(_DAT_0083f888,"Direct3DCreate9");
  _DAT_0083f864 = LoadLibraryA("dsound.dll");
  DAT_0083f840 = GetProcAddress(_DAT_0083f864,"DirectSoundCreate8");
  timeBeginPeriod(1);
  DVar1 = timeGetTime();
  *(DWORD *)(param_1 + 0x54) = DVar1;
  timeGetTime();
  FUN_008054e9();
  DAT_0083f880 = GetDC((HWND)0x0);
  DAT_0083f874 = CreateCompatibleDC(DAT_0083f880);
  DAT_0083f8bc = CreateCompatibleBitmap(DAT_0083f880,0x10,0x10);
  SelectObject(DAT_0083f874,DAT_0083f8bc);
  local_4c.lpszClassName = "kk";
  local_4c.lpfnWndProc = FUN_00803af6;
  local_4c.style = 0x40;
  local_4c.hInstance = DAT_0083f860;
  local_4c.hIcon = LoadIconA(DAT_0083f860,&DAT_00000065);
  local_4c.hCursor = LoadCursorA((HINSTANCE)0x0,&DAT_00007f00);
  local_4c.hbrBackground = (HBRUSH)0x0;
  local_4c.lpszMenuName = (LPCSTR)0x0;
  local_4c.cbClsExtra = 0;
  local_4c.cbWndExtra = 0;
  RegisterClassA(&local_4c);
  pHVar2 = CreateWindowExA(0,"kk","kk",0x90000000,0,0,*(int *)(param_1 + 0x22c),
                           *(int *)(param_1 + 0x230),(HWND)0x0,(HMENU)0x0,DAT_0083f860,(LPVOID)0x0);
  *(HWND *)(param_1 + 0x5c) = pHVar2;
  *(undefined4 *)(DAT_0083f868 + 0x58) = 1;
  puVar3 = (undefined4 *)(param_1 + 0xa068);
  for (iVar5 = 0x2800; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar3 = (undefined4 *)(param_1 + 0x14068);
  for (iVar5 = 0xc000; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined4 *)(param_1 + 0x44210) = 0;
  *(undefined4 *)(param_1 + 0x44214) = 0;
  puVar3 = (undefined4 *)(param_1 + 0x2cc);
  iVar5 = 0x400;
  do {
    *puVar3 = 0;
    puVar3 = puVar3 + 7;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  FUN_00803c05();
  FUN_00804821();
  FUN_0081e8cb();
  local_24.message = 0;
  PeekMessageA(&local_24,(HWND)0x0,0,0,0);
  while (local_24.message != 0x12) {
    while (BVar4 = PeekMessageA(&local_24,(HWND)0x0,0,0,1), BVar4 != 0) {
      TranslateMessage(&local_24);
      DispatchMessageA(&local_24);
    }
    local_8 = 0;
    if (0 < *(int *)(param_1 + 0x238)) {
      do {
        FUN_0081e8cb();
        local_8 = local_8 + 1;
      } while (local_8 < *(int *)(param_1 + 0x238));
    }
    *(undefined4 *)(param_1 + 0x238) = 0;
    FUN_00804243();
    FUN_00801c13();
  }
  FUN_0081e8cb();
  if (DAT_0083f890 != (int *)0x0) {
    (**(code **)(*DAT_0083f890 + 0x48))(DAT_0083f890);
  }
                    /* WARNING: Subroutine does not return */
  ExitProcess(0);
}


/* ---- WinMainCRTStartup @ 00805427 ---- */

void WinMainCRTStartup(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  DAT_0083f860 = GetModuleHandleA((LPCSTR)0x0);
  puVar1 = (undefined4 *)operator_new(0x2d629c);
  DAT_0083f868 = puVar1;
  for (iVar2 = 0xb58a6; puVar1 = puVar1 + 1, iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = 0;
  }
  sSystem_InitX();
  operator_delete(DAT_0083f868);
                    /* WARNING: Subroutine does not return */
  ExitProcess(0);
}


/* ---- FUN_00805474 @ 00805474 ---- */

uint FUN_00805474(void)

{
  uint uVar1;
  
  uVar1 = DAT_00821670 * 0x343fd + 0x269ec3;
  DAT_00821670 = uVar1 * 0x343fd + 0x269ec3;
  return DAT_00821670 >> 10 & 0xffffU | (uVar1 & 0x3fffc00) << 6;
}


/* ---- FUN_008054b7 @ 008054b7 ---- */

uint FUN_008054b7(void)

{
  uint uVar1;
  uint extraout_ECX;
  
  uVar1 = FUN_00805474();
  return uVar1 % extraout_ECX;
}


/* ---- FUN_008054c3 @ 008054c3 ---- */

/* WARNING: Removing unreachable block (ram,0x008054db) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __fastcall FUN_008054c3(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00805474(param_1);
  return (float10)(uVar1 & 0x3fffffff) * (float10)_DAT_0081f360;
}


/* ---- FUN_008054e9 @ 008054e9 ---- */

void __fastcall FUN_008054e9(int param_1)

{
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint extraout_ECX_01;
  
  DAT_00821670 = param_1 * 0x8b + (param_1 * 0x79) / 0x11;
  FUN_00805474();
  DAT_00821670 = DAT_00821670 ^ extraout_ECX;
  FUN_00805474();
  DAT_00821670 = DAT_00821670 ^ extraout_ECX_00;
  FUN_00805474();
  DAT_00821670 = DAT_00821670 ^ extraout_ECX_01;
  FUN_00805474();
  return;
}


/* ---- FUN_0080552a @ 0080552a ---- */

void __fastcall FUN_0080552a(int param_1)

{
  byte bVar1;
  
  bVar1 = 1;
  if (2 < param_1) {
    do {
      bVar1 = bVar1 + 1;
    } while (1 << (bVar1 & 0x1f) < param_1);
  }
  return;
}


/* ---- FUN_00805543 @ 00805543 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall
FUN_00805543(int param_1,int param_2,float *param_3,int param_4,float *param_5,int param_6,
            float param_7,float param_8,float param_9,float param_10)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  int iVar13;
  float local_8;
  
  fVar2 = 1.0 - param_8;
  fVar4 = param_3[-1];
  fVar3 = (1.0 - param_9) * fVar2;
  param_8 = (param_10 + _DAT_0081f2bc) * fVar3 * _DAT_0081f2ac;
  fVar7 = (param_9 + _DAT_0081f2bc) * (1.0 - param_10) * fVar2 * _DAT_0081f2ac;
  fVar6 = (param_9 + _DAT_0081f2bc) * (param_10 + _DAT_0081f2bc) * fVar2 * _DAT_0081f2ac;
  local_8 = (1.0 - param_10) * fVar3 * _DAT_0081f2ac;
  fVar2 = *(float *)(param_4 + -4);
  if (param_2 == 0) {
    param_8 = -param_8;
    param_9 = (fVar4 - fVar2) + fVar4;
    param_2 = param_4;
  }
  else {
    param_9 = *(float *)(param_2 + -4);
  }
  if (param_5 == (float *)0x0) {
    local_8 = -local_8;
    fVar3 = (fVar2 - fVar4) + fVar2;
    param_5 = param_3;
  }
  else {
    fVar3 = param_5[-1];
  }
  fVar5 = param_7 * param_7;
  fVar9 = param_7 * fVar5;
  fVar11 = (fVar9 * _DAT_0081f108 - fVar5 * _DAT_0081f368) + _DAT_0081f2bc;
  fVar12 = _DAT_0081f368 - param_7 * _DAT_0081f108;
  fVar8 = fVar2 - fVar4;
  fVar10 = ((fVar9 - fVar5 * _DAT_0081f108) + param_7) * fVar8 * _DAT_0081f108;
  fVar9 = (fVar9 - fVar5) * fVar8 * _DAT_0081f108;
  if (0 < param_6) {
    iVar13 = (int)param_5 - (int)param_3;
    param_4 = param_4 - (int)param_3;
    param_1 = param_1 - (int)param_3;
    param_10 = (float)param_6;
    do {
      pfVar1 = (float *)(iVar13 + (int)param_3);
      fVar5 = *(float *)(param_4 + (int)param_3) - *param_3;
      *(float *)(param_1 + (int)param_3) =
           fVar11 * *param_3 +
           fVar12 * param_7 * param_7 * *(float *)(param_4 + (int)param_3) +
           (fVar5 * fVar6 + (*pfVar1 - *(float *)(param_4 + (int)param_3)) * local_8) *
           (fVar9 / ((fVar3 - fVar2) + fVar8)) +
           (fVar5 * fVar7 +
           (*param_3 - *(float *)((int)pfVar1 + (param_2 - (int)param_5))) * param_8) *
           (fVar10 / ((fVar4 - param_9) + fVar8));
      param_3 = param_3 + 1;
      param_10 = (float)((int)param_10 + -1);
    } while (param_10 != 0.0);
  }
  return;
}


/* ---- FUN_008056db @ 008056db ---- */

float10 FUN_008056db(double param_1,double param_2)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  
  fVar2 = (float10)param_1;
  if (fVar2 != (float10)0) {
    fVar2 = (float10)param_2 * fVar2;
    fVar1 = (float10)1;
    fVar3 = (float10)f2xm1(fVar2 - (fVar2 / fVar1) * fVar1);
    fVar2 = (float10)fscale(fVar3 + fVar1,fVar2);
  }
  return (float10)(double)fVar2;
}


/* ---- FUN_00805708 @ 00805708 ---- */

float10 FUN_00805708(double param_1)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  
  fVar3 = (float10)1.4426950408889634 * (float10)param_1;
  fVar2 = (float10)1;
  fVar1 = (float10)f2xm1(fVar3 - (fVar3 / fVar2) * fVar2);
  fVar2 = (float10)fscale(fVar1 + fVar2,fVar3);
  return (float10)(double)fVar2;
}


/* ---- FUN_0080572a @ 0080572a ---- */

void __fastcall FUN_0080572a(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  
  for (uVar1 = param_3 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *param_1 = *param_2;
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
  }
  for (param_3 = param_3 & 3; param_3 != 0; param_3 = param_3 - 1) {
    *(undefined1 *)param_1 = *(undefined1 *)param_2;
    param_2 = (undefined4 *)((int)param_2 + 1);
    param_1 = (undefined4 *)((int)param_1 + 1);
  }
  return;
}


/* ---- FUN_0080574a @ 0080574a ---- */

void FUN_0080574a(int param_1)

{
  FUN_0080572a(param_1 << 2);
  return;
}


/* ---- FUN_0080575d @ 0080575d ---- */

void __thiscall FUN_0080575d(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  param_1[1] = 0;
  *param_1 = param_2;
  uVar1 = operator_new(param_2);
  param_1[2] = uVar1;
  *(undefined1 *)(param_1 + 3) = 1;
  return;
}


/* ---- FUN_0080577f @ 0080577f ---- */

void __fastcall FUN_0080577f(int param_1)

{
  *(undefined4 *)(param_1 + 4) = 0;
  return;
}


/* ---- FUN_00805784 @ 00805784 ---- */

int __thiscall FUN_00805784(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 4);
  *(int *)(param_1 + 4) = iVar1 + param_2;
  return *(int *)(param_1 + 8) + iVar1;
}


/* ---- FUN_0080579d @ 0080579d ---- */

uint __fastcall FUN_0080579d(undefined4 *param_1)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  
  pbVar2 = (byte *)*param_1;
  bVar1 = *pbVar2;
  uVar3 = (uint)bVar1;
  *param_1 = pbVar2 + 1;
  if ((char)bVar1 < '\0') {
    uVar3 = uVar3 & 0x7f | (uint)pbVar2[1] << 7;
    *param_1 = pbVar2 + 2;
  }
  return uVar3;
}


/* ---- FUN_008057ba @ 008057ba ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __fastcall FUN_008057ba(undefined4 *param_1)

{
  short sVar1;
  
  sVar1 = *(short *)*param_1;
  *param_1 = (short *)*param_1 + 1;
  return (float10)(int)sVar1 * (float10)_DAT_0081f36c;
}


/* ---- FUN_008057d6 @ 008057d6 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __fastcall FUN_008057d6(undefined4 *param_1)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  
  pbVar2 = (byte *)*param_1;
  bVar1 = *pbVar2;
  *param_1 = pbVar2 + 1;
  if (bVar1 == 0) {
    return (float10)_DAT_0081f374;
  }
  if (bVar1 == 0x80) {
    return (float10)_DAT_0081f2bc;
  }
  if (bVar1 == 1) {
    return (float10)_DAT_0081f2ac;
  }
  if (bVar1 == 0x81) {
    return (float10)_DAT_0081f370;
  }
  uVar3 = (uint)CONCAT11(bVar1,pbVar2[1]);
  *param_1 = pbVar2 + 2;
  return (float10)(float)(((uint)(ushort)((bVar1 & 0x80) << 8) << 3 | uVar3 & 0x3ff) << 0xd |
                         (((int)uVar3 >> 10 & 0x1fU) + 0x70) * 0x800000);
}


/* ---- FUN_00805853 @ 00805853 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __fastcall FUN_00805853(undefined4 *param_1)

{
  ushort uVar1;
  byte *pbVar2;
  uint uVar3;
  
  pbVar2 = (byte *)*param_1;
  uVar3 = (uint)*pbVar2;
  *param_1 = pbVar2 + 1;
  if (uVar3 == 0) {
    return (float10)_DAT_0081f374;
  }
  if (uVar3 == 1) {
    return (float10)_DAT_0081f2bc;
  }
  if (uVar3 == 0xff) {
    return (float10)_DAT_0081f378;
  }
  uVar1 = *(ushort *)(pbVar2 + 1);
  *param_1 = pbVar2 + 3;
  return (float10)(float)((((uint)(uVar1 & 0x8000) | uVar3 << 7) << 8 | uVar1 & 0x7fff) << 8);
}


/* ---- FUN_008058b3 @ 008058b3 ---- */

void __thiscall FUN_008058b3(float *param_1,float *param_2)

{
  if (*param_1 < *param_2) {
    *param_1 = *param_2;
  }
  if (param_1[1] < param_2[1]) {
    param_1[1] = param_2[1];
  }
  if (param_2[2] < param_1[2]) {
    param_1[2] = param_2[2];
  }
  if (param_2[3] < param_1[3]) {
    param_1[3] = param_2[3];
  }
  return;
}


/* ---- FUN_00805905 @ 00805905 ---- */

void __thiscall FUN_00805905(float *param_1,float *param_2)

{
  if (*param_2 < *param_1) {
    *param_1 = *param_2;
  }
  if (param_2[1] < param_1[1]) {
    param_1[1] = param_2[1];
  }
  if (param_1[2] < param_2[2]) {
    param_1[2] = param_2[2];
  }
  if (param_1[3] < param_2[3]) {
    param_1[3] = param_2[3];
  }
  return;
}


/* ---- FUN_00805957 @ 00805957 ---- */

void __thiscall FUN_00805957(float *param_1,float *param_2,float *param_3,float param_4)

{
  *param_1 = (*param_3 - *param_2) * param_4 + *param_2;
  param_1[1] = (param_3[1] - param_2[1]) * param_4 + param_2[1];
  param_1[2] = (param_3[2] - param_2[2]) * param_4 + param_2[2];
  return;
}


/* ---- FUN_0080598d @ 0080598d ---- */

void __thiscall FUN_0080598d(float *param_1,float *param_2,float *param_3)

{
  *param_1 = param_3[2] * param_2[1] - param_2[2] * param_3[1];
  param_1[1] = param_2[2] * *param_3 - *param_2 * param_3[2];
  param_1[2] = *param_2 * param_3[1] - *param_3 * param_2[1];
  return;
}


/* ---- FUN_008059c8 @ 008059c8 ---- */

void __thiscall FUN_008059c8(float *param_1,float *param_2,float *param_3,float param_4)

{
  *param_1 = (*param_3 - *param_2) * param_4 + *param_2;
  param_1[1] = (param_3[1] - param_2[1]) * param_4 + param_2[1];
  param_1[2] = (param_3[2] - param_2[2]) * param_4 + param_2[2];
  param_1[3] = (param_3[3] - param_2[3]) * param_4 + param_2[3];
  return;
}


/* ---- FUN_00805a0d @ 00805a0d ---- */

void __thiscall FUN_00805a0d(float *param_1,float *param_2,float *param_3)

{
  *param_1 = param_3[2] * param_2[1] - param_2[2] * param_3[1];
  param_1[1] = param_2[2] * *param_3 - *param_2 * param_3[2];
  param_1[2] = *param_2 * param_3[1] - *param_3 * param_2[1];
  param_1[3] = 0.0;
  return;
}


/* ---- FUN_00805a4d @ 00805a4d ---- */

void __fastcall FUN_00805a4d(undefined4 *param_1)

{
  *param_1 = 0x3f800000;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0x3f800000;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0x3f800000;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0x3f800000;
  return;
}


/* ---- FUN_00805a9d @ 00805a9d ---- */

void __thiscall FUN_00805a9d(float *param_1,float param_2,float param_3,float param_4)

{
  float fVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  
  fVar2 = (float10)fsin((float10)param_2);
  fVar3 = (float10)fcos((float10)param_2);
  fVar4 = (float10)fsin((float10)param_3);
  fVar5 = (float10)fcos((float10)param_3);
  fVar1 = (float)fVar5;
  fVar5 = (float10)fsin((float10)param_4);
  fVar6 = (float10)fcos((float10)param_4);
  *param_1 = (float)((float10)fVar1 * fVar6);
  param_1[1] = (float)(fVar5 * (float10)fVar1);
  param_1[2] = (float)-fVar4;
  param_1[3] = 0.0;
  param_1[4] = (float)(fVar6 * fVar4 * fVar2 - fVar5 * fVar3);
  param_1[5] = (float)((float10)(float)fVar6 * fVar3 + fVar5 * fVar4 * fVar2);
  param_1[6] = (float)((float10)fVar1 * fVar2);
  param_1[7] = 0.0;
  param_1[8] = (float)(fVar5 * fVar2 + fVar6 * fVar4 * fVar3);
  param_1[9] = (float)((float10)(float)(fVar5 * fVar4) * fVar3 - (float10)(float)fVar6 * fVar2);
  param_1[10] = (float)((float10)fVar1 * fVar3);
  param_1[0xb] = 0.0;
  param_1[0xc] = 0.0;
  param_1[0xd] = 0.0;
  param_1[0xe] = 0.0;
  param_1[0xf] = 1.0;
  return;
}


/* ---- FUN_00805b55 @ 00805b55 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00805b55(float *param_1,float *param_2)

{
  float fVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  
  fVar2 = (float10)fsin((float10)*param_2 * (float10)_DAT_0081f37c);
  fVar3 = (float10)fcos((float10)(float)((float10)*param_2 * (float10)_DAT_0081f37c));
  fVar4 = (float10)fsin((float10)param_2[1] * (float10)_DAT_0081f37c);
  fVar5 = (float10)fcos((float10)(float)((float10)param_2[1] * (float10)_DAT_0081f37c));
  fVar1 = (float)fVar5;
  fVar5 = (float10)fsin((float10)param_2[2] * (float10)_DAT_0081f37c);
  fVar6 = (float10)fcos((float10)(float)((float10)param_2[2] * (float10)_DAT_0081f37c));
  *param_1 = (float)((float10)fVar1 * fVar6);
  param_1[1] = (float)(fVar5 * (float10)fVar1);
  param_1[2] = (float)-fVar4;
  param_1[3] = 0.0;
  param_1[4] = (float)(fVar6 * fVar4 * fVar2 - fVar5 * fVar3);
  param_1[5] = (float)((float10)(float)fVar6 * fVar3 + fVar5 * fVar4 * fVar2);
  param_1[6] = (float)((float10)fVar1 * fVar2);
  param_1[7] = 0.0;
  param_1[8] = (float)(fVar5 * fVar2 + fVar6 * fVar4 * fVar3);
  param_1[9] = (float)((float10)(float)(fVar5 * fVar4) * fVar3 - (float10)(float)fVar6 * fVar2);
  param_1[10] = (float)((float10)fVar1 * fVar3);
  param_1[0xb] = 0.0;
  param_1[0xc] = 0.0;
  param_1[0xd] = 0.0;
  param_1[0xe] = 0.0;
  param_1[0xf] = 1.0;
  return;
}


/* ---- FUN_00805c2c @ 00805c2c ---- */

void __thiscall FUN_00805c2c(int param_1,int param_2,int param_3)

{
  float *pfVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = 0;
  do {
    uVar4 = uVar3 & 0xc;
    uVar2 = uVar3 & 3;
    pfVar1 = (float *)(param_2 + uVar4 * 4);
    *(float *)(param_1 + uVar3 * 4) =
         *(float *)(param_3 + uVar2 * 4) * *pfVar1 +
         *(float *)(param_3 + 0x10 + uVar2 * 4) * pfVar1[1] +
         *(float *)(param_2 + 8 + uVar4 * 4) * *(float *)(param_3 + 0x20 + uVar2 * 4) +
         *(float *)(param_2 + 0xc + uVar4 * 4) * *(float *)(param_3 + 0x30 + uVar2 * 4);
    uVar3 = uVar3 + 1;
  } while ((int)uVar3 < 0x10);
  return;
}


/* ---- FUN_00805c80 @ 00805c80 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00805c80(float *param_1)

{
  uint uVar1;
  uint uVar2;
  
  if (param_1[1] <= _DAT_0081f374) {
    uVar1 = 0;
  }
  else {
    uVar1 = 2;
  }
  if (param_1[2] <= _DAT_0081f374) {
    uVar2 = 0;
  }
  else {
    uVar2 = 4;
  }
  param_1[4] = (float)(uVar2 | _DAT_0081f374 < *param_1 | uVar1);
  return;
}


/* ---- FUN_00805cbc @ 00805cbc ---- */

void __fastcall FUN_00805cbc(undefined4 *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if (param_3 == 0) {
    *param_1 = 0;
  }
  else {
    uVar1 = operator_new(param_2 * param_3);
    *param_1 = uVar1;
  }
  param_1[1] = 0;
  param_1[3] = param_2;
  param_1[2] = param_3;
  return;
}


/* ---- FUN_00805cf1 @ 00805cf1 ---- */

/* WARNING: Removing unreachable block (ram,0x00805d2f) */
/* WARNING: Removing unreachable block (ram,0x00805d14) */
/* WARNING: Removing unreachable block (ram,0x00805d48) */
/* WARNING: Removing unreachable block (ram,0x00805d60) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00805cf1(float *param_1,uint param_2)

{
  float fVar1;
  
  fVar1 = _DAT_0081f388;
  *param_1 = (float)(param_2 >> 0x10 & 0xff) * _DAT_0081f388;
  param_1[1] = (float)(param_2 >> 8 & 0xff) * fVar1;
  param_1[2] = (float)(param_2 & 0xff) * fVar1;
  param_1[3] = (float)(param_2 >> 0x18) * fVar1;
  return;
}


/* ---- FUN_00805d72 @ 00805d72 ---- */

void __thiscall FUN_00805d72(float *param_1,float *param_2,float *param_3)

{
  *param_1 = *param_2 + *param_3;
  param_1[1] = param_2[1] + param_3[1];
  param_1[2] = param_2[2] + param_3[2];
  param_1[3] = param_2[3] + param_3[3];
  return;
}


/* ---- FUN_00805da0 @ 00805da0 ---- */

void __thiscall FUN_00805da0(float *param_1,float *param_2,float *param_3)

{
  *param_1 = *param_2 * *param_3;
  param_1[1] = param_2[1] * param_3[1];
  param_1[2] = param_2[2] * param_3[2];
  param_1[3] = param_2[3] * param_3[3];
  return;
}


/* ---- FUN_00805dce @ 00805dce ---- */

void __thiscall FUN_00805dce(float *param_1,float *param_2)

{
  *param_1 = *param_2 + *param_1;
  param_1[1] = param_2[1] + param_1[1];
  param_1[2] = param_2[2] + param_1[2];
  param_1[3] = param_2[3] + param_1[3];
  return;
}


/* ---- FUN_00805df9 @ 00805df9 ---- */

void __thiscall FUN_00805df9(float *param_1,float *param_2)

{
  *param_1 = *param_1 - *param_2;
  param_1[1] = param_1[1] - param_2[1];
  param_1[2] = param_1[2] - param_2[2];
  param_1[3] = param_1[3] - param_2[3];
  return;
}


/* ---- FUN_00805e24 @ 00805e24 ---- */

void __thiscall FUN_00805e24(float *param_1,float *param_2)

{
  *param_1 = *param_2 * *param_1;
  param_1[1] = param_2[1] * param_1[1];
  param_1[2] = param_2[2] * param_1[2];
  param_1[3] = param_2[3] * param_1[3];
  return;
}


/* ---- FUN_00805e4f @ 00805e4f ---- */

void __fastcall FUN_00805e4f(float *param_1)

{
  *param_1 = -*param_1;
  param_1[1] = -param_1[1];
  param_1[2] = -param_1[2];
  param_1[3] = -param_1[3];
  return;
}


/* ---- FUN_00805e6e @ 00805e6e ---- */

void __thiscall FUN_00805e6e(float *param_1,float param_2)

{
  *param_1 = param_2 * *param_1;
  param_1[1] = param_2 * param_1[1];
  param_1[2] = param_2 * param_1[2];
  param_1[3] = param_2 * param_1[3];
  return;
}


/* ---- FUN_00805e97 @ 00805e97 ---- */

void __thiscall FUN_00805e97(float *param_1,float *param_2,float param_3)

{
  *param_1 = param_3 * *param_2;
  param_1[1] = param_3 * param_2[1];
  param_1[2] = param_3 * param_2[2];
  param_1[3] = param_3 * param_2[3];
  return;
}


/* ---- FUN_00805ec3 @ 00805ec3 ---- */

void __thiscall FUN_00805ec3(float *param_1,float *param_2,float param_3)

{
  *param_1 = param_3 * *param_2 + *param_1;
  param_1[1] = param_3 * param_2[1] + param_1[1];
  param_1[2] = param_3 * param_2[2] + param_1[2];
  param_1[3] = param_3 * param_2[3] + param_1[3];
  return;
}


/* ---- FUN_00805efa @ 00805efa ---- */

void __thiscall FUN_00805efa(float *param_1,float *param_2,float *param_3)

{
  *param_1 = *param_2 + *param_3;
  param_1[1] = param_2[1] + param_3[1];
  param_1[2] = param_2[2] + param_3[2];
  return;
}


/* ---- FUN_00805f1f @ 00805f1f ---- */

void __thiscall FUN_00805f1f(float *param_1,float *param_2,float *param_3)

{
  *param_1 = *param_2 - *param_3;
  param_1[1] = param_2[1] - param_3[1];
  param_1[2] = param_2[2] - param_3[2];
  return;
}


/* ---- FUN_00805f44 @ 00805f44 ---- */

void __thiscall FUN_00805f44(float *param_1,float *param_2)

{
  *param_1 = *param_2 + *param_1;
  param_1[1] = param_2[1] + param_1[1];
  param_1[2] = param_2[2] + param_1[2];
  return;
}


/* ---- FUN_00805f66 @ 00805f66 ---- */

void __thiscall FUN_00805f66(float *param_1,float *param_2)

{
  *param_1 = *param_1 - *param_2;
  param_1[1] = param_1[1] - param_2[1];
  param_1[2] = param_1[2] - param_2[2];
  return;
}


/* ---- FUN_00805f88 @ 00805f88 ---- */

void __thiscall FUN_00805f88(float *param_1,float *param_2)

{
  *param_1 = *param_2 * *param_1;
  param_1[1] = param_2[1] * param_1[1];
  param_1[2] = param_2[2] * param_1[2];
  return;
}


/* ---- FUN_00805faa @ 00805faa ---- */

void __fastcall FUN_00805faa(float *param_1)

{
  *param_1 = -*param_1;
  param_1[1] = -param_1[1];
  param_1[2] = -param_1[2];
  return;
}


/* ---- FUN_00805fc1 @ 00805fc1 ---- */

float10 __thiscall FUN_00805fc1(float *param_1,float *param_2)

{
  return (float10)*param_2 * (float10)*param_1 +
         (float10)param_2[1] * (float10)param_1[1] + (float10)param_2[2] * (float10)param_1[2];
}


/* ---- FUN_00805fdf @ 00805fdf ---- */

void __thiscall FUN_00805fdf(float *param_1,float *param_2,float *param_3)

{
  *param_1 = *param_2 * *param_3 + *param_1;
  param_1[1] = param_2[1] * param_3[1] + param_1[1];
  param_1[2] = param_2[2] * param_3[2] + param_1[2];
  return;
}


/* ---- FUN_0080600c @ 0080600c ---- */

void __thiscall FUN_0080600c(float *param_1,float param_2)

{
  *param_1 = param_2 * *param_1;
  param_1[1] = param_2 * param_1[1];
  param_1[2] = param_2 * param_1[2];
  return;
}


/* ---- FUN_0080602c @ 0080602c ---- */

void __thiscall FUN_0080602c(float *param_1,float *param_2,float param_3)

{
  *param_1 = param_3 * *param_2;
  param_1[1] = param_3 * param_2[1];
  param_1[2] = param_3 * param_2[2];
  return;
}


/* ---- FUN_0080604f @ 0080604f ---- */

void __thiscall FUN_0080604f(float *param_1,float *param_2,float param_3)

{
  *param_1 = param_3 * *param_2 + *param_1;
  param_1[1] = param_3 * param_2[1] + param_1[1];
  param_1[2] = param_3 * param_2[2] + param_1[2];
  return;
}


/* ---- FUN_0080607a @ 0080607a ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0080607a(undefined4 param_1)

{
  char *pcVar1;
  float fVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  float *pfVar9;
  undefined4 *puVar10;
  undefined *puVar11;
  undefined4 *puVar12;
  
  FUN_008054e9(param_1,param_1);
  iVar5 = 0;
  do {
    pcVar1 = &DAT_0081f308 + iVar5;
    iVar5 = iVar5 + 1;
    (&DAT_008408ec)[iVar5] = *(undefined4 *)(&UNK_0081f348 + *pcVar1 * 4);
  } while (iVar5 < 0x40);
  iVar5 = 0;
  do {
    iVar6 = FUN_008054b7();
    fVar2 = (float)iVar6;
    if (iVar6 < 0) {
      fVar2 = fVar2 + _DAT_0081f364;
    }
    (&DAT_008409f0)[iVar5 * 2] = fVar2;
    (&DAT_008411f0)[iVar5] = (char)iVar5;
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x100);
  iVar5 = 0;
  pfVar9 = (float *)&DAT_008409f0;
  do {
    if (iVar5 < 0xff) {
      puVar11 = &DAT_008411f1 + iVar5;
      pfVar8 = pfVar9 + 2;
      do {
        if (*pfVar8 < *pfVar9) {
          fVar2 = *pfVar9;
          uVar3 = *puVar11;
          *pfVar9 = *pfVar8;
          *pfVar8 = fVar2;
          uVar4 = (&DAT_008411f0)[iVar5];
          (&DAT_008411f0)[iVar5] = uVar3;
          *puVar11 = uVar4;
        }
        pfVar8 = pfVar8 + 2;
        puVar11 = puVar11 + 1;
      } while ((int)pfVar8 < 0x8411f0);
    }
    iVar5 = iVar5 + 1;
    pfVar9 = pfVar9 + 2;
  } while ((int)pfVar9 < 0x8411e8);
  puVar10 = (undefined4 *)&DAT_008411f0;
  puVar12 = &DAT_008412f0;
  for (iVar5 = 0x40; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar12 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar12 = puVar12 + 1;
  }
  pfVar9 = (float *)&DAT_008409f4;
  do {
    iVar6 = FUN_008054b7();
    iVar6 = iVar6 + -0x8000;
    iVar5 = iVar6;
    iVar7 = FUN_008054b7();
    fVar2 = _DAT_0081f38c;
    iVar7 = iVar7 + -0x8000;
    if (iVar7 * iVar7 + iVar6 * iVar6 < 0x40000000) {
      pfVar9[-1] = (float)iVar5 * _DAT_0081f38c;
      *pfVar9 = (float)iVar7 * fVar2;
      pfVar9 = pfVar9 + 2;
    }
  } while ((int)pfVar9 < 0x8411f4);
  return;
}


/* ---- FUN_008061a4 @ 008061a4 ---- */

void FUN_008061a4(int param_1,undefined4 *param_2)

{
  int extraout_EDX;
  int extraout_EDX_00;
  
  FUN_0080602c(param_1,*param_2);
  FUN_0080604f(param_1 + 0x10,*(undefined4 *)(extraout_EDX + 4));
  FUN_0080604f(param_1 + 0x20,*(undefined4 *)(extraout_EDX_00 + 8));
  return;
}


/* ---- FUN_008061df @ 008061df ---- */

void __thiscall FUN_008061df(undefined4 *param_1,undefined4 param_2)

{
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  local_14 = *param_1;
  uStack_10 = param_1[1];
  uStack_c = param_1[2];
  uStack_8 = param_1[3];
  FUN_008061a4(param_2,&local_14);
  return;
}


/* ---- FUN_00806202 @ 00806202 ---- */

float10 __fastcall FUN_00806202(undefined4 param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)FUN_00805fc1(param_1);
  return SQRT(fVar1);
}


/* ---- FUN_0080620b @ 0080620b ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0080620b(undefined4 param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)FUN_00805fc1(param_1);
  FUN_0080600c((float)((float10)_DAT_0081f358 / SQRT(fVar1)));
  return;
}


/* ---- FUN_00806223 @ 00806223 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __fastcall FUN_00806223(undefined4 param_1)

{
  float *extraout_ECX;
  float10 fVar1;
  
  fVar1 = (float10)FUN_00805fc1(param_1);
  fVar1 = SQRT(fVar1);
  if ((float10)_DAT_0081f390 < fVar1) {
    FUN_0080600c((float)((float10)1 / fVar1));
    return (float10)(float)fVar1;
  }
  *extraout_ECX = (float)(float10)1;
  extraout_ECX[1] = 0.0;
  extraout_ECX[2] = 0.0;
  return fVar1;
}


/* ---- FUN_00806261 @ 00806261 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00806261(undefined4 param_1)

{
  undefined4 *extraout_ECX;
  float10 fVar1;
  
  fVar1 = (float10)FUN_00805fc1(param_1);
  if ((float10)_DAT_0081f390 < fVar1) {
    FUN_0080600c((float)((float10)_DAT_0081f358 / SQRT(fVar1)));
    return;
  }
  *extraout_ECX = 0x3f800000;
  extraout_ECX[1] = 0;
  extraout_ECX[2] = 0;
  return;
}


/* ---- FUN_00806297 @ 00806297 ---- */

void FUN_00806297(int param_1,undefined4 *param_2)

{
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  
  FUN_00805e97(param_1,*param_2);
  FUN_00805ec3(param_1 + 0x10,*(undefined4 *)(extraout_EDX + 4));
  FUN_00805ec3(param_1 + 0x20,*(undefined4 *)(extraout_EDX_00 + 8));
  FUN_00805ec3(param_1 + 0x30,*(undefined4 *)(extraout_EDX_01 + 0xc));
  return;
}


/* ---- FUN_008062e2 @ 008062e2 ---- */

void __thiscall FUN_008062e2(undefined4 *param_1,undefined4 param_2)

{
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  local_14 = *param_1;
  uStack_10 = param_1[1];
  uStack_c = param_1[2];
  uStack_8 = param_1[3];
  FUN_00806297(param_2,&local_14);
  return;
}


/* ---- FUN_00806305 @ 00806305 ---- */

void FUN_00806305(undefined4 param_1,undefined4 *param_2)

{
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  
  FUN_00805e97(param_1,*param_2);
  FUN_00805ec3(extraout_EDX + 0x10,param_2[1]);
  FUN_00805ec3(extraout_EDX_00 + 0x20,param_2[2]);
  FUN_00805dce(extraout_EDX_01 + 0x30);
  return;
}


/* ---- FUN_00806349 @ 00806349 ---- */

void __thiscall FUN_00806349(undefined4 *param_1,undefined4 param_2)

{
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  local_14 = *param_1;
  uStack_10 = param_1[1];
  uStack_c = param_1[2];
  uStack_8 = param_1[3];
  FUN_00806305(param_2,&local_14);
  return;
}


/* ---- FUN_0080636c @ 0080636c ---- */

void __thiscall FUN_0080636c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  float10 fVar1;
  undefined1 local_24 [16];
  undefined1 local_14 [16];
  
  FUN_00805f1f(param_3,param_2);
  FUN_00805f1f(param_4,param_2);
  FUN_0080598d(local_24,local_14);
  fVar1 = (float10)FUN_00805fc1(param_2);
  *(float *)(param_1 + 0xc) = (float)-fVar1;
  return;
}


/* ---- FUN_008063b2 @ 008063b2 ---- */

void __thiscall FUN_008063b2(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  
  FUN_00805b55(param_2 + 0xc);
  FUN_0080600c(*extraout_EDX);
  FUN_0080600c(*(undefined4 *)(extraout_EDX_00 + 4));
  FUN_0080600c(*(undefined4 *)(extraout_EDX_01 + 8));
  uVar1 = *(undefined4 *)(extraout_EDX_02 + 0x20);
  uVar2 = *(undefined4 *)(extraout_EDX_02 + 0x18);
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(extraout_EDX_02 + 0x1c);
  *(undefined4 *)(param_1 + 0x30) = uVar2;
  *(undefined4 *)(param_1 + 0x38) = uVar1;
  return;
}


/* ---- FUN_00806404 @ 00806404 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00806404(int param_1)

{
  int extraout_EDX;
  int extraout_EDX_00;
  float10 fVar1;
  undefined1 local_28 [36];
  
  do {
    fVar1 = (float10)FUN_008054c3();
    *(float *)(local_28 + (extraout_EDX + 1) * 4 + -4) =
         (float)(((float10)*(float *)(param_1 + extraout_EDX * 4) - (float10)_DAT_0081f2bc) * fVar1
                + (float10)_DAT_0081f2bc);
  } while (extraout_EDX + 1 < 3);
  do {
    fVar1 = (float10)FUN_008054c3();
    fVar1 = (fVar1 - (float10)_DAT_0081f2ac) * (float10)*(float *)(param_1 + extraout_EDX_00 * 4);
    *(float *)(local_28 + (extraout_EDX_00 + 1) * 4 + -4) = (float)(fVar1 + fVar1);
  } while (extraout_EDX_00 + 1 < 9);
  FUN_008063b2(local_28);
  return;
}


/* ---- FUN_00806468 @ 00806468 ---- */

void __fastcall FUN_00806468(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0x10) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x20) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x18);
  *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x24) = uVar1;
  return;
}


/* ---- FUN_0080648d @ 0080648d ---- */

void __fastcall FUN_0080648d(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0x10) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x20) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(param_1 + 0x30) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x18);
  *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x24) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x1c);
  *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x34);
  *(undefined4 *)(param_1 + 0x34) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x2c);
  *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(param_1 + 0x38) = uVar1;
  return;
}


/* ---- FUN_008064d6 @ 008064d6 ---- */

void FUN_008064d6(void)

{
  undefined4 extraout_EDX;
  
  FUN_00806468();
  FUN_00805faa();
  FUN_008061df(extraout_EDX);
  return;
}


/* ---- FUN_008064ec @ 008064ec ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_008064ec(undefined4 param_1)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  int extraout_EDX;
  int extraout_EDX_00;
  undefined4 extraout_EDX_01;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  
  fVar4 = (float10)FUN_00805fc1(param_1);
  fVar1 = (float10)_DAT_0081f358;
  fVar5 = (float10)FUN_00805fc1(extraout_EDX + 0x10);
  fVar2 = (float10)_DAT_0081f358;
  fVar6 = (float10)FUN_00805fc1(extraout_EDX_00 + 0x20);
  fVar3 = (float10)_DAT_0081f358;
  FUN_0080600c((float)(fVar1 / SQRT(fVar4)));
  FUN_0080600c((float)(fVar2 / SQRT(fVar5)));
  FUN_0080600c((float)(fVar3 / SQRT(fVar6)));
  FUN_00806468();
  FUN_0080600c((float)(fVar1 / SQRT(fVar4)));
  FUN_0080600c((float)(fVar2 / SQRT(fVar5)));
  FUN_0080600c((float)(fVar3 / SQRT(fVar6)));
  FUN_00805faa();
  FUN_008061df(extraout_EDX_01);
  return;
}


/* ---- FUN_0080659e @ 0080659e ---- */

void __thiscall FUN_0080659e(int param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 extraout_ECX;
  
  FUN_00805a4d();
  FUN_00805957(param_2,param_3,param_4);
  FUN_00805957(param_2 + 0x10,param_3 + 0x10,param_4);
  FUN_0080598d(param_1,param_1 + 0x10);
  FUN_0080620b();
  FUN_0080598d(param_1 + 0x10,extraout_ECX);
  FUN_0080620b();
  FUN_0080620b();
  FUN_00805957(param_2 + 0x30,param_3 + 0x30,param_4);
  return;
}


/* ---- FUN_0080661f @ 0080661f ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0080661f(float *param_1,undefined4 param_2)

{
  float fVar1;
  float *pfVar2;
  int extraout_EDX;
  int extraout_EDX_00;
  undefined4 extraout_EDX_01;
  int iVar3;
  float local_34 [12];
  
  FUN_0080602c(param_2,param_1[4] - *param_1);
  FUN_0080602c(extraout_EDX + 0x10,param_1[5] - param_1[1]);
  FUN_0080602c(extraout_EDX_00 + 0x20,param_1[6] - param_1[2]);
  FUN_00806349(extraout_EDX_01);
  fVar1 = _DAT_0081f374;
  param_1[4] = *param_1;
  param_1[5] = param_1[1];
  param_1[6] = param_1[2];
  param_1[7] = param_1[3];
  pfVar2 = local_34 + 1;
  iVar3 = 3;
  do {
    if (fVar1 <= pfVar2[-1]) {
      param_1[4] = pfVar2[-1] + param_1[4];
    }
    else {
      *param_1 = pfVar2[-1] + *param_1;
    }
    if (fVar1 <= *pfVar2) {
      param_1[5] = *pfVar2 + param_1[5];
    }
    else {
      param_1[1] = *pfVar2 + param_1[1];
    }
    if (fVar1 <= pfVar2[1]) {
      param_1[6] = param_1[6] + pfVar2[1];
    }
    else {
      param_1[2] = param_1[2] + pfVar2[1];
    }
    pfVar2 = pfVar2 + 4;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}


/* ---- FUN_008066e6 @ 008066e6 ---- */

void FUN_008066e6(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_00805e97(param_1,param_2);
  FUN_00805ec3(param_3,param_4);
  FUN_00805c80();
  return;
}


/* ---- FUN_00806710 @ 00806710 ---- */

void FUN_00806710(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_0080636c(param_1,param_2,param_3);
  FUN_00805c80();
  return;
}


/* ---- FUN_00806730 @ 00806730 ---- */

float10 FUN_00806730(undefined4 param_1)

{
  int extraout_ECX;
  float10 fVar1;
  
  fVar1 = (float10)FUN_00805fc1(param_1);
  return fVar1 + (float10)*(float *)(extraout_ECX + 0xc);
}


/* ---- FUN_00806742 @ 00806742 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __fastcall FUN_00806742(undefined4 *param_1,int param_2,int param_3)

{
  uint uVar1;
  float10 fVar2;
  uint in_EAX;
  undefined2 extraout_var;
  int extraout_ECX;
  int iVar3;
  float10 fVar4;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  iVar3 = 0;
  if (0 < param_3) {
    do {
      uVar1 = *(uint *)(param_2 + 0x10);
      if ((uVar1 & 1) == 0) {
        local_14 = *param_1;
      }
      else {
        local_14 = param_1[4];
      }
      if ((uVar1 & 2) == 0) {
        local_10 = param_1[1];
      }
      else {
        local_10 = param_1[5];
      }
      if ((uVar1 & 4) == 0) {
        local_c = param_1[2];
      }
      else {
        local_c = param_1[6];
      }
      fVar4 = (float10)FUN_00806730(&local_14);
      fVar2 = (float10)_DAT_0081f398;
      in_EAX = CONCAT22(extraout_var,
                        (ushort)(fVar4 < fVar2) << 8 | (ushort)(NAN(fVar4) || NAN(fVar2)) << 10 |
                        (ushort)(fVar4 == fVar2) << 0xe);
      if (fVar4 < fVar2) {
        return CONCAT31((int3)(in_EAX >> 8),1);
      }
      iVar3 = iVar3 + 1;
      param_2 = extraout_ECX + 0x14;
    } while (iVar3 < param_3);
  }
  return in_EAX & 0xffffff00;
}


/* ---- FUN_008067af @ 008067af ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_008067af(undefined4 param_1,undefined4 *param_2,float *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_44 [4];
  undefined1 local_34 [16];
  undefined1 local_24 [16];
  undefined1 local_14 [16];
  
  puVar2 = local_44;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar2 = puVar2 + 1;
  }
  FUN_0080648d();
  FUN_008066e6(local_14,-*param_3,local_44,0x3f800000);
  FUN_008066e6(local_14,param_3[2],local_44,_DAT_0081f378);
  FUN_008066e6(local_14,-param_3[1],local_34,0x3f800000);
  FUN_008066e6(local_14,param_3[3],local_34,_DAT_0081f378);
  FUN_008066e6(local_14,0,local_24,0x3f800000);
  FUN_008066e6(local_14,0x3f800000,local_24,_DAT_0081f378);
  return;
}


/* ---- FUN_00806890 @ 00806890 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00806890(undefined4 *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float10 fVar4;
  int local_c;
  
  param_2 = param_2 - (int)param_1;
  local_c = 6;
  do {
    puVar2 = (undefined4 *)(param_2 + (int)param_1);
    puVar3 = param_1;
    for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    fVar4 = (float10)FUN_00805fc1(param_3);
    if (fVar4 + (float10)(float)param_1[3] < (float10)_DAT_0081f374) {
      param_1[3] = (float)((float10)(float)param_1[3] - (fVar4 + (float10)(float)param_1[3]));
      FUN_00805c80();
    }
    param_1 = param_1 + 5;
    local_c = local_c + -1;
  } while (local_c != 0);
  return;
}


/* ---- FUN_008068f0 @ 008068f0 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall
FUN_008068f0(int param_1,int *param_2,undefined4 param_3,int param_4,float param_5,float param_6,
            float param_7,float *param_8)

{
  float fVar1;
  int extraout_ECX;
  undefined4 *puVar2;
  int extraout_ECX_00;
  int iVar3;
  int extraout_EDX;
  int extraout_EDX_00;
  float10 fVar4;
  undefined4 local_50 [4];
  undefined1 local_40 [16];
  undefined1 local_30 [16];
  undefined1 local_20 [16];
  int *local_10;
  float local_c;
  float local_8;
  
  local_8 = param_5 / param_6;
  param_6 = 0.0;
  puVar2 = local_50;
  local_c = param_5 / param_7;
  iVar3 = param_4;
  local_10 = param_2;
  do {
    *puVar2 = *(undefined4 *)(param_4 + 0x30);
    puVar2[1] = *(undefined4 *)(param_4 + 0x34);
    puVar2[2] = *(undefined4 *)(param_4 + 0x38);
    puVar2[3] = *(undefined4 *)(param_4 + 0x3c);
    if (((uint)param_6 & 1) == 0) {
      fVar1 = *param_8;
    }
    else {
      fVar1 = param_8[2];
    }
    FUN_0080604f(iVar3,fVar1 * local_8);
    if (((uint)param_6 & 2) == 0) {
      fVar1 = param_8[1];
    }
    else {
      fVar1 = param_8[3];
    }
    FUN_0080604f(extraout_EDX + 0x10,fVar1 * local_c);
    FUN_0080604f(param_4 + 0x20,param_5);
    param_6 = (float)((int)param_6 + 1);
    puVar2 = (undefined4 *)(extraout_ECX + 0x10);
    iVar3 = extraout_EDX_00;
  } while ((int)param_6 < 4);
  FUN_00806710(local_50,local_40,local_30);
  fVar4 = (float10)FUN_00805fc1(param_3);
  fVar4 = fVar4 + (float10)*(float *)(param_1 + 0xc);
  if (ABS(fVar4) <= (float10)_DAT_0081f3a0) {
    FUN_00806710(local_30,local_40,local_50);
    iVar3 = 2;
  }
  else {
    FUN_00806710(param_3,local_40,local_50);
    FUN_00806710(param_3,local_20,local_40);
    FUN_00806710(param_3,local_30,local_20);
    FUN_00806710(param_3,local_50,local_30);
    iVar3 = 5;
    if ((float)fVar4 < _DAT_0081f374) {
      param_8 = (float *)0x5;
      do {
        FUN_00805e6e(_DAT_0081f378);
        FUN_00805c80();
        param_8 = (float *)((int)param_8 + -1);
      } while (param_8 != (float *)0x0);
    }
  }
  FUN_00805f1f((undefined4 *)(param_4 + 0x30),param_3);
  FUN_0080604f(param_4 + 0x20,param_5);
  fVar4 = (float10)FUN_00805fc1(param_3);
  *(float *)(extraout_ECX_00 + 0xc) = (float)-fVar4;
  FUN_00805c80();
  *local_10 = iVar3 + 1;
  return;
}


/* ---- FUN_00806a7e @ 00806a7e ---- */

void __fastcall FUN_00806a7e(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  if (param_2 != param_1[2]) {
    puVar2 = (undefined4 *)operator_new(param_1[3] * param_2);
    if ((undefined4 *)*param_1 != (undefined4 *)0x0) {
      iVar3 = param_1[1];
      iVar1 = param_1[3];
      puVar5 = (undefined4 *)*param_1;
      puVar6 = puVar2;
      for (uVar4 = (uint)(iVar3 * iVar1) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      for (uVar4 = iVar3 * iVar1 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
        puVar5 = (undefined4 *)((int)puVar5 + 1);
        puVar6 = (undefined4 *)((int)puVar6 + 1);
      }
      operator_delete(*param_1);
    }
    iVar3 = param_1[1];
    if (param_2 <= (int)param_1[1]) {
      iVar3 = param_2;
    }
    param_1[1] = iVar3;
    *param_1 = puVar2;
    param_1[2] = param_2;
  }
  return;
}


/* ---- FUN_00806ae3 @ 00806ae3 ---- */

void __fastcall FUN_00806ae3(int param_1,int param_2)

{
  if (*(int *)(param_1 + 8) < param_2) {
    FUN_00806a7e();
    return;
  }
  return;
}


/* ---- FUN_00806b0e @ 00806b0e ---- */

void __fastcall FUN_00806b0e(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  param_1[1] = 0;
  if ((int)param_1[2] < (int)param_2[1]) {
    FUN_00806a7e();
  }
  iVar1 = param_2[3];
  iVar2 = param_2[1];
  puVar4 = (undefined4 *)*param_2;
  puVar5 = (undefined4 *)*param_1;
  for (uVar3 = (uint)(iVar1 * iVar2) >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  for (uVar3 = iVar1 * iVar2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
    puVar5 = (undefined4 *)((int)puVar5 + 1);
  }
  param_1[1] = param_2[1];
  return;
}


/* ---- FUN_00806b54 @ 00806b54 ---- */

int __fastcall FUN_00806b54(int *param_1)

{
  int iVar1;
  
  FUN_00806ae3();
  iVar1 = param_1[1];
  param_1[1] = iVar1 + 1;
  return param_1[3] * iVar1 + *param_1;
}


/* ---- FUN_00806b71 @ 00806b71 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00806b71(float *param_1,float param_2,float param_3,float param_4)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)FUN_00805708((double)(_DAT_00842888 * param_3));
  param_1[2] = (float)-(fVar1 * fVar1);
  fVar2 = (float10)fcos((float10)_DAT_0084288c * (float10)param_2);
  fVar2 = fVar2 * fVar1 + fVar2 * fVar1;
  param_1[1] = (float)fVar2;
  *param_1 = (float)((((float10)1 - fVar2) - -(fVar1 * fVar1)) * (float10)param_4);
  return;
}


/* ---- FUN_00806bbb @ 00806bbb ---- */

void __thiscall FUN_00806bbb(undefined4 *param_1,float param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  
  pfVar5 = (float *)*param_1;
  fVar1 = pfVar5[2];
  fVar2 = (float)param_1[2];
  fVar3 = pfVar5[1];
  fVar4 = *pfVar5;
  param_1[2] = param_1[1];
  param_1[1] = param_2 * fVar4 + fVar3 * (float)param_1[1] + fVar1 * fVar2;
  return;
}


/* ---- FUN_00806be2 @ 00806be2 ---- */

float10 FUN_00806be2(float param_1,float param_2,float param_3)

{
  return ((float10)param_2 - (float10)param_1) * (float10)param_3 + (float10)param_1;
}


/* ---- FUN_00806bf5 @ 00806bf5 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00806bf5(void)

{
  float10 fVar1;
  
  fVar1 = (float10)FUN_00806be2();
  FUN_008056db(_DAT_0081faa8,(double)((fVar1 - (float10)_DAT_0081fab4) * (float10)_DAT_0081fab0));
  return;
}


/* ---- FUN_00806c39 @ 00806c39 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00806c39(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *in_EAX;
  int iVar1;
  int unaff_EBX;
  undefined4 *puVar2;
  float10 fVar3;
  float fVar4;
  float fVar5;
  
  puVar2 = &DAT_00842b50;
  for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *in_EAX;
    in_EAX = in_EAX + 1;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_00842b00;
  for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  iVar1 = 0;
  do {
    fVar3 = (float10)FUN_00806bf5(**(undefined4 **)((int)&PTR_DAT_0081fb28 + iVar1),
                                  **(undefined4 **)((int)&PTR_DAT_0081fb44 + iVar1),param_2);
    fVar5 = (float)fVar3;
    fVar3 = (float10)FUN_00806be2(**(undefined4 **)((int)&PTR_DAT_0081faf0 + iVar1),
                                  **(undefined4 **)((int)&PTR_DAT_0081fb0c + iVar1),param_2);
    fVar4 = (float)fVar3;
    fVar3 = (float10)FUN_00806be2(**(undefined4 **)((int)&PTR_DAT_0081fab8 + iVar1),
                                  **(undefined4 **)((int)&PTR_DAT_0081fad4 + iVar1),param_2);
    FUN_00806b71((float)(fVar3 * (float10)_DAT_00842874),fVar4,fVar5);
    iVar1 = iVar1 + 4;
  } while (iVar1 < 0x1c);
  fVar3 = (float10)FUN_00806bf5(_DAT_00842b6c,_DAT_00842b1c,param_2);
  *(float *)(unaff_EBX + 0x54) = (float)fVar3;
  fVar3 = (float10)FUN_00806bf5(_DAT_00842b70,_DAT_00842b20,param_2);
  *(float *)(unaff_EBX + 0x58) = (float)fVar3;
  fVar3 = (float10)FUN_00806bf5(_DAT_00842b74,_DAT_00842b24,param_2);
  *(float *)(unaff_EBX + 0x5c) = (float)fVar3;
  fVar3 = (float10)FUN_00806bf5(_DAT_00842b78,_DAT_00842b28,param_2);
  *(float *)(unaff_EBX + 0x60) = (float)fVar3;
  return;
}


/* ---- FUN_00806d8f @ 00806d8f ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00806d8f(void)

{
  int iVar1;
  uint uVar2;
  float10 fVar3;
  
  iVar1 = DAT_0084286c;
  uVar2 = *(uint *)(DAT_0084286c + 0x120) * 0xbb38435 + 0x3619636b;
  *(uint *)(DAT_0084286c + 0x120) = uVar2;
  fVar3 = (float10)*(float *)(iVar1 + 0x124) * (float10)_DAT_0081fb60 +
          ((float10)(float)(uVar2 >> 9 | 0x40000000) - (float10)_DAT_0081f368);
  *(float *)(iVar1 + 0x124) = (float)fVar3;
  return fVar3 * (float10)_DAT_0081f370;
}


/* ---- FUN_00806ddc @ 00806ddc ---- */

void FUN_00806ddc(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  puVar1 = DAT_0084286c;
  puVar2 = DAT_0084286c;
  for (iVar3 = 0x5b; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  iVar3 = 7;
  puVar2 = puVar1;
  do {
    puVar2[0x32] = puVar2;
    puVar2 = puVar2 + 3;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  puVar1[0x58] = &DAT_00842878;
  FUN_00806c39(&DAT_00841948,0);
  FUN_00806c39(&DAT_00841948,0);
  puVar1[0x53] = 0x12;
  puVar1[0x52] = 0x12;
  puVar1[0x4b] = 4;
  return;
}


/* ---- FUN_00806e4c @ 00806e4c ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00806e4c(int param_1)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar2 = (float10)fpatan((float10)1,(float10)1);
  _DAT_00842884 = param_1;
  fVar1 = (float10)param_1;
  if (param_1 < 0) {
    fVar1 = fVar1 + (float10)_DAT_0081f364;
  }
  fVar1 = (fVar2 * (float10)_DAT_0081fb68 + fVar2 * (float10)_DAT_0081fb68) / fVar1;
  _DAT_0084288c = (float)fVar1;
  _DAT_00842888 = (float)(fVar1 * (float10)_DAT_0081fb64);
  return;
}


/* ---- FUN_00806e8d @ 00806e8d ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00806e8d(void)

{
  byte bVar1;
  float *pfVar2;
  int iVar3;
  char *pcVar4;
  float *pfVar5;
  int local_c;
  int local_8;
  
  iVar3 = 0;
  pcVar4 = &DAT_0081f3c8;
  local_8 = 0;
  pfVar5 = (float *)&DAT_008413f0;
  do {
    bVar1 = (&DAT_0081f3b0)[iVar3];
    local_c = 0x45;
    pfVar2 = pfVar5;
    do {
      local_8 = local_8 + *pcVar4;
      pcVar4 = pcVar4 + 1;
      *pfVar2 = (float)local_8 * (float)bVar1;
      pfVar2 = pfVar2 + 0x13;
      local_c = local_c + -1;
    } while (local_c != 0);
    pfVar5 = pfVar5 + 1;
    iVar3 = iVar3 + 1;
  } while ((int)pfVar5 < 0x84143c);
  DAT_0084286c = &DAT_00842890;
  FUN_00806ddc();
  _DAT_00842874 = 0x3f800000;
  _DAT_00842870 = 0x40400000;
  _DAT_008429d0 = DAT_00842a00;
  if (DAT_00842a00 == (undefined *)0x0) {
    _DAT_008429d0 = PTR_DAT_00821674;
  }
  _DAT_008429ac = 0;
  _DAT_008429d4 = _DAT_008429d0;
  FUN_00806b71(_DAT_0081fb6c,_DAT_0081fb70,_DAT_0081f108);
  return;
}


/* ---- FUN_00806f4c @ 00806f4c ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00806f4c(void)

{
  byte *pbVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  char *pcVar5;
  byte *pbVar6;
  byte *pbVar7;
  int iVar8;
  int iVar9;
  float10 fVar10;
  uint local_14;
  uint uStack_10;
  uint local_c;
  uint local_8;
  
  iVar4 = DAT_0084286c;
  if (*(int *)(DAT_0084286c + 0x154) != 0) {
    return;
  }
  if (*(int *)(DAT_0084286c + 0x150) != 0) {
    return;
  }
  if (*(int *)(DAT_0084286c + 0x128) < 1) {
    local_14 = (uint)(longlong)ROUND(_DAT_00842870);
    *(uint *)(DAT_0084286c + 0x128) = local_14;
    iVar9 = *(int *)(iVar4 + 0x130);
    if (iVar9 < 1) {
      *(int *)(iVar4 + 300) = *(int *)(iVar4 + 300) + 1;
      if ((3 < *(int *)(iVar4 + 300)) ||
         ((&DAT_0081f8ec)[*(int *)(iVar4 + 0x134) * 8 + *(int *)(iVar4 + 300)] == -1)) {
        cVar2 = **(char **)(iVar4 + 0x144);
        if (cVar2 == '\0') {
          *(undefined4 *)(iVar4 + 0x138) = 1;
          *(undefined4 *)(iVar4 + 0x128) = 1;
          *(undefined4 *)(iVar4 + 0x134) = 0x33;
          *(undefined4 *)(iVar4 + 300) = 0;
          *(undefined4 *)(iVar4 + 0x144) = *(undefined4 *)(iVar4 + 0x140);
        }
        else {
          if (cVar2 == '!') {
            *(undefined4 *)(iVar4 + 0x150) = 1;
LAB_00807021:
            *(undefined4 *)(iVar4 + 0x128) = 0;
            *(undefined4 *)(iVar4 + 0x130) = 0;
            *(char **)(iVar4 + 0x144) = *(char **)(iVar4 + 0x144) + 1;
            return;
          }
          if (cVar2 == '_') {
            *(undefined4 *)(iVar4 + 0x154) = 1;
            goto LAB_00807021;
          }
        }
        pcVar5 = *(char **)(iVar4 + 0x144);
        cVar2 = *pcVar5;
        if (((cVar2 != '\0') && (cVar2 != '!')) && (cVar2 != '_')) {
          *(undefined4 *)(iVar4 + 0x138) = 0;
          while ('/' < *pcVar5) {
            cVar2 = **(char **)(iVar4 + 0x144);
            if ('9' < cVar2) break;
            pcVar5 = *(char **)(iVar4 + 0x144) + 1;
            *(int *)(iVar4 + 0x138) = *(int *)(iVar4 + 0x138) * 10 + -0x30 + (int)cVar2;
            *(char **)(iVar4 + 0x144) = pcVar5;
          }
          if (*(int *)(iVar4 + 0x138) == 0) {
            *(undefined4 *)(iVar4 + 0x138) = 1;
          }
          local_8 = 0;
          pbVar6 = &DAT_0081f8e8;
          do {
            local_c = 0;
            pbVar7 = pbVar6;
            if (*pbVar6 != 0) {
              do {
                pbVar1 = pbVar7 + (*(int *)(iVar4 + 0x144) - (int)pbVar6);
                if (*pbVar1 == 0) break;
                bVar3 = *pbVar7;
                pbVar7 = pbVar7 + 1;
                if ((bVar3 | 0x20) != (*pbVar1 | 0x20)) goto LAB_008070ed;
                local_c = local_c + 1;
              } while (*pbVar7 != 0);
            }
            uStack_10 = ~-(uint)(*pbVar7 != 0) & local_c;
            if (uStack_10 != 0) goto LAB_008070fc;
LAB_008070ed:
            local_8 = local_8 + 1;
            pbVar6 = pbVar6 + 8;
          } while (local_8 < 0x33);
          uStack_10 = 1;
LAB_008070fc:
          *(int *)(iVar4 + 0x144) = *(int *)(iVar4 + 0x144) + uStack_10;
          *(uint *)(iVar4 + 0x134) = local_8;
          *(undefined4 *)(iVar4 + 300) = 0;
        }
      }
      *(int *)(iVar4 + 0x148) = *(int *)(iVar4 + 0x14c);
      cVar2 = (&DAT_0081f8ec)[*(int *)(iVar4 + 0x134) * 8 + *(int *)(iVar4 + 300)];
      *(int *)(iVar4 + 0x14c) = (int)cVar2;
      local_14 = (uint)(longlong)
                       ROUND((float)*(int *)(iVar4 + 0x138) *
                             *(float *)(&DAT_00841434 + cVar2 * 0x4c));
      *(uint *)(iVar4 + 0x130) = local_14;
      if (local_14 == 0) {
        *(undefined4 *)(iVar4 + 0x130) = 1;
      }
      iVar9 = *(int *)(iVar4 + 0x130);
      *(float *)(iVar4 + 0x13c) = _DAT_0081f2bc / ((float)iVar9 * _DAT_00842870);
    }
    *(int *)(iVar4 + 0x130) = iVar9 + -1;
  }
  *(int *)(iVar4 + 0x128) = *(int *)(iVar4 + 0x128) + -1;
  iVar9 = *(int *)(iVar4 + 0x148) * 0x4c;
  iVar8 = *(int *)(iVar4 + 0x14c) * 0x4c;
  fVar10 = (float10)FUN_008056db((double)(((float)*(int *)(iVar4 + 0x130) * _DAT_00842870 +
                                          (float)*(int *)(iVar4 + 0x128)) *
                                         *(float *)(iVar4 + 0x13c)),
                                 (double)(*(float *)(&DAT_00841438 + iVar9) /
                                         *(float *)(&DAT_00841438 + iVar8)));
  local_14 = (uint)(longlong)
                   ROUND(*(float *)(&DAT_00841438 + iVar8) - *(float *)(&DAT_00841438 + iVar9));
  if (8 < (int)((local_14 ^ (int)local_14 >> 0x1f) - ((int)local_14 >> 0x1f))) {
    iVar9 = iVar8;
  }
  FUN_00806c39((int)&DAT_008413f0 + iVar9,(float)fVar10);
  return;
}


/* ---- FUN_00807215 @ 00807215 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00807215(int param_1,uint param_2)

{
  float fVar1;
  int iVar2;
  undefined *puVar3;
  float10 fVar4;
  
  iVar2 = DAT_0084286c;
  if (param_1 == 4) {
    if (param_2 < 0x3f) {
      FUN_00806ddc();
      puVar3 = (undefined *)(&DAT_00842a00)[param_2];
      if ((undefined *)(&DAT_00842a00)[param_2] == (undefined *)0x0) {
        puVar3 = PTR_DAT_00821674;
      }
      *(undefined **)(iVar2 + 0x140) = puVar3;
      *(undefined **)(iVar2 + 0x144) = puVar3;
    }
    else {
      _DAT_00842870 = (float)(int)(param_2 - 0x3f);
      if ((int)(param_2 - 0x3f) < 0) {
        _DAT_00842870 = _DAT_00842870 + _DAT_0081f364;
      }
    }
  }
  else if (param_1 == 5) {
    fVar1 = (float)(int)param_2;
    if ((int)param_2 < 0) {
      fVar1 = fVar1 + _DAT_0081f364;
    }
    fVar4 = (float10)FUN_008056db(_DAT_0081faa8,(double)((fVar1 - _DAT_0081fb78) * _DAT_0081fb74));
    _DAT_00842874 = (float)fVar4;
  }
  return;
}


/* ---- FUN_008072b4 @ 008072b4 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_008072b4(int param_1,uint param_2)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  int local_14;
  uint local_10;
  float local_8;
  
  pfVar3 = DAT_0084286c;
  fVar2 = (float)(int)param_2;
  if ((int)param_2 < 0) {
    fVar2 = fVar2 + _DAT_0081f364;
  }
  fVar2 = _DAT_0081f2bc / fVar2;
  iVar5 = (int)&DAT_00842ba0 - (int)DAT_0084286c;
  iVar6 = 0x19;
  pfVar4 = DAT_0084286c;
  do {
    *(float *)(iVar5 + (int)pfVar4) = (pfVar4[0x19] - *pfVar4) * fVar2;
    pfVar4 = pfVar4 + 1;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  local_10 = 0;
  if (param_2 != 0) {
    do {
      iVar6 = 0x19;
      pfVar4 = pfVar3;
      do {
        *pfVar4 = *(float *)((int)pfVar4 + iVar5) + *pfVar4;
        pfVar4 = pfVar4 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      pfVar4 = (float *)(param_1 + local_10 * 8);
      fVar2 = *pfVar4;
      fVar7 = (float10)FUN_00806d8f();
      fVar7 = (float10)fVar2 * (float10)pfVar3[0x15] + fVar7 * (float10)pfVar3[0x16];
      fVar2 = (float)fVar7;
      fVar7 = (float10)FUN_00806bbb((float)fVar7);
      fVar8 = (float10)FUN_00806bbb(fVar2);
      local_8 = (float)(fVar8 + (float10)(float)fVar7);
      fVar7 = (float10)FUN_00806d8f();
      local_14 = 5;
      fVar1 = pfVar3[0x47];
      pfVar3[0x47] = fVar2;
      fVar2 = (float)((fVar7 * (float10)pfVar3[0x17] + (float10)fVar2) - (float10)fVar1);
      do {
        fVar7 = (float10)FUN_00806bbb(fVar2);
        local_14 = local_14 + -1;
        local_8 = (float)(fVar7 - (float10)local_8);
      } while (local_14 != 0);
      fVar2 = (fVar2 * pfVar3[0x18] - local_8) - pfVar3[0x56];
      pfVar3[0x56] = _DAT_0081fb7c * fVar2 + pfVar3[0x56];
      fVar2 = fVar2 - pfVar3[0x57];
      pfVar3[0x57] = _DAT_0081fb7c * fVar2 + pfVar3[0x57];
      fVar7 = (float10)FUN_00806bbb(fVar2);
      local_10 = local_10 + 1;
      *(float *)(param_1 + -4 + local_10 * 8) = (float)(fVar7 - (float10)fVar2);
      *pfVar4 = (float)(fVar7 - (float10)fVar2);
    } while (local_10 < param_2);
  }
  return;
}


/* ---- FUN_0080742f @ 0080742f ---- */

void FUN_0080742f(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar1 = DAT_0084286c;
  puVar3 = &DAT_00842a00;
  for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *param_1;
    param_1 = param_1 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined4 *)(iVar1 + 0x144) = DAT_00842a00;
  *(undefined4 *)(iVar1 + 0x140) = DAT_00842a00;
  return;
}


/* ---- FUN_00807464 @ 00807464 ---- */

void __fastcall
FUN_00807464(int param_1,int param_2,uint param_3,uint param_4,uint *param_5,int *param_6)

{
  uint uVar1;
  ulonglong uVar2;
  uint uVar3;
  
  uVar2 = (ulonglong)(uint)(param_1 - param_2) * (ulonglong)param_3;
  uVar3 = (uint)(uVar2 % (ulonglong)param_4);
  uVar1 = *param_5;
  *param_5 = *param_5 + uVar3;
  *param_6 = (int)(uVar2 / param_4) + (uint)CARRY4(uVar1,uVar3);
  return;
}


/* ---- FUN_00807492 @ 00807492 ---- */

void __fastcall FUN_00807492(undefined4 *param_1)

{
  *param_1 = 1000;
  *(undefined1 *)(param_1 + 1) = 0;
  return;
}


/* ---- FUN_0080749f @ 0080749f ---- */

uint __thiscall FUN_0080749f(int param_1,int *param_2)

{
  uint uVar1;
  int *piVar2;
  uint *puVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  uint uVar7;
  undefined4 *puVar8;
  int local_8;
  
  iVar4 = *param_2;
  *(int *)(param_1 + 0x10) = iVar4;
  *(int *)(param_1 + 0x14) = iVar4 * 10000;
  *(int *)(param_1 + 0x18) = param_2[1];
  *(int *)(param_1 + 0x20) = param_2[2];
  *(int **)(param_1 + 0x1c) = param_2 + 3;
  piVar2 = (int *)((int)(param_2 + 3) + *(int *)(param_1 + 0x20) * 10);
  piVar5 = (int *)(param_1 + 0x2c);
  local_8 = 0x10;
  do {
    iVar4 = *piVar2;
    piVar2 = piVar2 + 1;
    piVar5[-2] = iVar4;
    if (iVar4 != 0) {
      piVar5[-1] = (int)piVar2;
      piVar2 = (int *)((int)piVar2 + iVar4 * 5);
      iVar4 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar5[1] = (int)piVar2;
      piVar2 = piVar2 + iVar4;
      *piVar5 = iVar4;
      iVar4 = *piVar2;
      piVar5[2] = iVar4;
      piVar5[3] = (int)(piVar2 + 1);
      piVar2 = (int *)((int)(piVar2 + 1) + iVar4 * 5);
      piVar6 = piVar5 + 4;
      param_2 = (int *)0x7;
      do {
        iVar4 = *piVar2;
        piVar6[1] = (int)(piVar2 + 1);
        *piVar6 = iVar4;
        piVar6 = piVar6 + 2;
        param_2 = (int *)((int)param_2 + -1);
        piVar2 = piVar2 + 1 + iVar4;
      } while (param_2 != (int *)0x0);
    }
    piVar5 = piVar5 + 0x14;
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  iVar4 = *piVar2;
  if ((iVar4 < 0x4001) && (-1 < iVar4)) {
    *(int **)(param_1 + 0xc) = piVar2 + 1;
    piVar2 = (int *)((int)(piVar2 + 1) + iVar4);
    iVar4 = *piVar2;
    if ((iVar4 < 0x100001) && (-1 < iVar4)) {
      *(int **)(param_1 + 8) = piVar2 + 1;
      puVar3 = (uint *)((int)(piVar2 + 1) + iVar4);
      if ((*puVar3 == 0) || (0x1fff < *puVar3)) {
        puVar3 = (uint *)&DAT_0081fb80;
        puVar8 = (undefined4 *)(param_1 + 0x528);
        for (iVar4 = 0x100; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar8 = &DAT_0081fb80;
          puVar8 = puVar8 + 1;
        }
      }
      else {
        *(uint **)(param_1 + 0x524) = puVar3 + 1;
        uVar7 = puVar3[1];
        puVar3 = puVar3 + 2;
        if (uVar7 != 0) {
          piVar5 = (int *)(param_1 + 0x528);
          do {
            uVar1 = *puVar3;
            puVar3 = puVar3 + 1;
            *piVar5 = uVar1 + *(int *)(param_1 + 0x524);
            piVar5 = piVar5 + 1;
            uVar7 = uVar7 - 1;
          } while (uVar7 != 0);
        }
      }
      return CONCAT31((int3)((uint)puVar3 >> 8),1);
    }
  }
  return (uint)piVar2 & 0xffffff00;
}


/* ---- FUN_008075b3 @ 008075b3 ---- */

void __fastcall FUN_008075b3(int param_1)

{
  int iVar1;
  undefined1 *puVar2;
  uint uVar3;
  undefined1 *puVar4;
  undefined4 *puVar5;
  int *piVar6;
  int *piVar7;
  int local_14;
  int local_10;
  
  iVar1 = *(int *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x930) = 0xffffffff;
  puVar4 = *(undefined1 **)(param_1 + 0x1c);
  *(undefined4 *)(param_1 + 0x92c) = 0;
  *(undefined1 **)(param_1 + 0x934) = puVar4;
  *(undefined4 *)(param_1 + 0x93c) = 0;
  if (iVar1 != 0) {
    uVar3 = (uint)CONCAT21(CONCAT11(puVar4[iVar1 * 2],puVar4[iVar1]),*puVar4);
    *(uint *)(param_1 + 0x938) = uVar3;
    if (uVar3 != 0xffffffff) {
      *(uint *)(param_1 + 0x930) = uVar3;
    }
  }
  piVar6 = (int *)(param_1 + 0x2c);
  puVar4 = (undefined1 *)(param_1 + 0x968);
  local_14 = 0x10;
  do {
    if (piVar6[-2] != 0) {
      puVar2 = (undefined1 *)piVar6[-1];
      *(undefined1 **)(puVar4 + -0xc) = puVar2;
      puVar4[1] = 0;
      *puVar4 = 0;
      *(undefined4 *)(puVar4 + -8) = 0;
      iVar1 = piVar6[-2];
      if (iVar1 != 0) {
        uVar3 = *(int *)(param_1 + 0x92c) +
                (uint)CONCAT21(CONCAT11(puVar2[iVar1 * 2],puVar2[iVar1]),*puVar2);
        *(uint *)(puVar4 + -4) = uVar3;
        if (uVar3 < *(uint *)(param_1 + 0x930)) {
          *(uint *)(param_1 + 0x930) = uVar3;
        }
      }
      puVar2 = (undefined1 *)piVar6[1];
      *(undefined1 **)(puVar4 + 4) = puVar2;
      puVar4[0x10] = 0;
      *(undefined4 *)(puVar4 + 8) = 0;
      iVar1 = *piVar6;
      if (iVar1 != 0) {
        uVar3 = *(int *)(param_1 + 0x92c) +
                (uint)CONCAT21(CONCAT11(puVar2[iVar1 * 2],puVar2[iVar1]),*puVar2);
        *(uint *)(puVar4 + 0xc) = uVar3;
        if (uVar3 < *(uint *)(param_1 + 0x930)) {
          *(uint *)(param_1 + 0x930) = uVar3;
        }
      }
      puVar2 = (undefined1 *)piVar6[3];
      *(undefined1 **)(puVar4 + 0x14) = puVar2;
      puVar4[0x21] = 0;
      puVar4[0x20] = 0;
      *(undefined4 *)(puVar4 + 0x18) = 0;
      iVar1 = *piVar6;
      if (iVar1 != 0) {
        uVar3 = *(int *)(param_1 + 0x92c) +
                (uint)CONCAT21(CONCAT11(puVar2[iVar1 * 2],puVar2[iVar1]),*puVar2);
        *(uint *)(puVar4 + 0x1c) = uVar3;
        if (uVar3 < *(uint *)(param_1 + 0x930)) {
          *(uint *)(param_1 + 0x930) = uVar3;
        }
      }
      piVar7 = piVar6 + 4;
      puVar5 = (undefined4 *)(puVar4 + 0x24);
      local_10 = 7;
      do {
        puVar2 = (undefined1 *)piVar7[1];
        puVar5[2] = 0;
        *puVar5 = puVar2;
        *(undefined1 *)(puVar5 + 3) = 0;
        iVar1 = *piVar7;
        if (iVar1 != 0) {
          uVar3 = *(int *)(param_1 + 0x92c) +
                  (uint)CONCAT21(CONCAT11(puVar2[iVar1 * 2],puVar2[iVar1]),*puVar2);
          puVar5[1] = uVar3;
          if (uVar3 < *(uint *)(param_1 + 0x930)) {
            *(uint *)(param_1 + 0x930) = uVar3;
          }
        }
        piVar7 = piVar7 + 2;
        puVar5 = puVar5 + 4;
        local_10 = local_10 + -1;
      } while (local_10 != 0);
    }
    piVar6 = piVar6 + 0x14;
    puVar4 = puVar4 + 0xa0;
    local_14 = local_14 + -1;
  } while (local_14 != 0);
  iVar1 = *(int *)(param_1 + 0x136c);
  *(int *)(param_1 + 0x940) = iVar1 * 5000;
  *(undefined4 *)(param_1 + 0x944) = 4;
  *(undefined4 *)(param_1 + 0x948) = 4;
  *(undefined4 *)(param_1 + 0x94c) = 8;
  *(undefined4 *)(param_1 + 0x950) = 0;
  *(undefined4 *)(param_1 + 0x954) = 0;
  *(undefined4 *)(param_1 + 0x958) = 0;
  *(undefined4 *)(param_1 + 0x1364) = 0;
  if (iVar1 != 0) {
    FUN_00809e2e(*(undefined4 *)(param_1 + 8),iVar1);
    FUN_0080a530(*(undefined4 *)(param_1 + 0xc));
    FUN_0080742f(param_1 + 0x528);
  }
  return;
}


/* ---- FUN_008077d7 @ 008077d7 ---- */

void __fastcall FUN_008077d7(int param_1)

{
  undefined1 uVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  byte *pbVar6;
  undefined1 *puVar7;
  uint *puVar8;
  byte bVar9;
  uint uVar10;
  int iVar11;
  uint *puVar12;
  uint *puVar13;
  int local_1c;
  int local_14;
  uint local_10;
  byte *local_c;
  
  if (*(int *)(param_1 + 0x928) == 2) {
    iVar3 = *(int *)(param_1 + 0x930);
    *(int *)(param_1 + 0x958) = *(int *)(param_1 + 0x958) + (iVar3 - *(int *)(param_1 + 0x92c));
    if (*(uint *)(param_1 + 0x10) <= *(uint *)(param_1 + 0x958)) {
      do {
        *(int *)(param_1 + 0x958) = *(int *)(param_1 + 0x958) - *(uint *)(param_1 + 0x10);
        *(int *)(param_1 + 0x954) = *(int *)(param_1 + 0x954) + 1;
      } while (*(uint *)(param_1 + 0x10) <= *(uint *)(param_1 + 0x958));
    }
    uVar4 = (uint)(*(int *)(param_1 + 0x944) << 2) / *(uint *)(param_1 + 0x948);
    puVar13 = (uint *)(param_1 + 0x954);
    if (uVar4 <= *puVar13) {
      uVar10 = *puVar13;
      iVar11 = *(int *)(param_1 + 0x950);
      do {
        uVar10 = uVar10 - uVar4;
        iVar11 = iVar11 + 1;
      } while (uVar4 <= uVar10);
      *(int *)(param_1 + 0x950) = iVar11;
      *puVar13 = uVar10;
    }
    uVar4 = *(uint *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x930) = 0xffffffff;
    local_10 = 0xffffffff;
    pbVar6 = (byte *)(param_1 + 0x1374);
    *(int *)(param_1 + 0x92c) = iVar3;
    if ((*(uint *)(param_1 + 0x93c) < uVar4) && (iVar3 == *(int *)(param_1 + 0x938))) {
      iVar3 = *(int *)(param_1 + 0x93c);
      iVar11 = *(int *)(param_1 + 0x934);
      *(uint *)(param_1 + 0x940) =
           (*(uint *)(param_1 + 0x136c) / 100) *
           *(int *)(uVar4 * 3 + *(int *)(param_1 + 0x934) + iVar3 * 4);
      uVar4 = *(uint *)(param_1 + 0x20);
      *(uint *)(param_1 + 0x944) = (uint)*(byte *)(uVar4 * 7 + iVar11 + iVar3);
      *(uint *)(param_1 + 0x948) = (uint)*(byte *)(iVar11 + uVar4 * 8 + iVar3);
      uVar10 = iVar3 + 1;
      *(uint *)(param_1 + 0x94c) = (uint)*(byte *)(uVar4 * 9 + iVar11 + iVar3);
      *(uint *)(param_1 + 0x93c) = uVar10;
      if (uVar10 < uVar4) {
        uVar1 = *(undefined1 *)(uVar10 + uVar4 * 2 + iVar11);
        bVar9 = ((byte *)(iVar11 + uVar10))[uVar4];
        bVar2 = *(byte *)(iVar11 + uVar10);
        if (CONCAT21(CONCAT11(uVar1,bVar9),bVar2) != 0) {
          *(uint *)(param_1 + 0x938) =
               (uint)bVar2 + (uint)CONCAT11(uVar1,bVar9) * 0x100 + *(int *)(param_1 + 0x92c);
        }
      }
    }
    if ((*(uint *)(param_1 + 0x93c) < uVar4) && (*(int *)(param_1 + 0x938) != -1)) {
      *(int *)(param_1 + 0x930) = *(int *)(param_1 + 0x938);
    }
    local_14 = 0;
    puVar13 = (uint *)(param_1 + 0x2c);
    piVar5 = (int *)(param_1 + 0x96c);
    local_c = pbVar6;
    do {
      if (puVar13[-2] != 0) {
        if (((uint)piVar5[1] < *puVar13) && (*(int *)(param_1 + 0x92c) == piVar5[2])) {
          bVar9 = (byte)local_14 | 0xc0;
          if (local_10 != bVar9) {
            *pbVar6 = bVar9;
            pbVar6 = pbVar6 + 1;
            local_10 = (uint)bVar9;
          }
          *(char *)(piVar5 + 3) = (char)piVar5[3] + *(char *)(*puVar13 * 3 + *piVar5);
          *pbVar6 = *(byte *)(piVar5 + 3);
          local_c = pbVar6 + 1;
          piVar5[1] = piVar5[1] + 1;
          puVar7 = (undefined1 *)(*piVar5 + 1);
          *piVar5 = (int)puVar7;
          if ((uint)piVar5[1] < *puVar13) {
            if (CONCAT21(CONCAT11(puVar7[*puVar13 * 2],puVar7[*puVar13]),*puVar7) != 0) {
              piVar5[2] = (uint)CONCAT21(CONCAT11(puVar7[*puVar13 * 2],puVar7[*puVar13]),*puVar7) +
                          *(int *)(param_1 + 0x92c);
            }
          }
        }
        if (((uint)piVar5[1] < *puVar13) && ((uint)piVar5[2] < *(uint *)(param_1 + 0x930))) {
          *(int *)(param_1 + 0x930) = piVar5[2];
        }
        local_1c = 0;
        puVar12 = puVar13 + 4;
        puVar8 = (uint *)(piVar5 + 10);
        do {
          if ((*puVar8 < *puVar12) && (*(uint *)(param_1 + 0x92c) == puVar8[-1])) {
            bVar9 = (byte)local_14 | 0xb0;
            if (local_10 != bVar9) {
              *local_c = bVar9;
              local_10 = (uint)bVar9;
              local_c = local_c + 1;
            }
            pbVar6 = local_c + 1;
            *local_c = (char)local_1c + 1;
            *(char *)(puVar8 + 1) = (char)puVar8[1] + *(char *)(*puVar12 * 3 + puVar8[-2]);
            local_c = local_c + 2;
            *pbVar6 = (byte)puVar8[1];
            *puVar8 = *puVar8 + 1;
            puVar7 = (undefined1 *)(puVar8[-2] + 1);
            puVar8[-2] = (uint)puVar7;
            if (*puVar8 < *puVar12) {
              if (CONCAT21(CONCAT11(puVar7[*puVar12 * 2],puVar7[*puVar12]),*puVar7) != 0) {
                puVar8[-1] = (uint)CONCAT21(CONCAT11(puVar7[*puVar12 * 2],puVar7[*puVar12]),*puVar7)
                             + *(int *)(param_1 + 0x92c);
              }
            }
          }
          if ((*puVar8 < *puVar12) && (puVar8[-1] < *(uint *)(param_1 + 0x930))) {
            *(uint *)(param_1 + 0x930) = puVar8[-1];
          }
          local_1c = local_1c + 1;
          puVar12 = puVar12 + 2;
          puVar8 = puVar8 + 4;
        } while (local_1c < 7);
        if (((uint)piVar5[5] < puVar13[2]) && (*(int *)(param_1 + 0x92c) == piVar5[6])) {
          bVar9 = (byte)local_14 | 0xe0;
          if (local_10 != bVar9) {
            *local_c = bVar9;
            local_c = local_c + 1;
            local_10 = (uint)bVar9;
          }
          *(char *)(piVar5 + 7) = (char)piVar5[7] + *(char *)(*puVar13 * 3 + piVar5[4]);
          *local_c = *(byte *)(piVar5 + 7);
          *(char *)((int)piVar5 + 0x1d) =
               *(char *)((int)piVar5 + 0x1d) + *(char *)(piVar5[4] + *puVar13 * 4);
          local_c[1] = *(byte *)((int)piVar5 + 0x1d);
          local_c = local_c + 2;
          piVar5[5] = piVar5[5] + 1;
          piVar5[4] = piVar5[4] + 1;
          if ((uint)piVar5[5] < puVar13[2]) {
            puVar7 = (undefined1 *)piVar5[4];
            if (CONCAT21(CONCAT11(puVar7[puVar13[2] * 2],puVar7[puVar13[2]]),*puVar7) != 0) {
              piVar5[6] = (uint)CONCAT21(CONCAT11(puVar7[puVar13[2] * 2],puVar7[puVar13[2]]),*puVar7
                                        ) + *(int *)(param_1 + 0x92c);
            }
          }
        }
        if (((uint)piVar5[5] < puVar13[2]) && ((uint)piVar5[6] < *(uint *)(param_1 + 0x930))) {
          *(int *)(param_1 + 0x930) = piVar5[6];
        }
        while (((uint)piVar5[-3] < puVar13[-2] && (*(int *)(param_1 + 0x92c) == piVar5[-2]))) {
          bVar9 = (byte)local_14 | 0x90;
          if (local_10 != bVar9) {
            *local_c = bVar9;
            local_c = local_c + 1;
            local_10 = (uint)bVar9;
          }
          *(char *)(piVar5 + -1) = (char)piVar5[-1] + *(char *)(puVar13[-2] * 3 + piVar5[-4]);
          *local_c = *(byte *)(piVar5 + -1);
          *(char *)((int)piVar5 + -3) =
               *(char *)((int)piVar5 + -3) + *(char *)(piVar5[-4] + puVar13[-2] * 4);
          local_c[1] = *(byte *)((int)piVar5 + -3);
          local_c = local_c + 2;
          piVar5[-3] = piVar5[-3] + 1;
          piVar5[-4] = piVar5[-4] + 1;
          if ((uint)piVar5[-3] < puVar13[-2]) {
            puVar7 = (undefined1 *)piVar5[-4];
            if (CONCAT21(CONCAT11(puVar7[puVar13[-2] * 2],puVar7[puVar13[-2]]),*puVar7) != 0) {
              piVar5[-2] = (uint)CONCAT21(CONCAT11(puVar7[puVar13[-2] * 2],puVar7[puVar13[-2]]),
                                          *puVar7) + *(int *)(param_1 + 0x92c);
            }
          }
        }
        pbVar6 = local_c;
        if (((uint)piVar5[-3] < puVar13[-2]) && ((uint)piVar5[-2] < *(uint *)(param_1 + 0x930))) {
          *(int *)(param_1 + 0x930) = piVar5[-2];
        }
      }
      local_14 = local_14 + 1;
      puVar13 = puVar13 + 0x14;
      piVar5 = piVar5 + 0x28;
    } while (local_14 < 0x10);
    *pbVar6 = 0xfd;
    FUN_0080a222(param_1 + 0x1374);
    if (*(int *)(param_1 + 0x930) == -1) {
      *(undefined4 *)(param_1 + 0x928) = 1;
    }
  }
  return;
}


/* ---- FUN_00807d1a @ 00807d1a ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00807d1a(int *param_1,int param_2)

{
  float fVar1;
  int iVar2;
  
  if ((char)param_1[1] != '\0') {
    if (param_2 == 0) {
      param_1[0x24a] = 0;
    }
    else {
      iVar2 = (int)(((longlong)param_2 * (longlong)param_1[0x4db]) / (longlong)*param_1);
      fVar1 = (float)iVar2;
      if (iVar2 < 0) {
        fVar1 = fVar1 + _DAT_0081f364;
      }
      param_1[0x8de] = (int)((float)param_1[0x8dd] / fVar1);
    }
  }
  return;
}


/* ---- FUN_00807d71 @ 00807d71 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00807d71(int param_1,undefined4 *param_2,uint param_3)

{
  uint *puVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  uint local_8;
  
  if (param_2 != (undefined4 *)0x0) {
    if ((*(char *)(param_1 + 4) == '\0') || (*(int *)(param_1 + 0x928) != 2)) {
      if ((*(int *)(param_1 + 0x928) == 0) || (*(char *)(param_1 + 4) == '\0')) {
        puVar6 = param_2;
        for (iVar4 = param_3 << 1; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
      }
      else {
        FUN_00809f08(param_2,param_3,0,0);
        *(int *)(param_1 + 0x135c) = *(int *)(param_1 + 0x135c) + param_3;
      }
    }
    else {
      local_8 = param_3;
      if (param_3 != 0) {
        puVar1 = (uint *)(param_1 + 0x1360);
        do {
          uVar5 = *puVar1;
          if (local_8 <= *puVar1) {
            uVar5 = local_8;
          }
          if (uVar5 != 0) {
            FUN_00809f08(param_2,uVar5,0,0);
            local_8 = local_8 - uVar5;
            *puVar1 = *puVar1 - uVar5;
            *(int *)(param_1 + 0x135c) = *(int *)(param_1 + 0x135c) + uVar5;
            param_2 = param_2 + uVar5 * 2;
          }
          if (*puVar1 == 0) {
            FUN_008077d7();
            if (*(int *)(param_1 + 0x928) == 2) {
              FUN_00807464(*(undefined4 *)(param_1 + 0x940),*(undefined4 *)(param_1 + 0x14),
                           param_1 + 0x1364,puVar1);
            }
            else {
              *puVar1 = 0xffffffff;
            }
          }
        } while (local_8 != 0);
      }
    }
    fVar3 = _DAT_0081f374;
    if (*(float *)(param_1 + 0x2378) != _DAT_0081f374) {
      uVar5 = 0;
      if (param_3 != 0) {
        do {
          param_2[uVar5 * 2] = *(float *)(param_1 + 0x2374) * (float)param_2[uVar5 * 2];
          param_2[uVar5 * 2 + 1] = *(float *)(param_1 + 0x2374) * (float)param_2[uVar5 * 2 + 1];
          fVar2 = *(float *)(param_1 + 0x2374) - *(float *)(param_1 + 0x2378);
          *(float *)(param_1 + 0x2374) = fVar2;
          if (fVar2 < fVar3) {
            *(undefined4 *)(param_1 + 0x2374) = 0;
          }
          uVar5 = uVar5 + 1;
        } while (uVar5 < param_3);
      }
      if (*(float *)(param_1 + 0x2374) == fVar3) {
        FUN_00807d1a(0);
      }
    }
    if ((*(char *)(param_1 + 4) != '\0') && (*(int *)(param_1 + 0x928) == 2)) {
      return 1;
    }
  }
  return 0;
}


/* ---- FUN_00807ef2 @ 00807ef2 ---- */

void __fastcall FUN_00807ef2(int param_1)

{
  if (*(char *)(param_1 + 4) != '\0') {
    if (*(int *)(param_1 + 0x928) != 0) {
      FUN_00807d1a(0);
    }
    *(undefined1 *)(param_1 + 4) = 0;
  }
  return;
}


/* ---- FUN_00807f11 @ 00807f11 ---- */

void __thiscall FUN_00807f11(int param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  if ((*(char *)(param_1 + 4) != '\0') && (*(int *)(param_1 + 0x136c) != 0)) {
    FUN_00807d1a(0);
    FUN_008075b3();
    piVar1 = (int *)(param_1 + 0x1360);
    *(undefined1 *)(param_1 + 4) = 0;
    *(undefined4 *)(param_1 + 0x928) = 2;
    *piVar1 = 0;
    *(undefined4 *)(param_1 + 0x1364) = 0;
    if (param_2 != 0) {
      do {
        if (*(int *)(param_1 + 0x928) != 2) break;
        iVar2 = iVar2 + *piVar1;
        FUN_008077d7();
        if (*(int *)(param_1 + 0x928) == 2) {
          FUN_00807464(*(undefined4 *)(param_1 + 0x940),*(undefined4 *)(param_1 + 0x14),
                       param_1 + 0x1364,piVar1);
        }
        else {
          *piVar1 = -1;
        }
      } while ((uint)(*piVar1 + iVar2) < param_2);
    }
    *(undefined4 *)(param_1 + 0x2374) = 0x3f800000;
    *(undefined1 *)(param_1 + 4) = 1;
    *piVar1 = *piVar1 + (iVar2 - param_2);
    *(undefined4 *)(param_1 + 0x2378) = 0;
    *(int *)(param_1 + 0x1370) = iVar2 - *(int *)(param_1 + 0x135c);
  }
  return;
}


/* ---- FUN_00807fd6 @ 00807fd6 ---- */

bool __thiscall FUN_00807fd6(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  
  if (*(char *)(param_1 + 4) != '\0') {
    FUN_00807ef2();
  }
  *(undefined4 *)(param_1 + 0x136c) = param_3;
  cVar1 = FUN_0080749f(param_2);
  if (cVar1 != '\0') {
    FUN_008075b3();
    *(undefined1 *)(param_1 + 4) = 1;
  }
  return cVar1 != '\0';
}


/* ---- FUN_008081e9 @ 008081e9 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_008081e9(void)

{
  int in_EAX;
  float10 fVar1;
  float10 fVar2;
  
  DAT_008c4f04 = in_EAX;
  fVar1 = (float10)1 / (float10)in_EAX;
  _DAT_00821678 = (float)((float10)_DAT_00808118 * (float10)_DAT_00808018 * fVar1);
  _DAT_0082167c = (float)((float10)_DAT_0080811c * fVar1);
  fVar2 = fVar1 * (float10)_DAT_00808120 * (float10)_DAT_00808038;
  fVar1 = (float10)fcos(fVar2);
  fVar2 = (float10)fsin(fVar2);
  _DAT_00821684 = (float)fVar1;
  _DAT_00821680 = (float)fVar2;
  DAT_00821688 = (int)ROUND(((float10)in_EAX * (float10)_DAT_00808124) / (float10)_DAT_0080811c +
                            (float10)_DAT_00808028);
  return;
}


/* ---- FUN_0080824d @ 0080824d ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

unkbyte10 FUN_0080824d(void)

{
  float10 fVar1;
  float10 in_ST0;
  float10 fVar2;
  float10 fVar3;
  unkbyte10 Var4;
  
  fVar2 = (in_ST0 - (float10)1) * (float10)_DAT_00808078;
  fVar1 = (float10)1;
  fVar3 = (float10)f2xm1(fVar2 - (fVar2 / fVar1) * fVar1);
  Var4 = fscale(fVar3 + fVar1,fVar2);
  return Var4;
}


/* ---- FUN_00808266 @ 00808266 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

unkbyte10 FUN_00808266(void)

{
  float10 fVar1;
  float10 in_ST0;
  float10 fVar2;
  float10 fVar3;
  unkbyte10 Var4;
  
  fVar2 = (in_ST0 - (float10)1) * (float10)_DAT_00808054;
  fVar1 = (float10)1;
  fVar3 = (float10)f2xm1(fVar2 - (fVar2 / fVar1) * fVar1);
  Var4 = fscale(fVar3 + fVar1,fVar2);
  return Var4;
}


/* ---- FUN_0080827f @ 0080827f ---- */

unkbyte10 FUN_0080827f(void)

{
  float10 fVar1;
  float10 in_ST0;
  float10 fVar2;
  unkbyte10 Var3;
  
  fVar1 = (float10)1;
  fVar2 = (float10)f2xm1(in_ST0 - (in_ST0 / fVar1) * fVar1);
  Var3 = fscale(fVar2 + fVar1,in_ST0);
  return Var3;
}


/* ---- FUN_0080828e @ 0080828e ---- */

unkbyte10 FUN_0080828e(void)

{
  float10 fVar1;
  float10 in_ST0;
  float10 fVar2;
  unkbyte10 Var3;
  float10 in_ST1;
  float10 fVar4;
  
  fVar4 = in_ST1 * in_ST0;
  fVar1 = (float10)1;
  fVar2 = (float10)f2xm1(fVar4 - (fVar4 / fVar1) * fVar1);
  Var3 = fscale(fVar2 + fVar1,fVar4);
  return Var3;
}


/* ---- FUN_0080829f @ 0080829f ---- */

undefined8 __fastcall FUN_0080829f(undefined4 param_1,undefined4 param_2)

{
  undefined8 uVar1;
  undefined4 in_EAX;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + 8) = 0;
  *(undefined4 *)(unaff_EBP + 8) = 0;
  *(undefined4 *)(unaff_EBP + 0x2c) = 0;
  *(undefined4 *)(unaff_EBP + 0x30) = 0;
  uVar1 = rdtsc();
  *(int *)(unaff_EBP + 0x1c) = (int)uVar1;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_008082b5 @ 008082b5 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_008082b5(void)

{
  int unaff_EBP;
  float10 fVar1;
  
  fVar1 = (float10)FUN_00808266();
  *(float *)(unaff_EBP + 0x14) = (float)(fVar1 * (float10)_DAT_0082167c);
  fVar1 = (float10)FUN_0080827f();
  *(int *)(unaff_EBP + 0xc) = (int)ROUND(fVar1 * (float10)_DAT_00821678);
  return;
}


/* ---- FUN_008082f2 @ 008082f2 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_008082f2(undefined4 param_1,undefined4 param_2)

{
  float fVar1;
  undefined4 in_EAX;
  int *unaff_EBP;
  float *unaff_ESI;
  
  *unaff_EBP = (int)ROUND(*unaff_ESI);
  unaff_EBP[1] = (int)ROUND(unaff_ESI[1]);
  unaff_EBP[0xe] =
       (int)((unaff_ESI[3] - _DAT_0080803c) * _DAT_00808020 + (unaff_ESI[2] - _DAT_0080803c));
  FUN_008082b5();
  fVar1 = unaff_ESI[5] * _DAT_00808020;
  unaff_EBP[8] = (int)fVar1;
  unaff_EBP[9] = (int)(fVar1 * _DAT_00808024);
  fVar1 = unaff_ESI[4] * _DAT_00808020;
  unaff_EBP[4] = (int)ROUND(fVar1 * _DAT_00808018);
  unaff_EBP[4] = unaff_EBP[4] << 1;
  unaff_EBP[6] = (int)(1.0 - SQRT(fVar1));
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00808377 @ 00808377 ---- */

void FUN_00808377(void)

{
  uint *unaff_EBP;
  
                    /* WARNING: Could not recover jumptable at 0x00808382. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(&DAT_00808357 + (*unaff_EBP & 0xffffff07) * 4))();
  return;
}


/* ---- FUN_008086e6 @ 008086e6 ---- */

undefined8 __fastcall FUN_008086e6(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + 4) = 0;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_008086ee @ 008086ee ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_008086ee(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int unaff_EBP;
  int unaff_ESI;
  float10 fVar1;
  
  fVar1 = (float10)FUN_0080827f();
  *(float *)(unaff_EBP + 0xc) = (float)fVar1;
  fVar1 = (float10)FUN_0080824d();
  *(float *)(unaff_EBP + 0x10) = (float)((float10)1 - fVar1);
  *(undefined4 *)(unaff_EBP + 0x14) = *(undefined4 *)(unaff_ESI + 8);
  fVar1 = (float10)FUN_0080827f();
  *(float *)(unaff_EBP + 0x18) = (float)fVar1;
  fVar1 = (float10)FUN_0080824d();
  *(float *)(unaff_EBP + 0x1c) = (float)((float10)1 - fVar1);
  *(float *)(unaff_EBP + 0x20) = *(float *)(unaff_ESI + 0x14) * _DAT_00808020;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00808776 @ 00808776 ---- */

undefined8 __fastcall FUN_00808776(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  float *unaff_EBP;
  
  (**(code **)(&DAT_00808762 + (int)unaff_EBP[1] * 4))();
  *unaff_EBP = unaff_EBP[2] * unaff_EBP[8];
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00808849 @ 00808849 ---- */

undefined8 __fastcall FUN_00808849(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + 0xc) = 0;
  *(undefined4 *)(unaff_EBP + 0x10) = 0;
  *(undefined4 *)(unaff_EBP + 0x14) = 4;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00808859 @ 00808859 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_00808859(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int *unaff_EBP;
  float *unaff_ESI;
  float10 fVar1;
  
  *unaff_EBP = (int)ROUND(*unaff_ESI);
  fVar1 = (float10)FUN_00808266();
  unaff_EBP[2] = (int)(1.0 - unaff_ESI[2] * _DAT_00808020);
  unaff_EBP[1] = (int)(float)(fVar1 * (float10)_DAT_0082167c);
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_008088a8 @ 008088a8 ---- */

undefined8 __fastcall FUN_008088a8(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  byte *unaff_EBP;
  float10 fVar1;
  float10 extraout_ST1;
  
  fVar1 = (float10)(*(code *)(&PTR_LAB_00808888)[*unaff_EBP & 7])();
  *(float *)(unaff_EBP + 0x10) = (float)fVar1;
  *(float *)(unaff_EBP + 0xc) = (float)extraout_ST1;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_008088ce @ 008088ce ---- */

float10 FUN_008088ce(void)

{
  float *unaff_ESI;
  float10 in_ST0;
  float10 in_ST1;
  float10 in_ST2;
  float10 fVar1;
  float10 in_ST3;
  float10 fVar2;
  
  fVar2 = in_ST0 * in_ST2 + in_ST1;
  fVar1 = (((float10)*unaff_ESI - in_ST0 * in_ST3) - fVar2) * in_ST2 + in_ST0;
  return ((float10)*unaff_ESI - fVar1 * in_ST3) - (fVar1 * in_ST2 + fVar2);
}


/* ---- FUN_0080895d @ 0080895d ---- */

undefined8 __fastcall FUN_0080895d(undefined4 param_1,undefined4 param_2)

{
  undefined8 uVar1;
  undefined4 in_EAX;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + 0x14) = 0;
  *(undefined4 *)(unaff_EBP + 0x28) = 0;
  uVar1 = rdtsc();
  *(int *)(unaff_EBP + 0x24) = (int)uVar1;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_0080896d @ 0080896d ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_0080896d(undefined4 param_1,undefined4 param_2)

{
  float fVar1;
  float fVar2;
  char cVar3;
  undefined4 in_EAX;
  int unaff_EBP;
  float *unaff_ESI;
  float10 fVar4;
  
  *(int *)(unaff_EBP + 4) = (int)ROUND(*unaff_ESI);
  *(int *)(unaff_EBP + 8) = (int)ROUND(unaff_ESI[1]);
  *(int *)(unaff_EBP + 0xc) = (int)ROUND(unaff_ESI[2]);
  fVar4 = (float10)FUN_00808266();
  *(int *)(unaff_EBP + 0x10) = (int)ROUND(fVar4 * (float10)_DAT_00808018 * (float10)_DAT_00808028);
  *(int *)(unaff_EBP + 0x18) = (int)ROUND(unaff_ESI[4] * _DAT_00808020 * _DAT_00808018);
  *(int *)(unaff_EBP + 0x18) = *(int *)(unaff_EBP + 0x18) << 1;
  fVar1 = unaff_ESI[6];
  DAT_008c4f04 = (int)ROUND(unaff_ESI[5]);
  fVar2 = -fVar1 * _DAT_00808028;
  cVar3 = (char)DAT_008c4f04;
  if (cVar3 != '\x02') {
    fVar2 = fVar2 - fVar2;
  }
  *(float *)(unaff_EBP + 0x20) = fVar2;
  if (cVar3 == '\x01') {
    fVar1 = -fVar1;
  }
  *(float *)(unaff_EBP + 0x1c) = fVar1;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00808a0b @ 00808a0b ---- */

undefined8 __fastcall FUN_00808a0b(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  float fVar1;
  float *unaff_EBP;
  float10 fVar2;
  
  fVar2 = (float10)(**(code **)(&DAT_008089f7 + ((uint)unaff_EBP[1] & 0xffffff07) * 4))();
  *unaff_EBP = (float)(fVar2 * (float10)unaff_EBP[7] + (float10)unaff_EBP[8]);
  fVar1 = (float)((int)unaff_EBP[5] + (int)unaff_EBP[4]);
  if ((CARRY4((uint)unaff_EBP[5],(uint)unaff_EBP[4])) && (unaff_EBP[3] != 0.0)) {
    fVar1 = -NAN;
  }
  unaff_EBP[5] = fVar1;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00808aa7 @ 00808aa7 ---- */

undefined8 __fastcall FUN_00808aa7(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + 0x1c) = 0;
  *(undefined4 *)(unaff_EBP + 0x24) = 0;
  *(undefined4 *)(unaff_EBP + 0x28) = 0;
  *(undefined4 *)(unaff_EBP + 0x30) = 0;
  *(undefined4 *)(unaff_EBP + 0x34) = 0;
  *(undefined4 *)(unaff_EBP + 0x3c) = 0;
  *(undefined4 *)(unaff_EBP + 0x40) = 0;
  FUN_00808849();
  FUN_00808849();
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00808af9 @ 00808af9 ---- */

undefined8 __fastcall FUN_00808af9(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  uint *unaff_EBP;
  float *unaff_ESI;
  float10 fVar1;
  
  *unaff_EBP = (int)ROUND(*unaff_ESI);
  fVar1 = (float10)FUN_0080827f();
  unaff_EBP[1] = (uint)(float)fVar1;
  (**(code **)(&DAT_00808ad1 + (*unaff_EBP & 0xffffff0f) * 4))();
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00808c29 @ 00808c29 ---- */

undefined8 __fastcall FUN_00808c29(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int *unaff_EBP;
  
  (**(code **)(&DAT_00808c01 + *unaff_EBP * 4))();
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00808d2e @ 00808d2e ---- */

undefined8 __fastcall FUN_00808d2e(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int *unaff_EBP;
  
  (**(code **)(&DAT_00808d06 + *unaff_EBP * 4))();
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00808d88 @ 00808d88 ---- */

undefined8 __fastcall FUN_00808d88(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  
  FUN_0080829f();
  FUN_0080829f();
  FUN_0080829f();
  FUN_008086e6();
  FUN_008086e6();
  FUN_00808849();
  FUN_00808849();
  FUN_0080895d();
  FUN_0080895d();
  FUN_00808aa7();
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00808ddb @ 00808ddb ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_00808ddb(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  FUN_00808776();
  FUN_00808776();
  FUN_00808a0b();
  FUN_00808a0b();
  *(float *)(unaff_EBP + 0x10) =
       (*(float *)(unaff_EBP + 0x114) * _DAT_00808020 - *(float *)(unaff_EBP + 0xc)) * _DAT_00808074
  ;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00808e22 @ 00808e22 ---- */

undefined8 __fastcall FUN_00808e22(int param_1,undefined4 param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 in_EAX;
  int extraout_ECX;
  int iVar4;
  int extraout_ECX_00;
  char extraout_DL;
  int unaff_EBP;
  float *pfVar5;
  undefined4 *puVar6;
  float *pfVar7;
  
  puVar6 = &DAT_008c2c04;
  for (; param_1 != 0; param_1 = param_1 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  FUN_00808377();
  FUN_00808377();
  FUN_00808377();
  if ((char)*(undefined4 *)(unaff_EBP + 0x18) == '\x02') {
    FUN_008088a8();
  }
  FUN_008088a8();
  if (extraout_DL != '\0') {
    if (extraout_DL == '\x02') {
      pfVar5 = (float *)&DAT_008c3064;
      pfVar7 = (float *)&DAT_008c2c04;
      fVar1 = *(float *)(unaff_EBP + 0x24);
      fVar2 = *(float *)(unaff_EBP + 0x28);
      iVar4 = extraout_ECX;
      do {
        fVar3 = *pfVar5;
        pfVar5 = pfVar5 + 1;
        *pfVar7 = *pfVar7 * fVar1 + fVar3 * fVar2;
        pfVar7 = pfVar7 + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    else {
      FUN_008088a8();
    }
  }
  FUN_00808c29();
  pfVar7 = (float *)&DAT_008c34c4;
  pfVar5 = (float *)&DAT_008c2c04;
  fVar1 = *(float *)(unaff_EBP + 0xc);
  iVar4 = extraout_ECX_00;
  do {
    fVar3 = *pfVar5 * fVar1;
    fVar1 = fVar1 + *(float *)(unaff_EBP + 0x10);
    fVar2 = *(float *)(unaff_EBP + 0x20);
    *pfVar7 = fVar3 * *(float *)(unaff_EBP + 0x1c) + *pfVar7;
    pfVar7[1] = fVar3 * fVar2 + pfVar7[1];
    pfVar5 = pfVar5 + 1;
    pfVar7 = pfVar7 + 2;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  *(float *)(unaff_EBP + 0xc) = fVar1;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00808f44 @ 00808f44 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_00808f44(undefined4 param_1,undefined4 param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 in_EAX;
  int *unaff_EBP;
  float *unaff_ESI;
  
  fVar1 = unaff_ESI[1] - _DAT_0080803c;
  unaff_EBP[5] = (int)fVar1;
  fVar1 = fVar1 + (float)*unaff_EBP;
  unaff_EBP[0x19] = (int)fVar1;
  unaff_EBP[0x28] = (int)fVar1;
  unaff_EBP[0x37] = (int)fVar1;
  unaff_EBP[6] = (int)ROUND(unaff_ESI[0x1a]);
  unaff_EBP[0xb] = (int)ROUND(unaff_ESI[0x3a]);
  fVar1 = *unaff_ESI * _DAT_00808020;
  unaff_EBP[7] = (int)SQRT(1.0 - fVar1);
  unaff_EBP[8] = (int)SQRT(fVar1);
  DAT_008c4f04 = (int)ROUND(unaff_ESI[0x1b] - _DAT_0080803c);
  fVar1 = (unaff_ESI[0x1b] - _DAT_0080803c) * _DAT_0080806c;
  if (DAT_008c4f04 < 0) {
    fVar3 = 1.0;
    fVar2 = fVar1 + 1.0;
  }
  else {
    fVar2 = 1.0;
    fVar3 = 1.0 - fVar1;
  }
  unaff_EBP[10] = (int)fVar2;
  unaff_EBP[9] = (int)fVar3;
  FUN_008082f2();
  FUN_008082f2();
  FUN_008082f2();
  FUN_008086ee();
  FUN_008086ee();
  FUN_00808859();
  FUN_00808859();
  FUN_0080896d();
  FUN_0080896d();
  FUN_00808af9();
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_008090be @ 008090be ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_008090be(undefined4 param_1,int param_2)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  float fVar4;
  undefined4 in_EAX;
  uint uVar5;
  int iVar6;
  uint uVar7;
  float fVar8;
  int iVar9;
  
  iVar3 = (&DAT_008c4f58)[param_2];
  if (-1 < iVar3) {
    iVar9 = *(int *)(_DAT_008c4f48 + (uint)(byte)(&DAT_008c5058)[iVar3 * 8] * 4) + _DAT_008c4f48;
    iVar6 = 0;
    do {
      DAT_008c4f04 = (float)(uint)*(byte *)(iVar9 + iVar6);
      *(float *)(&DAT_008c50dc + iVar6 * 4 + param_2 * 0xec) = (float)(int)DAT_008c4f04;
      iVar6 = iVar6 + 1;
    } while ((char)iVar6 != ';');
    pbVar1 = (byte *)(iVar9 + 0x56);
    for (uVar7 = (uint)*(byte *)(iVar9 + 0x55); uVar7 != 0; uVar7 = uVar7 - 1) {
      bVar2 = *pbVar1;
      if (bVar2 == 0) {
        fVar8 = *(float *)(&DAT_008c6e60 + param_2 * 0x228);
      }
      else if (bVar2 < 8) {
        fVar8 = (float)(byte)(&DAT_008c5058)[iVar3 * 8 + (uint)bVar2];
      }
      else if (bVar2 < 0xc) {
        fVar8 = *(float *)((int)(&DAT_008c6e5c + param_2 * 0x228) +
                          *(int *)(&DAT_008090ae + (uint)(bVar2 & 3) * 4));
      }
      else {
        fVar8 = (float)*(int *)(&DAT_008c6e5c + param_2 * 0x228) - _DAT_00808070;
        fVar8 = fVar8 + fVar8;
      }
      DAT_008c4f04 = (float)(uint)pbVar1[1];
      fVar4 = ((float)(int)DAT_008c4f04 - _DAT_0080803c) * _DAT_00808020;
      uVar5 = (uint)pbVar1[2];
      if (uVar5 < 0x3b) {
        DAT_008c4f04 = (fVar4 + fVar4) * fVar8 +
                       *(float *)(&DAT_008c50dc + uVar5 * 4 + param_2 * 0xec);
        fVar8 = DAT_008c4f04;
        if ((int)DAT_008c4f04 < 0) {
          fVar8 = 0.0;
        }
        if (0x43000000 < (uint)fVar8) {
          fVar8 = 128.0;
        }
        *(float *)(&DAT_008c50dc + uVar5 * 4 + param_2 * 0xec) = fVar8;
      }
      pbVar1 = pbVar1 + 3;
    }
    FUN_00808f44();
  }
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_008091f9 @ 008091f9 ---- */

undefined8 __fastcall FUN_008091f9(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_008091fc @ 008091fc ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_008091fc(undefined4 param_1,undefined4 param_2)

{
  float10 fVar1;
  int iVar2;
  undefined4 in_EAX;
  int *unaff_EBP;
  float *unaff_ESI;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  
  DAT_008c4f04 = (int)ROUND(*unaff_ESI);
  iVar2 = DAT_008c4f04;
  *unaff_EBP = DAT_008c4f04;
  if (iVar2 == 0) {
    return CONCAT44(param_2,in_EAX);
  }
  fVar3 = (float10)FUN_0080827f();
  fVar4 = SQRT(((float10)1 + fVar3 * fVar3) - (fVar3 - (float10)1) * (fVar3 - (float10)1)) *
          (float10)_DAT_00821680;
  fVar5 = fVar3 - (float10)1;
  fVar9 = fVar3 + (float10)1;
  fVar1 = (float10)_DAT_00821684;
  fVar6 = fVar5 * (float10)_DAT_00821684;
  fVar8 = (float10)1 / (fVar4 + fVar6 + fVar9);
  fVar7 = fVar5 - fVar9 * fVar1;
  unaff_EBP[4] = (int)(float)((fVar7 + fVar7) * fVar3 * fVar8);
  fVar5 = fVar5 + fVar9 * fVar1;
  unaff_EBP[1] = (int)(float)(-(fVar5 + fVar5) * fVar8);
  unaff_EBP[2] = (int)(float)(((fVar6 + fVar9) - fVar4) * fVar8);
  unaff_EBP[3] = (int)(float)(((fVar9 - fVar6) + fVar4) * fVar8 * fVar3);
  unaff_EBP[5] = (int)(float)(((fVar9 - fVar6) - fVar4) * fVar8 * fVar3);
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_008092a1 @ 008092a1 ---- */

undefined8 __fastcall FUN_008092a1(int param_1,undefined4 param_2)

{
  float fVar1;
  undefined4 in_EAX;
  int unaff_EBP;
  float *unaff_ESI;
  float10 in_ST0;
  float10 in_ST1;
  float10 fVar2;
  float10 in_ST2;
  float10 in_ST3;
  
  do {
    fVar1 = *unaff_ESI;
    fVar2 = (in_ST1 * (float10)*(float *)(unaff_EBP + 0x14) -
            in_ST0 * (float10)*(float *)(unaff_EBP + 8)) +
            (in_ST3 * (float10)*(float *)(unaff_EBP + 0x10) -
            in_ST2 * (float10)*(float *)(unaff_EBP + 4)) +
            (float10)fVar1 * (float10)*(float *)(unaff_EBP + 0xc);
    *unaff_ESI = (float)fVar2;
    unaff_ESI = unaff_ESI + 2;
    param_1 = param_1 + -1;
    in_ST0 = in_ST2;
    in_ST1 = in_ST3;
    in_ST2 = fVar2;
    in_ST3 = (float10)fVar1;
  } while (param_1 != 0);
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_008092d7 @ 008092d7 ---- */

undefined8 __fastcall FUN_008092d7(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  char *unaff_EBP;
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  float10 extraout_ST1;
  float10 extraout_ST1_00;
  
  if (*unaff_EBP != '\0') {
    fVar1 = (float10)*(float *)(unaff_EBP + 0x18);
    fVar2 = (float10)*(float *)(unaff_EBP + 0x28);
    fVar3 = (float10)FUN_008092a1();
    *(float *)(unaff_EBP + 0x30) = (float)fVar3;
    *(float *)(unaff_EBP + 0x20) = (float)extraout_ST1;
    *(float *)(unaff_EBP + 0x28) = (float)fVar2;
    *(float *)(unaff_EBP + 0x18) = (float)fVar1;
    fVar1 = (float10)*(float *)(unaff_EBP + 0x1c);
    fVar2 = (float10)*(float *)(unaff_EBP + 0x2c);
    fVar3 = (float10)FUN_008092a1();
    *(float *)(unaff_EBP + 0x34) = (float)fVar3;
    *(float *)(unaff_EBP + 0x24) = (float)extraout_ST1_00;
    *(float *)(unaff_EBP + 0x2c) = (float)fVar2;
    *(float *)(unaff_EBP + 0x1c) = (float)fVar1;
  }
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_0080931d @ 0080931d ---- */

undefined8 __fastcall FUN_0080931d(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 in_EAX;
  int iVar2;
  int *unaff_EBP;
  undefined4 *puVar3;
  
  unaff_EBP[3] = 0;
  unaff_EBP[6] = 0;
  iVar1 = *unaff_EBP;
  iVar2 = unaff_EBP[2];
  puVar3 = (undefined4 *)unaff_EBP[1];
  do {
    *puVar3 = 0;
    *(undefined4 *)(iVar1 + iVar2 * 4) = 0;
    iVar2 = iVar2 + -1;
    puVar3 = puVar3 + 1;
  } while (-1 < iVar2);
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00809338 @ 00809338 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_00809338(undefined4 param_1,undefined4 param_2)

{
  float fVar1;
  undefined4 in_EAX;
  int unaff_EBP;
  float *unaff_ESI;
  float10 fVar2;
  
  fVar1 = (*unaff_ESI - _DAT_0080803c) * _DAT_00808020;
  fVar1 = fVar1 + fVar1;
  *(float *)(unaff_EBP + 0x30) = fVar1;
  *(float *)(unaff_EBP + 0x2c) = 1.0 - ABS(fVar1);
  fVar1 = (unaff_ESI[1] - _DAT_0080803c) * _DAT_00808020;
  *(float *)(unaff_EBP + 0x28) = fVar1 + fVar1;
  fVar1 = ((float)*(int *)(unaff_EBP + 8) - _DAT_0080805c) * _DAT_00808020;
  *(int *)(unaff_EBP + 0x10) = (int)ROUND(unaff_ESI[2] * fVar1);
  *(int *)(unaff_EBP + 0x14) = (int)ROUND(unaff_ESI[3] * fVar1);
  fVar2 = (float10)FUN_00808266();
  *(int *)(unaff_EBP + 0x1c) = (int)ROUND(fVar2 * (float10)_DAT_00808098 * (float10)_DAT_0082167c);
  *(int *)(unaff_EBP + 0x24) = (int)ROUND(unaff_ESI[5] * _DAT_00808020 * _DAT_0080805c);
  *(int *)(unaff_EBP + 0x20) =
       (int)ROUND((unaff_ESI[6] - _DAT_0080803c) * _DAT_00808020 * _DAT_00808018);
  *(int *)(unaff_EBP + 0x20) = *(int *)(unaff_EBP + 0x20) << 1;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_008093d4 @ 008093d4 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __fastcall FUN_008093d4(undefined4 param_1,int param_2)

{
  int iVar1;
  longlong lVar2;
  uint uVar3;
  int *unaff_EBP;
  float10 in_ST0;
  float10 fVar4;
  float10 in_ST1;
  float10 in_ST2;
  float10 in_ST3;
  float10 in_ST4;
  
  lVar2 = (ulonglong)((unaff_EBP[6] + unaff_EBP[8]) * 2 ^ -(uint)(unaff_EBP[6] + unaff_EBP[8] < 0))
          * (ulonglong)(uint)unaff_EBP[9];
  uVar3 = (param_2 - ((int)((ulonglong)lVar2 >> 0x20) + unaff_EBP[5])) - 1U & unaff_EBP[2];
  iVar1 = unaff_EBP[1];
  fVar4 = (float10)*(float *)(iVar1 + uVar3 * 4);
  *(float *)(iVar1 + param_2 * 4) =
       (float)((fVar4 + ((float10)*(float *)(iVar1 + (uVar3 + 1 & unaff_EBP[2]) * 4) - fVar4) *
                        ((float10)_DAT_00808014 - (float10)(float)((uint)lVar2 >> 9 | 0x3f800000)))
               * in_ST4 + in_ST0);
  lVar2 = (ulonglong)(unaff_EBP[6] << 1 ^ -(uint)(unaff_EBP[6] < 0)) * (ulonglong)(uint)unaff_EBP[9]
  ;
  uVar3 = param_2 - ((int)((ulonglong)lVar2 >> 0x20) + unaff_EBP[4]) & unaff_EBP[2];
  DAT_008c4f04 = (float)((uint)lVar2 >> 9 | 0x3f800000);
  iVar1 = *unaff_EBP;
  fVar4 = (float10)*(float *)(iVar1 + uVar3 * 4);
  fVar4 = fVar4 + ((float10)*(float *)(iVar1 + (uVar3 + 1 & unaff_EBP[2]) * 4) - fVar4) *
                  ((float10)_DAT_00808014 - (float10)DAT_008c4f04);
  *(float *)(iVar1 + param_2 * 4) = (float)(fVar4 * in_ST4 + in_ST1);
  unaff_EBP[6] = unaff_EBP[6] + unaff_EBP[7];
  return in_ST1 * in_ST3 + fVar4 * in_ST2;
}


/* ---- FUN_008094a5 @ 008094a5 ---- */

undefined8 __fastcall FUN_008094a5(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int extraout_ECX;
  undefined4 extraout_EDX;
  int unaff_EBP;
  float *unaff_EDI;
  float10 fVar1;
  float10 extraout_ST1;
  
  if (*(int *)(unaff_EBP + 0x30) != 0) {
    do {
      fVar1 = (float10)FUN_008093d4();
      *unaff_EDI = (float)(fVar1 + (float10)*unaff_EDI);
      unaff_EDI[1] = (float)(extraout_ST1 + (float10)unaff_EDI[1]);
      unaff_EDI = unaff_EDI + 2;
    } while (extraout_ECX != 1);
    *(undefined4 *)(unaff_EBP + 0xc) = extraout_EDX;
  }
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_008094e5 @ 008094e5 ---- */

undefined8 __fastcall FUN_008094e5(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int extraout_ECX;
  undefined4 extraout_EDX;
  int unaff_EBP;
  float *pfVar1;
  float10 fVar2;
  float10 extraout_ST1;
  
  if (*(int *)(unaff_EBP + 0x30) != 0) {
    pfVar1 = (float *)&DAT_008c34c4;
    do {
      fVar2 = (float10)FUN_008093d4();
      *pfVar1 = (float)fVar2;
      pfVar1[1] = (float)extraout_ST1;
      pfVar1 = pfVar1 + 2;
    } while (extraout_ECX != 1);
    *(undefined4 *)(unaff_EBP + 0xc) = extraout_EDX;
  }
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_0080951f @ 0080951f ---- */

undefined8 __fastcall FUN_0080951f(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  undefined1 *unaff_EBP;
  
  *unaff_EBP = 2;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00809527 @ 00809527 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_00809527(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  uint uVar1;
  int iVar2;
  int *unaff_EBP;
  float *unaff_ESI;
  int *piVar3;
  float10 fVar4;
  float10 extraout_ST1;
  
  DAT_008c4f04 = (int)ROUND(*unaff_ESI);
  uVar1 = DAT_008c4f04 - 1;
  DAT_008c4f04 = (int)ROUND(unaff_ESI[1]);
  iVar2 = (uVar1 & 5) + DAT_008c4f04 * 2;
  *unaff_EBP = iVar2;
  if (iVar2 != unaff_EBP[1]) {
    unaff_EBP[1] = iVar2;
    unaff_EBP[0xb] = 0;
    unaff_EBP[0xc] = 0;
    unaff_EBP[0xe] = 0;
    unaff_EBP[0xf] = 0;
    piVar3 = unaff_EBP + 0x2c98;
    for (iVar2 = 0x4000; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar3 = 0;
      piVar3 = piVar3 + 1;
    }
    unaff_EBP[9] = 0x3f800000;
    unaff_EBP[10] = 0x3f800000;
  }
  unaff_EBP[7] = (int)ROUND(unaff_ESI[3] * _DAT_0080809c);
  fVar4 = (float10)FUN_00808266();
  fVar4 = fVar4 + fVar4 + fVar4 + fVar4;
  unaff_EBP[2] = (int)(float)((float10)1 / (fVar4 + fVar4));
  DAT_008c4f04 = (int)ROUND(unaff_ESI[2]);
  fVar4 = (float10)FUN_0080827f();
  unaff_EBP[4] = (int)(float)(fVar4 * extraout_ST1);
  unaff_EBP[3] = (int)(unaff_ESI[5] * _DAT_00808020);
  fVar4 = (float10)FUN_0080827f();
  unaff_EBP[5] = (int)(float)fVar4;
  fVar4 = (float10)FUN_0080827f();
  unaff_EBP[6] = (int)(float)fVar4;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_0080978b @ 0080978b ---- */

undefined8 __fastcall FUN_0080978b(int param_1,uint param_2)

{
  float fVar1;
  float fVar2;
  undefined4 in_EAX;
  uint uVar3;
  int unaff_EBX;
  int unaff_EBP;
  float *unaff_ESI;
  float *unaff_EDI;
  float10 in_ST0;
  float10 fVar4;
  
  uVar3 = param_2;
  do {
    DAT_008c4f04 = (float)in_ST0;
    fVar1 = *(float *)(unaff_EBX + uVar3 * 8);
    *(float *)(unaff_EBX + uVar3 * 8) = *unaff_ESI * *(float *)(unaff_EBP + 8);
    uVar3 = uVar3 + 1;
    if (*(uint *)(unaff_EBP + 0x1c) < uVar3) {
      uVar3 = 0;
    }
    if ((uint)*unaff_EDI < 0x3f800000) {
      fVar4 = (float10)1;
    }
    else {
      fVar4 = (float10)1 /
              ((float10)1 +
              ((float10)*unaff_EDI - (float10)1) * (float10)*(float *)(unaff_EBP + 0xc));
    }
    unaff_EDI = unaff_EDI + 2;
    DAT_008c4f08 = (float)fVar4;
    if ((uint)DAT_008c4f08 < (uint)DAT_008c4f04) {
      fVar2 = *(float *)(unaff_EBP + 0x14);
    }
    else {
      fVar2 = *(float *)(unaff_EBP + 0x18);
    }
    in_ST0 = (fVar4 - in_ST0) * (float10)fVar2 + in_ST0;
    *unaff_ESI = (float)((float10)fVar1 * (float10)*(float *)(unaff_EBP + 0x10) * in_ST0);
    unaff_ESI = unaff_ESI + 2;
    param_1 = param_1 + -1;
  } while (param_1 != 0);
  DAT_008c4f04 = (float)uVar3;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00809818 @ 00809818 ---- */

undefined8 __fastcall FUN_00809818(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int extraout_ECX;
  int iVar1;
  uint *unaff_EBP;
  undefined4 *puVar2;
  char in_FPUStatusWord;
  float10 fVar3;
  
  if ((*unaff_EBP & 4) == 0) {
    (*(code *)(&PTR_LAB_00809808)[*unaff_EBP & 0xffffff03])();
    if (in_FPUStatusWord < '\0') {
      puVar2 = &DAT_008c2c04;
      for (iVar1 = extraout_ECX * 2; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      }
    }
    fVar3 = (float10)FUN_0080978b();
    unaff_EBP[9] = (uint)(float)fVar3;
    fVar3 = (float10)FUN_0080978b();
    unaff_EBP[10] = (uint)(float)fVar3;
    unaff_EBP[8] = DAT_008c4f04;
    return CONCAT44(param_2,in_EAX);
  }
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00809899 @ 00809899 ---- */

undefined8 __fastcall FUN_00809899(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int iVar1;
  undefined1 *unaff_EBP;
  
  for (iVar1 = 0xda70; iVar1 != 0; iVar1 = iVar1 + -1) {
    *unaff_EBP = 0;
    unaff_EBP = unaff_EBP + 1;
  }
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_008098a7 @ 008098a7 ---- */

undefined8 __fastcall FUN_008098a7(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int iVar1;
  int unaff_EBP;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)(unaff_EBP + 0x24);
  for (iVar1 = 0xda4c; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_008098b6 @ 008098b6 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_008098b6(undefined4 param_1,undefined4 param_2)

{
  float fVar1;
  undefined4 in_EAX;
  int extraout_ECX;
  int unaff_EBP;
  int unaff_ESI;
  float10 fVar2;
  
  do {
    fVar2 = (float10)FUN_0080828e();
    *(float *)(unaff_EBP + extraout_ECX * 4) = (float)fVar2;
  } while ((char)extraout_ECX != '\x05');
  *(float *)(unaff_EBP + 0x1c) = *(float *)(unaff_ESI + 4) * _DAT_00808020 * _DAT_0082167c;
  *(float *)(unaff_EBP + 0x18) = *(float *)(unaff_ESI + 0xc) * _DAT_00808020;
  fVar1 = *(float *)(unaff_ESI + 8) * _DAT_00808020;
  fVar1 = fVar1 * fVar1;
  *(float *)(unaff_EBP + 0x20) = fVar1 * fVar1 * _DAT_0082167c;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_0080991f @ 0080991f ---- */

/* WARNING: Removing unreachable block (ram,0x00809b8f) */

undefined8 __fastcall FUN_0080991f(int param_1,undefined4 param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 in_EAX;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float *unaff_EBP;
  float *pfVar10;
  float *unaff_EDI;
  
  pfVar10 = (float *)&DAT_008c3d84;
  fVar1 = unaff_EBP[8];
  fVar2 = unaff_EBP[7];
  do {
    fVar3 = *pfVar10 * unaff_EBP[6];
    pfVar10 = pfVar10 + 1;
    fVar5 = unaff_EBP[9];
    fVar4 = ((unaff_EBP[(int)fVar5 + 0x1f] * *unaff_EBP + fVar3) - unaff_EBP[0x15]) * fVar2 +
            unaff_EBP[0x15];
    unaff_EBP[0x15] = fVar4;
    unaff_EBP[(int)fVar5 + 0x1f] = fVar4;
    fVar5 = (float)((int)fVar5 + 1);
    if (SUB42(fVar5,0) == 0x51d) {
      fVar5 = 0.0;
    }
    unaff_EBP[9] = fVar5;
    fVar5 = unaff_EBP[10];
    fVar9 = ((unaff_EBP[(int)fVar5 + 0x53c] * unaff_EBP[1] - fVar3) - unaff_EBP[0x16]) * fVar2 +
            unaff_EBP[0x16];
    unaff_EBP[0x16] = fVar9;
    unaff_EBP[(int)fVar5 + 0x53c] = fVar9;
    fVar5 = (float)((int)fVar5 + 1);
    if (SUB42(fVar5,0) == 0x663) {
      fVar5 = 0.0;
    }
    unaff_EBP[10] = fVar5;
    fVar5 = unaff_EBP[0xb];
    fVar7 = ((unaff_EBP[(int)fVar5 + 0xb9f] * unaff_EBP[2] + fVar3) - unaff_EBP[0x17]) * fVar2 +
            unaff_EBP[0x17];
    unaff_EBP[0x17] = fVar7;
    unaff_EBP[(int)fVar5 + 0xb9f] = fVar7;
    fVar5 = (float)((int)fVar5 + 1);
    if (SUB42(fVar5,0) == 0x713) {
      fVar5 = 0.0;
    }
    unaff_EBP[0xb] = fVar5;
    fVar5 = unaff_EBP[0xc];
    fVar8 = ((unaff_EBP[(int)fVar5 + 0x12b2] * unaff_EBP[3] - fVar3) - unaff_EBP[0x18]) * fVar2 +
            unaff_EBP[0x18];
    unaff_EBP[0x18] = fVar8;
    unaff_EBP[(int)fVar5 + 0x12b2] = fVar8;
    fVar5 = (float)((int)fVar5 + 1);
    if (SUB42(fVar5,0) == 0x786) {
      fVar5 = 0.0;
    }
    unaff_EBP[0xc] = fVar5;
    fVar6 = unaff_EBP[0xd];
    fVar5 = unaff_EBP[(int)fVar6 + 0x1a38];
    fVar4 = fVar5 * unaff_EBP[4] + fVar8 + fVar7 + fVar9 + fVar4;
    unaff_EBP[(int)fVar6 + 0x1a38] = fVar4;
    fVar6 = (float)((int)fVar6 + 1);
    if (SUB41(fVar6,0) == -0x24) {
      fVar6 = 0.0;
    }
    unaff_EBP[0xd] = fVar6;
    fVar7 = unaff_EBP[0xe];
    fVar9 = unaff_EBP[(int)fVar7 + 0x1b14];
    fVar5 = fVar9 * unaff_EBP[5] + (fVar5 - fVar4 * unaff_EBP[4]);
    unaff_EBP[(int)fVar7 + 0x1b14] = fVar5;
    fVar9 = fVar9 - fVar5 * unaff_EBP[5];
    fVar7 = (float)((int)fVar7 + 1);
    if (SUB41(fVar7,0) == 'J') {
      fVar7 = 0.0;
    }
    unaff_EBP[0xe] = fVar7;
    fVar5 = (fVar9 - unaff_EBP[0x1d]) * fVar1 + unaff_EBP[0x1d];
    unaff_EBP[0x1d] = fVar5;
    *unaff_EDI = (fVar9 - fVar5) + *unaff_EDI;
    fVar5 = unaff_EBP[0xf];
    fVar4 = ((unaff_EBP[(int)fVar5 + 0x1b5e] * *unaff_EBP + fVar3) - unaff_EBP[0x19]) * fVar2 +
            unaff_EBP[0x19];
    unaff_EBP[0x19] = fVar4;
    unaff_EBP[(int)fVar5 + 0x1b5e] = fVar4;
    fVar5 = (float)((int)fVar5 + 1);
    if (SUB42(fVar5,0) == 0x52f) {
      fVar5 = 0.0;
    }
    unaff_EBP[0xf] = fVar5;
    fVar5 = unaff_EBP[0x10];
    fVar9 = ((unaff_EBP[(int)fVar5 + 0x208d] * unaff_EBP[1] - fVar3) - unaff_EBP[0x1a]) * fVar2 +
            unaff_EBP[0x1a];
    unaff_EBP[0x1a] = fVar9;
    unaff_EBP[(int)fVar5 + 0x208d] = fVar9;
    fVar5 = (float)((int)fVar5 + 1);
    if (SUB42(fVar5,0) == 0x65f) {
      fVar5 = 0.0;
    }
    unaff_EBP[0x10] = fVar5;
    fVar5 = unaff_EBP[0x11];
    fVar7 = ((unaff_EBP[(int)fVar5 + 0x26ec] * unaff_EBP[2] + fVar3) - unaff_EBP[0x1b]) * fVar2 +
            unaff_EBP[0x1b];
    unaff_EBP[0x1b] = fVar7;
    unaff_EBP[(int)fVar5 + 0x26ec] = fVar7;
    fVar5 = (float)((int)fVar5 + 1);
    if (SUB42(fVar5,0) == 0x729) {
      fVar5 = 0.0;
    }
    unaff_EBP[0x11] = fVar5;
    fVar5 = unaff_EBP[0x12];
    fVar3 = ((unaff_EBP[(int)fVar5 + 0x2e15] * unaff_EBP[3] - fVar3) - unaff_EBP[0x1c]) * fVar2 +
            unaff_EBP[0x1c];
    unaff_EBP[0x1c] = fVar3;
    unaff_EBP[(int)fVar5 + 0x2e15] = fVar3;
    fVar5 = (float)((int)fVar5 + 1);
    if (SUB42(fVar5,0) == 0x76d) {
      fVar5 = 0.0;
    }
    unaff_EBP[0x12] = fVar5;
    fVar8 = unaff_EBP[0x13];
    fVar5 = unaff_EBP[(int)fVar8 + 0x3582];
    fVar4 = fVar5 * unaff_EBP[4] + fVar3 + fVar7 + fVar9 + fVar4;
    unaff_EBP[(int)fVar8 + 0x3582] = fVar4;
    fVar8 = (float)((int)fVar8 + 1);
    if (SUB41(fVar8,0) == -0x33) {
      fVar8 = 0.0;
    }
    unaff_EBP[0x13] = fVar8;
    fVar9 = unaff_EBP[0x14];
    fVar3 = unaff_EBP[(int)fVar9 + 0x364f];
    fVar5 = fVar3 * unaff_EBP[5] + (fVar5 - fVar4 * unaff_EBP[4]);
    unaff_EBP[(int)fVar9 + 0x364f] = fVar5;
    fVar3 = fVar3 - fVar5 * unaff_EBP[5];
    fVar9 = (float)((int)fVar9 + 1);
    if (SUB41(fVar9,0) == 'M') {
      fVar9 = 0.0;
    }
    unaff_EBP[0x14] = fVar9;
    fVar5 = (fVar3 - unaff_EBP[0x1e]) * fVar1 + unaff_EBP[0x1e];
    unaff_EBP[0x1e] = fVar5;
    unaff_EDI[1] = (fVar3 - fVar5) + unaff_EDI[1];
    unaff_EDI = unaff_EDI + 2;
    param_1 = param_1 + -1;
  } while (param_1 != 0);
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00809b96 @ 00809b96 ---- */

undefined8 __fastcall FUN_00809b96(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  
  FUN_00808aa7();
  FUN_0080931d();
  FUN_0080951f();
  FUN_008091f9();
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00809bbc @ 00809bbc ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_00809bbc(undefined4 param_1,undefined4 param_2)

{
  float fVar1;
  undefined4 in_EAX;
  float *unaff_EBP;
  float *unaff_ESI;
  
  fVar1 = *unaff_ESI * _DAT_00808020 * _DAT_00808090;
  *unaff_EBP = fVar1;
  unaff_EBP[1] = unaff_ESI[1] * _DAT_00808020 * _DAT_00808094 * fVar1;
  unaff_EBP[2] = unaff_ESI[2] * _DAT_00808020 * _DAT_00808094 * fVar1;
  unaff_EBP[3] = (float)(int)ROUND(unaff_ESI[3]);
  FUN_00808af9();
  FUN_00809338();
  FUN_00809527();
  FUN_008091fc();
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00809c2d @ 00809c2d ---- */

undefined8 __fastcall FUN_00809c2d(undefined4 param_1,undefined4 param_2)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 in_EAX;
  int extraout_ECX;
  int extraout_ECX_00;
  int iVar5;
  int iVar6;
  float *unaff_EBP;
  float *pfVar7;
  float *pfVar8;
  
  pfVar7 = (float *)&DAT_008c34c4;
  FUN_00809818();
  FUN_008092d7();
  if (unaff_EBP[3] == 0.0) {
    FUN_00808d2e();
    FUN_008094e5();
    iVar6 = extraout_ECX;
  }
  else {
    FUN_008094e5();
    FUN_00808d2e();
    iVar6 = extraout_ECX_00;
  }
  if (unaff_EBP[1] != 0.0) {
    pfVar8 = (float *)&DAT_008c3d84;
    iVar5 = iVar6;
    do {
      fVar2 = *pfVar7;
      pfVar1 = pfVar7 + 1;
      pfVar7 = pfVar7 + 2;
      *pfVar8 = (fVar2 + *pfVar1) * unaff_EBP[1] + *pfVar8;
      pfVar8 = pfVar8 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  pfVar7 = (float *)&DAT_008c34c4;
  if (unaff_EBP[2] != 0.0) {
    pfVar8 = (float *)&DAT_008c41e4;
    iVar5 = iVar6;
    do {
      fVar2 = *pfVar7;
      pfVar1 = pfVar7 + 1;
      pfVar7 = pfVar7 + 2;
      *pfVar8 = (fVar2 + *pfVar1) * unaff_EBP[2] + *pfVar8;
      pfVar8 = pfVar8 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  pfVar7 = (float *)&DAT_008c34c4;
  pfVar8 = (float *)&DAT_008c4644;
  do {
    fVar2 = *pfVar7;
    fVar3 = pfVar7[1];
    fVar4 = *unaff_EBP;
    pfVar7 = pfVar7 + 2;
    *pfVar8 = fVar2 * *unaff_EBP + *pfVar8;
    pfVar8[1] = fVar3 * fVar4 + pfVar8[1];
    pfVar8 = pfVar8 + 2;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00809cfa @ 00809cfa ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_00809cfa(undefined4 param_1,undefined4 param_2)

{
  float *pfVar1;
  byte *pbVar2;
  byte bVar3;
  float fVar4;
  undefined4 in_EAX;
  int iVar5;
  uint uVar6;
  float fVar7;
  int unaff_EBX;
  float *pfVar8;
  int iVar9;
  
  iVar9 = *(int *)(_DAT_008c4f48 + (uint)(byte)(&DAT_008c5058)[unaff_EBX * 8] * 4) + _DAT_008c4f48;
  pfVar1 = (float *)(&DAT_008cb35c + unaff_EBX * 100);
  iVar5 = 0x3b;
  pfVar8 = pfVar1;
  do {
    DAT_008c4f04 = (float)(uint)*(byte *)(iVar9 + iVar5);
    *pfVar8 = (float)(int)DAT_008c4f04;
    pfVar8 = pfVar8 + 1;
    iVar5 = iVar5 + 1;
  } while ((char)iVar5 != 'T');
  uVar6 = (uint)*(byte *)(iVar9 + 0x55);
  pbVar2 = (byte *)(iVar9 + 0x56);
  do {
    if (uVar6 == 0) {
      FUN_00809bbc();
      return CONCAT44(param_2,in_EAX);
    }
    if ((0x3a < pbVar2[2]) && (pbVar2[2] < 0x54)) {
      bVar3 = *pbVar2;
      if (bVar3 == 0) {
        fVar7 = *(float *)(&DAT_008cb9a0 + unaff_EBX * 0x1b350);
      }
      else {
        if (7 < bVar3) goto LAB_00809df2;
        fVar7 = (float)(byte)(&DAT_008c5058)[unaff_EBX * 8 + (uint)bVar3];
      }
      fVar4 = ((float)pbVar2[1] - _DAT_0080803c) * _DAT_00808020;
      DAT_008c4f04 = (fVar4 + fVar4) * fVar7 + pfVar1[(byte)(pbVar2[2] - 0x3b)];
      fVar7 = DAT_008c4f04;
      if ((int)DAT_008c4f04 < 0) {
        fVar7 = 0.0;
      }
      if (0x43000000 < (uint)fVar7) {
        fVar7 = 128.0;
      }
      pfVar1[(byte)(pbVar2[2] - 0x3b)] = fVar7;
    }
LAB_00809df2:
    pbVar2 = pbVar2 + 3;
    uVar6 = uVar6 - 1;
  } while( true );
}


/* ---- FUN_00809e04 @ 00809e04 ---- */

undefined8 __fastcall FUN_00809e04(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  
  FUN_00806e8d();
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00809e1c @ 00809e1c ---- */

undefined8 __fastcall FUN_00809e1c(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  
  FUN_00806f4c();
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00809e24 @ 00809e24 ---- */

undefined8 __fastcall FUN_00809e24(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  undefined4 unaff_ESI;
  
  FUN_008072b4(unaff_ESI,param_1);
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00809e2e @ 00809e2e ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall
FUN_00809e2e(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 in_EAX;
  int iVar1;
  int extraout_ECX;
  int extraout_ECX_00;
  undefined *puVar2;
  undefined1 *puVar3;
  
  FUN_00806e4c(param_4);
  puVar3 = &DAT_008c4f48;
  for (iVar1 = 0x1e2cc8; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  _DAT_008c4f54 = param_4;
  FUN_008081e9();
  _DAT_008c4f48 = param_3;
  do {
    FUN_00808d88();
    *(undefined4 *)(&DAT_008c4f54 + extraout_ECX * 4) = 0xffffffff;
  } while (extraout_ECX != 1);
  iVar1 = 0;
  puVar2 = &DAT_008cb99c;
  do {
    (&DAT_008c505f)[iVar1 * 8] = 0x7f;
    *(undefined **)(puVar2 + 0xbc) = &DAT_00882c04 + iVar1 * 0x4000;
    *(int *)(puVar2 + 0xc0) = iVar1 * 0x4000 + 0x884c04;
    *(undefined4 *)(puVar2 + 0xc4) = 0x7ff;
    FUN_00809b96();
    puVar2 = puVar2 + 0x1b350;
    iVar1 = extraout_ECX_00 + 1;
  } while ((char)iVar1 != '\x10');
  FUN_00809899();
  DAT_00a8c964 = &DAT_00842c04;
  DAT_00a8c968 = &DAT_00862c04;
  DAT_00a8c96c = 0x7fff;
  FUN_0080931d();
  FUN_00809e04();
  FUN_0080951f();
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_00809f08 @ 00809f08 ---- */

undefined8 __fastcall
FUN_00809f08(undefined4 param_1,undefined4 param_2,int *param_3,int param_4,int *param_5,int param_6
            )

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 in_EAX;
  int iVar4;
  int extraout_EDX;
  char cVar5;
  int *piVar6;
  ushort in_FPUControlWord;
  
  DAT_008c4f04._0_2_ = in_FPUControlWord & 0xf0ff | 0x3f;
  DAT_00aa7c10 = param_4;
  DAT_00aa7c20 = param_6;
  DAT_00aa7c1c = param_5;
  DAT_00aa7c18 = param_3;
  DAT_008c4f44 = in_FPUControlWord;
  while (DAT_00aa7c10 != 0) {
    if (DAT_008c50d8 == 0) {
      iVar4 = 0;
      do {
        if (-1 < (int)(&DAT_008c4f58)[iVar4]) {
          FUN_008090be();
          FUN_00808ddb();
          iVar1 = iVar4 * 0x8a;
          iVar4 = extraout_EDX;
          if ((&DAT_008c6f74)[iVar1] == 0) {
            (&DAT_008c4f58)[extraout_EDX] = 0xffffffff;
          }
        }
        iVar4 = iVar4 + 1;
      } while ((char)iVar4 != ' ');
      cVar5 = '\0';
      do {
        FUN_00809cfa();
        cVar5 = cVar5 + '\x01';
      } while (cVar5 != '\x10');
      FUN_00809e1c();
      DAT_008c50d8 = DAT_00821688;
      FUN_0080a074();
    }
    piVar6 = &DAT_008c4644 + (DAT_00821688 - DAT_008c50d8) * 2;
    iVar4 = DAT_008c50d8;
    if (DAT_00aa7c10 < DAT_008c50d8) {
      iVar4 = DAT_00aa7c10;
    }
    DAT_00aa7c10 = DAT_00aa7c10 - iVar4;
    DAT_008c50d8 = DAT_008c50d8 - iVar4;
    if (DAT_00aa7c1c == (int *)0x0) {
      for (iVar4 = iVar4 << 1; iVar4 != 0; iVar4 = iVar4 + -1) {
        *DAT_00aa7c18 = *piVar6;
        piVar6 = piVar6 + 1;
        DAT_00aa7c18 = DAT_00aa7c18 + 1;
      }
    }
    else if (DAT_00aa7c20 == 0) {
      do {
        iVar1 = *piVar6;
        iVar2 = piVar6[1];
        piVar6 = piVar6 + 2;
        *DAT_00aa7c18 = iVar1;
        DAT_00aa7c18 = DAT_00aa7c18 + 1;
        *DAT_00aa7c1c = iVar2;
        DAT_00aa7c1c = DAT_00aa7c1c + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    else {
      do {
        iVar1 = *DAT_00aa7c1c;
        iVar2 = *piVar6;
        iVar3 = piVar6[1];
        piVar6 = piVar6 + 2;
        *DAT_00aa7c18 = *DAT_00aa7c18 + iVar2;
        DAT_00aa7c18 = DAT_00aa7c18 + 1;
        *DAT_00aa7c1c = iVar1 + iVar3;
        DAT_00aa7c1c = DAT_00aa7c1c + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
  }
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_0080a074 @ 0080a074 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_0080a074(int param_1,undefined4 param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 in_EAX;
  int iVar4;
  int iVar5;
  int extraout_EDX;
  float *pfVar6;
  undefined4 *puVar7;
  
  puVar7 = &DAT_008c4644;
  DAT_00aa7c14 = param_1;
  for (iVar4 = param_1 << 1; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  puVar7 = &DAT_008c3d84;
  for (iVar4 = DAT_00aa7c14; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  puVar7 = &DAT_008c41e4;
  for (iVar4 = DAT_00aa7c14; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  iVar4 = 0;
  do {
    iVar5 = 0;
    while (iVar4 != (&DAT_008c4f58)[iVar5]) {
      iVar5 = iVar5 + 1;
      if ((char)iVar5 == ' ') goto LAB_0080a127;
    }
    puVar7 = &DAT_008c34c4;
    for (iVar5 = DAT_00aa7c14 << 1; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    iVar5 = 0;
    do {
      if (iVar4 == (&DAT_008c4f58)[iVar5]) {
        FUN_00808e22();
        iVar5 = extraout_EDX;
      }
      iVar5 = iVar5 + 1;
    } while ((char)iVar5 != ' ');
    if ((char)iVar4 == '\x0f') {
      FUN_00809e24();
    }
    FUN_00809c2d();
LAB_0080a127:
    iVar4 = iVar4 + 1;
    if ((char)iVar4 == '\x10') {
      FUN_0080991f();
      FUN_008094a5();
      fVar3 = DAT_00aa7c04;
      pfVar6 = (float *)&DAT_008c4644;
      iVar4 = DAT_00aa7c14;
      do {
        fVar2 = *pfVar6 - _DAT_00aa7bfc;
        _DAT_00aa7bfc = fVar2 * _DAT_00aa7bf8 + _DAT_00aa7bfc;
        fVar1 = pfVar6[1] - _DAT_00aa7c00;
        _DAT_00aa7c00 = fVar1 * _DAT_00aa7bf8 + _DAT_00aa7c00;
        if (fVar3 != 1.0) {
          fVar2 = (fVar2 - _DAT_00aa7c08) * DAT_00aa7c04 + _DAT_00aa7c08;
          fVar1 = (fVar1 - _DAT_00aa7c0c) * DAT_00aa7c04 + _DAT_00aa7c0c;
          _DAT_00aa7c0c = fVar1;
          _DAT_00aa7c08 = fVar2;
        }
        *pfVar6 = fVar2;
        pfVar6[1] = fVar1;
        pfVar6 = pfVar6 + 2;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
      FUN_00809818();
      return CONCAT44(param_2,in_EAX);
    }
  } while( true );
}


/* ---- FUN_0080a222 @ 0080a222 ---- */

undefined8 __fastcall FUN_0080a222(undefined4 param_1,undefined4 param_2,byte *param_3)

{
  byte bVar1;
  undefined4 in_EAX;
  ushort in_FPUControlWord;
  
  DAT_008c4f04._0_2_ = in_FPUControlWord & 0xf0ff | 0x3f;
  DAT_008c4f44 = in_FPUControlWord;
  do {
    bVar1 = *param_3;
    if ((bVar1 & 0x80) != 0) {
      if (bVar1 == 0xfd) {
LAB_0080a257:
        return CONCAT44(param_2,in_EAX);
      }
      param_3 = param_3 + 1;
      DAT_008c4f4c = (uint)bVar1;
    }
    if ((DAT_008c4f4c >> 4 & 8) == 0) goto LAB_0080a257;
    (**(code **)(&DAT_0080a202 + (DAT_008c4f4c >> 4 & 7) * 4))();
  } while( true );
}


/* ---- FUN_0080a530 @ 0080a530 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __fastcall FUN_0080a530(undefined4 param_1,undefined4 param_2,byte *param_3)

{
  float fVar1;
  undefined4 in_EAX;
  int iVar2;
  float *pfVar3;
  
  pfVar3 = (float *)&DAT_00a7ee9c;
  iVar2 = 0x16;
  do {
    DAT_008c4f04 = (uint)*param_3;
    *pfVar3 = (float)DAT_008c4f04;
    pfVar3 = pfVar3 + 1;
    iVar2 = iVar2 + -1;
    param_3 = param_3 + 1;
  } while (iVar2 != 0);
  FUN_008098b6();
  FUN_00809338();
  FUN_00809527();
  fVar1 = (_DAT_00a7eec8 + 1.0) * _DAT_00808020;
  _DAT_00aa7bf8 = fVar1 * fVar1;
  fVar1 = (_DAT_00a7eecc + 1.0) * _DAT_00808020;
  DAT_00aa7c04 = fVar1 * fVar1;
  return CONCAT44(param_2,in_EAX);
}


/* ---- FUN_0080a608 @ 0080a608 ---- */

uint FUN_0080a608(void)

{
  int *piVar1;
  int *piVar2;
  uint in_EAX;
  uint *unaff_EDI;
  
  piVar2 = (int *)*unaff_EDI;
  if (1 < piVar2[2]) {
    in_EAX = (**(code **)(*piVar2 + 4))();
    *unaff_EDI = in_EAX;
    piVar1 = piVar2 + 2;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      in_EAX = (**(code **)*piVar2)(1);
    }
  }
  return in_EAX & 0xffffff00;
}


/* ---- FUN_0080a62b @ 0080a62b ---- */

int __fastcall FUN_0080a62b(int param_1)

{
  int iVar1;
  
  if (param_1 < 0) {
    return 0;
  }
  iVar1 = 0x7fff;
  if (param_1 < 0x8000) {
    iVar1 = param_1;
  }
  return iVar1;
}


/* ---- FUN_0080a63e @ 0080a63e ---- */

ulonglong __fastcall FUN_0080a63e(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (param_1 >> 0x18) << 0x10 | (param_1 & 0xff0000) >> 0x10;
  uVar2 = (param_1 & 0xff00) << 8 | param_1 & 0xff;
  return CONCAT44(uVar1 << 7 | uVar1 >> 1,uVar2 << 7 | uVar2 >> 1) & 0x7fff7fff7fff7fff;
}


/* ---- FUN_0080a6b3 @ 0080a6b3 ---- */

void __fastcall
FUN_0080a6b3(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,int param_4)

{
  undefined2 uVar1;
  uint uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  
  uVar2 = param_4 >> 1;
  uVar3 = packssdw((ulonglong)uVar2,(ulonglong)uVar2);
  uVar1 = (undefined2)uVar3;
  uVar4 = pmulhw(*param_3,CONCAT44(CONCAT22(uVar1,uVar1),CONCAT22(uVar1,uVar1)));
  uVar3 = packssdw((ulonglong)(0x8000 - uVar2),(ulonglong)(0x8000 - uVar2));
  uVar1 = (undefined2)uVar3;
  uVar3 = pmulhw(*param_2,CONCAT44(CONCAT22(uVar1,uVar1),CONCAT22(uVar1,uVar1)));
  uVar3 = psllw(CONCAT26((short)((ulonglong)uVar3 >> 0x30) + (short)((ulonglong)uVar4 >> 0x30),
                         CONCAT24((short)((ulonglong)uVar3 >> 0x20) +
                                  (short)((ulonglong)uVar4 >> 0x20),
                                  CONCAT22((short)((ulonglong)uVar3 >> 0x10) +
                                           (short)((ulonglong)uVar4 >> 0x10),
                                           (short)uVar3 + (short)uVar4))),1);
  *param_1 = uVar3;
  return;
}


/* ---- FUN_0080a709 @ 0080a709 ---- */

void __fastcall
FUN_0080a709(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,int param_4)

{
  undefined2 uVar1;
  undefined8 uVar2;
  short sVar3;
  short sVar5;
  short sVar6;
  short sVar7;
  undefined8 uVar4;
  
  uVar4 = *param_2;
  uVar2 = packssdw((ulonglong)(uint)(param_4 >> 1),(ulonglong)(uint)(param_4 >> 1));
  uVar1 = (undefined2)uVar2;
  uVar2 = pmulhw(*param_3,CONCAT44(CONCAT22(uVar1,uVar1),CONCAT22(uVar1,uVar1)));
  sVar3 = ((ushort)uVar4 >> 1) + (short)uVar2;
  sVar5 = ((ushort)((ulonglong)uVar4 >> 0x10) >> 1) + (short)((ulonglong)uVar2 >> 0x10);
  sVar6 = ((ushort)((ulonglong)uVar4 >> 0x20) >> 1) + (short)((ulonglong)uVar2 >> 0x20);
  sVar7 = (ushort)((ulonglong)uVar4 >> 0x31) + (short)((ulonglong)uVar2 >> 0x30);
  uVar4 = psllw(CONCAT26((ushort)(0x3fff < sVar7) * 0x3fff | (ushort)(0x3fff >= sVar7) * sVar7,
                         CONCAT24((ushort)(0x3fff < sVar6) * 0x3fff |
                                  (ushort)(0x3fff >= sVar6) * sVar6,
                                  CONCAT22((ushort)(0x3fff < sVar5) * 0x3fff |
                                           (ushort)(0x3fff >= sVar5) * sVar5,
                                           (ushort)(0x3fff < sVar3) * 0x3fff |
                                           (ushort)(0x3fff >= sVar3) * sVar3))),1);
  *param_1 = uVar4;
  return;
}


/* ---- FUN_0080a757 @ 0080a757 ---- */

uint __fastcall FUN_0080a757(uint param_1,uint param_2,int param_3)

{
  if (param_3 == 0) {
    param_1 = param_1 & param_2;
  }
  else if ((int)param_1 < 0) {
    param_1 = 0;
  }
  else if ((int)param_2 < (int)param_1) {
    param_1 = param_2;
  }
  return param_1;
}


/* ---- FUN_0080a778 @ 0080a778 ---- */

void __fastcall
FUN_0080a778(undefined4 param_1,int param_2,int param_3,undefined4 param_4,undefined2 param_5,
            undefined2 param_6,uint param_7)

{
  int iVar1;
  undefined4 extraout_ECX;
  
  FUN_0080a757(param_7 & 2);
  iVar1 = FUN_0080a757(param_7 & 2);
  param_2 = param_2 + iVar1 * param_3 * 8;
  iVar1 = FUN_0080a757(param_7 & 1);
  FUN_0080a6b3(iVar1 * 8 + param_2,param_6);
  iVar1 = FUN_0080a757(param_7 & 1);
  FUN_0080a6b3(iVar1 * 8 + param_2,param_6);
  FUN_0080a6b3(extraout_ECX,param_5);
  return;
}


/* ---- FUN_0080a831 @ 0080a831 ---- */

int __fastcall FUN_0080a831(uint param_1)

{
  return ((int)((*(int *)(&DAT_00aa7c34 + ((int)param_1 >> 5) * 4) -
                (&DAT_00aa7c30)[(int)param_1 >> 5]) * (param_1 & 0x1f)) >> 5) +
         (&DAT_00aa7c30)[(int)param_1 >> 5];
}


/* ---- Bitmap_Format @ 0080a853 ---- */

int Bitmap_Format(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_2 < 1) {
    param_1 = 0;
  }
  else {
    FUN_0080a608();
    *(int *)(param_1 + 0x1c) = param_2;
    *(undefined4 *)(param_1 + 0x24) = param_3;
    *(undefined4 *)(param_1 + 0x28) = param_4;
  }
  return param_1;
}


/* ---- FUN_0080a883 @ 0080a883 ---- */

void FUN_0080a883(undefined4 param_1,undefined8 *param_2,undefined4 param_3,int param_4)

{
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = (code *)&LAB_0080a9a8;
  if (((((-1 < param_4 + -1) && (UNRECOVERED_JUMPTABLE = (code *)&LAB_0080a9b5, -1 < param_4 + -2))
       && (UNRECOVERED_JUMPTABLE = (code *)&LAB_0080a9c2, -1 < param_4 + -3)) &&
      (((UNRECOVERED_JUMPTABLE = (code *)&LAB_0080a9d3, -1 < param_4 + -4 &&
        (UNRECOVERED_JUMPTABLE = (code *)&LAB_0080a9e7, -1 < param_4 + -5)) &&
       ((UNRECOVERED_JUMPTABLE = (code *)&LAB_0080aa20, -1 < param_4 + -6 &&
        ((UNRECOVERED_JUMPTABLE = (code *)&LAB_0080aa30, -1 < param_4 + -7 &&
         (UNRECOVERED_JUMPTABLE = (code *)&LAB_0080aa3c, -1 < param_4 + -8)))))))) &&
     ((UNRECOVERED_JUMPTABLE = (code *)&LAB_0080aa48, -1 < param_4 + -9 &&
      (((((UNRECOVERED_JUMPTABLE = (code *)&LAB_0080aa7d, -1 < param_4 + -10 &&
          (UNRECOVERED_JUMPTABLE = (code *)&LAB_0080aa89, -1 < param_4 + -0xb)) &&
         (UNRECOVERED_JUMPTABLE = (code *)&LAB_0080aaaf, -1 < param_4 + -0xc)) &&
        ((UNRECOVERED_JUMPTABLE = (code *)&LAB_0080aad3, -1 < param_4 + -0xd &&
         (UNRECOVERED_JUMPTABLE = (code *)&LAB_0080aaf7, -1 < param_4 + -0xe)))) &&
       ((UNRECOVERED_JUMPTABLE = (code *)&LAB_0080ab01, -1 < param_4 + -0xf &&
        (UNRECOVERED_JUMPTABLE = (code *)&LAB_0080ab29, -1 < param_4 + -0x10)))))))) {
    psubsw(param_2[1],*param_2);
    UNRECOVERED_JUMPTABLE = (code *)&LAB_0080ab59;
  }
                    /* WARNING: Could not recover jumptable at 0x0080a9a6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}


/* ---- Bitmap_Merge @ 0080ab7c ---- */

int Bitmap_Merge(int param_1,int param_2,int param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  if (param_3 == 0) {
    return 0;
  }
  iVar4 = 1;
  if (((*(int *)(param_3 + 4) == 1) && (-1 < param_1)) && (param_1 < 6)) {
    if (param_1 == 5) {
      param_1 = 0xc;
    }
    iVar3 = iVar4;
    if (1 < param_2) {
      do {
        if ((&param_3)[iVar3] == 0) break;
        if (*(int *)((&param_3)[iVar3] + 4) != 1) goto LAB_0080ac0a;
        iVar3 = iVar3 + 1;
      } while (iVar3 < param_2);
    }
    FUN_0080a608();
    iVar3 = param_3;
    if (1 < param_2) {
      do {
        puVar2 = (undefined4 *)(&param_3)[iVar4];
        if (puVar2 == (undefined4 *)0x0) {
          return iVar3;
        }
        FUN_0080a883(*(undefined4 *)(iVar3 + 0xc),puVar2[3],*(undefined4 *)(iVar3 + 0x18),param_1,0)
        ;
        piVar1 = puVar2 + 2;
        *piVar1 = *piVar1 + -1;
        if (*piVar1 == 0) {
          (**(code **)*puVar2)(1);
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < param_2);
    }
  }
  else {
LAB_0080ac0a:
    iVar3 = 0;
  }
  return iVar3;
}


/* ---- Bitmap_Color @ 0080ac0f ---- */

int Bitmap_Color(int param_1,int param_2)

{
  undefined8 local_c;
  
  if ((param_2 < 0) || (5 < param_2)) {
    param_1 = 0;
  }
  else {
    FUN_0080a608();
    local_c = FUN_0080a63e();
    FUN_0080a883(*(undefined4 *)(param_1 + 0xc),&local_c,*(undefined4 *)(param_1 + 0x18),param_2 + 5
                 ,0);
  }
  return param_1;
}


/* ---- Bitmap_Range @ 0080ac5c ---- */

int Bitmap_Range(int param_1,uint param_2)

{
  undefined8 local_14;
  undefined8 local_c;
  
  if (((int)param_2 < 0) || (5 < (int)param_2)) {
    param_1 = 0;
  }
  else {
    FUN_0080a608();
    local_14 = FUN_0080a63e();
    local_c = FUN_0080a63e();
    if ((param_2 & 1) != 0) {
      FUN_0080a883(*(undefined4 *)(param_1 + 0xc),&local_14,*(undefined4 *)(param_1 + 0x18),8,0);
    }
    FUN_0080a883(*(undefined4 *)(param_1 + 0xc),&local_14,*(undefined4 *)(param_1 + 0x18),0x10,0);
  }
  return param_1;
}


/* ---- Bitmap_GlowRect @ 0080accf ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Bitmap_GlowRect(int param_1,float param_2,float param_3,float param_4,float param_5,
                   float param_6,float param_7,undefined4 param_8,float param_9,float param_10,
                   int param_11,int param_12)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  float10 fVar8;
  undefined8 local_18;
  float local_10;
  float local_c;
  float local_8;
  
  if (param_11 == 1) {
    if (_DAT_0081f2bc < param_2 + param_4 + param_6) {
      param_1 = Bitmap_GlowRect(param_1,param_2 - _DAT_0081f2bc,param_3,param_4,param_5,param_6,
                                param_7,param_8,param_9,param_10,2,param_12);
    }
    if ((param_2 - param_4) - param_6 < _DAT_0081f374) {
      param_1 = Bitmap_GlowRect(param_1,param_2 + _DAT_0081f2bc,param_3,param_4,param_5,param_6,
                                param_7,param_8,param_9,param_10,2,param_12);
    }
  }
  else if (param_11 != 2) goto LAB_0080ae91;
  if (_DAT_0081f2bc < param_3 + param_5 + param_7) {
    param_1 = Bitmap_GlowRect(param_1,param_2,param_3 - _DAT_0081f2bc,param_4,param_5,param_6,
                              param_7,param_8,param_9,param_10,0,param_12);
  }
  if ((param_3 - param_5) - param_7 < _DAT_0081f374) {
    param_1 = Bitmap_GlowRect(param_1,param_2,param_3 + _DAT_0081f2bc,param_4,param_5,param_6,
                              param_7,param_8,param_9,param_10,0,param_12);
  }
LAB_0080ae91:
  iVar7 = param_1;
  FUN_0080a608();
  if (param_10 == _DAT_0081f374) {
    param_10 = _DAT_0081f384;
  }
  param_10 = (float)_DAT_0081fb88 / param_10;
  fVar4 = (float)*(int *)(param_1 + 0x10);
  fVar1 = (float)*(int *)(param_1 + 0x14);
  param_4 = fVar4 * param_4;
  param_5 = fVar1 * param_5;
  param_6 = (float)*(int *)(param_1 + 0x10) * param_6;
  param_7 = fVar1 * param_7;
  if (param_4 < _DAT_0081f384) {
    param_4 = _DAT_0081f384;
  }
  fVar3 = _DAT_0081f2bc / (param_4 * param_4);
  if (param_5 < _DAT_0081f384) {
    param_5 = _DAT_0081f384;
  }
  fVar5 = _DAT_0081f2bc / (param_5 * param_5);
  param_9 = param_9 * _DAT_0081fb84;
  local_18 = FUN_0080a63e();
  local_8 = -param_7;
  local_c = -param_6;
  param_11 = 0;
  do {
    fVar2 = (float)param_11 - fVar1 * param_3;
    if (local_8 <= fVar2) {
      if (fVar2 <= param_7) {
        fVar2 = 0.0;
      }
      else {
        fVar2 = fVar2 - param_7;
      }
    }
    else {
      fVar2 = fVar2 + param_7;
    }
    param_1 = 0;
    do {
      fVar6 = (float)param_1 - param_2 * fVar4;
      if (local_c <= fVar6) {
        if (fVar6 <= param_6) {
          fVar6 = 0.0;
        }
        else {
          fVar6 = fVar6 - param_6;
        }
      }
      else {
        fVar6 = fVar6 + param_6;
      }
      fVar6 = fVar6 * fVar6 * fVar3 + fVar2 * fVar2 * fVar5;
      if (param_12 == 0) {
        if (fVar6 < _DAT_0081f2bc) {
          fVar8 = (float10)FUN_008056db((double)fVar6,(double)(param_10 + param_10));
          fVar8 = ((float10)_DAT_0081f358 - fVar8) * (float10)param_9;
          goto LAB_0080b046;
        }
      }
      else if (_DAT_0081f374 < _DAT_0081f2bc - fVar6) {
        fVar8 = (float10)FUN_008056db((double)(_DAT_0081f2bc - fVar6),(double)param_10);
        fVar8 = fVar8 * (float10)param_9;
LAB_0080b046:
        local_10 = (float)fVar8;
        FUN_0080a6b3(&local_18,(int)ROUND(local_10));
      }
      param_1 = param_1 + 1;
    } while (param_1 < *(int *)(iVar7 + 0x10));
    param_11 = param_11 + 1;
    if (*(int *)(iVar7 + 0x14) <= param_11) {
      return iVar7;
    }
  } while( true );
}


/* ---- Bitmap_Mask @ 0080b082 ---- */

int Bitmap_Mask(int param_1,undefined4 *param_2,undefined4 *param_3,int param_4)

{
  int *piVar1;
  undefined4 uVar2;
  
  if ((((param_2 == (undefined4 *)0x0) || (param_3 == (undefined4 *)0x0)) || (param_2[1] != 1)) ||
     (((param_3[1] != 1 || (*(int *)(param_1 + 0x18) != param_2[6])) ||
      (*(int *)(param_1 + 0x18) != param_3[6])))) {
    param_1 = 0;
  }
  else {
    FUN_0080a608();
    uVar2 = *(undefined4 *)(param_1 + 0x18);
    FUN_0080a883(*(undefined4 *)(param_1 + 0xc),*(undefined4 *)(param_1 + 0xc),uVar2,8,0);
    if (param_4 == 0) {
      FUN_0080a883(*(undefined4 *)(param_1 + 0xc),param_2[3],uVar2,0xb,param_3[3]);
    }
    piVar1 = param_2 + 2;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      (**(code **)*param_2)(1);
    }
    piVar1 = param_3 + 2;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      (**(code **)*param_3)(1);
    }
  }
  return param_1;
}


/* ---- Bitmap_Rotate @ 0080b119 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Bitmap_Rotate(int param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
                 undefined4 param_7)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  float10 fVar10;
  float10 fVar11;
  undefined4 local_8;
  
  if ((param_3 == _DAT_0081f374) || (param_4 == _DAT_0081f374)) {
    param_1 = 0;
  }
  else {
    FUN_0080a608();
    uVar7 = operator_new(*(int *)(param_1 + 0x18) << 3);
    iVar5 = *(int *)(param_1 + 0x10);
    iVar6 = *(int *)(param_1 + 0x14);
    fVar10 = (float10)fcos((float10)param_2 * (float10)_DAT_0081f37c);
    iVar1 = (int)ROUND((float)(fVar10 * (float10)_DAT_0081fb98) / param_3);
    fVar11 = (float10)fsin((float10)(float)((float10)param_2 * (float10)_DAT_0081f37c));
    iVar2 = (int)ROUND((float)(((((float10)(double)fVar11 * (float10)_DAT_0081fb98) /
                                (float10)param_3) * (float10)iVar6) / (float10)iVar5));
    iVar3 = (int)ROUND((float)(((((float10)(double)fVar11 * (float10)_DAT_0081fb90) /
                                (float10)param_4) * (float10)iVar5) / (float10)iVar6));
    iVar4 = (int)ROUND((float)(fVar10 * (float10)_DAT_0081fb98) / param_4);
    iVar9 = (int)ROUND((float)iVar5 * param_5 * _DAT_0081fb84 -
                       (float)((iVar3 * iVar6 + iVar1 * iVar5) / 2));
    iVar8 = (int)ROUND((float)iVar6 * param_6 * _DAT_0081fb84 -
                       (float)((iVar4 * iVar6 + iVar2 * iVar5) / 2));
    local_8 = iVar6;
    if (0 < iVar6) {
      do {
        param_3 = (float)iVar8;
        param_4 = (float)iVar9;
        param_5 = (float)iVar5;
        if (0 < iVar5) {
          do {
            FUN_0080a778(iVar5,iVar6,param_4,param_3,param_7);
            param_5 = (float)((int)param_5 + -1);
            param_3 = (float)((int)param_3 + iVar2);
            param_4 = (float)((int)param_4 + iVar1);
          } while (param_5 != 0.0);
        }
        iVar9 = iVar9 + iVar3;
        iVar8 = iVar8 + iVar4;
        local_8 = local_8 + -1;
      } while (local_8 != 0);
    }
    FUN_0080574a(*(int *)(param_1 + 0x18) * 2);
    operator_delete(uVar7);
  }
  return param_1;
}


/* ---- Bitmap_Twirl @ 0080b2f6 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Bitmap_Twirl(int param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
                float param_7,undefined4 param_8)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 local_28;
  undefined4 local_8;
  
  iVar6 = param_1;
  if ((param_4 == _DAT_0081f374) || (param_5 == _DAT_0081f374)) {
    iVar6 = 0;
  }
  else {
    FUN_0080a608();
    operator_new();
    iVar1 = *(int *)(param_1 + 0x14);
    iVar2 = *(int *)(param_1 + 0x10);
    param_4 = param_4 * _DAT_0081f2ac;
    local_8 = 0;
    param_5 = param_5 * _DAT_0081f2ac;
    param_2 = param_2 * _DAT_0081f37c;
    if (0 < iVar1) {
      do {
        param_1 = 0;
        if (0 < iVar2) {
          fVar3 = (float)local_8 / (float)iVar1 - param_7;
          do {
            local_28 = (float)param_1 / (float)iVar2;
            fVar4 = local_28 - param_6;
            fVar5 = (_DAT_0081f2bc - (1.0 / param_4) * fVar4 * fVar4) - (fVar3 / param_5) * fVar3;
            if (fVar5 <= _DAT_0081f374) {
              fVar7 = (float10)((float)local_8 / (float)iVar1);
            }
            else {
              fVar7 = (float10)FUN_008056db((double)fVar5,(double)param_3);
              fVar7 = fVar7 * (float10)param_2;
              fVar8 = (float10)fsin(fVar7);
              fVar7 = (float10)fcos(fVar7);
              local_28 = (float)(fVar7 * (float10)fVar4 + (float10)(float)fVar8 * (float10)fVar3 +
                                (float10)param_6);
              fVar7 = fVar7 * (float10)fVar3 +
                      ((float10)param_7 - (float10)(float)fVar8 * (float10)fVar4);
            }
            FUN_0080a778(iVar2,iVar1,(int)ROUND((float)iVar2 * local_28 * _DAT_0081fb84),
                         (int)ROUND((float)((float10)iVar1 * fVar7 * (float10)_DAT_0081fb84)),
                         param_8);
            param_1 = param_1 + 1;
          } while (param_1 < iVar2);
        }
        local_8 = local_8 + 1;
      } while (local_8 < iVar1);
    }
    FUN_0080574a();
    operator_delete();
  }
  return iVar6;
}


/* ---- Bitmap_RotateMul @ 0080b4cc ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
Bitmap_RotateMul(int param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
                undefined4 param_7,undefined4 param_8,uint param_9,int param_10,uint param_11)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  float10 fVar10;
  float10 fVar11;
  int local_c;
  uint local_8;
  
  if ((param_10 < 1) || (param_1 == 0)) {
    uVar4 = 0;
  }
  else if (*(int *)(param_1 + 4) == 1) {
    piVar5 = (int *)Bitmap_Color();
    (**(code **)(*piVar5 + 4))();
    if ((param_9 & 0x10) == 0) {
      local_c = 1;
      param_8 = _DAT_0081f2bc / (float)param_10;
      param_2 = param_2 * param_8;
      fVar9 = (float)_DAT_0081fba0;
      param_5 = (param_5 - fVar9) / (float)param_10 + fVar9;
      param_6 = (param_6 - fVar9) / (float)param_10 + fVar9;
      fVar10 = (float10)FUN_008056db((double)param_3,(double)param_8);
      fVar11 = (float10)FUN_008056db((double)param_4,(double)param_8);
      fVar9 = (float)fVar11;
      fVar8 = fVar9;
      param_4 = fVar9;
    }
    else {
      iVar6 = 1 << ((byte)param_10 & 0x1f);
      iVar7 = iVar6 + -1;
      param_2 = param_2 / (float)iVar6;
      fVar9 = (float)iVar7;
      fVar8 = (float)_DAT_0081fba0;
      param_5 = (param_5 - fVar8) / fVar9 + fVar8;
      param_6 = (param_6 - fVar8) / fVar9 + fVar8;
      fVar9 = _DAT_0081f2bc / (float)iVar7;
      fVar10 = (float10)FUN_008056db((double)param_3,(double)fVar9);
      fVar11 = (float10)FUN_008056db((double)param_4,(double)fVar9);
      param_8 = (float)(param_11 >> 0x10 & 0xff);
      local_8 = param_11 >> 8 & 0xff;
      fVar9 = (float)(param_11 & 0xff);
      fVar8 = (float)(param_11 >> 0x18);
      param_4 = (float)fVar11;
    }
    param_3 = (float)fVar10;
    do {
      if ((param_9 & 0x10) == 0) {
        if (param_11 != 0xffffffff) {
          piVar5 = (int *)Bitmap_Color();
        }
        piVar5[2] = piVar5[2] + 1;
        fVar3 = (float)local_c;
        fVar2 = (float)_DAT_0081fba0;
        Bitmap_Rotate(piVar5,fVar3 * param_2,(param_3 - _DAT_0081f2bc) * fVar3 + _DAT_0081f2bc,
                      (param_4 - _DAT_0081f2bc) * fVar3 + _DAT_0081f2bc,
                      (param_5 - fVar2) * (float)local_c + fVar2,
                      (param_6 - fVar2) * (float)local_c + fVar2,param_7);
        uVar4 = Bitmap_Merge();
        local_c = local_c + 1;
      }
      else {
        if (param_11 != 0xffffffff) {
          piVar5 = (int *)Bitmap_Color();
          fVar8 = (float)((int)fVar8 * (int)fVar8 >> 8);
          param_8 = (float)((int)param_8 * (int)param_8 >> 8);
          local_8 = (int)(local_8 * local_8) >> 8;
          fVar9 = (float)((int)fVar9 * (int)fVar9 >> 8);
          param_11 = (((int)fVar8 << 8 | (uint)param_8) << 8 | local_8) << 8 | (uint)fVar9;
        }
        Bitmap_Rotate(piVar5,param_2,param_3,param_4,param_5,param_6,param_7);
        piVar5 = (int *)Bitmap_Merge();
        uVar4 = (**(code **)(*piVar5 + 4))();
        param_2 = param_2 * _DAT_0081f108;
        param_5 = (param_5 - _DAT_0081f2ac) * _DAT_0081f108 + _DAT_0081f2ac;
        param_6 = (param_6 - _DAT_0081f2ac) * _DAT_0081f108 + _DAT_0081f2ac;
        param_3 = param_3 * param_3;
        param_4 = param_4 * param_4;
      }
      param_10 = param_10 + -1;
    } while (param_10 != 0);
    piVar1 = piVar5 + 2;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      (**(code **)*piVar5)();
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}


/* ---- Bitmap_Distort @ 0080b7c7 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Bitmap_Distort(undefined4 *param_1,int param_2,float param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  ushort *puVar4;
  int local_20;
  int local_18;
  int local_10;
  int local_c;
  
  if ((((param_1 == (undefined4 *)0x0) || (param_2 == 0)) || (param_1[1] != 1)) ||
     ((*(int *)(param_2 + 4) != 1 || (*(int *)(param_2 + 0x18) != param_1[6])))) {
    param_2 = 0;
  }
  else {
    FUN_0080a608();
    piVar1 = param_1 + 2;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      (**(code **)*param_1)(1);
    }
    iVar2 = *(int *)(param_2 + 0x10);
    puVar4 = *(ushort **)(param_2 + 0xc);
    iVar3 = *(int *)(param_2 + 0x14);
    local_20 = (int)(longlong)ROUND((float)iVar2 * param_3 * _DAT_0081fb68);
    local_18 = (int)(longlong)ROUND((float)iVar3 * param_3 * _DAT_0081fb68);
    local_10 = 0;
    if (0 < iVar2) {
      do {
        if (0 < iVar3) {
          param_3 = 0.0;
          local_c = iVar3;
          do {
            FUN_0080a778(iVar2,iVar3,(*puVar4 - 0x4000) * local_20 + (int)param_3,
                         (puVar4[1] - 0x4000) * local_18 + local_10 * 0x10000,param_4);
            param_3 = (float)((int)param_3 + 0x10000);
            puVar4 = puVar4 + 4;
            local_c = local_c + -1;
          } while (local_c != 0);
        }
        local_10 = local_10 + 1;
      } while (local_10 < iVar2);
    }
  }
  return param_2;
}


/* ---- FUN_0080b8ca @ 0080b8ca ---- */

int __fastcall FUN_0080b8ca(int param_1,int param_2,uint param_3)

{
  uint in_EAX;
  
  return (((uint)*(ushort *)(param_1 + (in_EAX - param_2 & param_3) * 2) -
          (uint)*(ushort *)(param_1 + (in_EAX & param_3) * 2)) * 3 +
         (uint)*(ushort *)(param_1 + (in_EAX + param_2 * -2 & param_3) * 2)) -
         (uint)*(ushort *)(param_1 + (in_EAX + param_2 & param_3) * 2);
}


/* ---- FUN_0080b90b @ 0080b90b ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __fastcall FUN_0080b90b(uint param_1,uint param_2,uint param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint in_EAX;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  float10 fVar7;
  float10 fVar8;
  
  uVar5 = in_EAX & 0xff;
  fVar7 = (float10)(param_1 & 0xffff) * (float10)_DAT_0081f384;
  fVar3 = (float)(param_2 & 0xffff) * _DAT_0081f384;
  uVar6 = (int)param_1 >> 0x10 & uVar5;
  uVar4 = ((int)param_1 >> 0x10) + 1U & uVar5;
  fVar8 = fVar7 * (float10)(float)(&DAT_008409f0)
                                  [(uint)(byte)(&DAT_008411f0)
                                               [(byte)(&DAT_008411f0)
                                                      [(int)param_2 >> 0x10 & uVar5 ^ param_3 & 0xff
                                                      ] + uVar6] * 2] +
          (float10)fVar3 *
          (float10)(float)(&DAT_008409f4)
                          [(uint)(byte)(&DAT_008411f0)
                                       [(byte)(&DAT_008411f0)
                                              [(int)param_2 >> 0x10 & uVar5 ^ param_3 & 0xff] +
                                        uVar6] * 2];
  fVar1 = (float)(fVar7 * (float10)(float)(&DAT_008409f0)
                                          [(uint)(byte)(&DAT_008411f0)
                                                       [uVar6 + (byte)(&DAT_008411f0)
                                                                      [((int)param_2 >> 0x10) + 1U &
                                                                       uVar5 ^ param_3 & 0xff]] * 2]
                 + ((float10)fVar3 - (float10)_DAT_0081f2bc) *
                   (float10)(float)(&DAT_008409f4)
                                   [(uint)(byte)(&DAT_008411f0)
                                                [uVar6 + (byte)(&DAT_008411f0)
                                                               [((int)param_2 >> 0x10) + 1U & uVar5
                                                                ^ param_3 & 0xff]] * 2]);
  fVar2 = (float)(((float10)_DAT_0081f368 - (fVar7 + fVar7)) * fVar7 * fVar7);
  fVar8 = ((float10)(float)((float10)fVar3 *
                            (float10)(float)(&DAT_008409f4)
                                            [(uint)(byte)(&DAT_008411f0)
                                                         [(byte)(&DAT_008411f0)
                                                                [(int)param_2 >> 0x10 & uVar5 ^
                                                                 param_3 & 0xff] + uVar4] * 2] +
                           (fVar7 - (float10)_DAT_0081f2bc) *
                           (float10)(float)(&DAT_008409f0)
                                           [(uint)(byte)(&DAT_008411f0)
                                                        [(byte)(&DAT_008411f0)
                                                               [(int)param_2 >> 0x10 & uVar5 ^
                                                                param_3 & 0xff] + uVar4] * 2]) -
          fVar8) * (float10)fVar2 + fVar8;
  return ((((float10)(float)((fVar7 - (float10)_DAT_0081f2bc) *
                             (float10)(float)(&DAT_008409f0)
                                             [(uint)(byte)(&DAT_008411f0)
                                                          [uVar4 + (byte)(&DAT_008411f0)
                                                                         [((int)param_2 >> 0x10) +
                                                                          1U & uVar5 ^
                                                                          param_3 & 0xff]] * 2] +
                            ((float10)fVar3 - (float10)_DAT_0081f2bc) *
                            (float10)(float)(&DAT_008409f4)
                                            [(uint)(byte)(&DAT_008411f0)
                                                         [uVar4 + (byte)(&DAT_008411f0)
                                                                        [((int)param_2 >> 0x10) + 1U
                                                                         & uVar5 ^ param_3 & 0xff]]
                                             * 2]) - (float10)fVar1) * (float10)fVar2 +
          (float10)fVar1) - fVar8) *
         ((float10)_DAT_0081f368 - ((float10)fVar3 + (float10)fVar3)) * (float10)fVar3 *
         (float10)fVar3 + fVar8;
}


/* ---- FUN_0080ba53 @ 0080ba53 ---- */

undefined4 * __fastcall FUN_0080ba53(undefined4 *param_1)

{
  FUN_008178b0();
  param_1[8] = 0xffffffff;
  param_1[1] = 1;
  param_1[7] = 1;
  *param_1 = &PTR_FUN_0081fba8;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  return param_1;
}


/* ---- FUN_0080ba86 @ 0080ba86 ---- */

void __fastcall FUN_0080ba86(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_0081fba8;
  operator_delete(param_1[3]);
  if (param_1[8] != -1) {
    FUN_00801323(param_1[8]);
  }
  FUN_008178c4();
  return;
}


/* ---- FUN_0080bade @ 0080bade ---- */

void __thiscall FUN_0080bade(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  *(int *)(param_1 + 0x10) = param_2;
  *(int *)(param_1 + 0x18) = param_2 * param_3;
  *(int *)(param_1 + 0x14) = param_3;
  uVar1 = operator_new(param_2 * param_3 * 8);
  *(undefined4 *)(param_1 + 0xc) = uVar1;
  return;
}


/* ---- FUN_0080bb08 @ 0080bb08 ---- */

void __thiscall FUN_0080bb08(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 0x1c) = param_2;
  uVar1 = FUN_0080445b(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14),param_2,
                       *(undefined4 *)(param_1 + 0xc),*(undefined4 *)(param_1 + 0x24),
                       *(undefined4 *)(param_1 + 0x28));
  *(undefined4 *)(param_1 + 0x20) = uVar1;
  return;
}


/* ---- FUN_0080bb37 @ 0080bb37 ---- */

undefined4 __thiscall FUN_0080bb37(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  param_1 = param_1 + DAT_00aa7c28;
  iVar4 = 10;
  iVar3 = iVar4;
  if ((param_1 < 10) && (iVar3 = param_1, param_1 < 1)) {
    iVar3 = 0;
  }
  param_2 = DAT_00aa7c28 + param_2;
  if ((param_2 < 10) && (iVar4 = param_2, param_2 < 1)) {
    iVar4 = 0;
  }
  iVar1 = operator_new(0x2c);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0080ba53();
  }
  FUN_0080bade(1 << ((byte)iVar3 & 0x1f),1 << ((byte)iVar4 & 0x1f));
  return uVar2;
}


/* ---- Bitmap_Flat @ 0080bba9 ---- */

int Bitmap_Flat(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  
  iVar2 = FUN_0080bb37(param_2);
  iVar1 = *(int *)(iVar2 + 0x18);
  uVar6 = FUN_0080a63e();
  puVar4 = *(undefined8 **)(iVar2 + 0xc);
  if (iVar1 != 0) {
    *puVar4 = uVar6;
    puVar5 = puVar4 + 1;
    for (uVar3 = iVar1 * 8 - 5U >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)puVar5 = *(undefined4 *)puVar4;
      puVar4 = (undefined8 *)((int)puVar4 + 4);
      puVar5 = (undefined8 *)((int)puVar5 + 4);
    }
  }
  return iVar2;
}


/* ---- Bitmap_RenderTarget @ 0080bbeb ---- */

int Bitmap_RenderTarget(byte param_1,byte param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar1 = operator_new(0x2c);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0080ba53();
  }
  iVar2 = 1 << (param_1 & 0x1f);
  iVar4 = 1 << (param_2 & 0x1f);
  *(undefined4 *)(iVar1 + 0x1c) = param_3;
  *(int *)(iVar1 + 0x10) = iVar2;
  *(int *)(iVar1 + 0x14) = iVar4;
  uVar3 = FUN_0080445b(iVar2,iVar4,param_3,0,0,0);
  *(undefined4 *)(iVar1 + 0x20) = uVar3;
  return iVar1;
}


/* ---- Bitmap_HSCB @ 0080bc43 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Bitmap_HSCB(int param_1,undefined4 param_2,undefined4 param_3,float param_4,float param_5)

{
  undefined2 uVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined4 local_24;
  int local_10;
  int local_c;
  undefined2 *local_8;
  
  FUN_0080a608();
  local_8 = *(undefined2 **)(param_1 + 0xc);
  local_c = 0;
  puVar2 = &DAT_00aa7c30;
  do {
    fVar3 = (float10)FUN_008056db(((double)local_c + _DAT_0081fbc8) * _DAT_0081fbc0,
                                  (double)(param_4 * param_4));
    local_24 = (undefined4)(longlong)ROUND(fVar3 * (float10)param_5 * (float10)_DAT_0081fbb8);
    local_c = local_c + 0x20;
    *puVar2 = local_24;
    puVar2 = puVar2 + 1;
  } while ((int)puVar2 < 0xaa8c34);
  local_10 = 0;
  if (0 < *(int *)(param_1 + 0x18)) {
    do {
      FUN_0080a831();
      FUN_0080a831();
      FUN_0080a831();
      uVar1 = FUN_0080a62b();
      local_8[2] = uVar1;
      uVar1 = FUN_0080a62b();
      local_8[1] = uVar1;
      uVar1 = FUN_0080a62b();
      *local_8 = uVar1;
      local_8 = local_8 + 4;
      local_10 = local_10 + 1;
    } while (local_10 < *(int *)(param_1 + 0x18));
  }
  return param_1;
}


/* ---- Bitmap_Blur @ 0080bf83 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Bitmap_Blur(int param_1,uint param_2,float param_3,float param_4,float param_5)

{
  uint uVar1;
  int iVar2;
  longlong lVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  short sVar6;
  short sVar7;
  ulonglong uVar8;
  float fVar9;
  float fVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  undefined8 *puVar14;
  undefined8 *puVar15;
  short sVar16;
  short sVar17;
  int iVar18;
  uint uVar19;
  undefined8 *puVar20;
  uint uVar21;
  undefined2 uVar22;
  uint uVar23;
  undefined8 uVar24;
  uint uVar26;
  unkbyte10 extraout_ST1;
  undefined2 uVar27;
  unkbyte10 in_ST3;
  uint uVar28;
  undefined8 uVar29;
  uint uVar30;
  unkbyte10 in_ST4;
  undefined8 uVar31;
  undefined8 uVar32;
  unkbyte10 in_ST5;
  undefined8 *local_bc;
  int local_b8;
  int local_b4;
  uint local_b0;
  int local_ac;
  uint local_a8;
  undefined8 *local_a4;
  undefined8 *local_98;
  uint local_88;
  uint local_7c;
  int local_78;
  unkbyte10 Var25;
  
  FUN_0080a608();
  puVar14 = *(undefined8 **)(param_1 + 0xc);
  local_a4 = (undefined8 *)operator_new(*(int *)(param_1 + 0x18) << 3);
  fVar10 = _DAT_0081f0ec;
  iVar2 = *(int *)(param_1 + 0x14);
  param_5 = param_5 * _DAT_0081fbd0;
  local_ac = 2;
  Var25 = extraout_ST1;
  fVar9 = (float)*(int *)(param_1 + 0x10) * param_3;
  do {
    local_98 = puVar14;
    uVar21 = (int)ROUND(fVar9 * fVar10) >> 1 & 0x3f;
    iVar11 = ((int)ROUND(fVar9 * fVar10) / 0x80) * 2;
    if ((param_2 & 0x10) != 0) {
      iVar11 = iVar11 + 1;
    }
    iVar12 = ((iVar11 + 1) * 0x40 - (0x40 - uVar21)) + uVar21;
    local_bc = (undefined8 *)0x1;
    if (0 < iVar12) {
      local_bc = (undefined8 *)iVar12;
    }
    lVar3 = (longlong)ROUND(param_5 / (float)(int)local_bc);
    local_78 = (int)lVar3;
    iVar12 = *(int *)(param_1 + 0x10);
    local_b4 = 0;
    uVar1 = iVar12 * 4 - 1;
    iVar13 = (int)(0x4000000000 / (longlong)local_78) + -1;
    sVar7 = (short)(0x40 - uVar21);
    sVar6 = (short)uVar21;
    sVar16 = (short)lVar3;
    sVar17 = (short)((ulonglong)lVar3 >> 0x10);
    uVar8 = (ulonglong)CONCAT24(sVar6 - sVar7,(uint)(ushort)(sVar6 - sVar7));
    uVar4 = CONCAT26(sVar6,CONCAT24(sVar7,CONCAT22(sVar6,sVar7)));
    in_ST3 = CONCAT28((short)((unkuint10)in_ST3 >> 0x40),uVar4);
    uVar21 = ((iVar11 + 1) / -2) * 4;
    do {
      iVar18 = *(int *)(param_1 + 0x10) * local_b4;
      puVar14 = local_98 + iVar18;
      puVar15 = local_a4 + iVar18;
      local_7c = param_2 & 0xf;
      do {
        puVar20 = puVar14;
        uVar29 = *(undefined8 *)((int)puVar20 + (uVar21 & uVar1) * 2);
        uVar27 = (undefined2)((unkuint10)Var25 >> 0x40);
        uVar22 = (undefined2)((ulonglong)uVar29 >> 0x10);
        uVar24 = pmaddwd((longlong)
                         CONCAT64(CONCAT42(CONCAT22(uVar27,uVar22),uVar22),
                                  CONCAT22((short)uVar29,(short)uVar29)),uVar8);
        Var25 = CONCAT28(uVar27,uVar24);
        uVar22 = (undefined2)((ulonglong)uVar29 >> 0x20);
        uVar27 = (undefined2)((ulonglong)uVar29 >> 0x30);
        uVar29 = pmaddwd(CONCAT26(uVar27,CONCAT24(uVar27,CONCAT22(uVar22,uVar22))),uVar8);
        in_ST4 = CONCAT28((short)((unkuint10)in_ST4 >> 0x40),uVar29);
        uVar19 = uVar21;
        local_b8 = iVar11;
        local_b0 = uVar21;
        if (0 < iVar11) {
          do {
            local_b0 = local_b0 + 4;
            uVar29 = *(undefined8 *)((int)puVar20 + (uVar19 & uVar1) * 2);
            uVar24 = *(undefined8 *)((int)puVar20 + (local_b0 & uVar1) * 2);
            uVar22 = (undefined2)((unkuint10)in_ST5 >> 0x40);
            uVar31 = pmaddwd((longlong)
                             CONCAT64(CONCAT42(CONCAT22(uVar22,(short)((ulonglong)uVar24 >> 0x10)),
                                               (short)((ulonglong)uVar29 >> 0x10)),
                                      CONCAT22((short)uVar24,(short)uVar29)),(longlong)in_ST3);
            in_ST5 = CONCAT28(uVar22,uVar31);
            Var25 = CONCAT28((short)((unkuint10)Var25 >> 0x40),
                             CONCAT44((int)((unkuint10)Var25 >> 0x20) +
                                      (int)((ulonglong)uVar31 >> 0x20),(int)Var25 + (int)uVar31));
            uVar19 = uVar19 + 4;
            local_b8 = local_b8 + -1;
            uVar29 = pmaddwd(CONCAT26((short)((ulonglong)uVar24 >> 0x30),
                                      CONCAT24((short)((ulonglong)uVar29 >> 0x30),
                                               CONCAT22((short)((ulonglong)uVar24 >> 0x20),
                                                        (short)((ulonglong)uVar29 >> 0x20)))),
                             (longlong)in_ST3);
            in_ST4 = CONCAT28((short)((unkuint10)in_ST4 >> 0x40),
                              CONCAT44((int)((unkuint10)in_ST4 >> 0x20) +
                                       (int)((ulonglong)uVar29 >> 0x20),(int)in_ST4 + (int)uVar29));
          } while (local_b8 != 0);
        }
        local_b8 = 0;
        puVar14 = puVar15;
        local_a8 = uVar21;
        local_b0 = uVar19;
        local_88 = uVar21;
        if (0 < iVar12) {
          do {
            local_88 = local_88 + 4;
            local_b0 = local_b0 + 4;
            uVar29 = *(undefined8 *)((int)puVar20 + (uVar19 & uVar1) * 2);
            uVar27 = (undefined2)((unkuint10)in_ST5 >> 0x40);
            uVar24 = *(undefined8 *)((int)puVar20 + (local_b0 & uVar1) * 2);
            uVar31 = pmaddwd((longlong)
                             CONCAT64(CONCAT42(CONCAT22(uVar27,(short)((ulonglong)uVar24 >> 0x10)),
                                               (short)((ulonglong)uVar29 >> 0x10)),
                                      CONCAT22((short)uVar24,(short)uVar29)),(longlong)in_ST3);
            uVar23 = (int)Var25 + (int)uVar31;
            uVar22 = (undefined2)((unkuint10)Var25 >> 0x40);
            uVar26 = (int)((unkuint10)Var25 >> 0x20) + (int)((ulonglong)uVar31 >> 0x20);
            uVar29 = pmaddwd(CONCAT26((short)((ulonglong)uVar24 >> 0x30),
                                      CONCAT24((short)((ulonglong)uVar29 >> 0x30),
                                               CONCAT22((short)((ulonglong)uVar24 >> 0x20),
                                                        (short)((ulonglong)uVar29 >> 0x20)))),
                             (longlong)in_ST3);
            uVar28 = (int)in_ST4 + (int)uVar29;
            uVar30 = (int)((unkuint10)in_ST4 >> 0x20) + (int)((ulonglong)uVar29 >> 0x20);
            uVar24 = packssdw(CONCAT44((int)(uVar26 * 0x400) >> 0x10,(int)(uVar23 * 0x400) >> 0x10),
                              CONCAT44((int)(uVar30 * 0x400) >> 0x10,(int)(uVar28 * 0x400) >> 0x10))
            ;
            uVar31 = pmulhuw(uVar24,CONCAT26(sVar16,CONCAT24(sVar16,CONCAT22(sVar16,sVar16))));
            uVar29 = packssdw(CONCAT44(uVar26 >> 0x16,uVar23 >> 0x16),
                              CONCAT44(uVar30 >> 0x16,uVar28 >> 0x16));
            uVar32 = CONCAT26((short)((ulonglong)uVar29 >> 0x30) * sVar16,
                              CONCAT24((short)((ulonglong)uVar29 >> 0x20) * sVar16,
                                       CONCAT22((short)((ulonglong)uVar29 >> 0x10) * sVar16,
                                                (short)uVar29 * sVar16)));
            in_ST5 = CONCAT28(uVar27,uVar32);
            uVar29 = packssdw(CONCAT44(-(uint)(iVar13 < (int)uVar26),-(uint)(iVar13 < (int)uVar23)),
                              CONCAT44(-(uint)(iVar13 < (int)uVar30),-(uint)(iVar13 < (int)uVar28)))
            ;
            uVar29 = paddusw(uVar29,uVar32);
            uVar29 = paddusw(uVar29,CONCAT26((short)((ulonglong)uVar24 >> 0x30) * sVar17,
                                             CONCAT24((short)((ulonglong)uVar24 >> 0x20) * sVar17,
                                                      CONCAT22((short)((ulonglong)uVar24 >> 0x10) *
                                                               sVar17,(short)uVar24 * sVar17))));
            uVar29 = paddusw(uVar29,uVar31);
            uVar29 = psubsw(CONCAT26((short)((ulonglong)uVar29 >> 0x30) + -0x8000,
                                     CONCAT24((short)((ulonglong)uVar29 >> 0x20) + -0x8000,
                                              CONCAT22((short)((ulonglong)uVar29 >> 0x10) + -0x8000,
                                                       (short)uVar29 + -0x8000))),0x8000800080008000
                           );
            *puVar14 = uVar29;
            uVar29 = *(undefined8 *)((int)puVar20 + (local_a8 & uVar1) * 2);
            uVar24 = *(undefined8 *)((int)puVar20 + (local_88 & uVar1) * 2);
            iVar12 = *(int *)(param_1 + 0x10);
            in_ST3 = CONCAT28((short)((unkuint10)in_ST3 >> 0x40),uVar4);
            uVar31 = pmaddwd((longlong)
                             CONCAT64(CONCAT42(CONCAT22(uVar22,(short)((ulonglong)uVar29 >> 0x10)),
                                               (short)((ulonglong)uVar24 >> 0x10)),
                                      CONCAT22((short)uVar29,(short)uVar24)),uVar4);
            Var25 = CONCAT28(uVar22,CONCAT44(uVar26 - (int)((ulonglong)uVar31 >> 0x20),
                                             uVar23 - (int)uVar31));
            uVar29 = pmaddwd(CONCAT26((short)((ulonglong)uVar29 >> 0x30),
                                      CONCAT24((short)((ulonglong)uVar24 >> 0x30),
                                               CONCAT22((short)((ulonglong)uVar29 >> 0x20),
                                                        (short)((ulonglong)uVar24 >> 0x20)))),uVar4)
            ;
            uVar19 = uVar19 + 4;
            puVar14 = puVar14 + 1;
            local_b8 = local_b8 + 1;
            in_ST4 = CONCAT28((short)((unkuint10)in_ST4 >> 0x40),
                              CONCAT44(uVar30 - (int)((ulonglong)uVar29 >> 0x20),
                                       uVar28 - (int)uVar29));
            local_a8 = local_a8 + 4;
          } while (local_b8 < iVar12);
        }
        local_7c = local_7c - 1;
        puVar14 = puVar15;
        puVar15 = puVar20;
      } while (local_7c != 0);
      local_b4 = local_b4 + 1;
    } while (local_b4 < *(int *)(param_1 + 0x14));
    puVar14 = local_a4;
    if ((param_2 & 1) != 0) {
      puVar14 = local_98;
      local_98 = local_a4;
    }
    iVar11 = *(int *)(param_1 + 0x14);
    local_b4 = 0;
    iVar12 = *(int *)(param_1 + 0x10);
    puVar15 = puVar14;
    iVar13 = iVar12;
    local_bc = local_98;
    if (0 < iVar11) {
      do {
        iVar18 = 0;
        puVar20 = local_bc;
        if (0 < iVar13) {
          do {
            uVar4 = puVar20[1];
            uVar29 = puVar20[2];
            Var25 = CONCAT28((short)((unkuint10)Var25 >> 0x40),uVar29);
            uVar24 = puVar20[3];
            in_ST3 = CONCAT28((short)((unkuint10)in_ST3 >> 0x40),*puVar20);
            *puVar15 = *puVar20;
            puVar15[iVar12] = uVar4;
            puVar15[iVar12 * 2] = uVar29;
            puVar15[iVar12 * 3] = uVar24;
            puVar20 = puVar20 + iVar11;
            iVar13 = *(int *)(param_1 + 0x10);
            puVar15 = puVar15 + 1;
            iVar18 = iVar18 + 1;
          } while (iVar18 < iVar13);
        }
        local_b4 = local_b4 + 4;
        local_bc = local_bc + 4;
        puVar15 = puVar15 + iVar12 * 3;
      } while (local_b4 < *(int *)(param_1 + 0x14));
    }
    local_ac = local_ac + -1;
    uVar5 = *(undefined4 *)(param_1 + 0x10);
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0x14);
    *(undefined4 *)(param_1 + 0x14) = uVar5;
    local_a4 = local_98;
    fVar9 = (float)iVar2 * param_4;
  } while (local_ac != 0);
  operator_delete(local_98);
  return param_1;
}


/* ---- Bitmap_Normals @ 0080c475 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Bitmap_Normals(int param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  double dVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  int iVar7;
  short *psVar8;
  short sVar9;
  int iVar10;
  int local_60;
  int local_58;
  int local_1c;
  short *local_18;
  
  iVar4 = param_1;
  FUN_0080a608();
  psVar5 = (short *)operator_new(*(int *)(param_1 + 0x18) << 3);
  iVar1 = *(int *)(param_1 + 0x10);
  iVar2 = *(int *)(param_1 + 0x14);
  FUN_0080552a();
  FUN_0080552a();
  if (0 < iVar2) {
    iVar6 = iVar1 << 2;
    local_1c = iVar2;
    local_18 = psVar5;
    do {
      param_1 = 0;
      if (0 < iVar1) {
        do {
          FUN_0080b8ca(iVar6 + -4);
          local_58 = FUN_0080a62b();
          local_58 = local_58 + -0x4000;
          FUN_0080b8ca((iVar2 + -1) * iVar1 * 4);
          iVar7 = FUN_0080a62b();
          iVar7 = iVar7 + -0x4000;
          sVar9 = 0;
          if ((param_3 & 1) != 0) {
            iVar10 = (0xfff8001 - local_58 * local_58) - iVar7 * iVar7;
            if (iVar10 < 1) {
              sVar9 = 0;
              dVar3 = _DAT_0081fbd8 / SQRT((double)(local_58 * local_58 + iVar7 * iVar7));
              local_58 = (int)(longlong)ROUND((double)local_58 * dVar3);
              local_60 = (int)(longlong)ROUND((double)iVar7 * dVar3);
              iVar7 = local_60;
            }
            else {
              local_60._0_2_ = (short)(longlong)ROUND(SQRT((float10)iVar10));
              sVar9 = (short)local_60;
            }
          }
          local_18[3] = -1;
          local_18[1] = (short)iVar7 + 0x4000;
          *local_18 = (short)local_58 + 0x4000;
          psVar8 = local_18 + 4;
          param_1 = param_1 + 1;
          local_18[2] = sVar9 + 0x4000;
          local_18 = psVar8;
        } while (param_1 < iVar1);
      }
      iVar6 = iVar1 * 4;
      local_1c = local_1c + -1;
    } while (local_1c != 0);
  }
  FUN_0080574a(*(int *)(iVar4 + 0x18) * 2);
  operator_delete(psVar5);
  return iVar4;
}


/* ---- Bitmap_Bump @ 0080c67a ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Bitmap_Bump(float param_1,undefined4 *param_2,int param_3,float param_4,float param_5,
               float param_6,float param_7,float param_8,undefined4 param_9,undefined4 param_10,
               float param_11,undefined4 param_12,float param_13,undefined4 param_14,float param_15,
               float param_16)

{
  int *piVar1;
  ushort *puVar2;
  ushort *puVar3;
  int iVar4;
  ushort uVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  undefined2 uVar11;
  int iVar12;
  int iVar13;
  int extraout_EDX;
  ushort *puVar14;
  float10 fVar15;
  float10 fVar16;
  undefined2 local_24 [4];
  undefined8 local_1c;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  iVar12 = (int)param_1;
  if (param_11 == _DAT_0081f374) {
    iVar12 = 0;
  }
  else {
    FUN_0080a608();
    iVar6 = *(int *)((int)param_1 + 0x10);
    iVar7 = *(int *)((int)param_1 + 0x14);
    FUN_0080a63e();
    FUN_0080a63e();
    local_1c = FUN_0080a63e();
    fVar8 = (float)iVar6;
    param_4 = param_4 * fVar8;
    param_10 = 0;
    piVar1 = (int *)((int)param_1 + 0x10);
    puVar14 = (ushort *)param_2[3];
    param_5 = (float)iVar7 * param_5;
    fVar8 = fVar8 * param_6;
    fVar15 = (float10)fcos((float10)param_8 * (float10)_DAT_0081fbe4);
    fVar16 = (float10)fsin((float10)param_7 * (float10)_DAT_0081f37c);
    local_10 = 0.0;
    param_11 = (float)(fVar15 * fVar16);
    fVar16 = (float10)fcos((float10)param_7 * (float10)_DAT_0081f37c);
    param_1 = (float)(fVar15 * fVar16);
    fVar15 = (float10)fsin((float10)param_8 * (float10)_DAT_0081fbe4);
    param_14 = (float)fVar15;
    if (0 < *piVar1) {
      do {
        param_9 = 0;
        if (0 < *(int *)(iVar12 + 0x14)) {
          do {
            if (param_3 != 2) {
              param_11 = (float)param_9 - ((param_4 + param_4) - (float)(iVar6 / 2));
              param_1 = (float)param_10 - ((param_5 + param_5) - (float)(iVar7 / 2));
              param_14 = (float)_DAT_0081f358 /
                         SQRT(fVar8 * fVar8 + param_11 * param_11 + param_1 * param_1);
              param_11 = param_14 * param_11;
              param_1 = param_14 * param_1;
              param_14 = param_14 * fVar8;
            }
            uVar5 = *puVar14;
            puVar2 = puVar14 + 1;
            puVar3 = puVar14 + 2;
            puVar14 = puVar14 + 4;
            local_8 = (float)(int)(*puVar3 - 0x4000) * _DAT_0081fbe0;
            local_c = param_1 * (float)(int)(*puVar2 - 0x4000) * _DAT_0081fbe0;
            fVar9 = (float)(int)(uVar5 - 0x4000) * _DAT_0081fbe0 * param_11;
            local_14 = param_14 * local_8 + fVar9 + local_c;
            if (param_16 != _DAT_0081f374) {
              fVar10 = param_14 + _DAT_0081f2bc;
              fVar9 = fVar10 * local_8 + fVar9 + local_c;
              if (fVar9 < _DAT_0081f374) {
                fVar9 = 0.0;
              }
              fVar15 = (float10)FUN_008056db((double)(((float)_DAT_0081f358 /
                                                      SQRT(param_11 * param_11 +
                                                           param_1 * param_1 + fVar10 * fVar10)) *
                                                     fVar9),(double)param_15);
              local_10 = (float)fVar15;
            }
            local_14 = local_14 * param_13;
            do {
              uVar11 = FUN_0080a62b();
              *(undefined2 *)((int)local_24 + extraout_EDX) = uVar11;
            } while (extraout_EDX + 2 < 8);
            iVar4 = (int)ROUND(local_10 * param_16 * _DAT_0081fb84);
            iVar13 = 0xffff;
            if (iVar4 < 0x10000) {
              iVar13 = iVar4;
            }
            FUN_0080a709(&local_1c,iVar13);
            param_9 = param_9 + 1;
          } while (param_9 < *(int *)(iVar12 + 0x14));
        }
        param_10 = param_10 + 1;
      } while (param_10 < *(int *)(iVar12 + 0x10));
    }
    piVar1 = param_2 + 2;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      (**(code **)*param_2)();
    }
  }
  return iVar12;
}


/* ---- Bitmap_Text @ 0080c951 ---- */

int Bitmap_Text(int param_1,int param_2,float param_3,float param_4,uint *param_5,float param_6,
               undefined4 param_7,uint param_8,int param_9,uint *param_10,char *param_11,
               int param_12)

{
  int iVar1;
  undefined4 uVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  uint *puVar10;
  int local_28;
  undefined8 local_20;
  undefined8 local_18;
  float local_10;
  float local_c;
  int local_8;
  
  local_20 = FUN_0080a63e();
  FUN_0080a608();
  iVar4 = *(int *)(param_2 + 0x14) << 2;
  local_10 = (float)iVar4;
  iVar8 = *(int *)(param_2 + 0x10) << 2;
  local_c = (float)iVar8;
  local_18._0_4_ = (int)(longlong)ROUND(local_10 * (float)param_5);
  uVar2 = (int)local_18;
  local_18 = (longlong)ROUND(local_c * param_6);
  local_8 = iVar8;
  iVar4 = FUN_00801f53(iVar8,iVar4,param_12,(int)local_18,uVar2,4);
  param_12 = param_9 << 2;
  local_18._0_4_ = (int)(longlong)ROUND(local_c * (float)param_10);
  iVar1 = (int)local_18;
  uVar7 = param_8 >> 4 & 7;
  param_9 = (int)local_18;
  local_18._0_4_ = (int)(longlong)ROUND(local_c * param_3 + (float)param_12);
  iVar6 = (int)local_18;
  local_18._4_4_ = (int)local_18;
  param_10 = (uint *)(int)local_18;
  local_28 = (int)(longlong)ROUND(local_10 * param_4 + (float)param_12);
  param_6 = (float)local_28;
  if (uVar7 == 0) {
    if ((param_8 & 1) != 0) {
      iVar4 = FUN_008020cf(param_11,0xffffffff);
      iVar6 = iVar6 + iVar4 / -2;
    }
    FUN_00802105(iVar6,local_28,param_11,0xffffffff);
  }
  else {
    puVar9 = (undefined4 *)(uVar7 * 0x1000 + 0x14f0 + param_1);
    for (iVar6 = 0x400; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar9 = 0;
      puVar9 = puVar9 + 1;
    }
    cVar3 = *param_11;
    param_8 = param_8 & 0xffffff;
    param_7._3_1_ = 'a';
    iVar8 = local_8;
    if (cVar3 != '\0') {
      iVar4 = iVar4 + iVar1 * 2;
      iVar1 = uVar7 * 0x100;
      iVar6 = (int)local_18;
      do {
        if (cVar3 == '-') {
          pcVar5 = param_11 + 1;
          cVar3 = *pcVar5;
          if ((cVar3 != '-') && (cVar3 != '\0')) {
            param_11 = param_11 + 2;
            param_8 = CONCAT13(*pcVar5,(undefined3)param_8);
          }
        }
        if (param_8._3_1_ == '\0') {
          param_7._3_1_ = *param_11;
          param_11 = param_11 + 1;
        }
        else {
          param_7._3_1_ = param_7._3_1_ + '\x01';
          if (param_8._3_1_ <= param_7._3_1_) {
            param_8 = param_8 & 0xffffff;
          }
        }
        param_10 = (uint *)iVar6;
        iVar8 = FUN_008020cf((int)&param_7 + 3,1);
        iVar8 = iVar8 + param_9 * 2;
        if (local_8 <= iVar8 + iVar6 + param_12) {
          param_10 = (uint *)local_18._4_4_;
          param_6 = (float)((iVar4 + 3 + (int)param_6 & 0xfffffffcU) + param_12);
          iVar6 = local_18._4_4_;
        }
        iVar8 = iVar8 + iVar6;
        *(float *)((param_7._3_1_ + 0x14f + iVar1) * 0x10 + param_1) =
             (float)(int)param_10 / local_c;
        *(float *)((param_7._3_1_ + iVar1) * 0x10 + 0x14f4 + param_1) =
             (float)(int)param_6 / local_10;
        *(float *)((param_7._3_1_ + iVar1) * 0x10 + 0x14f8 + param_1) = (float)iVar8 / local_c;
        param_10 = (uint *)(iVar4 + (int)param_6);
        *(float *)((param_7._3_1_ + iVar1) * 0x10 + 0x14fc + param_1) =
             (float)(int)param_10 / local_10;
        FUN_00802105(iVar6 + param_9,(int)param_6 + param_9,(int)&param_7 + 3,1);
        cVar3 = *param_11;
        iVar6 = (iVar8 + 3U & 0xfffffffc) + param_12;
        iVar8 = local_8;
        param_10 = (uint *)iVar6;
      } while (cVar3 != '\0');
    }
  }
  param_5 = (uint *)FUN_0080213c();
  param_11 = (char *)0x0;
  param_6 = 0.0;
  iVar4 = *(int *)(param_2 + 0x10);
  param_10 = param_5;
  if (0 < iVar4) {
    iVar8 = iVar8 << 4;
    param_9 = iVar8;
    do {
      iVar1 = local_8;
      param_8 = 0;
      if (0 < iVar4) {
        param_12 = local_8 * 0xc + 8;
        puVar10 = param_5;
        do {
          uVar7 = (puVar10[local_8 * 2] & 0xff) + (puVar10[local_8 * 2 + 1] & 0xff) +
                  (*(uint *)(param_12 + -8 + (int)puVar10) & 0xff) +
                  (*(uint *)(param_12 + -4 + (int)puVar10) & 0xff) + (puVar10[iVar1] & 0xff) +
                  (puVar10[iVar1 + 1] & 0xff) + (puVar10[local_8 * 2 + 3] & 0xff) +
                  (puVar10[local_8 * 2 + 2] & 0xff) +
                  (*(uint *)(param_12 + 4 + (int)puVar10) & 0xff) +
                  (*(uint *)(param_12 + (int)puVar10) & 0xff) + (puVar10[iVar1 + 3] & 0xff) +
                  (puVar10[iVar1 + 2] & 0xff) + (puVar10[3] & 0xff) + (puVar10[2] & 0xff) +
                  (puVar10[1] & 0xff) + (*puVar10 & 0xff) >> 4;
          FUN_0080a6b3(&local_20,uVar7 << 8 | uVar7);
          param_11 = (char *)((int)param_11 + 1);
          puVar10 = puVar10 + 4;
          param_8 = param_8 + 1;
          iVar8 = param_9;
        } while ((int)param_8 < *(int *)(param_2 + 0x10));
      }
      param_6 = (float)((int)param_6 + 1);
      iVar4 = *(int *)(param_2 + 0x10);
      param_5 = (uint *)((int)param_5 + iVar8);
    } while ((int)param_6 < iVar4);
  }
  operator_delete(param_10);
  return param_2;
}


/* ---- Bitmap_Perlin @ 0080cce1 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Bitmap_Perlin(undefined4 param_1,int param_2,int param_3,int param_4,float param_5,
                 undefined4 param_6,uint param_7,float param_8,float param_9)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  int iStack00000028;
  int iStack0000002c;
  undefined8 local_30;
  undefined8 local_28;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  int local_10;
  int local_c;
  float local_8;
  
  iVar1 = FUN_0080bb37(param_2);
  FUN_0080a63e();
  local_30 = FUN_0080a63e();
  local_1c = FUN_0080552a();
  local_18 = FUN_0080552a();
  local_c = *(int *)(iVar1 + 0xc);
  iStack0000002c = 0;
  if (0 < *(int *)(iVar1 + 0x10)) {
    do {
      iStack00000028 = 0;
      if (0 < *(int *)(iVar1 + 0x14)) {
        local_10 = param_4 + param_3;
        local_14 = param_7 & 1;
        do {
          param_1 = 0.0;
          local_8 = 1.0;
          if (param_3 < local_10) {
            local_20 = iStack00000028 << (0x10U - (char)local_1c & 0x1f);
            local_28 = CONCAT44(param_7,(undefined4)local_28) & 0x2ffffffff;
            param_2 = param_3;
            do {
              fVar3 = (float10)FUN_0080b90b();
              if (local_14 != 0) {
                fVar3 = ABS(fVar3);
              }
              if (local_28._4_4_ != 0) {
                fVar3 = (float10)fsin((float10)_DAT_0081f37c * fVar3);
                fVar3 = fVar3 * (float10)_DAT_0081fba0;
              }
              param_2 = param_2 + 1;
              param_1 = (float)(fVar3 * (float10)local_8 + (float10)param_1);
              local_8 = local_8 * param_5;
            } while (param_2 < local_10);
          }
          param_1 = param_1 * param_8;
          if (local_14 == 0) {
            param_1 = (param_1 + _DAT_0081f2bc) * _DAT_0081f2ac;
          }
          fVar3 = (float10)FUN_008056db((double)param_1,(double)param_9);
          local_28 = (ulonglong)ROUND((float10)_DAT_0081fbe8 * fVar3);
          iVar2 = FUN_0080a62b();
          FUN_0080a6b3(&local_30,iVar2 * 2);
          local_c = local_c + 8;
          iStack00000028 = iStack00000028 + 1;
        } while (iStack00000028 < *(int *)(iVar1 + 0x14));
      }
      iStack0000002c = iStack0000002c + 1;
    } while (iStack0000002c < *(int *)(iVar1 + 0x10));
  }
  return iVar1;
}


/* ---- Bitmap_Cell @ 0080ce6c ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Bitmap_Cell(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  int iVar5;
  undefined4 uVar6;
  undefined8 *puVar7;
  int iVar8;
  uint *puVar9;
  int iVar10;
  float10 fVar11;
  int iStack00000004;
  int *piStack00000008;
  int iStack0000000c;
  int iStack00000010;
  int *piStack00000014;
  int in_stack_00000018;
  uint *puStack0000001c;
  float in_stack_00000020;
  float in_stack_00000024;
  uint in_stack_00000028;
  int *in_stack_0000002c;
  float in_stack_00000034;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  int local_20;
  float local_1c;
  int local_18;
  undefined8 local_14;
  uint local_c;
  int local_8;
  
  if ((in_stack_00000018 < 1) || (0x100 < in_stack_00000018)) {
    iVar5 = 0;
  }
  else {
    iVar5 = FUN_0080bb37();
    local_20 = iVar5;
    FUN_008054e9();
    iVar10 = 0;
    if (0 < in_stack_00000018 * 3) {
      do {
        uVar6 = FUN_008054b7();
        (&DAT_00aa9038)[iVar10] = uVar6;
        iVar10 = iVar10 + 1;
      } while (iVar10 < in_stack_00000018 * 3);
    }
    local_1c = (float)((int)ROUND((float)in_stack_0000002c * _DAT_0081fbec) *
                      (int)ROUND((float)in_stack_0000002c * _DAT_0081fbec));
    iStack00000004 = 1;
    if (1 < in_stack_00000018) {
      local_c = in_stack_00000028 & 2;
      puStack0000001c = &DAT_00aa9048;
      puVar9 = &DAT_00aa903c + in_stack_00000018 * 3;
      do {
        if (local_c != 0) {
          FUN_008054b7();
        }
        local_8 = 0;
        iVar5 = (puStack0000001c[-1] & 0x3fff) - 0x2000;
        local_18 = (*puStack0000001c & 0x3fff) - 0x2000;
        local_14 = CONCAT44(iVar5,(undefined4)local_14);
        bVar4 = false;
        if ((int)puStack0000001c < 0xaa903d) {
LAB_0080cfbb:
          iStack00000004 = iStack00000004 + 1;
          puStack0000001c = puStack0000001c + 3;
        }
        else {
          in_stack_0000002c = &DAT_00aa903c;
          do {
            if (bVar4) goto LAB_0080cfa0;
            iVar8 = (*in_stack_0000002c - local_18 & 0x3fffU) - 0x2000;
            iVar10 = (in_stack_0000002c[-1] - iVar5 & 0x3fffU) - 0x2000;
            if (iVar8 * iVar8 + iVar10 * iVar10 < (int)local_1c) {
              bVar4 = true;
            }
            local_8 = local_8 + 1;
            in_stack_0000002c = in_stack_0000002c + 3;
          } while (local_8 < iStack00000004);
          if (!bVar4) goto LAB_0080cfbb;
LAB_0080cfa0:
          in_stack_00000018 = in_stack_00000018 + -1;
          puStack0000001c[-1] = puVar9[-4];
          *puStack0000001c = puVar9[-3];
          puStack0000001c[1] = puVar9[-2];
          puVar9 = puVar9 + -3;
        }
        iVar5 = local_20;
      } while (iStack00000004 < in_stack_00000018);
    }
    local_18 = FUN_0080552a();
    local_18 = 0xe - local_18;
    local_20 = FUN_0080552a();
    local_20 = 0xe - local_20;
    local_30 = FUN_0080a63e();
    local_28 = FUN_0080a63e();
    local_38 = FUN_0080a63e();
    fVar11 = (float10)FUN_008056db(_DAT_0081faa8,(double)in_stack_00000034);
    iStack0000000c = 0;
    local_1c = (float)(fVar11 * fVar11);
    fVar1 = (float)((float10)_DAT_0081f2bc / (fVar11 * (float10)_DAT_0081fbec));
    if (0 < *(int *)(iVar5 + 0x10)) {
      do {
        iStack00000004 = 0;
        if (0 < in_stack_00000018) {
          piStack00000008 = &DAT_00aa903c;
          do {
            iVar10 = (*piStack00000008 - (iStack0000000c << ((byte)local_20 & 0x1f)) & 0x3fffU) -
                     0x2000;
            piStack00000008 = piStack00000008 + 3;
            iStack00000004 = iStack00000004 + 1;
            local_14 = (longlong)ROUND((float)(iVar10 * iVar10) * local_1c);
            *(undefined4 *)(&DAT_00aa8c34 + iStack00000004 * 4) = (undefined4)local_14;
          } while (iStack00000004 < in_stack_00000018);
        }
        iStack00000010 = 0;
        if (0 < *(int *)(iVar5 + 0x14)) {
          local_c = in_stack_00000028 & 2;
          do {
            local_8 = -1;
            piStack00000008 = (int *)0x40000000;
            puStack0000001c = (uint *)0x40000000;
            iStack00000004 = 0;
            if (0 < in_stack_00000018) {
              piStack00000014 = &DAT_00aa9038;
              do {
                iVar10 = (*piStack00000014 - (iStack00000010 << ((byte)local_18 & 0x1f)) & 0x3fffU)
                         - 0x2000;
                iVar10 = iVar10 * iVar10 + (&DAT_00aa8c38)[iStack00000004];
                if (iVar10 < (int)piStack00000008) {
                  puStack0000001c = (uint *)piStack00000008;
                  local_8 = iStack00000004;
                  piStack00000008 = (int *)iVar10;
                }
                else if (iVar10 < (int)puStack0000001c) {
                  puStack0000001c = (uint *)iVar10;
                }
                piStack00000014 = piStack00000014 + 3;
                iStack00000004 = iStack00000004 + 1;
              } while (iStack00000004 < in_stack_00000018);
            }
            fVar2 = SQRT((float)(int)piStack00000008) * fVar1;
            fVar3 = SQRT((float)(int)puStack0000001c) * fVar1;
            fVar11 = (float10)FUN_008056db((double)(((fVar3 - fVar2) / (fVar3 + fVar2)) *
                                                   in_stack_00000020),(double)in_stack_00000024);
            local_14 = (longlong)ROUND(fVar11 * (float10)_DAT_0081fbb8);
            iVar10 = FUN_0080a62b();
            if (local_c == 0) {
              puVar7 = &local_28;
            }
            else {
              FUN_0080a6b3(&local_28,*(int *)(&DAT_00aa9040 + local_8 * 0xc) << 2);
              puVar7 = &local_38;
            }
            FUN_0080a6b3(puVar7,iVar10 * 2);
            iStack00000010 = iStack00000010 + 1;
          } while (iStack00000010 < *(int *)(iVar5 + 0x14));
        }
        iStack0000000c = iStack0000000c + 1;
      } while (iStack0000000c < *(int *)(iVar5 + 0x10));
    }
  }
  return iVar5;
}


/* ---- Bitmap_Gradient @ 0080d1df ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Bitmap_Gradient(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  int iStack0000000c;
  float in_stack_00000018;
  int in_stack_00000020;
  undefined8 local_c;
  
  iVar1 = FUN_0080bb37(param_2);
  FUN_0080a63e();
  local_c = FUN_0080a63e();
  fcos((float10)in_stack_00000018 * (float10)_DAT_0081fc00);
  fsin((float10)(double)((float10)in_stack_00000018 * (float10)_DAT_0081fc00));
  iStack0000000c = (int)(0x10000 / (longlong)*(int *)(iVar1 + 0x14));
  iVar2 = *(int *)(iVar1 + 0x10);
  param_1 = 0;
  if (0 < *(int *)(iVar1 + 0x14)) {
    do {
      param_2 = 0;
      if (0 < iVar2) {
        do {
          if (in_stack_00000020 == 0) {
            iStack0000000c = FUN_0080a62b();
            iStack0000000c = iStack0000000c * 2;
          }
          else if ((in_stack_00000020 != 1) && (in_stack_00000020 == 2)) {
            iVar2 = FUN_0080a62b();
            fVar3 = (float10)fsin((float10)iVar2 * (float10)_DAT_0081fbf8);
            iStack0000000c = (int)ROUND((float)(fVar3 * (float10)_DAT_0081fbf0));
          }
          FUN_0080a6b3(&local_c,iStack0000000c);
          iVar2 = *(int *)(iVar1 + 0x10);
          param_2 = param_2 + 1;
        } while (param_2 < iVar2);
      }
      param_1 = param_1 + 1;
    } while (param_1 < *(int *)(iVar1 + 0x14));
  }
  return iVar1;
}


/* ---- Bitmap_Sharpen @ 0080d34f ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Bitmap_Sharpen(undefined4 *param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                  float param_5)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint local_14;
  uint local_c;
  uint local_8;
  
  if (param_1 == (undefined4 *)0x0) {
    iVar2 = 0;
  }
  else {
    piVar1 = param_1 + 2;
    *piVar1 = *piVar1 + 1;
    FUN_0080a608();
    local_14 = (uint)(longlong)ROUND(param_5 * _DAT_0081fc08);
    uVar3 = 0x7fff;
    if (((int)local_14 < 0x7fff) && (uVar3 = 0xffff8001, -0x7fff < (int)local_14)) {
      uVar3 = local_14;
    }
    local_c = uVar3 & 0xffff | uVar3 << 0x10;
    local_8 = local_c;
    iVar2 = Bitmap_Blur(param_1,param_2 | 0x10,param_3,param_4,0x3f800000);
    FUN_0080a883(*(undefined4 *)(iVar2 + 0xc),&local_c,*(undefined4 *)(iVar2 + 0x18),0xf,param_1[3])
    ;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      (**(code **)*param_1)(1);
    }
  }
  return iVar2;
}


/* ---- FUN_0080d404 @ 0080d404 ---- */

undefined4 __thiscall FUN_0080d404(undefined4 param_1,byte param_2)

{
  FUN_0080ba86();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


/* ---- FUN_0080d423 @ 0080d423 ---- */

void __thiscall FUN_0080d423(int param_1,int param_2)

{
  *(undefined4 *)(param_1 + 0x20) = 0xffffffff;
  FUN_0080bade(*(undefined4 *)(param_2 + 0x10),*(undefined4 *)(param_2 + 0x14));
  FUN_0080574a(*(int *)(param_1 + 0x18) * 2);
  return;
}


/* ---- Bitmap_Light @ 0080d453 ---- */

void Bitmap_Light(void)

{
  return;
}


/* ---- FUN_0080d456 @ 0080d456 ---- */

void FUN_0080d456(int param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_00804b25(*(undefined4 *)(param_1 + 0xd4),param_1,param_2,param_3);
  return;
}


/* ---- FUN_0080d472 @ 0080d472 ---- */

undefined4 __thiscall FUN_0080d472(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((param_2 < *(int *)(param_1 + 0x54)) &&
     (iVar1 = *(int *)(*(int *)(param_1 + 0x7c) + param_2 * 4), iVar1 != 0)) {
    uVar2 = *(undefined4 *)(iVar1 + 0x18);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}


/* ---- FUN_0080d492 @ 0080d492 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __fastcall FUN_0080d492(undefined4 *param_1)

{
  undefined4 uVar1;
  
  FUN_008178b0();
  uVar1 = _DAT_0081fc1c;
  *param_1 = &PTR_FUN_0081fc10;
  param_1[1] = 9;
  param_1[8] = uVar1;
  param_1[9] = uVar1;
  param_1[10] = uVar1;
  param_1[0xb] = 0x3f800000;
  uVar1 = _DAT_0081fc0c;
  param_1[4] = _DAT_0081fc0c;
  param_1[5] = uVar1;
  param_1[6] = uVar1;
  param_1[7] = 0x3f800000;
  param_1[0xc] = 0;
  param_1[0xe] = 0;
  param_1[3] = 0;
  param_1[0xd] = 4;
  return param_1;
}


/* ---- FUN_0080d4e5 @ 0080d4e5 ---- */

void __fastcall FUN_0080d4e5(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_0081fc10;
  FUN_008178c4();
  return;
}


/* ---- Material_Add @ 0080d4f0 ---- */

void Material_Add(void)

{
  return;
}


/* ---- FUN_0080d4f1 @ 0080d4f1 ---- */

void __thiscall
FUN_0080d4f1(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  param_1[5] = 0;
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  param_1[3] = param_7;
  param_1[4] = param_8;
  param_1[6] = param_5;
  param_1[7] = param_6;
  return;
}


/* ---- Init_Effect_Print @ 0080d525 ---- */

undefined4 Init_Effect_Print(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = operator_new(0x3c);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0080d492();
  }
  return uVar2;
}


/* ---- FUN_0080d53f @ 0080d53f ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0080d53f(int *param_1,float param_2,float param_3,int param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  short sVar7;
  int *extraout_EDX;
  float *pfVar8;
  uint uVar9;
  float10 fVar10;
  
  pfVar8 = (float *)((param_1[9] * 0x100 + 0x14f + param_4) * 0x10 + *param_1);
  fVar1 = *pfVar8;
  fVar2 = pfVar8[1];
  fVar3 = pfVar8[2];
  fVar4 = pfVar8[3];
  fVar10 = (float10)fVar4 - (float10)fVar2;
  if ((float10)_DAT_0081f374 < fVar10) {
    uVar9 = 0;
    fVar10 = ((float10)fVar3 - (float10)fVar1) / fVar10;
    do {
      fVar5 = fVar2;
      if ((uVar9 & 2) != 0) {
        fVar5 = fVar4;
      }
      fVar6 = fVar3;
      if ((uVar9 & 1) == 0) {
        fVar10 = (float10)0;
        fVar6 = fVar1;
      }
      fVar10 = (float10)FUN_0080d4f1((float)(fVar10 * (float10)(float)param_1[1] + (float10)param_2)
                                     ,(float)(int)-(uint)((uVar9 & 2) != 0) * (float)param_1[2] +
                                      param_3,0,fVar6,fVar5,0xffffffff,0xffffffff);
      extraout_EDX[5] = extraout_EDX[5] + 0x20;
      uVar9 = uVar9 + 1;
      param_1 = extraout_EDX;
    } while ((int)uVar9 < 4);
    sVar7 = (short)(extraout_EDX[7] << 2);
    *(short *)extraout_EDX[6] = sVar7;
    *(short *)(extraout_EDX[6] + 2) = sVar7 + 1;
    *(short *)(extraout_EDX[6] + 4) = sVar7 + 3;
    *(short *)(extraout_EDX[6] + 6) = sVar7;
    *(short *)(extraout_EDX[6] + 8) = sVar7 + 3;
    *(short *)(extraout_EDX[6] + 10) = sVar7 + 2;
    extraout_EDX[6] = extraout_EDX[6] + 0xc;
    extraout_EDX[7] = extraout_EDX[7] + 1;
  }
  return;
}


/* ---- FUN_0080d641 @ 0080d641 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __thiscall FUN_0080d641(int *param_1,int param_2)

{
  float *pfVar1;
  float10 fVar2;
  
  pfVar1 = (float *)((param_1[9] * 0x100 + 0x14f + param_2) * 0x10 + *param_1);
  if ((float10)pfVar1[3] - (float10)pfVar1[1] <= (float10)_DAT_0081f374) {
    fVar2 = (float10)_DAT_0081f374;
  }
  else {
    fVar2 = (((float10)pfVar1[2] - (float10)*pfVar1) / ((float10)pfVar1[3] - (float10)pfVar1[1])) *
            (float10)(float)param_1[1];
  }
  return fVar2;
}


/* ---- FUN_0080d695 @ 0080d695 ---- */

float10 __thiscall FUN_0080d695(int param_1,char *param_2)

{
  int extraout_ECX;
  float10 fVar1;
  float10 fVar2;
  
  fVar2 = (float10)0;
  while( true ) {
    if (*param_2 == '\0') break;
    fVar1 = (float10)FUN_0080d641((int)*param_2);
    param_2 = param_2 + 1;
    fVar2 = fVar1 + (float10)(float)fVar2 + (float10)*(float *)(extraout_ECX + 0xc);
    param_1 = extraout_ECX;
  }
  return (float10)(float)fVar2 - (float10)*(float *)(param_1 + 0xc);
}


/* ---- Init_Effect_PartEmitter @ 0080d6c5 ---- */

undefined4 Init_Effect_PartEmitter(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = operator_new(0x14c);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0081583d();
  }
  return uVar2;
}


/* ---- FUN_0080d6e2 @ 0080d6e2 ---- */

undefined4 __thiscall FUN_0080d6e2(undefined4 param_1,byte param_2)

{
  FUN_0080d4e5();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


/* ---- Exec_Effect_Print @ 0080d701 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Exec_Effect_Print(undefined4 param_1,int param_2,uint param_3,float param_4,float param_5,
                      float param_6,float param_7,char *param_8)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  float10 fVar8;
  char local_234;
  char local_233 [511];
  int local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  int local_18;
  int local_14;
  uint local_10;
  int local_c;
  float local_8;
  
  iVar3 = FUN_0080d472(0);
  uVar1 = param_3;
  local_8 = 0.0;
  local_34 = param_2;
  local_30 = param_4;
  local_2c = param_5;
  local_28 = param_6;
  local_24 = param_7;
  local_10 = (int)param_3 >> 4 & 7;
  local_18 = 0;
  local_14 = 0x1000;
  FUN_00804b25(*(undefined4 *)(*(int *)(iVar3 + 0xc) + 0xd4),*(int *)(iVar3 + 0xc),0,0);
  param_3 = FUN_0080166b(6,3);
  FUN_0080479f(param_3,local_14 << 2,local_14 * 6,local_20,local_1c,3);
  cVar2 = *param_8;
  if (cVar2 != '\0') {
    pcVar6 = param_8;
    param_8 = (char *)(uVar1 & 1);
    do {
      param_1 = &local_234;
      param_4 = 0.0;
      while ((cVar2 != '\0' && (cVar2 != '\n'))) {
        if ((cVar2 == '%') && (((pcVar6[1] != '\0' && (pcVar6[2] != '\0')) && (pcVar6[3] != '\0'))))
        {
          iVar5 = (int)pcVar6[1];
          iVar4 = 0;
          cVar2 = pcVar6[2];
          iVar3 = iVar5 + -0x30;
          if ('/' < pcVar6[3]) {
            do {
            } while (pcVar6[3] < ':');
          }
          pcVar6 = pcVar6 + 4;
          if (cVar2 == 'W') {
            iVar4 = *(int *)(*(int *)(param_2 + 0x1358) + 0x1498c +
                            (*(int *)(*(int *)(param_2 + 0x1358) + 0x14968) / 2 & 3U) * 4);
          }
          else if (((cVar2 != 'a') && (cVar2 != 'f')) && (cVar2 == 'l')) {
            iVar4 = *(int *)(*(int *)(param_2 + 0x1358) + 0x1497c);
          }
          if (0 < iVar3) {
            pcVar7 = param_1 + iVar5 + -0x31;
            local_c = iVar3;
            do {
              *pcVar7 = (char)(iVar4 % 10) + '0';
              pcVar7 = pcVar7 + -1;
              local_c = local_c + -1;
              iVar4 = iVar4 / 10;
            } while (local_c != 0);
            local_c = 0;
          }
          param_1 = param_1 + iVar3;
        }
        else {
          *param_1 = cVar2;
          param_1 = param_1 + 1;
          pcVar6 = pcVar6 + 1;
        }
        cVar2 = *pcVar6;
      }
      *param_1 = '\0';
      pcVar7 = &local_234;
      cVar2 = local_234;
      if (param_8 != (char *)0x0) {
        fVar8 = (float10)FUN_0080d695(pcVar7);
        param_4 = (float)(fVar8 * (float10)_DAT_0081fb64);
        cVar2 = local_234;
      }
      while (cVar2 != '\0') {
        FUN_0080d53f(param_4,local_8,(int)cVar2);
        fVar8 = (float10)FUN_0080d641((int)cVar2);
        pcVar7 = pcVar7 + 1;
        param_4 = (float)(fVar8 + (float10)param_4 + (float10)param_6);
        cVar2 = *pcVar7;
      }
      if (*pcVar6 == '\n') {
        do {
          pcVar6 = pcVar6 + 1;
          local_8 = local_8 - (param_5 + param_7);
        } while (*pcVar6 == '\n');
      }
      cVar2 = *pcVar6;
    } while (cVar2 != '\0');
  }
  FUN_00801856(param_3,local_18 << 2,local_18 * 6);
  FUN_008016d1(&param_3);
  FUN_008045d4(param_3);
  return;
}


/* ---- Init_Effect_PartSystem @ 0080d954 ---- */

void Init_Effect_PartSystem(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  param_2 = param_2 * 0xc;
  uVar1 = operator_new(param_3 * 0x28);
  *(undefined4 *)(&DAT_00aa9c40 + param_2) = 0;
  *(undefined4 *)(&DAT_00aa9c38 + param_2) = uVar1;
  *(int *)(&DAT_00aa9c3c + param_2) = param_3;
  iVar2 = operator_new(0x3c);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_0080d492();
  }
  *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(*(int *)(param_1 + 0xc) + 0xe0);
  return;
}


/* ---- Exec_Effect_PartEmitter @ 0080d9a9 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Exec_Effect_PartEmitter
               (int param_1,int param_2,int param_3,uint param_4,int param_5,float param_6,
               float param_7)

{
  float *pfVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  int *piVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float in_stack_0000002c;
  float in_stack_00000030;
  float in_stack_00000034;
  float in_stack_00000038;
  float in_stack_0000003c;
  float in_stack_00000040;
  float in_stack_00000044;
  float in_stack_00000048;
  float in_stack_0000004c;
  float local_30;
  float local_2c;
  float local_28;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  undefined8 local_10;
  int *local_8;
  
  local_8 = (int *)(&DAT_00aa9c38 + param_3 * 0xc);
  iVar4 = FUN_00817b57(param_1,0x18);
  if (*(char *)(iVar4 + 0x10) != '\0') {
    *(int *)(iVar4 + 0x14) = param_5;
  }
  local_10._0_4_ =
       (float)(longlong)
              ROUND((float)(*(uint *)(param_2 + 0x14d8) - *(int *)(param_2 + 0x14e0) & 0xffffff) *
                    param_7 * _DAT_0081f2c4);
  param_1 = (int)(float)local_10;
  local_10._0_4_ =
       (float)(longlong)
              ROUND((float)(*(uint *)(param_2 + 0x14d8) & 0xffffff) * param_7 * _DAT_0081f2c4);
  param_1 = (int)(float)local_10 - param_1;
  if (param_5 != 0) {
    iVar2 = *(int *)(iVar4 + 0x14);
    if (iVar2 < param_1) {
      param_1 = iVar2;
    }
    *(int *)(iVar4 + 0x14) = iVar2 - param_1;
  }
  if (0 < param_1) {
    local_10 = (longlong)ROUND(param_6 * _DAT_0081fc24);
    fVar3 = (float)local_10;
    piVar6 = (int *)(&DAT_00aa9c38 + param_3 * 0xc);
    do {
      pfVar5 = (float *)(piVar6[2] * 0x28 + *piVar6);
      piVar6[2] = piVar6[2] + 1;
      *pfVar5 = *(float *)(param_2 + 0x9520);
      pfVar5[1] = *(float *)(param_2 + 0x9524);
      pfVar5[2] = *(float *)(param_2 + 0x9528);
      pfVar5[3] = *(float *)(param_2 + 0x952c);
      FUN_008061a4(param_2 + 0x94f0,&stack0x00000020);
      pfVar1 = pfVar5 + 4;
      *pfVar1 = local_30;
      pfVar5[5] = local_2c;
      pfVar5[6] = local_28;
      pfVar5[7] = in_stack_0000002c;
      pfVar5[8] = 0.0;
      pfVar5[9] = fVar3;
      do {
        fVar7 = (float10)FUN_008054c3();
        local_10 = CONCAT44((float)((fVar7 + fVar7) - (float10)_DAT_0081f2bc),(float)local_10);
        fVar8 = (float10)FUN_008054c3();
        fVar7 = (float10)_DAT_0081f2bc;
        fVar9 = (float10)FUN_008054c3();
        local_18 = local_10._4_4_;
        local_20 = (float)((fVar9 + fVar9) - (float10)_DAT_0081f2bc);
        local_14 = 0;
        local_1c = (float)((fVar8 + fVar8) - fVar7);
        fVar7 = (float10)FUN_00805fc1(&local_20);
      } while ((float10)_DAT_0081f2bc < fVar7);
      if ((param_4 & 1) != 0) {
        FUN_0080620b();
      }
      if ((param_4 & 8) != 0) {
        FUN_00805f88(&local_20);
      }
      *pfVar5 = in_stack_00000030 * local_20 + *pfVar5;
      pfVar5[1] = in_stack_00000034 * local_1c + pfVar5[1];
      pfVar5[2] = in_stack_00000038 * local_18 + pfVar5[2];
      fVar7 = (float10)FUN_008054c3();
      pfVar5[3] = (float)(((fVar7 + fVar7) - (float10)_DAT_0081f2bc) * (float10)in_stack_0000003c +
                         (float10)_DAT_0081fc20);
      do {
        fVar7 = (float10)FUN_008054c3();
        local_10 = CONCAT44((float)((fVar7 + fVar7) - (float10)_DAT_0081f2bc),(float)local_10);
        fVar8 = (float10)FUN_008054c3();
        fVar7 = (float10)_DAT_0081f2bc;
        fVar9 = (float10)FUN_008054c3();
        local_18 = local_10._4_4_;
        local_20 = (float)((fVar9 + fVar9) - (float10)_DAT_0081f2bc);
        local_14 = 0;
        local_1c = (float)((fVar8 + fVar8) - fVar7);
        fVar7 = (float10)FUN_00805fc1(&local_20);
      } while ((float10)_DAT_0081f2bc < fVar7);
      *pfVar1 = in_stack_00000040 * local_20 + *pfVar1;
      pfVar5[5] = in_stack_00000044 * local_1c + pfVar5[5];
      pfVar5[6] = in_stack_00000048 * local_18 + pfVar5[6];
      fVar7 = (float10)FUN_008054c3();
      param_1 = param_1 + -1;
      pfVar5[7] = (float)(((fVar7 + fVar7) - (float10)_DAT_0081f2bc) * (float10)in_stack_0000004c +
                         (float10)pfVar5[7]);
      piVar6 = local_8;
    } while (param_1 != 0);
  }
  return;
}


/* ---- Exec_Effect_PartSystem @ 0080dc14 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Exec_Effect_PartSystem
               (undefined4 param_1,int param_2,int param_3,undefined4 param_4,int param_5,
               int param_6,float param_7,float param_8,float param_9,float param_10,float param_11,
               float param_12,undefined4 *param_13)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  float10 fVar8;
  undefined4 local_a0 [4];
  undefined1 local_90 [48];
  float local_60;
  float local_5c;
  longlong local_58;
  float local_50;
  int local_4c;
  int *local_48;
  undefined8 local_44;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined8 local_2c;
  undefined8 local_24;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_4c = *(int *)(param_2 + 0x14e0);
  iVar4 = param_3 * 0xc;
  local_48 = (int *)(&DAT_00aa9c38 + iVar4);
  local_44 = FUN_0080a63e();
  local_24 = FUN_0080a63e();
  local_2c = FUN_0080a63e();
  iVar2 = FUN_0080d472(0);
  if (((iVar2 != 0) && (0 < *(int *)(&DAT_00aa9c40 + iVar4))) && (0 < *(int *)(iVar2 + 0x10))) {
    FUN_0080d456(*(undefined4 *)(iVar2 + 0xc),param_2 + 0x135c,0);
    param_3 = FUN_0080166b(6,6);
    local_34 = 0;
    local_30 = 0xffff0000;
    puVar6 = (undefined4 *)(DAT_0083f868 + 0x9fa4);
    puVar7 = local_a0;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    FUN_00806468();
    FUN_0080479f(param_3,*(int *)(&DAT_00aa9c40 + iVar4) << 2,0,&param_5,0,3);
    param_1 = 0;
    if (0 < *(int *)(&DAT_00aa9c40 + iVar4)) {
      param_6 = 0;
      local_5c = param_11 * _DAT_0081fc2c + _DAT_0081f2bc;
      param_12 = param_12 * _DAT_0081fc2c + _DAT_0081f2bc;
      local_60 = (float)local_4c;
      local_50 = local_60 * local_60 * (float)param_13 * _DAT_0081f2c4;
      local_60 = local_60 * _DAT_0081f2c4;
      piVar5 = (int *)(&DAT_00aa9c38 + iVar4);
      do {
        puVar6 = (undefined4 *)(*piVar5 + param_6);
        iVar2 = puVar6[8];
        local_58 = (longlong)ROUND((float)(int)puVar6[9] * local_5c * _DAT_0081fc28);
        param_13 = puVar6;
        if (iVar2 < (int)local_58) {
          param_7 = (float)(CONCAT44(iVar2 >> 0x10,iVar2 << 0x10) / (longlong)(int)local_58);
          FUN_0080a6b3(&local_24,param_7);
          param_7 = (param_9 - param_8) * (float)(int)param_7 * _DAT_0081f384 + param_8;
        }
        else {
          param_7 = (float)(CONCAT44(iVar2 - (int)local_58 >> 0x10,(iVar2 - (int)local_58) * 0x10000
                                    ) / (longlong)(puVar6[9] - (int)local_58));
          FUN_0080a6b3(&local_2c,param_7);
          param_7 = (param_10 - param_9) * (float)(int)param_7 * _DAT_0081f384 + param_9;
        }
        fVar1 = (float)puVar6[8];
        uVar3 = 0xffff;
        local_58 = (longlong)ROUND((float)(int)puVar6[9] * param_12 * _DAT_0081fc28);
        if ((int)fVar1 < (int)local_58) {
          uVar3 = (undefined4)
                  (CONCAT44((int)fVar1 >> 0x10,(int)fVar1 << 0x10) / (longlong)(int)local_58);
          param_11 = fVar1;
        }
        if (puVar6[9] - (int)local_58 < (int)puVar6[8]) {
          param_11 = (float)(puVar6[9] - puVar6[8]);
          uVar3 = (undefined4)
                  (CONCAT44((int)param_11 >> 0x10,(int)param_11 * 0x10000) / (longlong)(int)local_58
                  );
        }
        local_3c = local_c;
        local_38 = local_8;
        FUN_0080a6b3(&local_3c,uVar3);
        fVar8 = (float10)fcos((float10)(float)puVar6[3]);
        fVar1 = (float)(fVar8 * (float10)param_7);
        local_1c = *puVar6;
        fVar8 = (float10)fsin((float10)(float)puVar6[3]);
        local_18 = puVar6[1];
        local_14 = puVar6[2];
        uStack_10 = puVar6[3];
        param_7 = (float)(fVar8 * (float10)param_7);
        FUN_0080604f(local_a0,fVar1);
        FUN_0080604f(local_90,param_7);
        FUN_0080d4f1(local_1c,local_18,local_14,0,0,local_c,local_8);
        puVar6 = param_13;
        param_5 = param_5 + 0x20;
        local_1c = *param_13;
        local_18 = param_13[1];
        local_14 = param_13[2];
        uStack_10 = param_13[3];
        FUN_0080604f(local_a0,param_7);
        param_11 = -fVar1;
        FUN_0080604f(local_90,param_11);
        FUN_0080d4f1(local_1c,local_18,local_14,0,0x3f800000,local_c,local_8);
        param_5 = param_5 + 0x20;
        local_1c = *puVar6;
        local_18 = puVar6[1];
        local_14 = puVar6[2];
        uStack_10 = puVar6[3];
        FUN_0080604f(local_a0,param_11);
        param_7 = -param_7;
        FUN_0080604f(local_90,param_7);
        FUN_0080d4f1(local_1c,local_18,local_14,0x3f800000,0x3f800000,local_c,local_8);
        param_5 = param_5 + 0x20;
        local_1c = *puVar6;
        local_18 = puVar6[1];
        local_14 = puVar6[2];
        uStack_10 = puVar6[3];
        FUN_0080604f(local_a0,param_7);
        FUN_0080604f(local_90,fVar1);
        FUN_0080d4f1(local_1c,local_18,local_14,0x3f800000,0,local_c,local_8);
        param_5 = param_5 + 0x20;
        puVar6[5] = (float)puVar6[5] - local_50;
        FUN_00805ec3(puVar6 + 4,local_60);
        puVar6[8] = puVar6[8] + local_4c;
        if ((int)puVar6[9] < (int)puVar6[8]) {
          local_48[2] = local_48[2] + -1;
          puVar6 = (undefined4 *)(local_48[2] * 0x28 + *local_48);
          puVar7 = (undefined4 *)(param_6 + *local_48);
          for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar7 = *puVar6;
            puVar6 = puVar6 + 1;
            puVar7 = puVar7 + 1;
          }
        }
        else {
          param_1 = param_1 + 1;
          param_6 = param_6 + 0x28;
        }
        piVar5 = local_48;
      } while (param_1 < local_48[2]);
    }
    FUN_00801856(param_3,0xffffffff,0xffffffff);
    FUN_008016d1(&param_3);
    FUN_008045d4(param_3);
  }
  return;
}


/* ---- FUN_0080e106 @ 0080e106 ---- */

undefined4 __thiscall FUN_0080e106(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 < *(int *)(param_1 + 0x6c)) {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x78) + param_2 * 4);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


/* ---- FUN_0080e11f @ 0080e11f ---- */

undefined4 __thiscall FUN_0080e11f(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 < *(int *)(param_1 + 0x54)) {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x7c) + param_2 * 4);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


/* ---- FUN_0080e138 @ 0080e138 ---- */

undefined4 * __fastcall FUN_0080e138(undefined4 *param_1)

{
  FUN_008178b0();
  *param_1 = &PTR_FUN_0081fc30;
  param_1[1] = 5;
  FUN_00805cbc(0);
  return param_1;
}


/* ---- FUN_0080e160 @ 0080e160 ---- */

void __fastcall FUN_0080e160(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_0081fc30;
  FUN_008178c4();
  return;
}


/* ---- Exec_Material_Material @ 0080e16b ---- */

void Exec_Material_Material(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  iVar2 = param_1;
  FUN_00818e4a(param_2);
  iVar1 = *(int *)(param_1 + 0x18);
  param_1 = 0;
  if (0 < *(int *)(iVar1 + 0x10)) {
    param_2 = 0;
    do {
      iVar3 = *(int *)(iVar1 + 0xc) + param_2;
      iVar4 = *(int *)(iVar3 + 0xdc) + *(int *)(iVar3 + 0xd8);
      if ((((iVar4 != 0) && (iVar4 != 1)) && (iVar4 != 2)) &&
         (((iVar4 != 3 && (iVar4 != 4)) && (iVar4 == 5)))) {
        puVar5 = (undefined4 *)(*(int *)(iVar2 + 0x94) + 0x60);
        puVar6 = (undefined4 *)(iVar3 + 0x60);
        for (iVar4 = 0x18; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
      }
      param_1 = param_1 + 1;
      param_2 = param_2 + 0xf0;
    } while (param_1 < *(int *)(iVar1 + 0x10));
  }
  return;
}


/* ---- Mesh_MatLink @ 0080e1de ---- */

int Mesh_MatLink(int param_1,int param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if ((param_2 == 0) || (*(int *)(param_2 + 4) != 5)) {
    param_1 = 0;
  }
  else {
    FUN_0081108f();
    uVar1 = *(undefined4 *)(param_1 + 0x40);
    piVar2 = (int *)FUN_00806b54();
    *piVar2 = param_2;
    piVar2[0x11] = param_4;
    iVar5 = 0;
    if (0 < *(int *)(param_1 + 0x30)) {
      iVar4 = 0;
      do {
        iVar3 = *(int *)(param_1 + 0x2c) + iVar4;
        if (*(char *)(iVar3 + 2) != '\0') {
          *(undefined4 *)(iVar3 + 4) = uVar1;
        }
        iVar5 = iVar5 + 1;
        iVar4 = iVar4 + 0x18;
      } while (iVar5 < *(int *)(param_1 + 0x30));
    }
  }
  return param_1;
}


/* ---- FUN_0080e244 @ 0080e244 ---- */

undefined4 __thiscall FUN_0080e244(undefined4 param_1,byte param_2)

{
  FUN_0080e160();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


/* ---- Init_Material_Material @ 0080e263 ---- */

int Init_Material_Material(int param_1)

{
  int iVar1;
  uint *puVar2;
  uint *puVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  int *piVar10;
  uint *puVar11;
  int local_13c [8];
  uint local_11c [4];
  uint local_10c;
  uint local_bc;
  uint local_94 [18];
  uint local_4c;
  uint local_3c;
  uint local_2c [8];
  int local_c;
  int local_8;
  
  iVar7 = 0;
  do {
    local_2c[iVar7] = 0xffffffff;
    piVar10 = local_13c + iVar7;
    *piVar10 = 0;
    iVar1 = FUN_0080e11f(iVar7);
    if ((iVar1 != 0) && (iVar1 = FUN_0080e11f(iVar7), *(int *)(*(int *)(iVar1 + 0x18) + 4) == 1)) {
      iVar1 = FUN_0080e11f(iVar7);
      iVar1 = *(int *)(iVar1 + 0x18);
      iVar9 = *(int *)(iVar1 + 0x20);
      *piVar10 = iVar1;
      if (iVar9 == -1) {
        FUN_0080bb08(*(undefined4 *)(iVar1 + 0x1c));
      }
      local_2c[iVar7] = *(uint *)(*piVar10 + 0x20);
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 < 8);
  iVar7 = operator_new(0x1c);
  if (iVar7 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = FUN_0080e138();
  }
  FUN_008021c8();
  local_4c = *(uint *)(DAT_0140e128 + 0xd8);
  puVar8 = *(uint **)(param_1 + 0x94);
  puVar3 = puVar8;
  puVar11 = local_11c;
  for (iVar7 = 0x30; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar11 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar11 = puVar11 + 1;
  }
  local_3c = puVar8[0x31];
  if ((puVar8[0x30] & 0x1e) == 0) {
    puVar2 = (uint *)FUN_00806b54();
    puVar3 = local_11c;
    puVar11 = puVar2;
    for (iVar7 = 0x3c; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar11 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar11 = puVar11 + 1;
    }
    puVar2[0x30] = local_2c[0];
    puVar2[0x31] = local_2c[1];
    puVar2[0x32] = local_2c[2];
    puVar2[0x33] = local_2c[3];
    puVar2[0x36] = 4;
    puVar2[0x37] = 1;
    uVar4 = puVar8[0x30];
    puVar2[1] = uVar4 & 0x1000;
    if ((uVar4 & 0x1000) != 0) {
      *(byte *)((int)puVar2 + 2) = *(byte *)((int)puVar2 + 2) | 2;
    }
  }
  else {
    local_c = local_8 + 0xc;
    puVar3 = (uint *)FUN_00806b54();
    FUN_008021c8();
    puVar3[0x36] = 0;
    puVar3[0x34] = local_4c;
    *puVar3 = 0x20300;
    *puVar3 = local_11c[0] & 2 | 0x20300;
    if ((puVar8[0x30] & 2) == 0) {
      uVar4 = 0xffffff;
    }
    else {
      uVar4 = puVar8[0x35];
    }
    puVar3[0x1c] = uVar4;
    puVar3[9] = 0x10;
    puVar3[0x13] = 0x20;
    puVar3[0x17] = 0xd;
    puVar3[1] = 0x1000;
    puVar3[0x39] = 0xb;
    if ((*(byte *)((int)puVar8 + 0xc1) & 4) != 0) {
      puVar3[0x30] = local_2c[0];
      puVar3[4] = local_10c;
      *puVar3 = *puVar3 | 1;
      puVar3[0x18] = local_bc;
      puVar3[0x17] = 4;
    }
    puVar2 = (uint *)FUN_00806b54();
    FUN_008021c8();
    puVar2[0x36] = 2;
    puVar2[0x34] = local_4c;
    *puVar2 = 0x200;
    puVar2[2] = 5;
    *puVar2 = local_11c[0] & 2 | 0x2200;
    puVar2[0x20] = puVar8[0x33];
    puVar2[0x1c] = puVar8[0x34];
    puVar2[0x17] = 0xd;
    puVar2[8] = 0x10;
    puVar2[9] = 0x40;
    puVar3 = local_94;
    puVar11 = puVar2 + 0x22;
    for (iVar7 = 0xe; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar11 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar11 = puVar11 + 1;
    }
    if (local_2c[4] != 0xffffffff) {
      puVar2[0x31] = local_2c[4];
      puVar2[5] = puVar8[0x38];
      puVar2[0x19] = puVar8[0x3c];
    }
    if ((puVar8[0x30] & 0x400) != 0) {
      puVar2[0x30] = local_2c[0];
      puVar2[4] = local_10c;
      *puVar2 = *puVar2 | 1;
      puVar2[0x18] = local_bc;
      puVar2[0x17] = 4;
    }
    uVar4 = *(uint *)(*(int *)(DAT_0140e128 + 0x1860) + 0x20);
    puVar2[1] = puVar2[1] | 0x400;
    puVar2[0x33] = uVar4;
    puVar2[7] = 0x4101;
    puVar2[0x12] = 0x40;
    if ((puVar8[0x30] & 0x200) != 0) {
      piVar10 = (int *)(local_8 + 0xc);
      puVar2 = (uint *)FUN_00806b54();
      puVar3 = (uint *)((*(int *)(local_8 + 0x10) + -2) * 0xf0 + *piVar10);
      puVar11 = puVar2;
      for (iVar7 = 0x3c; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar11 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar11 = puVar11 + 1;
      }
      puVar2[0x38] = 2;
      puVar2[0x36] = 4;
      puVar2[2] = 6;
      *puVar2 = *puVar2 & 0xffff2fff | 0x2000;
      if ((puVar8[0x30] & 0x2000) != 0) {
        *(byte *)(puVar2 + 1) = (byte)puVar2[1] | 0x80;
      }
    }
    if ((puVar8[0x30] & 4) != 0) {
      puVar5 = (undefined4 *)FUN_00806b54();
      FUN_008021c8();
      puVar5[0x36] = 1;
      puVar5[0x39] = 7;
      puVar5[0x34] = local_4c;
      *puVar5 = 0x70220;
      puVar5[9] = 0x10;
    }
    if ((puVar8[0x30] & 8) != 0) {
      puVar2 = (uint *)FUN_00806b54();
      puVar3 = local_11c;
      puVar11 = puVar2;
      for (iVar7 = 0x3c; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar11 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar11 = puVar11 + 1;
      }
      uVar4 = *puVar2;
      puVar2[0x30] = local_2c[0];
      puVar2[0x31] = local_2c[1];
      puVar2[0x32] = local_2c[2];
      puVar2[0x33] = local_2c[3];
      puVar2[0x36] = 3;
      puVar2[0x17] = 0xc;
      *puVar2 = uVar4 & 0xffff4eff | 0x4200;
      if ((*(byte *)((int)puVar8 + 0xc1) & 4) != 0) {
        puVar2[0x17] = 4;
        *puVar2 = uVar4 & 0xffff4eff | 0x4201;
        puVar2[4] = local_10c;
      }
    }
    if ((puVar8[0x30] & 0x10) != 0) {
      puVar5 = (undefined4 *)FUN_00806b54();
      FUN_008021c8();
      puVar5[0x36] = 4;
      puVar5[0x34] = local_4c;
      *puVar5 = 0x2200;
      puVar5[1] = (-(uint)((puVar8[0x30] & 0x100) != 0) & 0xfffffff0) + 0x20;
      puVar5[0x32] = local_2c[6];
      puVar5[0x1e] = puVar8[0x35];
      puVar5[6] = puVar8[0x3a];
      puVar5[0x1a] = puVar8[0x3e];
      puVar5[0x11] = 0x10;
      puVar8 = local_94;
      puVar3 = puVar5 + 0x22;
      for (iVar7 = 0xe; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar3 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar3 = puVar3 + 1;
      }
    }
  }
  iVar7 = local_8;
  iVar1 = 0;
  if (0 < *(int *)(local_8 + 0x10)) {
    param_1 = 0;
    do {
      iVar9 = *(int *)(iVar7 + 0xc) + param_1;
      FUN_00804af1();
      uVar6 = FUN_00802664(iVar9);
      param_1 = param_1 + 0xf0;
      iVar1 = iVar1 + 1;
      *(undefined4 *)(iVar9 + 0xd4) = uVar6;
    } while (iVar1 < *(int *)(iVar7 + 0x10));
  }
  iVar1 = 0;
  do {
    puVar5 = (undefined4 *)local_13c[iVar1];
    if (puVar5 != (undefined4 *)0x0) {
      piVar10 = puVar5 + 2;
      *piVar10 = *piVar10 + -1;
      if (*piVar10 == 0) {
        (**(code **)*puVar5)(1);
      }
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 8);
  return iVar7;
}


/* ---- FUN_0080e753 @ 0080e753 ---- */

void __thiscall FUN_0080e753(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_44 [16];
  
  puVar2 = local_44;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  FUN_00805c2c(local_44,param_2);
  return;
}


/* ---- FUN_0080e77b @ 0080e77b ---- */

void __fastcall FUN_0080e77b(undefined1 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 1;
  return;
}


/* ---- FUN_0080e78a @ 0080e78a ---- */

void __thiscall FUN_0080e78a(byte *param_1,byte param_2,char param_3,int param_4)

{
  if (param_4 == 0) {
    if (param_3 == '\0') {
      return;
    }
LAB_0080e7b7:
    *param_1 = *param_1 | param_2;
  }
  else {
    if (param_4 != 1) {
      if (param_4 != 2) {
        return;
      }
      if (param_3 != '\0') goto LAB_0080e7b7;
    }
    *param_1 = *param_1 & ~param_2;
  }
  return;
}


/* ---- FUN_0080e7bd @ 0080e7bd ---- */

void FUN_0080e7bd(void)

{
  undefined1 *puVar1;
  int extraout_ECX;
  int iVar2;
  
  FUN_0080e77b();
  *(undefined4 *)(extraout_ECX + 4) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 8) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 0xc) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 0x10) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 0x14) = 0xffffffff;
  puVar1 = (undefined1 *)(extraout_ECX + 0x18);
  iVar2 = 4;
  do {
    puVar1[4] = 0xff;
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


/* ---- FUN_0080e7e6 @ 0080e7e6 ---- */

void FUN_0080e7e6(void)

{
  int extraout_ECX;
  
  FUN_0080e77b();
  *(undefined4 *)(extraout_ECX + 0x2c) = 0;
  *(undefined4 *)(extraout_ECX + 4) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 8) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 0xc) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 0x10) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 0x14) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 0x18) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 0x1c) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 0x20) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 0x24) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 0x28) = 0xffffffff;
  return;
}


/* ---- FUN_0080e811 @ 0080e811 ---- */

void FUN_0080e811(void)

{
  int extraout_ECX;
  
  FUN_0080e77b();
  *(undefined4 *)(extraout_ECX + 8) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 0xc) = 0xffffffff;
  *(undefined4 *)(extraout_ECX + 0x10) = 0;
  *(undefined4 *)(extraout_ECX + 0x14) = 0;
  *(undefined4 *)(extraout_ECX + 4) = 1;
  return;
}


/* ---- FUN_0080e82e @ 0080e82e ---- */

void __fastcall FUN_0080e82e(undefined4 *param_1)

{
  int iVar1;
  
  for (iVar1 = 0x85; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = 0;
    param_1 = param_1 + 1;
  }
  return;
}


/* ---- FUN_0080e83c @ 0080e83c ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __thiscall FUN_0080e83c(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = DAT_00aba10c;
  if (*(int *)(param_1 + 0x90) == 0) {
    DAT_012ba118 = 0;
    DAT_00aba110 = 0;
    DAT_00aba10c = 0;
    _DAT_012ba120 = param_1;
    *(int *)(param_1 + 0x90) = 1;
    iVar2 = 0;
  }
  piVar1 = (int *)(param_1 + 0x94);
  *piVar1 = *piVar1 + 1;
  if (param_2 != 0) {
    (&DAT_00aba118)[iVar2] = param_2;
    iVar2 = iVar2 + 1;
    DAT_00aba10c = iVar2;
    *(int *)(param_1 + 0x98) = *piVar1 + -1;
  }
  return &DAT_00aba118 + iVar2;
}


/* ---- FUN_0080e8a2 @ 0080e8a2 ---- */

int FUN_0080e8a2(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  iVar1 = DAT_012ba118;
  iVar3 = DAT_012ba118 * 0x40;
  DAT_012ba118 = DAT_012ba118 + 1;
  puVar4 = (undefined4 *)(&DAT_00aaa0f8 + iVar3);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *param_1;
    param_1 = param_1 + 1;
    puVar4 = puVar4 + 1;
  }
  return iVar1;
}


/* ---- FUN_0080e8cf @ 0080e8cf ---- */

int FUN_0080e8cf(undefined4 param_1)

{
  int iVar1;
  
  *(undefined4 *)(&DAT_00aa9cf8 + DAT_00aba110 * 4) = param_1;
  iVar1 = DAT_00aba110;
  DAT_00aba110 = DAT_00aba110 + 1;
  return iVar1;
}


/* ---- FUN_0080e8ef @ 0080e8ef ---- */

void FUN_0080e8ef(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + param_2;
  for (; param_1 < puVar1; param_1 = (undefined4 *)(*(code *)*param_1)(param_3,param_4)) {
  }
  return;
}


/* ---- FUN_0080e91e @ 0080e91e ---- */

int __thiscall FUN_0080e91e(int param_1,uint param_2)

{
  return *(int *)(*(int *)(param_1 + 0x1c) + 0x14 + ((param_2 >> 1) * 0xc + (param_2 & 1)) * 4) *
         0x18 + *(int *)(param_1 + 0x2c);
}


/* ---- FUN_0080e941 @ 0080e941 ---- */

int __thiscall FUN_0080e941(int param_1,uint param_2)

{
  return *(int *)(*(int *)(param_1 + 0x1c) + 0x14 + ((param_2 >> 1) * 0xc + (~param_2 & 1)) * 4) *
         0x18 + *(int *)(param_1 + 0x2c);
}


/* ---- FUN_0080e966 @ 0080e966 ---- */

int __thiscall FUN_0080e966(int param_1,uint param_2)

{
  return *(int *)(*(int *)(param_1 + 0x1c) + 0x1c + ((param_2 >> 1) * 0xc + (param_2 & 1)) * 4) *
         0x20 + *(int *)(param_1 + 0xc);
}


/* ---- FUN_0080e989 @ 0080e989 ---- */

undefined4 __thiscall FUN_0080e989(int param_1,uint param_2)

{
  return *(undefined4 *)
          (*(int *)(param_1 + 0x1c) + 0x14 + ((param_2 >> 1) * 0xc + (param_2 & 1)) * 4);
}


/* ---- FUN_0080e9a6 @ 0080e9a6 ---- */

undefined4 __thiscall FUN_0080e9a6(int param_1,uint param_2)

{
  return *(undefined4 *)
          (*(int *)(param_1 + 0x1c) + 0x1c + ((param_2 >> 1) * 0xc + (param_2 & 1)) * 4);
}


/* ---- FUN_0080e9c3 @ 0080e9c3 ---- */

undefined4 __thiscall FUN_0080e9c3(int param_1,uint param_2)

{
  return *(undefined4 *)(*(int *)(param_1 + 0x1c) + 4 + ((param_2 >> 1) * 0xc + (param_2 & 1)) * 4);
}


/* ---- FUN_0080e9e0 @ 0080e9e0 ---- */

undefined4 __thiscall FUN_0080e9e0(int param_1,uint param_2)

{
  return *(undefined4 *)
          (*(int *)(param_1 + 0x1c) + 0xc + ((param_2 >> 1) * 0xc + (param_2 & 1)) * 4);
}


/* ---- FUN_0080e9fd @ 0080e9fd ---- */

uint __thiscall FUN_0080e9fd(int param_1,uint param_2)

{
  return *(uint *)(*(int *)(param_1 + 0x1c) + 0xc + ((param_2 >> 1) * 0xc + (param_2 & 1)) * 4) ^ 1;
}


/* ---- FUN_0080ea1d @ 0080ea1d ---- */

undefined4 __thiscall FUN_0080ea1d(int param_1,uint param_2)

{
  return *(undefined4 *)(*(int *)(param_1 + 0x1c) + 4 + ((param_2 >> 1) * 0xc + (~param_2 & 1)) * 4)
  ;
}


/* ---- FUN_0080ea3c @ 0080ea3c ---- */

undefined4 FUN_0080ea3c(undefined4 param_1,int param_2)

{
  for (; param_2 != 0; param_2 = param_2 + -1) {
    param_1 = FUN_0080e9c3(param_1);
  }
  return param_1;
}


/* ---- FUN_0080ea5d @ 0080ea5d ---- */

void __thiscall FUN_0080ea5d(int param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  undefined1 local_24 [16];
  undefined1 local_14 [16];
  
  FUN_00805f1f(param_4 * 0x10 + *(int *)(param_1 + 0x7c),*(int *)(param_1 + 0x7c) + param_3 * 0x10);
  FUN_00805f1f(param_5 * 0x10 + *(int *)(param_1 + 0x7c),*(int *)(param_1 + 0x7c) + param_3 * 0x10);
  FUN_0080598d(local_24,local_14);
  return;
}


/* ---- FUN_0080eab3 @ 0080eab3 ---- */

void __fastcall FUN_0080eab3(int param_1,int *param_2,int param_3)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  int local_1c;
  
  local_1c = *param_2;
  iVar2 = param_2[1];
  uVar3 = param_2[2];
  param_2 = param_2 + 3;
  pfVar10 = (float *)(*param_2 * 0x40 + param_3);
  if (local_1c != 0) {
    do {
      param_2 = param_2 + 1;
      pfVar11 = (float *)((iVar2 + *param_2) * 0x10 + *(int *)(param_1 + 0x7c));
      fVar1 = pfVar11[3];
      pfVar9 = (float *)((*param_2 + (uVar3 & 0xf)) * 0x10 + *(int *)(param_1 + 0x7c));
      fVar4 = *pfVar11;
      fVar5 = pfVar11[1];
      fVar6 = pfVar11[2];
      fVar8 = fVar4 * *pfVar10 + fVar6 * pfVar10[8] + fVar1 * pfVar10[0xc] + fVar5 * pfVar10[4];
      fVar7 = fVar4 * pfVar10[1] + fVar6 * pfVar10[9] + fVar1 * pfVar10[0xd] + fVar5 * pfVar10[5];
      fVar4 = fVar6 * pfVar10[10] + fVar1 * pfVar10[0xe] + fVar5 * pfVar10[6] + fVar4 * pfVar10[2];
      if ((uVar3 & 0x10) == 0) {
        *pfVar9 = fVar8;
        pfVar9[1] = fVar7;
        pfVar9[3] = fVar1;
        pfVar9[2] = fVar4;
      }
      else {
        *pfVar9 = fVar8 + *pfVar9;
        pfVar9[1] = fVar7 + pfVar9[1];
        pfVar9[2] = fVar4 + pfVar9[2];
      }
      local_1c = local_1c + -1;
    } while (local_1c != 0);
  }
  return;
}


/* ---- FUN_0080ebc9 @ 0080ebc9 ---- */

int * __fastcall FUN_0080ebc9(undefined4 param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = param_2 + 2;
  for (iVar1 = *param_2; iVar1 != 0; iVar1 = iVar1 + -1) {
    FUN_0080574a(piVar2[2] << 2);
    piVar2 = piVar2 + 3;
  }
  return piVar2;
}


/* ---- FUN_0080ec25 @ 0080ec25 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint * __fastcall FUN_0080ec25(int param_1,undefined4 *param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  uint *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 local_40 [4];
  uint *local_30;
  float local_2c;
  uint local_28;
  float local_24;
  float local_20;
  undefined4 *local_1c;
  float local_18;
  undefined4 *local_14;
  int local_10;
  uint local_c;
  int local_8;
  
  local_8 = param_1;
  puVar3 = param_2 + 2;
  local_2c = *(float *)(param_2[1] * 0x40 + param_3);
  puVar5 = (undefined4 *)*param_2;
  puVar6 = local_14;
  while (local_14 = puVar5, local_14 != (undefined4 *)0x0) {
    puVar5 = (undefined4 *)(*puVar3 * 0x50 + *(int *)(local_8 + 0x7c));
    puVar3 = puVar3 + 1;
    param_3 = 0;
    puVar6 = puVar5;
    for (iVar2 = 0x14; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    do {
      uVar1 = *puVar3;
      puVar3 = puVar3 + 1;
      param_3 = param_3 + 1;
      local_10 = ((uVar1 & 0x7fffffff) * 0x50 + *(int *)(local_8 + 0x7c)) - (int)puVar5;
      local_20 = 7.00649e-45;
      local_1c = puVar5;
      do {
        FUN_00805dce(local_10 + (int)local_1c);
        local_1c = local_1c + 4;
        local_20 = (float)((int)local_20 + -1);
      } while (local_20 != 0.0);
    } while (-1 < (int)uVar1);
    iVar2 = 5;
    local_18 = _DAT_0081f2bc / (float)param_3;
    local_20 = 0.0;
    do {
      FUN_00805e6e(local_18);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    puVar6 = (undefined4 *)((int)local_14 + -1);
    puVar5 = puVar6;
  }
  puVar4 = puVar3 + 1;
  local_14 = puVar6;
  if (*puVar3 != 0) {
    local_28 = *puVar3;
    local_24 = local_2c * _DAT_0081fb68;
    do {
      local_c = puVar4[1];
      uVar1 = puVar4[2];
      local_1c = (undefined4 *)0x0;
      puVar3 = puVar4 + uVar1 + 3;
      local_14 = (undefined4 *)(*puVar4 * 0x50 + *(int *)(local_8 + 0x7c));
      iVar2 = (*puVar3 * 0x50 + *(int *)(local_8 + 0x7c)) - (int)local_14;
      local_30 = puVar3;
      local_10 = iVar2;
      local_18 = local_24 / (float)(int)(uVar1 * uVar1);
      local_20 = _DAT_0081f2bc - local_24 / (float)(int)uVar1;
      do {
        if ((local_c & 1) == 0) {
          FUN_00805e97((int)local_14 + iVar2,local_20);
          iVar2 = 0;
          if (0 < (int)uVar1) {
            do {
              FUN_00805ec3((puVar4[iVar2 + 3] * 5 + (int)local_1c) * 0x10 + *(int *)(local_8 + 0x7c)
                           ,local_18);
              iVar2 = iVar2 + 1;
            } while (iVar2 < (int)uVar1);
          }
          puVar6 = local_40;
          iVar2 = local_10;
          puVar3 = local_30;
        }
        else {
          puVar6 = (undefined4 *)((int)local_14 + iVar2);
        }
        puVar5 = local_14;
        local_c = (int)local_c >> 1;
        local_1c = (undefined4 *)((int)local_1c + 1);
        local_14 = local_14 + 4;
        *puVar5 = *puVar6;
        puVar5[1] = puVar6[1];
        puVar5[2] = puVar6[2];
        puVar5[3] = puVar6[3];
      } while ((int)local_1c < 5);
      local_28 = local_28 - 1;
      puVar4 = puVar3 + 1;
    } while (local_28 != 0);
  }
  local_18 = local_2c * _DAT_0081f370;
  puVar3 = puVar4 + 1;
  local_20 = _DAT_0081f2ac - local_18;
  for (uVar1 = *puVar4; uVar1 != 0; uVar1 = uVar1 - 1) {
    local_c = puVar3[1];
    iVar2 = 0;
    do {
      FUN_00805d72((puVar3[2] * 5 + iVar2) * 0x10 + *(int *)(local_8 + 0x7c),
                   (puVar3[3] * 5 + iVar2) * 0x10 + *(int *)(local_8 + 0x7c));
      if ((local_c & 1) == 0) {
        FUN_00805e97(local_40,_DAT_0081f2ac);
      }
      else {
        FUN_00805e97(local_40,local_20);
        FUN_00805d72((puVar3[4] * 5 + iVar2) * 0x10 + *(int *)(local_8 + 0x7c),
                     (puVar3[5] * 5 + iVar2) * 0x10 + *(int *)(local_8 + 0x7c));
        FUN_00805ec3(local_40,local_18);
      }
      local_c = (int)local_c >> 1;
      iVar2 = iVar2 + 1;
    } while (iVar2 < 5);
    puVar3 = puVar3 + 6;
  }
  return puVar3;
}


/* ---- FUN_0080eec6 @ 0080eec6 ---- */

uint FUN_0080eec6(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  uVar2 = 1;
  for (; param_2 != 0; param_2 = (int)param_2 >> 1) {
    if ((param_2 & 1) != 0) {
      if ((param_1 & 1) != 0) {
        uVar1 = uVar1 | uVar2;
      }
      uVar2 = uVar2 * 2;
    }
    param_1 = (int)param_1 >> 1;
  }
  return uVar1;
}


/* ---- FUN_0080eeef @ 0080eeef ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __fastcall FUN_0080eeef(int param_1,int *param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float10 fVar7;
  undefined1 local_8c [16];
  undefined4 local_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined1 local_6c [16];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  float local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  int local_28;
  float local_24;
  int local_20;
  int local_1c;
  float local_18;
  int local_14;
  float local_10;
  float local_c;
  int local_8;
  
  local_8 = *(int *)(param_1 + 0x7c);
  local_28 = *param_2;
  param_2 = param_2 + 2;
  while (local_28 != 0) {
    iVar5 = *param_2;
    iVar4 = param_2[1] + local_8;
    local_20 = param_2[2] + local_8;
    local_24 = (float)(param_2[3] + local_8);
    param_2 = param_2 + 4;
    local_14 = iVar4;
    FUN_00805f1f(local_24,local_20);
    fVar7 = (float10)FUN_00805fc1(&local_38);
    local_18 = (float)fVar7;
    local_5c = 0;
    local_58 = 0;
    local_54 = 0;
    local_50 = 0;
    local_48 = 0;
    local_44 = 0;
    local_40 = 0;
    local_3c = 0;
    iVar3 = iVar5 + -1;
    if (0 < iVar5 + -1) {
      do {
        local_1c = iVar3;
        local_7c = local_38;
        uStack_78 = uStack_34;
        uStack_74 = uStack_30;
        uStack_70 = uStack_2c;
        iVar5 = *param_2 + local_8;
        fVar6 = (float)(param_2[1] + local_8);
        local_4c = local_18;
        local_10 = local_24;
        local_c = (float)local_20;
        param_2 = param_2 + 2;
        local_24 = fVar6;
        local_20 = iVar5;
        FUN_00805f1f(fVar6,iVar5);
        fVar7 = (float10)FUN_00805fc1(&local_38);
        local_18 = (float)fVar7;
        FUN_0080598d(&local_7c,&local_38);
        if (_DAT_0081f2b8 < local_4c * local_18) {
          FUN_0080604f(local_8c,1.0 / (local_4c * local_18));
        }
        fVar1 = *(float *)((int)local_c + 0x44) - *(float *)((int)local_10 + 0x44);
        fVar2 = *(float *)((int)fVar6 + 0x44) - *(float *)(iVar5 + 0x44);
        fVar6 = (*(float *)((int)fVar6 + 0x40) - *(float *)(iVar5 + 0x40)) * fVar1 +
                (*(float *)((int)local_10 + 0x40) - *(float *)((int)local_c + 0x40)) * fVar2;
        local_c = fVar1;
        if ((float)_DAT_0081fc80 < ABS(fVar6)) {
          local_10 = 1.0 / fVar6;
          FUN_0080602c(&local_7c,local_10 * fVar2);
          FUN_0080604f(&local_38,local_10 * local_c);
          FUN_00806261();
          FUN_00805f44(local_6c);
        }
        iVar3 = local_1c + -1;
      } while (local_1c + -1 != 0);
      local_1c = 0;
      iVar4 = local_14;
    }
    FUN_00806261();
    *(undefined4 *)(iVar4 + 0x10) = local_5c;
    *(undefined4 *)(iVar4 + 0x14) = local_58;
    *(undefined4 *)(iVar4 + 0x18) = local_54;
    *(undefined4 *)(iVar4 + 0x1c) = local_50;
    fVar7 = (float10)FUN_00805fc1((undefined4 *)(iVar4 + 0x10));
    FUN_0080604f(local_14 + 0x10,(float)-fVar7);
    FUN_00806261();
    local_28 = local_28 + -1;
    *(undefined4 *)(local_14 + 0x20) = local_48;
    *(undefined4 *)(local_14 + 0x24) = local_44;
    *(undefined4 *)(local_14 + 0x28) = local_40;
    *(undefined4 *)(local_14 + 0x2c) = local_3c;
  }
  return param_2;
}


/* ---- FUN_0080f102 @ 0080f102 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __fastcall FUN_0080f102(undefined4 param_1,int *param_2,int param_3,int param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  ulonglong uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  float *pfVar15;
  uint uVar16;
  uint uVar17;
  float local_3c;
  float local_38;
  float local_34;
  undefined4 local_30;
  undefined8 local_2c;
  int local_24;
  uint local_20;
  int local_1c;
  int local_18;
  int local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  local_1c = *param_2;
  pfVar15 = (float *)(param_2[2] * 0x40 + param_3);
  iVar5 = *(int *)(param_4 + param_2[1] * 4);
  fVar1 = *pfVar15;
  fVar2 = pfVar15[1];
  fVar3 = pfVar15[2];
  param_2 = param_2 + 3;
  FUN_0080600c(_DAT_0081fc88);
  iVar14 = *(int *)(iVar5 + 0xc);
  uVar17 = *(int *)(iVar5 + 0x10) - 1;
  local_10 = *(int *)(iVar5 + 0x14) - 1;
  local_24 = iVar14;
  local_c = uVar17;
  for (; local_1c != 0; local_1c = local_1c + -1) {
    iVar6 = *param_2;
    local_3c = 0.0;
    param_2 = param_2 + 1;
    param_3 = 0;
    local_38 = 0.0;
    local_34 = 0.0;
    local_30 = 0;
    local_14 = iVar6;
    if (0 < iVar6) {
      do {
        iVar12 = param_2[param_3] * 0x10 + *(int *)(local_18 + 0x7c);
        fVar8 = (float)*(int *)(iVar5 + 0x10) * *(float *)(iVar12 + 0x40);
        local_2c._0_4_ = (uint)(longlong)ROUND(fVar8);
        uVar17 = (uint)local_2c & uVar17;
        fVar8 = fVar8 - (float)(int)(uint)local_2c;
        fVar10 = (float)*(int *)(iVar5 + 0x14) * *(float *)(iVar12 + 0x44);
        local_2c._0_4_ = (uint)(longlong)ROUND(fVar10);
        local_8 = (uint)local_2c & local_10;
        fVar9 = (float)(int)(uint)local_2c;
        iVar13 = *(int *)(iVar5 + 0x10) * local_8;
        uVar16 = uVar17 + 1 & local_c;
        fVar7 = (float)*(ushort *)(iVar14 + (iVar13 + uVar17) * 8);
        iVar14 = *(int *)(iVar5 + 0x10) * (local_8 + 1 & local_10);
        local_20 = (uint)*(ushort *)(local_24 + (uVar17 + iVar14) * 8);
        uVar4 = *(ushort *)(local_24 + (uVar16 + iVar14) * 8);
        local_2c = (ulonglong)CONCAT24(uVar4,(uint)local_2c);
        uVar11 = local_2c;
        fVar7 = ((float)*(ushort *)(local_24 + (iVar13 + uVar16) * 8) - fVar7) * fVar8 + fVar7;
        local_2c._4_4_ = (uint)uVar4;
        fVar7 = ((((((float)local_2c._4_4_ - (float)local_20) * fVar8 + (float)local_20) - fVar7) *
                  (fVar10 - fVar9) + fVar7) - _DAT_0081fbec) * (_DAT_0081f2bc / (float)iVar6);
        local_3c = fVar7 * *(float *)(iVar12 + 0x10) * fVar1 + local_3c;
        param_3 = param_3 + 1;
        local_38 = fVar7 * *(float *)(iVar12 + 0x14) * fVar2 + local_38;
        local_34 = fVar7 * *(float *)(iVar12 + 0x18) * fVar3 + local_34;
        iVar14 = local_24;
        uVar17 = local_c;
        local_2c = uVar11;
      } while (param_3 < iVar6);
    }
    for (; iVar6 != 0; iVar6 = iVar6 + -1) {
      param_2 = param_2 + 1;
      FUN_00805f44(&local_3c);
    }
  }
  return param_2;
}


/* ---- FUN_0080f2cc @ 0080f2cc ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __fastcall FUN_0080f2cc(int param_1,int *param_2,int param_3)

{
  float *pfVar1;
  int iVar2;
  float fVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 local_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined1 local_64 [16];
  undefined1 local_54 [16];
  float local_44 [4];
  uint local_34 [3];
  float local_28 [4];
  int local_18;
  uint local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  local_c = param_3 + param_2[1] * 0x40;
  local_74 = *(undefined4 *)(local_c + 0x40);
  uStack_70 = *(undefined4 *)(local_c + 0x44);
  uStack_6c = *(undefined4 *)(local_c + 0x48);
  local_8 = param_2 + 2;
  uStack_68 = *(undefined4 *)(local_c + 0x4c);
  local_10 = param_1;
  for (iVar2 = *param_2; iVar2 != 0; iVar2 = iVar2 + -1) {
    local_18 = *local_8 * 0x50 + *(int *)(local_10 + 0x7c);
    local_8 = local_8 + 1;
    FUN_00806305(local_c,local_18);
    iVar6 = 0;
    do {
      pfVar1 = (float *)((int)local_28 + iVar6);
      *pfVar1 = *(float *)((int)local_44 + iVar6);
      local_14 = (uint)ROUND(*(float *)((int)local_44 + iVar6));
      *(uint *)((int)local_34 + iVar6) = local_14 & 0xff;
      uVar5 = local_34[1];
      uVar4 = local_34[0];
      fVar3 = *pfVar1 - (float)(int)local_14;
      iVar6 = iVar6 + 4;
      *pfVar1 = ((_DAT_0081fc94 * fVar3 - _DAT_0081fc90) * fVar3 + _DAT_0081fc8c) * fVar3 * fVar3 *
                fVar3;
    } while (iVar6 < 0xc);
    FUN_00805957(&DAT_008408f0 +
                 ((byte)(&DAT_008411f0)
                        [local_34[2] +
                         (byte)(&DAT_008411f0)[local_34[1] + (byte)(&DAT_008411f0)[local_34[0]]]] &
                 0xf) * 4,&DAT_008408f0 +
                          ((byte)(&DAT_008411f0)
                                 [local_34[2] +
                                  (byte)(&DAT_008411f0)
                                        [local_34[1] + (byte)(&DAT_008411f1)[local_34[0]]]] & 0xf) *
                          4,local_28[0]);
    FUN_00805957(&DAT_008408f0 +
                 ((byte)(&DAT_008411f0)
                        [local_34[2] + (byte)(&DAT_008411f1)[uVar5 + (byte)(&DAT_008411f0)[uVar4]]]
                 & 0xf) * 4,
                 &DAT_008408f0 +
                 ((byte)(&DAT_008411f0)
                        [local_34[2] + (byte)(&DAT_008411f1)[uVar5 + (byte)(&DAT_008411f1)[uVar4]]]
                 & 0xf) * 4,local_28[0]);
    FUN_00805957(local_44,local_54,local_28[1]);
    FUN_00805957(&DAT_008408f0 +
                 ((byte)(&DAT_008411f1)
                        [local_34[2] + (byte)(&DAT_008411f0)[uVar5 + (byte)(&DAT_008411f0)[uVar4]]]
                 & 0xf) * 4,
                 &DAT_008408f0 +
                 ((byte)(&DAT_008411f1)
                        [local_34[2] + (byte)(&DAT_008411f0)[uVar5 + (byte)(&DAT_008411f1)[uVar4]]]
                 & 0xf) * 4,local_28[0]);
    FUN_00805957(&DAT_008408f0 +
                 ((byte)(&DAT_008411f1)
                        [local_34[2] + (byte)(&DAT_008411f1)[uVar5 + (byte)(&DAT_008411f0)[uVar4]]]
                 & 0xf) * 4,
                 &DAT_008408f0 +
                 ((byte)(&DAT_008411f1)
                        [local_34[2] + (byte)(&DAT_008411f1)[uVar5 + (byte)(&DAT_008411f1)[uVar4]]]
                 & 0xf) * 4,local_28[0]);
    FUN_00805957(local_54,local_64,local_28[1]);
    FUN_00805957(local_44,local_54,local_28[2]);
    FUN_00805fdf(local_44,&local_74);
  }
  return local_8;
}


/* ---- FUN_0080f53a @ 0080f53a ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0080f53a(float param_1)

{
  int iVar1;
  
  iVar1 = (int)ROUND(param_1 * _DAT_0081fc98);
  if (iVar1 < 0) {
    iVar1 = 0;
  }
  if (0x7fff < iVar1) {
    iVar1 = 0x7fff;
  }
  return iVar1;
}


/* ---- FUN_0080f564 @ 0080f564 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0080f564(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  int iVar5;
  undefined2 uVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  short sVar10;
  float *pfVar11;
  undefined4 *puVar12;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  undefined4 *extraout_ECX_02;
  uint uVar13;
  int iVar14;
  int *piVar15;
  int *piVar16;
  int *piVar17;
  short *psVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  int local_44;
  int local_38;
  int local_30;
  uint local_28;
  int local_24;
  short *local_1c;
  int local_14;
  short *local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  iVar2 = *(int *)(param_2 + 4);
  iVar14 = 0;
  pfVar11 = *(float **)(param_2 + 0x210);
  if (0 < *(int *)(param_2 + 0x20c)) {
    do {
      *pfVar11 = (float)((uint)*pfVar11 & 0xfffffffe);
      *pfVar11 = (float)((uint)*pfVar11 |
                        (uint)(_DAT_0081f374 <=
                              DAT_00aba0fc * *pfVar11 +
                              DAT_00aba100 * pfVar11[1] + DAT_00aba104 * pfVar11[2] + pfVar11[3]));
      pfVar11 = pfVar11 + 4;
      iVar14 = iVar14 + 1;
    } while (iVar14 < *(int *)(param_2 + 0x20c));
  }
  local_38 = 0;
  if (0 < *(int *)(param_2 + 8)) {
    piVar15 = (int *)(param_2 + 0xc);
    do {
      local_14 = *piVar15;
      if (local_14 == -1) {
        if (iVar2 == 1) {
LAB_0080f618:
          uVar20 = 0x1b;
          uVar19 = 6;
LAB_0080f61c:
          local_14 = FUN_0080166b(uVar19,uVar20);
        }
        else if (iVar2 != 2) {
          if (((iVar2 == 3) || (iVar2 == 4)) || (iVar2 == 7)) {
            uVar20 = 0xb;
            uVar19 = 5;
            goto LAB_0080f61c;
          }
          if (iVar2 == 0xb) goto LAB_0080f618;
        }
        *piVar15 = local_14;
      }
      uVar7 = FUN_008016d1(&local_14);
      if (uVar7 != 0) {
        local_1c = (short *)piVar15[0x40];
        local_24 = piVar15[0x10];
        piVar16 = (int *)piVar15[0x50];
        iVar14 = piVar15[0x20];
        if ((iVar2 == 1) || (iVar2 == 2)) {
LAB_0080f68b:
          FUN_0080479f(local_14,iVar14,local_24,&local_c,&local_10,3);
          psVar18 = local_10;
          if (0 < iVar14) {
            do {
              puVar12 = (undefined4 *)(*piVar16 * 0x50 + *(int *)(param_1 + 0x7c));
              *local_c = *puVar12;
              piVar16 = piVar16 + 1;
              local_c[1] = puVar12[1];
              local_c[2] = puVar12[2];
              if (iVar2 == 0xb) {
                uVar6 = FUN_0080f53a(puVar12[0xc]);
                *(undefined2 *)(local_c + 3) = uVar6;
                uVar6 = FUN_0080f53a(*(undefined4 *)(extraout_ECX + 0x34));
                *(undefined2 *)((int)local_c + 0xe) = uVar6;
                uVar6 = FUN_0080f53a(*(undefined4 *)(extraout_ECX_00 + 0x38));
                *(undefined2 *)(local_c + 4) = uVar6;
                uVar6 = FUN_0080f53a(*(undefined4 *)(extraout_ECX_01 + 0x3c));
                *(undefined2 *)((int)local_c + 0x12) = uVar6;
                *(undefined2 *)(local_c + 5) = 0;
                *(undefined2 *)((int)local_c + 0x16) = 0;
                puVar12 = extraout_ECX_02;
              }
              else {
                *(short *)(local_c + 3) = (short)(int)ROUND((float)puVar12[4] * _DAT_0081fc98);
                *(short *)((int)local_c + 0xe) =
                     (short)(int)ROUND((float)puVar12[5] * _DAT_0081fc98);
                *(short *)(local_c + 4) = (short)(int)ROUND((float)puVar12[6] * _DAT_0081fc98);
                *(short *)((int)local_c + 0x12) =
                     (short)(int)ROUND((float)puVar12[10] * _DAT_0081fc98);
                *(short *)(local_c + 5) = (short)(int)ROUND((float)puVar12[8] * _DAT_0081fc98);
                *(short *)((int)local_c + 0x16) =
                     (short)(int)ROUND((float)puVar12[9] * _DAT_0081fc98);
              }
              local_c[6] = puVar12[0x10];
              local_c[7] = puVar12[0x11];
              local_c = local_c + 8;
              iVar14 = iVar14 + -1;
              psVar18 = local_10;
            } while (iVar14 != 0);
          }
          for (; local_24 != 0; local_24 = local_24 + -1) {
            *psVar18 = *local_1c;
            local_1c = local_1c + 1;
            psVar18 = psVar18 + 1;
          }
          FUN_00801856(local_14,0xffffffff,0xffffffff);
          FUN_008016d1(&local_14);
        }
        else if ((iVar2 != 3) && (iVar2 != 4)) {
          if (iVar2 == 7) {
            iVar3 = piVar15[0x70];
            local_44 = piVar15[0x30];
            iVar5 = iVar14 * 2;
            FUN_0080479f(local_14,iVar5,local_44 * 6 + local_24,&local_8,&local_10,uVar7);
            if (((uVar7 & 1) != 0) && (0 < iVar14)) {
              do {
                puVar12 = (undefined4 *)(*piVar16 * 0x50 + *(int *)(param_1 + 0x7c));
                piVar16 = piVar16 + 1;
                *local_8 = *puVar12;
                local_8[1] = puVar12[1];
                local_8[2] = puVar12[2];
                local_8[3] = 0x3f800000;
                local_8[4] = *puVar12;
                local_8[5] = puVar12[1];
                local_8[6] = puVar12[2];
                local_8[7] = 0;
                local_8 = local_8 + 8;
                iVar14 = iVar14 + -1;
              } while (iVar14 != 0);
            }
            if (0 < local_44) {
              iVar8 = iVar3 + 8;
              iVar14 = local_44;
              do {
                *(byte *)(iVar8 + 3) = *(byte *)(iVar8 + 3) & 0x7f;
                iVar8 = iVar8 + 0x10;
                iVar14 = iVar14 + -1;
              } while (iVar14 != 0);
            }
            local_30 = 0;
            iVar14 = *(int *)(param_2 + 0x210);
            if (0 < local_44) {
              local_28 = 0;
              piVar16 = (int *)(iVar3 + 8);
              do {
                piVar9 = piVar16 + -2;
                if ((-1 < *piVar16) &&
                   (uVar7 = local_28, piVar17 = piVar16,
                   ((*(uint *)(iVar14 + piVar16[1] * 4) ^ *(uint *)(iVar14 + *piVar16 * 4)) & 1) !=
                   0)) {
                  do {
                    uVar13 = (*(uint *)(iVar14 + piVar9[(uVar7 & 1) + 2] * 4) ^ uVar7) & 1;
                    local_30 = local_30 + 6;
                    sVar10 = *(short *)((int)piVar9 + uVar13 * 2);
                    sVar1 = *(short *)((int)piVar9 + (uVar13 ^ 1) * 2);
                    *local_10 = sVar1;
                    local_10[1] = sVar10;
                    sVar10 = sVar10 + 1;
                    local_10[2] = sVar10;
                    local_10[3] = sVar1;
                    local_10[4] = sVar10;
                    local_10[5] = sVar1 + 1;
                    local_10 = local_10 + 6;
                    *(byte *)((int)piVar17 + 3) = *(byte *)((int)piVar17 + 3) | 0x80;
                    uVar7 = uVar7 ^ 1;
                    do {
                      uVar7 = (uint)*(ushort *)((int)piVar9 + (uVar7 & 1) * 2 + 4);
                      piVar9 = (int *)((uVar7 / 2) * 0x10 + iVar3);
                      if (piVar9[2] < 0) break;
                    } while (((*(uint *)(iVar14 + piVar9[3] * 4) ^ *(uint *)(iVar14 + piVar9[2] * 4)
                              ) & 1) == 0);
                  } while ((-1 < piVar9[2]) && (piVar17 = piVar9 + 2, uVar7 != local_28));
                }
                local_28 = local_28 + 2;
                piVar16 = piVar16 + 4;
                local_44 = local_44 + -1;
              } while (local_44 != 0);
            }
            piVar16 = (int *)piVar15[0x60];
            if ((DAT_012ba11c & 0x800000) == 0) {
              local_24 = 0;
            }
            if (0 < local_24) {
              local_44 = (local_24 - 1U) / 3 + 1;
              do {
                uVar4 = (ushort)*(undefined4 *)(iVar14 + *piVar16 * 4) & 1;
                piVar16 = piVar16 + 1;
                *local_10 = *local_1c * 2 + uVar4;
                local_10[1] = local_1c[1] * 2 + uVar4;
                psVar18 = local_1c + 2;
                local_1c = local_1c + 3;
                local_10[2] = *psVar18 * 2 + uVar4;
                local_10 = local_10 + 3;
                local_44 = local_44 + -1;
              } while (local_44 != 0);
            }
            FUN_00801856(local_14,iVar5,local_30 + local_24);
            if (local_30 + local_24 != 0) {
              FUN_00805162(DAT_012ba11c | 0x500002);
              FUN_008016d1(&local_14);
            }
            FUN_008016bc(local_14,2);
          }
          else if (iVar2 != 8) goto LAB_0080f68b;
        }
      }
      local_38 = local_38 + 1;
      piVar15 = piVar15 + 1;
    } while (local_38 < *(int *)(param_2 + 8));
  }
  return;
}


/* ---- FUN_0080fae3 @ 0080fae3 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __fastcall FUN_0080fae3(undefined4 param_1,int *param_2,int param_3)

{
  float fVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  float10 fVar5;
  float local_60 [4];
  float local_50 [7];
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  int local_10;
  int local_c;
  float local_8;
  
  local_c = *param_2;
  local_14 = param_2[1];
  pfVar2 = (float *)(param_2[2] * 0x40 + param_3);
  fVar1 = 1.0 / pfVar2[7];
  param_2 = param_2 + 3;
  iVar3 = 0;
  do {
    if (_DAT_0081f374 <= *pfVar2) {
      local_8 = 1.0;
    }
    else {
      local_8 = -1.0;
    }
    fVar5 = (float10)FUN_008056db((double)ABS(*pfVar2),(double)fVar1);
    iVar4 = iVar3 + 4;
    *(float *)((int)local_60 + iVar3) = (float)(fVar5 * (float10)local_8);
    *(float *)((int)local_50 + iVar3) = fVar1 * pfVar2[4];
    *(float *)((int)local_50 + iVar3 + 0xc) = fVar1 * pfVar2[8];
    iVar3 = iVar4;
    pfVar2 = pfVar2 + 1;
  } while (iVar4 < 0xc);
  FUN_00805b55();
  if (local_c != 0) {
    local_8 = (float)(local_14 & 3);
    do {
      iVar3 = *param_2;
      if (local_8 == 1.4013e-45) {
        iVar4 = 0;
        local_24 = 0;
        local_20 = 0;
        local_1c = 0;
        local_18 = 0;
        if (0 < iVar3) {
          do {
            FUN_00805f44();
            iVar4 = iVar4 + 1;
          } while (iVar4 < iVar3);
        }
        FUN_00806261();
        FUN_00805f88();
      }
      param_3 = 0;
      local_34 = 0;
      local_30 = 0;
      local_2c = 0;
      local_28 = 0x3f800000;
      if (0 < iVar3) {
        do {
          if ((local_8 == 0.0) || (local_8 == 4.2039e-45)) {
            FUN_00805fdf(param_2[param_3 + 1] * 0x50 + *(int *)(local_10 + 0x7c) + 0x10,local_50 + 3
                        );
          }
          else {
            FUN_00805f44();
          }
          FUN_00805f88();
          FUN_008061df();
          FUN_008061df();
          param_3 = param_3 + 1;
        } while (param_3 < iVar3);
      }
      local_c = local_c + -1;
      param_2 = param_2 + iVar3 + 1;
    } while (local_c != 0);
  }
  return param_2;
}


/* ---- FUN_0080fc8b @ 0080fc8b ---- */

void FUN_0080fc8b(uint param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_0080e78a(param_1 >> 0x10,param_2,param_3);
  return;
}


/* ---- FUN_0080fca4 @ 0080fca4 ---- */

void FUN_0080fca4(uint param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_0080e78a(param_1 >> 8,param_2,param_3);
  return;
}


/* ---- FUN_0080fcbd @ 0080fcbd ---- */

undefined4 * __fastcall FUN_0080fcbd(undefined4 *param_1)

{
  int *piVar1;
  int *piVar2;
  
  FUN_008178b0();
  *param_1 = &PTR_FUN_0081fc9c;
  param_1[1] = 6;
  FUN_00805cbc(0x10);
  FUN_00805cbc(0x10);
  FUN_00805cbc(0x10);
  piVar1 = param_1 + 0xf;
  FUN_00805cbc(0x10);
  FUN_00805cbc(0x10);
  FUN_00805cbc(1);
  FUN_00805cbc(1);
  param_1[0x26] = 0xffffffff;
  param_1[0x27] = 0xffffffff;
  param_1[0x21] = 0;
  param_1[0x20] = 0;
  param_1[0x1f] = 0;
  param_1[0x22] = 0;
  param_1[0x23] = 0;
  param_1[0x24] = 0;
  param_1[0x25] = 0;
  *(undefined1 *)(param_1 + 0x28) = 0;
  param_1[0x10] = 2;
  *(undefined4 *)*piVar1 = 0;
  *(undefined4 *)(*piVar1 + 0x44) = 0;
  *(undefined4 *)(*piVar1 + 0x4c) = *(undefined4 *)(DAT_0140e128 + 0x1858);
  piVar2 = (int *)(*(int *)(*piVar1 + 0x4c) + 8);
  *piVar2 = *piVar2 + 1;
  *(undefined4 *)(*piVar1 + 0x90) = 0;
  return param_1;
}


/* ---- FUN_0080fda5 @ 0080fda5 ---- */

void __fastcall FUN_0080fda5(undefined4 *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 1;
  *param_1 = &PTR_FUN_0081fc9c;
  if (1 < (int)param_1[0x10]) {
    iVar4 = 0x4c;
    do {
      puVar2 = *(undefined4 **)(iVar4 + param_1[0xf]);
      piVar1 = puVar2 + 2;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        (**(code **)*puVar2)(1);
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 0x4c;
    } while (iVar3 < (int)param_1[0x10]);
  }
  operator_delete(param_1[0x1f]);
  if (param_1[3] != 0) {
    operator_delete(param_1[3]);
    param_1[3] = 0;
  }
  if (param_1[7] != 0) {
    operator_delete(param_1[7]);
    param_1[7] = 0;
  }
  if (param_1[0xb] != 0) {
    operator_delete(param_1[0xb]);
    param_1[0xb] = 0;
  }
  if (param_1[0xf] != 0) {
    operator_delete(param_1[0xf]);
    param_1[0xf] = 0;
  }
  if (param_1[0x13] != 0) {
    operator_delete(param_1[0x13]);
    param_1[0x13] = 0;
  }
  if (param_1[0x17] != 0) {
    operator_delete(param_1[0x17]);
    param_1[0x17] = 0;
  }
  if (param_1[0x1b] != 0) {
    operator_delete(param_1[0x1b]);
    param_1[0x1b] = 0;
  }
  FUN_008178c4();
  return;
}


/* ---- FUN_0080fe61 @ 0080fe61 ---- */

void __thiscall FUN_0080fe61(int param_1,undefined4 param_2,int param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(int *)(param_1 + 0x84) = param_3;
  puVar1 = (undefined4 *)operator_new(param_3 * 0x50);
  iVar2 = *(int *)(param_1 + 0x84) * 0x14;
  *(undefined4 **)(param_1 + 0x7c) = puVar1;
  if (iVar2 != 0) {
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar1 = 0;
      puVar1 = puVar1 + 1;
    }
  }
  FUN_00806ae3();
  FUN_00806ae3();
  FUN_00806ae3();
  return;
}


/* ---- FUN_0080fec8 @ 0080fec8 ---- */

void __thiscall FUN_0080fec8(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int local_8;
  
  iVar1 = *(int *)(param_1 + 0x84);
  if (iVar1 <= param_2) {
    iVar1 = iVar1 * 2 - iVar1 / 2;
    local_8 = param_2;
    if (param_2 <= iVar1) {
      local_8 = iVar1;
    }
    iVar2 = operator_new(local_8 * 0x50);
    FUN_0080574a(*(int *)(param_1 + 0x80) * 0x14);
    iVar1 = *(int *)(param_1 + 0x80);
    iVar4 = (local_8 - iVar1) * 0x14;
    puVar3 = (undefined4 *)(iVar1 * 0x50 + iVar2);
    if (iVar4 != 0) {
      for (; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
    }
    operator_delete(*(undefined4 *)(param_1 + 0x7c));
    *(int *)(param_1 + 0x7c) = iVar2;
    *(int *)(param_1 + 0x84) = local_8;
  }
  *(int *)(param_1 + 0x80) = param_2;
  return;
}


/* ---- FUN_0080ff59 @ 0080ff59 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0080ff59(int param_1)

{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + 0x94);
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == *(int *)(param_1 + 0x98)) {
    *(int *)(param_1 + 0x98) = -1;
  }
  if (*piVar1 == 0) {
    FUN_0080e8ef(&DAT_00aba118,DAT_00aba10c,&DAT_00aaa0f8,&DAT_00aa9cf8);
    _DAT_012ba120 = 0;
    DAT_00aba10c = 0;
    DAT_012ba118 = 0;
    DAT_00aba110 = 0;
    *(undefined4 *)(param_1 + 0x90) = 0;
  }
  return;
}


/* ---- FUN_0080ffb7 @ 0080ffb7 ---- */

int __fastcall FUN_0080ffb7(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10);
  FUN_0080fec8(iVar1 + 1);
  FUN_00806ae3();
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  return iVar1;
}


/* ---- FUN_0080ffdb @ 0080ffdb ---- */

int FUN_0080ffdb(void)

{
  int iVar1;
  int *extraout_EDX;
  int iVar2;
  
  iVar1 = FUN_0080ffb7();
  iVar2 = iVar1 * 0x20;
  FUN_0080e7bd();
  *(int *)(*extraout_EDX + 0x14 + iVar2) = iVar1;
  *(int *)(*extraout_EDX + 4 + iVar2) = iVar1;
  *(int *)(*extraout_EDX + 8 + iVar2) = iVar1;
  return iVar1;
}


/* ---- FUN_00810010 @ 00810010 ---- */

void __thiscall FUN_00810010(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar1 = FUN_0080ffb7();
  puVar3 = (undefined4 *)(param_2 * 0x20 + *(int *)(param_1 + 0xc));
  puVar4 = (undefined4 *)(iVar1 * 0x20 + *(int *)(param_1 + 0xc));
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  *(int *)(*(int *)(param_1 + 0xc) + 0x14 + iVar1 * 0x20) = iVar1;
  return;
}


/* ---- FUN_00810043 @ 00810043 ---- */

void __thiscall FUN_00810043(int param_1,uint param_2,uint param_3,uint param_4,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  
  uVar4 = FUN_0080e9e0(param_2);
  uVar5 = FUN_0080e9e0(param_3);
  iVar6 = FUN_0080e989(param_2);
  iVar10 = *(int *)(param_1 + 0x20);
  FUN_00806ae3();
  iVar1 = *(int *)(param_1 + 0x30);
  *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
  FUN_00806ae3();
  *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + 1;
  iVar2 = *(int *)(param_1 + 0x2c);
  iVar3 = *(int *)(param_1 + 0x1c);
  puVar13 = (undefined4 *)(iVar10 * 0x30 + iVar3);
  puVar12 = (undefined4 *)((param_2 >> 1) * 0x30 + iVar3);
  puVar8 = puVar13;
  for (iVar9 = 0xc; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar8 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar8 = puVar8 + 1;
  }
  puVar13[0xb] = 0;
  FUN_0080e78a(param_4,1,param_5);
  uVar7 = FUN_0080e9a6(param_3);
  puVar13[7] = uVar7;
  uVar7 = FUN_0080e9a6(param_2);
  puVar13[9] = 0xffffffff;
  puVar13[10] = 0xffffffff;
  puVar13[1] = param_2;
  puVar13[8] = uVar7;
  puVar13[2] = param_3;
  puVar13[5] = iVar6;
  puVar13[6] = iVar6;
  puVar13[3] = uVar5;
  puVar13[4] = uVar4;
  iVar10 = iVar10 * 2;
  *(int *)(iVar3 + 0xc + ((param_2 >> 1) * 0xc + (param_2 & 1)) * 4) = iVar10;
  *(int *)(iVar3 + 4 + (((int)uVar4 >> 1) * 0xc + (uVar4 & 1)) * 4) = iVar10 + 1;
  *(int *)(iVar3 + 0xc + ((param_3 >> 1) * 0xc + (param_3 & 1)) * 4) = iVar10 + 1;
  *(int *)(iVar3 + 4 + (((int)uVar5 >> 1) * 0xc + (uVar5 & 1)) * 4) = iVar10;
  puVar8 = (undefined4 *)(iVar6 * 0x18 + iVar2);
  puVar11 = (undefined4 *)(iVar1 * 0x18 + iVar2);
  puVar13 = puVar8;
  puVar12 = puVar11;
  for (iVar10 = 6; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar12 = *puVar13;
    puVar13 = puVar13 + 1;
    puVar12 = puVar12 + 1;
  }
  FUN_0080e78a(param_4 >> 8,1,param_5);
  puVar8[2] = param_2;
  puVar11[2] = param_3;
  uVar4 = param_3;
  do {
    *(int *)(iVar3 + 0x14 + ((uVar4 >> 1) * 0xc + (uVar4 & 1)) * 4) = iVar1;
    uVar4 = FUN_0080e9c3(uVar4);
  } while (uVar4 != param_3);
  return;
}


/* ---- FUN_008101da @ 008101da ---- */

void __fastcall FUN_008101da(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar2 = *(int *)(param_1 + 0x10);
  iVar5 = 0;
  if (0 < iVar2) {
    iVar4 = 0;
    do {
      iVar3 = *(int *)(param_1 + 0xc);
      if (*(int *)(iVar4 + 0x14 + iVar3) == iVar5) {
        piVar1 = (int *)(iVar4 + 8 + iVar3);
        *piVar1 = *(int *)(*piVar1 * 0x20 + 0x14 + iVar3);
        piVar1 = (int *)(iVar4 + 4 + *(int *)(param_1 + 0xc));
        *piVar1 = *(int *)(*piVar1 * 0x20 + 0x14 + *(int *)(param_1 + 0xc));
      }
      else {
        *(int *)(iVar4 + 4 + iVar3) = iVar5;
        *(int *)(iVar4 + 8 + *(int *)(param_1 + 0xc)) = iVar5;
        *(undefined1 *)(iVar4 + 2 + *(int *)(param_1 + 0xc)) = 0;
        *(undefined1 *)(iVar4 + *(int *)(param_1 + 0xc)) = 0;
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x20;
    } while (iVar5 < iVar2);
  }
  iVar5 = *(int *)(param_1 + 0x20);
  if (0 < iVar5) {
    iVar4 = 0;
    do {
      piVar1 = (int *)(iVar4 + 0x1c + *(int *)(param_1 + 0x1c));
      *piVar1 = *(int *)(*piVar1 * 0x20 + 0x14 + *(int *)(param_1 + 0xc));
      piVar1 = (int *)(iVar4 + 0x20 + *(int *)(param_1 + 0x1c));
      iVar4 = iVar4 + 0x30;
      iVar5 = iVar5 + -1;
      *piVar1 = *(int *)(*piVar1 * 0x20 + 0x14 + *(int *)(param_1 + 0xc));
    } while (iVar5 != 0);
  }
  iVar4 = 0;
  iVar5 = 0;
  if (0 < iVar2) {
    do {
      *(int *)(iVar4 + 0x14 + *(int *)(param_1 + 0xc)) = iVar5;
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x20;
    } while (iVar5 < iVar2);
  }
  return;
}


/* ---- FUN_00810297 @ 00810297 ---- */

undefined4 FUN_00810297(uint param_1,int param_2)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  int extraout_ECX;
  
  iVar3 = FUN_0080e91e(param_1);
  cVar1 = *(char *)(iVar3 + 2);
  iVar3 = FUN_0080e941(param_1);
  cVar2 = *(char *)(iVar3 + 2);
  if (((*(byte *)((param_1 >> 1) * 0x30 + 0x2c + *(int *)(extraout_ECX + 0x1c)) & 6) != 0) ||
     (param_2 != 0)) {
    cVar2 = '\0';
  }
  if ((cVar1 == '\0') || (cVar2 != '\0')) {
    uVar4 = 0;
  }
  else {
    uVar4 = 1;
  }
  return uVar4;
}


/* ---- FUN_008102dc @ 008102dc ---- */

void __thiscall FUN_008102dc(int param_1,uint param_2)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  
  if ((param_2 & 0xff0000) != 0) {
    iVar3 = 0;
    iVar4 = 0;
    if (0 < *(int *)(param_1 + 0x10)) {
      do {
        pbVar1 = (byte *)(*(int *)(param_1 + 0xc) + iVar3);
        iVar4 = iVar4 + 1;
        pbVar1[2] = (*pbVar1 & (byte)(param_2 >> 0x10)) != 0;
        iVar3 = iVar3 + 0x20;
      } while (iVar4 < *(int *)(param_1 + 0x10));
    }
  }
  bVar2 = (byte)(param_2 >> 8);
  if (bVar2 != 0) {
    iVar3 = 0;
    iVar4 = 0;
    if (0 < *(int *)(param_1 + 0x30)) {
      do {
        pbVar1 = (byte *)(*(int *)(param_1 + 0x2c) + iVar3);
        iVar4 = iVar4 + 1;
        pbVar1[2] = (*pbVar1 & bVar2) != 0;
        iVar3 = iVar3 + 0x18;
      } while (iVar4 < *(int *)(param_1 + 0x30));
    }
  }
  if ((byte)param_2 != 0) {
    iVar3 = 0;
    iVar4 = 0;
    if (0 < *(int *)(param_1 + 0x20)) {
      do {
        pbVar1 = (byte *)(*(int *)(param_1 + 0x1c) + iVar3);
        iVar4 = iVar4 + 1;
        pbVar1[2] = (*pbVar1 & (byte)param_2) != 0;
        iVar3 = iVar3 + 0x30;
      } while (iVar4 < *(int *)(param_1 + 0x20));
    }
  }
  return;
}


/* ---- FUN_00810366 @ 00810366 ---- */

void __thiscall FUN_00810366(int param_1,char param_2,byte param_3)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  
  if (((param_3 & 4) != 0) && (iVar3 = 0, 0 < *(int *)(param_1 + 0x10))) {
    iVar1 = 0;
    do {
      *(char *)(*(int *)(param_1 + 0xc) + 2 + iVar1) = param_2;
      iVar3 = iVar3 + 1;
      iVar1 = iVar1 + 0x20;
    } while (iVar3 < *(int *)(param_1 + 0x10));
  }
  if (((param_3 & 2) != 0) && (iVar3 = 0, 0 < *(int *)(param_1 + 0x30))) {
    iVar1 = 0;
    do {
      if ((param_2 == '\0') || (*(int *)(*(int *)(param_1 + 0x2c) + 4 + iVar1) == 0)) {
        uVar2 = 0;
      }
      else {
        uVar2 = 1;
      }
      *(undefined1 *)(*(int *)(param_1 + 0x2c) + 2 + iVar1) = uVar2;
      iVar3 = iVar3 + 1;
      iVar1 = iVar1 + 0x18;
    } while (iVar3 < *(int *)(param_1 + 0x30));
  }
  if (((param_3 & 1) != 0) && (iVar3 = 0, 0 < *(int *)(param_1 + 0x20))) {
    iVar1 = 0;
    do {
      *(char *)(iVar1 + 2 + *(int *)(param_1 + 0x1c)) = param_2;
      iVar3 = iVar3 + 1;
      iVar1 = iVar1 + 0x30;
    } while (iVar3 < *(int *)(param_1 + 0x20));
  }
  return;
}


/* ---- FUN_008103f3 @ 008103f3 ---- */

void __thiscall FUN_008103f3(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_2._2_1_ != '\0') {
    iVar2 = 0;
    iVar1 = 0;
    if (0 < *(int *)(param_1 + 0x10)) {
      do {
        FUN_0080fc8b(param_2,CONCAT31((int3)((uint)*(int *)(param_1 + 0xc) >> 8),
                                      *(undefined1 *)(*(int *)(param_1 + 0xc) + iVar2 + 2)),param_3)
        ;
        iVar1 = iVar1 + 1;
        iVar2 = iVar2 + 0x20;
      } while (iVar1 < *(int *)(param_1 + 0x10));
    }
  }
  if (param_2._1_1_ != '\0') {
    iVar2 = 0;
    iVar1 = 0;
    if (0 < *(int *)(param_1 + 0x30)) {
      do {
        FUN_0080fca4(param_2,CONCAT31((int3)((uint)*(int *)(param_1 + 0x2c) >> 8),
                                      *(undefined1 *)(*(int *)(param_1 + 0x2c) + iVar2 + 2)),param_3
                    );
        iVar1 = iVar1 + 1;
        iVar2 = iVar2 + 0x18;
      } while (iVar1 < *(int *)(param_1 + 0x30));
    }
  }
  return;
}


/* ---- FUN_0081045c @ 0081045c ---- */

void __thiscall FUN_0081045c(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  if (0 < *(int *)(param_1 + 0x10)) {
    do {
      if ((param_2 & 0xff0000) != 0) {
        FUN_0080e78a(param_2 >> 0x10,1,param_3);
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < *(int *)(param_1 + 0x10));
  }
  iVar2 = 0;
  iVar1 = 0;
  if (0 < *(int *)(param_1 + 0x30)) {
    do {
      if ((*(int *)(*(int *)(param_1 + 0x2c) + iVar2 + 4) != 0) && (param_2._1_1_ != '\0')) {
        FUN_0080e78a(param_2 >> 8,1,param_3);
      }
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + 0x18;
    } while (iVar1 < *(int *)(param_1 + 0x30));
  }
  iVar1 = 0;
  if (0 < *(int *)(param_1 + 0x20)) {
    do {
      if ((param_2 & 0xff) != 0) {
        FUN_0080e78a(param_2,1,param_3);
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < *(int *)(param_1 + 0x20));
  }
  return;
}


/* ---- FUN_0081050f @ 0081050f ---- */

void FUN_0081050f(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int extraout_ECX;
  int extraout_ECX_00;
  int iVar4;
  undefined4 local_8;
  
  iVar4 = 0;
  FUN_00810366(0,4);
  local_8 = 0;
  iVar2 = extraout_ECX;
  if (0 < *(int *)(extraout_ECX + 0x30)) {
    do {
      iVar1 = *(int *)(iVar2 + 0x2c) + iVar4;
      if (*(char *)(iVar1 + 2) != '\0') {
        iVar1 = *(int *)(iVar1 + 8);
        iVar3 = iVar1;
        do {
          iVar2 = FUN_0080e966(iVar3);
          *(undefined1 *)(iVar2 + 2) = 1;
          iVar3 = FUN_0080e9c3(iVar3);
          iVar2 = extraout_ECX_00;
        } while (iVar3 != iVar1);
      }
      local_8 = local_8 + 1;
      iVar4 = iVar4 + 0x18;
    } while (local_8 < *(int *)(iVar2 + 0x30));
  }
  return;
}


/* ---- FUN_00810561 @ 00810561 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00810561(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int extraout_ECX;
  int extraout_ECX_00;
  int iVar3;
  
  iVar3 = 0;
  if (0 < *(int *)(param_1 + 0x20) * 2) {
    do {
      if (*(char *)((iVar3 / 2) * 0x30 + 2 + *(int *)(param_1 + 0x1c)) != '\0') {
        uVar1 = FUN_0080e9e0(iVar3);
        iVar2 = FUN_0080e9a6(uVar1);
        param_1 = extraout_ECX;
        if (_DAT_0081f2ac <
            *(float *)(*(int *)(extraout_ECX + 0x7c) + 0x40 + (iVar2 * 0x14 + param_2) * 4)) {
          iVar2 = FUN_0080e966(iVar3);
          *(undefined1 *)(iVar2 + 2) = 1;
          uVar1 = FUN_0080e9c3(iVar3);
          iVar2 = FUN_0080e966(uVar1);
          *(undefined1 *)(iVar2 + 2) = 1;
          param_1 = extraout_ECX_00;
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(param_1 + 0x20) * 2);
  }
  return;
}


/* ---- FUN_008105d3 @ 008105d3 ---- */

void __fastcall FUN_008105d3(int param_1)

{
  bool bVar1;
  undefined1 uVar2;
  int iVar3;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int iVar4;
  int iVar5;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar4 = 0;
  iVar5 = 0;
  if (0 < *(int *)(param_1 + 0x20)) {
    do {
      iVar3 = FUN_0080e966(iVar5 * 2);
      param_1 = extraout_ECX;
      if (*(char *)(iVar3 + 2) == '\0') {
LAB_00810605:
        uVar2 = 0;
      }
      else {
        iVar3 = FUN_0080e966(iVar5 * 2 + 1);
        param_1 = extraout_ECX_00;
        if (*(char *)(iVar3 + 2) == '\0') goto LAB_00810605;
        uVar2 = 1;
      }
      *(undefined1 *)(*(int *)(param_1 + 0x1c) + 2 + iVar4) = uVar2;
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x30;
    } while (iVar5 < *(int *)(param_1 + 0x20));
  }
  local_10 = 0;
  if (0 < *(int *)(param_1 + 0x30)) {
    local_c = 0;
    do {
      iVar4 = *(int *)(param_1 + 0x2c) + local_c;
      iVar5 = *(int *)(iVar4 + 8);
      bVar1 = true;
      local_8 = iVar5;
      do {
        iVar3 = FUN_0080e966(local_8);
        if (*(char *)(iVar3 + 2) == '\0') {
          bVar1 = false;
        }
        local_8 = FUN_0080e9c3(local_8);
      } while ((iVar5 != local_8) && (bVar1));
      local_10 = local_10 + 1;
      local_c = local_c + 0x18;
      *(bool *)(iVar4 + 2) = bVar1;
      param_1 = extraout_ECX_01;
    } while (local_10 < *(int *)(extraout_ECX_01 + 0x30));
  }
  return;
}


/* ---- FUN_0081066f @ 0081066f ---- */

void __thiscall FUN_0081066f(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x2c) + 8 + param_3 * 0x18);
  uVar1 = FUN_0080e9c3(uVar4);
  iVar2 = FUN_0080e9a6(uVar1);
  iVar2 = iVar2 * 5;
  iVar3 = FUN_0080e9a6(uVar4);
  iVar3 = iVar3 * 5;
  uVar4 = FUN_0080e9e0(uVar4);
  iVar5 = FUN_0080e9a6(uVar4);
  FUN_0080ea5d(param_2,iVar5 * 5,iVar3,iVar2);
  return;
}


/* ---- FUN_008106b7 @ 008106b7 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_008106b7(int param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  float10 fVar7;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x2c) + 8 + param_3 * 0x18);
  iVar6 = iVar1;
  do {
    iVar2 = FUN_0080e9c3(iVar6);
    iVar3 = FUN_0080e9a6(iVar2);
    iVar3 = iVar3 * 5;
    iVar4 = FUN_0080e9a6(iVar6);
    iVar4 = iVar4 * 5;
    uVar5 = FUN_0080e9e0(iVar6);
    iVar6 = FUN_0080e9a6(uVar5);
    FUN_0080ea5d(param_2,iVar6 * 5,iVar4,iVar3);
    fVar7 = (float10)FUN_00805fc1(param_2);
    if ((float10)_DAT_0081fca8 <= fVar7) break;
    iVar6 = iVar2;
  } while (iVar2 != iVar1);
  if (fVar7 < (float10)_DAT_0081fca8) {
    *param_2 = 0x3f800000;
    param_2[1] = 0;
    param_2[2] = 0;
  }
  else {
    FUN_0080600c((float)((float10)_DAT_0081f358 / SQRT(fVar7)));
  }
  return;
}


/* ---- FUN_00810764 @ 00810764 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00810764(int param_1,undefined4 param_2,float *param_3)

{
  float fVar1;
  float *pfVar2;
  int iVar3;
  float local_18;
  float local_14;
  float local_10;
  int local_8;
  
  pfVar2 = param_3;
  FUN_00810366(1,2);
  FUN_0081050f();
  fVar1 = _DAT_0081fcb0;
  *param_3 = _DAT_0081fcb0;
  iVar3 = 0;
  local_8 = 0;
  param_3[1] = fVar1;
  param_3[2] = fVar1;
  param_3[3] = 1.0;
  fVar1 = _DAT_0081fcac;
  param_3[4] = _DAT_0081fcac;
  param_3[5] = fVar1;
  param_3[6] = fVar1;
  param_3[7] = 1.0;
  if (0 < *(int *)(param_1 + 0x10)) {
    param_3 = (float *)0x0;
    do {
      if (*(char *)(iVar3 + 2 + *(int *)(param_1 + 0xc)) != '\0') {
        FUN_00806305(param_2,*(int *)(param_1 + 0x7c) + (int)param_3);
        fVar1 = *pfVar2;
        if (local_18 <= *pfVar2) {
          fVar1 = local_18;
        }
        *pfVar2 = fVar1;
        fVar1 = pfVar2[1];
        if (local_14 <= pfVar2[1]) {
          fVar1 = local_14;
        }
        pfVar2[1] = fVar1;
        fVar1 = pfVar2[2];
        if (local_10 <= pfVar2[2]) {
          fVar1 = local_10;
        }
        pfVar2[2] = fVar1;
        fVar1 = pfVar2[4];
        if (pfVar2[4] <= local_18) {
          fVar1 = local_18;
        }
        pfVar2[4] = fVar1;
        fVar1 = pfVar2[5];
        if (pfVar2[5] <= local_14) {
          fVar1 = local_14;
        }
        pfVar2[5] = fVar1;
        fVar1 = pfVar2[6];
        if (pfVar2[6] <= local_10) {
          fVar1 = local_10;
        }
        pfVar2[6] = fVar1;
      }
      local_8 = local_8 + 1;
      param_3 = (float *)((int)param_3 + 0x50);
      iVar3 = iVar3 + 0x20;
    } while (local_8 < *(int *)(param_1 + 0x10));
  }
  return;
}


/* ---- FUN_00810873 @ 00810873 ---- */

void __thiscall
FUN_00810873(int param_1,float *param_2,float *param_3,undefined4 param_4,undefined4 param_5)

{
  undefined1 uVar1;
  float *pfVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  iVar3 = 0;
  local_c = 0;
  if (0 < *(int *)(param_1 + 0x10)) {
    local_8 = 0;
    do {
      pfVar2 = (float *)(local_8 + *(int *)(param_1 + 0x7c));
      if (((*param_3 < ABS(*pfVar2 - *param_2)) || (param_3[1] < ABS(pfVar2[1] - param_2[1]))) ||
         (param_3[2] < ABS(pfVar2[2] - param_2[2]))) {
        uVar1 = 0;
      }
      else {
        uVar1 = 1;
      }
      local_c = local_c + 1;
      local_8 = local_8 + 0x50;
      *(undefined1 *)(iVar3 + 2 + *(int *)(param_1 + 0xc)) = uVar1;
      iVar3 = iVar3 + 0x20;
    } while (local_c < *(int *)(param_1 + 0x10));
  }
  FUN_008105d3();
  FUN_008103f3(param_4,param_5);
  return;
}


/* ---- FUN_00810905 @ 00810905 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00810905(int param_1,int param_2,undefined4 param_3,float param_4,float param_5)

{
  int iVar1;
  float *pfVar2;
  int extraout_ECX;
  int extraout_EDX;
  int iVar3;
  int extraout_EDX_00;
  float10 fVar4;
  float10 fVar5;
  int local_c;
  int local_8;
  
  FUN_00806ae3();
  FUN_00806ae3();
  *(int *)(param_1 + 0x20) = param_2;
  FUN_00806ae3();
  *(undefined4 *)(param_1 + 0x30) = 2;
  FUN_0080e811();
  *(undefined4 *)(*(int *)(param_1 + 0x2c) + 8) = 0;
  FUN_0080e811();
  *(undefined4 *)(*(int *)(param_1 + 0x2c) + 0x20) = 1;
  local_8 = 0;
  if (0 < param_2) {
    local_c = 0;
    do {
      FUN_0080ffdb();
      pfVar2 = (float *)(*(int *)(param_1 + 0x7c) + local_c);
      fVar4 = ((float10)_DAT_0081f37c * (float10)local_8) / (float10)param_2 + (float10)param_5;
      fVar5 = (float10)fsin(fVar4);
      *pfVar2 = (float)(fVar5 * (float10)param_4);
      fVar4 = (float10)fcos(fVar4);
      pfVar2[1] = (float)-(fVar4 * (float10)param_4);
      pfVar2[3] = 1.0;
      pfVar2[0x10] = (float)((float10)local_8 / (float10)param_2);
      pfVar2[0x13] = 1.0;
      iVar3 = (extraout_EDX + local_8 + -1) % param_2;
      FUN_0080e7e6();
      *(undefined4 *)(extraout_ECX + 0x14) = 0;
      local_c = local_c + 0x50;
      iVar1 = iVar3 * 2;
      *(int *)(extraout_ECX + 4) = iVar1;
      *(int *)(extraout_ECX + 0x10) = iVar1 + 1;
      iVar1 = local_8 + 1;
      *(int *)(extraout_ECX + 0x1c) = local_8;
      *(int *)(extraout_ECX + 8) = extraout_EDX_00 * 2 + 1;
      *(int *)(extraout_ECX + 0xc) = extraout_EDX_00 * 2;
      *(undefined4 *)(extraout_ECX + 0x18) = 1;
      *(int *)(extraout_ECX + 0x20) = iVar3;
      local_8 = iVar1;
    } while (iVar1 < param_2);
  }
  FUN_0081045c(param_3,0);
  return;
}


/* ---- FUN_00810a34 @ 00810a34 ---- */

void FUN_00810a34(uint param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int extraout_ECX;
  int extraout_ECX_00;
  int iVar4;
  int iVar5;
  int local_8;
  
  iVar1 = FUN_0080e966(param_1);
  iVar1 = *(int *)(iVar1 + 0x14);
  *(int *)(iVar1 * 0x20 + 8 + *(int *)(extraout_ECX + 0xc)) = iVar1;
  *(int *)(iVar1 * 0x20 + 4 + *(int *)(extraout_ECX + 0xc)) = iVar1;
  local_8 = (int)param_1 / 2;
  iVar3 = extraout_ECX;
  iVar4 = iVar1;
  uVar2 = param_1;
  do {
    *(int *)(*(int *)(iVar3 + 0x1c) + 0x1c + (local_8 * 0xc + (uVar2 & 1)) * 4) = iVar4;
    uVar2 = FUN_0080e9fd(uVar2);
    iVar3 = FUN_0080e966(uVar2);
    iVar3 = *(int *)(iVar3 + 0x14);
    local_8 = (int)uVar2 / 2;
    iVar5 = iVar4;
    if (((*(int *)(local_8 * 0x30 + 0x2c + *(int *)(extraout_ECX_00 + 0x1c)) != 0) &&
        (iVar5 = iVar3, iVar3 != iVar4)) && (iVar3 != iVar1)) {
      *(int *)(iVar4 * 0x20 + 4 + *(int *)(extraout_ECX_00 + 0xc)) = iVar3;
      *(int *)(iVar3 * 0x20 + 8 + *(int *)(extraout_ECX_00 + 0xc)) = iVar1;
      *(int *)(iVar3 * 0x20 + 4 + *(int *)(extraout_ECX_00 + 0xc)) = iVar1;
    }
    iVar3 = extraout_ECX_00;
    iVar4 = iVar5;
  } while (uVar2 != param_1);
  return;
}


/* ---- FUN_00810ae3 @ 00810ae3 ---- */

void __fastcall FUN_00810ae3(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < *(int *)(param_1 + 0x30)) {
    iVar1 = 0;
    do {
      if (*(char *)(iVar1 + 2 + *(int *)(param_1 + 0x2c)) != '\0') {
        *(undefined4 *)(iVar1 + 4 + *(int *)(param_1 + 0x2c)) = 0;
        *(undefined1 *)(iVar1 + 2 + *(int *)(param_1 + 0x2c)) = 0;
        *(undefined1 *)(iVar1 + *(int *)(param_1 + 0x2c)) = 0;
      }
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 0x18;
    } while (iVar2 < *(int *)(param_1 + 0x30));
  }
  return;
}


/* ---- FUN_00810b16 @ 00810b16 ---- */

void __thiscall FUN_00810b16(int param_1,int *param_2)

{
  uint *puVar1;
  int *piVar2;
  short *psVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  short *psVar12;
  undefined4 *puVar13;
  float10 fVar14;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  float local_40;
  undefined4 local_3c;
  int local_38;
  short *local_34;
  undefined4 local_30;
  undefined4 *local_2c;
  uint *local_28;
  uint local_24;
  int local_20;
  uint local_1c;
  uint local_18;
  uint *local_14;
  int local_10;
  short *local_c;
  uint local_8;
  
  piVar2 = param_2;
  local_20 = param_2[1];
  local_38 = param_1;
  if (local_20 == 7) {
    iVar4 = 1;
    param_2 = (int *)0x0;
    if (0 < *(int *)(param_1 + 0x30)) {
      iVar11 = 0;
      do {
        iVar9 = *(int *)(param_1 + 0x2c) + iVar11;
        if ((*(int *)(iVar9 + 4) == *piVar2) && (*(char *)(iVar9 + 3) != '\0')) {
          *(int *)(iVar9 + 0xc) = iVar4;
          iVar4 = iVar4 + 1;
        }
        else {
          *(undefined4 *)(iVar9 + 0xc) = 0;
        }
        param_2 = (int *)((int)param_2 + 1);
        iVar11 = iVar11 + 0x18;
      } while ((int)param_2 < *(int *)(param_1 + 0x30));
    }
    piVar2[0x83] = iVar4;
    puVar5 = (undefined4 *)operator_new(iVar4 << 4);
    piVar2[0x84] = (int)puVar5;
    *puVar5 = 0;
    puVar5[1] = 0;
    param_2 = (int *)0x0;
    puVar5[2] = 0;
    puVar5[3] = 0;
    if (0 < *(int *)(param_1 + 0x30)) {
      local_24 = 0x10;
      local_18 = 0;
      do {
        if (*(int *)(*(int *)(param_1 + 0x2c) + 0xc + local_18) != 0) {
          FUN_008106b7(&local_4c,param_2);
          iVar4 = FUN_0080e9a6(*(undefined4 *)(*(int *)(param_1 + 0x2c) + 8 + local_18));
          fVar14 = (float10)FUN_00805fc1(iVar4 * 0x50 + *(int *)(param_1 + 0x7c));
          puVar5 = (undefined4 *)(piVar2[0x84] + local_24);
          local_24 = local_24 + 0x10;
          local_40 = (float)-fVar14;
          *puVar5 = local_4c;
          puVar5[1] = uStack_48;
          puVar5[2] = uStack_44;
          puVar5[3] = local_40;
          param_1 = local_38;
        }
        param_2 = (int *)((int)param_2 + 1);
        local_18 = local_18 + 0x18;
      } while ((int)param_2 < *(int *)(param_1 + 0x30));
    }
  }
  piVar2[2] = 0;
  iVar4 = 0;
  local_10 = 0;
  if (0 < *(int *)(param_1 + 0x20)) {
    iVar11 = 0;
    do {
      *(undefined1 *)(*(int *)(param_1 + 0x1c) + 2 + iVar11) = 0;
      *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0x24 + iVar11) = 0xffffffff;
      iVar4 = iVar4 + 1;
      iVar11 = iVar11 + 0x30;
    } while (iVar4 < *(int *)(param_1 + 0x20));
  }
  if (0 < *(int *)(param_1 + 0x30)) {
    do {
      if (0xf < piVar2[2]) {
        return;
      }
      local_1c = 0;
      local_18 = 0;
      local_c = (short *)0x0;
      local_24 = 0;
      iVar11 = 0;
      psVar12 = (short *)&DAT_0138a128;
      iVar4 = 0;
      local_28 = &DAT_0130a128;
      local_2c = &DAT_012da128;
      local_34 = (short *)&DAT_0138a128;
      if (0 < *(int *)(param_1 + 0x10)) {
        do {
          *(undefined1 *)(*(int *)(param_1 + 0xc) + 2 + iVar11) = 0;
          iVar4 = iVar4 + 1;
          iVar11 = iVar11 + 0x20;
        } while (iVar4 < *(int *)(param_1 + 0x10));
      }
      if (local_10 < *(int *)(param_1 + 0x30)) {
        local_14 = (uint *)(local_10 * 0x18);
        do {
          if (((0x7eff < (int)local_18) || (0x16fff < (int)((int)local_c * 6 + local_1c))) ||
             (0x3f7f < (int)local_c)) break;
          if (((local_20 != 7) || (*(char *)(*(int *)(param_1 + 0x2c) + 3 + (int)local_14) != '\0'))
             && (*(int *)((int)local_14 + *(int *)(param_1 + 0x2c) + 4) == *piVar2)) {
            param_2 = *(int **)((int)local_14 + *(int *)(param_1 + 0x2c) + 8);
            local_8 = (uint)param_2;
            do {
              iVar4 = FUN_0080e966(param_2);
              if (*(char *)(iVar4 + 2) == '\0') {
                *(uint *)(iVar4 + 0x10) = local_18;
                *(undefined1 *)(iVar4 + 2) = 1;
                local_18 = local_18 + 1;
                *local_28 = iVar4 - *(int *)(param_1 + 0xc) >> 5;
                local_28 = local_28 + 1;
              }
              param_2 = (int *)FUN_0080e9c3(param_2);
            } while (param_2 != (int *)local_8);
            psVar3 = local_34;
            if (local_20 == 7) {
              param_2 = *(int **)(*(int *)(param_1 + 0x2c) + 8 + (int)local_14);
              local_8 = (uint)param_2;
              do {
                iVar4 = ((uint)param_2 >> 1) * 0x30 + *(int *)(param_1 + 0x1c);
                if (*(char *)(iVar4 + 2) == '\0') {
                  *(undefined1 *)(iVar4 + 2) = 1;
                  *(int *)(iVar4 + 0x24) = piVar2[2];
                  *(int *)(iVar4 + 0x28) = (int)local_c * 2;
                  iVar4 = FUN_0080e966(param_2);
                  *psVar12 = *(short *)(iVar4 + 0x10) * 2;
                  uVar6 = FUN_0080e9c3(param_2);
                  iVar4 = FUN_0080e966(uVar6);
                  psVar12[1] = *(short *)(iVar4 + 0x10) * 2;
                  *(int **)(psVar12 + 2) = param_2;
                  iVar4 = FUN_0080e91e(param_2);
                  *(int *)(psVar12 + 4) = *(int *)(iVar4 + 0xc) << 2;
                  iVar4 = FUN_0080e91e((uint)param_2 ^ 1);
                  *(int *)(psVar12 + 6) = *(int *)(iVar4 + 0xc) << 2;
                  psVar12 = psVar12 + 8;
                  local_c = (short *)((int)local_c + 1);
                }
                param_2 = (int *)FUN_0080e9c3(param_2);
                psVar3 = psVar12;
              } while (param_2 != (int *)local_8);
            }
            local_34 = psVar3;
            uVar6 = *(undefined4 *)(*(int *)(param_1 + 0x2c) + 8 + (int)local_14);
            iVar4 = FUN_0080e966(uVar6);
            local_3c = *(undefined4 *)(iVar4 + 0x10);
            uVar7 = FUN_0080e9c3(uVar6);
            local_8 = uVar7;
            iVar4 = FUN_0080e966(uVar7);
            local_30 = *(undefined4 *)(iVar4 + 0x10);
            uVar8 = FUN_0080e9c3(uVar7);
            iVar4 = FUN_0080e966(uVar8);
            uVar6 = *(undefined4 *)(iVar4 + 0x10);
            param_2 = (int *)FUN_0080e9c3(uVar8);
            do {
              if (local_20 == 7) {
                (&DAT_012ba128)[local_24] =
                     *(int *)(*(int *)(param_1 + 0x2c) + 0xc + (int)local_14) << 2;
                local_24 = local_24 + 1;
              }
              local_1c = local_1c + 3;
              *(undefined2 *)local_2c = (undefined2)local_3c;
              *(undefined2 *)((int)local_2c + 2) = (undefined2)local_30;
              *(short *)(local_2c + 1) = (short)uVar6;
              local_2c = (undefined4 *)((int)local_2c + 6);
              local_30 = uVar6;
              iVar4 = FUN_0080e966(param_2);
              uVar6 = *(undefined4 *)(iVar4 + 0x10);
              param_2 = (int *)FUN_0080e9c3(param_2);
              psVar12 = local_34;
            } while (param_2 != (int *)local_8);
          }
          local_10 = local_10 + 1;
          local_14 = local_14 + 6;
        } while (local_10 < *(int *)(param_1 + 0x30));
        if (0 < (int)local_c) {
          local_14 = &DAT_0138a12c;
          local_34 = local_c;
          do {
            local_8 = *local_14;
            param_2 = (int *)0x0;
            local_28 = local_14;
            do {
              uVar7 = (uint)param_2 ^ local_8;
              iVar4 = *(int *)(param_1 + 0x1c);
              do {
                uVar7 = FUN_0080ea1d(uVar7);
              } while (*(int *)((uVar7 >> 1) * 0x30 + 0x24 + iVar4) != piVar2[2]);
              param_2 = (int *)((int)param_2 + 1);
              puVar1 = (uint *)((int)local_28 + 2);
              *(ushort *)local_28 =
                   ((byte)~(byte)uVar7 & 1) + *(short *)((uVar7 >> 1) * 0x30 + 0x28 + iVar4);
              local_28 = puVar1;
            } while ((int)param_2 < 2);
            local_14 = local_14 + 4;
            local_34 = (short *)((int)local_34 + -1);
          } while (local_34 != (short *)0x0);
        }
        uVar7 = local_1c;
        if (0 < (int)local_18) {
          uVar10 = local_1c * 2;
          piVar2[piVar2[2] + 0x13] = local_1c;
          iVar4 = operator_new(uVar10);
          psVar12 = local_c;
          piVar2[piVar2[2] + 0x43] = iVar4;
          puVar5 = &DAT_012da128;
          puVar13 = (undefined4 *)piVar2[piVar2[2] + 0x43];
          for (uVar7 = (uVar7 & 0x7fffffff) >> 1; uVar7 != 0; uVar7 = uVar7 - 1) {
            *puVar13 = *puVar5;
            puVar5 = puVar5 + 1;
            puVar13 = puVar13 + 1;
          }
          for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
            *(undefined1 *)puVar13 = *(undefined1 *)puVar5;
            puVar5 = (undefined4 *)((int)puVar5 + 1);
            puVar13 = (undefined4 *)((int)puVar13 + 1);
          }
          piVar2[piVar2[2] + 0x33] = (int)local_c;
          if (local_c != (short *)0x0) {
            iVar4 = operator_new((int)local_c << 4);
            piVar2[piVar2[2] + 0x73] = iVar4;
            puVar5 = &DAT_0138a128;
            puVar13 = (undefined4 *)piVar2[piVar2[2] + 0x73];
            for (iVar4 = ((uint)psVar12 & 0xfffffff) << 2; iVar4 != 0; iVar4 = iVar4 + -1) {
              *puVar13 = *puVar5;
              puVar5 = puVar5 + 1;
              puVar13 = puVar13 + 1;
            }
            for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
              *(undefined1 *)puVar13 = *(undefined1 *)puVar5;
              puVar5 = (undefined4 *)((int)puVar5 + 1);
              puVar13 = (undefined4 *)((int)puVar13 + 1);
            }
          }
          uVar7 = local_24;
          if (local_20 == 7) {
            iVar4 = operator_new(local_24 << 2);
            piVar2[piVar2[2] + 99] = iVar4;
            puVar5 = &DAT_012ba128;
            puVar13 = (undefined4 *)piVar2[piVar2[2] + 99];
            for (uVar7 = uVar7 & 0x3fffffff; uVar7 != 0; uVar7 = uVar7 - 1) {
              *puVar13 = *puVar5;
              puVar5 = puVar5 + 1;
              puVar13 = puVar13 + 1;
            }
            for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
              *(undefined1 *)puVar13 = *(undefined1 *)puVar5;
              puVar5 = (undefined4 *)((int)puVar5 + 1);
              puVar13 = (undefined4 *)((int)puVar13 + 1);
            }
          }
          uVar7 = local_18;
          piVar2[piVar2[2] + 0x23] = local_18;
          iVar4 = operator_new(local_18 << 2);
          piVar2[piVar2[2] + 0x53] = iVar4;
          puVar5 = &DAT_0130a128;
          puVar13 = (undefined4 *)piVar2[piVar2[2] + 0x53];
          for (uVar7 = uVar7 & 0x3fffffff; uVar7 != 0; uVar7 = uVar7 - 1) {
            *puVar13 = *puVar5;
            puVar5 = puVar5 + 1;
            puVar13 = puVar13 + 1;
          }
          for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
            *(undefined1 *)puVar13 = *(undefined1 *)puVar5;
            puVar5 = (undefined4 *)((int)puVar5 + 1);
            puVar13 = (undefined4 *)((int)puVar13 + 1);
          }
          piVar2[piVar2[2] + 3] = -1;
          piVar2[2] = piVar2[2] + 1;
          param_1 = local_38;
        }
      }
    } while (local_10 < *(int *)(param_1 + 0x30));
  }
  return;
}


/* ---- FUN_0081104f @ 0081104f ---- */

int __thiscall FUN_0081104f(int param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  if (0 < *(int *)(param_1 + 0x50)) {
    piVar2 = *(int **)(param_1 + 0x4c);
    do {
      if ((piVar2[1] == param_2) && (*piVar2 == param_3)) {
        return iVar1;
      }
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 0x85;
    } while (iVar1 < *(int *)(param_1 + 0x50));
  }
  return -1;
}


/* ---- FUN_00811081 @ 00811081 ---- */

void __fastcall FUN_00811081(int param_1)

{
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x88) = 0;
  return;
}


/* ---- FUN_0081108f @ 0081108f ---- */

uint __fastcall FUN_0081108f(int *param_1,int param_2)

{
  undefined4 *puVar1;
  uint in_EAX;
  int iVar2;
  int *piVar3;
  
  puVar1 = (undefined4 *)*param_1;
  if (1 < (int)puVar1[2]) {
    iVar2 = operator_new(0xc4);
    if (iVar2 == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)FUN_0080fcbd();
    }
    *param_1 = (int)piVar3;
    in_EAX = (**(code **)(*piVar3 + 8))(puVar1);
    piVar3 = puVar1 + 2;
    *piVar3 = *piVar3 + -1;
    if (*piVar3 == 0) {
      in_EAX = (**(code **)*puVar1)(1);
    }
  }
  if (-1 < param_2) {
    if (param_2 == 0) {
      in_EAX = FUN_00810366(1,7);
    }
    else {
      in_EAX = FUN_008102dc(param_2);
    }
  }
  return in_EAX & 0xffffff00;
}


/* ---- Mesh_SelectCube @ 008110ee ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 Mesh_SelectCube(undefined4 param_1,undefined4 param_2,uint param_3)

{
  float in_stack_0000001c;
  float in_stack_00000020;
  float in_stack_00000024;
  
  FUN_0081108f();
  in_stack_0000001c = in_stack_0000001c * _DAT_0081f2ac;
  in_stack_00000020 = in_stack_00000020 * _DAT_0081f2ac;
  in_stack_00000024 = in_stack_00000024 * _DAT_0081f2ac;
  FUN_00810873(&stack0x00000010,&stack0x0000001c,0,0);
  FUN_008103f3(param_2,param_3 & 3);
  return param_1;
}


/* ---- FUN_0081114b @ 0081114b ---- */

undefined4 FUN_0081114b(void)

{
  undefined4 extraout_ECX;
  
  FUN_0081108f();
  FUN_00810ae3();
  return extraout_ECX;
}


/* ---- FUN_0081116a @ 0081116a ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float * __fastcall FUN_0081116a(int param_1,float *param_2,float param_3)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  undefined1 local_40 [16];
  undefined1 local_30 [16];
  int local_20;
  uint local_1c;
  float local_18;
  int local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_10 = *param_2;
  local_20 = (int)param_2[2] * 0x40 + (int)param_3;
  iVar4 = (int)param_2[3] * 0x40 + (int)param_3;
  local_18 = param_2[4];
  pfVar3 = param_2 + 5;
  local_c = *(float *)(iVar4 + 0x10);
  iVar2 = (int)param_2[1] * 0x40 + (int)param_3;
  param_3 = *(float *)(iVar4 + 0x14);
  local_14 = param_1;
  if ((((uint)local_18 & 2) != 0) && (local_10 != 0.0)) {
    fVar5 = (float10)FUN_00805fc1(iVar4);
    param_3 = (float)fVar5;
    local_8 = 1.4013e-45;
    local_c = param_3;
    if (1 < (uint)local_10) {
      do {
        fVar5 = (float10)FUN_00805fc1(iVar4);
        if (fVar5 <= (float10)local_c) {
          local_c = (float)fVar5;
        }
        if ((float10)param_3 <= fVar5) {
          param_3 = (float)fVar5;
        }
        local_8 = (float)((int)local_8 + 1);
      } while ((uint)local_8 < (uint)local_10);
    }
  }
  fVar1 = _DAT_0081f2bc / (param_3 - local_c);
  if (local_10 != 0.0) {
    local_1c = (uint)local_18 & 5;
    local_18 = local_10;
    do {
      local_10 = (float)((int)*pfVar3 * 0x10 + *(int *)(local_14 + 0x7c));
      pfVar3 = pfVar3 + 1;
      fVar5 = (float10)FUN_00805fc1(iVar4);
      fVar5 = (fVar5 - (float10)local_c) * (float10)fVar1;
      if (fVar5 < (float10)_DAT_0081f2bc) {
        if (fVar5 < (float10)_DAT_0081f374 != (fVar5 == (float10)_DAT_0081f374)) {
          fVar5 = (float10)0;
        }
      }
      else {
        fVar5 = (float10)1;
      }
      if (local_1c == 1) {
        fVar6 = (float10)_DAT_0081f368 - (fVar5 + fVar5);
LAB_008112d4:
        fVar5 = fVar6 * fVar5 * fVar5;
      }
      else if (local_1c == 4) {
        fVar5 = (float10)_DAT_0081f358 -
                (ABS(fVar5 - (float10)_DAT_0081f2ac) + ABS(fVar5 - (float10)_DAT_0081f2ac));
      }
      else if (local_1c == 5) {
        fVar6 = ((float10)_DAT_0081f150 * fVar5 - (float10)_DAT_0081fcb4) * fVar5 +
                (float10)_DAT_0081f150;
        goto LAB_008112d4;
      }
      local_8 = (float)fVar5;
      FUN_00806305(iVar2,local_10);
      FUN_00806305(local_20,local_10);
      FUN_00805957(local_40,local_30,local_8);
      local_18 = (float)((int)local_18 - 1);
    } while (local_18 != 0.0);
  }
  return pfVar3;
}


/* ---- Mesh_Bend2 @ 00811320 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Mesh_Bend2(int param_1,float param_2,float param_3,float param_4)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float in_stack_00000020;
  float in_stack_00000024;
  undefined4 local_98 [16];
  undefined4 local_58 [12];
  float local_28;
  float local_24;
  float local_20;
  float local_18;
  float local_14;
  float local_8;
  
  iVar1 = param_1;
  FUN_0081108f();
  FUN_00805b55(&stack0x00000014);
  local_28 = -param_2;
  local_24 = -param_3;
  local_20 = -param_4;
  puVar3 = local_58;
  puVar4 = local_98;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  FUN_008064d6();
  iVar2 = 0;
  in_stack_00000024 = in_stack_00000024 * _DAT_0081f37c;
  if (0 < *(int *)(param_1 + 0x10)) {
    param_1 = 0;
    local_8 = 1.0 / in_stack_00000020;
    do {
      FUN_00806305(local_58,*(int *)(iVar1 + 0x7c) + param_1);
      fVar5 = (float10)local_14;
      fVar6 = fVar5;
      if ((float10)_DAT_0081f374 <= fVar5) {
        if ((float10)in_stack_00000020 <= fVar5) {
          fVar6 = (float10)in_stack_00000020;
        }
        fVar6 = fVar5 - fVar6;
      }
      fVar5 = fVar5 * (float10)local_8;
      if (fVar5 < (float10)_DAT_0081f2bc) {
        if (fVar5 < (float10)_DAT_0081f374 != (fVar5 == (float10)_DAT_0081f374)) {
          fVar5 = (float10)0;
        }
      }
      else {
        fVar5 = (float10)1;
      }
      fVar7 = (float10)fsin(fVar5 * (float10)in_stack_00000024);
      fVar5 = (float10)fcos(fVar5 * (float10)in_stack_00000024);
      fVar8 = (float10)local_18;
      local_18 = (float)((float10)local_18 * fVar5 - (float10)(float)fVar7 * fVar6);
      local_14 = (float)(fVar5 * fVar6 + fVar8 * (float10)(float)fVar7);
      FUN_00806305(local_98,&local_18);
      param_1 = param_1 + 0x50;
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)(iVar1 + 0x10));
  }
  *(undefined1 *)(iVar1 + 0xa0) = 0;
  return iVar1;
}


/* ---- Mesh_LightSlot @ 00811462 ---- */

int Mesh_LightSlot(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  undefined4 param_5,float param_6)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = operator_new(0xc4);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_0080fcbd();
  }
  FUN_0080fe61(0x2f,1);
  FUN_0080ffdb();
  puVar3 = (undefined4 *)FUN_00806b54();
  *puVar3 = 0;
  puVar3 = *(undefined4 **)(iVar2 + 0x7c);
  puVar3[3] = 0x3f800000;
  *puVar3 = param_1;
  puVar3[1] = param_2;
  puVar3[2] = param_3;
  FUN_00805cf1(param_4);
  FUN_00805e6e(param_5);
  iVar1 = *(int *)(iVar2 + 0x7c);
  *(float *)(iVar1 + 0x20) = param_6;
  *(float *)(iVar1 + 0x24) = param_6 * param_6;
  *(float *)(iVar1 + 0x28) = 1.0 / param_6;
  *(undefined4 *)(iVar1 + 0x2c) = 0;
  return iVar2;
}


/* ---- Mesh_ShadowEnable @ 008114ff ---- */

void Mesh_ShadowEnable(int param_1,undefined1 param_2)

{
  int iVar1;
  int iVar2;
  
  FUN_0081108f();
  iVar2 = 0;
  if (0 < *(int *)(param_1 + 0x30)) {
    iVar1 = 0;
    do {
      *(undefined1 *)(iVar1 + 3 + *(int *)(param_1 + 0x2c)) = param_2;
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 0x18;
    } while (iVar2 < *(int *)(param_1 + 0x30));
  }
  return;
}


/* ---- FUN_00811536 @ 00811536 ---- */

undefined4 __thiscall FUN_00811536(undefined4 param_1,byte param_2)

{
  FUN_0080fda5();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


/* ---- FUN_00811555 @ 00811555 ---- */

void __thiscall FUN_00811555(int param_1,int param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 1;
  if (1 < *(int *)(param_1 + 0x40)) {
    iVar3 = 0x4c;
    do {
      puVar2 = *(undefined4 **)(iVar3 + *(int *)(param_1 + 0x3c));
      piVar1 = puVar2 + 2;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        (**(code **)*puVar2)(1);
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x4c;
    } while (iVar4 < *(int *)(param_1 + 0x40));
  }
  FUN_00806b0e();
  FUN_00806b0e();
  FUN_00806b0e();
  FUN_00806b0e();
  FUN_00806b0e();
  FUN_00806b0e();
  iVar4 = 1;
  if (1 < *(int *)(param_1 + 0x40)) {
    iVar3 = 0x4c;
    do {
      piVar1 = (int *)(*(int *)(iVar3 + *(int *)(param_1 + 0x3c)) + 8);
      *piVar1 = *piVar1 + 1;
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x4c;
    } while (iVar4 < *(int *)(param_1 + 0x40));
  }
  *(undefined4 *)(param_1 + 0x88) = 0;
  FUN_0080fe61(0x2f,*(undefined4 *)(param_2 + 0x84));
  FUN_0080574a(*(int *)(param_2 + 0x80) * 0x14);
  *(int *)(param_1 + 0x80) = *(int *)(param_2 + 0x80);
  *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_2 + 0x8c);
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_2 + 0x9c);
  *(undefined1 *)(param_1 + 0xa0) = *(undefined1 *)(param_2 + 0xa0);
  return;
}


/* ---- FUN_00811645 @ 00811645 ---- */

void FUN_00811645(int param_1)

{
  DAT_00aba10c = param_1 + -0xaba118 >> 2;
  FUN_0080ff59();
  return;
}


/* ---- FUN_00811661 @ 00811661 ---- */

void __fastcall FUN_00811661(int param_1)

{
  undefined4 uVar1;
  
  FUN_00806a7e();
  FUN_00806a7e();
  FUN_00806a7e();
  FUN_00806a7e();
  FUN_00806a7e();
  FUN_00806a7e();
  FUN_00806a7e();
  if (*(int *)(param_1 + 0x80) < *(int *)(param_1 + 0x84)) {
    uVar1 = operator_new(*(int *)(param_1 + 0x80) * 0x50);
    FUN_0080574a(*(int *)(param_1 + 0x80) * 0x14);
    operator_delete(*(undefined4 *)(param_1 + 0x7c));
    *(undefined4 *)(param_1 + 0x7c) = uVar1;
    *(undefined4 *)(param_1 + 0x84) = *(undefined4 *)(param_1 + 0x80);
  }
  return;
}


/* ---- FUN_008116fb @ 008116fb ---- */

void __thiscall
FUN_008116fb(int param_1,uint param_2,uint param_3,undefined4 *param_4,undefined4 *param_5,
            uint param_6,undefined4 param_7,undefined4 *param_8,undefined4 *param_9)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  int extraout_ECX;
  int iVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  uint local_28;
  uint local_20;
  uint local_10;
  uint local_c;
  
  iVar2 = *(int *)(param_1 + 0x20);
  FUN_00806ae3();
  *(int *)(param_1 + 0x20) = iVar2 + 1;
  uVar7 = *param_4;
  FUN_0080e78a(param_6 >> 0x10,1,param_7);
  uVar8 = param_2 ^ 1;
  *(undefined4 *)(extraout_ECX + 8) = uVar7;
  *(undefined4 *)(extraout_ECX + 4) = uVar7;
  local_20 = FUN_0080e9e0(param_3);
  local_c = FUN_0080e9c3(uVar8);
  uVar5 = FUN_0080e9a6(local_c);
  local_10 = 0;
  if (local_c == param_3) {
    local_c = iVar2 * 2;
    local_20 = local_c + 1;
  }
  else {
    iVar4 = *(int *)(param_1 + 0x1c);
    uVar6 = local_c;
    do {
      uVar3 = *(uint *)(((int)uVar6 / 2) * 0x30 + 0x2c + iVar4);
      if (uVar3 != 0) {
        local_10 = local_10 | uVar3;
        local_28 = uVar6;
      }
      uVar6 = FUN_0080ea1d(uVar6);
    } while (uVar6 != param_3);
  }
  iVar4 = *(int *)(param_1 + 0x1c);
  puVar1 = (undefined4 *)(iVar2 * 0x30 + iVar4);
  puVar10 = (undefined4 *)((param_2 >> 1) * 0x30 + iVar4);
  puVar11 = puVar1;
  for (iVar9 = 0xc; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar11 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar11 = puVar11 + 1;
  }
  puVar1[0xb] = local_10;
  FUN_0080e78a(param_6,1,param_7);
  puVar1[7] = uVar7;
  puVar1[8] = uVar5;
  uVar7 = FUN_0080e989(param_3);
  puVar1[5] = uVar7;
  uVar7 = FUN_0080e989(uVar8);
  puVar1[6] = uVar7;
  puVar1[2] = local_c;
  puVar1[9] = 0xffffffff;
  puVar1[10] = 0xffffffff;
  puVar1[1] = param_3;
  puVar1[3] = local_20;
  puVar1[4] = uVar8;
  iVar2 = iVar2 * 2;
  *(int *)(iVar4 + 4 + (((int)local_20 / 2) * 0xc + (local_20 & 1)) * 4) = iVar2;
  *(int *)(iVar4 + 0xc + (((int)param_3 / 2) * 0xc + (param_3 & 1)) * 4) = iVar2;
  *(int *)(iVar4 + 4 + (((int)uVar8 / 2) * 0xc + (uVar8 & 1)) * 4) = iVar2 + 1;
  *(int *)(iVar4 + 0xc + (((int)local_c / 2) * 0xc + (local_c & 1)) * 4) = iVar2 + 1;
  if (local_10 == 0) {
    if (param_8 != (undefined4 *)0x0) {
      *param_8 = 0xffffffff;
    }
  }
  else {
    uVar8 = FUN_0080ea1d(local_28);
    uVar7 = FUN_0080e9a6(uVar8 ^ 1);
    uVar5 = FUN_00810010(uVar7);
    FUN_0080e78a(param_6 >> 0x10,1,param_7);
    *(undefined4 *)(iVar4 + 0x1c + (((int)local_28 / 2) * 0xc + (local_28 & 1)) * 4) = uVar5;
    if (param_8 != (undefined4 *)0x0) {
      *param_8 = uVar7;
      *param_9 = uVar5;
    }
  }
  FUN_00810a34(iVar2);
  FUN_00810a34(iVar2 + 1);
  uVar7 = FUN_0080e9a6(iVar2);
  *param_4 = uVar7;
  uVar7 = FUN_0080e9a6(local_c);
  *param_5 = uVar7;
  return;
}


/* ---- FUN_0081192e @ 0081192e ---- */

void __thiscall FUN_0081192e(int param_1,undefined4 param_2,int param_3,uint param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  undefined8 uVar8;
  
  iVar2 = *(int *)(&DAT_0081fc40 + param_3 * 4);
  uVar6 = *(uint *)(&DAT_0081fc40 + (param_4 & 0xf) * 4);
  if ((param_4 & 0x10) != 0) {
    uVar6 = uVar6 | 0x10;
  }
  piVar1 = (int *)FUN_0080e83c(FUN_0080eab3);
  piVar1[1] = iVar2;
  piVar1[2] = uVar6;
  uVar8 = FUN_0080e8a2(param_2);
  puVar4 = (undefined4 *)((ulonglong)uVar8 >> 0x20);
  *puVar4 = (int)uVar8;
  iVar3 = 0;
  piVar5 = puVar4 + 1;
  iVar2 = 0;
  if (0 < *(int *)(param_1 + 0x10)) {
    iVar7 = 0;
    do {
      if (*(char *)(*(int *)(param_1 + 0xc) + 2 + iVar3) != '\0') {
        *piVar5 = iVar7;
        piVar5 = piVar5 + 1;
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x20;
      iVar7 = iVar7 + 5;
    } while (iVar2 < *(int *)(param_1 + 0x10));
  }
  *piVar1 = ((int)piVar5 - (int)piVar1 >> 2) + -4;
  FUN_00811645(piVar5);
  return;
}


/* ---- FUN_008119c5 @ 008119c5 ---- */

void __thiscall FUN_008119c5(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int *piVar7;
  undefined8 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int local_20;
  int local_1c;
  int local_18;
  int *local_14;
  int local_10;
  uint local_c;
  uint local_8;
  
  piVar2 = (int *)FUN_0080e83c(FUN_0080ebc9);
  *piVar2 = 0;
  local_14 = piVar2;
  uVar8 = FUN_0080e8cf(0);
  local_8 = (uint)((ulonglong)uVar8 >> 0x20);
  piVar2[1] = (int)uVar8;
  local_10 = *(int *)(param_1 + 0x20) * 2;
  piVar2 = piVar2 + 2;
  piVar7 = piVar2;
  if ((int)local_8 < local_10) {
    do {
      iVar4 = (((int)local_8 / 2) * 0xc + (local_8 & 1)) * 4 + 0x24;
      *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x1c)) = 0xffffffff;
      cVar1 = FUN_00810297(local_8,param_4);
      uVar6 = local_8;
      piVar2 = piVar7;
      if (cVar1 != '\0') {
        *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x1c)) = 0;
        local_c = local_8;
        do {
          local_c = FUN_0080e9fd(local_c);
          cVar1 = FUN_00810297(local_c ^ 1,param_4);
        } while (cVar1 == '\0');
        uVar3 = FUN_0080e9a6(uVar6);
        iVar4 = FUN_00810010(uVar3);
        local_18 = iVar4;
        FUN_008116fb(local_c,local_8,&local_18,&local_c,param_2,param_3,&local_1c,&local_20);
        *piVar7 = iVar4 * 5;
        iVar4 = FUN_0080e9a6(local_8);
        piVar7[1] = iVar4 * 5;
        piVar7[2] = 5;
        piVar2 = piVar7 + 3;
        *local_14 = *local_14 + 1;
        if (local_1c != -1) {
          *piVar2 = local_20 * 5;
          piVar7[4] = local_1c * 5;
          piVar7[5] = 5;
          piVar2 = piVar7 + 6;
          *local_14 = *local_14 + 1;
        }
      }
      local_8 = local_8 + 1;
      piVar7 = piVar2;
    } while ((int)local_8 < local_10);
  }
  uVar6 = 0;
  if (0 < local_10) {
    do {
      if (*(int *)(*(int *)(param_1 + 0x1c) + 0x24 + (((int)uVar6 / 2) * 0xc + (uVar6 & 1)) * 4) ==
          0) {
        uVar10 = 0;
        uVar9 = 0;
        uVar3 = FUN_0080e9e0(uVar6);
        uVar5 = FUN_0080e9c3(uVar6);
        uVar5 = FUN_0080e9c3(uVar5);
        FUN_00810043(uVar5,uVar3,uVar9,uVar10);
        *(undefined1 *)(*(int *)(param_1 + 0x30) * 0x18 + -0x18 + *(int *)(param_1 + 0x2c)) = 0;
        *(undefined1 *)(*(int *)(param_1 + 0x30) * 0x18 + -0x16 + *(int *)(param_1 + 0x2c)) = 0;
        FUN_0080e78a(param_2 >> 8,1,param_3);
      }
      uVar6 = uVar6 + 1;
    } while ((int)uVar6 < local_10);
  }
  FUN_00811645(piVar2);
  return;
}


/* ---- FUN_00811b86 @ 00811b86 ---- */

void __thiscall FUN_00811b86(int param_1,uint param_2)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  byte *pbVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  undefined4 *puVar11;
  uint *puVar12;
  longlong lVar13;
  undefined8 uVar14;
  int **ppiVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  int local_26c [128];
  undefined4 local_6c [16];
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  int *local_1c;
  byte *local_18;
  uint local_14;
  int local_10;
  int *local_c;
  uint local_8;
  
  iVar9 = *(int *)(param_1 + 0x30);
  local_10 = iVar9;
  piVar2 = (int *)FUN_0080e83c(FUN_0080ec25);
  *piVar2 = 0;
  local_14 = *(uint *)(param_1 + 0x10);
  local_6c[0] = param_2;
  local_1c = piVar2;
  lVar13 = FUN_0080e8a2(local_6c);
  piVar2[1] = (int)lVar13;
  piVar2 = piVar2 + 2;
  iVar8 = 0;
  if (0xffffffff < lVar13) {
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + 0xc + *(int *)(param_1 + 0xc)) = 0xffffffff;
      *(int *)(iVar3 + 0x10 + *(int *)(param_1 + 0xc)) = iVar8;
      iVar8 = iVar8 + 1;
      iVar3 = iVar3 + 0x20;
    } while (iVar8 < (int)local_14);
  }
  if (0 < iVar9) {
    iVar9 = 0;
    do {
      *(undefined4 *)(iVar9 + 0xc + *(int *)(param_1 + 0x2c)) = 0xffffffff;
      *(undefined4 *)(iVar9 + 0x10 + *(int *)(param_1 + 0x2c)) = 0xffffffff;
      local_18 = *(byte **)(iVar9 + 8 + *(int *)(param_1 + 0x2c));
      local_8 = (uint)local_18;
      iVar8 = FUN_0080ffdb();
      *(int *)(iVar9 + 0x10 + *(int *)(param_1 + 0x2c)) = iVar8;
      *piVar2 = iVar8;
      *(undefined1 *)(*(int *)(param_1 + 0xc) + 2 + iVar8 * 0x20) =
           *(undefined1 *)(iVar9 + 2 + *(int *)(param_1 + 0x2c));
      *(undefined1 *)(iVar8 * 0x20 + *(int *)(param_1 + 0xc)) =
           *(undefined1 *)(iVar9 + *(int *)(param_1 + 0x2c));
      piVar2 = piVar2 + 1;
      do {
        piVar4 = piVar2;
        iVar8 = FUN_0080e9a6(local_8);
        *piVar4 = iVar8;
        local_c = (int *)(iVar8 * 0x20);
        piVar2 = piVar4 + 1;
        if (*(int *)(*(int *)(param_1 + 0xc) + 0x14 + (int)local_c) == iVar8) {
          local_20 = FUN_00810010(iVar8);
          *(uint *)(*(int *)(param_1 + 0xc) + 0xc + (int)local_c) = local_8;
          *(int *)(*(int *)(param_1 + 0xc) + 0x10 + (int)local_c) = iVar8;
          *(int *)(*(int *)(param_1 + 0xc) + 0x14 + (int)local_c) = local_20;
          *(int *)(local_20 * 0x20 + 0x10 + *(int *)(param_1 + 0xc)) = iVar8;
        }
        local_8 = FUN_0080e9c3(local_8);
      } while ((byte *)local_8 != local_18);
      *(byte *)((int)piVar4 + 3) = *(byte *)((int)piVar4 + 3) | 0x80;
      *local_1c = *local_1c + 1;
      iVar9 = iVar9 + 0x18;
      local_10 = local_10 + -1;
    } while (local_10 != 0);
  }
  *piVar2 = 0;
  piVar4 = piVar2 + 1;
  param_2 = 0;
  if (0 < (int)local_14) {
    local_10 = 0;
    local_1c = piVar2;
    do {
      iVar9 = *(int *)(param_1 + 0xc) + local_10;
      local_20 = *(int *)(iVar9 + 0x14);
      if (local_20 != param_2) {
        local_18 = *(byte **)(iVar9 + 0xc);
        if (local_18 != (byte *)0xffffffff) {
          uVar10 = 0;
          local_c = (int *)0x0;
          local_8 = (uint)local_18;
          do {
            iVar9 = FUN_0080e9a6(local_8 ^ 1);
            uVar1 = local_8;
            local_26c[uVar10] = iVar9;
            iVar9 = FUN_0080e91e(uVar1);
            uVar1 = local_8;
            local_26c[uVar10 + 1] = *(int *)(iVar9 + 0x10);
            uVar10 = uVar10 + 2;
            iVar9 = FUN_0080e9a6(uVar1);
            if (iVar9 == param_2) {
              local_c = (int *)((uint)local_c |
                               *(uint *)(((int)local_8 / 2) * 0x30 + 0x2c + *(int *)(param_1 + 0x1c)
                                        ));
            }
            local_8 = FUN_0080e9fd(local_8);
          } while ((byte *)local_8 != local_18);
          *piVar4 = local_20;
          local_18 = (byte *)uVar10;
          iVar9 = FUN_0080eec6(local_c,0x2f);
          piVar4[1] = iVar9;
          piVar4[2] = uVar10;
          local_c = piVar4 + 3;
          if (0 < (int)uVar10) {
            piVar2 = local_26c;
            piVar4 = local_c;
            for (; uVar10 != 0; uVar10 = uVar10 - 1) {
              *piVar4 = *piVar2;
              piVar2 = piVar2 + 1;
              piVar4 = piVar4 + 1;
            }
            local_c = local_c + (int)local_18;
          }
          *local_c = param_2;
          piVar4 = local_c + 1;
          *local_1c = *local_1c + 1;
        }
      }
      param_2 = param_2 + 1;
      local_10 = local_10 + 0x20;
    } while ((int)param_2 < (int)local_14);
  }
  *piVar4 = 0;
  param_2 = 0;
  local_24 = *(int *)(param_1 + 0x20) * 2;
  piVar2 = piVar4 + 1;
  local_1c = piVar4;
  if (0 < local_24) {
    do {
      piVar4 = (int *)FUN_0080ffdb();
      local_c = piVar4;
      uVar5 = FUN_0080ea3c(param_2,2);
      local_18 = (byte *)FUN_0080e966(uVar5);
      pbVar6 = (byte *)FUN_0080e966(param_2);
      *(byte *)((int)piVar4 * 0x20 + *(int *)(param_1 + 0xc)) = *local_18 | *pbVar6;
      uVar19 = 0;
      uVar18 = 0;
      uVar17 = 0;
      uVar16 = 0x100000;
      piVar4 = &local_10;
      ppiVar15 = &local_c;
      uVar10 = param_2 ^ 1;
      local_14 = uVar10;
      uVar5 = FUN_0080ea1d(uVar10);
      uVar7 = FUN_0080e9fd(uVar10);
      FUN_008116fb(uVar7,uVar5,ppiVar15,piVar4,uVar16,uVar17,uVar18,uVar19);
      uVar5 = FUN_0080e9e0(uVar10);
      iVar9 = FUN_0080e966(uVar5);
      local_28 = *(undefined4 *)(iVar9 + 0x10);
      uVar5 = FUN_0080e9c3(uVar10);
      iVar9 = FUN_0080e966(uVar5);
      local_2c = *(undefined4 *)(iVar9 + 0x10);
      iVar9 = FUN_0080e966(param_2);
      uVar5 = *(undefined4 *)(iVar9 + 0x10);
      uVar7 = FUN_0080e9c3(param_2);
      uVar7 = FUN_0080e9c3(uVar7);
      iVar9 = FUN_0080e966(uVar7);
      local_18 = *(byte **)(iVar9 + 0x10);
      local_8 = *(uint *)(((int)param_2 / 2) * 0x30 + 0x2c + *(int *)(param_1 + 0x1c));
      *piVar2 = (int)local_c;
      uVar14 = FUN_0080eec6(~local_8,0x2f);
      iVar9 = (int)((ulonglong)uVar14 >> 0x20);
      local_20 = (int)uVar14;
      piVar2[1] = local_20;
      puVar11 = (undefined4 *)((int)(piVar2 + 1) + iVar9);
      *puVar11 = uVar5;
      puVar12 = (uint *)((int)puVar11 + iVar9);
      *puVar12 = (uint)local_18;
      puVar11 = (undefined4 *)((int)puVar12 + iVar9);
      iVar9 = FUN_0080e91e(param_2);
      *puVar11 = *(undefined4 *)(iVar9 + 0x10);
      iVar9 = FUN_0080e91e(local_14);
      piVar4 = local_1c;
      puVar11[1] = *(undefined4 *)(iVar9 + 0x10);
      piVar2 = puVar11 + 2;
      *local_1c = *local_1c + 1;
      if (local_8 != 0) {
        *piVar2 = local_10;
        puVar11[3] = local_20;
        puVar11[4] = local_28;
        puVar11[5] = local_2c;
        iVar9 = FUN_0080e91e(param_2);
        puVar11[6] = *(undefined4 *)(iVar9 + 0x10);
        iVar9 = FUN_0080e91e(local_14);
        puVar11[7] = *(undefined4 *)(iVar9 + 0x10);
        piVar2 = puVar11 + 8;
        *piVar4 = *piVar4 + 1;
      }
      iVar9 = FUN_0080e91e(param_2);
      *(uint *)(iVar9 + 0xc) = param_2;
      uVar5 = FUN_0080e9e0(local_14);
      iVar9 = FUN_0080e941(param_2);
      param_2 = param_2 + 2;
      *(undefined4 *)(iVar9 + 0xc) = uVar5;
    } while ((int)param_2 < local_24);
  }
  if (0 < (int)*(int **)(param_1 + 0x30)) {
    local_14 = 0;
    local_1c = *(int **)(param_1 + 0x30);
    do {
      param_2 = 0;
      iVar9 = *(int *)(param_1 + 0x2c) + local_14;
      iVar8 = *(int *)(iVar9 + 0xc);
      do {
        iVar8 = FUN_0080e9c3(iVar8);
        iVar3 = param_2 + 1;
        local_26c[param_2] = iVar8;
        iVar8 = FUN_0080e9c3(iVar8);
        param_2 = iVar3;
      } while (*(int *)(iVar9 + 0xc) != iVar8);
      local_c = *(int **)(iVar9 + 0x10);
      uVar18 = 0;
      uVar17 = 0;
      uVar16 = 0;
      uVar7 = 0;
      piVar4 = &local_10;
      ppiVar15 = &local_c;
      iVar9 = local_26c[0];
      uVar5 = FUN_0080e9fd(local_26c[0]);
      FUN_008116fb(uVar5,iVar9,ppiVar15,piVar4,uVar7,uVar16,uVar17,uVar18);
      local_8 = 1;
      if (1 < iVar3) {
        do {
          iVar9 = local_26c[local_8];
          uVar16 = 0;
          uVar7 = 0;
          uVar5 = FUN_0080e9e0(iVar9);
          uVar5 = FUN_0080e9e0(uVar5);
          uVar5 = FUN_0080e9e0(uVar5);
          FUN_00810043(uVar5,iVar9,uVar7,uVar16);
          local_8 = local_8 + 1;
        } while ((int)local_8 < iVar3);
      }
      local_14 = local_14 + 0x18;
      local_1c = (int *)((int)local_1c + -1);
    } while (local_1c != (int *)0x0);
  }
  FUN_00811645(piVar2);
  FUN_008101da();
  return;
}


/* ---- FUN_00812049 @ 00812049 ---- */

void __thiscall FUN_00812049(int param_1,int param_2,uint param_3,undefined4 param_4,uint param_5)

{
  uint *puVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  uint local_10;
  uint local_c;
  uint local_8;
  
  piVar3 = (int *)FUN_0080e83c(FUN_0080ebc9);
  *piVar3 = 0;
  iVar4 = FUN_0080e8cf(0);
  piVar3[1] = iVar4;
  piVar9 = piVar3 + 2;
  local_8 = 0;
  if (0 < *(int *)(param_1 + 0x20) * 2) {
    do {
      if (param_2 == 0) {
        iVar4 = FUN_0080e91e(local_8);
        if ((*(char *)(iVar4 + 2) != '\0') &&
           (iVar4 = FUN_0080e941(local_8), *(char *)(iVar4 + 2) == '\0')) {
LAB_008120ca:
          iVar4 = ((int)local_8 / 2) * 0x30;
          if (*(int *)(*(int *)(param_1 + 0x1c) + 0x2c + iVar4) == 0) {
            local_10 = 0;
            do {
              local_c = local_10 ^ local_8;
              iVar5 = FUN_0080e9a6(local_c);
              uVar2 = *(undefined4 *)(*(int *)(param_1 + 0xc) + 8 + iVar5 * 0x20);
              uVar8 = 0;
              uVar6 = local_c;
              do {
                uVar8 = uVar8 | *(uint *)(((int)uVar6 / 2) * 0x30 + 0x2c + *(int *)(param_1 + 0x1c))
                ;
                uVar6 = FUN_0080e9fd(uVar6);
              } while (uVar6 != local_c);
              if (uVar8 != 0) {
                iVar7 = FUN_00810010(iVar5);
                FUN_0080e78a(param_3 >> 0x10,1,param_4);
                *(undefined4 *)(*(int *)(param_1 + 0xc) + 8 + iVar7 * 0x20) = uVar2;
                *(int *)(*(int *)(param_1 + 0xc) + 4 + iVar5 * 0x20) = iVar7;
                *piVar9 = iVar7 * 5;
                piVar9[1] = iVar5 * 5;
                piVar9[2] = 5;
                piVar9 = piVar9 + 3;
                *piVar3 = *piVar3 + 1;
                iVar5 = (int)local_c / 2;
                do {
                  *(int *)(*(int *)(param_1 + 0x1c) + 0x1c + (iVar5 * 0xc + (local_c & 1)) * 4) =
                       iVar7;
                  local_c = FUN_0080e9fd(local_c);
                  iVar5 = (int)local_c / 2;
                } while (*(int *)(iVar5 * 0x30 + 0x2c + *(int *)(param_1 + 0x1c)) == 0);
              }
              local_10 = local_10 + 1;
            } while ((int)local_10 < 2);
          }
          puVar1 = (uint *)(*(int *)(param_1 + 0x1c) + 0x2c + iVar4);
          *puVar1 = *puVar1 | param_5;
        }
      }
      else if (*(char *)(((int)local_8 / 2) * 0x30 + 2 + *(int *)(param_1 + 0x1c)) != '\0')
      goto LAB_008120ca;
      local_8 = local_8 + 1;
    } while ((int)local_8 < *(int *)(param_1 + 0x20) * 2);
  }
  FUN_00811645(piVar9);
  return;
}


/* ---- FUN_00812227 @ 00812227 ---- */

void FUN_00812227(int param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  int iVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  int local_10;
  int local_c;
  int local_8;
  
  uVar8 = (-(uint)(param_1 != 0) & 0xfffffffe) + 2;
  piVar2 = (int *)FUN_0080e83c(FUN_0080eeef);
  iVar5 = 0;
  *piVar2 = 0;
  iVar3 = 0;
  if (0 < *(int *)(extraout_ECX + 0x10)) {
    do {
      *(undefined4 *)(iVar5 + 0xc + *(int *)(extraout_ECX + 0xc)) = 0xffffffff;
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + 0x20;
    } while (iVar3 < *(int *)(extraout_ECX + 0x10));
  }
  iVar5 = 0;
  iVar3 = extraout_ECX;
  if (0 < *(int *)(extraout_ECX + 0x20) * 2) {
    do {
      iVar3 = FUN_0080e9a6(iVar5);
      *(int *)(iVar3 * 0x20 + 0xc + *(int *)(extraout_ECX_00 + 0xc)) = iVar5;
      iVar5 = iVar5 + 1;
      iVar3 = extraout_ECX_00;
    } while (iVar5 < *(int *)(extraout_ECX_00 + 0x20) * 2);
  }
  piVar2[1] = (int)param_2;
  piVar7 = piVar2 + 2;
  local_10 = 0;
  if (0 < *(int *)(iVar3 + 0x10)) {
    local_c = 0;
    local_8 = 0;
    do {
      iVar5 = *(int *)(local_8 + 0xc + *(int *)(iVar3 + 0xc));
      param_1 = iVar5;
      if (iVar5 != -1) {
        do {
          if ((*(uint *)((param_1 / 2) * 0x30 + 0x2c + *(int *)(iVar3 + 0x1c)) & uVar8) != 0) break;
          param_1 = FUN_0080ea1d(param_1);
          iVar3 = extraout_ECX_01;
        } while (param_1 != iVar5);
        iVar3 = param_1;
        param_2 = piVar7 + 1;
        iVar5 = 0;
        do {
          iVar6 = iVar5;
          piVar1 = param_2 + 1;
          iVar5 = FUN_0080e9a6(param_1);
          param_2 = param_2 + 2;
          *piVar1 = iVar5 * 0x50;
          uVar4 = FUN_0080e9c3(param_1);
          iVar5 = FUN_0080e9a6(uVar4);
          *param_2 = iVar5 * 0x50;
          param_1 = FUN_0080e9fd(param_1);
          if (param_1 == iVar3) break;
          iVar5 = iVar6 + 2;
        } while ((*(uint *)((param_1 / 2) * 0x30 + 0x2c + *(int *)(extraout_ECX_02 + 0x1c)) & uVar8)
                 == 0);
        uVar4 = FUN_0080ea1d(param_1);
        iVar3 = FUN_0080e9a6(uVar4);
        piVar7[iVar6 + 4] = iVar3 * 0x50;
        uVar4 = FUN_0080e9e0(uVar4);
        iVar3 = FUN_0080e9a6(uVar4);
        piVar7[iVar6 + 5] = iVar3 * 0x50;
        *piVar2 = *piVar2 + 1;
        *piVar7 = (iVar6 + 4) / 2;
        piVar7[1] = local_c;
        piVar7 = piVar7 + iVar6 + 6;
        iVar3 = extraout_ECX_03;
      }
      local_10 = local_10 + 1;
      local_8 = local_8 + 0x20;
      local_c = local_c + 0x50;
    } while (local_10 < *(int *)(iVar3 + 0x10));
  }
  FUN_00811645(piVar7);
  return;
}


/* ---- FUN_008123b5 @ 008123b5 ---- */

void __fastcall FUN_008123b5(int param_1)

{
  if (*(char *)(param_1 + 0xa0) == '\0') {
    FUN_00812227(0,7);
    *(char *)(param_1 + 0xa0) = '\x01';
  }
  return;
}


/* ---- FUN_008123cf @ 008123cf ---- */

void __thiscall FUN_008123cf(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int *piVar5;
  undefined1 *puVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  int aiStack_81c [256];
  int local_41c [256];
  undefined1 local_1c [4];
  int *local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_18 = (int *)FUN_0080e83c(FUN_0080ec25);
  *local_18 = 0;
  local_18[1] = 0;
  piVar4 = local_18 + 2;
  local_10 = 0;
  if (0 < *(int *)(param_1 + 0x30)) {
    local_14 = 0;
    do {
      iVar1 = *(int *)(param_1 + 0x2c) + local_14;
      if (*(char *)(iVar1 + 2) != '\0') {
        iVar1 = *(int *)(iVar1 + 8);
        local_8 = 0;
        local_c = iVar1;
        do {
          local_41c[local_8] = iVar1;
          iVar2 = FUN_0080e9a6(iVar1);
          piVar5 = aiStack_81c + local_8;
          local_8 = local_8 + 1;
          *piVar5 = iVar2;
          iVar1 = FUN_0080e9c3(iVar1);
        } while (iVar1 != local_c);
        if (param_2 <= local_8) {
          local_c = FUN_0080ffdb();
          *piVar4 = local_c;
          piVar4 = piVar4 + 1;
          FUN_0080e78a(param_3 >> 0x10,1,param_4);
          iVar1 = 0;
          if (0 < local_8) {
            do {
              *piVar4 = aiStack_81c[iVar1];
              piVar4 = piVar4 + 1;
              if (iVar1 == 0) {
                puVar6 = local_1c;
                piVar5 = &local_c;
                iVar2 = local_41c[0];
                uVar7 = param_3;
                uVar8 = param_4;
                iVar9 = iVar1;
                iVar10 = iVar1;
                uVar3 = FUN_0080e9fd(local_41c[0]);
                FUN_008116fb(uVar3,iVar2,piVar5,puVar6,uVar7,uVar8,iVar9,iVar10);
              }
              else {
                iVar2 = local_41c[iVar1];
                uVar7 = param_3;
                uVar8 = param_4;
                uVar3 = FUN_0080e9e0(iVar2);
                uVar3 = FUN_0080e9e0(uVar3);
                FUN_00810043(uVar3,iVar2,uVar7,uVar8);
              }
              iVar1 = iVar1 + 1;
            } while (iVar1 < local_8);
          }
          *(byte *)((int)piVar4 + -1) = *(byte *)((int)piVar4 + -1) | 0x80;
          *local_18 = *local_18 + 1;
        }
      }
      local_10 = local_10 + 1;
      local_14 = local_14 + 0x18;
    } while (local_10 < *(int *)(param_1 + 0x30));
  }
  *piVar4 = 0;
  piVar4[1] = 0;
  FUN_00811645(piVar4 + 2);
  return;
}


/* ---- FUN_00812526 @ 00812526 ---- */

void FUN_00812526(undefined4 param_1)

{
  undefined4 local_44 [5];
  undefined4 local_30;
  undefined4 local_1c;
  
  FUN_00805a4d();
  local_44[0] = param_1;
  local_30 = param_1;
  local_1c = param_1;
  FUN_0081192e(local_44,1,0x10);
  return;
}


/* ---- FUN_00812557 @ 00812557 ---- */

void __thiscall
FUN_00812557(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  int *local_8;
  
  local_8 = (int *)FUN_0080e83c(FUN_0080f102);
  uVar7 = FUN_0080e8cf(param_2);
  *(undefined4 *)((ulonglong)uVar7 >> 0x20) = (int)uVar7;
  local_48 = param_3;
  local_44 = param_4;
  local_40 = param_5;
  uVar7 = FUN_0080e8a2(&local_48);
  puVar2 = (undefined4 *)((ulonglong)uVar7 >> 0x20);
  *puVar2 = (int)uVar7;
  iVar5 = 0;
  piVar4 = puVar2 + 1;
  param_3 = 0;
  if (0 < *(int *)(param_1 + 0x10)) {
    param_2 = 0;
    piVar3 = piVar4;
    do {
      iVar1 = *(int *)(param_1 + 0xc);
      piVar4 = piVar3;
      if (*(char *)(param_2 + 2 + iVar1) != '\0') {
        piVar4 = piVar3 + 1;
        iVar6 = iVar5;
        do {
          *(undefined1 *)(iVar1 + 2 + iVar6 * 0x20) = 0;
          *piVar4 = iVar6 * 5;
          iVar1 = *(int *)(param_1 + 0xc);
          iVar6 = *(int *)(iVar1 + 4 + iVar6 * 0x20);
          piVar4 = piVar4 + 1;
        } while (iVar6 != iVar5);
        param_3 = param_3 + 1;
        *piVar3 = ((int)piVar4 - (int)piVar3 >> 2) + -1;
      }
      param_2 = param_2 + 0x20;
      iVar5 = iVar5 + 1;
      piVar3 = piVar4;
    } while (iVar5 < *(int *)(param_1 + 0x10));
  }
  *local_8 = param_3;
  FUN_00811645(piVar4);
  return;
}


/* ---- FUN_00812613 @ 00812613 ---- */

void FUN_00812613(undefined4 param_1,undefined4 *param_2)

{
  int *piVar1;
  int iVar2;
  int extraout_EDX;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  int *local_c;
  
  piVar1 = (int *)FUN_0080e83c(FUN_0080f2cc);
  local_c = piVar1;
  iVar2 = FUN_0080e8a2(param_1);
  piVar1[1] = iVar2;
  piVar1 = piVar1 + 2;
  FUN_00805a4d();
  local_4c = *param_2;
  uStack_48 = param_2[1];
  uStack_44 = param_2[2];
  uStack_40 = param_2[3];
  FUN_0080e8a2(&local_4c);
  iVar2 = 0;
  if (0 < *(int *)(extraout_EDX + 0x10)) {
    do {
      *piVar1 = iVar2;
      piVar1 = piVar1 + 1;
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)(extraout_EDX + 0x10));
  }
  *local_c = ((int)piVar1 - (int)local_c >> 2) + -2;
  FUN_00811645(piVar1);
  return;
}


/* ---- FUN_0081268d @ 0081268d ---- */

undefined4 __thiscall FUN_0081268d(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  undefined8 uVar12;
  int local_18;
  int local_14;
  int local_c;
  int local_8;
  
  iVar1 = *(int *)(param_1 + 0x10);
  FUN_00806ae3();
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + *(int *)(param_2 + 0x10);
  iVar7 = *(int *)(param_1 + 0x20);
  FUN_00806ae3();
  *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + *(int *)(param_2 + 0x20);
  local_14 = *(int *)(param_1 + 0x30);
  FUN_00806ae3();
  *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + *(int *)(param_2 + 0x30);
  FUN_00806ae3();
  local_18 = *(int *)(param_1 + 0x60);
  FUN_00806ae3();
  *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + *(int *)(param_2 + 0x60);
  iVar8 = *(int *)(param_1 + 0x70);
  FUN_00806ae3();
  *(int *)(param_1 + 0x70) = *(int *)(param_1 + 0x70) + *(int *)(param_2 + 0x70);
  FUN_0080fec8(*(int *)(param_2 + 0x10) + iVar1);
  iVar9 = 0;
  if (0 < *(int *)(param_2 + 0x10)) {
    local_c = 0;
    iVar6 = iVar1 << 5;
    do {
      puVar10 = (undefined4 *)(*(int *)(param_2 + 0xc) + local_c);
      local_c = local_c + 0x20;
      puVar2 = (undefined4 *)(*(int *)(param_1 + 0xc) + iVar6);
      puVar11 = puVar2;
      for (iVar5 = 8; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar11 = puVar11 + 1;
      }
      puVar2[1] = puVar2[1] + iVar1;
      puVar2[2] = puVar2[2] + iVar1;
      puVar2[5] = puVar2[5] + iVar1;
      iVar9 = iVar9 + 1;
      iVar6 = iVar6 + 0x20;
    } while (iVar9 < *(int *)(param_2 + 0x10));
  }
  local_8 = 0;
  if (0 < *(int *)(param_2 + 0x20)) {
    iVar9 = iVar7 * 0x30;
    local_c = 0;
    do {
      puVar2 = (undefined4 *)(*(int *)(param_1 + 0x1c) + iVar9);
      puVar10 = (undefined4 *)(*(int *)(param_2 + 0x1c) + local_c);
      puVar11 = puVar2;
      for (iVar6 = 0xc; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar11 = puVar11 + 1;
      }
      piVar3 = puVar2 + 3;
      iVar6 = 2;
      do {
        piVar3[-2] = piVar3[-2] + iVar7 * 2;
        *piVar3 = *piVar3 + iVar7 * 2;
        piVar3[4] = piVar3[4] + iVar1;
        piVar3[2] = piVar3[2] + local_14;
        piVar3 = piVar3 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      local_8 = local_8 + 1;
      local_c = local_c + 0x30;
      iVar9 = iVar9 + 0x30;
    } while (local_8 < *(int *)(param_2 + 0x20));
  }
  *(undefined4 *)(*(int *)(param_2 + 0x3c) + 0x48) = 0;
  local_8 = 1;
  if (1 < *(int *)(param_2 + 0x40)) {
    iVar9 = 0x4c;
    do {
      local_c = 1;
      if (1 < *(int *)(param_1 + 0x40)) {
        piVar3 = (int *)(*(int *)(param_2 + 0x3c) + iVar9);
        piVar4 = *(int **)(param_1 + 0x3c);
        do {
          if ((piVar4[0x13] == *piVar3) && (piVar4[0x24] == piVar3[0x11])) {
            piVar3[0x12] = local_c;
            goto LAB_00812856;
          }
          local_c = local_c + 1;
          piVar4 = piVar4 + 0x13;
        } while (local_c < *(int *)(param_1 + 0x40));
      }
      *(undefined4 *)(*(int *)(param_2 + 0x3c) + 0x48 + iVar9) = *(undefined4 *)(param_1 + 0x40);
      piVar4 = (int *)FUN_00806b54();
      iVar6 = *(int *)(iVar9 + *(int *)(param_2 + 0x3c));
      *piVar4 = iVar6;
      piVar3 = (int *)(iVar6 + 8);
      *piVar3 = *piVar3 + 1;
      piVar4[0x11] = *(int *)(*(int *)(param_2 + 0x3c) + 0x44 + iVar9);
LAB_00812856:
      local_8 = local_8 + 1;
      iVar9 = iVar9 + 0x4c;
    } while (local_8 < *(int *)(param_2 + 0x40));
  }
  local_8 = 0;
  if (0 < *(int *)(param_2 + 0x30)) {
    local_c = 0;
    local_14 = local_14 * 0x18;
    do {
      puVar2 = (undefined4 *)(*(int *)(param_1 + 0x2c) + local_14);
      puVar10 = (undefined4 *)(*(int *)(param_2 + 0x2c) + local_c);
      local_c = local_c + 0x18;
      local_14 = local_14 + 0x18;
      puVar11 = puVar2;
      for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar11 = puVar11 + 1;
      }
      puVar2[2] = puVar2[2] + iVar7 * 2;
      local_8 = local_8 + 1;
      puVar2[1] = *(undefined4 *)(puVar2[1] * 0x4c + 0x48 + *(int *)(param_2 + 0x3c));
    } while (local_8 < *(int *)(param_2 + 0x30));
  }
  iVar7 = 0;
  local_8 = 0;
  if (0 < *(int *)(param_2 + 0x60)) {
    local_18 = local_18 * 0x34;
    do {
      iVar9 = *(int *)(param_1 + 0x5c) + local_18;
      local_c = 0;
      local_14 = iVar7;
      do {
        piVar3 = (int *)(*(int *)(param_2 + 0x5c) + local_14);
        iVar6 = local_c + 1;
        local_14 = local_14 + 4;
        *(int *)(iVar9 + local_c * 4) = *piVar3 + iVar1;
        local_c = iVar6;
      } while (iVar6 < 8);
      local_8 = local_8 + 1;
      local_18 = local_18 + 0x34;
      *(undefined4 *)(iVar9 + 0x20) = *(undefined4 *)(*(int *)(param_2 + 0x5c) + 0x20 + iVar7);
      puVar10 = (undefined4 *)(*(int *)(param_2 + 0x5c) + 0x24 + iVar7);
      *(undefined4 *)(iVar9 + 0x24) = *puVar10;
      *(undefined4 *)(iVar9 + 0x28) = puVar10[1];
      *(undefined4 *)(iVar9 + 0x2c) = puVar10[2];
      *(undefined4 *)(iVar9 + 0x30) = puVar10[3];
      iVar7 = iVar7 + 0x34;
    } while (local_8 < *(int *)(param_2 + 0x60));
  }
  iVar7 = 0;
  if (0 < *(int *)(param_2 + 0x70)) {
    iVar8 = iVar8 << 2;
    do {
      *(int *)(iVar8 + *(int *)(param_1 + 0x6c)) =
           *(int *)(*(int *)(param_2 + 0x6c) + iVar7 * 4) + iVar1;
      iVar7 = iVar7 + 1;
      iVar8 = iVar8 + 4;
    } while (iVar7 < *(int *)(param_2 + 0x70));
  }
  puVar10 = (undefined4 *)FUN_0080e83c(FUN_0080ebc9);
  *puVar10 = 1;
  uVar12 = FUN_0080e8cf(param_2);
  puVar10 = (undefined4 *)((ulonglong)uVar12 >> 0x20);
  *puVar10 = (int)uVar12;
  puVar10[1] = iVar1 * 5;
  puVar10[2] = 0;
  puVar10[3] = *(int *)(param_2 + 0x10) * 5;
  FUN_00811645(puVar10 + 4);
  *(undefined4 *)(param_1 + 0x9c) = 0xffffffff;
  FUN_00811081(0);
  return 1;
}


/* ---- FUN_008129b8 @ 008129b8 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
FUN_008129b8(int param_1,undefined4 param_2,int param_3,undefined4 param_4,char param_5)

{
  float fVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  float *pfVar5;
  undefined1 local_a4 [64];
  float local_64 [5];
  float local_50;
  float local_44;
  float local_40;
  float local_24;
  float local_20;
  float local_1c;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_14 = 1 << ((byte)param_4 & 0x1f);
  local_8 = 0;
  do {
    if (param_5 == '\0') {
      local_10 = 1;
    }
    else {
      local_10 = (-(uint)((local_8 & 1) != 0) & 2) - 1;
    }
    FUN_00810366(0,6);
    local_c = 0;
    if (0 < *(int *)(param_1 + 0x30)) {
      iVar4 = 0;
      do {
        if ((param_3 == 0) ||
           (pbVar2 = (byte *)(*(int *)(param_1 + 0x2c) + iVar4), (*pbVar2 & (byte)param_3) != 0)) {
          FUN_0081066f(&local_24,local_c);
          uVar3 = 0;
          fVar1 = local_24;
          if (ABS(local_24) < ABS(local_20)) {
            uVar3 = 2;
            fVar1 = local_20;
          }
          if (ABS(fVar1) < ABS(local_1c)) {
            uVar3 = 4;
            fVar1 = local_1c;
          }
          if (_DAT_0081f374 < fVar1) {
            uVar3 = uVar3 + 1;
          }
          *(bool *)(*(int *)(param_1 + 0x2c) + 2 + iVar4) = uVar3 == local_8;
        }
        else {
          pbVar2[2] = 0;
        }
        local_c = local_c + 1;
        iVar4 = iVar4 + 0x18;
      } while (local_c < *(int *)(param_1 + 0x30));
    }
    FUN_00812049(0,0,0,local_14);
    FUN_0081050f();
    pfVar5 = local_64;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar5 = 0.0;
      pfVar5 = pfVar5 + 1;
    }
    if ((int)local_8 / 2 == 0) {
      local_44 = (float)local_10;
      local_50 = -1.0;
    }
    else if ((int)local_8 / 2 == 1) {
      local_64[0] = 1.0;
      local_40 = (float)local_10 * _DAT_0081f378;
    }
    else {
      local_64[0] = (float)local_10 * _DAT_0081f378;
      local_50 = _DAT_0081f378;
    }
    FUN_00805c2c(param_2,local_64);
    FUN_0081192e(local_a4,0,param_4);
    local_8 = local_8 + 1;
  } while ((int)local_8 < 6);
  return;
}


/* ---- FUN_00812b30 @ 00812b30 ---- */

void __fastcall FUN_00812b30(int param_1)

{
  int iVar1;
  int iVar2;
  int *extraout_EDX;
  int iVar3;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  FUN_008123b5();
  *(undefined4 *)(param_1 + 0x88) = 1;
  local_8 = 1;
  if (1 < *(int *)(param_1 + 0x40)) {
    local_c = 0x4c;
    do {
      iVar1 = *(int *)(local_c + *(int *)(param_1 + 0x3c));
      local_18 = 0;
      if (0 < *(int *)(iVar1 + 0x10)) {
        local_14 = 0;
        local_10 = local_c;
        do {
          iVar3 = *(int *)(iVar1 + 0xc) + local_14;
          iVar2 = FUN_0081104f(*(undefined4 *)(iVar3 + 0xe4),local_8);
          if (iVar2 == -1) {
            iVar2 = *(int *)(param_1 + 0x50);
            FUN_00806b54();
            FUN_0080e82e();
            *extraout_EDX = local_8;
            extraout_EDX[1] = *(int *)(iVar3 + 0xe4);
            FUN_00810b16(extraout_EDX);
          }
          local_18 = local_18 + 1;
          local_14 = local_14 + 0xf0;
          *(int *)(*(int *)(param_1 + 0x3c) + 4 + local_10) = iVar2;
          local_10 = local_10 + 4;
        } while (local_18 < *(int *)(iVar1 + 0x10));
      }
      local_8 = local_8 + 1;
      local_c = local_c + 0x4c;
    } while (local_8 < *(int *)(param_1 + 0x40));
  }
  return;
}


/* ---- FUN_00812bfa @ 00812bfa ---- */

void __thiscall FUN_00812bfa(int param_1,int param_2,int param_3)

{
  FUN_0080f564(*(int *)(*(int *)(param_1 + 0x3c) + 4 + (param_2 * 0x13 + param_3) * 4) * 0x214 +
               *(int *)(param_1 + 0x4c));
  return;
}


/* ---- Mesh_Subdivide @ 00812c20 ---- */

int Mesh_Subdivide(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  FUN_0081108f();
  for (; param_5 != 0; param_5 = param_5 + -1) {
    FUN_00811b86(param_4);
  }
  *(undefined1 *)(param_2 + 0xa0) = 0;
  return param_2;
}


/* ---- Mesh_Extrude @ 00812c5d ---- */

int Mesh_Extrude(undefined4 param_1,uint param_2,undefined4 param_3,uint param_4,uint param_5,
                int param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
                undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
                undefined4 param_14,int param_15)

{
  uint uVar1;
  int iVar2;
  char cVar3;
  char *pcVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  float local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  uint local_c;
  int local_8;
  
  iVar2 = param_2;
  FUN_0081108f();
  FUN_008123b5();
  if (((param_5 & 8) == 0) && (((byte)param_5 & 6) != 2)) {
    param_3 = 1;
  }
  else {
    param_3 = 0;
  }
  iVar6 = 0;
  iVar8 = 0;
  if (0 < *(int *)(param_2 + 0x30)) {
    do {
      *(int *)(*(int *)(param_2 + 0x2c) + 0xc + iVar6) = param_3 + -1;
      iVar8 = iVar8 + 1;
      iVar6 = iVar6 + 0x18;
    } while (iVar8 < *(int *)(param_2 + 0x30));
  }
  do {
    iVar6 = *(int *)(iVar2 + 0x30);
    iVar8 = 0;
    if (0 < iVar6) {
      pcVar4 = (char *)(*(int *)(iVar2 + 0x2c) + 2);
      do {
        if ((*(int *)(pcVar4 + 10) == -1) && (*pcVar4 != '\0')) break;
        iVar8 = iVar8 + 1;
        pcVar4 = pcVar4 + 0x18;
      } while (iVar8 < iVar6);
    }
    if (iVar8 == iVar6) {
      FUN_0080e83c(0);
      local_40 = 0;
      local_30 = (float)param_6;
      local_4c = param_10;
      local_48 = param_11;
      local_44 = param_12;
      local_3c = param_13;
      local_20 = 0;
      local_38 = param_14;
      local_34 = param_15;
      local_2c = param_7;
      local_28 = param_8;
      local_24 = param_9;
      local_c = FUN_0080e8a2(&local_4c);
      if (param_6 != 0) {
        uVar1 = param_5 & 1;
        uVar7 = (int)param_5 >> 1;
        uVar9 = (int)param_5 >> 4;
        param_15 = param_6;
        do {
          FUN_008119c5((param_4 & 0xff) << 8,uVar9 & 3,uVar1);
          piVar5 = (int *)FUN_0080e83c(FUN_0080fae3);
          *piVar5 = param_3;
          piVar5[1] = uVar7 & 7;
          piVar5[2] = local_c;
          iVar8 = 0;
          piVar5 = piVar5 + 3;
          iVar6 = 0;
          if (0 < *(int *)(iVar2 + 0x10)) {
            do {
              *(undefined4 *)(iVar8 + 0xc + *(int *)(iVar2 + 0xc)) = 0;
              iVar6 = iVar6 + 1;
              iVar8 = iVar8 + 0x20;
            } while (iVar6 < *(int *)(iVar2 + 0x10));
          }
          local_8 = 0;
          if (0 < param_3) {
            do {
              param_5 = 0;
              param_2 = 0;
              if (0 < *(int *)(iVar2 + 0x20) * 2) {
                do {
                  iVar6 = FUN_0080e91e(param_2);
                  if (((*(char *)(iVar6 + 2) != '\0') &&
                      (iVar6 = FUN_0080e91e(param_2), *(int *)(iVar6 + 0xc) == local_8)) &&
                     (iVar6 = FUN_0080e966(param_2), (*(byte *)(iVar6 + 0xc) & 1) == 0)) {
                    iVar6 = FUN_0080e966(param_2);
                    param_5 = param_5 + 1;
                    *(undefined4 *)(iVar6 + 0xc) = 1;
                    iVar6 = FUN_0080e9a6(param_2);
                    piVar5[param_5] = iVar6;
                  }
                  param_2 = param_2 + 1;
                } while ((int)param_2 < *(int *)(iVar2 + 0x20) * 2);
              }
              local_8 = local_8 + 1;
              *piVar5 = param_5;
              piVar5 = piVar5 + param_5 + 1;
            } while (local_8 < param_3);
          }
          FUN_00811645(piVar5);
          param_15 = param_15 + -1;
        } while (param_15 != 0);
      }
      FUN_0080ff59();
      FUN_0081050f();
      FUN_008103f3((param_4 & 0xff00) << 8,0);
      *(undefined1 *)(iVar2 + 0xa0) = 0;
      return iVar2;
    }
    iVar6 = 1;
    DAT_0140a128 = iVar8;
    do {
      iVar8 = iVar6 * 4;
      iVar6 = iVar6 + -1;
      iVar8 = *(int *)(iVar8 + 0x140a124) * 0x18;
      *(int *)(*(int *)(iVar2 + 0x2c) + 0xc + iVar8) = param_3;
      param_2 = *(uint *)(*(int *)(iVar2 + 0x2c) + 8 + iVar8);
      local_c = param_2;
      do {
        local_8 = FUN_0080e989(param_2 ^ 1);
        piVar5 = (int *)(local_8 * 0x18 + 0xc + *(int *)(iVar2 + 0x2c));
        if ((*piVar5 == -1) && (cVar3 = FUN_00810297(param_2,param_5 & 1), cVar3 == '\0')) {
          *piVar5 = -2;
          (&DAT_0140a128)[iVar6] = local_8;
          iVar6 = iVar6 + 1;
        }
        param_2 = FUN_0080e9c3(param_2);
      } while (param_2 != local_c);
    } while (iVar6 != 0);
    param_3 = param_3 + 1;
  } while( true );
}


/* ---- Mesh_Transform @ 00812f29 ---- */

int Mesh_Transform(undefined4 param_1,int param_2)

{
  undefined1 local_44 [64];
  
  FUN_0081108f();
  FUN_008063b2(&stack0x00000010);
  FUN_0081192e(local_44,0,0);
  *(undefined1 *)(param_2 + 0xa0) = 0;
  return param_2;
}


/* ---- Mesh_TransformEx @ 00812f6a ---- */

undefined4 Mesh_TransformEx(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_stack_00000034;
  undefined4 in_stack_00000038;
  undefined1 local_44 [64];
  
  FUN_0081108f();
  FUN_008063b2(&stack0x00000010);
  FUN_0081192e(local_44,in_stack_00000034,in_stack_00000038);
  return param_2;
}


/* ---- Mesh_Cylinder @ 00812fa3 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Mesh_Cylinder(undefined4 param_1,int param_2,byte param_3,int param_4)

{
  byte *pbVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float10 fVar6;
  undefined1 local_a4 [20];
  undefined4 local_90;
  float local_80;
  undefined4 local_74;
  float local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined1 local_64 [20];
  undefined4 local_50;
  undefined4 local_34;
  float local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float local_14;
  float local_10;
  float local_c;
  undefined4 local_8;
  
  iVar3 = operator_new(0xc4);
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = FUN_0080fcbd();
  }
  FUN_0080fe61(0x2f,0x400);
  FUN_00810905(param_1,0,_DAT_0081f2ac,0);
  FUN_00805a4d();
  local_2c = 0x3f800000;
  FUN_00805a4d();
  fVar2 = _DAT_0081f2bc / (float)param_2;
  *(undefined1 *)(*(int *)(iVar3 + 0x2c) + 2) = 1;
  local_70 = fVar2;
  if (0 < param_2) {
    do {
      FUN_008119c5(0,0,0);
      FUN_0080e78a(1,1,0);
      FUN_0081050f();
      FUN_0081192e(local_64,0,0);
      FUN_0081192e(local_a4,5,5);
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  FUN_00805a9d(_DAT_0081fcbc,0,0);
  local_14 = _DAT_0081f2bc / (float)param_4;
  local_8 = 0x3f800000;
  local_10 = fVar2;
  local_c = local_14;
  FUN_00805e24(&local_14);
  FUN_00805e24(&local_14);
  FUN_00805e24(&local_14);
  local_34 = 0;
  local_30 = _DAT_0081f2ac;
  local_2c = 0;
  local_28 = 0x3f800000;
  FUN_00810366(1,4);
  FUN_0081192e(local_64,0,0);
  fVar6 = (float10)FUN_0081045c(0x10100,1);
  local_24 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = _DAT_0081fcb8;
  local_10 = 0.0001;
  local_c = _DAT_0081fcb8;
  local_8 = 0;
  local_20 = (float)fVar6;
  FUN_00810873(&local_24,&local_14,0x10100,0);
  local_20 = -0.5;
  FUN_00810873(&local_24,&local_14,0x10100,0);
  FUN_008102dc(0x100);
  FUN_008123cf(4,0,0,0);
  if (1 < param_4) {
    FUN_00810366(1,4);
    FUN_00805a4d();
    local_50 = 0;
    FUN_0081192e(local_64,0,1);
    FUN_008102dc(0x100);
    iVar4 = 0;
    if (0 < *(int *)(iVar3 + 0x30)) {
      iVar5 = 0;
      do {
        pbVar1 = (byte *)(*(int *)(iVar3 + 0x2c) + 2 + iVar5);
        *pbVar1 = *pbVar1 ^ 1;
        iVar4 = iVar4 + 1;
        iVar5 = iVar5 + 0x18;
      } while (iVar4 < *(int *)(iVar3 + 0x30));
    }
    if (1 < param_4) {
      param_4 = param_4 + -1;
      do {
        iVar4 = *(int *)(iVar3 + 0x20);
        FUN_008119c5(0x100,0,0);
        if (iVar4 < *(int *)(iVar3 + 0x20)) {
          iVar5 = iVar4 * 0x30;
          do {
            *(undefined1 *)(iVar5 + *(int *)(iVar3 + 0x1c)) = 0;
            iVar4 = iVar4 + 1;
            iVar5 = iVar5 + 0x30;
          } while (iVar4 < *(int *)(iVar3 + 0x20));
        }
        FUN_0081050f();
        FUN_00812526(0x3f800000);
        param_4 = param_4 + -1;
      } while (param_4 != 0);
    }
  }
  param_2 = -1;
  local_24 = 0;
  param_4 = 1;
  local_1c = 0;
  local_18 = 0x3f800000;
  do {
    local_8 = 0x3f800000;
    local_14 = 2.0;
    local_10 = 0.01;
    local_c = 2.0;
    local_20 = (float)param_2 * _DAT_0081f2ac;
    FUN_00810366(0,6);
    FUN_00810873(&local_24,&local_14,0,0);
    FUN_00812049(0,0,0,0xfe);
    FUN_0081050f();
    FUN_00805a4d();
    local_90 = 0;
    local_80 = (float)param_4;
    local_74 = 0x3f000000;
    local_70 = 0.5;
    local_6c = 0;
    local_68 = 0x3f800000;
    FUN_0081192e(local_a4,0,5);
    param_4 = param_4 + -2;
    param_2 = param_2 + 2;
  } while (-2 < param_4);
  FUN_0081045c(0x20000,1);
  FUN_008102dc(0x20001);
  FUN_00812049(1,0,0,0x20);
  FUN_00810561(0);
  FUN_00805a4d();
  local_74 = 0x3f800000;
  FUN_0081192e(local_a4,5,5);
  if ((param_3 & 1) != 0) {
    iVar3 = FUN_0081114b(iVar3,1);
  }
  if ((param_3 & 2) != 0) {
    FUN_00805a4d();
    local_30 = 0.5;
    FUN_00810366(1,7);
    FUN_0081192e(local_64,0,0);
  }
  FUN_0081045c(1,1);
  return iVar3;
}


/* ---- Mesh_Crease @ 0081337d ---- */

void Mesh_Crease(void)

{
  return;
}


/* ---- Mesh_Triangulate @ 00813380 ---- */

int Mesh_Triangulate(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_0081108f();
  FUN_008123cf(param_3,0,0,param_4);
  *(undefined1 *)(param_1 + 0xa0) = 0;
  return param_1;
}


/* ---- Mesh_Displace @ 008133b4 ---- */

int Mesh_Displace(undefined4 param_1,int param_2,undefined4 *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  int *piVar1;
  
  if (param_3 == (undefined4 *)0x0) {
    param_2 = 0;
  }
  else {
    FUN_0081108f();
    FUN_008123b5();
    FUN_00812557(param_3,param_5,param_6,param_7);
    piVar1 = param_3 + 2;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      (**(code **)*param_3)(1);
    }
    *(undefined1 *)(param_2 + 0xa0) = 0;
  }
  return param_2;
}


/* ---- Mesh_Perlin @ 00813417 ---- */

undefined4 Mesh_Perlin(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_44 [64];
  
  FUN_0081108f();
  FUN_008063b2(&stack0x00000010);
  FUN_00812613(local_44,&stack0x00000034);
  return param_2;
}


/* ---- Mesh_Add @ 0081344e ---- */

int Mesh_Add(int param_1,int param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  FUN_0081108f();
  iVar3 = param_2;
  iVar4 = 1;
  if (1 < param_1) {
    do {
      puVar2 = (undefined4 *)(&param_2)[iVar4];
      FUN_0081268d(puVar2,0);
      piVar1 = puVar2 + 2;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        (**(code **)*puVar2)(1);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < param_1);
  }
  *(undefined1 *)(iVar3 + 0xa0) = 0;
  return iVar3;
}


/* ---- Mesh_Multiply @ 0081349b ---- */

int Mesh_Multiply(undefined4 param_1,undefined4 *param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int in_stack_00000030;
  uint in_stack_00000034;
  float in_stack_00000038;
  float in_stack_0000003c;
  undefined1 local_148 [64];
  undefined1 local_108 [64];
  undefined1 local_c8 [64];
  undefined1 local_88 [64];
  undefined1 local_48 [48];
  float local_18;
  float local_14;
  int local_8;
  
  FUN_0081108f();
  FUN_008063b2(&stack0x0000000c);
  FUN_00805b55(&stack0x00000040);
  iVar3 = operator_new(0xc4);
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = FUN_0080fcbd();
  }
  FUN_0080fe61(0x2f,0);
  FUN_00805a4d();
  FUN_00805a4d();
  FUN_008054e9();
  local_8 = 0;
  if (0 < in_stack_00000030) {
    uVar2 = in_stack_00000034 & 2;
    in_stack_00000034 = in_stack_00000034 & 1;
    do {
      FUN_0081268d(param_2,local_8 != 0);
      iVar4 = 0;
      if (*(int *)(iVar3 + 0x10) != param_2[4] && -1 < *(int *)(iVar3 + 0x10) - param_2[4]) {
        iVar5 = 0;
        do {
          *(undefined1 *)(iVar5 + 2 + *(int *)(iVar3 + 0xc)) = 0;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + 0x20;
        } while (iVar4 < *(int *)(iVar3 + 0x10) - param_2[4]);
      }
      if (iVar4 < *(int *)(iVar3 + 0x10)) {
        iVar5 = iVar4 << 5;
        do {
          *(undefined1 *)(iVar5 + 2 + *(int *)(iVar3 + 0xc)) = 1;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + 0x20;
        } while (iVar4 < *(int *)(iVar3 + 0x10));
      }
      FUN_00805c2c(local_c8,local_88);
      FUN_0081192e(local_48,0,0);
      if (uVar2 == 0) {
        FUN_0080e753(local_108);
      }
      else {
        FUN_00806404(&stack0x0000000c);
      }
      FUN_0080e753(local_148);
      if (in_stack_00000034 != 0) {
        FUN_00805a4d();
        local_18 = in_stack_00000038 * (float)local_8;
        local_14 = (float)local_8 * in_stack_0000003c;
        FUN_0081192e(local_48,5,5);
      }
      local_8 = local_8 + 1;
    } while (local_8 < in_stack_00000030);
  }
  piVar1 = param_2 + 2;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    (**(code **)*param_2)(1);
  }
  *(undefined1 *)(iVar3 + 0xa0) = 0;
  return iVar3;
}


/* ---- Mesh_Bend @ 00813636 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Mesh_Bend(undefined4 param_1,int param_2)

{
  float fVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  float in_stack_00000058;
  float in_stack_0000005c;
  undefined4 in_stack_00000060;
  undefined4 in_stack_00000064;
  int in_stack_00000068;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_20;
  
  FUN_0081108f();
  piVar2 = (int *)FUN_0080e83c(FUN_0081116a);
  FUN_008063b2(&stack0x00000010);
  iVar3 = FUN_0080e8a2(&local_44);
  piVar2[1] = iVar3;
  FUN_008063b2(&stack0x00000034);
  iVar3 = FUN_0080e8a2(&local_44);
  fVar1 = in_stack_0000005c * _DAT_0081f37c;
  piVar2[2] = iVar3;
  FUN_00805a9d(in_stack_00000058 * _DAT_0081f37c,0,fVar1);
  local_44 = local_40;
  local_40 = local_30;
  local_3c = local_20;
  local_34 = in_stack_00000060;
  local_30 = in_stack_00000064;
  iVar3 = FUN_0080e8a2(&local_44);
  piVar2[3] = iVar3;
  piVar2[4] = in_stack_00000068;
  iVar4 = 0;
  piVar5 = piVar2 + 5;
  iVar3 = 0;
  if (0 < *(int *)(param_2 + 0x10)) {
    do {
      *piVar5 = iVar4;
      piVar5 = piVar5 + 1;
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 5;
    } while (iVar3 < *(int *)(param_2 + 0x10));
  }
  *piVar2 = ((int)piVar5 - (int)piVar2 >> 2) + -5;
  FUN_00811645(piVar5);
  *(undefined1 *)(param_2 + 0xa0) = 0;
  return param_2;
}


/* ---- Mesh_CollisionCube @ 00813737 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 *
Mesh_CollisionCube(undefined4 *param_1,undefined4 param_2,undefined4 param_3,float param_4,
                  float param_5,float param_6,float param_7,float param_8,float param_9,
                  uint param_10,int param_11,int param_12,int param_13,undefined1 param_14,
                  undefined1 param_15,undefined4 param_16,undefined1 param_17)

{
  int *piVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  float10 fVar9;
  float10 fVar10;
  float local_4c;
  float local_48;
  float local_44;
  float local_3c;
  float local_38;
  float local_2c [2];
  int local_24;
  int local_20;
  int local_1c;
  uint local_18;
  uint local_14;
  int local_10;
  float *local_c;
  float local_8;
  
  puVar6 = (undefined4 *)0x0;
  if (param_1 != (undefined4 *)0x0) {
    FUN_0081108f();
  }
  iVar7 = param_11 * param_12 * param_13;
  iVar3 = operator_new(0xc4);
  if (iVar3 != 0) {
    puVar6 = (undefined4 *)FUN_0080fcbd();
  }
  FUN_0080fe61(0x2f,iVar7 * 8);
  piVar1 = puVar6 + 0x17;
  FUN_00806ae3();
  local_18 = param_10 & 0x10;
  puVar6[0x18] = iVar7;
  if (local_18 == 0) {
    local_44 = param_9;
    local_4c = param_5;
    local_48 = param_7;
    local_3c = (param_4 - param_5) / (float)param_11;
    fVar2 = (param_8 - param_9) / (float)param_13;
    iVar3 = param_12;
  }
  else {
    local_48 = param_6;
    local_4c = (param_4 + param_5) * _DAT_0081f2ac;
    iVar3 = -param_12;
    local_44 = (param_8 + param_9) * _DAT_0081f2ac;
    fVar2 = _DAT_0081f2bc / ((float)-param_11 + (float)-param_11);
    local_3c = fVar2 * (param_4 - param_5);
    fVar2 = fVar2 * (param_8 - param_9);
  }
  local_38 = (param_6 - param_7) / (float)iVar3;
  param_8 = 0.0;
  param_4 = 0.0;
  if (0 < param_11) {
    do {
      param_7 = 0.0;
      if (0 < param_12) {
        iVar3 = (int)param_8 * 0x34;
        iVar7 = param_13 * 0x34;
        local_24 = iVar7;
        do {
          param_6 = 0.0;
          if (0 < param_13) {
            local_8 = (float)param_13;
            local_14 = param_10 & 0xf;
            param_8 = (float)((int)param_8 + param_13);
            local_20 = iVar3 + iVar7;
            iVar8 = iVar3;
            do {
              *(uint *)(iVar8 + 0x20 + *piVar1) = local_14;
              local_10 = (int)param_6 + 1;
              param_5 = 0.0;
              local_2c[0] = ((float)local_10 * _DAT_0081f37c) / local_8;
              local_2c[1] = ((float)(int)param_6 * _DAT_0081f37c) / local_8;
              param_9 = (float)iVar8;
              do {
                iVar3 = FUN_0080ffdb();
                *(int *)((int)param_9 + *piVar1) = iVar3;
                *(undefined1 *)(iVar8 + 0x24 + *piVar1) = param_14;
                *(undefined1 *)(iVar8 + 0x25 + *piVar1) = param_15;
                *(undefined4 *)(iVar8 + 0x28 + *piVar1) = param_16;
                *(undefined1 *)(iVar8 + 0x26 + *piVar1) = param_17;
                *(undefined4 *)(iVar8 + 0x2c + *piVar1) = param_2;
                *(undefined4 *)(iVar8 + 0x30 + *piVar1) = param_3;
                pfVar4 = (float *)(iVar3 * 0x50 + puVar6[0x1f]);
                if (local_18 == 0) {
                  local_1c = ((int)param_5 >> 2 & 1U) + (int)param_6;
                  *pfVar4 = (float)(int)(((uint)param_5 & 1) + (int)param_4) * local_3c + local_4c;
                  pfVar4[1] = (float)(int)(((int)param_5 >> 1 & 1U) + (int)param_7) * local_38 +
                              local_48;
                  pfVar4[2] = (float)local_1c * fVar2 + local_44;
                }
                else {
                  local_c = local_2c + ((uint)param_5 & 1);
                  fVar9 = (float10)(int)(((int)param_5 >> 2 & 1U) + (int)param_4);
                  fVar10 = (float10)fsin((float10)*local_c);
                  local_1c = ((int)param_5 >> 1 & 1U) + (int)param_7;
                  *pfVar4 = (float)(fVar10 * (float10)local_3c * fVar9 + (float10)local_4c);
                  pfVar4[1] = (float)local_1c * local_38 + local_48;
                  fVar10 = (float10)fcos((float10)*local_c);
                  pfVar4[2] = (float)(fVar10 * (float10)fVar2 * fVar9 + (float10)local_44);
                }
                param_5 = (float)((int)param_5 + 1);
                param_9 = (float)((int)param_9 + 4);
                pfVar4[3] = 1.0;
              } while ((int)param_5 < 8);
              param_6 = (float)local_10;
              iVar8 = iVar8 + 0x34;
              iVar3 = local_20;
              iVar7 = local_24;
            } while (local_10 < param_13);
          }
          param_7 = (float)((int)param_7 + 1);
        } while ((int)param_7 < param_12);
      }
      param_4 = (float)((int)param_4 + 1);
    } while ((int)param_4 < param_11);
  }
  puVar5 = puVar6;
  if (param_1 != (undefined4 *)0x0) {
    FUN_0081268d(puVar6,0);
    piVar1 = puVar6 + 2;
    *piVar1 = *piVar1 + -1;
    puVar5 = param_1;
    if (*piVar1 == 0) {
      (**(code **)*puVar6)(1);
    }
  }
  return puVar5;
}


/* ---- Mesh_UVProjection @ 00813a39 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Mesh_UVProjection(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  int in_stack_00000030;
  undefined1 local_54 [64];
  float local_14;
  float local_10;
  float local_c;
  
  FUN_0081108f();
  FUN_008063b2(&stack0x0000000c);
  iVar1 = 0;
  if ((in_stack_00000030 == 0) || (in_stack_00000030 == 3)) {
    FUN_008129b8(local_54,param_2,5,in_stack_00000030 == 0);
  }
  else if (0 < *(int *)(param_1 + 0x10)) {
    in_stack_00000030 = 0;
    do {
      iVar2 = *(int *)(param_1 + 0x7c) + in_stack_00000030;
      FUN_00806305(local_54,iVar2);
      in_stack_00000030 = in_stack_00000030 + 0x50;
      fVar3 = (float10)fpatan((float10)local_14,(float10)local_c);
      iVar1 = iVar1 + 1;
      *(float *)(iVar2 + 0x40) = (float)((float10)_DAT_0081fba0 - fVar3 * (float10)_DAT_0081fcc0);
      *(float *)(iVar2 + 0x44) = -local_10;
    } while (iVar1 < *(int *)(param_1 + 0x10));
  }
  return param_1;
}


/* ---- Mesh_Center @ 00813ad4 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 Mesh_Center(undefined4 param_1,undefined4 param_2,byte param_3)

{
  undefined1 local_64 [48];
  float local_34;
  float local_30;
  float local_2c;
  float local_24;
  float local_20;
  float local_1c;
  float local_14;
  float local_10;
  float local_c;
  
  FUN_0081108f();
  FUN_00805a4d();
  FUN_00810764(local_64,&local_24);
  FUN_00810366(1,4);
  if ((param_3 & 1) != 0) {
    local_34 = (local_14 + local_24) * _DAT_0081fb64;
  }
  if ((param_3 & 2) != 0) {
    if ((char)param_3 < '\0') {
      local_30 = -local_20;
    }
    else {
      local_30 = (local_10 + local_20) * _DAT_0081fb64;
    }
  }
  if ((param_3 & 4) != 0) {
    local_2c = (local_c + local_1c) * _DAT_0081fb64;
  }
  FUN_0081192e(local_64,0,0);
  return param_1;
}


/* ---- Mesh_AutoCollision @ 00813b67 ---- */

undefined4
Mesh_AutoCollision(undefined4 param_1,float param_2,undefined4 param_3,undefined4 param_4,
                  undefined4 param_5,undefined4 param_6,int param_7)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined1 local_64 [64];
  float local_24;
  float local_20;
  float local_1c;
  float local_14;
  float local_10;
  float local_c;
  
  FUN_0081108f();
  FUN_00805a4d();
  FUN_00810764(local_64,&local_24);
  puVar2 = (undefined4 *)
           Mesh_CollisionCube(0,0,0,local_24 - param_2,local_14 + param_2,local_20 - param_2,
                              local_10 + param_2,local_1c - param_2,local_c + param_2,param_3,
                              param_4,param_5,param_6,0,0,0,0);
  FUN_0081045c(param_7 << 0x10,3);
  FUN_0081045c(param_7 << 0x10,2);
  FUN_0081268d(puVar2,0);
  piVar1 = puVar2 + 2;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    (**(code **)*puVar2)(1);
  }
  return param_1;
}


/* ---- Mesh_Color @ 00813c2a ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Mesh_Color(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  float in_stack_00000014;
  float in_stack_00000018;
  float in_stack_0000001c;
  float in_stack_00000020;
  float in_stack_00000024;
  int in_stack_00000028;
  undefined1 local_38 [28];
  undefined4 local_1c;
  undefined1 local_18 [16];
  int local_8;
  
  iVar1 = param_1;
  FUN_0081108f();
  FUN_008123b5();
  FUN_00805a9d(in_stack_00000014 * _DAT_0081f37c,0,in_stack_00000018 * _DAT_0081f37c);
  local_1c = 0;
  FUN_00805cf1(in_stack_0000001c);
  FUN_00805e6e(in_stack_00000020);
  in_stack_0000001c = in_stack_00000024 * in_stack_00000024;
  local_8 = 0;
  in_stack_00000020 = 1.0 / in_stack_00000024;
  if (0 < *(int *)(param_1 + 0x10)) {
    in_stack_00000018 = 0.0;
    do {
      iVar2 = *(int *)(iVar1 + 0x7c) + (int)in_stack_00000018;
      if (in_stack_00000028 != 0) {
        if (in_stack_00000028 == 1) {
          FUN_00805f1f(&stack0x00000008,iVar2);
          fVar4 = (float10)FUN_00805fc1(local_18);
          in_stack_00000024 = (float)fVar4;
          if ((fVar4 < (float10)in_stack_0000001c) &&
             (fVar4 = (float10)FUN_00805fc1(iVar2 + 0x10), (float10)_DAT_0081f374 < fVar4)) {
            FUN_0080604f(local_38,(float)(fVar4 * ((float10)_DAT_0081f358 /
                                                   SQRT((float10)in_stack_00000024) -
                                                  (float10)in_stack_00000020)));
          }
        }
        else if (in_stack_00000028 == 2) {
          param_1 = 0;
          if (0 < *(int *)(iVar1 + 0x70)) {
            do {
              iVar3 = *(int *)(*(int *)(iVar1 + 0x6c) + param_1 * 4) * 0x50 + *(int *)(iVar1 + 0x7c)
              ;
              in_stack_0000001c = *(float *)(iVar3 + 0x24);
              in_stack_00000020 = *(float *)(iVar3 + 0x28);
              FUN_00805f1f(iVar3,iVar2);
              fVar4 = (float10)FUN_00805fc1(local_18);
              in_stack_00000024 = (float)fVar4;
              if ((fVar4 < (float10)in_stack_0000001c) &&
                 (fVar4 = (float10)FUN_00805fc1(iVar2 + 0x10), (float10)_DAT_0081f374 < fVar4)) {
                FUN_0080604f(iVar3 + 0x30,
                             (float)(fVar4 * ((float10)_DAT_0081f358 /
                                              SQRT((float10)in_stack_00000024) -
                                             (float10)in_stack_00000020)));
              }
              param_1 = param_1 + 1;
            } while (param_1 < *(int *)(iVar1 + 0x70));
          }
        }
        else if (in_stack_00000028 == 3) {
          FUN_00805f44(local_38);
        }
      }
      local_8 = local_8 + 1;
      in_stack_00000018 = (float)((int)in_stack_00000018 + 0x50);
    } while (local_8 < *(int *)(iVar1 + 0x10));
  }
  if (in_stack_00000028 == 2) {
    *(undefined4 *)(iVar1 + 0x70) = 0;
  }
  return iVar1;
}


/* ---- Mesh_Cube @ 00813e24 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int Mesh_Cube(uint param_1,float param_2,int param_3,uint param_4,float param_5,float param_6,
             float param_7)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  float local_7c [5];
  float local_68;
  float local_5c;
  float local_58;
  float local_54;
  float local_4c [16];
  int local_c;
  int local_8;
  
  iVar1 = operator_new(0xc4);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0080fcbd();
  }
  FUN_0080fe61(0x2f,0x400);
  FUN_00810905(4,0,_DAT_0081fccc,_DAT_0081fc20);
  *(undefined1 *)(*(int *)(iVar1 + 0x2c) + 2) = 1;
  FUN_008119c5(0x10000,0,0);
  FUN_00805a4d();
  local_4c[2] = 1.0;
  FUN_008102dc(0x10000);
  FUN_0081192e(local_7c,0,0);
  local_4c[0] = _DAT_0081f2ac;
  local_4c[1] = _DAT_0081f2ac;
  local_4c[2] = 0.0;
  local_4c[3] = 1.0;
  FUN_00810366(1,7);
  FUN_0081192e(local_7c,0,0);
  FUN_00805a4d();
  FUN_0081192e(local_7c,0,5);
  if ((param_4 & 8) == 0) {
    local_4c[0xc] = 1.0;
    local_4c[0xd] = 1.0;
    local_4c[0xe] = 1.0;
  }
  else {
    local_4c[0xc] = param_5;
    local_4c[0xd] = param_6;
    local_4c[0xe] = param_7;
  }
  local_8 = 0;
  local_4c[4] = 1.0;
  local_4c[5] = 1.0;
  local_4c[6] = 1.0;
  local_4c[7] = 1.0;
  do {
    local_4c[8] = (float)_DAT_0081fcb8;
    local_4c[9] = (float)_DAT_0081fcb8;
    local_4c[10] = (float)_DAT_0081fcb8;
    local_4c[0xb] = 1.0;
    *(undefined4 *)((int)local_4c + local_8 + 0x20) = _DAT_0081fcc8;
    FUN_00810873(local_4c + 4,local_4c + 8,0,0);
    FUN_00805a4d();
    *(undefined4 *)((int)local_4c + local_8) = 0x3f800000;
    FUN_0080e83c(0);
    if (1 < *(int *)((int)&param_1 + local_8)) {
      local_c = *(int *)((int)&param_1 + local_8) + -1;
      do {
        FUN_008119c5(0x10000,0x100,0);
        FUN_0081050f();
        FUN_0081192e(local_7c,0,0);
        FUN_0081192e(local_7c,5,5);
        local_c = local_c + -1;
      } while (local_c != 0);
    }
    FUN_0080ff59();
    local_8 = local_8 + 4;
  } while (local_8 < 0xc);
  FUN_00805a4d();
  local_7c[0] = _DAT_0081f2bc / (float)(int)param_1;
  local_68 = _DAT_0081f2bc / (float)(int)param_2;
  local_54 = _DAT_0081f2bc / (float)param_3;
  FUN_00810366(1,7);
  FUN_0081192e(local_7c,5,5);
  local_4c[0] = _DAT_0081fb64;
  local_4c[1] = _DAT_0081fb64;
  local_4c[2] = _DAT_0081fb64;
  local_4c[3] = 1.0;
  FUN_0081192e(local_7c,0,0);
  param_1 = 0;
  local_c = (-(uint)((param_4 & 1) != 0) & 0x1de) + 0x20;
  do {
    local_4c[4] = 0.0;
    local_4c[5] = 0.0;
    local_4c[6] = 0.0;
    local_4c[7] = 1.0;
    local_4c[8] = (float)_DAT_0081fcb8;
    local_4c[9] = (float)_DAT_0081fcb8;
    local_4c[10] = (float)_DAT_0081fcb8;
    local_4c[0xb] = 1.0;
    param_3 = (int)param_1 / 2;
    param_2 = (float)(int)((-(uint)((param_1 & 1) != 0) & 2) - 1);
    local_4c[param_3 + 4] = param_2 * _DAT_0081f2ac;
    local_4c[param_3 + 8] = _DAT_0081f2c4;
    FUN_00810873(local_4c + 4,local_4c + 8,0,0);
    FUN_00812049(0,0,0,local_c);
    FUN_0081050f();
    FUN_008103f3(0x10100 << ((byte)param_1 & 0x1f),2);
    pfVar3 = local_7c;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pfVar3 = 0.0;
      pfVar3 = pfVar3 + 1;
    }
    if (param_3 == 0) {
      local_68 = local_4c[0xd] * _DAT_0081f378;
      local_5c = param_2 * local_4c[0xe];
    }
    else if (param_3 == 1) {
      local_7c[0] = local_4c[0xc];
      local_58 = param_2 * local_4c[0xe] * _DAT_0081f378;
    }
    else {
      local_7c[0] = param_2 * local_4c[0xc] * _DAT_0081f378;
      local_68 = local_4c[0xd] * _DAT_0081f378;
    }
    local_4c[0] = (ABS(local_7c[0]) + ABS(local_5c)) * (float)_DAT_0081fba0;
    local_4c[1] = (ABS(local_68) + ABS(local_58)) * (float)_DAT_0081fba0;
    FUN_0081192e(local_7c,0,5);
    param_1 = param_1 + 1;
  } while ((int)param_1 < 6);
  if ((param_4 & 2) != 0) {
    FUN_00805a4d();
    local_4c[0] = local_4c[0xe];
    FUN_008102dc(0x100000);
    FUN_0081192e(local_7c,5,5);
    local_4c[0] = local_4c[0] + local_4c[0xc];
    FUN_008102dc(0x20000);
    FUN_0081192e(local_7c,5,5);
    local_4c[0] = local_4c[0] + local_4c[0xe];
    FUN_008102dc(0x200000);
    FUN_0081192e(local_7c,5,5);
  }
  if ((param_4 & 0x30) != 0) {
    iVar1 = Mesh_CollisionCube(iVar1,0,0,_DAT_0081fb64,_DAT_0081f2ac,_DAT_0081fb64,_DAT_0081f2ac,
                               _DAT_0081fb64,_DAT_0081f2ac,
                               ((int)param_4 >> 4 & 3U) - 1 | (int)param_4 >> 4 & 0xcU,1,1,1,0,0,0,0
                              );
  }
  FUN_00810366(1,7);
  if ((param_4 & 4) != 0) {
    FUN_00805a4d();
    local_4c[1] = 0.5;
    FUN_0081192e(local_7c,0,0);
  }
  FUN_008063b2(&param_5);
  FUN_0081192e(local_7c,0,0);
  return iVar1;
}


/* ---- FUN_0081429e @ 0081429e ---- */

void __fastcall FUN_0081429e(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)(param_1 + 0xc);
  iVar2 = 0xc;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + 4;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  *(undefined4 *)(param_1 + 0x388) = 0;
  *(undefined4 *)(param_1 + 0x38c) = 0;
  FUN_00804b25(*(undefined4 *)(param_1 + 0x39c),param_1 + 0x2c8,0,0);
  *(undefined4 *)(param_1 + 0xe4) = 0;
  return;
}


/* ---- FUN_008142e1 @ 008142e1 ---- */

int __thiscall FUN_008142e1(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = (int *)(param_1 + 8);
  while ((piVar2[1] != 0 || (*piVar2 != param_3))) {
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 4;
    if (0xb < iVar1) {
      return param_1 + 0xc0;
    }
  }
  param_1 = iVar1 * 0x10 + param_1;
  *(undefined4 *)(param_1 + 0xc) = param_4;
  *(undefined4 *)(param_1 + 4) = param_2;
  return param_1;
}


/* ---- FUN_0081431e @ 0081431e ---- */

int __thiscall FUN_0081431e(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = (int *)(param_1 + 4);
  while ((piVar2[2] == 0 || (*piVar2 != param_2))) {
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 4;
    if (0xb < iVar1) {
      return 0;
    }
  }
  return iVar1 * 0x10 + param_1;
}


/* ---- FUN_0081434b @ 0081434b ---- */

void FUN_0081434b(int param_1)

{
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + -1;
  return;
}


/* ---- FUN_00814358 @ 00814358 ---- */

void FUN_00814358(int *param_1,int param_2)

{
  if (param_1[2] < 4) {
    FUN_008023e2(*(undefined4 *)(*param_1 + 0x20));
  }
  else {
    FUN_008023a5(0);
    *(undefined4 *)(param_2 + 8) = 0;
    *(undefined4 *)(param_2 + 0xc) = 0x80;
    *(undefined4 *)(param_2 + 0x10) = 0x400;
    *(undefined4 *)(param_2 + 0x14) = 0x280;
  }
  return;
}


/* ---- FUN_0081439e @ 0081439e ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0081439e(int param_1,uint param_2,float *param_3,float *param_4)

{
  undefined4 *puVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  uint uVar6;
  undefined1 local_184 [372];
  undefined4 local_10;
  int local_c;
  float *local_8;
  
  if (param_3 == (float *)0x0) {
    param_3 = (float *)&DAT_0083f268;
  }
  if (param_4 == (float *)0x0) {
    param_4 = (float *)&DAT_0083f268;
  }
  FUN_0080221c();
  iVar2 = param_2 * 0xf0 + 0xe8 + param_1;
  local_10 = 2;
  FUN_00804b25(*(undefined4 *)(iVar2 + 0xd4),iVar2,local_184,0);
  puVar1 = (undefined4 *)(param_1 + 0xd4);
  FUN_0080479f(*puVar1,4,0,&local_8,0,3);
  fVar4 = _DAT_0081f2ac;
  param_2 = 0;
  do {
    uVar5 = (int)param_2 >> 1 ^ param_2;
    uVar6 = uVar5 & 1;
    if (uVar6 == 0) {
      local_c = 0;
    }
    else {
      local_c = *(int *)(DAT_0083f868 + 0x204);
    }
    *local_8 = (float)local_c - fVar4;
    uVar5 = uVar5 & 2;
    if (uVar5 == 0) {
      local_c = 0;
    }
    else {
      local_c = *(int *)(DAT_0083f868 + 0x208);
    }
    local_8[1] = (float)local_c - fVar4;
    local_8[2] = 1.0;
    local_8[3] = 0.0;
    if (uVar6 == 0) {
      fVar3 = *param_3;
    }
    else {
      fVar3 = param_3[2];
    }
    local_8[4] = fVar3;
    if (uVar5 == 0) {
      fVar3 = param_3[1];
    }
    else {
      fVar3 = param_3[3];
    }
    local_8[5] = fVar3;
    if (uVar6 == 0) {
      fVar3 = *param_4;
    }
    else {
      fVar3 = param_4[2];
    }
    local_8[6] = fVar3;
    if (uVar5 == 0) {
      fVar3 = param_4[1];
    }
    else {
      fVar3 = param_4[3];
    }
    local_8[7] = fVar3;
    local_8 = local_8 + 8;
    param_2 = param_2 + 1;
  } while ((int)param_2 < 4);
  FUN_00801856(*puVar1,0xffffffff,0xffffffff);
  FUN_008016d1(puVar1);
  return;
}


/* ---- FUN_0081451d @ 0081451d ---- */

undefined4 * __fastcall FUN_0081451d(undefined4 *param_1)

{
  FUN_008178b0();
  *param_1 = &PTR_FUN_0081fcd0;
  param_1[1] = 8;
  return param_1;
}


/* ---- FUN_00814536 @ 00814536 ---- */

void __fastcall FUN_00814536(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_0081fcd0;
  FUN_008178c4();
  return;
}


/* ---- Init_IPP_Viewport @ 00814541 ---- */

undefined4 Init_IPP_Viewport(undefined4 *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  piVar1 = param_1 + 2;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    (**(code **)*param_1)(1);
  }
  iVar2 = operator_new(0xc);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_0081451d();
  }
  return uVar3;
}


/* ---- Init_IPP_Blur @ 0081456d ---- */

undefined4 Init_IPP_Blur(undefined4 *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  piVar1 = param_1 + 2;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    (**(code **)*param_1)(1);
  }
  iVar2 = operator_new(0xc);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_0081451d();
  }
  return uVar3;
}


/* ---- Bitmap_Dots__Init_IPP_Copy @ 00814599 ---- */

void Bitmap_Dots__Init_IPP_Copy(void)

{
  return;
}


/* ---- Init_IPP_Color @ 0081459c ---- */

undefined4 Init_IPP_Color(undefined4 *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  piVar1 = param_1 + 2;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    (**(code **)*param_1)(1);
  }
  iVar2 = operator_new(0xc);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_0081451d();
  }
  return uVar3;
}


/* ---- Init_IPP_Merge @ 008145c8 ---- */

undefined4 Init_IPP_Merge(undefined4 *param_1,undefined4 *param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  piVar1 = param_1 + 2;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    (**(code **)*param_1)(1);
  }
  piVar1 = param_2 + 2;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    (**(code **)*param_2)(1);
  }
  iVar2 = operator_new(0xc);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_0081451d();
  }
  return uVar3;
}


/* ---- Init_IPP_Mask @ 00814602 ---- */

undefined4 Init_IPP_Mask(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  piVar1 = param_1 + 2;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    (**(code **)*param_1)(1);
  }
  piVar1 = param_2 + 2;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    (**(code **)*param_2)(1);
  }
  piVar1 = param_3 + 2;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    (**(code **)*param_3)(1);
  }
  iVar2 = operator_new(0xc);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_0081451d();
  }
  return uVar3;
}


/* ---- Init_IPP_Select @ 0081464a ---- */

undefined4 Init_IPP_Select(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = 0;
  if (0 < param_1) {
    do {
      puVar2 = *(undefined4 **)(&stack0x00000008 + iVar4 * 4);
      piVar1 = puVar2 + 2;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        (**(code **)*puVar2)(1);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < param_1);
  }
  iVar4 = operator_new(0xc);
  if (iVar4 != 0) {
    uVar3 = FUN_0081451d();
    return uVar3;
  }
  return 0;
}


/* ---- Exec_IPP_Viewport @ 00814683 ---- */

void Exec_IPP_Viewport(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined1 local_24 [28];
  undefined4 local_8;
  
  iVar1 = FUN_0081431e(param_1);
  if (iVar1 == 0) {
    FUN_0080e106(0);
    FUN_00818d42(param_2);
    iVar1 = FUN_008142e1(param_1,param_3,param_4);
    FUN_00814358(iVar1,local_24);
    local_8 = 0;
    FUN_008151b3(*(undefined4 *)(DAT_0140e128 + 0x1864));
  }
  *(int *)(DAT_0140e128 + 0xe4) = iVar1;
  return;
}


/* ---- Exec_IPP_Color @ 00814701 ---- */

void Exec_IPP_Color(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5
                   ,undefined4 param_6,undefined4 param_7)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_24 [24];
  undefined4 local_c;
  
  FUN_00818e4a(param_2);
  piVar1 = *(int **)(DAT_0140e128 + 0xe4);
  if (param_3 == 5) {
    param_3 = piVar1[2];
  }
  uVar2 = FUN_008142e1(param_1,param_3,param_7);
  FUN_00814358(uVar2,local_24);
  local_c = 0;
  FUN_00801037(local_24);
  iVar3 = param_5 * 0xf0;
  *(undefined4 *)(iVar3 + 0x748 + DAT_0140e128) = *(undefined4 *)(*piVar1 + 0x20);
  *(undefined4 *)(iVar3 + 0x6f8 + DAT_0140e128) = param_4;
  *(undefined4 *)(iVar3 + 0x700 + DAT_0140e128) = param_6;
  FUN_0081439e(param_5 + 6,0,0);
  FUN_008012d2();
  FUN_0081434b(piVar1);
  *(undefined4 *)(DAT_0140e128 + 0xe4) = uVar2;
  return;
}


/* ---- Exec_IPP_Merge @ 008147d6 ---- */

void Exec_IPP_Merge(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5
                   ,undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  undefined4 *puVar2;
  int extraout_ECX;
  int iVar3;
  undefined1 local_2c [24];
  undefined4 local_14;
  int *local_c [2];
  
  iVar1 = FUN_0081431e(param_1);
  iVar3 = extraout_ECX;
  if (iVar1 == 0) {
    iVar3 = 0;
    puVar2 = (undefined4 *)(extraout_ECX + 0xe4);
    do {
      *puVar2 = 0;
      FUN_00818ea3(param_2,iVar3);
      puVar2 = (undefined4 *)(DAT_0140e128 + 0xe4);
      local_c[iVar3] = (int *)*puVar2;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 2);
    iVar1 = FUN_008142e1(param_1,local_c[0][2],param_7);
    FUN_00814358(iVar1,local_2c);
    local_14 = 0;
    FUN_00801037(local_2c);
    iVar3 = param_4 * 0xf0;
    *(undefined4 *)(iVar3 + 0xec8 + DAT_0140e128) = *(undefined4 *)(*local_c[0] + 0x20);
    *(undefined4 *)(iVar3 + 0xecc + DAT_0140e128) = *(undefined4 *)(*local_c[1] + 0x20);
    *(int *)(iVar3 + 0xe78 + DAT_0140e128) = param_5 << 0x18;
    *(undefined4 *)(iVar3 + 0xe80 + DAT_0140e128) = param_6;
    FUN_0081439e(param_4 + 0xe,0,0);
    FUN_008012d2();
    FUN_0081434b(local_c[0]);
    FUN_0081434b(local_c[1]);
    iVar3 = DAT_0140e128;
  }
  *(int *)(iVar3 + 0xe4) = iVar1;
  return;
}


/* ---- Exec_IPP_Mask @ 008148fd ---- */

void Exec_IPP_Mask(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined1 local_30 [24];
  undefined4 local_18;
  int *local_10 [3];
  
  iVar3 = 0;
  iVar4 = 0;
  puVar1 = (undefined4 *)(DAT_0140e128 + 0xe4);
  do {
    *puVar1 = 0;
    FUN_00818ea3(param_2,iVar4);
    puVar1 = (undefined4 *)(DAT_0140e128 + 0xe4);
    local_10[iVar4] = (int *)*puVar1;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 3);
  uVar2 = FUN_008142e1(param_1,local_10[0][2],param_4);
  FUN_00814358(uVar2,local_30);
  local_18 = 0;
  FUN_00801037(local_30);
  *(undefined4 *)(DAT_0140e128 + 0x1738) = *(undefined4 *)(*local_10[2] + 0x20);
  *(undefined4 *)(DAT_0140e128 + 0x173c) = *(undefined4 *)(*local_10[1] + 0x20);
  FUN_0081439e(0x17,0,0);
  *(undefined4 *)(DAT_0140e128 + 0x1828) = *(undefined4 *)(*local_10[2] + 0x20);
  *(undefined4 *)(DAT_0140e128 + 0x1830) = *(undefined4 *)(*local_10[0] + 0x20);
  FUN_0081439e(0x18,0,0);
  FUN_008012d2();
  do {
    FUN_0081434b(local_10[iVar3]);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 3);
  *(undefined4 *)(DAT_0140e128 + 0xe4) = uVar2;
  return;
}


/* ---- Exec_IPP_Select @ 00814a0e ---- */

void Exec_IPP_Select(undefined4 param_1,undefined4 param_2)

{
  FUN_00818e4a(param_2);
  return;
}


/* ---- FUN_00814a1e @ 00814a1e ---- */

undefined4 * __fastcall FUN_00814a1e(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int local_c;
  undefined4 *local_8;
  
  FUN_008021c8();
  param_1[0x3a] = 0x300;
  param_1[0x6e] = 1;
  param_1[0x56] = 0xff0000;
  param_1[0x43] = 0x10;
  FUN_008021c8();
  param_1[0x76] = 0x632002;
  param_1[0xaa] = 1;
  param_1[0x92] = 0x2000;
  param_1[0x7f] = 0x10;
  param_1[0x8d] = 8;
  FUN_008021c8();
  param_1[0xe6] = 1;
  param_1[0xe2] = 1;
  param_1[0xe3] = 1;
  param_1[0xb2] = 0x20002;
  param_1[0xbd] = 0x18;
  param_1[0xbe] = 0x28;
  param_1[0xb6] = 0x101;
  param_1[0xb7] = 0x111;
  puVar4 = param_1 + 0xb2;
  puVar3 = param_1 + 0xee;
  for (iVar2 = 0x3c; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar3 = puVar3 + 1;
  }
  *(byte *)((int)param_1 + 0x3b9) = *(byte *)((int)param_1 + 0x3b9) | 0x20;
  FUN_008021c8();
  param_1[0x15e] = 1;
  param_1[0x15a] = 1;
  param_1[0x12a] = 0x20002;
  param_1[0x146] = 0xffffff;
  param_1[0x133] = 0x10;
  param_1[0x135] = 0x40;
  FUN_008021c8();
  puVar4 = param_1 + 0x12a;
  puVar3 = param_1 + 0x166;
  for (iVar2 = 0x3c; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar4 = param_1 + 0x1ab;
  local_8 = &DAT_0083f2a8;
  do {
    FUN_008021c8();
    puVar4[0x2b] = 1;
    *puVar4 = 0x10;
    puVar4[-9] = 0x20002;
    puVar4[2] = *local_8;
    puVar4[6] = 0x60;
    puVar4[-5] = 0x101;
    puVar4[0x27] = 1;
    puVar3 = puVar4 + -9;
    puVar5 = puVar4 + 0x1d7;
    for (iVar2 = 0x3c; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar4[0x1e0] = 0;
    puVar3 = local_8 + 1;
    puVar4[0x1e2] = 0x10;
    puVar4[0x1e3] = *local_8;
    puVar4[0x1dc] = 0x111;
    puVar4[0x208] = 1;
    puVar4 = puVar4 + 0x3c;
    local_8 = puVar3;
  } while ((int)puVar3 < 0x83f2c8);
  puVar4 = param_1 + 0x382;
  puVar3 = param_1 + 0x562;
  for (iVar2 = 0x3c; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar3 = puVar3 + 1;
  }
  param_1[0x56e] = 0x195;
  FUN_008021c8();
  param_1[0x59e] = 0x20002;
  param_1[0x5d2] = 1;
  param_1[0x5a7] = 0x10;
  param_1[0x5a9] = 0xb0;
  param_1[0x5aa] = 0x40;
  param_1[0x5ba] = 0x408040;
  param_1[0x5a2] = 0x101;
  param_1[0x5a3] = 0x101;
  param_1[0x5ce] = 1;
  param_1[0x5cf] = 1;
  FUN_008021c8();
  param_1[0x60e] = 1;
  param_1[0x5da] = 0x22002;
  param_1[0x5e3] = 0x10;
  param_1[0x5e5] = 0xb0;
  param_1[0x5e9] = 0xa0;
  param_1[0x5eb] = 0x40;
  param_1[0x5f6] = 0x408040;
  param_1[0x5f8] = 0xffffff;
  param_1[0x5de] = 0x101;
  param_1[0x5e0] = 0x101;
  param_1[0x60a] = 1;
  param_1[0x60c] = 1;
  iVar2 = operator_new(0x1c);
  if (iVar2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_0080e138();
  }
  param_1[0x616] = uVar1;
  FUN_00806b54();
  puVar4 = param_1 + 0x3a;
  puVar3 = *(undefined4 **)(param_1[0x616] + 0xc);
  for (iVar2 = 0x3c; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined4 *)(*(int *)(param_1[0x616] + 0xc) + 0xd8) = 3;
  iVar2 = *(int *)(param_1[0x616] + 0xc);
  uVar1 = FUN_00802664(iVar2);
  *(undefined4 *)(iVar2 + 0xd4) = uVar1;
  puVar4 = param_1 + 0x6f;
  iVar2 = 0x19;
  do {
    uVar1 = FUN_00802664(puVar4 + -0x35);
    *puVar4 = uVar1;
    puVar4 = puVar4 + 0x3c;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  iVar2 = 0;
  param_1[0x38] = 0;
  param_1[0x36] = 1;
  param_1[0x37] = 0;
  local_c = 0;
  puVar4 = param_1;
  do {
    local_8 = (undefined4 *)0x3;
    do {
      puVar3 = puVar4;
      if ((int)param_1[0x36] < 3) {
        uVar1 = 1;
      }
      else {
        uVar1 = *(undefined4 *)((int)&DAT_0083f280 + iVar2);
      }
      uVar1 = Bitmap_RenderTarget(*(undefined4 *)((int)&DAT_0083f278 + iVar2),
                                  *(undefined4 *)((int)&DAT_0083f27c + iVar2),uVar1);
      puVar3[1] = 0;
      puVar3[3] = 0;
      *puVar3 = uVar1;
      puVar3[2] = local_c;
      puVar4 = puVar3 + 4;
      local_8 = (undefined4 *)((int)local_8 + -1);
    } while (local_8 != (undefined4 *)0x0);
    local_c = local_c + 1;
    iVar2 = iVar2 + 0xc;
  } while (iVar2 < 0x30);
  *puVar4 = 0;
  puVar3[6] = 4;
  puVar3[7] = 0;
  uVar1 = FUN_0080166b(2,6);
  param_1[0x34] = 1;
  param_1[0x35] = uVar1;
  *(undefined1 *)(param_1 + 0x617) = 0;
  param_1[0x39] = 0;
  param_1[0x619] = 0;
  uVar1 = Bitmap_RenderTarget(9 - *(int *)(DAT_0083f868 + 0x10),8 - *(int *)(DAT_0083f868 + 0x10),1)
  ;
  param_1[0x618] = uVar1;
  return param_1;
}


/* ---- FUN_00814e2f @ 00814e2f ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
FUN_00814e2f(int param_1,int *param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
            float param_6)

{
  undefined1 local_34 [24];
  undefined4 local_1c;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  FUN_00814358(param_3,local_34);
  local_c = _DAT_0081f2ac;
  param_6 = param_6 * _DAT_0081f2ac;
  local_1c = 0;
  local_14 = _DAT_0081f2ac - param_6;
  *(undefined4 *)(param_1 + 0x568) = *(undefined4 *)(*param_2 + 0x20);
  *(undefined4 *)(param_1 + 0x518) = param_5;
  local_c = param_6 + local_c;
  local_10 = local_14;
  local_8 = local_c;
  FUN_00801037(local_34);
  FUN_0081439e(4,&local_14,0);
  FUN_008012d2();
  return;
}


/* ---- FUN_00814eaa @ 00814eaa ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00814eaa(int *param_1,undefined4 param_2,int param_3,undefined4 param_4,float param_5)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined1 local_30 [24];
  undefined4 local_18;
  longlong local_10;
  int local_8;
  
  FUN_00814358(param_2,local_30);
  iVar6 = 0;
  local_18 = 0;
  uVar4 = 0;
  do {
    uVar5 = uVar4 & 1;
    pfVar1 = (float *)(param_3 + uVar4 * 8);
    *pfVar1 = *pfVar1 / (float)*(int *)(*param_1 + 0x10) + (float)uVar5;
    pfVar1 = (float *)(param_3 + 4 + uVar4 * 8);
    uVar4 = uVar4 + 1;
    *pfVar1 = *pfVar1 / (float)*(int *)(*param_1 + 0x14) + (float)uVar5;
  } while ((int)uVar4 < 8);
  FUN_00801037(local_30);
  puVar7 = (undefined4 *)(local_8 + 0x38c);
  local_10 = (longlong)ROUND(param_5 * _DAT_0081fb78);
  iVar2 = (int)local_10;
  do {
    puVar7[-1] = *(undefined4 *)(*param_1 + 0x20);
    *puVar7 = *(undefined4 *)(*param_1 + 0x20);
    iVar3 = 0xff;
    if ((iVar2 < 0xff) && (iVar3 = 0, 0 < iVar2)) {
      iVar3 = iVar2;
    }
    puVar7[-0x15] = iVar3 << 0x18;
    FUN_0081439e(iVar6 + 2,param_3,param_3 + 0x10);
    param_3 = param_3 + 0x20;
    iVar6 = iVar6 + 1;
    puVar7 = puVar7 + 0x3c;
  } while (iVar6 < 2);
  FUN_008012d2();
  return;
}


/* ---- FUN_00814f91 @ 00814f91 ---- */

undefined4
FUN_00814f91(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  undefined4 uVar1;
  
  uVar1 = FUN_008142e1(param_1,param_6,param_7);
  FUN_00814eaa(param_2,uVar1,param_3,param_4,param_5);
  FUN_0081434b(param_2);
  return uVar1;
}


/* ---- FUN_00814fd2 @ 00814fd2 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall
FUN_00814fd2(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4,float param_5,
            undefined4 param_6,uint param_7,int param_8,undefined4 param_9)

{
  int iVar1;
  float *pfVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  float local_48 [16];
  undefined4 local_8;
  
  iVar5 = 0;
  do {
    iVar5 = iVar5 + 1;
    param_5 = param_5 * _DAT_0081f2ac;
    if (param_8 <= iVar5) break;
  } while (_DAT_0081f2ac < param_5);
  if (iVar5 != 0) {
    local_8 = param_1;
    do {
      iVar5 = iVar5 + -1;
      iVar4 = 4;
      pfVar2 = local_48;
      piVar3 = (int *)(&DAT_0083f2cc + (param_7 & 1) * 0x20);
      do {
        iVar1 = piVar3[-1];
        pfVar2[2] = (float)iVar1 * param_5;
        *pfVar2 = (float)iVar1 * param_5;
        iVar1 = *piVar3;
        piVar3 = piVar3 + 2;
        iVar4 = iVar4 + -1;
        pfVar2[3] = (float)iVar1 * param_5;
        pfVar2[1] = (float)iVar1 * param_5;
        pfVar2 = pfVar2 + 4;
      } while (iVar4 != 0);
      uVar6 = param_2;
      uVar7 = param_6;
      uVar8 = param_4;
      uVar9 = param_9;
      if (iVar5 != 0) {
        if ((param_7 & 2) == 0) {
          uVar7 = 0x3f800000;
        }
        uVar6 = 0;
        uVar8 = -(uint)(param_4 != 4) & param_4;
        uVar9 = 1;
      }
      param_3 = FUN_00814f91(uVar6,param_3,local_48,1,uVar7,uVar8,uVar9);
      param_5 = param_5 + param_5;
    } while (iVar5 != 0);
  }
  return param_3;
}


/* ---- FUN_008150af @ 008150af ---- */

undefined4 __thiscall FUN_008150af(undefined4 param_1,byte param_2)

{
  FUN_00814536();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


/* ---- Mesh_Bevel__Exec_IPP_Copy @ 008150ce ---- */

void Mesh_Bevel__Exec_IPP_Copy(void)

{
  return;
}


/* ---- Exec_IPP_Blur @ 008150d1 ---- */

void Exec_IPP_Blur(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 uVar1;
  
  FUN_00818e4a(param_2);
  uVar1 = FUN_00814fd2(param_1,*(undefined4 *)(DAT_0140e128 + 0xe4),param_3,param_4,param_5,param_6,
                       param_7,param_8);
  *(undefined4 *)(DAT_0140e128 + 0xe4) = uVar1;
  return;
}


/* ---- FUN_0081511e @ 0081511e ---- */

void FUN_0081511e(void)

{
  int iVar1;
  
  iVar1 = operator_new(0x1868);
  if (iVar1 != 0) {
    DAT_0140e128 = FUN_00814a1e();
    return;
  }
  DAT_0140e128 = 0;
  return;
}


/* ---- FUN_00815142 @ 00815142 ---- */

undefined4 * __fastcall FUN_00815142(undefined4 *param_1)

{
  FUN_008178b0();
  *param_1 = &PTR_FUN_0081fcdc;
  param_1[1] = 7;
  return param_1;
}


/* ---- FUN_0081515b @ 0081515b ---- */

void __fastcall FUN_0081515b(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_0081fcdc;
  FUN_008178c4();
  return;
}


/* ---- OpE0_Init @ 00815166 ---- */

undefined4 OpE0_Init(void)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = 0;
  do {
    puVar2 = *(undefined4 **)(&stack0x00000004 + iVar4 * 4);
    if (puVar2 != (undefined4 *)0x0) {
      piVar1 = puVar2 + 2;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        (**(code **)*puVar2)(1);
      }
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0xf);
  iVar4 = operator_new(0xc);
  if (iVar4 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_00815142();
  }
  return uVar3;
}


/* ---- Exec_Misc_Nop__OpE0_Exec @ 008151a1 ---- */

void Exec_Misc_Nop__OpE0_Exec(undefined4 param_1,undefined4 param_2)

{
  FUN_00818e4a(param_2);
  return;
}


/* ---- FUN_008151b3 @ 008151b3 ---- */

void FUN_008151b3(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 0x14960);
    if ((*(char *)(param_1 + 0x14fe9) != '\0') && (*(char *)(param_1 + 0x14fe9) != '\x01')) {
      *(undefined4 *)(param_1 + 0x14960) = 0;
    }
  }
  FUN_00817bf5();
  FUN_008198ce(param_1);
  FUN_00817134();
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14960) = uVar1;
  }
  return;
}


/* ---- FUN_0081520f @ 0081520f ---- */

undefined4 __thiscall FUN_0081520f(undefined4 param_1,byte param_2)

{
  FUN_0081515b();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


/* ---- Exec_Scene_Camera @ 0081522e ---- */

void Exec_Scene_Camera(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_84 [16];
  undefined1 local_44 [64];
  
  FUN_008063b2(&stack0x0000000c);
  FUN_00805c2c(local_44,param_2 + 0x94f0);
  puVar2 = local_84;
  puVar3 = (undefined4 *)(param_2 + 0x1478);
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return;
}


/* ---- Exec_Scene_Limb @ 0081526f ---- */

void Exec_Scene_Limb(undefined4 param_1,int param_2,float param_3,float param_4,float param_5,
                    undefined4 param_6,undefined4 param_7,undefined4 param_8,float param_9,
                    float param_10,byte param_11)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_13c [64];
  undefined4 local_fc [12];
  float local_cc;
  float local_c8;
  float local_c4;
  undefined4 local_bc [4];
  undefined1 local_ac [16];
  undefined4 local_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c [4];
  undefined1 local_6c [16];
  undefined4 local_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  float local_4c;
  float local_48;
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  float local_1c;
  float local_18;
  float local_14;
  undefined4 local_10;
  float local_c;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)(param_2 + 0x94f0);
  puVar5 = local_8;
  puVar4 = local_fc;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar4 = puVar4 + 1;
  }
  local_2c = param_6;
  local_28 = param_7;
  local_1c = -(param_3 - local_cc);
  local_24 = param_8;
  local_18 = -(param_4 - local_c8);
  local_14 = -(param_5 - local_c4);
  local_10 = 0;
  local_20 = 0;
  FUN_008061df(local_fc);
  FUN_00805a0d(&local_2c,&local_1c);
  FUN_00805a0d(&local_1c,&local_3c);
  fVar6 = (float10)FUN_00806202();
  fVar1 = (float)fVar6;
  FUN_0080620b();
  FUN_0080620b();
  FUN_0080620b();
  fVar2 = ((fVar1 * fVar1 + param_9 * param_9) - param_10 * param_10) / (fVar1 + fVar1);
  if (param_9 < fVar2 == (param_9 == fVar2)) {
    local_c = SQRT(param_9 * param_9 - fVar2 * fVar2);
  }
  else {
    local_c = 0.0;
  }
  local_9c = local_3c;
  uStack_98 = uStack_38;
  uStack_94 = uStack_34;
  uStack_90 = uStack_30;
  FUN_00805e97(&local_1c,fVar2);
  FUN_0080604f(&local_2c,local_c);
  FUN_0080620b();
  FUN_00805a0d(local_ac,&local_9c);
  local_8c = 0;
  local_88 = 0;
  local_84 = 0;
  local_80 = 0x3f800000;
  if ((param_9 < fVar2 == (param_9 == fVar2)) || ((param_11 & 1) != 0)) {
    local_5c = local_3c;
    uStack_58 = uStack_38;
    uStack_54 = uStack_34;
    uStack_50 = uStack_30;
    FUN_00805e97(&local_1c,fVar1 - fVar2);
    FUN_0080604f(&local_2c,-local_c);
    FUN_0080620b();
    FUN_00805a0d(local_6c,&local_5c);
    local_40 = 0x3f800000;
    local_4c = param_3 - local_cc;
    local_48 = param_4 - local_c8;
    local_44 = param_5 - local_c4;
  }
  else {
    puVar5 = local_bc;
    puVar4 = local_7c;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar4 = puVar4 + 1;
    }
    FUN_0080604f(&local_1c,-param_9 - param_10);
  }
  puVar5 = local_bc;
  puVar4 = local_8;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar4 = puVar4 + 1;
  }
  FUN_00805f44(&local_cc);
  FUN_00817bb7(local_7c,local_13c);
  FUN_00818ea3(param_2,0);
  FUN_00817bdc(local_13c);
  puVar5 = local_8;
  FUN_00805c2c(local_7c,local_fc);
  puVar4 = local_7c;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  FUN_00805f44(&local_cc);
  FUN_00817bb7(local_bc,local_13c);
  FUN_00818ea3(param_2,1);
  FUN_00817bdc(local_13c);
  puVar5 = local_fc;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *local_8 = *puVar5;
    puVar5 = puVar5 + 1;
    local_8 = local_8 + 1;
  }
  return;
}


/* ---- Exec_Scene_Rotate @ 00815555 ---- */

void Exec_Scene_Rotate(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
                      undefined4 param_5,int param_6)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 local_94 [8];
  undefined1 local_74 [16];
  undefined4 local_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 local_54 [4];
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_14 = param_3;
  local_8 = 0;
  local_10 = param_4;
  local_c = param_5;
  FUN_00806261();
  puVar2 = (undefined4 *)(param_2 + 0x94f0);
  puVar3 = puVar2;
  puVar4 = local_94;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  if ((param_6 != 0) && (param_6 == 1)) {
    local_44 = local_14;
    uStack_40 = local_10;
    uStack_3c = local_c;
    uStack_38 = local_8;
    FUN_00805a0d(&local_44,local_74);
    FUN_0080620b();
    FUN_00805a0d(local_54,&local_44);
    FUN_0080620b();
  }
  local_24 = local_64;
  uStack_20 = uStack_60;
  uStack_1c = uStack_5c;
  uStack_18 = uStack_58;
  puVar3 = local_54;
  puVar4 = puVar2;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  FUN_00818e4a(param_2);
  puVar3 = local_94;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}


/* ---- Exec_Scene_Sector @ 0081560e ---- */

void Exec_Scene_Sector(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  iVar1 = *(int *)(param_1 + 0x18);
  *(undefined4 *)(iVar1 + 0xdc) = *(undefined4 *)(param_2 + 0x9584);
  uVar2 = FUN_0080e106(0);
  *(undefined4 *)(iVar1 + 0x120) = uVar2;
  puVar4 = (undefined4 *)(param_2 + 0x94f0);
  puVar5 = (undefined4 *)(iVar1 + 0xe0);
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  *(undefined1 *)(iVar1 + 0x4e) = 0;
  *(int *)(param_2 + 0x9584) = iVar1;
  return;
}


/* ---- FUN_0081565b @ 0081565b ---- */

void FUN_0081565b(void)

{
  DAT_0149e6b0 = 0;
  DAT_0149e6ac = 0;
  return;
}


/* ---- FUN_0081566a @ 0081566a ---- */

void __fastcall FUN_0081566a(int param_1,int param_2,int *param_3,int param_4)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 local_54 [16];
  int local_14;
  int local_10;
  undefined4 *local_c;
  int local_8;
  
  local_c = &DAT_0149e6b8 + param_1 * 0x20;
  local_10 = 0x20;
  local_14 = param_1;
  local_8 = param_2;
  do {
    for (piVar1 = (int *)*local_c; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
      puVar5 = (undefined4 *)(*piVar1 + 0x1c);
      puVar6 = (undefined4 *)(local_8 + 0xdc);
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      iVar3 = *piVar1;
      if (*(undefined4 **)(iVar3 + 0xc) != (undefined4 *)0x0) {
        puVar5 = *(undefined4 **)(iVar3 + 0xc);
        puVar6 = (undefined4 *)(*(int *)(iVar3 + 0x10) * 0x10 + 0x1134 + param_4);
        for (iVar4 = (*(uint *)(iVar3 + 0x14) & 0xfffffff) << 2; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
        for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
          puVar5 = (undefined4 *)((int)puVar5 + 1);
          puVar6 = (undefined4 *)((int)puVar6 + 1);
        }
      }
      if ((*(int *)(*piVar1 + 4) != 0) && (*(int *)(*(int *)(*piVar1 + 4) + 0x38) == 0)) {
        FUN_00804b25(0xffffffff,0,local_8,0);
        puVar5 = (undefined4 *)(*piVar1 + 0x1c);
        puVar6 = (undefined4 *)(param_4 + 0x94f0);
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
        FUN_0081961c(param_4,*(int *)(*piVar1 + 4) + 0x4c);
      }
      if (piVar1[2] != 0) {
        if ((param_3 != (int *)0x0) && (local_14 == 1)) {
          puVar5 = (undefined4 *)(local_8 + 0xdc);
          puVar6 = local_54;
          for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar6 = *puVar5;
            puVar5 = puVar5 + 1;
            puVar6 = puVar6 + 1;
          }
          FUN_008064ec();
          FUN_00806305(local_54,*param_3 + 0x4c);
          *(undefined4 *)(local_8 + 0x10) = DAT_00aba0fc;
          *(undefined4 *)(local_8 + 0x14) = DAT_00aba100;
          *(undefined4 *)(local_8 + 0x18) = DAT_00aba104;
          *(undefined4 *)(local_8 + 0x1c) = DAT_00aba108;
          if (*(int *)(*piVar1 + 0x7c) != DAT_0149e6b0) {
            DAT_0149e6b0 = *(int *)(*piVar1 + 0x7c);
            FUN_00806890(*param_3 + 0x4c);
          }
          cVar2 = FUN_00806742(DAT_0149e6a0);
          DAT_012ba11c = (-(uint)(cVar2 != '\0') & 0xff800000) + 0x800000;
          cVar2 = FUN_00806742(6);
          if (cVar2 != '\0') goto LAB_00815819;
        }
        FUN_0080d456(piVar1[6],local_8,DAT_0149e6ac == piVar1[6]);
        DAT_0149e6ac = piVar1[6];
        FUN_00812bfa(piVar1[3],piVar1[4],local_8);
      }
LAB_00815819:
    }
    local_c = local_c + 1;
    local_10 = local_10 + -1;
    if (local_10 == 0) {
      return;
    }
  } while( true );
}


/* ---- FUN_0081583d @ 0081583d ---- */

undefined4 * __fastcall FUN_0081583d(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  FUN_008178b0();
  *param_1 = &PTR_FUN_0081fce8;
  param_1[1] = 3;
  FUN_00805cbc(0);
  param_1[7] = 0;
  param_1[9] = 0;
  param_1[8] = 0;
  puVar2 = param_1 + 0x49;
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[0x49] = 0x3f800000;
  param_1[0x4a] = 0x3f800000;
  param_1[0x4b] = 0x3f800000;
  param_1[0x52] = 0;
  param_1[0x12] = 0;
  param_1[0x37] = 0;
  *(undefined1 *)(param_1 + 0x13) = 0;
  return param_1;
}


/* ---- FUN_008158a6 @ 008158a6 ---- */

void __fastcall FUN_008158a6(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_0081fce8;
  FUN_008178c4();
  return;
}


/* ---- FUN_008158b1 @ 008158b1 ---- */

int __fastcall FUN_008158b1(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined1 local_44 [64];
  
  if (*(int *)(param_1 + 4) != 3) {
    if (*(int *)(param_1 + 4) == 6) {
      iVar2 = operator_new(0x14c);
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = FUN_0081583d();
      }
      *(int *)(iVar2 + 0x1c) = param_1;
      FUN_00805a4d();
      FUN_00811661();
      FUN_00810764(local_44,(undefined4 *)(iVar2 + 0x28));
      puVar4 = (undefined4 *)(iVar2 + 0x28);
      puVar5 = (undefined4 *)(*(int *)(iVar2 + 0x1c) + 0xa4);
      for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      *(int *)(iVar2 + 0x20) = *(int *)(iVar2 + 0x1c);
      piVar1 = (int *)(*(int *)(iVar2 + 0x1c) + 8);
      *piVar1 = *piVar1 + 1;
      param_1 = iVar2;
    }
    else {
      iVar2 = operator_new(0x14c);
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = FUN_0081583d();
      }
      *(int *)(iVar2 + 0x24) = param_1;
      puVar4 = (undefined4 *)(param_1 + 0x10);
      puVar5 = (undefined4 *)(iVar2 + 0x28);
      for (iVar3 = 8; param_1 = iVar2, iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
    }
  }
  return param_1;
}


/* ---- Init_Scene_Scene @ 00815954 ---- */

int Init_Scene_Scene(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if (param_1 == 0) {
    iVar1 = operator_new(0x14c);
    if (iVar1 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = FUN_0081583d();
    }
  }
  else {
    iVar2 = FUN_008158b1();
    puVar3 = (undefined4 *)&stack0x00000008;
    puVar4 = (undefined4 *)(iVar2 + 0x124);
    for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  return iVar2;
}


/* ---- Init_Scene_Add @ 00815998 ---- */

undefined4 Init_Scene_Add(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 local_8;
  
  iVar1 = operator_new(0x14c);
  iVar4 = 0;
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = FUN_0081583d();
  }
  if (0 < param_1) {
    do {
      uVar2 = FUN_008158b1();
      puVar3 = (undefined4 *)FUN_00806b54();
      iVar4 = iVar4 + 1;
      *puVar3 = uVar2;
    } while (iVar4 < param_1);
  }
  return local_8;
}


/* ---- Init_Scene_Multiply @ 008159ee ---- */

int Init_Scene_Multiply(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 in_stack_0000002c;
  
  uVar1 = FUN_008158b1();
  iVar2 = operator_new(0x14c);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_0081583d();
  }
  puVar3 = (undefined4 *)FUN_00806b54();
  *puVar3 = uVar1;
  *(undefined4 *)(iVar2 + 0x148) = in_stack_0000002c;
  puVar3 = (undefined4 *)&stack0x00000008;
  puVar5 = (undefined4 *)(iVar2 + 0x124);
  for (iVar4 = 9; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar5 = puVar5 + 1;
  }
  return iVar2;
}


/* ---- Init_Scene_Transform @ 00815a46 ---- */

void Init_Scene_Transform
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
               undefined4 param_9,undefined4 param_10)

{
  Init_Scene_Multiply(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,0);
  return;
}


/* ---- Init_Scene_Light @ 00815a7c ---- */

int Init_Scene_Light(void)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 in_stack_0000001c;
  undefined4 in_stack_00000020;
  undefined4 in_stack_00000024;
  undefined4 in_stack_00000028;
  undefined4 in_stack_0000002c;
  
  iVar1 = operator_new(0x14c);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0081583d();
  }
  puVar2 = (undefined4 *)operator_new(0x1c);
  *(undefined4 **)(iVar1 + 0x48) = puVar2;
  puVar4 = (undefined4 *)(iVar1 + 0x130);
  for (iVar3 = 6; register0x00000010 = (BADSPACEBASE *)((int)register0x00000010 + 4), iVar3 != 0;
      iVar3 = iVar3 + -1) {
    *puVar4 = *(undefined4 *)register0x00000010;
    puVar4 = puVar4 + 1;
  }
  puVar2[5] = 0;
  *puVar2 = in_stack_0000001c;
  puVar2[1] = in_stack_00000020;
  puVar2[2] = in_stack_00000024;
  puVar2[3] = in_stack_00000028;
  puVar2[4] = in_stack_0000002c;
  return iVar1;
}


/* ---- Init_Scene_Camera @ 00815ae1 ---- */

void Init_Scene_Camera(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar1 = operator_new(0x14c);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0081583d();
  }
  puVar3 = (undefined4 *)(iVar1 + 0x124);
  for (iVar2 = 9; register0x00000010 = (BADSPACEBASE *)((int)register0x00000010 + 4), iVar2 != 0;
      iVar2 = iVar2 + -1) {
    *puVar3 = *(undefined4 *)register0x00000010;
    puVar3 = puVar3 + 1;
  }
  return;
}


/* ---- Init_Scene_Limb @ 00815b14 ---- */

undefined4 Init_Scene_Limb(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  iVar1 = operator_new(0x14c);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0081583d();
  }
  uVar3 = FUN_008158b1();
  puVar4 = (undefined4 *)FUN_00806b54();
  *puVar4 = uVar3;
  uVar3 = FUN_008158b1();
  puVar4 = (undefined4 *)FUN_00806b54();
  *puVar4 = uVar3;
  return uVar2;
}


/* ---- Init_Scene_Walk @ 00815b6c ---- */

undefined4 Init_Scene_Walk(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  iVar1 = operator_new(0x14c);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0081583d();
  }
  uVar3 = FUN_008158b1();
  puVar4 = (undefined4 *)FUN_00806b54();
  *puVar4 = uVar3;
  return uVar2;
}


/* ---- Init_Scene_Rotate @ 00815bab ---- */

undefined4 Init_Scene_Rotate(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  iVar1 = operator_new(0x14c);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0081583d();
  }
  uVar3 = FUN_008158b1();
  puVar4 = (undefined4 *)FUN_00806b54();
  *puVar4 = uVar3;
  return uVar2;
}


/* ---- Init_Scene_Physic @ 00815bea ---- */

undefined4 Init_Scene_Physic(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  iVar1 = operator_new(0x14c);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0081583d();
  }
  if (param_1 != 0) {
    uVar3 = FUN_008158b1();
    puVar4 = (undefined4 *)FUN_00806b54();
    *puVar4 = uVar3;
  }
  return uVar2;
}


/* ---- Init_Scene_Sector @ 00815c2d ---- */

int Init_Scene_Sector(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  iVar1 = operator_new(0x14c);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0081583d();
  }
  uVar2 = FUN_008158b1();
  puVar3 = (undefined4 *)FUN_00806b54();
  *puVar3 = uVar2;
  *(undefined1 *)(iVar1 + 0x4c) = 1;
  return iVar1;
}


/* ---- Init_Scene_Portal @ 00815c70 ---- */

int Init_Scene_Portal(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = param_2 + 2;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    (**(code **)*param_2)(1);
  }
  piVar1 = param_3 + 2;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    (**(code **)*param_3)(1);
  }
  if (param_4 != (undefined4 *)0x0) {
    piVar1 = param_4 + 2;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      (**(code **)*param_4)(1);
    }
  }
  if (param_1 == 0) {
    iVar2 = operator_new(0x14c);
    if (iVar2 == 0) {
      param_1 = 0;
    }
    else {
      param_1 = FUN_0081583d();
    }
  }
  return param_1;
}


/* ---- FUN_00815cc6 @ 00815cc6 ---- */

undefined4 * __fastcall
FUN_00815cc6(int param_1,int param_2,undefined4 param_3,int param_4,undefined4 *param_5)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined1 local_20 [16];
  int local_10;
  int local_c;
  float local_8;
  
  local_10 = param_2;
  local_c = param_1;
  if (((param_4 == 1) && (*(int *)(param_1 + 0x133c) != 0)) &&
     (0 < *(int *)(*(int *)(param_1 + 0x133c) + 0xb0))) {
    FUN_00805f1f(param_1 + 0x9520,param_1 + 0x14a8);
    iVar5 = *(int *)(*(int *)(param_1 + 0x133c) + 0xb0);
    local_8 = (float)(iVar5 * iVar5);
    fVar7 = (float10)FUN_00805fc1(local_20);
    if ((float10)local_8 < fVar7) {
      return (undefined4 *)0x0;
    }
  }
  puVar3 = (undefined4 *)FUN_00805784(0x84);
  iVar2 = local_c;
  puVar3[3] = 0;
  puVar3[2] = param_3;
  puVar3[1] = param_2;
  puVar3[6] = param_4;
  puVar6 = (undefined4 *)(param_1 + 0x94f0);
  puVar4 = puVar3 + 7;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar4 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar4 = puVar4 + 1;
  }
  if (param_5 != (undefined4 *)0x0) {
    puVar6 = puVar3 + 0x17;
    for (iVar5 = 8; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = *param_5;
      param_5 = param_5 + 1;
      puVar6 = puVar6 + 1;
    }
  }
  uVar1 = *(undefined4 *)(local_c + 0x953c);
  puVar3[0x20] = 0;
  puVar3[0x1f] = uVar1;
  if (param_4 == 2) {
    *puVar3 = *(undefined4 *)(local_c + 0x9538);
    *(undefined4 *)(local_c + 0x9538) = puVar3;
  }
  else {
    *puVar3 = *(undefined4 *)(local_c + 0x9534);
    *(undefined4 *)(local_c + 0x9534) = puVar3;
    puVar3[3] = 0;
    puVar3[4] = *(undefined4 *)(local_10 + 0x44);
    iVar5 = *(int *)(local_10 + 0x48);
    puVar3[5] = iVar5;
    if (0 < iVar5) {
      puVar4 = (undefined4 *)FUN_00805784(iVar5 << 4);
      puVar3[3] = puVar4;
      puVar6 = (undefined4 *)(puVar3[4] * 0x10 + 0x1134 + iVar2);
      for (iVar5 = (puVar3[5] & 0xfffffff) << 2; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar4 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar4 = puVar4 + 1;
      }
      for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
        *(undefined1 *)puVar4 = *(undefined1 *)puVar6;
        puVar6 = (undefined4 *)((int)puVar6 + 1);
        puVar4 = (undefined4 *)((int)puVar4 + 1);
      }
    }
  }
  return puVar3;
}


/* ---- FUN_00815e01 @ 00815e01 ---- */

void __fastcall FUN_00815e01(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 local_b4 [16];
  undefined4 local_74 [16];
  undefined4 local_34 [8];
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = param_2;
  local_8 = param_1;
  if (param_3 == 0) {
    puVar5 = (undefined4 *)(param_2 + 0x94f0);
    puVar4 = local_74;
  }
  else {
    FUN_008063b2(param_3);
    puVar4 = (undefined4 *)(param_2 + 0x94f0);
    FUN_00805c2c(local_74,puVar4);
    puVar5 = puVar4;
    puVar6 = local_74;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar5 = local_b4;
  }
  iVar3 = local_8;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar4 = puVar4 + 1;
  }
  local_10 = *(int *)(iVar3 + 0x6c);
  param_3 = 0;
  if (0 < *(int *)(iVar3 + 0x6c)) {
    do {
      local_14 = FUN_0080e106(param_3);
      if ((*(int *)(local_14 + 0x18) == 0) ||
         ((iVar2 = *(int *)(*(int *)(local_14 + 0x18) + 4), iVar2 != 6 && (iVar2 != 9)))) {
        FUN_00818d42(local_c);
      }
      else {
        iVar2 = *(int *)(local_8 + 0x18);
        if (*(int *)(iVar2 + 0x10) == 0) {
          puVar4 = (undefined4 *)(iVar2 + 0x28);
          puVar5 = local_34;
          for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
          }
        }
        else {
          puVar4 = (undefined4 *)(*(int *)(*(int *)(iVar2 + 0xc) + param_3 * 4) + 0x28);
          puVar5 = local_34;
          for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
          }
          iVar2 = *(int *)(*(int *)(iVar2 + 0xc) + param_3 * 4);
        }
        uVar1 = *(undefined4 *)(iVar2 + 0x20);
        FUN_0080661f((undefined4 *)(param_2 + 0x94f0));
        FUN_00815cc6(uVar1,1,local_34);
      }
      param_3 = param_3 + 1;
    } while (param_3 < local_10);
  }
  puVar4 = local_74;
  puVar5 = (undefined4 *)(param_2 + 0x94f0);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  return;
}


/* ---- Exec_Scene_Scene @ 00815f11 ---- */

void Exec_Scene_Scene(void)

{
  FUN_00815e01(&stack0x0000000c);
  return;
}


/* ---- Exec_Scene_Add @ 00815f27 ---- */

void Exec_Scene_Add(void)

{
  FUN_00815e01(0);
  return;
}


/* ---- Exec_Scene_Multiply @ 00815f3b ---- */

void Exec_Scene_Multiply(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int in_stack_00000030;
  undefined4 local_c4 [16];
  undefined1 local_84 [64];
  undefined4 local_44 [16];
  
  puVar2 = (undefined4 *)(param_2 + 0x94f0);
  puVar3 = puVar2;
  puVar4 = local_c4;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  FUN_008063b2(&stack0x0000000c);
  if (0 < in_stack_00000030) {
    do {
      FUN_00815e01(0);
      FUN_00805c2c(local_84,puVar2);
      in_stack_00000030 = in_stack_00000030 + -1;
      puVar3 = local_44;
      puVar4 = puVar2;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
    } while (in_stack_00000030 != 0);
  }
  puVar3 = local_c4;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}


/* ---- Exec_Scene_Transform @ 00815fb0 ---- */

void Exec_Scene_Transform(void)

{
  FUN_00815e01(&stack0x0000000c);
  return;
}


/* ---- Exec_Scene_Light @ 00815fc6 ---- */

void Exec_Scene_Light(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                     undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                     undefined4 param_13)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 local_a8 [16];
  undefined4 local_68 [16];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_1c = param_3;
  local_28 = 0x3f800000;
  local_18 = param_4;
  local_24 = 0x3f800000;
  local_14 = param_5;
  local_20 = 0x3f800000;
  local_10 = param_6;
  local_c = param_7;
  local_8 = param_8;
  FUN_008063b2(&local_28);
  puVar4 = (undefined4 *)(param_2 + 0x94f0);
  FUN_00805c2c(local_68,puVar4);
  puVar2 = puVar4;
  puVar5 = local_68;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar5 = puVar5 + 1;
  }
  puVar2 = local_a8;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  iVar1 = FUN_00815cc6(0,2,0);
  puVar2 = local_68;
  puVar4 = (undefined4 *)(param_2 + 0x94f0);
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = (undefined4 *)FUN_00805784(0x1c);
  *(undefined4 **)(iVar1 + 0x80) = puVar2;
  *puVar2 = param_9;
  *(undefined4 *)(*(int *)(iVar1 + 0x80) + 4) = param_10;
  *(undefined4 *)(*(int *)(iVar1 + 0x80) + 8) = param_11;
  *(undefined4 *)(*(int *)(iVar1 + 0x80) + 0xc) = param_12;
  *(undefined4 *)(*(int *)(iVar1 + 0x80) + 0x10) = param_13;
  *(undefined4 *)(*(int *)(iVar1 + 0x80) + 0x14) = *(undefined4 *)(param_2 + 0x133c);
  *(undefined4 *)(*(int *)(iVar1 + 0x80) + 0x18) = *(undefined4 *)(param_2 + 0x9580);
  return;
}


/* ---- Exec_Scene_Walk @ 008160d1 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Exec_Scene_Walk(undefined4 param_1,int param_2,uint param_3,float param_4,float param_5,
                    float param_6,float param_7,int param_8,int param_9,float param_10,
                    undefined4 *param_11,float param_12,float param_13,float param_14,float param_15
                    ,undefined4 param_16,undefined4 param_17,int param_18)

{
  undefined4 uVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  float *pfVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  undefined4 *puVar10;
  float fVar11;
  undefined4 *puVar12;
  float10 fVar13;
  float10 fVar14;
  float in_stack_000000a0;
  float in_stack_000000a4;
  float in_stack_000000a8;
  undefined4 local_2d0 [32];
  undefined4 local_250 [16];
  float local_210 [32];
  undefined4 local_190 [32];
  float local_110;
  float fStack_10c;
  float fStack_108;
  float fStack_104;
  undefined4 local_100 [4];
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_dc;
  undefined4 local_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  float *local_c0;
  undefined4 local_bc [5];
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  float local_78;
  float local_74;
  int local_70;
  float local_68;
  int local_5c [3];
  float local_50;
  float local_4c;
  int local_48;
  int local_44;
  int local_40;
  float local_3c;
  float local_38;
  int local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  float local_1c;
  float fStack_18;
  int local_14;
  undefined4 *local_10;
  float local_c;
  undefined4 *local_8;
  
  local_5c[0] = param_8;
  local_5c[1] = param_9;
  local_74 = param_10;
  local_70 = (int)param_11;
  local_38 = (float)(int)ROUND(param_12 * _DAT_0081fc24);
  local_34 = (int)ROUND(param_13 * _DAT_0081fc24);
  local_4c = (float)(int)ROUND(param_14 * _DAT_0081fc24);
  if ((int)local_38 <= (int)ROUND(param_14 * _DAT_0081fc24)) {
    local_4c = local_38;
  }
  local_48 = (int)ROUND(param_15 * _DAT_0081fc24);
  if (local_34 <= (int)ROUND(param_15 * _DAT_0081fc24)) {
    local_48 = local_34;
  }
  DAT_0149e130 = FUN_00817b57();
  if (((*(char *)(DAT_0149e130 + 0x10) != '\0') || ((param_3 & 0x100) != 0)) ||
     (*(int *)(param_2 + 0x14ec) != 0)) {
    puVar10 = (undefined4 *)(param_2 + 0x94f0);
    puVar12 = local_bc;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar12 = puVar12 + 1;
    }
    if ((param_3 & 2) != 0) {
      FUN_0081b115();
    }
    iVar7 = DAT_0149e130;
    local_30 = 0;
    local_2c = 0;
    local_28 = 0;
    local_24 = 0;
    *(undefined4 *)(DAT_0149e130 + 0x5d8) = 0;
    *(undefined4 *)(iVar7 + 0x5dc) = 0;
    *(undefined4 *)(iVar7 + 0x5e0) = 0;
    *(undefined4 *)(iVar7 + 0x5e4) = 0;
    *(int *)(DAT_0149e130 + 0x60c) = (int)param_4 * 2;
    if (0 < (int)param_4) {
      param_11 = &param_17;
      local_10 = (undefined4 *)(_DAT_0081f2bc / (float)(int)param_4);
      param_9 = 0x594;
      local_c = param_4;
      iVar7 = 0;
      do {
        puVar10 = (undefined4 *)(iVar7 + 0x610 + DAT_0149e130);
        *puVar10 = param_11[-1];
        puVar10[3] = 0;
        uVar1 = *param_11;
        puVar10[2] = param_11[1];
        puVar10[1] = uVar1;
        FUN_00805efa();
        local_14 = 0;
        puVar10 = (undefined4 *)(iVar7 + 0x514 + DAT_0149e130);
        *puVar10 = local_20;
        puVar10[1] = local_1c;
        puVar10[2] = fStack_18;
        puVar10[3] = 0;
        iVar4 = DAT_0149e130 + iVar7;
        *(undefined4 *)(iVar4 + 0x494) = *(undefined4 *)(iVar4 + 0x514);
        *(undefined4 *)(iVar4 + 0x498) = *(undefined4 *)(iVar4 + 0x518);
        *(undefined4 *)(iVar4 + 0x49c) = *(undefined4 *)(iVar4 + 0x51c);
        *(undefined4 *)(iVar4 + 0x4a0) = *(undefined4 *)(iVar4 + 0x520);
        *(float *)(param_9 + DAT_0149e130) = local_38;
        FUN_0081a939();
        param_9 = param_9 + 4;
        param_11 = param_11 + 3;
        local_c = (float)((int)local_c - 1);
        *(float *)(DAT_0149e130 + 0x5d8) =
             (float)local_10 * *(float *)(iVar7 + 0x610 + DAT_0149e130) +
             *(float *)(DAT_0149e130 + 0x5d8);
        *(float *)(DAT_0149e130 + 0x5e0) =
             (float)local_10 * *(float *)(iVar7 + 0x618 + DAT_0149e130) +
             *(float *)(DAT_0149e130 + 0x5e0);
        iVar7 = iVar7 + 0x10;
      } while (local_c != 0.0);
    }
    *(undefined4 *)((int)param_4 * 0x80 + -0x6c + DAT_0149e130) = 1;
    FUN_0081a939();
    *(undefined4 *)(DAT_0149e130 + 0x414) = 1;
    *(undefined4 *)(DAT_0149e130 + 0x5b4) = *(undefined4 *)(param_2 + 0x14d8);
    iVar7 = DAT_0149e130;
    puVar10 = (undefined4 *)(DAT_0149e130 + 0x5cc);
    *(undefined4 *)(DAT_0149e130 + 0x5c8) = local_8c;
    *puVar10 = local_88;
    *(undefined4 *)(iVar7 + 0x5d0) = local_84;
    *(undefined4 *)(iVar7 + 0x5d4) = local_80;
    *(undefined4 *)(DAT_0149e130 + 0x5e8) = 0;
    *(undefined4 *)(DAT_0149e130 + 0x5ec) = 0;
    fVar11 = param_4;
    if (0 < (int)param_4) {
      do {
        FUN_00805f66();
        fVar11 = (float)((int)fVar11 - 1);
      } while (fVar11 != 0.0);
    }
  }
  param_15 = *(float *)(DAT_0149e130 + 0x5e8);
  param_9 = 0;
  local_30 = 0;
  param_18 = *(int *)(DAT_0149e130 + 0x5ec);
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_8 = (undefined4 *)0x0;
  if (0 < (int)param_4) {
    iVar7 = local_5c[(int)param_15];
    local_c = (float)(int)(&local_38)[(int)param_15];
    iVar4 = 0;
    param_13 = 2.00105e-42;
    do {
      fVar13 = (float10)*(int *)((int)param_13 + DAT_0149e130) / (float10)local_c;
      if (fVar13 < (float10)_DAT_0081f2bc) {
        if (fVar13 < (float10)_DAT_0081f374 != (fVar13 == (float10)_DAT_0081f374)) {
          fVar13 = (float10)0;
        }
      }
      else {
        fVar13 = (float10)1;
      }
      if (param_9 < iVar7) {
        local_8 = (undefined4 *)(float)((float10)(float)local_8 + fVar13);
      }
      if (in_stack_000000a8 == 0.0) {
        *(undefined4 *)((int)local_210 + iVar4) = 0;
        pfVar5 = (float *)((int)local_210 + iVar4 + 0xc);
        fVar14 = (float10)fsin((float10)_DAT_0081fd08 * fVar13);
        *(float *)((int)local_210 + iVar4 + 4) = (float)(fVar14 * (float10)_DAT_0081fb88);
        *(undefined4 *)((int)local_210 + iVar4 + 8) = 0;
      }
      else {
        local_10 = (undefined4 *)(float)(int)param_15;
        pfVar5 = (float *)((int)local_210 + iVar4);
        FUN_00817d55();
        if (*(float *)((int)pfVar5 + DAT_0149e130 + (0x610 - (int)local_210)) < _DAT_0081f374) {
          *pfVar5 = -*pfVar5;
        }
        if (*(float *)(iVar4 + 0x618 + DAT_0149e130) < _DAT_0081f374) {
          *(float *)((int)local_210 + iVar4 + 8) = -*(float *)((int)local_210 + iVar4 + 8);
        }
        pfVar5 = (float *)((int)local_210 + iVar4 + 0xc);
        fVar13 = (float10)*pfVar5 - (float10)(float)local_10;
      }
      *pfVar5 = (float)fVar13;
      FUN_00805957();
      *(undefined4 *)((int)local_190 + iVar4 + 0xc) = 0x3f800000;
      FUN_00805f44();
      param_9 = param_9 + 1;
      param_13 = (float)((int)param_13 + 4);
      iVar4 = iVar4 + 0x10;
    } while (param_9 < (int)param_4);
  }
  FUN_0080600c();
  local_bc[0] = 0;
  local_8c = local_30;
  local_bc[1] = 0;
  local_88 = local_2c;
  local_84 = local_28;
  local_bc[2] = 0;
  local_bc[3] = 0;
  local_9c = 0;
  local_98 = 0;
  local_94 = 0;
  local_90 = 0;
  local_80 = 0x3f800000;
  if (0 < (int)param_4) {
    in_stack_000000a8 = param_4;
    do {
      FUN_00805f1f();
      FUN_0080604f();
      FUN_0080604f();
      FUN_0080604f();
      in_stack_000000a8 = (float)((int)in_stack_000000a8 - 1);
    } while (in_stack_000000a8 != 0.0);
  }
  if ((param_3 >> 2 & 3) == 0) {
    local_bc[0] = *(undefined4 *)(param_2 + 0x94f0);
    local_bc[1] = *(undefined4 *)(param_2 + 0x94f4);
    local_bc[2] = *(undefined4 *)(param_2 + 0x94f8);
    local_bc[3] = *(undefined4 *)(param_2 + 0x94fc);
    local_bc[4] = *(undefined4 *)(param_2 + 0x9500);
    uStack_a8 = *(undefined4 *)(param_2 + 0x9504);
    uStack_a4 = *(undefined4 *)(param_2 + 0x9508);
    uStack_a0 = *(undefined4 *)(param_2 + 0x950c);
    local_9c = *(undefined4 *)(param_2 + 0x9510);
    local_98 = *(undefined4 *)(param_2 + 0x9514);
    local_94 = *(undefined4 *)(param_2 + 0x9518);
    local_90 = *(undefined4 *)(param_2 + 0x951c);
  }
  param_13 = (float)((int)param_15 * 4);
  param_11 = (undefined4 *)local_5c[(int)param_15];
  fVar11 = ((float)param_18 + (float)local_8) / (float)(int)param_11;
  if (_DAT_0081f108 <= fVar11) {
    fVar11 = fVar11 - _DAT_0081f108;
  }
  if (_DAT_0081f2bc <= fVar11) {
    fVar11 = fVar11 - _DAT_0081f2bc;
  }
  local_c0 = (float *)(param_2 + 0x12e4);
  local_110 = *local_c0;
  fStack_10c = *(float *)(param_2 + 0x12e8);
  fStack_108 = *(float *)(param_2 + 0x12ec);
  fStack_104 = *(float *)(param_2 + 0x12f0);
  *local_c0 = ((float)(int)param_15 + fVar11) * _DAT_0081f2ac;
  *(undefined4 *)(param_2 + 0x12e8) = 0;
  *(undefined4 *)(param_2 + 0x12ec) = 0;
  *(undefined4 *)(param_2 + 0x12f0) = 0;
  iVar7 = *(int *)(param_2 + 0x14d8) - *(int *)(DAT_0149e130 + 0x5b4);
  *(int *)(DAT_0149e130 + 0x5b4) = *(int *)(param_2 + 0x14d8);
  if (iVar7 < 0) {
    iVar7 = 0;
  }
  local_10 = (undefined4 *)(param_2 + 0x94f0);
  puVar10 = local_10;
  puVar12 = local_100;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar12 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar12 = puVar12 + 1;
  }
  if (0 < *(int *)(DAT_0149e130 + 0x608)) {
    FUN_00805efa();
  }
  local_dc = 0;
  FUN_0080620b();
  local_f0 = 0;
  local_ec = 0x3f800000;
  local_e8 = 0;
  local_e4 = 0;
  FUN_00805a0d();
  if (0 < (int)param_4) {
    fVar11 = (&local_38)[(int)param_15];
    iVar4 = 0x594;
    fVar9 = param_4;
    do {
      piVar6 = (int *)(DAT_0149e130 + iVar4);
      if (*piVar6 < (int)fVar11) {
        *piVar6 = *piVar6 + iVar7;
      }
      iVar4 = iVar4 + 4;
      fVar9 = (float)((int)fVar9 - 1);
    } while (fVar9 != 0.0);
  }
  local_3c = 0.0;
  in_stack_000000a8 = (float)((param_18 + 1) % (int)param_11);
  param_9 = 0;
  local_c = in_stack_000000a8;
  if (0 < (int)param_4) {
    local_44 = -0xc24 - param_2;
    local_8 = (undefined4 *)(param_2 + 0x1234);
    local_40 = 0x594;
    iVar7 = 0;
    do {
      FUN_00806305();
      FUN_00805f66();
      local_1c = 0.0;
      fVar13 = (float10)FUN_00806202();
      puVar10 = local_8;
      if (((float10)local_3c < fVar13) &&
         ((int)(&local_38)[(int)param_15] <= *(int *)(local_40 + DAT_0149e130))) {
        local_3c = (float)fVar13;
        local_c = (float)param_9;
      }
      puVar12 = local_8 + 1;
      *(undefined4 *)((int)local_2d0 + iVar7) = *local_8;
      *(undefined4 *)((int)local_2d0 + iVar7 + 4) = *puVar12;
      *(undefined4 *)((int)local_2d0 + iVar7 + 8) = puVar10[2];
      *(undefined4 *)((int)local_2d0 + iVar7 + 0xc) = puVar10[3];
      FUN_008061a4();
      FUN_00805efa();
      param_9 = param_9 + 1;
      local_8[3] = *(undefined4 *)((int)local_210 + iVar7 + 0xc);
      local_40 = local_40 + 4;
      local_8 = local_8 + 4;
      iVar7 = iVar7 + 0x10;
    } while (param_9 < (int)param_4);
  }
  iVar7 = 1;
  if (0 < (int)param_4) {
    piVar6 = (int *)(DAT_0149e130 + 0x594);
    fVar11 = param_4;
    do {
      if (*piVar6 < (int)(&local_38)[(int)param_15]) {
        iVar7 = 0;
      }
      piVar6 = piVar6 + 1;
      fVar11 = (float)((int)fVar11 - 1);
    } while (fVar11 != 0.0);
  }
  if (((param_15 == 0.0) && (param_7 < local_3c)) ||
     ((param_15 == 1.4013e-45 && (local_3c < param_6)))) {
    iVar7 = iVar7 + 2;
  }
  if ((iVar7 == 3) &&
     (((param_15 == 0.0 && (param_7 < local_3c)) ||
      ((param_15 == 1.4013e-45 && (local_3c < param_6)))))) {
    param_15 = (float)(1 - (int)param_15);
    param_13 = (float)((int)param_15 * 4);
    param_11 = (undefined4 *)local_5c[(int)param_15];
    iVar7 = 0;
    param_18 = param_18 % (int)param_11;
    if (0 < (int)param_4) {
      fVar11 = (&local_38)[(int)param_15];
      iVar4 = 0x594;
      fVar9 = param_4;
      do {
        *(float *)(iVar4 + DAT_0149e130) = fVar11;
        iVar4 = iVar4 + 4;
        fVar9 = (float)((int)fVar9 - 1);
      } while (fVar9 != 0.0);
    }
    in_stack_000000a8 = (float)((int)local_c % (int)param_11);
  }
  iVar4 = (int)local_c % (int)param_11;
  if ((*(int *)(DAT_0149e130 + 0x5f4) != 0) && (iVar7 == 1)) {
    in_stack_000000a8 = (float)iVar4;
  }
  *(int *)(DAT_0149e130 + 0x5f4) = 0;
  if (iVar7 != 2) {
    iVar8 = *(int *)((int)&local_4c + (int)param_13);
    iVar7 = param_18 * 4 + 0x594;
    if ((iVar8 <= *(int *)(iVar7 + DAT_0149e130)) &&
       (*(int *)((int)&local_38 + (int)param_13) <=
        *(int *)(DAT_0149e130 + 0x594 + (int)in_stack_000000a8 * 4))) {
      piVar6 = (int *)(DAT_0149e130 + 0x60c);
      fVar11 = local_3c;
      if (0 < *piVar6) {
        *piVar6 = *piVar6 + -1;
        fVar11 = _DAT_0081fd00;
      }
      piVar6 = (int *)(DAT_0149e130 + 0x608);
      if (0 < *piVar6) {
        *piVar6 = *piVar6 + -1;
      }
      if (fVar11 <= param_5) {
        *(undefined4 *)(DAT_0149e130 + 0x5f4) = 1;
      }
      else {
        FUN_00805f1f();
        fVar13 = (float10)FUN_00806202();
        iVar2 = DAT_0149e130;
        if (((param_3 & 1) != 0) && (*(int *)(DAT_0149e130 + 0x60c) == 0)) {
          in_stack_000000a8 = (float)iVar4;
        }
        if (fVar13 <= (float10)*(float *)((int)&local_74 + (int)param_13)) {
          puVar10 = (undefined4 *)(DAT_0149e130 + 0x5cc);
          *(undefined4 *)(DAT_0149e130 + 0x5c8) = local_d0;
          *puVar10 = uStack_cc;
          *(undefined4 *)(iVar2 + 0x5d0) = uStack_c8;
          *(undefined4 *)(iVar2 + 0x5d4) = uStack_c4;
        }
        else {
          puVar10 = (undefined4 *)(DAT_0149e130 + 0x5cc);
          *(undefined4 *)(DAT_0149e130 + 0x5c8) = local_8c;
          *puVar10 = local_88;
          *(undefined4 *)(iVar2 + 0x5d0) = local_84;
          *(undefined4 *)(iVar2 + 0x5d4) = local_80;
          FUN_0080604f();
        }
        local_d0 = *(undefined4 *)(DAT_0149e130 + 0x5c8);
        uStack_cc = *(undefined4 *)(DAT_0149e130 + 0x5cc);
        uStack_c8 = *(undefined4 *)(DAT_0149e130 + 0x5d0);
        uStack_c4 = *(undefined4 *)(DAT_0149e130 + 0x5d4);
        iVar8 = *(int *)(iVar7 + DAT_0149e130) - iVar8;
        param_9 = (int)in_stack_000000a8;
        if ((int)in_stack_000000a8 < (int)param_4) {
          param_6 = (float)((int)in_stack_000000a8 << 7);
          local_c = (float)((int)param_11 << 4);
          param_18 = (int)param_11 << 7;
          param_3 = (int)in_stack_000000a8 * 4 + 0x594;
          iVar7 = (int)in_stack_000000a8 << 4;
          do {
            puVar10 = (undefined4 *)(iVar7 + 0x494 + DAT_0149e130);
            *puVar10 = *(undefined4 *)((int)local_190 + iVar7);
            puVar10[1] = *(undefined4 *)((int)local_190 + iVar7 + 4);
            puVar10[2] = *(undefined4 *)((int)local_190 + iVar7 + 8);
            puVar10[3] = *(undefined4 *)((int)local_190 + iVar7 + 0xc);
            puVar10 = (undefined4 *)(iVar7 + 0x610 + DAT_0149e130);
            local_20 = *puVar10;
            fStack_18 = (float)puVar10[2];
            local_14 = puVar10[3];
            local_1c = 0.0;
            FUN_00806349();
            iVar4 = *(int *)((int)param_6 + 0x30 + DAT_0149e130);
            puVar10 = (undefined4 *)(iVar7 + 0x514 + DAT_0149e130);
            *puVar10 = local_20;
            puVar10[1] = local_1c;
            puVar10[2] = fStack_18;
            puVar10[3] = local_14;
            *(int *)(param_3 + DAT_0149e130) = iVar8;
            if (iVar4 != 0) {
              *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x15538) = 1;
              local_7c = local_20;
              local_74 = fStack_18;
              local_70 = local_14;
              local_78 = local_1c + in_stack_000000a0;
              iVar4 = FUN_0081b115();
              if (iVar4 != 0) {
                local_5c[2] = local_20;
                local_4c = fStack_18;
                local_48 = local_14;
                local_50 = local_1c - in_stack_000000a4;
                cVar3 = FUN_0081c852();
                if (((cVar3 != '\0') && ((float)_DAT_0081fcf8 < local_68)) && (local_50 < local_78))
                {
                  puVar10 = (undefined4 *)(iVar7 + 0x514 + DAT_0149e130);
                  *puVar10 = local_5c[2];
                  puVar10[1] = local_50;
                  puVar10[2] = local_4c;
                  puVar10[3] = local_48;
                  *(int *)(param_3 + DAT_0149e130) = iVar8;
                }
              }
              *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x15538) = 0;
            }
            param_9 = param_9 + (int)param_11;
            iVar7 = iVar7 + (int)local_c;
            param_3 = param_3 + (int)param_11 * 4;
            param_6 = (float)((int)param_6 + param_18);
          } while (param_9 < (int)param_4);
        }
        param_18 = (int)in_stack_000000a8;
      }
    }
  }
  puVar10 = local_10;
  puVar12 = local_250;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar12 = puVar12 + 1;
  }
  puVar10 = local_bc;
  puVar12 = local_10;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar12 = puVar12 + 1;
  }
  FUN_00818e4a();
  puVar10 = local_250;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *local_10 = *puVar10;
    puVar10 = puVar10 + 1;
    local_10 = local_10 + 1;
  }
  *(float *)(DAT_0149e130 + 0x5e8) = param_15;
  *(int *)(DAT_0149e130 + 0x5ec) = param_18;
  *(float *)(DAT_0149e130 + 0x5f0) = in_stack_000000a8;
  if (0 < (int)param_4) {
    puVar10 = local_2d0;
    puVar12 = (undefined4 *)(param_2 + 0x1234);
    for (iVar7 = ((uint)param_4 & 0xfffffff) << 2; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar12 = puVar12 + 1;
    }
  }
  iVar7 = *(int *)(param_2 + 0x133c);
  *local_c0 = local_110;
  local_c0[1] = fStack_10c;
  local_c0[2] = fStack_108;
  local_c0[3] = fStack_104;
  if (iVar7 != 0) {
    puVar10 = local_bc;
    puVar12 = (undefined4 *)(iVar7 + 0x6c);
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar12 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar12 = puVar12 + 1;
    }
  }
  return;
}


/* ---- Exec_Scene_Physic @ 00816d8c ---- */

void Exec_Scene_Physic(undefined4 param_1,int param_2,uint param_3,undefined4 param_4,
                      undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                      int param_9)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 in_stack_00000034;
  undefined4 in_stack_00000038;
  undefined4 local_e4 [16];
  undefined1 local_a4 [64];
  undefined4 local_64 [12];
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_1c = param_9;
  local_c = param_6;
  local_14 = param_4;
  local_8 = 0;
  local_10 = param_5;
  local_18 = 0;
  param_6 = 0;
  local_24 = param_7;
  local_20 = param_8;
  param_9 = 0;
  if ((param_3 & 0x20) != 0) {
    param_6 = *(undefined4 *)(param_2 + 0x133c);
    param_9 = *(int *)(param_2 + 0x1358) + 0x14d44;
  }
  puVar2 = (undefined4 *)(param_2 + 0x94f0);
  puVar5 = local_e4;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar5 = puVar5 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x94f0);
  puVar5 = local_64;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar5 = puVar5 + 1;
  }
  FUN_008061df(local_64);
  iVar3 = FUN_00817b57(param_1,0x87c);
  FUN_00805a4d();
  if (*(char *)(iVar3 + 0x10) != '\0') {
    *(uint *)(iVar3 + 0x14) = param_3;
    param_3 = param_3 & 3;
    if (param_3 == 0) {
LAB_00816e58:
      FUN_0081a939(&local_34,&local_14,*(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x14960));
      *(undefined4 *)(iVar3 + 0x2e8) = in_stack_00000034;
      *(undefined4 *)(iVar3 + 0x2c8) = in_stack_00000038;
      *(undefined4 *)(iVar3 + 0x2e0) = param_6;
      *(undefined4 *)(iVar3 + 700) = 1;
      *(int *)(iVar3 + 0x2dc) = param_9;
    }
    else if (param_3 == 1) {
      FUN_0081aaa4(local_64,&local_24,&local_14,
                   *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x14960));
      puVar2 = (undefined4 *)(iVar3 + 0x348);
      iVar4 = 8;
      do {
        puVar2[8] = in_stack_00000034;
        *puVar2 = in_stack_00000038;
        puVar2[6] = param_6;
        puVar2[5] = param_9;
        puVar2 = puVar2 + 0x20;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    else if (param_3 == 2) {
      FUN_0081c8bb(local_a4,&local_24,1);
      FUN_0081a7f8(local_64);
    }
    else if (param_3 != 3) goto LAB_00816e58;
  }
  uVar1 = *(uint *)(iVar3 + 0x14) & 3;
  if (uVar1 != 0) {
    if (uVar1 == 1) {
      FUN_0081abbd(local_64);
      FUN_0081ab9d(*(undefined4 *)(param_2 + 0x1358));
      goto LAB_00816ee9;
    }
    if (uVar1 == 2) {
      puVar2 = local_64;
      puVar5 = (undefined4 *)(iVar3 + 0x27c);
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar5 = puVar5 + 1;
      }
      FUN_00819f5f(iVar3 + 0x18);
      goto LAB_00816ee9;
    }
    if (uVar1 == 3) goto LAB_00816ee9;
  }
  FUN_00819f28(iVar3 + 700);
  local_34 = *(undefined4 *)(iVar3 + 0x2fc);
  uStack_30 = *(undefined4 *)(iVar3 + 0x300);
  uStack_2c = *(undefined4 *)(iVar3 + 0x304);
  local_28 = 0x3f800000;
LAB_00816ee9:
  puVar2 = local_64;
  puVar5 = (undefined4 *)(param_2 + 0x94f0);
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar5 = puVar5 + 1;
  }
  FUN_00818e4a(param_2);
  puVar2 = local_e4;
  puVar5 = (undefined4 *)(param_2 + 0x94f0);
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar5 = puVar5 + 1;
  }
  return;
}


/* ---- Exec_Scene_Portal @ 00816fe0 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Exec_Scene_Portal(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
                      undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                      int param_9,float param_10)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char cVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  int local_10 [3];
  
  uVar8 = 0;
  local_10[0] = FUN_0080e11f(0);
  local_10[1] = FUN_0080e11f(1);
  local_10[2] = FUN_0080e11f(2);
  if (local_10[2] != 0) {
    FUN_00817a85(3);
  }
  if (((local_10[0] != 0) && (local_10[1] != 0)) && (cVar4 = FUN_00817a85(3), cVar4 != '\0')) {
    FUN_00817a85(3);
  }
  piVar5 = (int *)FUN_00805784(0x94);
  uVar3 = _DAT_0081fcb0;
  uVar2 = _DAT_0081fcac;
  *piVar5 = *(int *)(param_2 + 0x9588);
  iVar7 = 0;
  piVar6 = piVar5;
  do {
    piVar6 = piVar6 + 1;
    if ((local_10[iVar7] == 0) || (iVar1 = *(int *)(local_10[iVar7] + 0x18), iVar1 == 0)) {
      *piVar6 = 0;
    }
    else {
      *piVar6 = iVar1;
      *(undefined1 *)(iVar1 + 0x4d) = 0;
      *(undefined4 *)(*piVar6 + 0x50) = 0;
      iVar1 = *piVar6;
      *(undefined4 *)(iVar1 + 0x54) = uVar3;
      *(undefined4 *)(iVar1 + 0x58) = uVar3;
      *(undefined4 *)(iVar1 + 0x5c) = uVar2;
      *(undefined4 *)(iVar1 + 0x60) = uVar2;
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 < 3);
  do {
    local_18 = param_7;
    if ((uVar8 & 4) != 0) {
      local_18 = param_8;
    }
    local_1c = param_5;
    if ((uVar8 & 2) != 0) {
      local_1c = param_6;
    }
    local_20 = param_3;
    if ((uVar8 & 1) != 0) {
      local_20 = param_4;
    }
    local_14 = 0x3f800000;
    FUN_00806305(param_2 + 0x94f0,&local_20);
    uVar8 = uVar8 + 1;
  } while ((int)uVar8 < 8);
  if (param_10 < _DAT_0081fd10) {
    param_9 = 0x100;
  }
  piVar5[4] = param_9;
  *(int **)(param_2 + 0x9588) = piVar5;
  FUN_00818ea3(param_2,0);
  return;
}


/* ---- FUN_00817134 @ 00817134 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00817134(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  byte *pbVar3;
  bool bVar4;
  int *piVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined1 *puVar10;
  int iVar11;
  int *piVar12;
  undefined4 *puVar13;
  float10 fVar14;
  undefined4 local_1e8 [8];
  undefined4 local_1c8;
  undefined4 local_1c4;
  undefined4 local_1c0;
  undefined4 local_1bc;
  undefined1 local_1a8 [8];
  undefined4 auStack_1a0 [53];
  undefined1 local_cc [64];
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_7c;
  undefined1 local_60 [24];
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  int *local_2c;
  int local_28;
  undefined4 *local_24;
  int *local_20;
  float local_1c;
  int local_18;
  undefined4 *local_14;
  int local_10;
  char local_9;
  int local_8;
  
  local_40 = _DAT_0081f378;
  local_3c = _DAT_0081f378;
  local_2c = *(int **)(param_1 + 0x9538);
  local_38 = 0x3f800000;
  puVar6 = *(undefined4 **)(param_1 + 0x9534);
  local_34 = 0x3f800000;
  *(undefined4 *)(param_1 + 0x9534) = 0;
  *(undefined4 *)(param_1 + 0x9538) = 0;
  local_30 = param_2;
  local_10 = param_1;
  FUN_008067af(&local_40);
  DAT_0149e6a8 = 0;
  DAT_0149e6a4 = 0;
  puVar13 = &DAT_0149e6b8;
  for (iVar7 = 0xa0; iVar11 = DAT_0149e6a8, piVar12 = local_2c, iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  for (; DAT_0149e6a8 = iVar11, local_2c = piVar12, puVar6 != (undefined4 *)0x0;
      puVar6 = (undefined4 *)*puVar6) {
    iVar7 = puVar6[2];
    local_8 = 0;
    if ((iVar7 != 0) ||
       ((puVar6[1] != 0 && (iVar7 = *(int *)(puVar6[1] + 0x18), *(int *)(iVar7 + 4) == 6)))) {
      local_8 = iVar7;
    }
    if ((puVar6[1] != 0) && (iVar7 = *(int *)(puVar6[1] + 0x18), *(int *)(iVar7 + 4) == 9)) {
      iVar9 = *(int *)(iVar7 + 0x34);
      DAT_0149e6a8 = iVar11 + 1;
      iVar7 = *(int *)(iVar7 + 0x30);
      (&DAT_0140e130)[iVar11 * 9] = puVar6;
      uVar1 = (&DAT_0149e6b8)[iVar9 * 0x20 + iVar7];
      (&DAT_0140e144)[iVar11 * 9] = 0;
      (&DAT_0140e138)[iVar11 * 9] = 0;
      (&DAT_0140e13c)[iVar11 * 9] = 0;
      (&DAT_0140e140)[iVar11 * 9] = 0;
      (&DAT_0140e134)[iVar11 * 9] = uVar1;
      (&DAT_0140e14c)[iVar11 * 9] = 0;
      (&DAT_0149e6b8)[iVar9 * 0x20 + iVar7] = &DAT_0140e130 + iVar11 * 9;
    }
    if (local_8 != 0) {
      local_9 = FUN_00806742(6);
      iVar7 = local_8;
      if ((puVar6[0x1f] != 0) && (*(char *)(puVar6[0x1f] + 0x4e) == '\0')) {
        local_9 = '\x01';
      }
      if (*(int *)(local_8 + 0x88) == 0) {
        FUN_00812b30();
      }
      local_18 = 1;
      if (1 < *(int *)(iVar7 + 0x40)) {
        local_1c = 1.06499e-43;
        do {
          if (0x3fff < DAT_0149e6a8) break;
          local_20 = (int *)(*(int *)(local_8 + 0x3c) + (int)local_1c);
          local_28 = 0;
          iVar7 = *local_20;
          if (0 < *(int *)(iVar7 + 0x10)) {
            local_14 = (undefined4 *)0x0;
            local_24 = &DAT_0140e130 + DAT_0149e6a8 * 9;
            do {
              uVar8 = *(int *)(iVar7 + 0xc) + (int)local_14;
              iVar7 = *(int *)(uVar8 + 0xe0);
              iVar11 = local_20[0x11];
              iVar9 = *(int *)(uVar8 + 0xd8);
              if ((local_9 == '\0') || (iVar9 == 1)) {
                DAT_0149e6a8 = DAT_0149e6a8 + 1;
                local_24[2] = local_8;
                local_24[3] = local_18;
                local_24[4] = local_28;
                iVar2 = (&DAT_0149e6b8)[iVar9 * 0x20 + (iVar7 + iVar11 & 0x1fU)];
                *local_24 = puVar6;
                local_24[5] = 0;
                local_24[6] = uVar8;
                local_24[7] = 0;
                if ((iVar2 == 0) || (uVar8 <= *(uint *)(iVar2 + 0x18))) {
                  local_24[1] = iVar2;
                  (&DAT_0149e6b8)[iVar9 * 0x20 + (iVar7 + iVar11 & 0x1fU)] = local_24;
                  local_24 = local_24 + 9;
                }
                else {
                  do {
                    iVar7 = iVar2;
                    if (*(int *)(iVar7 + 4) == 0) break;
                    iVar2 = *(int *)(iVar7 + 4);
                  } while (*(uint *)(*(int *)(iVar7 + 4) + 0x18) < uVar8);
                  local_24[1] = *(undefined4 *)(iVar7 + 4);
                  *(undefined4 **)(iVar7 + 4) = local_24;
                  local_24 = local_24 + 9;
                }
              }
              local_28 = local_28 + 1;
              iVar7 = *local_20;
              local_14 = (undefined4 *)((int)local_14 + 0xf0);
            } while (local_28 < *(int *)(iVar7 + 0x10));
          }
          local_18 = local_18 + 1;
          local_1c = (float)((int)local_1c + 0x4c);
        } while (local_18 < *(int *)(local_8 + 0x40));
      }
    }
    iVar11 = DAT_0149e6a8;
    piVar12 = local_2c;
  }
  local_14 = (undefined4 *)0x0;
  local_20 = (int *)0xffffffff;
  piVar5 = piVar12;
  if (piVar12 != (int *)0x0) {
    do {
      piVar5 = (int *)*piVar5;
    } while (piVar5 != (int *)0x0);
    local_24 = (undefined4 *)(local_10 + 0x14a8);
    do {
      iVar7 = DAT_0149e6a8;
      iVar11 = DAT_0149e6a8 * 0x24;
      puVar6 = &DAT_0140e130 + DAT_0149e6a8 * 9;
      DAT_0149e6a8 = DAT_0149e6a8 + 1;
      *puVar6 = piVar12;
      (&DAT_0140e144)[iVar7 * 9] = piVar12[0x20];
      (&DAT_0140e138)[iVar7 * 9] = 0;
      (&DAT_0140e13c)[iVar7 * 9] = 0;
      (&DAT_0140e140)[iVar7 * 9] = 0;
      (&DAT_0140e134)[iVar7 * 9] = 0;
      (&DAT_0140e14c)[iVar7 * 9] = 0;
      FUN_00805f1f(piVar12 + 0x13,local_24);
      fVar14 = (float10)FUN_00806202();
      local_1c = (float)fVar14;
      if (fVar14 <= (float10)_DAT_0081fcc8) {
        fVar14 = (float10)_DAT_0081fcc8;
      }
      iVar9 = (&DAT_0140e144)[iVar7 * 9];
      fVar14 = (float10)*(float *)(iVar9 + 0x10) / fVar14;
      if (local_1c < _DAT_0081fd18) {
        if (_DAT_0081fd14 <= local_1c) {
          *(float *)(iVar9 + 0xc) =
               (_DAT_0081fd18 - local_1c) * *(float *)(iVar9 + 0xc) * _DAT_0081fcc8;
        }
      }
      else {
        fVar14 = (float10)0;
      }
      pbVar3 = (byte *)(&DAT_0140e144)[iVar7 * 9];
      *(float *)(iVar11 + 0x140e150) = (float)fVar14;
      iVar7 = DAT_0149e6a4;
      if ((*pbVar3 & 1) == 0) {
        DAT_0149e6a4 = DAT_0149e6a4 + 1;
        (&DAT_0149e1b0)[iVar7] = puVar6;
      }
      else {
        if (*(int *)(piVar12[0x20] + 0x14) == 0) {
          iVar7 = 0;
        }
        else {
          iVar7 = *(int *)(*(int *)(piVar12[0x20] + 0x14) + 8);
        }
        if ((local_14 == (undefined4 *)0x0) || ((int)local_20 < iVar7)) {
          local_20 = (int *)iVar7;
          local_14 = puVar6;
        }
      }
      iVar7 = DAT_0149e6a4;
      piVar12 = (int *)*piVar12;
    } while (piVar12 != (int *)0x0);
    if (local_14 != (undefined4 *)0x0) {
      DAT_0149e6a4 = DAT_0149e6a4 + 1;
      local_14[8] = 0x60ad78ec;
      (&DAT_0149e1b0)[iVar7] = local_14;
    }
  }
  iVar7 = local_10;
  iVar11 = DAT_0149e6a4 + -1;
  do {
    bVar4 = true;
    iVar9 = 0;
    if (iVar11 < 1) break;
    do {
      if (*(float *)((&DAT_0149e1b0)[iVar9] + 0x20) < *(float *)((&DAT_0149e1b4)[iVar9] + 0x20)) {
        uVar1 = (&DAT_0149e1b0)[iVar9];
        (&DAT_0149e1b0)[iVar9] = (&DAT_0149e1b4)[iVar9];
        (&DAT_0149e1b4)[iVar9] = uVar1;
        bVar4 = false;
      }
      iVar9 = iVar9 + 1;
    } while (iVar9 < iVar11);
  } while (!bVar4);
  if (3 < DAT_0149e6a4) {
    DAT_0149e6a4 = 4;
  }
  puVar6 = (undefined4 *)(local_10 + 0x135c);
  puVar13 = local_1e8;
  for (iVar11 = 0x5e; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar13 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar13 = puVar13 + 1;
  }
  FUN_00805a4d();
  local_1c0 = 0xff000000;
  local_1e8[0] = *(undefined4 *)(iVar7 + 0x14a8);
  local_1e8[1] = *(undefined4 *)(iVar7 + 0x14ac);
  local_1e8[2] = *(undefined4 *)(iVar7 + 0x14b0);
  local_1e8[3] = *(undefined4 *)(iVar7 + 0x14b4);
  local_1bc = 0x3f800000;
  local_1c4 = 0xffffffff;
  local_1c8 = 0x43000000;
  FUN_0080221c();
  FUN_00805a4d();
  FUN_008023e2(*(undefined4 *)(*(int *)(DAT_0140e128 + 0x1860) + 0x20));
  iVar11 = DAT_0149e6a4;
  local_48 = 3;
  if ((DAT_0149e6a4 < 1) || (iVar9 = 0, *(int *)(DAT_0140e128 + 0xdc) != 0)) {
    local_44 = 0xffffffff;
    FUN_00801037(local_60);
  }
  else {
    local_8 = 0;
    local_18 = 0;
    if (0 < DAT_0149e6a4) {
      do {
        if (2 < iVar9) break;
        piVar12 = &DAT_0149e1b0 + local_8;
        if ((**(byte **)(*piVar12 + 0x14) & 2) != 0) {
          iVar7 = *piVar12;
          piVar5 = &DAT_0149e1b0 + iVar9;
          *piVar12 = *piVar5;
          iVar9 = iVar9 + 1;
          *piVar5 = iVar7;
          iVar7 = local_10;
          local_18 = iVar9;
        }
        local_8 = local_8 + 1;
      } while (local_8 < iVar11);
    }
    local_44 = (&DAT_0083f318)[iVar9];
    FUN_00801037(local_60);
    FUN_0081565b();
    FUN_0081566a(0,iVar7);
    local_8 = 0;
    if (0 < iVar9) {
      do {
        iVar11 = local_8;
        iVar9 = local_8 * 4;
        piVar12 = (int *)(&DAT_0149e1b0)[local_8];
        iVar7 = *piVar12;
        local_1e8[0] = *(undefined4 *)(iVar7 + 0x4c);
        local_1e8[1] = *(undefined4 *)(iVar7 + 0x50);
        local_1e8[2] = *(undefined4 *)(iVar7 + 0x54);
        local_1e8[3] = *(undefined4 *)(iVar7 + 0x58);
        local_1c4 = *(undefined4 *)(piVar12[5] + 8);
        local_1c8 = *(undefined4 *)(piVar12[5] + 0x10);
        local_1bc = *(undefined4 *)(piVar12[5] + 0xc);
        FUN_00806890(*piVar12 + 0x4c);
        FUN_008068f0(*(int *)(&DAT_0149e1b0)[iVar11] + 0x4c,local_cc,local_7c,local_8c,local_88,
                     &local_40);
        FUN_0081565b();
        FUN_0081566a((&DAT_0149e1b0)[iVar11],local_10);
        *(undefined4 *)(DAT_0140e128 + 0x248) = *(undefined4 *)(&DAT_0083f308 + iVar9);
        FUN_0081439e(1,0,0);
        local_8 = local_8 + 1;
      } while (local_8 < local_18);
    }
  }
  FUN_008012d2();
  *(undefined4 *)(local_30 + 0x18) = 3;
  FUN_00801037(local_30);
  FUN_0081565b();
  FUN_0081566a(0,local_10);
  if (0 < DAT_0149e6a4) {
    local_8 = 0;
    puVar10 = local_1a8;
    do {
      piVar12 = (int *)(&DAT_0149e1b0)[local_8];
      iVar7 = *piVar12;
      *(undefined4 *)(puVar10 + -0x10) = *(undefined4 *)(iVar7 + 0x4c);
      *(undefined4 *)(puVar10 + -0xc) = *(undefined4 *)(iVar7 + 0x50);
      *(undefined4 *)(puVar10 + -8) = *(undefined4 *)(iVar7 + 0x54);
      *(undefined4 *)(puVar10 + -4) = *(undefined4 *)(iVar7 + 0x58);
      FUN_00805cf1(*(undefined4 *)(piVar12[5] + 8));
      iVar7 = (&DAT_0149e1b0)[local_8];
      *(undefined4 *)(puVar10 + 0x10) = *(undefined4 *)(*(int *)(iVar7 + 0x14) + 0x10);
      iVar11 = local_8 + 1;
      *(undefined4 *)(puVar10 + 0x14) = *(undefined4 *)(*(int *)(iVar7 + 0x14) + 0xc);
      puVar10 = puVar10 + 0x28;
      local_8 = iVar11;
    } while (iVar11 < DAT_0149e6a4);
    if (iVar11 < 4) {
      iVar7 = 4 - iVar11;
      puVar6 = auStack_1a0 + iVar11 * 10;
      do {
        puVar6[-2] = 0;
        puVar6[-1] = 0;
        *puVar6 = 0;
        iVar7 = iVar7 + -1;
        puVar6[1] = 0;
        puVar6[-6] = local_1e8[0];
        puVar6[-5] = local_1e8[1];
        puVar6[-4] = local_1e8[2];
        puVar6[-3] = local_1e8[3];
        puVar6[3] = 0;
        puVar6 = puVar6 + 10;
      } while (iVar7 != 0);
    }
    FUN_0081565b();
    FUN_0081566a(0,local_10);
  }
  FUN_0081565b();
  FUN_0081566a(0,local_10);
  FUN_0081565b();
  FUN_0081566a(0,local_10);
  DAT_0149e938 = 0;
  FUN_008012d2();
  return;
}


/* ---- FUN_00817875 @ 00817875 ---- */

undefined4 __thiscall FUN_00817875(undefined4 param_1,byte param_2)

{
  FUN_008158a6();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


/* ---- FUN_00817894 @ 00817894 ---- */

undefined4 __thiscall FUN_00817894(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 < *(int *)(param_1 + 100)) {
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x88) + param_2 * 4);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


/* ---- FUN_008178b0 @ 008178b0 ---- */

void __fastcall FUN_008178b0(undefined4 *param_1)

{
  param_1[1] = 0;
  *param_1 = &PTR_FUN_0081fd1c;
  param_1[2] = 1;
  return;
}


/* ---- FUN_008178c4 @ 008178c4 ---- */

void __fastcall FUN_008178c4(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_0081fd1c;
  return;
}


/* ---- FUN_008178cb @ 008178cb ---- */

/* WARNING: Unable to track spacebase fully for stack */

undefined4 __fastcall FUN_008178cb(code *param_1,undefined4 *param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 **ppuVar3;
  undefined1 *apuStack_20 [2];
  
  apuStack_20[1] = &stack0xfffffffc;
  ppuVar3 = apuStack_20 + (1 - param_3);
  for (iVar2 = param_3; iVar2 != 0; iVar2 = iVar2 + -1) {
    *ppuVar3 = (undefined1 *)*param_2;
    param_2 = param_2 + 1;
    ppuVar3 = ppuVar3 + 1;
  }
  apuStack_20[-param_3] = (undefined1 *)0x8178f3;
  uVar1 = (*param_1)();
  *(undefined4 *)(apuStack_20[1] + -0xc) = uVar1;
  return *(undefined4 *)(apuStack_20[1] + -0xc);
}


/* ---- FUN_00817902 @ 00817902 ---- */

void __thiscall FUN_00817902(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  bool bVar6;
  int local_604 [384];
  
  uVar1 = *(uint *)(param_1 + 0x2c);
  bVar6 = (uVar1 & 0x40000000) != 0;
  if (bVar6) {
    local_604[0] = param_1;
  }
  uVar5 = (uint)bVar6;
  if ((uVar1 & 0x800000) != 0) {
    local_604[uVar5] = param_2;
    uVar5 = uVar5 + 1;
  }
  uVar1 = uVar1 >> 8 & 0xf;
  iVar4 = 0;
  if (uVar1 != 0) {
    do {
      iVar2 = FUN_0080e106(iVar4);
      if (iVar2 == 0) {
        local_604[uVar5] = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 0x18);
        piVar3 = (int *)(iVar2 + 8);
        *piVar3 = *piVar3 + 1;
        local_604[uVar5] = iVar2;
      }
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 1;
    } while (iVar4 < (int)uVar1);
  }
  uVar1 = *(uint *)(param_1 + 0x2c) >> 0xc & 0xf;
  iVar4 = 0;
  if (uVar1 != 0) {
    do {
      iVar2 = *(int *)(*(int *)(param_1 + 0x7c) + iVar4 * 4);
      if ((*(byte *)(param_1 + 0x2f) & 0x10) == 0) {
        if (iVar2 == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = *(int *)(iVar2 + 0x18);
        }
        if (iVar2 != 0) {
          *(int *)(iVar2 + 8) = *(int *)(iVar2 + 8) + 1;
        }
      }
      local_604[uVar5] = iVar2;
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 1;
    } while (iVar4 < (int)uVar1);
  }
  uVar1 = *(uint *)(param_1 + 0x2c) & 0xff;
  if (uVar1 != 0) {
    piVar3 = *(int **)(param_1 + 0x94);
    do {
      local_604[uVar5] = *piVar3;
      uVar5 = uVar5 + 1;
      piVar3 = piVar3 + 1;
      uVar1 = uVar1 - 1;
    } while (uVar1 != 0);
  }
  uVar1 = *(uint *)(param_1 + 0x2c) >> 0x10 & 0xf;
  if (uVar1 != 0) {
    piVar3 = *(int **)(param_1 + 0x84);
    do {
      local_604[uVar5] = *piVar3;
      uVar5 = uVar5 + 1;
      piVar3 = piVar3 + 1;
      uVar1 = uVar1 - 1;
    } while (uVar1 != 0);
  }
  uVar1 = *(uint *)(param_1 + 0x2c) >> 0x14 & 0xf;
  param_2 = 0;
  if (uVar1 != 0) {
    do {
      iVar4 = FUN_00817894(param_2);
      local_604[uVar5] = iVar4;
      uVar5 = uVar5 + 1;
      param_2 = param_2 + 1;
    } while (param_2 < (int)uVar1);
  }
  uVar1 = *(uint *)(param_1 + 0x2c);
  if ((uVar1 & 0x8000000) != 0) {
    local_604[uVar5] = *(int *)(param_1 + 0x70);
    uVar5 = uVar5 + 1;
  }
  if ((uVar1 & 0x1000000) != 0) {
    iVar4 = *(int *)(param_1 + 0x6c);
    local_604[uVar5] = iVar4;
    uVar5 = uVar5 + 1;
    iVar2 = 0;
    if (0 < iVar4) {
      iVar4 = *(int *)(param_1 + 0x78);
      do {
        piVar3 = (int *)(*(int *)(*(int *)(iVar4 + iVar2 * 4) + 0x18) + 8);
        *piVar3 = *piVar3 + 1;
        iVar4 = *(int *)(param_1 + 0x78);
        local_604[uVar5] = *(int *)(*(int *)(iVar4 + iVar2 * 4) + 0x18);
        uVar5 = uVar5 + 1;
        iVar2 = iVar2 + 1;
      } while (iVar2 < *(int *)(param_1 + 0x6c));
    }
  }
  if ((*(byte *)(param_1 + 0x2f) & 0x20) == 0) {
    FUN_008178cb(uVar5);
  }
  else {
    (**(code **)(param_1 + 0x20))(param_1);
  }
  return;
}


/* ---- FUN_00817a85 @ 00817a85 ---- */

undefined1 FUN_00817a85(void)

{
  return 1;
}


/* ---- FUN_00817a8a @ 00817a8a ---- */

void __thiscall FUN_00817a8a(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_3 != 0) {
    if (*(int *)(param_1 + 0x48) == 0) {
      *(int *)(param_1 + 0x44) = param_2;
      *(int *)(param_1 + 0x48) = param_3;
    }
    else {
      iVar2 = *(int *)(param_1 + 0x44);
      iVar1 = *(int *)(param_1 + 0x48) + iVar2;
      if (param_2 < iVar2) {
        iVar2 = param_2;
      }
      if (iVar1 < param_2 + param_3) {
        iVar1 = param_2 + param_3;
      }
      *(int *)(param_1 + 0x44) = iVar2;
      *(int *)(param_1 + 0x48) = iVar1 - iVar2;
    }
  }
  return;
}


/* ---- FUN_00817acc @ 00817acc ---- */

void __fastcall FUN_00817acc(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if (param_1 != 0) {
    piVar1 = (int *)(param_1 + 0x10);
    *piVar1 = *piVar1 + -1;
    if ((((*piVar1 == 0) && (puVar2 = *(undefined4 **)(param_1 + 0x18), puVar2 != (undefined4 *)0x0)
         ) && (*(char *)(param_1 + 0x40) == '\0')) &&
       ((iVar3 = puVar2[1], iVar3 == 1 || (iVar3 == 6)))) {
      *(int *)(param_1 + 4) = iVar3;
      piVar1 = puVar2 + 2;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        (**(code **)*puVar2)(1);
      }
      *(undefined1 *)(param_1 + 0x40) = 1;
    }
  }
  return;
}


/* ---- FUN_00817b06 @ 00817b06 ---- */

void __fastcall FUN_00817b06(int param_1)

{
  int iVar1;
  
  while (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 4);
    operator_delete(param_1);
    param_1 = iVar1;
  }
  return;
}


/* ---- FUN_00817b1d @ 00817b1d ---- */

int __fastcall FUN_00817b1d(byte *param_1)

{
  if (0x7f < *param_1) {
    return 2;
  }
  return *(byte *)((int)&PTR_DAT_0083f760 + (uint)*param_1) + 1;
}


/* ---- FUN_00817b33 @ 00817b33 ---- */

int __fastcall FUN_00817b33(int param_1)

{
  int iVar1;
  int extraout_ECX;
  char extraout_DL;
  
  do {
    iVar1 = FUN_00817b1d();
  } while (extraout_DL != '\x01');
  return (extraout_ECX + iVar1) - param_1;
}


/* ---- FUN_00817b4a @ 00817b4a ---- */

void FUN_00817b4a(int param_1)

{
  do {
  } while (0 < param_1);
  return;
}


/* ---- FUN_00817b57 @ 00817b57 ---- */

undefined4 * __thiscall FUN_00817b57(int param_1,undefined4 param_2,uint param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  puVar1 = *(undefined4 **)(param_1 + 0x1340);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)operator_new(param_3);
    puVar3 = puVar1;
    for (uVar2 = param_3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    for (param_3 = param_3 & 3; param_3 != 0; param_3 = param_3 - 1) {
      *(undefined1 *)puVar3 = 0;
      puVar3 = (undefined4 *)((int)puVar3 + 1);
    }
    **(undefined4 **)(param_1 + 0x1344) = puVar1;
    *(undefined4 **)(param_1 + 0x1344) = puVar1 + 1;
    *puVar1 = param_2;
    *(undefined1 *)(puVar1 + 4) = 1;
  }
  else {
    *(undefined1 *)(puVar1 + 4) = 0;
    *(undefined4 *)(param_1 + 0x1340) = puVar1[1];
  }
  return puVar1;
}


/* ---- FUN_00817bb7 @ 00817bb7 ---- */

void __thiscall FUN_00817bb7(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(param_1 + 0x12f4);
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_3 = *puVar2;
    puVar2 = puVar2 + 1;
    param_3 = param_3 + 1;
  }
  puVar2 = (undefined4 *)(param_1 + 0x12f4);
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}


/* ---- FUN_00817bdc @ 00817bdc ---- */

void __thiscall FUN_00817bdc(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(param_1 + 0x12f4);
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}


/* ---- FUN_00817bf5 @ 00817bf5 ---- */

void __fastcall FUN_00817bf5(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined1 local_44 [64];
  
  FUN_008022a7(local_44);
  puVar2 = (undefined4 *)(param_1 + 0x1478);
  puVar3 = (undefined4 *)(param_1 + 0x9540);
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  FUN_008064d6();
  FUN_0080e753(local_44);
  return;
}


/* ---- FUN_00817c39 @ 00817c39 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 __thiscall FUN_00817c39(int *param_1,float param_2,int param_3)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  float10 fVar5;
  float fVar6;
  float *local_8;
  
  pfVar4 = (float *)param_1[1];
  if (param_2 < *pfVar4 == (param_2 == *pfVar4)) {
    iVar2 = *param_1;
    if (param_2 < pfVar4[iVar2 * 2 + -2]) {
      iVar3 = 0;
      local_8 = pfVar4;
      if (iVar2 != 1 && -1 < iVar2 + -1) {
        do {
          local_8 = local_8 + 2;
          if (param_2 < *local_8) {
            pfVar1 = (float *)(param_1[1] + iVar3 * 8);
            if (param_3 == 0) {
              pfVar4 = pfVar4 + iVar3 * 2 + 5;
              if (iVar2 <= iVar3 + 2) {
                pfVar4 = (float *)0x0;
              }
              fVar6 = (param_2 - *pfVar1) / (pfVar1[2] - *pfVar1);
LAB_00817cfb:
              FUN_00805543(pfVar1 + 1,pfVar1 + 3,pfVar4,1,fVar6,0,0,0);
              return (float10)param_2;
            }
            if (param_3 == 1) {
              fVar6 = (param_2 - *pfVar1) / (pfVar1[2] - *pfVar1);
              pfVar4 = pfVar1 + 3;
              goto LAB_00817cfb;
            }
            if (param_3 == 2) {
              return (float10)pfVar1[1];
            }
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 < iVar2 + -1);
      }
      fVar5 = (float10)_DAT_0081f374;
    }
    else {
      fVar5 = (float10)pfVar4[iVar2 * 2 + -1];
    }
  }
  else {
    fVar5 = (float10)pfVar4[1];
  }
  return fVar5;
}


/* ---- FUN_00817d55 @ 00817d55 ---- */

void __thiscall FUN_00817d55(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = 0;
  if (0 < *(int *)(param_1 + 0x20)) {
    do {
      fVar2 = (float10)FUN_00817c39(param_2,*(undefined4 *)(param_1 + 0x24));
      *(float *)(param_3 + iVar1 * 4) = (float)fVar2;
      iVar1 = iVar1 + 1;
    } while (iVar1 < *(int *)(param_1 + 0x20));
  }
  return;
}


/* ---- FUN_00817d8d @ 00817d8d ---- */

void __fastcall FUN_00817d8d(undefined4 *param_1)

{
  int iVar1;
  
  for (iVar1 = 0x2d; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = 0;
    param_1 = param_1 + 1;
  }
  return;
}


/* ---- FUN_00817d99 @ 00817d99 ---- */

void __fastcall FUN_00817d99(int param_1)

{
  if (*(int *)(param_1 + 0x1c) != 0) {
    FUN_00817b06();
    *(undefined4 *)(param_1 + 0x1c) = 0xffffffff;
  }
  return;
}


/* ---- FUN_00817dae @ 00817dae ---- */

void __fastcall FUN_00817dae(int param_1)

{
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 1;
  return;
}


/* ---- FUN_00817dba @ 00817dba ---- */

void __thiscall FUN_00817dba(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  
  *(uint *)(param_1 + 0x50) = param_2 >> 8 & 0xf;
  uVar6 = param_2 >> 0xc & 0xf;
  uVar2 = param_2 >> 0x10 & 0xf;
  uVar4 = param_2 >> 0x14 & 0xf;
  *(uint *)(param_1 + 0x5c) = param_2 & 0xff;
  *(uint *)(param_1 + 0x54) = uVar6;
  *(uint *)(param_1 + 0x60) = uVar2;
  *(uint *)(param_1 + 100) = uVar4;
  *(undefined4 *)(param_1 + 0x68) = 1;
  if ((param_2 & 0x1000000) != 0) {
    *(undefined4 *)(param_1 + 0x50) = 0xff;
  }
  *(undefined4 *)(param_1 + 0x58) = 0;
  uVar2 = uVar4 + (uVar2 + (param_2 & 0xff)) * 2 + uVar6 + 1 + *(int *)(param_1 + 0x50);
  puVar3 = (undefined4 *)operator_new(uVar2 * 4);
  *(undefined4 **)(param_1 + 0x74) = puVar3;
  puVar7 = puVar3;
  for (uVar2 = uVar2 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(undefined1 *)puVar7 = 0;
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  *(undefined4 **)(param_1 + 0x78) = puVar3;
  puVar3 = puVar3 + *(int *)(param_1 + 0x50);
  puVar7 = puVar3 + *(int *)(param_1 + 0x54);
  *(undefined4 **)(param_1 + 0x80) = puVar7;
  puVar7 = puVar7 + *(int *)(param_1 + 0x58);
  *(undefined4 **)(param_1 + 0x84) = puVar7;
  *(undefined4 **)(param_1 + 0x7c) = puVar3;
  puVar7 = puVar7 + *(int *)(param_1 + 0x60);
  *(undefined4 **)(param_1 + 0x88) = puVar7;
  puVar7 = puVar7 + *(int *)(param_1 + 100);
  *(undefined4 **)(param_1 + 0x90) = puVar7;
  *(undefined4 **)(param_1 + 0x94) = puVar7 + *(int *)(param_1 + 0x5c);
  puVar3 = puVar7 + *(int *)(param_1 + 0x5c) + *(int *)(param_1 + 0x5c);
  iVar5 = 0;
  if (0 < *(int *)(param_1 + 0x60)) {
    do {
      *(undefined4 **)(*(int *)(param_1 + 0x84) + iVar5 * 4) = puVar3;
      iVar1 = iVar5 * 4;
      puVar3 = puVar3 + 1;
      iVar5 = iVar5 + 1;
      **(undefined1 **)(*(int *)(param_1 + 0x84) + iVar1) = 0;
    } while (iVar5 < *(int *)(param_1 + 0x60));
  }
  *(undefined4 **)(param_1 + 0x8c) = puVar3;
  *(undefined1 *)puVar3 = 1;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  return;
}


/* ---- Init_Misc_Load @ 00817ed0 ---- */

undefined4 Init_Misc_Load(undefined4 param_1)

{
  return param_1;
}


/* ---- Init_Misc_Nop @ 00817eda ---- */

undefined4 Init_Misc_Nop(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 1;
  if (1 < *(int *)(param_1 + 0x6c)) {
    do {
      iVar3 = FUN_0080e106(iVar4);
      puVar2 = *(undefined4 **)(iVar3 + 0x18);
      piVar1 = puVar2 + 2;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        (**(code **)*puVar2)(1);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(int *)(param_1 + 0x6c));
  }
  iVar4 = FUN_0080e106(0);
  return *(undefined4 *)(iVar4 + 0x18);
}


/* ---- Init_Misc_Event @ 00817f1a ---- */

undefined4 Init_Misc_Event(undefined4 param_1)

{
  return param_1;
}


/* ---- Init_Misc_Trigger @ 00817f24 ---- */

undefined4 Init_Misc_Trigger(undefined4 param_1)

{
  return param_1;
}


/* ---- FUN_00817f2e @ 00817f2e ---- */

undefined4 __thiscall FUN_00817f2e(undefined4 param_1,byte param_2)

{
  FUN_008178c4();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


/* ---- FUN_00817f4d @ 00817f4d ---- */

void __fastcall FUN_00817f4d(int param_1)

{
  *(undefined4 *)(param_1 + 0x1118) = 0;
  *(undefined4 *)(param_1 + 0x134c) = 1;
  FUN_00817b06();
  *(undefined4 *)(param_1 + 0x1348) = 0;
  *(undefined4 *)(param_1 + 0x1340) = 0;
  *(undefined4 *)(param_1 + 0x1344) = 0;
  *(undefined4 *)(param_1 + 0x14d4) = 0;
  *(undefined4 *)(param_1 + 0x14d8) = 0;
  *(undefined4 *)(param_1 + 0x14dc) = 0;
  *(undefined4 *)(param_1 + 0x14e0) = 0;
  *(undefined4 *)(param_1 + 0x14e4) = 0;
  *(undefined4 *)(param_1 + 0x14e8) = 0;
  *(undefined4 *)(param_1 + 0x14ec) = 1;
  *(undefined4 *)(*(int *)(param_1 + 0x1358) + 0x38) = 0;
  return;
}


/* ---- FUN_00817fba @ 00817fba ---- */

void __fastcall FUN_00817fba(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < *(int *)(param_1 + 0x1128)) {
    do {
      iVar1 = iVar2 * 4;
      iVar2 = iVar2 + 1;
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x1124) + iVar1) + 0x1c) = 0;
    } while (iVar2 < *(int *)(param_1 + 0x1128));
  }
  iVar2 = 0;
  if (0 < *(int *)(param_1 + 0x1118)) {
    do {
      iVar1 = *(int *)(*(int *)(param_1 + 0x1114) + iVar2 * 4);
      if ((*(int *)(iVar1 + 0xc) == *(int *)(iVar1 + 8)) ||
         (*(int *)(param_1 + 0x14d4) < *(int *)(iVar1 + 0xc))) {
        iVar2 = iVar2 + 1;
      }
      else {
        FUN_00817b06();
        *(int *)(param_1 + 0x1118) = *(int *)(param_1 + 0x1118) + -1;
        *(undefined4 *)(*(int *)(param_1 + 0x1114) + iVar2 * 4) =
             *(undefined4 *)(*(int *)(param_1 + 0x1114) + *(int *)(param_1 + 0x1118) * 4);
        operator_delete(iVar1);
      }
    } while (iVar2 < *(int *)(param_1 + 0x1118));
  }
  *(undefined4 *)(param_1 + 0x1128) = 0;
  *(undefined4 *)(param_1 + 0x134c) = 0;
  return;
}


/* ---- FUN_00818047 @ 00818047 ---- */

void FUN_00818047(undefined4 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00806b54();
  *puVar1 = param_1;
  return;
}


/* ---- FUN_0081805e @ 0081805e ---- */

void __thiscall FUN_0081805e(int param_1,int *param_2)

{
  int *piVar1;
  
  if ((param_2[2] == param_2[3]) ||
     ((param_2[2] <= *(int *)(param_1 + 0x14d4) && (*(int *)(param_1 + 0x14d4) < param_2[3])))) {
    if (*(int *)(*param_2 + 0x1c) == 0) {
      piVar1 = (int *)FUN_00806b54();
      *piVar1 = *param_2;
    }
    param_2[1] = *(int *)(*param_2 + 0x1c);
    *(int **)(*param_2 + 0x1c) = param_2;
  }
  return;
}


/* ---- FUN_008180a6 @ 008180a6 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_008180a6(int param_1,int param_2,byte *param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int *piVar3;
  byte bVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  byte *pbVar8;
  byte bVar9;
  int local_14;
  undefined4 *local_8;
  
  local_8 = &DAT_0149e950;
  puVar7 = &DAT_0149e960;
  pbVar8 = param_3;
switchD_008180ef_caseD_0:
  param_3 = pbVar8;
  puVar6 = puVar7;
  bVar4 = *param_3;
  pbVar8 = param_3 + 1;
  bVar9 = bVar4;
  if (0x7f < bVar4) {
    bVar9 = bVar4 & 0xf0;
  }
  puVar7 = puVar6;
  if (0x80 < bVar9) {
    if (bVar9 != 0x90) {
      if (bVar9 == 0xa0) goto switchD_008180ef_caseD_0;
      if (bVar9 != 0xb0) {
        if (bVar9 == 0xd0) goto LAB_0081827c;
        if ((bVar9 == 0xe0) || (bVar9 != 0xf0)) goto switchD_008180ef_caseD_0;
      }
      local_8 = local_8 + -4;
      local_14 = (int)(longlong)ROUND((float)puVar6[-1] * _DAT_0081f3a8);
      if (local_14 < 0xff) {
        bVar4 = (local_14 < 1) - 1U & (byte)(longlong)ROUND((float)puVar6[-1] * _DAT_0081f3a8);
      }
      else {
        bVar4 = 0xff;
      }
      *(byte *)(*(int *)(param_2 + 0x94) + (uint)*pbVar8 * 4 + 3) = bVar4;
      puVar7 = puVar6 + -4;
      pbVar8 = param_3 + 2;
      goto switchD_008180ef_caseD_0;
    }
LAB_0081827c:
    local_8 = local_8 + -4;
    puVar7 = puVar6 + -4;
    puVar1 = (undefined4 *)(*(int *)(param_2 + 0x94) + (uint)*pbVar8 * 4);
    if ((bVar4 & 1) != 0) {
      *puVar1 = *puVar7;
    }
    if ((bVar4 & 2) != 0) {
      puVar1[1] = puVar6[-3];
    }
    pbVar8 = param_3 + 2;
    if ((bVar4 & 4) != 0) {
      puVar1[2] = puVar6[-2];
    }
    goto switchD_008180ef_caseD_0;
  }
  switch(bVar9) {
  default:
    goto switchD_008180ef_caseD_0;
  case 1:
    goto switchD_008180ef_caseD_1;
  case 2:
    bVar4 = *pbVar8;
    local_8 = local_8 + 4;
    puVar7 = (undefined4 *)((uint)bVar4 * 0x10 + 0x1134 + param_1);
    *puVar6 = *puVar7;
    puVar6[1] = puVar7[1];
    puVar6[2] = puVar7[2];
    puVar6[3] = puVar7[3];
    FUN_00817a8a((uint)bVar4,1);
    puVar7 = puVar6 + 4;
    pbVar8 = param_3 + 2;
    goto switchD_008180ef_caseD_0;
  case 5:
    uVar5 = (uint)*pbVar8;
    param_3 = param_3 + 2;
    piVar3 = (int *)(param_2 + 0x90);
    *puVar6 = *(undefined4 *)(*piVar3 + uVar5 * 4);
    puVar6[1] = *(undefined4 *)(*piVar3 + 4 + uVar5 * 4);
    puVar6[2] = *(undefined4 *)(*piVar3 + 8 + uVar5 * 4);
    uVar2 = 0;
    break;
  case 7:
    uVar2 = *local_8;
    puVar6[-3] = uVar2;
    puVar6[-2] = uVar2;
    puVar6[-1] = uVar2;
    goto switchD_008180ef_caseD_0;
  case 0xb:
    local_8 = local_8 + -4;
    FUN_00805dce(puVar6 + -4);
    puVar7 = puVar6 + -4;
    goto switchD_008180ef_caseD_0;
  case 0xc:
    local_8 = local_8 + -4;
    FUN_00805df9(puVar6 + -4);
    puVar7 = puVar6 + -4;
    goto switchD_008180ef_caseD_0;
  case 0xd:
    local_8 = local_8 + -4;
    FUN_00805e24(puVar6 + -4);
    puVar7 = puVar6 + -4;
    goto switchD_008180ef_caseD_0;
  case 0x16:
    *puVar6 = *(undefined4 *)pbVar8;
    puVar6[1] = *(undefined4 *)(param_3 + 5);
    puVar6[2] = *(undefined4 *)(param_3 + 9);
    puVar6[3] = *(undefined4 *)(param_3 + 0xd);
    param_3 = param_3 + 0x11;
    goto LAB_008181c0;
  case 0x18:
    uVar2 = *(undefined4 *)pbVar8;
    param_3 = param_3 + 5;
    *puVar6 = uVar2;
    puVar6[1] = uVar2;
    puVar6[2] = uVar2;
    break;
  case 0x19:
    uVar2 = *local_8;
    *local_8 = 0;
    local_8[1] = 0;
    local_8[2] = 0;
    local_8[3] = 0;
    FUN_00817d55(uVar2,local_8);
    pbVar8 = param_3 + 3;
    goto switchD_008180ef_caseD_0;
  }
  puVar6[3] = uVar2;
LAB_008181c0:
  local_8 = local_8 + 4;
  puVar7 = puVar6 + 4;
  pbVar8 = param_3;
  goto switchD_008180ef_caseD_0;
switchD_008180ef_caseD_1:
  return 0;
}


/* ---- FUN_0081830f @ 0081830f ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall
FUN_0081830f(int *param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  float *pfVar1;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  float local_c8 [32];
  int *local_48;
  int *local_44;
  int local_40;
  int local_3c;
  int *local_38;
  float local_34;
  float local_30;
  float fStack_2c;
  float local_28;
  int *local_24;
  uint local_20;
  float *local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  char local_5;
  
  *(int *)(param_2 + 0x50) = *(int *)(param_2 + 0x50) + 1;
  *(undefined1 *)(param_2 + 0x4d) = 1;
  *(undefined1 *)(param_2 + 0x4e) = 1;
  local_48 = param_1;
  local_3c = param_2;
  FUN_00805905(param_4);
  for (; param_1 != (int *)0x0; param_1 = (int *)*param_1) {
    if (param_1[4] + param_3 < 0x100) {
      local_20 = 0;
      local_38 = param_1;
      do {
        local_38 = local_38 + 1;
        if ((*local_38 == param_2) &&
           (local_44 = param_1 + (local_20 ^ 1) + 1, *(int *)(*local_44 + 0x50) == 0)) {
          local_1c = local_c8;
          local_24 = param_1 + 5;
          local_18 = 1e+15;
          local_14 = 1e+15;
          local_10 = -1e+15;
          local_c = -1e+15;
          local_5 = '\0';
          local_40 = 8;
          do {
            pfVar1 = local_1c;
            FUN_00806297(param_5,local_24);
            if (pfVar1[2] < _DAT_0081f374) {
              local_5 = '\x01';
            }
            else {
              local_34 = *pfVar1;
              local_30 = pfVar1[1];
              fStack_2c = pfVar1[2];
              local_28 = pfVar1[3];
              FUN_00805e6e(1.0 / local_28);
              if (local_34 <= local_18) {
                local_18 = local_34;
              }
              if (local_30 <= local_14) {
                local_14 = local_30;
              }
              if (local_10 <= local_34) {
                local_10 = local_34;
              }
              param_2 = local_3c;
              if (local_c <= local_30) {
                local_c = local_30;
              }
            }
            local_24 = local_24 + 4;
            local_1c = local_1c + 4;
            local_40 = local_40 + -1;
          } while (local_40 != 0);
          if (local_5 != '\0') {
            pbVar4 = &DAT_0083f77d;
            do {
              uVar2 = (uint)pbVar4[-1];
              uVar3 = (uint)*pbVar4;
              if (local_c8[uVar2 * 4 + 2] * local_c8[uVar3 * 4 + 2] < _DAT_0081f374) {
                FUN_008059c8(local_c8 + uVar2 * 4,local_c8 + uVar3 * 4,
                             local_c8[uVar2 * 4 + 2] /
                             (local_c8[uVar2 * 4 + 2] - local_c8[uVar3 * 4 + 2]));
                FUN_00805e6e(1.0 / local_28);
                if (local_34 <= local_18) {
                  local_18 = local_34;
                }
                if (local_30 <= local_14) {
                  local_14 = local_30;
                }
                if (local_10 <= local_34) {
                  local_10 = local_34;
                }
                if (local_c <= local_30) {
                  local_c = local_30;
                }
              }
              pbVar4 = pbVar4 + 2;
            } while ((int)pbVar4 < 0x83f795);
          }
          FUN_008058b3(param_4);
          if ((local_10 - local_18 < _DAT_0081f374 != (local_10 - local_18 == _DAT_0081f374)) ||
             (local_c - local_14 < _DAT_0081f374 != (local_c - local_14 == _DAT_0081f374))) {
            local_18 = 1.0;
            local_14 = 1.0;
            local_10 = _DAT_0081f378;
            local_c = _DAT_0081f378;
          }
          FUN_0081830f(param_1[4] + param_3,&local_18,param_5);
        }
        local_20 = local_20 + 1;
      } while ((int)local_20 < 2);
    }
  }
  *(int *)(param_2 + 0x50) = *(int *)(param_2 + 0x50) + -1;
  return;
}


/* ---- FUN_0081859c @ 0081859c ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0081859c(undefined4 *param_1,int *param_2)

{
  uint *puVar1;
  byte bVar2;
  undefined *puVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  char *pcVar10;
  undefined4 *puVar11;
  int iVar12;
  uint *puVar13;
  uint *puVar14;
  int *piVar15;
  uint *puVar16;
  float10 fVar17;
  float *local_2c;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  char *local_c;
  uint *local_8;
  
  piVar4 = (int *)*param_2;
  iVar12 = *piVar4;
  param_1[1] = iVar12;
  piVar4 = piVar4 + 1;
  *param_1 = piVar4;
  piVar4 = (int *)((int)piVar4 + (iVar12 + 3U & 0xfffffffc));
  iVar12 = *piVar4;
  param_1[3] = iVar12;
  piVar4 = piVar4 + 1;
  param_1[2] = piVar4;
  local_8 = (uint *)((int)piVar4 + (iVar12 + 3U & 0xfffffffc));
  iVar5 = FUN_0080579d();
  iVar6 = FUN_0080579d();
  piVar4 = param_1 + 4;
  FUN_00805cbc(iVar5);
  param_1[5] = iVar5;
  FUN_00805cbc(iVar6);
  local_18 = 0;
  param_1[0xd] = iVar6;
  iVar12 = *local_8;
  if (iVar12 != 0) {
    puVar11 = &DAT_0149f988;
    do {
      puVar11[-2] = iVar12;
      iVar12 = local_8[1];
      local_8 = (uint *)((int)local_8 + 5);
      puVar11[-1] = local_8;
      do {
        uVar8 = *local_8;
        local_8 = (uint *)((int)local_8 + 1);
      } while ((char)uVar8 != '\0');
      iVar7 = 0;
      if (KHandlers != (char)iVar12) {
        local_c = &KHandlers;
        do {
          local_c = local_c + 0xc;
          iVar7 = iVar7 + 1;
        } while (*local_c != (char)iVar12);
      }
      puVar3 = (&PTR_Init_Misc_Load_0083f32c)[iVar7 * 3];
      puVar11[1] = (&PTR_Exec_Misc_Load_0083f330)[iVar7 * 3];
      *puVar11 = puVar3;
      iVar12 = *local_8;
      puVar11 = puVar11 + 4;
      local_18 = local_18 + 1;
    } while (iVar12 != 0);
  }
  local_8 = local_8 + 1;
  local_c = (char *)0x0;
  if (0 < iVar5) {
    local_1c = 0;
    do {
      bVar2 = (byte)*local_8;
      puVar1 = (uint *)((int)local_8 + 1);
      uVar8 = bVar2 & 0x7f;
      puVar14 = (uint *)(*piVar4 + local_1c);
      puVar13 = &DAT_0149f980 + uVar8 * 4;
      puVar16 = puVar14;
      for (iVar12 = 0x26; iVar12 != 0; iVar12 = iVar12 + -1) {
        *puVar16 = 0;
        puVar16 = puVar16 + 1;
      }
      FUN_00817dba(*puVar13);
      *puVar14 = uVar8;
      puVar14[0xb] = *puVar13;
      puVar14[8] = (&DAT_0149f988)[uVar8 * 4];
      puVar14[9] = (&DAT_0149f98c)[uVar8 * 4];
      puVar14[5] = (&DAT_0149f984)[uVar8 * 4];
      puVar14[0xd] = (uint)local_c;
      if ((bVar2 & 0x80) == 0) {
        if ((int)*puVar13 < 0) {
          uVar8 = (uint)*(byte *)puVar1;
          local_8 = (uint *)((int)local_8 + 2);
          goto joined_r0x00818735;
        }
        uVar8 = *puVar13 >> 8 & 0xf;
        local_8 = puVar1;
        goto joined_r0x00818735;
      }
      uVar8 = 1;
      local_8 = puVar1;
      do {
        iVar12 = 0;
        if ((bVar2 & 0x80) == 0) {
          iVar12 = FUN_0080579d();
        }
        iVar12 = (((int)local_c - iVar12) + -1) * 0x98 + *piVar4;
        *(int *)(puVar14[0x1e] + puVar14[0x1b] * 4) = iVar12;
        puVar14[0x1b] = puVar14[0x1b] + 1;
        piVar15 = (int *)(iVar12 + 0x70);
        *piVar15 = *piVar15 + 1;
        uVar8 = uVar8 - 1;
joined_r0x00818735:
      } while (uVar8 != 0);
      local_c = (char *)((int)local_c + 1);
      local_1c = local_1c + 0x98;
    } while ((int)local_c < iVar5);
  }
  if (0 < iVar5) {
    local_1c = 0;
    local_20 = iVar5;
    do {
      iVar12 = *piVar4 + local_1c;
      iVar7 = 0;
      if ((*(uint *)(iVar12 + 0x2c) >> 0xc & 0xf) != 0) {
        do {
          iVar9 = FUN_0080579d();
          if (iVar9 == 0) {
            iVar9 = 0;
          }
          else {
            iVar9 = iVar9 * 0x98 + -0x98 + *piVar4;
          }
          *(int *)(*(int *)(iVar12 + 0x7c) + iVar7 * 4) = iVar9;
          if (iVar9 != 0) {
            *(int *)(iVar9 + 0x70) = *(int *)(iVar9 + 0x70) + 1;
          }
          iVar7 = iVar7 + 1;
        } while (iVar7 < (int)(*(uint *)(iVar12 + 0x2c) >> 0xc & 0xf));
      }
      local_1c = local_1c + 0x98;
      local_20 = local_20 + -1;
    } while (local_20 != 0);
  }
  local_c = (char *)0x0;
  if (0 < local_18) {
    do {
      if (0 < iVar5) {
        local_1c = 0;
        local_24 = iVar5;
        do {
          piVar15 = (int *)(*piVar4 + local_1c);
          if ((char *)*piVar15 == local_c) {
            pcVar10 = (char *)piVar15[5];
            if (*pcVar10 != '\0') {
              iVar12 = 0;
              do {
                iVar7 = (int)*pcVar10;
                if ((0x40 < iVar7) && (iVar7 < 0x5b)) {
                  iVar7 = iVar7 + 0x20;
                }
                if (iVar7 < 0x68) {
                  if (iVar7 == 0x67) {
                    local_2c = (float *)(piVar15[0x24] + iVar12);
                    fVar17 = (float10)FUN_008057d6();
                  }
                  else {
                    if (iVar7 == 0x62) {
                      *(uint *)(iVar12 + piVar15[0x24]) = (uint)(byte)*local_8;
                      local_8 = (uint *)((int)local_8 + 1);
                      goto LAB_0081890a;
                    }
                    if (iVar7 == 99) goto LAB_008188f8;
                    if (iVar7 == 0x65) {
                      local_2c = (float *)(piVar15[0x24] + iVar12);
                      fVar17 = (float10)FUN_008057ba();
                    }
                    else {
                      if (iVar7 != 0x66) goto LAB_0081890a;
                      local_2c = (float *)(piVar15[0x24] + iVar12);
                      fVar17 = (float10)FUN_00805853();
                    }
                  }
                  *local_2c = (float)fVar17;
                }
                else if (iVar7 == 0x69) {
LAB_008188f8:
                  *(uint *)(iVar12 + piVar15[0x24]) = *local_8;
                  local_8 = local_8 + 1;
                }
                else if (iVar7 == 0x6d) {
                  *(uint *)(iVar12 + piVar15[0x24]) = *local_8 & 0xffffff;
                  local_8 = (uint *)((int)local_8 + 3);
                }
                else if (iVar7 == 0x73) {
                  *(int *)(iVar12 + piVar15[0x24]) = (int)(short)(ushort)*local_8;
                  local_8 = (uint *)((int)local_8 + 2);
                }
LAB_0081890a:
                iVar12 = iVar12 + 4;
                pcVar10 = pcVar10 + 1;
              } while (*pcVar10 != '\0');
            }
            iVar12 = 0;
            if ((*(byte *)((int)piVar15 + 0x2e) & 0xf) != 0) {
              do {
                *(uint **)(piVar15[0x21] + iVar12 * 4) = local_8;
                for (; (byte)*local_8 != 0; local_8 = (uint *)((int)local_8 + 1)) {
                }
                local_8 = (uint *)((int)local_8 + 1);
                iVar12 = iVar12 + 1;
              } while (iVar12 < (int)(*(byte *)((int)piVar15 + 0x2e) & 0xf));
            }
            iVar12 = 0;
            if (((uint)piVar15[0xb] >> 0x14 & 0xf) != 0) {
              do {
                uVar8 = *local_8;
                local_8 = (uint *)((int)local_8 + 2);
                if ((ushort)uVar8 == 0) {
                  iVar7 = 0;
                }
                else {
                  iVar7 = (uint)(ushort)uVar8 * 0x28 + -0x28 + param_1[0xc];
                }
                *(int *)(piVar15[0x22] + iVar12 * 4) = iVar7;
                iVar12 = iVar12 + 1;
              } while (iVar12 < (int)((uint)piVar15[0xb] >> 0x14 & 0xf));
            }
          }
          local_1c = local_1c + 0x98;
          local_24 = local_24 + -1;
        } while (local_24 != 0);
      }
      local_c = (char *)((int)local_c + 1);
    } while ((int)local_c < local_18);
  }
  if (0 < iVar5) {
    iVar12 = 0;
    do {
      iVar9 = FUN_00817b33();
      iVar7 = *piVar4;
      *(uint **)(iVar7 + iVar12 + 0x8c) = local_8;
      *(int *)(iVar7 + iVar12 + 0x68) = iVar9;
      local_8 = (uint *)((int)local_8 + iVar9);
      iVar12 = iVar12 + 0x98;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  FUN_00805cbc(0);
  iVar12 = FUN_0080579d();
  FUN_00806ae3();
  for (; iVar12 != 0; iVar12 = iVar12 + -1) {
    piVar15 = (int *)FUN_00806b54();
    FUN_00817d8d();
    iVar5 = FUN_0080579d();
    *piVar15 = iVar5 * 0x98 + *piVar4;
    piVar15[2] = *local_8;
    piVar15[3] = local_8[1];
    fVar17 = (float10)FUN_00805853();
    piVar15[10] = (int)(float)fVar17;
    fVar17 = (float10)FUN_00805853();
    piVar15[0xb] = (int)(float)fVar17;
    piVar15[0xc] = (uint)(byte)local_8[2];
    fVar17 = (float10)FUN_00805853();
    piVar15[0xd] = (int)(float)fVar17;
    fVar17 = (float10)FUN_00805853();
    piVar15[0xe] = (int)(float)fVar17;
    fVar17 = (float10)FUN_00805853();
    piVar15[0xf] = (int)(float)fVar17;
    fVar17 = (float10)FUN_00805853();
    piVar15[0x11] = (int)(float)fVar17;
    fVar17 = (float10)FUN_00805853();
    piVar15[0x12] = (int)(float)fVar17;
    fVar17 = (float10)FUN_00805853();
    piVar15[0x13] = (int)(float)fVar17;
    fVar17 = (float10)FUN_00805853();
    piVar15[0x15] = (int)(float)fVar17;
    fVar17 = (float10)FUN_00805853();
    piVar15[0x16] = (int)(float)fVar17;
    fVar17 = (float10)FUN_00805853();
    piVar15[0x17] = (int)(float)fVar17;
    piVar15[0x19] = *(int *)((int)local_8 + 9);
    local_8 = (uint *)((int)local_8 + 0xd);
    FUN_0080579d();
    piVar15[0x1a] = 0;
    FUN_00805a4d();
  }
  if (0 < iVar6) {
    local_18 = 0;
    local_24 = iVar6;
    do {
      bVar2 = (byte)*local_8;
      piVar15 = (int *)(param_1[0xc] + local_18);
      local_8 = (uint *)((int)local_8 + 1);
      local_1c = 0;
      piVar15[8] = bVar2 & 7;
      piVar15[9] = (int)(uint)bVar2 >> 3;
      piVar4 = piVar15;
      if ((bVar2 & 7) != 0) {
        do {
          iVar12 = FUN_0080579d();
          *piVar4 = iVar12;
          iVar12 = operator_new(iVar12 << 3);
          iVar5 = 0;
          piVar4[1] = iVar12;
          if (0 < *piVar4) {
            do {
              *(float *)(piVar4[1] + iVar5 * 8) = (float)(byte)*local_8 * _DAT_0081f388;
              local_8 = (uint *)((int)local_8 + 1);
              fVar17 = (float10)FUN_008057d6();
              *(float *)(piVar4[1] + 4 + iVar5 * 8) = (float)fVar17;
              iVar5 = iVar5 + 1;
            } while (iVar5 < *piVar4);
          }
          local_1c = local_1c + 1;
          piVar4 = piVar4 + 2;
        } while (local_1c < piVar15[8]);
      }
      local_18 = local_18 + 0x28;
      local_24 = local_24 + -1;
    } while (local_24 != 0);
  }
  *param_2 = (int)local_8;
  return;
}


/* ---- FUN_00818ba7 @ 00818ba7 ---- */

void __fastcall FUN_00818ba7(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = 0;
  if (0 < *(int *)(param_1 + 0x24)) {
    do {
      FUN_0081805e(*(int *)(param_1 + 0x20) + iVar1);
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 0xb4;
    } while (iVar2 < *(int *)(param_1 + 0x24));
  }
  return;
}


/* ---- FUN_00818bd9 @ 00818bd9 ---- */

uint __thiscall FUN_00818bd9(int param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  uint local_8;
  
  local_8 = 0;
  if (((*(int *)(param_1 + 0x3c) == 0) || (*(int *)(param_1 + 8) != 0)) ||
     (*(int *)(param_1 + 0x18) == 0)) {
    puVar6 = *(undefined4 **)(param_1 + 0x90);
    puVar7 = *(undefined4 **)(param_1 + 0x94);
    for (uVar4 = *(uint *)(param_1 + 0x5c) & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
    *(undefined4 *)(param_1 + 0x3c) = 1;
    uVar2 = FUN_008180a6(param_1,*(undefined4 *)(param_1 + 0x8c));
    local_8 = 1;
    *(undefined4 *)(param_1 + 0x38) = 0;
    if ((*(byte *)(param_1 + 0x2f) & 2) != 0) {
      *(undefined4 *)(param_1 + 0x38) = 1;
    }
    if (**(char **)(param_1 + 0x8c) != '\x01') {
      *(undefined4 *)(param_1 + 0x38) = 0;
    }
    iVar5 = 0;
    if (0 < *(int *)(param_1 + 0x6c)) {
      iVar3 = *(int *)(param_1 + 0x78);
      do {
        if (*(int *)(iVar3 + iVar5 * 4) != 0) {
          uVar4 = FUN_00818bd9(param_2,param_3,0);
          local_8 = local_8 | uVar4;
          iVar3 = *(int *)(*(int *)(param_1 + 0x78) + iVar5 * 4);
          FUN_00817a8a(*(undefined4 *)(iVar3 + 0x44),*(undefined4 *)(iVar3 + 0x48));
          iVar3 = *(int *)(param_1 + 0x78);
          piVar1 = (int *)(iVar3 + iVar5 * 4);
          *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) & *(uint *)(*piVar1 + 0x38);
          *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) & *(uint *)(*piVar1 + 0x3c);
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < *(int *)(param_1 + 0x6c));
    }
    if (((*(byte *)(param_1 + 0x2f) & 0x10) == 0) && (iVar5 = 0, 0 < *(int *)(param_1 + 0x54))) {
      iVar3 = *(int *)(param_1 + 0x7c);
      do {
        if (*(int *)(iVar3 + iVar5 * 4) != 0) {
          uVar4 = FUN_00818bd9(param_2,param_3,0);
          local_8 = local_8 | uVar4;
          iVar3 = *(int *)(*(int *)(param_1 + 0x7c) + iVar5 * 4);
          FUN_00817a8a(*(undefined4 *)(iVar3 + 0x44),*(undefined4 *)(iVar3 + 0x48));
          iVar3 = *(int *)(param_1 + 0x7c);
          piVar1 = (int *)(iVar3 + iVar5 * 4);
          *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) & *(uint *)(*piVar1 + 0x38);
          *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) & *(uint *)(*piVar1 + 0x3c);
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < *(int *)(param_1 + 0x54));
    }
    iVar3 = FUN_00817902(param_2);
    *(int *)(param_1 + 0x18) = iVar3;
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0x70);
    iVar5 = *(int *)(param_1 + 0x14);
    *(undefined4 *)(param_1 + 8) = 0;
    *(uint *)(param_1 + 0x28) = (uint)(iVar3 == 0);
    if (iVar5 < 0x61) {
      iVar5 = 0x60;
    }
    *(int *)(param_1 + 0x14) = iVar5;
    FUN_00817b4a(uVar2);
  }
  return local_8;
}


/* ---- FUN_00818d42 @ 00818d42 ---- */

void __thiscall FUN_00818d42(int param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int local_60c [384];
  undefined4 local_c;
  int local_8;
  
  local_c = FUN_008180a6(param_1,*(undefined4 *)(param_1 + 0x8c));
  if ((*(uint *)(param_1 + 0x2c) & 0x4000000) == 0) {
    uVar1 = *(uint *)(param_1 + 0x2c) & 0xff;
    local_60c[1] = param_2;
    iVar4 = 2;
    if (uVar1 != 0) {
      iVar2 = *(int *)(param_1 + 0x94);
      do {
        local_60c[iVar4] = *(int *)(iVar2 + iVar4 * 4 + -8);
        iVar4 = iVar4 + 1;
        uVar1 = uVar1 - 1;
      } while (uVar1 != 0);
    }
    uVar1 = *(uint *)(param_1 + 0x2c) >> 0x10 & 0xf;
    if (uVar1 != 0) {
      piVar3 = *(int **)(param_1 + 0x84);
      do {
        local_60c[iVar4] = *piVar3;
        iVar4 = iVar4 + 1;
        piVar3 = piVar3 + 1;
        uVar1 = uVar1 - 1;
      } while (uVar1 != 0);
    }
    uVar1 = *(uint *)(param_1 + 0x2c) >> 0x14 & 0xf;
    local_8 = 0;
    local_60c[0] = param_1;
    if (uVar1 != 0) {
      do {
        iVar2 = FUN_00817894(local_8);
        local_60c[iVar4] = iVar2;
        iVar4 = iVar4 + 1;
        local_8 = local_8 + 1;
      } while (local_8 < (int)uVar1);
    }
    if ((*(byte *)(param_1 + 0x2f) & 8) != 0) {
      local_60c[iVar4] = *(int *)(param_1 + 0x70);
      iVar4 = iVar4 + 1;
    }
    FUN_008178cb(iVar4);
  }
  else {
    (**(code **)(param_1 + 0x24))(param_1,param_2);
  }
  FUN_00817b4a(local_c);
  iVar4 = *(int *)(param_1 + 0x14);
  if (iVar4 < 0x61) {
    iVar4 = 0x60;
  }
  *(int *)(param_1 + 0x14) = iVar4;
  return;
}


/* ---- FUN_00818e4a @ 00818e4a ---- */

void __thiscall FUN_00818e4a(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar1 = *(int *)(param_1 + 0x6c);
  iVar3 = 0;
  if (0 < iVar1) {
    do {
      uVar4 = param_2;
      FUN_0080e106(iVar3);
      FUN_00818d42(uVar4);
      iVar3 = iVar3 + 1;
    } while (iVar3 < iVar1);
  }
  if ((*(byte *)(param_1 + 0x2f) & 0x10) == 0) {
    iVar1 = *(int *)(param_1 + 0x54);
    iVar3 = 0;
    if (0 < iVar1) {
      do {
        iVar2 = FUN_0080e11f(iVar3);
        if (iVar2 != 0) {
          FUN_00818d42(param_2);
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < iVar1);
    }
  }
  return;
}


/* ---- FUN_00818ea3 @ 00818ea3 ---- */

void FUN_00818ea3(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_0080e106(param_2);
  if (iVar1 != 0) {
    FUN_00818d42(param_1);
  }
  return;
}


/* ---- FUN_00818ec0 @ 00818ec0 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00818ec0(int param_1,int param_2,int param_3)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  undefined4 *puVar4;
  
  fVar1 = (float)param_2 * _DAT_0081f384;
  pfVar3 = (float *)(param_1 + 0x1134);
  for (iVar2 = 0x80; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = 0.0;
    pfVar3 = pfVar3 + 1;
  }
  *(float *)(param_1 + 0x1134) = fVar1;
  *(float *)(param_1 + 0x1138) = fVar1;
  *(float *)(param_1 + 0x113c) = fVar1;
  *(float *)(param_1 + 0x1140) = fVar1;
  *(undefined4 *)(param_1 + 0x1174) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x1178) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x117c) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x1180) = 0;
  puVar4 = (undefined4 *)(param_1 + 0x10);
  for (iVar2 = 0x400; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = (undefined4 *)(param_1 + 0x1010);
  for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  *(undefined4 *)(param_1 + 0x1110) = 0;
  FUN_0080221c();
  FUN_00805a4d();
  *(int *)(param_1 + 0x14d4) = param_2;
  *(int *)(param_1 + 0x14dc) = *(int *)(param_1 + 0x14d8);
  iVar2 = *(int *)(param_1 + 0x14dc);
  *(int *)(param_1 + 0x14d8) = param_3;
  *(int *)(param_1 + 0x14e0) = param_3 - iVar2;
  *(undefined4 *)(param_1 + 0x9530) = 1;
  *(undefined4 *)(param_1 + 0x9534) = 0;
  *(undefined4 *)(param_1 + 0x9538) = 0;
  *(undefined4 *)(param_1 + 0x9588) = 0;
  *(undefined4 *)(param_1 + 0x9584) = 0;
  *(undefined4 *)(param_1 + 0x1334) = 0;
  *(undefined4 *)(param_1 + 0x1338) = 0;
  *(undefined4 *)(param_1 + 0x133c) = 0;
  *(undefined4 *)(param_1 + 0x9580) = 0;
  *(undefined4 *)(param_1 + 0x14ec) = 0;
  *(int *)(param_1 + 0x14e4) = param_3 / 10 - iVar2 / 10;
  *(int *)(param_1 + 0x14e8) = param_3 % 10;
  param_2 = 0;
  if (0 < *(int *)(param_1 + 0x1118)) {
    do {
      FUN_0081805e(*(undefined4 *)(*(int *)(param_1 + 0x1114) + param_2 * 4));
      param_2 = param_2 + 1;
    } while (param_2 < *(int *)(param_1 + 0x1118));
  }
  iVar2 = *(int *)(param_1 + 0x1348);
  *(int *)(param_1 + 0x1344) = 0;
  *(int *)(param_1 + 0x1340) = iVar2;
  if (iVar2 == 0) {
    *(int *)(param_1 + 0x1344) = param_1 + 0x1348;
  }
  return;
}


/* ---- FUN_00819016 @ 00819016 ---- */

void __thiscall FUN_00819016(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  if (0 < *(int *)(param_1 + 0x14)) {
    local_c = 0;
    do {
      iVar2 = *(int *)(param_1 + 0x10) + local_c;
      FUN_00818bd9(param_2,1,1);
      iVar1 = 0;
      if (0 < *(int *)(iVar2 + 0x6c)) {
        do {
          FUN_0080e106(iVar1);
          FUN_00817acc();
          iVar1 = iVar1 + 1;
        } while (iVar1 < *(int *)(iVar2 + 0x6c));
      }
      iVar1 = 0;
      if (0 < *(int *)(iVar2 + 0x54)) {
        do {
          FUN_0080e11f(iVar1);
          FUN_00817acc();
          iVar1 = iVar1 + 1;
        } while (iVar1 < *(int *)(iVar2 + 0x54));
      }
      FUN_008040d8(local_8,*(undefined4 *)(param_1 + 0x14));
      local_8 = local_8 + 1;
      local_c = local_c + 0x98;
    } while (local_8 < *(int *)(param_1 + 0x14));
  }
  return;
}


/* ---- Exec_Misc_Load @ 008190a3 ---- */

void Exec_Misc_Load(undefined4 param_1,undefined4 param_2)

{
  FUN_0080e11f(0);
  FUN_00818d42(param_2);
  return;
}


/* ---- Exec_Misc_Delay @ 008190be ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Exec_Misc_Delay(undefined4 param_1,int param_2,uint param_3,int param_4,float param_5,
                    float param_6,float param_7,float param_8,float param_9)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = FUN_00817b57(param_1,0x1c);
  if (*(char *)(iVar5 + 0x10) != '\0') {
    *(undefined4 *)(iVar5 + 0x14) = 0;
    *(undefined4 *)(iVar5 + 0x18) = 0;
  }
  if ((param_3 & 0xc0) == 0) {
    param_6 = 0.0;
    fVar2 = 0.0;
    param_5 = 0.5;
    if (*(int *)(param_2 + 0x1358) != -0x14fe8) {
      fVar2 = (float)*(byte *)(*(int *)(param_2 + 0x1358) + 0x14fe8 + param_4);
    }
  }
  else {
    fVar2 = *(float *)(((int)param_3 >> 6 & 3U) * 0x10 + 0x1134 + param_2);
  }
  if ((*(int *)(iVar5 + 0x14) == 2) && (fVar2 < param_5 - param_6)) {
    *(undefined4 *)(iVar5 + 0x14) = 3;
    *(undefined4 *)(iVar5 + 0x18) = 0;
  }
  if ((*(int *)(iVar5 + 0x14) == 0) && (param_5 + param_6 < fVar2)) {
    *(undefined4 *)(iVar5 + 0x14) = 1;
    *(undefined4 *)(iVar5 + 0x18) = 0;
  }
  fVar4 = _DAT_0081f2bc;
  fVar2 = (float)(*(int *)(param_2 + 0x14d8) - *(int *)(param_2 + 0x14dc)) * _DAT_0081f2c4;
  if (fVar2 < _DAT_0081f374) {
    fVar2 = 0.0;
  }
  iVar3 = *(int *)(iVar5 + 0x14);
  if (iVar3 == 1) {
    if (param_7 <= _DAT_0081f374) {
      fVar2 = 1.0;
    }
    else {
      fVar2 = fVar2 / param_7 + *(float *)(iVar5 + 0x18);
    }
    *(float *)(iVar5 + 0x18) = fVar2;
    if (*(float *)(iVar5 + 0x18) < _DAT_0081f2bc) goto LAB_00819274;
    *(undefined4 *)(iVar5 + 0x14) = 2;
  }
  else if (iVar3 == 2) {
    if (param_8 <= _DAT_0081f374) goto LAB_00819274;
    fVar2 = fVar2 / param_8 + *(float *)(iVar5 + 0x18);
    *(float *)(iVar5 + 0x18) = fVar2;
    if (fVar4 < fVar2) {
      *(float *)(iVar5 + 0x18) = fVar2 - _DAT_0081f2bc;
    }
    if (*(float *)(iVar5 + 0x18) <= _DAT_0081f2bc) goto LAB_00819274;
  }
  else {
    if (iVar3 != 3) goto LAB_00819274;
    if (param_9 <= _DAT_0081f374) {
      fVar2 = 1.0;
    }
    else {
      fVar2 = fVar2 / param_9 + *(float *)(iVar5 + 0x18);
    }
    *(float *)(iVar5 + 0x18) = fVar2;
    if (*(float *)(iVar5 + 0x18) < _DAT_0081f2bc) goto LAB_00819274;
    *(undefined4 *)(iVar5 + 0x14) = 0;
  }
  *(undefined4 *)(iVar5 + 0x18) = 0;
LAB_00819274:
  iVar3 = *(int *)(iVar5 + 0x14);
  fVar2 = 0.0;
  if (iVar3 == 1) {
    fVar2 = *(float *)(iVar5 + 0x18);
  }
  if (iVar3 == 2) {
    fVar2 = 1.0;
  }
  uVar6 = param_3 & 0xf;
  if (uVar6 == 0) {
    if (iVar3 == 3) {
      fVar2 = 1.0 - *(float *)(iVar5 + 0x18);
    }
  }
  else if (uVar6 == 1) {
    if (iVar3 == 3) {
      fVar2 = *(float *)(iVar5 + 0x18) + _DAT_0081f2bc;
    }
    fVar2 = fVar2 * _DAT_0081f2ac;
  }
  else if (uVar6 == 2) {
    if (iVar3 == 2) {
      fVar2 = *(float *)(iVar5 + 0x18) + *(float *)(iVar5 + 0x18) + _DAT_0081f2bc;
    }
    if (iVar3 == 3) {
      fVar2 = *(float *)(iVar5 + 0x18) + _DAT_0081f368;
    }
    fVar2 = fVar2 * _DAT_0081f370;
  }
  pfVar1 = (float *)(((int)param_3 >> 4 & 3U) * 0x10 + 0x1134 + param_2);
  *pfVar1 = fVar2;
  pfVar1[1] = fVar2;
  pfVar1[2] = fVar2;
  pfVar1[3] = fVar2;
  FUN_00818ea3(param_2,0);
  return;
}


/* ---- Exec_Misc_SetIf @ 00819316 ---- */

void Exec_Misc_SetIf(undefined4 param_1,int param_2,int param_3,uint param_4,int param_5)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar6 = (float)(*(byte *)(*(int *)(param_2 + 0x1358) + 0x14fe8 + param_3) == param_4);
  pfVar1 = (float *)(param_5 * 0x10 + 0x1134 + param_2);
  fVar2 = *pfVar1;
  fVar3 = pfVar1[1];
  fVar4 = pfVar1[2];
  fVar5 = pfVar1[3];
  *pfVar1 = fVar6;
  pfVar1[1] = fVar6;
  pfVar1[2] = fVar6;
  pfVar1[3] = fVar6;
  FUN_00818e4a(param_2);
  *pfVar1 = fVar2;
  pfVar1[1] = fVar3;
  pfVar1[2] = fVar4;
  pfVar1[3] = fVar5;
  return;
}


/* ---- Exec_Misc_State @ 0081937b ---- */

void Exec_Misc_State(undefined4 param_1,int param_2,int param_3,undefined1 param_4,int param_5,
                    int param_6,uint param_7)

{
  int iVar1;
  bool bVar2;
  
  switch(param_5) {
  case 0:
    goto switchD_0081938e_caseD_0;
  case 1:
    bVar2 = *(int *)(*(int *)(param_2 + 0x1358) + 0x1553c) == 0x20;
    break;
  case 2:
    bVar2 = *(int *)(*(int *)(param_2 + 0x1358) + 0x1553c) == 10;
    break;
  case 3:
    iVar1 = *(int *)(*(int *)(param_2 + 0x1358) + 0x1553c);
    if (iVar1 != 8) {
      bVar2 = iVar1 == 0x1b;
      break;
    }
    goto switchD_0081938e_caseD_0;
  case 4:
    bVar2 = *(int *)(*(int *)(param_2 + 0x1358) + 0x1553c) == 0x10000;
    break;
  case 5:
    bVar2 = *(int *)(*(int *)(param_2 + 0x1358) + 0x1553c) == 0x10001;
    break;
  case 6:
    bVar2 = *(int *)(*(int *)(param_2 + 0x1358) + 0x1553c) == 0x10002;
    break;
  case 7:
    bVar2 = *(int *)(*(int *)(param_2 + 0x1358) + 0x1553c) == 0x10003;
    break;
  default:
    goto switchD_0081938e_default;
  }
  if (bVar2) {
switchD_0081938e_caseD_0:
    if (((*(byte *)(*(int *)(param_2 + 0x1358) + 0x14fe8 + param_6) == param_7) && (param_3 != 0))
       && (*(undefined1 *)(*(int *)(param_2 + 0x1358) + 0x14fe8 + param_3) = param_4, param_5 != 0))
    {
      *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x1553c) = 0;
    }
  }
switchD_0081938e_default:
  FUN_00818e4a(param_2);
  return;
}


/* ---- Exec_Misc_PlaySample @ 00819479 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Exec_Misc_PlaySample
               (undefined4 param_1,int param_2,uint param_3,float param_4,float param_5,
               undefined4 param_6,float param_7,float param_8,float param_9)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  undefined4 local_54 [16];
  float local_14;
  float local_c;
  
  iVar1 = FUN_00817b57(param_1,0x20);
  if (*(char *)(iVar1 + 0x10) != '\0') {
    *(undefined4 *)(iVar1 + 0x18) = 0xffffffff;
    *(uint *)(iVar1 + 0x1c) = (uint)*(byte *)(*(int *)(param_2 + 0x1358) + 0x14fe8 + param_3);
  }
  uVar3 = (uint)*(byte *)(*(int *)(param_2 + 0x1358) + 0x14fe8 + param_3);
  if (((float)uVar3 != param_4) || (param_3 = 1, param_5 <= _DAT_0081f374)) {
    param_3 = 0;
  }
  if (param_4 == -NAN) {
    param_3 = (uint)(uVar3 != *(uint *)(iVar1 + 0x1c));
  }
  *(uint *)(iVar1 + 0x1c) = uVar3;
  if ((-1 < *(int *)(iVar1 + 0x18)) &&
     (iVar2 = *(int *)(iVar1 + 0x18) - *(int *)(param_2 + 0x14e0), *(int *)(iVar1 + 0x18) = iVar2,
     iVar2 < 0)) {
    *(undefined4 *)(iVar1 + 0x14) = 0;
  }
  if ((param_3 != 0) && (*(int *)(iVar1 + 0x14) == 0)) {
    fVar6 = (float10)FUN_008056db(_DAT_0081fd30,(double)(param_7 * _DAT_0081fd38));
    param_4 = 0.0;
    if (param_9 != _DAT_0081f374) {
      puVar4 = (undefined4 *)(param_2 + 0x1478);
      puVar5 = local_54;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      FUN_008064ec();
      FUN_00806305(local_54,param_2 + 0x9520);
      param_4 = local_14 / ABS(local_c + _DAT_0081fd28);
      param_9 = param_9 * _DAT_0081f2ac;
      fVar7 = (float10)FUN_00806202();
      fVar7 = (float10)param_9 / fVar7;
      if ((float10)_DAT_0081f2bc < fVar7) {
        fVar7 = (float10)1;
      }
      fVar6 = fVar7 * (float10)(float)fVar6;
    }
    FUN_00804a47(param_6,(float)fVar6,param_4,0xac44);
    if (_DAT_0081f374 < param_8) {
      *(int *)(iVar1 + 0x18) = (int)ROUND(param_8 * _DAT_0081fc24);
    }
  }
  *(uint *)(iVar1 + 0x14) = param_3;
  FUN_00818e4a();
  return;
}


/* ---- FUN_0081961c @ 0081961c ---- */

void FUN_0081961c(int param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  iVar1 = *param_2;
  uVar2 = *(undefined4 *)(param_1 + 0x1344);
  uVar3 = *(undefined4 *)(param_1 + 0x1340);
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0x1340) = 0;
    *(int **)(param_1 + 0x1344) = param_2;
  }
  else {
    *(undefined4 *)(param_1 + 0x1344) = 0;
    *(int *)(param_1 + 0x1340) = iVar1;
  }
  FUN_00818d42(param_1);
  *(undefined4 *)(param_1 + 0x1340) = uVar3;
  *(undefined4 *)(param_1 + 0x1344) = uVar2;
  return;
}


/* ---- FUN_0081966f @ 0081966f ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0081966f(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float local_9c [32];
  undefined4 local_1c;
  float *local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_8;
  
  local_8 = *(undefined4 *)(param_1 + 0x1338);
  local_14 = *(undefined4 *)(param_1 + 0x1334);
  local_1c = *(undefined4 *)(param_1 + 0x953c);
  pfVar6 = (float *)(param_1 + 0x1134);
  uVar2 = *(undefined4 *)(param_1 + 0x133c);
  pfVar5 = pfVar6;
  pfVar7 = local_9c;
  for (iVar4 = 0x20; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar7 = *pfVar5;
    pfVar5 = pfVar5 + 1;
    pfVar7 = pfVar7 + 1;
  }
  if (*(int *)(param_2 + 8) < *(int *)(param_2 + 0xc)) {
    fVar3 = (float)(*(int *)(param_1 + 0x14d4) - *(int *)(param_2 + 8)) /
            (float)(*(int *)(param_2 + 0xc) - *(int *)(param_2 + 8));
    if (_DAT_0081f2bc <= fVar3) {
      fVar3 = 1.0;
      goto LAB_00819703;
    }
    if (fVar3 < _DAT_0081f374 == (fVar3 == _DAT_0081f374)) goto LAB_00819703;
  }
  fVar3 = 0.0;
LAB_00819703:
  *(float *)(param_1 + 0x1140) = fVar3;
  *(float *)(param_1 + 0x113c) = fVar3;
  *(float *)(param_1 + 0x1138) = fVar3;
  *pfVar6 = fVar3;
  uVar1 = *(undefined4 *)(param_2 + 0x28);
  *(undefined4 *)(param_1 + 0x1150) = uVar1;
  *(undefined4 *)(param_1 + 0x114c) = uVar1;
  *(undefined4 *)(param_1 + 0x1148) = uVar1;
  *(undefined4 *)(param_1 + 0x1144) = uVar1;
  uVar1 = *(undefined4 *)(param_2 + 0x2c);
  *(undefined4 *)(param_1 + 0x1160) = uVar1;
  *(undefined4 *)(param_1 + 0x115c) = uVar1;
  *(undefined4 *)(param_1 + 0x1158) = uVar1;
  *(undefined4 *)(param_1 + 0x1154) = uVar1;
  fVar3 = (float)(int)ROUND((float)*(int *)(param_2 + 0x30));
  *(float *)(param_1 + 0x1170) = fVar3;
  *(float *)(param_1 + 0x116c) = fVar3;
  *(float *)(param_1 + 0x1168) = fVar3;
  *(float *)(param_1 + 0x1164) = fVar3;
  *(undefined4 *)(param_1 + 0x1174) = *(undefined4 *)(param_2 + 0x34);
  *(undefined4 *)(param_1 + 0x1178) = *(undefined4 *)(param_2 + 0x38);
  *(undefined4 *)(param_1 + 0x117c) = *(undefined4 *)(param_2 + 0x3c);
  *(undefined4 *)(param_1 + 0x1180) = *(undefined4 *)(param_2 + 0x40);
  *(undefined4 *)(param_1 + 0x1184) = *(undefined4 *)(param_2 + 0x44);
  *(undefined4 *)(param_1 + 0x1188) = *(undefined4 *)(param_2 + 0x48);
  *(undefined4 *)(param_1 + 0x118c) = *(undefined4 *)(param_2 + 0x4c);
  *(undefined4 *)(param_1 + 0x1190) = *(undefined4 *)(param_2 + 0x50);
  *(undefined4 *)(param_1 + 0x1194) = *(undefined4 *)(param_2 + 0x54);
  *(undefined4 *)(param_1 + 0x1198) = *(undefined4 *)(param_2 + 0x58);
  *(undefined4 *)(param_1 + 0x119c) = *(undefined4 *)(param_2 + 0x5c);
  *(undefined4 *)(param_1 + 0x11a0) = *(undefined4 *)(param_2 + 0x60);
  local_18 = pfVar6;
  local_10 = uVar2;
  FUN_00805cf1(*(undefined4 *)(param_2 + 100));
  uVar2 = *(undefined4 *)(param_2 + 0xac);
  *(int *)(param_1 + 0x133c) = param_2;
  *(undefined4 *)(param_1 + 0x1338) = uVar2;
  FUN_0081961c(param_1,param_2 + 0x1c);
  *(undefined4 *)(param_1 + 0x953c) = local_1c;
  *(undefined4 *)(param_1 + 0x1334) = local_14;
  *(undefined4 *)(param_1 + 0x1338) = local_8;
  *(undefined4 *)(param_1 + 0x133c) = local_10;
  pfVar6 = local_9c;
  for (iVar4 = 0x20; iVar4 != 0; iVar4 = iVar4 + -1) {
    *local_18 = *pfVar6;
    pfVar6 = pfVar6 + 1;
    local_18 = local_18 + 1;
  }
  return;
}


/* ---- FUN_008197eb @ 008197eb ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __fastcall FUN_008197eb(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  undefined4 *puVar6;
  uint local_8;
  
  *(undefined4 *)(param_1 + 0x1334) = 0;
  *(undefined4 *)(param_1 + 0x1338) = 0;
  *(undefined4 *)(param_1 + 0x1350) = 0;
  *(undefined4 *)(param_1 + 0x1354) = 0;
  FUN_0080575d(0x40000);
  *(undefined4 *)(param_1 + 0x14dc) = 0;
  *(undefined4 *)(param_1 + 0x1348) = 0;
  *(undefined4 *)(param_1 + 0x1340) = 0;
  *(undefined4 *)(param_1 + 0x1344) = 0;
  FUN_00805cbc(0);
  FUN_00805cbc(0);
  FUN_00818ec0(0,0);
  fVar3 = _DAT_0081fd3c;
  *(undefined4 *)(param_1 + 0x134c) = 0;
  puVar6 = (undefined4 *)(param_1 + 0x14f0);
  for (iVar4 = 0x2000; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  local_8 = 0;
  pfVar5 = (float *)(param_1 + 0x18f4);
  do {
    iVar4 = (int)local_8 / 8;
    fVar1 = (float)(local_8 & 7) * fVar3;
    pfVar5[-1] = fVar1;
    local_8 = local_8 + 1;
    fVar2 = (float)iVar4 * fVar3;
    *pfVar5 = fVar2;
    pfVar5[1] = fVar1 + fVar3;
    pfVar5[2] = fVar2 + fVar3;
    pfVar5 = pfVar5 + 4;
  } while ((int)local_8 < 0x40);
  *(undefined4 *)(param_1 + 0x1358) = 0;
  *(undefined4 *)(param_1 + 0x953c) = 0;
  return param_1;
}


/* ---- FUN_008198ce @ 008198ce ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_008198ce(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_1c = _DAT_0081f378;
  local_18 = _DAT_0081f378;
  local_14 = 0x3f800000;
  puVar4 = *(undefined4 **)(param_1 + 0x9588);
  local_10 = 0x3f800000;
  local_c = *(int *)(param_1 + 0x9584);
  *(undefined4 *)(param_1 + 0x9588) = 0;
  *(int *)(param_1 + 0x9584) = 0;
  iVar2 = local_c;
  local_8 = param_1;
  if (*(int *)(param_2 + 0x14960) == 0) {
    for (; iVar3 = local_c, iVar2 != 0; iVar2 = *(int *)(iVar2 + 0xdc)) {
    }
  }
  else {
    FUN_0081830f(0,&local_1c,param_1 + 0x9540);
    uVar1 = _DAT_0081f378;
    for (; iVar3 = local_c, puVar4 != (undefined4 *)0x0; puVar4 = (undefined4 *)*puVar4) {
      if ((puVar4[3] != 0) &&
         ((*(char *)(puVar4[1] + 0x4d) != '\0' || (*(char *)(puVar4[2] + 0x4d) != '\0')))) {
        *(undefined1 *)(puVar4[3] + 0x4d) = 1;
        *(undefined1 *)(puVar4[3] + 0x4e) = 1;
        iVar2 = puVar4[3];
        *(undefined4 *)(iVar2 + 0x58) = uVar1;
        *(undefined4 *)(iVar2 + 0x54) = uVar1;
        *(undefined4 *)(iVar2 + 0x5c) = 0x3f800000;
        *(undefined4 *)(iVar2 + 0x60) = 0x3f800000;
      }
    }
  }
  for (; iVar3 != 0; iVar3 = *(int *)(iVar3 + 0xdc)) {
    if (*(char *)(iVar3 + 0x4d) != '\0') {
      *(undefined1 *)(iVar3 + 0x4d) = 0;
      FUN_008067af(iVar3 + 0x54);
      puVar4 = (undefined4 *)(iVar3 + 0xe0);
      puVar5 = (undefined4 *)(param_1 + 0x94f0);
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      *(int *)(local_8 + 0x953c) = iVar3;
      FUN_0081961c(local_8,*(int *)(iVar3 + 0x120) + 0x4c);
      param_1 = local_8;
    }
  }
  *(undefined4 *)(param_1 + 0x953c) = 0;
  return;
}


/* ---- Exec_Misc_Time @ 008199f8 ---- */

void Exec_Misc_Time(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x1c);
  if (iVar1 != 0) {
    uVar2 = 0;
    FUN_0080e106(0);
    FUN_0081966f(param_2,iVar1,uVar2);
  }
  return;
}


/* ---- Exec_Misc_Event @ 00819a1d ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Exec_Misc_Event(int param_1,int param_2,float param_3)

{
  int iVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  for (iVar1 = *(int *)(param_1 + 0x1c); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
    if (*(int *)(iVar1 + 8) == *(int *)(iVar1 + 0xc)) {
      fVar2 = param_3 * _DAT_0081fb84;
      *(undefined4 *)(iVar1 + 8) = *(undefined4 *)(param_2 + 0x14d4);
      *(int *)(iVar1 + 0xc) = *(int *)(iVar1 + 8) + (int)ROUND(fVar2);
    }
    uVar5 = 0;
    iVar3 = param_2;
    iVar4 = iVar1;
    FUN_0080e106(0);
    FUN_0081966f(iVar3,iVar4,uVar5);
  }
  return;
}


/* ---- Exec_Misc_Trigger @ 00819a7f ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Exec_Misc_Trigger(undefined4 param_1,int param_2,float param_3,float param_4,float param_5,
                      float param_6,byte param_7,int param_8,int param_9,int param_10,int param_11,
                      undefined8 param_12,int param_13,int param_14,int param_15,int param_16,
                      int param_17,int param_18)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int *extraout_EDX;
  int local_c;
  
  iVar2 = FUN_0080e11f(0);
  if ((iVar2 != 0) && (*(code **)(iVar2 + 0x24) == Exec_Misc_Event)) {
    iVar3 = FUN_00817b57(param_1,0x1c);
    if (*(char *)(iVar3 + 0x10) != '\0') {
      *(undefined4 *)(iVar3 + 0x14) = 1;
      *(undefined4 *)(iVar3 + 0x18) = *(undefined4 *)(param_2 + 0x14d4);
    }
    bVar1 = param_4 < param_3;
    if ((param_7 & 1) != 0) {
      bVar1 = param_3 <= param_4;
    }
    if (!bVar1) {
      *(undefined4 *)(iVar3 + 0x18) = *(undefined4 *)(param_2 + 0x14d4);
    }
    if ((((param_7 & 2) != 0) && (*(int *)(iVar3 + 0x14) != 0)) &&
       (*(int *)(iVar3 + 0x18) <= *(int *)(param_2 + 0x14d4))) {
      *(undefined4 *)(iVar3 + 0x14) = 0;
    }
    if (bVar1) {
      if (*(int *)(iVar3 + 0x14) == 0) {
        operator_new(0xb4);
        FUN_00817d8d();
        param_6 = param_6 * _DAT_0081fb84;
        *extraout_EDX = iVar2;
        iVar2 = *(int *)(iVar3 + 0x18);
        extraout_EDX[2] = iVar2;
        extraout_EDX[8] = 1;
        local_c = (int)(longlong)ROUND(param_6 + (float)iVar2);
        extraout_EDX[3] = local_c;
        extraout_EDX[10] = param_8;
        extraout_EDX[0xb] = param_9;
        extraout_EDX[0xc] = param_10;
        extraout_EDX[0x10] = 0;
        extraout_EDX[0xd] = param_11;
        extraout_EDX[0xe] = (int)param_12;
        extraout_EDX[0xf] = param_12._4_4_;
        extraout_EDX[0x14] = 0;
        extraout_EDX[0x11] = param_13;
        extraout_EDX[0x12] = param_14;
        extraout_EDX[0x13] = param_15;
        extraout_EDX[0x18] = 0;
        extraout_EDX[0x15] = param_16;
        extraout_EDX[0x16] = param_17;
        extraout_EDX[0x17] = param_18;
        if ((param_7 & 4) != 0) {
          extraout_EDX[0x15] = *(int *)(param_2 + 0x9520);
          extraout_EDX[0x16] = *(int *)(param_2 + 0x9524);
          extraout_EDX[0x17] = *(int *)(param_2 + 0x9528);
          extraout_EDX[0x18] = *(int *)(param_2 + 0x952c);
          extraout_EDX[0x18] = 0;
        }
        FUN_00818047(extraout_EDX);
        param_5 = param_5 * _DAT_0081fb84;
        *(undefined4 *)(iVar3 + 0x14) = 1;
        param_12._0_4_ = (int)(longlong)ROUND(param_5 + (float)*(int *)(iVar3 + 0x18));
        *(int *)(iVar3 + 0x18) = (int)param_12;
      }
    }
    else {
      *(undefined4 *)(iVar3 + 0x14) = 0;
    }
  }
  FUN_00818ea3(param_2,0);
  return;
}


/* ---- Exec_Misc_If @ 00819c14 ---- */

void Exec_Misc_If(int param_1,int param_2,int param_3,uint param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(byte *)(*(int *)(param_2 + 0x1358) + 0x14fe8 + param_3) == param_4) {
    uVar2 = 0;
  }
  else {
    if (*(int *)(param_1 + 0x6c) < 2) {
      return;
    }
    uVar2 = 1;
  }
  iVar1 = FUN_0080e106(uVar2);
  FUN_0081961c(param_2,iVar1 + 0x4c);
  return;
}


/* ---- FUN_00819c56 @ 00819c56 ---- */

void __fastcall FUN_00819c56(undefined4 *param_1)

{
  param_1[4] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[1] = 0;
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[5] = 100;
  param_1[9] = 100;
  param_1[10] = 0x32;
  param_1[0xd] = 1;
  param_1[0xe] = 1;
  param_1[0xf] = 1;
  param_1[0x15] = 100;
  param_1[0x16] = 100;
  param_1[0x17] = 100;
  param_1[0x18] = 8;
  param_1[0x19] = 500;
  param_1[0x1a] = 200;
  param_1[0x1b] = 100;
  param_1[0x1c] = 1000;
  param_1[0x1d] = 1;
  param_1[0x1e] = 1;
  param_1[0x1f] = 1;
  param_1[0x20] = 1;
  param_1[0x21] = 1;
  param_1[0x22] = 1;
  param_1[0x23] = 1;
  param_1[0x24] = 1;
  *param_1 = 1;
  return;
}


/* ---- FUN_00819cf4 @ 00819cf4 ---- */

void __thiscall FUN_00819cf4(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x18);
  if (iVar1 < param_2) {
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + ((iVar1 - iVar1 / 4) - param_2);
  }
  else {
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + param_2 / -4;
  }
  if (*(int *)(param_1 + 0x14) < 0) {
    *(undefined4 *)(param_1 + 0x14) = 0;
  }
  if (4 < param_2) {
    FUN_00804a47(10,0x3f800000,0,0xac44);
  }
  return;
}


/* ---- FUN_00819d55 @ 00819d55 ---- */

void __thiscall FUN_00819d55(int *param_1,undefined4 param_2)

{
  while( true ) {
    FUN_00805f44(param_2);
    if (*param_1 != 0) break;
    param_1 = param_1 + 0x20;
  }
  return;
}


/* ---- FUN_00819d78 @ 00819d78 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00819d78(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 local_14;
  
  *(undefined4 *)(param_1 + 0x1534c) = 0;
  *(undefined4 *)(param_1 + 0x15358) = 0;
  *(undefined1 *)(param_1 + 0x15364) = 0;
  *(undefined4 *)(param_1 + 0x15350) = 0;
  *(undefined1 *)(param_1 + 0x15365) = 1;
  *(undefined4 *)(param_1 + 0x15368) = 0;
  *(undefined4 *)(param_1 + 0x15538) = 0;
  *(undefined4 *)(param_1 + 0x1535c) = 0;
  *(undefined4 *)(param_1 + 0x15390) = 0x3951b717;
  *(undefined4 *)(param_1 + 0x153a4) = 0x3f0ccccd;
  *(undefined4 *)(param_1 + 0x153a8) = 0x3fcccccd;
  *(undefined4 *)(param_1 + 0x15354) = 0;
  *(undefined4 *)(param_1 + 0x153c0) = 0x3eb33333;
  uVar2 = _DAT_0081fd48;
  *(undefined4 *)(param_1 + 0x15360) = 0;
  *(undefined4 *)(param_1 + 0x15394) = uVar2;
  *(undefined4 *)(param_1 + 0x1551c) = 0;
  uVar1 = _DAT_0081fd44;
  *(undefined4 *)(param_1 + 0x15348) = 0x3f866666;
  *(undefined4 *)(param_1 + 0x15398) = uVar1;
  *(undefined4 *)(param_1 + 0x14964) = 0;
  *(undefined4 *)(param_1 + 0x153d4) = uVar1;
  *(undefined4 *)(param_1 + 0x1539c) = uVar1;
  *(undefined4 *)(param_1 + 0x153a0) = uVar1;
  *(undefined4 *)(param_1 + 0x153ac) = uVar2;
  *(undefined4 *)(param_1 + 0x153b0) = uVar2;
  uVar1 = _DAT_0081fd40;
  *(undefined4 *)(param_1 + 0x153b4) = _DAT_0081fd40;
  *(undefined4 *)(param_1 + 0x153b8) = uVar1;
  *(undefined4 *)(param_1 + 0x153bc) = uVar1;
  FUN_00801bae(0,local_1c);
  *(undefined4 *)(param_1 + 0x15374) = local_18;
  *(undefined4 *)(param_1 + 0x15378) = local_14;
  return;
}


/* ---- FUN_00819e7b @ 00819e7b ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00819e7b(int param_1,int param_2)

{
  if (*(int *)(param_1 + 0x14964) == 0) {
    FUN_00805a9d(*(undefined4 *)(param_1 + 0x14958),*(undefined4 *)(param_1 + 0x1495c),0);
    *(undefined4 *)(param_2 + 0x14c) = *(undefined4 *)(param_1 + 0x15380);
    *(undefined4 *)(param_2 + 0x150) = *(undefined4 *)(param_1 + 0x15384);
    *(undefined4 *)(param_2 + 0x154) = *(undefined4 *)(param_1 + 0x15388);
    *(undefined4 *)(param_2 + 0x158) = *(undefined4 *)(param_1 + 0x1538c);
    *(undefined4 *)(param_2 + 0x158) = 0x3f800000;
  }
  else {
    FUN_00805a9d(0,*(undefined4 *)(param_1 + 0x1495c),0);
    *(undefined4 *)(param_2 + 0x14c) = *(undefined4 *)(param_1 + 0x14948);
    *(undefined4 *)(param_2 + 0x150) = *(undefined4 *)(param_1 + 0x1494c);
    *(undefined4 *)(param_2 + 0x154) = *(undefined4 *)(param_1 + 0x14950);
    *(undefined4 *)(param_2 + 0x158) = *(undefined4 *)(param_1 + 0x14954);
    *(undefined4 *)(param_2 + 0x158) = 0x3f800000;
    FUN_0080604f(param_2 + 0x13c,_DAT_0081f104);
  }
  *(undefined4 *)(param_2 + 0x174) = 0;
  *(undefined4 *)(param_2 + 0x160) = 0x3f800000;
  *(undefined4 *)(param_2 + 0x15c) = 0x3f800000;
  return;
}


/* ---- FUN_00819f28 @ 00819f28 ---- */

void __thiscall FUN_00819f28(int param_1,undefined4 param_2)

{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + 0x14844);
  *(undefined4 *)(param_1 + 0x44 + *piVar1 * 4) = param_2;
  *piVar1 = *piVar1 + 1;
  return;
}


/* ---- FUN_00819f42 @ 00819f42 ---- */

void __thiscall FUN_00819f42(int param_1,undefined4 param_2)

{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + 0x14848);
  *(undefined4 *)(param_1 + 0x10044 + *piVar1 * 4) = param_2;
  *piVar1 = *piVar1 + 1;
  return;
}


/* ---- FUN_00819f5f @ 00819f5f ---- */

void __thiscall FUN_00819f5f(int param_1,undefined4 param_2)

{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + 0x1484c);
  *(undefined4 *)(param_1 + 0x14044 + *piVar1 * 4) = param_2;
  *piVar1 = *piVar1 + 1;
  return;
}


/* ---- FUN_00819f7c @ 00819f7c ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00819f7c(int param_1)

{
  float10 fVar1;
  float10 fVar2;
  undefined1 local_14 [16];
  
  FUN_00805f1f(*(int *)(param_1 + 0xc) + 0x40,*(int *)(param_1 + 8) + 0x40);
  fVar1 = (float10)FUN_00805fc1(local_14);
  fVar2 = (float10)*(float *)(param_1 + 0x10) * (float10)*(float *)(param_1 + 0x10);
  FUN_0080600c((float)(fVar2 / (fVar2 + fVar1) - (float10)_DAT_0081f2ac));
  FUN_00805f44(local_14);
  FUN_00805f66(local_14);
  return;
}


/* ---- FUN_00819fea @ 00819fea ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __thiscall FUN_00819fea(int param_1,float *param_2,float param_3)

{
  int iVar1;
  float *pfVar2;
  uint local_8;
  
  iVar1 = 0;
  local_8 = 0;
  if (0 < *(int *)(param_1 + 0xf0)) {
    pfVar2 = (float *)(param_1 + 0x24);
    do {
      if (*pfVar2 * param_2[1] + pfVar2[-1] * *param_2 + pfVar2[1] * param_2[2] + pfVar2[2] +
          param_3 < _DAT_0081f374) {
        local_8 = local_8 | 1 << ((byte)iVar1 & 0x1f);
      }
      iVar1 = iVar1 + 1;
      pfVar2 = pfVar2 + 4;
    } while (iVar1 < *(int *)(param_1 + 0xf0));
  }
  return local_8;
}


/* ---- FUN_0081a047 @ 0081a047 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall
FUN_0081a047(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4,float *param_5)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  float10 fVar5;
  int local_10;
  float local_8;
  
  local_10 = -1;
  local_8 = 0.0;
  iVar1 = 0;
  if (0 < *(int *)(param_1 + 0xf0)) {
    iVar2 = param_1 + 0x20;
    do {
      fVar4 = (float10)FUN_00805fc1(param_2);
      fVar4 = fVar4 + (float10)*(float *)(iVar2 + 0xc);
      if (fVar4 < (float10)_DAT_0081f374) {
        fVar5 = (float10)FUN_00805fc1(param_3);
        fVar4 = ((float10)_DAT_0081f378 / fVar5) * (float10)(float)fVar4;
        if (fVar4 < (float10)local_8) {
          local_8 = (float)fVar4;
          local_10 = iVar1;
        }
      }
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + 0x10;
    } while (iVar1 < *(int *)(param_1 + 0xf0));
    if (-1 < local_10) {
      puVar3 = (undefined4 *)((local_10 + 2) * 0x10 + param_1);
      *param_4 = *puVar3;
      param_4[1] = puVar3[1];
      param_4[2] = puVar3[2];
      param_4[3] = puVar3[3];
      *param_5 = local_8;
      return 1;
    }
  }
  return 0;
}


/* ---- FUN_0081a0e3 @ 0081a0e3 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall
FUN_0081a0e3(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4,float *param_5)

{
  float fVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  float10 fVar6;
  int local_c;
  float local_8;
  
  local_c = -1;
  iVar2 = 0;
  local_8 = -1048576.0;
  if (0 < *(int *)(param_1 + 0xf0)) {
    iVar3 = param_1 + 0x20;
    do {
      fVar5 = (float10)FUN_00805fc1(param_2);
      fVar1 = *(float *)(iVar3 + 0xc);
      fVar6 = (float10)FUN_00805fc1(param_3);
      if (((float10)_DAT_0081fd50 < fVar6) &&
         (fVar5 = -((float10)(float)(fVar5 + (float10)fVar1) / fVar6), (float10)local_8 < fVar5)) {
        local_8 = (float)fVar5;
        local_c = iVar2;
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x10;
    } while (iVar2 < *(int *)(param_1 + 0xf0));
    if (-1 < local_c) {
      puVar4 = (undefined4 *)((local_c + 2) * 0x10 + param_1);
      *param_4 = *puVar4;
      param_4[1] = puVar4[1];
      param_4[2] = puVar4[2];
      param_4[3] = puVar4[3];
      *param_5 = local_8;
      return 1;
    }
  }
  return 0;
}


/* ---- FUN_0081a181 @ 0081a181 ---- */

undefined2 FUN_0081a181(float *param_1,float *param_2,int param_3)

{
  undefined2 uVar1;
  uint uVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  uint local_8;
  
  iVar5 = param_3;
  pfVar4 = param_1;
  if (param_1[4] < *param_2) {
    return 0;
  }
  if (param_2[4] < *param_1) {
    return 0;
  }
  if (param_1[5] < param_2[1]) {
    return 0;
  }
  if (param_2[5] < param_1[1]) {
    return 0;
  }
  if (param_1[6] < param_2[2]) {
    return 0;
  }
  if (param_2[6] < param_1[2]) {
    return 0;
  }
  local_8 = 0;
  uVar3 = 0xffff;
  param_1 = (float *)0xffff;
  param_3 = 8;
  do {
    uVar2 = FUN_00819fea(iVar5,0);
    param_1 = (float *)((uint)param_1 & uVar2);
    local_8 = local_8 | uVar2;
    iVar5 = iVar5 + 0x10;
    param_3 = param_3 + -1;
  } while (param_3 != 0);
  if (param_1 == (float *)0x0) {
    if (local_8 == 0) {
      pfVar4 = pfVar4 + 0x56;
      param_1 = (float *)0x8;
      do {
        uVar2 = FUN_00819fea(pfVar4,0);
        uVar3 = uVar3 & uVar2;
        pfVar4 = pfVar4 + 4;
        param_1 = (float *)((int)param_1 + -1);
      } while (param_1 != (float *)0x0);
      if (uVar3 != 0) goto LAB_0081a24b;
    }
    uVar1 = 1;
  }
  else {
LAB_0081a24b:
    uVar1 = 0;
  }
  return uVar1;
}


/* ---- FUN_0081a258 @ 0081a258 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 __thiscall
FUN_0081a258(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4,int param_5,
            undefined4 *param_6,float *param_7)

{
  undefined4 *puVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 local_5;
  
  local_5 = 0;
  if ((*(int *)(param_5 + 0x100) == 1) ||
     ((*(int *)(param_5 + 0x100) == 9 && (*(int *)(param_1 + 0x15538) != 0)))) {
    uVar3 = FUN_00819fea(param_4,0);
    uVar4 = FUN_00819fea(param_3,0);
    puVar1 = param_3;
    if (uVar3 == 0) {
      *param_6 = 0x3f800000;
      DAT_014a0980 = 1;
      param_6[1] = 0;
      param_6[2] = 0;
      param_6[3] = 0;
      *param_7 = 0.0;
      return 1;
    }
    if (((uVar3 & uVar4) == 0) &&
       (cVar2 = FUN_0081a0e3(param_3,param_2,&local_28,&param_3), cVar2 != '\0')) {
      if ((float)param_3 < *param_7) {
        local_18 = *puVar1;
        uStack_14 = puVar1[1];
        uStack_10 = puVar1[2];
        uStack_c = puVar1[3];
        FUN_0080604f(param_2,param_3);
        iVar5 = FUN_00819fea(&local_18,_DAT_0081f380);
        if (iVar5 == 0) {
          *param_7 = (float)param_3;
          *param_6 = local_28;
          param_6[1] = uStack_24;
          param_6[2] = uStack_20;
          param_6[3] = uStack_1c;
          FUN_00805e4f();
          local_5 = 1;
        }
      }
    }
  }
  return local_5;
}


/* ---- Exec_KKrieger_Para @ 0081a35e ---- */

void Exec_KKrieger_Para(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  byte bVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  puVar5 = *(undefined4 **)(param_1 + 0x94);
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x149bc) = puVar5[1];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x149c0) = puVar5[3];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x149c4) = puVar5[5];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x149c8) = puVar5[7];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x149cc) = puVar5[9];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x149d0) = puVar5[0xb];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x149d4) = puVar5[0xd];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x149d8) = puVar5[0xf];
  bVar3 = 0;
  if (*(char *)(*(int *)(param_2 + 0x1358) + 0x15365) != '\0') {
    *(undefined1 *)(*(int *)(param_2 + 0x1358) + 0x15365) = 0;
    *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x1497c) = *puVar5;
    *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x14980) = puVar5[2];
    *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x14984) = puVar5[4];
    *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x14988) = puVar5[6];
    *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x1498c) = puVar5[8];
    *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x14990) = puVar5[10];
    *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x14994) = puVar5[0xc];
    *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x14998) = puVar5[0xe];
    iVar4 = 0x1499c;
    do {
      *(uint *)(iVar4 + *(int *)(param_2 + 0x1358)) = (uint)puVar5[0x10] >> (bVar3 & 0x1f) & 1;
      iVar4 = iVar4 + 4;
      bVar3 = bVar3 + 1;
    } while (iVar4 < 0x149bc);
  }
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x15394) = puVar5[0x11];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x1539c) = puVar5[0x12];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x15398) = puVar5[0x13];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x153a0) = puVar5[0x14];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x153a4) = puVar5[0x15];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x153a8) = puVar5[0x16];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x153ac) = puVar5[0x17];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x153b0) = puVar5[0x18];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x153b4) = puVar5[0x19];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x153b8) = puVar5[0x1a];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x153bc) = puVar5[0x1b];
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x153c0) = puVar5[0x1c];
  uVar1 = puVar5[0x1f];
  iVar4 = *(int *)(param_2 + 0x1358);
  uVar2 = puVar5[0x1d];
  *(undefined4 *)(iVar4 + 0x153c8) = puVar5[0x1e];
  *(undefined4 *)(iVar4 + 0x153cc) = uVar1;
  *(undefined4 *)(iVar4 + 0x153c4) = uVar2;
  *(undefined4 *)(iVar4 + 0x153d0) = 0;
  *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x153d4) = puVar5[0x38];
  puVar5 = puVar5 + 0x20;
  puVar6 = (undefined4 *)(*(int *)(param_2 + 0x1358) + 0x150e8);
  for (iVar4 = 0x18; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  iVar4 = *(int *)(param_2 + 0x1358);
  *(float *)(iVar4 + 0x15348) = *(float *)(iVar4 + 0x153a8) - *(float *)(iVar4 + 0x153a4);
  FUN_00818e4a(param_2);
  return;
}


/* ---- Exec_KKrieger_Events @ 0081a5c5 ---- */

void Exec_KKrieger_Events(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = **(int **)(param_1 + 0x94);
  iVar2 = 0;
  if (iVar3 != 0) {
    if (iVar3 == 1) {
      iVar3 = *(int *)(param_2 + 0x1358) + 0x154b0;
      goto LAB_0081a627;
    }
    if (iVar3 == 2) {
      iVar3 = *(int *)(param_2 + 0x1358) + 0x154d0;
      goto LAB_0081a627;
    }
    if (iVar3 == 3) {
      iVar3 = *(int *)(param_2 + 0x1358) + 0x154f0;
      goto LAB_0081a627;
    }
  }
  iVar3 = *(int *)(param_2 + 0x1358) + 0x15490;
LAB_0081a627:
  do {
    uVar1 = FUN_0080e11f(iVar2);
    *(undefined4 *)(iVar3 + iVar2 * 4) = uVar1;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 8);
  FUN_00818e4a(param_2);
  return;
}


/* ---- Init_KKrieger_Para__Init_KKrieger_Events @ 0081a649 ---- */

undefined4 Init_KKrieger_Para__Init_KKrieger_Events(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0080e106(0);
  if (iVar1 == 0) {
    iVar1 = operator_new(0x14c);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = FUN_0081583d();
    }
  }
  else {
    iVar1 = FUN_0080e106(0);
    uVar2 = *(undefined4 *)(iVar1 + 0x18);
  }
  return uVar2;
}


/* ---- Init_KKrieger_Monster @ 0081a687 ---- */

undefined4 Init_KKrieger_Monster(void)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = FUN_0080e106(0);
  puVar2 = *(undefined4 **)(iVar3 + 0x18);
  piVar1 = puVar2 + 2;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    (**(code **)*puVar2)(1);
  }
  iVar3 = operator_new(0x14c);
  if (iVar3 == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = FUN_0081583d();
  }
  return uVar4;
}


/* ---- Init_KKrieger_Respawn @ 0081a6c2 ---- */

undefined4 Init_KKrieger_Respawn(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = operator_new(0x14c);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0081583d();
  }
  return uVar2;
}


/* ---- Exec_KKrieger_Respawn @ 0081a6df ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Exec_KKrieger_Respawn
               (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,int param_6,float param_7)

{
  undefined4 *puVar1;
  
  *(undefined4 *)(param_6 * 0x1c + 0x15148 + *(int *)(param_2 + 0x1358)) = 1;
  puVar1 = (undefined4 *)((param_6 + 0xc0c) * 0x1c + *(int *)(param_2 + 0x1358));
  *puVar1 = param_3;
  puVar1[3] = 0;
  puVar1[1] = param_4;
  param_7 = param_7 * _DAT_0081f37c;
  puVar1[2] = param_5;
  *(float *)(param_6 * 0x1c + 0x15160 + *(int *)(param_2 + 0x1358)) = param_7;
  return;
}


/* ---- Init_KKrieger_SplashDamage @ 0081a73e ---- */

undefined4 Init_KKrieger_SplashDamage(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = operator_new(0x14c);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0081583d();
  }
  return uVar2;
}


/* ---- FUN_0081a75b @ 0081a75b ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool FUN_0081a75b(float *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  float10 extraout_ST0;
  undefined1 local_34 [16];
  undefined1 local_24 [16];
  float local_14;
  float local_10;
  float local_c;
  
  FUN_00805f1f(param_2,param_3);
  FUN_00805f1f(param_3,param_4);
  FUN_0080598d(local_34,local_24);
  fVar2 = (float10)FUN_00805fc1(&local_14);
  fVar1 = (float10)_DAT_0081fd58;
  if (fVar1 <= fVar2) {
    fVar3 = (float10)FUN_00805fc1(&local_14);
    fVar3 = (float10)1 / SQRT(fVar3);
    local_14 = (float)((float10)local_14 * fVar3);
    local_10 = (float)((float10)local_10 * fVar3);
    local_c = (float)((float10)local_c * fVar3);
    FUN_00805fc1(param_3);
    *param_1 = local_14;
    param_1[1] = local_10;
    param_1[2] = local_c;
    param_1[3] = (float)extraout_ST0;
  }
  return fVar1 <= fVar2;
}


/* ---- FUN_0081a7f8 @ 0081a7f8 ---- */

void __thiscall FUN_0081a7f8(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = 0;
  if (0 < *(int *)(param_1 + 0xf0)) {
    puVar1 = (undefined4 *)(param_1 + 0x13c);
    do {
      *puVar1 = puVar1[-0x47];
      puVar1[1] = puVar1[-0x46];
      puVar1[2] = puVar1[-0x45];
      iVar2 = iVar2 + 1;
      puVar1[3] = puVar1[-0x44];
      puVar1 = puVar1 + 4;
    } while (iVar2 < *(int *)(param_1 + 0xf0));
  }
  *(uint *)(param_1 + 0x100) = *(uint *)(param_1 + 0x100) | 0x20;
  *(undefined4 *)(param_1 + 0x138) = 0;
  puVar1 = param_2;
  puVar3 = (undefined4 *)(param_1 + 0x1a4);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = param_2;
  puVar3 = (undefined4 *)(param_1 + 0x1e4);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = param_2;
  puVar3 = (undefined4 *)(param_1 + 0x224);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = (undefined4 *)(param_1 + 0x264);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = *param_2;
    param_2 = param_2 + 1;
    puVar1 = puVar1 + 1;
  }
  *(undefined4 *)(param_1 + 0x19c) = 0;
  *(undefined4 *)(param_1 + 0x1a0) = 0;
  return;
}


/* ---- FUN_0081a880 @ 0081a880 ---- */

void __thiscall FUN_0081a880(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  float local_10;
  int local_c;
  undefined4 *local_8;
  
  local_c = 0;
  if (0 < *(int *)(param_1 + 0xf0)) {
    local_8 = (undefined4 *)(param_1 + 0x20);
    do {
      local_1c = local_8[0x47];
      uStack_18 = local_8[0x48];
      uStack_14 = local_8[0x49];
      local_10 = (float)local_8[0x4a];
      FUN_0080602c(&local_1c,-local_10);
      FUN_008061df(param_2);
      FUN_00806349(param_2);
      FUN_0080620b();
      fVar3 = (float10)FUN_00805fc1(&local_1c);
      local_c = local_c + 1;
      *local_8 = local_1c;
      local_8[1] = uStack_18;
      local_8[2] = uStack_14;
      local_8[3] = (float)-fVar3;
      local_8 = local_8 + 4;
    } while (local_c < *(int *)(param_1 + 0xf0));
  }
  *(undefined4 *)(param_1 + 0xe0) = param_2[0xc];
  *(undefined4 *)(param_1 + 0xe4) = param_2[0xd];
  *(undefined4 *)(param_1 + 0xe8) = param_2[0xe];
  *(undefined4 *)(param_1 + 0xec) = param_2[0xf];
  puVar2 = (undefined4 *)(param_1 + 0x1e4);
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)(param_1 + 0x138) = 0;
  return;
}


/* ---- FUN_0081a939 @ 0081a939 ---- */

void __thiscall
FUN_0081a939(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[3] = 0;
  param_1[7] = param_4;
  param_1[0x10] = *param_2;
  param_1[0x11] = param_2[1];
  param_1[0x12] = param_2[2];
  param_1[0x13] = param_2[3];
  param_1[0x1c] = *param_2;
  param_1[0x1d] = param_2[1];
  param_1[0x1e] = param_2[2];
  param_1[0x1f] = param_2[3];
  param_1[4] = 0;
  param_1[5] = 1;
  param_1[0x14] = *param_2;
  param_1[0x15] = param_2[1];
  param_1[0x16] = param_2[2];
  param_1[0x17] = param_2[3];
  FUN_00805f1f(param_2,param_3);
  return;
}


/* ---- FUN_0081a98d @ 0081a98d ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
FUN_0081a98d(int param_1,int param_2,int *param_3,float *param_4,undefined4 param_5,int param_6)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  float10 fVar4;
  
  iVar1 = *(int *)(param_1 + 0x24);
  if (iVar1 != 0) {
    iVar2 = *(int *)(param_1 + 0xc);
    if (((((7 < iVar2) && (iVar2 < 0x10)) && (0 < *(int *)(iVar1 + 8))) &&
        ((*(int *)(iVar1 + 0x30) == 0 &&
         (iVar2 = *(int *)(param_2 + 0x154b0 + (iVar2 + param_6 * 8) * 4), iVar2 != 0)))) &&
       ((param_6 != 0 || (*(int *)(iVar1 + 0x14) + 10 < *(int *)(param_2 + 0x15540))))) {
      *(undefined4 *)(iVar1 + 0x28) = 0x40a00000;
      piVar3 = (int *)operator_new(0xb4);
      FUN_00817d8d();
      *piVar3 = iVar2;
      piVar3[0x15] = *param_3;
      piVar3[0x16] = param_3[1];
      piVar3[0x17] = param_3[2];
      piVar3[0x18] = param_3[3];
      fVar4 = (float10)fpatan(-(float10)param_4[1],
                              SQRT((float10)param_4[2] * (float10)param_4[2] +
                                   (float10)*param_4 * (float10)*param_4));
      piVar3[0x11] = (int)(float)(fVar4 * (float10)_DAT_0081fcc0);
      fVar4 = (float10)fpatan((float10)*param_4,(float10)param_4[2]);
      piVar3[0x12] = (int)(float)(fVar4 * (float10)_DAT_0081fcc0);
      piVar3[0x13] = 0;
      FUN_00818047(piVar3);
    }
    if (((*(byte *)(param_2 + 0x15108 + *(int *)(param_1 + 0xc) * 4) & 2) == 0) || (param_6 != 0)) {
      *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x30) = 1;
      FUN_00817dae();
    }
    *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x14) = *(undefined4 *)(param_2 + 0x15540);
  }
  return;
}


/* ---- FUN_0081aaa4 @ 0081aaa4 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
FUN_0081aaa4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  int iVar1;
  byte *pbVar2;
  char *pcVar3;
  undefined4 *puVar4;
  float10 fVar5;
  float local_18;
  float local_14;
  float local_10;
  undefined4 local_c;
  int local_8;
  
  pcVar3 = &DAT_0081fd81;
  do {
    local_18 = (float)(int)pcVar3[-1];
    local_8 = (int)pcVar3[1];
    local_14 = (float)(int)*pcVar3;
    local_10 = (float)local_8;
    local_c = 0;
    FUN_0080600c(_DAT_0081f2ac);
    FUN_00805f88(param_3);
    FUN_00806349(param_2);
    FUN_0081a939(&local_18,param_4,param_5);
    pcVar3 = pcVar3 + 3;
  } while ((int)pcVar3 < 0x81fd99);
  *(undefined4 *)(param_1 + 0x380) = 1;
  pbVar2 = &DAT_0081fd61;
  puVar4 = (undefined4 *)(param_1 + 0x404);
  do {
    puVar4[-1] = 0;
    *puVar4 = 0;
    puVar4[1] = (uint)pbVar2[-1] * 0x80 + param_1;
    iVar1 = (uint)*pbVar2 * 0x80 + param_1;
    puVar4[2] = iVar1;
    FUN_00805f1f(puVar4[1] + 0x40,iVar1 + 0x40);
    fVar5 = (float10)FUN_00806202();
    puVar4[3] = (float)fVar5;
    pbVar2 = pbVar2 + 2;
    puVar4 = puVar4 + 5;
  } while ((int)pbVar2 < 0x81fd81);
  *(undefined4 *)(param_1 + 0x52c) = 1;
  return;
}


/* ---- FUN_0081ab9a @ 0081ab9a ---- */

void FUN_0081ab9a(void)

{
  return;
}


/* ---- FUN_0081ab9d @ 0081ab9d ---- */

void __fastcall FUN_0081ab9d(int param_1)

{
  FUN_00819f28(param_1);
  FUN_00819f42(param_1 + 0x400);
  return;
}


/* ---- FUN_0081abbd @ 0081abbd ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0081abbd(int param_1,int *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  undefined4 local_dc [4];
  undefined1 local_cc [16];
  undefined1 local_bc [16];
  undefined1 local_ac [16];
  undefined1 local_9c [16];
  undefined1 local_8c [16];
  undefined1 local_7c [16];
  undefined1 local_6c [16];
  int local_5c [17];
  undefined4 *local_18;
  undefined1 local_14 [16];
  
  local_5c[0] = 0;
  local_18 = (undefined4 *)(param_1 + 0x40);
  local_5c[1] = 0;
  puVar4 = local_dc;
  local_5c[2] = 0;
  local_5c[0x10] = 8;
  local_5c[3] = 0;
  local_5c[4] = 0;
  local_5c[5] = 0;
  local_5c[6] = 0;
  local_5c[7] = 0;
  local_5c[8] = 0;
  local_5c[9] = 0;
  local_5c[10] = 0;
  local_5c[0xb] = 0;
  local_5c[0xc] = 0;
  local_5c[0xd] = 0;
  local_5c[0xe] = 0;
  local_5c[0xf] = 0x3f800000;
  do {
    puVar2 = local_18;
    puVar1 = local_18 + 1;
    *puVar4 = *local_18;
    puVar4[1] = *puVar1;
    puVar4[2] = puVar2[2];
    puVar4[3] = puVar2[3];
    FUN_00805f44(puVar4);
    local_18 = local_18 + 0x20;
    puVar4 = puVar4 + 4;
    local_5c[0x10] = local_5c[0x10] + -1;
  } while (local_5c[0x10] != 0);
  FUN_00805f1f(local_ac,local_dc);
  FUN_00805f44(local_14);
  FUN_00805f1f(local_bc,local_cc);
  FUN_00805f44(local_14);
  FUN_00805f1f(local_6c,local_9c);
  FUN_00805f44(local_14);
  FUN_00805f1f(local_7c,local_8c);
  FUN_00805f44(local_14);
  FUN_00805f1f(local_cc,local_dc);
  FUN_00805f44(local_14);
  FUN_00805f1f(local_bc,local_ac);
  FUN_00805f44(local_14);
  FUN_00805f1f(local_8c,local_9c);
  FUN_00805f44(local_14);
  FUN_00805f1f(local_7c,local_6c);
  FUN_00805f44(local_14);
  FUN_00805f1f(local_9c,local_dc);
  FUN_00805f44(local_14);
  FUN_00805f1f(local_8c,local_cc);
  FUN_00805f44(local_14);
  FUN_00805f1f(local_7c,local_bc);
  FUN_00805f44(local_14);
  FUN_00805f1f(local_6c,local_ac);
  FUN_00805f44(local_14);
  FUN_0080620b();
  FUN_0080620b();
  FUN_0080620b();
  FUN_0080600c(_DAT_0081fd3c);
  piVar5 = local_5c;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *param_2 = *piVar5;
    piVar5 = piVar5 + 1;
    param_2 = param_2 + 1;
  }
  return;
}


/* ---- FUN_0081ae0f @ 0081ae0f ---- */

void __fastcall FUN_0081ae0f(int param_1)

{
  FUN_00819f28(param_1);
  FUN_00819f42(param_1 + 0x280);
  FUN_00819f5f(param_1 + 0x348);
  return;
}


/* ---- FUN_0081ae3b @ 0081ae3b ---- */

void __fastcall FUN_0081ae3b(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int local_8;
  
  local_8 = 0;
  if (0 < *(int *)(param_1 + 8)) {
    do {
      iVar2 = local_8 * 4;
      piVar3 = (int *)(*(int *)(iVar2 + *(int *)(param_1 + 4)) + 0x128);
      iVar4 = *piVar3;
      if (iVar4 != 0) {
        operator_delete(iVar4);
        *piVar3 = 0;
      }
      piVar3 = (int *)(*(int *)(iVar2 + *(int *)(param_1 + 4)) + 0x138);
      iVar4 = *piVar3;
      if (iVar4 != 0) {
        operator_delete(iVar4);
        *piVar3 = 0;
      }
      piVar3 = (int *)(*(int *)(iVar2 + *(int *)(param_1 + 4)) + 0x148);
      iVar4 = *piVar3;
      if (iVar4 != 0) {
        operator_delete(iVar4);
        *piVar3 = 0;
      }
      operator_delete(*(undefined4 *)(iVar2 + *(int *)(param_1 + 4)));
      local_8 = local_8 + 1;
    } while (local_8 < *(int *)(param_1 + 8));
  }
  iVar4 = 0;
  if (0 < *(int *)(param_1 + 0x18)) {
    do {
      operator_delete(*(undefined4 *)(*(int *)(param_1 + 0x14) + iVar4 * 4));
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(int *)(param_1 + 0x18));
  }
  local_8 = 0;
  if (0 < *(int *)(param_1 + 0x28)) {
    do {
      iVar2 = local_8 * 4;
      iVar4 = 0xf8;
      do {
        if (*(int *)(iVar4 + *(int *)(iVar2 + *(int *)(param_1 + 0x24))) != 0) {
          FUN_00817d99();
          operator_delete(*(undefined4 *)(*(int *)(iVar2 + *(int *)(param_1 + 0x24)) + iVar4));
          *(undefined4 *)(iVar4 + *(int *)(iVar2 + *(int *)(param_1 + 0x24))) = 0;
        }
        iVar4 = iVar4 + 4;
      } while (iVar4 < 0x100);
      operator_delete(*(undefined4 *)(iVar2 + *(int *)(param_1 + 0x24)));
      local_8 = local_8 + 1;
    } while (local_8 < *(int *)(param_1 + 0x28));
  }
  puVar1 = (undefined4 *)(param_1 + 0x154b0);
  iVar4 = 8;
  do {
    puVar1[-8] = 0;
    *puVar1 = 0;
    puVar1[8] = 0;
    puVar1[0x10] = 0;
    puVar1 = puVar1 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  *(undefined4 *)(param_1 + 0x1548c) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x15510) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x14844) = 0;
  *(undefined4 *)(param_1 + 0x14848) = 0;
  *(undefined4 *)(param_1 + 0x15518) = 0;
  *(undefined4 *)(param_1 + 0x15514) = 0;
  *(undefined4 *)(param_1 + 0x14968) = 1;
  *(undefined4 *)(param_1 + 0x1496c) = 0;
  return;
}


/* ---- FUN_0081af9e @ 0081af9e ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0081af9e(int param_1)

{
  float *pfVar1;
  int iVar2;
  undefined4 uVar3;
  float fVar4;
  int iVar5;
  
  iVar5 = 0;
  if (0 < *(int *)(param_1 + 0x28)) {
    do {
      iVar2 = *(int *)(*(int *)(param_1 + 0x24) + iVar5 * 4);
      if ((*(int *)(iVar2 + 0xf8) != 0) && (*(int *)(iVar2 + 0x124) == 0)) {
        FUN_0081805e(*(int *)(iVar2 + 0xf8));
      }
      if ((*(int *)(iVar2 + 0xfc) != 0) && (0 < *(int *)(iVar2 + 0x124))) {
        FUN_0081805e(*(int *)(iVar2 + 0xfc));
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < *(int *)(param_1 + 0x28));
  }
  if ((*(int *)(param_1 + 0x1496c) != *(int *)(param_1 + 0x14968)) &&
     (_DAT_0081f2bc <= *(float *)(param_1 + 0x1548c))) {
    *(int *)(param_1 + 0x14968) = *(int *)(param_1 + 0x1496c);
    FUN_00817d99();
    FUN_00817d8d();
    uVar3 = *(undefined4 *)(param_1 + 0x154b0 + *(int *)(param_1 + 0x14968) * 4);
    *(undefined4 *)(param_1 + 0x1548c) = 0;
    *(undefined4 *)(param_1 + 87000) = uVar3;
  }
  if (*(int *)(param_1 + 87000) != 0) {
    *(undefined4 *)(param_1 + 0x1542c) = *(undefined4 *)(param_1 + 0x14948);
    *(undefined4 *)(param_1 + 0x15430) = *(undefined4 *)(param_1 + 0x1494c);
    *(undefined4 *)(param_1 + 0x15434) = *(undefined4 *)(param_1 + 0x14950);
    *(undefined4 *)(param_1 + 0x15438) = *(undefined4 *)(param_1 + 0x14954);
    *(float *)(param_1 + 0x15430) = *(float *)(param_1 + 0x1537c) + *(float *)(param_1 + 0x15348);
    fVar4 = *(float *)(param_1 + 0x1495c) * _DAT_0081fd98;
    *(float *)(param_1 + 0x1541c) = *(float *)(param_1 + 0x14958) * _DAT_0081fd98;
    *(float *)(param_1 + 0x15420) = fVar4;
    *(undefined4 *)(param_1 + 0x15424) = 0;
    *(undefined4 *)(param_1 + 0x15428) = 0;
    *(undefined4 *)(param_1 + 0x15400) = *(undefined4 *)(param_1 + 0x1548c);
    *(undefined4 *)(param_1 + 0x15404) = 0;
    pfVar1 = (float *)(param_1 + 0x15108 + *(int *)(param_1 + 0x14968) * 4);
    if (_DAT_0081fd48 < *pfVar1) {
      *(float *)(param_1 + 0x15404) = (*pfVar1 - *(float *)(param_1 + 0x14978)) / *pfVar1;
    }
    FUN_0081805e((int *)(param_1 + 87000));
  }
  return;
}


/* ---- FUN_0081b0f1 @ 0081b0f1 ---- */

void __fastcall FUN_0081b0f1(int param_1)

{
  *(undefined4 *)(param_1 + 0x14844) = 0;
  *(undefined4 *)(param_1 + 0x14848) = 0;
  *(undefined4 *)(param_1 + 0x1484c) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  FUN_0081ae0f(param_1);
  return;
}


/* ---- FUN_0081b115 @ 0081b115 ---- */

undefined4 __fastcall FUN_0081b115(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = *(int *)(param_1 + 8);
  iVar4 = 0;
  if (0 < iVar1) {
    iVar2 = *(int *)(param_1 + 4);
    do {
      iVar3 = FUN_00819fea(&stack0x00000004,0);
      if (iVar3 == 0) {
        return *(undefined4 *)(iVar2 + iVar4 * 4);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < iVar1);
  }
  return 0;
}


/* ---- FUN_0081b15a @ 0081b15a ---- */

void FUN_0081b15a(undefined4 param_1,int param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  
  if ((*(int *)(param_5 + 0x24) == 0) || (*(int *)(*(int *)(param_5 + 0x24) + 0x30) == 0)) {
    uVar2 = 1 << ((byte)*(undefined4 *)(param_5 + 0xc) & 0x1f);
    do {
      param_5 = 0;
      if (0 < *(int *)(param_2 + 0x14c)) {
        do {
          iVar1 = *(int *)(*(int *)(param_2 + 0x148) + param_5 * 4);
          iVar3 = FUN_00819fea(param_1,0);
          iVar4 = FUN_00819fea(param_3,0);
          if (iVar3 == 0) {
            if (iVar4 == 0) {
LAB_0081b1e8:
              *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) | uVar2;
            }
            else {
              *(uint *)(iVar1 + 0x11c) = *(uint *)(iVar1 + 0x11c) | uVar2;
            }
          }
          else if (iVar4 == 0) {
            *(uint *)(iVar1 + 0x118) = *(uint *)(iVar1 + 0x118) | uVar2;
            goto LAB_0081b1e8;
          }
          param_5 = param_5 + 1;
        } while (param_5 < *(int *)(param_2 + 0x14c));
      }
      bVar5 = param_2 != param_4;
      param_2 = param_4;
    } while (bVar5);
  }
  return;
}


/* ---- FUN_0081b213 @ 0081b213 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 __thiscall
FUN_0081b213(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4,int param_5,
            int *param_6,undefined4 param_7,undefined4 *param_8,int param_9,int param_10)

{
  int iVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined1 local_30 [16];
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  int local_10;
  int local_c;
  undefined1 local_5;
  
  if ((param_9 == 0) || ((*(int *)(param_9 + 0xc) != 1 && (*(int *)(param_9 + 0xc) != 2)))) {
    local_10 = 1;
  }
  else {
    local_10 = 0;
  }
  *param_8 = _DAT_0081f380;
  iVar5 = 0;
  local_5 = 0;
  local_c = param_1;
  if (0 < (int)param_6) {
    do {
      iVar1 = *(int *)(param_5 + iVar5 * 4);
      iVar4 = 0;
      if (0 < *(int *)(iVar1 + 0x13c)) {
        do {
          iVar2 = *(int *)(*(int *)(iVar1 + 0x138) + iVar4 * 4);
          if ((((*(int *)(iVar2 + 0x100) == 1) ||
               ((*(int *)(iVar2 + 0x100) == 9 && (*(int *)(param_1 + 0x15538) != 0)))) &&
              ((local_10 == 0 || (*(int *)(iVar2 + 0x104) == 0)))) &&
             ((cVar3 = FUN_0081a258(param_2,param_3,param_4,iVar2,param_7,param_8),
              param_1 = local_c, cVar3 != '\0' && (local_5 = 1, DAT_014a0980 != 0)))) {
            return 1;
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < *(int *)(iVar1 + 0x13c));
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < (int)param_6);
  }
  param_5 = 0;
  if (0 < *(int *)(param_1 + 0x1484c)) {
    param_6 = (int *)(param_1 + 0x14044);
    do {
      iVar5 = *param_6;
      if ((((*(int *)(iVar5 + 0x100) == 1) && ((local_10 == 0 || (*(int *)(iVar5 + 0x104) == 0))))
          && (((*(int *)(iVar5 + 0x1a0) == 0 && (iVar5 != param_1 + 0x14d44)) || (param_9 != 0))))
         && (cVar3 = FUN_0081a258(param_2,param_3,param_4,iVar5,param_7,param_8), param_1 = local_c,
            cVar3 != '\0')) {
        local_5 = 1;
        if (DAT_014a0980 != 0) {
          return 1;
        }
        if ((param_10 != 0) &&
           ((*(int *)(param_10 + 0x24) == 0 || (*(int *)(*(int *)(param_10 + 0x24) + 0x30) == 0))))
        {
          *(uint *)(iVar5 + 0x120) =
               *(uint *)(iVar5 + 0x120) | 1 << ((byte)*(undefined4 *)(param_10 + 0xc) & 0x1f);
          local_20 = *param_3;
          uStack_1c = param_3[1];
          uStack_18 = param_3[2];
          uStack_14 = param_3[3];
          FUN_0080604f(param_2,*param_8);
          FUN_0081a98d(local_c,&local_20,param_7,0,*(int *)(iVar5 + 0x1a0) != 0);
        }
        param_1 = local_c;
        if (((param_9 != 0) && (_DAT_0081f374 < *(float *)(param_9 + 0x2c))) &&
           (*(int *)(iVar5 + 0x19c) != 0)) {
          FUN_00805f1f(param_3,param_4);
          local_20 = *param_3;
          uStack_1c = param_3[1];
          uStack_18 = param_3[2];
          uStack_14 = param_3[3];
          FUN_0080604f(param_2,*param_8);
          FUN_0081ab9a(&local_20,local_30,*(undefined4 *)(param_9 + 0x2c));
          param_1 = local_c;
        }
      }
      param_5 = param_5 + 1;
      param_6 = param_6 + 1;
    } while (param_5 < *(int *)(param_1 + 0x1484c));
  }
  return local_5;
}


/* ---- FUN_0081b45a @ 0081b45a ---- */

undefined4 __thiscall
FUN_0081b45a(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4,
            int *param_5,undefined4 *param_6,float *param_7,int param_8,undefined4 param_9)

{
  int *piVar1;
  int iVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  undefined4 uVar6;
  float *pfVar7;
  int iVar8;
  int local_60 [16];
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_60[0] = *param_5;
  local_8 = 1;
  local_10 = param_1;
LAB_0081b52d:
  cVar4 = FUN_0081a047(param_3,param_2,param_6,param_7);
  pfVar7 = param_7;
  if (cVar4 == '\0') {
    uVar6 = FUN_0081b213(param_2,param_3,param_4,local_60,local_8,param_6,param_7,param_8,param_9);
  }
  else {
    if ((param_8 == 0) || ((*(int *)(param_8 + 0xc) != 1 && (*(int *)(param_8 + 0xc) != 2)))) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    local_20 = *param_3;
    uStack_1c = param_3[1];
    uStack_18 = param_3[2];
    uStack_14 = param_3[3];
    FUN_0080604f(param_2,*param_7);
    if (local_8 < 0x10) {
      iVar2 = *param_5;
      for (iVar8 = 0; pfVar7 = param_7, iVar8 < *(int *)(iVar2 + 300); iVar8 = iVar8 + 1) {
        local_c = *(int *)(*(int *)(iVar2 + 0x128) + iVar8 * 4);
        iVar5 = FUN_00819fea(&local_20,0);
        if ((iVar5 == 0) && ((bVar3 || (*(int *)(local_c + 0x104) == 0)))) {
          iVar5 = 0;
          while( true ) {
            if (local_8 <= iVar5) {
              piVar1 = local_60 + local_8;
              local_8 = local_8 + 1;
              *piVar1 = iVar2;
              *param_5 = *(int *)(*(int *)(iVar2 + 0x128) + iVar8 * 4);
              goto LAB_0081b52d;
            }
            if (local_60[iVar5] == local_c) break;
            iVar5 = iVar5 + 1;
          }
        }
      }
    }
    cVar4 = FUN_0081b213(param_2,param_3,param_4,local_60,local_8,&local_20,&param_7,param_8,param_9
                        );
    if (cVar4 != '\0') {
      if ((float)param_7 < *pfVar7) {
        *pfVar7 = (float)param_7;
        *param_6 = local_20;
        param_6[1] = uStack_1c;
        param_6[2] = uStack_18;
        param_6[3] = uStack_14;
      }
    }
    uVar6 = 1;
  }
  return uVar6;
}


/* ---- FUN_0081b5bd @ 0081b5bd ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 FUN_0081b5bd(int param_1,char param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  uint *puVar3;
  int iVar4;
  char cVar5;
  float10 fVar6;
  undefined1 local_e8 [16];
  undefined1 local_d8 [16];
  undefined1 local_c8 [16];
  undefined1 local_b8 [16];
  float local_a8;
  float fStack_a4;
  float fStack_a0;
  float local_9c;
  float local_98;
  float fStack_94;
  float fStack_90;
  float local_8c;
  undefined1 local_88 [16];
  undefined4 local_78;
  float local_74;
  float local_70;
  float local_6c;
  undefined4 local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  float local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined4 local_c;
  float local_8;
  
  iVar4 = param_1;
  local_10 = *(undefined4 *)(param_1 + 0x1c);
  local_34 = *(undefined4 *)(param_1 + 0x50);
  uStack_30 = *(undefined4 *)(param_1 + 0x54);
  uStack_2c = *(undefined4 *)(param_1 + 0x58);
  uStack_28 = *(undefined4 *)(param_1 + 0x5c);
  local_20 = *(undefined4 *)(param_1 + 0x40);
  uStack_1c = *(undefined4 *)(param_1 + 0x44);
  uStack_18 = *(undefined4 *)(param_1 + 0x48);
  piVar1 = (int *)(param_1 + 0x20);
  uStack_14 = *(undefined4 *)(param_1 + 0x4c);
  param_1._3_1_ = 0;
  if (*piVar1 != 0) {
    puVar3 = (uint *)(*piVar1 + 0x100);
    *puVar3 = *puVar3 | 0x10;
  }
  FUN_00805f1f(&local_20,&local_34);
  fVar6 = (float10)FUN_00805fc1(local_88);
  if ((float10)_DAT_0081fd50 <= fVar6) {
    local_24 = (float)((float10)_DAT_0081f2bc / SQRT(fVar6));
    FUN_0080600c((float)((float10)_DAT_0081f2bc / SQRT(fVar6)));
    DAT_014a0980 = 0;
    cVar5 = FUN_0081b45a(local_88,&local_20,&local_34,&local_10,&local_98,&local_8,iVar4,iVar4);
    if (cVar5 == '\0') {
LAB_0081ba4e:
      if (*(int *)(iVar4 + 0xc) != 0) {
        FUN_0081b15a(iVar4 + 0x50,*(undefined4 *)(iVar4 + 0x1c),&local_20,local_10,iVar4);
      }
      *(undefined4 *)(iVar4 + 0x50) = local_20;
      *(undefined4 *)(iVar4 + 0x54) = uStack_1c;
      *(undefined4 *)(iVar4 + 0x58) = uStack_18;
      *(undefined4 *)(iVar4 + 0x5c) = uStack_14;
      *(undefined4 *)(iVar4 + 0x1c) = local_10;
      if (param_2 == '\0') {
        *(undefined4 *)(iVar4 + 0x40) = local_20;
        *(undefined4 *)(iVar4 + 0x44) = uStack_1c;
        *(undefined4 *)(iVar4 + 0x48) = uStack_18;
        *(undefined4 *)(iVar4 + 0x4c) = uStack_14;
      }
      if (*(int *)(iVar4 + 0x20) == 0) {
        return param_1._3_1_;
      }
      puVar3 = (uint *)(*(int *)(iVar4 + 0x20) + 0x100);
      *puVar3 = *puVar3 & 0xffffffef;
      return param_1._3_1_;
    }
    param_1._3_1_ = 1;
    if (DAT_014a0980 == 0) {
      local_34 = local_20;
      uStack_30 = uStack_1c;
      uStack_2c = uStack_18;
      uStack_28 = uStack_14;
      FUN_0080604f(local_88,local_8);
      if (*(int *)(iVar4 + 0x24) != 0) {
        FUN_0081a98d(local_c,&local_34,&local_98,0,0);
      }
      FUN_0080604f(&local_98,_DAT_0081f380);
      fVar6 = (float10)FUN_00805fc1(&local_20);
      FUN_0080604f(&local_98,(float)((float10)_DAT_0081f380 - (fVar6 + (float10)local_8c)));
      FUN_00805f1f(&local_20,&local_34);
      fVar6 = (float10)FUN_00805fc1(&local_44);
      if ((float10)_DAT_0081fd50 < fVar6) {
        FUN_0080602c(&local_44,local_24);
      }
      cVar5 = FUN_0081b45a(local_88,&local_20,&local_34,&local_10,&local_a8,&local_78,iVar4,0);
      if (cVar5 == '\0') goto LAB_0081ba4e;
      if (DAT_014a0980 == 0) {
        fVar6 = (float10)FUN_00805fc1(&local_a8);
        local_8 = (float)fVar6;
        local_34 = local_20;
        uStack_30 = uStack_1c;
        uStack_2c = uStack_18;
        uStack_28 = uStack_14;
        FUN_0080604f(local_88,local_78);
        if (_DAT_0081fd9c <= local_8) {
          if (local_8 <= _DAT_0081f380) {
            local_54 = local_98;
            local_50 = fStack_94;
            local_4c = fStack_90;
            local_48 = local_8c - _DAT_0081f380;
            local_64 = local_a8;
            local_60 = fStack_a4;
            local_5c = fStack_a0;
            local_58 = local_9c - _DAT_0081f380;
            FUN_0080598d(&local_98,&local_a8);
            local_68 = 0;
            local_44 = 0;
            local_40 = 0;
            local_3c = 0;
            local_38 = 0;
            FUN_0080598d(&local_64,&local_74);
            FUN_0080604f(local_c8,-local_48);
            FUN_0080598d(&local_74,&local_54);
            FUN_0080604f(local_d8,-local_58);
            FUN_0080598d(&local_54,&local_64);
            local_8 = _DAT_0081f2bc /
                      ((((local_6c * local_60 * local_54 +
                         local_74 * local_5c * local_50 + local_70 * local_64 * local_4c) -
                        local_70 * local_5c * local_54) - local_64 * local_50 * local_6c) -
                      local_4c * local_74 * local_60);
            fVar6 = (float10)FUN_00805fc1(&local_20);
            local_20 = local_44;
            uStack_1c = local_40;
            uStack_18 = local_3c;
            uStack_14 = local_38;
            FUN_0080604f(local_b8,(float)fVar6);
            FUN_0080600c(local_8);
            fVar6 = (float10)FUN_00805fc1(&local_34);
            local_34 = local_44;
            uStack_30 = local_40;
            uStack_2c = local_3c;
            uStack_28 = local_38;
            FUN_0080604f(local_b8,(float)fVar6);
            FUN_0080600c(local_8);
          }
          else {
            FUN_0080604f(&local_a8,_DAT_0081f380);
            fVar6 = (float10)FUN_00805fc1(&local_20);
            FUN_0080604f(&local_a8,(float)((float10)_DAT_0081f380 - (fVar6 + (float10)local_9c)));
          }
        }
        else {
          puVar2 = (undefined4 *)(iVar4 + 0x50);
          *(undefined4 *)(iVar4 + 0x60) = *puVar2;
          *(undefined4 *)(iVar4 + 100) = *(undefined4 *)(iVar4 + 0x54);
          *(undefined4 *)(iVar4 + 0x68) = *(undefined4 *)(iVar4 + 0x58);
          *(undefined4 *)(iVar4 + 0x6c) = *(undefined4 *)(iVar4 + 0x5c);
          *(undefined4 *)(iVar4 + 0x40) = *puVar2;
          *(undefined4 *)(iVar4 + 0x44) = *(undefined4 *)(iVar4 + 0x54);
          *(undefined4 *)(iVar4 + 0x48) = *(undefined4 *)(iVar4 + 0x58);
          *(undefined4 *)(iVar4 + 0x4c) = *(undefined4 *)(iVar4 + 0x5c);
          local_20 = *puVar2;
          uStack_1c = *(undefined4 *)(iVar4 + 0x54);
          uStack_18 = *(undefined4 *)(iVar4 + 0x58);
          uStack_14 = *(undefined4 *)(iVar4 + 0x5c);
        }
        FUN_00805f1f(&local_20,&local_34);
        fVar6 = (float10)FUN_00805fc1(&local_44);
        if ((float10)_DAT_0081fd50 < fVar6) {
          FUN_0080602c(&local_44,local_24);
        }
        FUN_0080600c(local_24);
        cVar5 = FUN_0081b45a(local_88,&local_20,&local_34,&local_10,local_e8,&local_78,iVar4,0);
        if (cVar5 == '\0') goto LAB_0081ba4e;
      }
    }
  }
  if (*(int *)(iVar4 + 0xc) != 0) {
    FUN_0081b15a(iVar4 + 0x50,*(undefined4 *)(iVar4 + 0x1c),&local_20,local_10,iVar4);
  }
  if (param_2 == '\0') {
    *(undefined4 *)(iVar4 + 0x60) = *(undefined4 *)(iVar4 + 0x50);
    *(undefined4 *)(iVar4 + 100) = *(undefined4 *)(iVar4 + 0x54);
    *(undefined4 *)(iVar4 + 0x68) = *(undefined4 *)(iVar4 + 0x58);
    *(undefined4 *)(iVar4 + 0x6c) = *(undefined4 *)(iVar4 + 0x5c);
    *(undefined4 *)(iVar4 + 0x40) = *(undefined4 *)(iVar4 + 0x50);
    *(undefined4 *)(iVar4 + 0x44) = *(undefined4 *)(iVar4 + 0x54);
    *(undefined4 *)(iVar4 + 0x48) = *(undefined4 *)(iVar4 + 0x58);
    *(undefined4 *)(iVar4 + 0x4c) = *(undefined4 *)(iVar4 + 0x5c);
  }
  if (*(int *)(iVar4 + 0x20) != 0) {
    puVar3 = (uint *)(*(int *)(iVar4 + 0x20) + 0x100);
    *puVar3 = *puVar3 & 0xffffffef;
  }
  return 2;
}


/* ---- Exec_KKrieger_SplashDamage @ 0081baee ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Exec_KKrieger_SplashDamage
               (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,float param_5)

{
  int iVar1;
  char cVar2;
  int iVar3;
  
  iVar3 = FUN_00817b57(param_1,0x18);
  if (param_5 <= _DAT_0081f374) {
    cVar2 = '\0';
  }
  else {
    cVar2 = '\x01';
    if (*(int *)(iVar3 + 0x14) == 0) {
      *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x1551c) = 1;
      iVar1 = *(int *)(param_2 + 0x1358);
      *(undefined4 *)(iVar1 + 0x15520) = *(undefined4 *)(param_2 + 0x9520);
      *(undefined4 *)(iVar1 + 0x15524) = *(undefined4 *)(param_2 + 0x9524);
      *(undefined4 *)(iVar1 + 0x15528) = *(undefined4 *)(param_2 + 0x9528);
      *(undefined4 *)(iVar1 + 0x1552c) = *(undefined4 *)(param_2 + 0x952c);
      *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x15530) = param_4;
      *(undefined4 *)(*(int *)(param_2 + 0x1358) + 0x15534) = param_3;
    }
  }
  *(int *)(iVar3 + 0x14) = (int)cVar2;
  return;
}


/* ---- FUN_0081bb6f @ 0081bb6f ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0081bb6f(float *param_1,float *param_2,int *param_3)

{
  float *pfVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  char cVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  float10 fVar10;
  float local_28;
  float fStack_24;
  float fStack_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  pfVar8 = param_1;
  for (iVar9 = 0x4a; iVar9 != 0; iVar9 = iVar9 + -1) {
    *pfVar8 = 0.0;
    pfVar8 = pfVar8 + 1;
  }
  param_1[0x40] = (float)((uint)param_3 & 0xb);
  param_1[0x41] = (float)((uint)param_3 >> 2 & 1);
  param_3 = &DAT_0083f798;
  do {
    cVar6 = FUN_0081a75b(&local_28,param_2 + *param_3 * 4,param_2 + param_3[1] * 4,
                         param_2 + param_3[2] * 4);
    if (cVar6 == '\0') {
      FUN_0081a75b(&local_28,param_2 + param_3[1] * 4,param_2 + param_3[2] * 4,
                   param_2 + param_3[3] * 4);
      cVar6 = FUN_0081a75b(&local_28,param_2 + param_3[2] * 4,param_2 + param_3[3] * 4,
                           param_2 + *param_3 * 4);
      if (cVar6 != '\0') goto LAB_0081bd08;
      FUN_0081a75b(&local_28,param_2 + param_3[3] * 4,param_2 + *param_3 * 4,
                   param_2 + param_3[1] * 4);
    }
    else {
      fVar10 = (float10)FUN_00805fc1(param_2 + param_3[3] * 4);
      if ((float10)_DAT_0081fda0 <= fVar10 - (float10)local_1c) {
        if (fVar10 - (float10)local_1c <= (float10)_DAT_0081fd40) goto LAB_0081bd08;
        pfVar8 = param_1 + ((int)param_1[0x3c] + 2) * 4;
        *pfVar8 = local_28;
        pfVar8[1] = fStack_24;
        pfVar8[2] = fStack_20;
        pfVar8[3] = local_1c;
        param_1[0x3c] = (float)((int)param_1[0x3c] + 1);
        iVar2 = *param_3;
        iVar9 = param_3[3];
        iVar7 = param_3[2];
      }
      else {
        FUN_0081a75b(&local_28,param_2 + param_3[1] * 4,param_2 + param_3[2] * 4,
                     param_2 + param_3[3] * 4);
        pfVar8 = param_1 + ((int)param_1[0x3c] + 2) * 4;
        *pfVar8 = local_28;
        pfVar8[1] = fStack_24;
        pfVar8[2] = fStack_20;
        pfVar8[3] = local_1c;
        param_1[0x3c] = (float)((int)param_1[0x3c] + 1);
        iVar2 = param_3[1];
        iVar9 = *param_3;
        iVar7 = param_3[3];
      }
      FUN_0081a75b(&local_28,param_2 + iVar7 * 4,param_2 + iVar9 * 4,param_2 + iVar2 * 4);
LAB_0081bd08:
      pfVar8 = param_1 + ((int)param_1[0x3c] + 2) * 4;
      *pfVar8 = local_28;
      pfVar8[1] = fStack_24;
      pfVar8[2] = fStack_20;
      pfVar8[3] = local_1c;
      param_1[0x3c] = (float)((int)param_1[0x3c] + 1);
    }
    param_3 = param_3 + 4;
    if (0x83f7f7 < (int)param_3) {
      iVar9 = 0;
      if (0 < (int)param_1[0x3c]) {
        pfVar8 = param_1 + 0xb;
        do {
          fVar3 = _DAT_0081fd40 - *pfVar8;
          *pfVar8 = fVar3;
          if ((SUB41(param_1[0x40],0) & 3) == 1) {
            *pfVar8 = fVar3 + _DAT_0081fd40;
          }
          iVar9 = iVar9 + 1;
          pfVar8 = pfVar8 + 4;
        } while (iVar9 < (int)param_1[0x3c]);
      }
      pfVar8 = param_1 + 4;
      *pfVar8 = *param_2;
      param_1[5] = param_2[1];
      param_1[6] = param_2[2];
      param_1[7] = param_2[3];
      *param_1 = *pfVar8;
      param_1[1] = param_1[5];
      param_1[2] = param_1[6];
      param_1[3] = param_1[7];
      param_1[0x38] = *pfVar8;
      param_1[0x39] = param_1[5];
      param_1[0x3a] = param_1[6];
      param_1[0x3b] = param_1[7];
      pfVar8 = param_2 + 6;
      param_2 = (float *)0x7;
      do {
        pfVar1 = pfVar8 + -2;
        FUN_00805f44(pfVar1);
        fVar3 = *pfVar1;
        if (*param_1 < *pfVar1) {
          fVar3 = *param_1;
        }
        *param_1 = fVar3;
        local_8 = pfVar8[-1];
        if (param_1[1] < pfVar8[-1]) {
          local_8 = param_1[1];
        }
        param_1[1] = local_8;
        local_c = *pfVar8;
        if (param_1[2] < *pfVar8) {
          local_c = param_1[2];
        }
        param_1[2] = local_c;
        local_10 = *pfVar1;
        if (*pfVar1 < param_1[4]) {
          local_10 = param_1[4];
        }
        param_1[4] = local_10;
        local_14 = pfVar8[-1];
        if (pfVar8[-1] < param_1[5]) {
          local_14 = param_1[5];
        }
        param_1[5] = local_14;
        local_18 = param_1[6];
        fVar4 = *pfVar8;
        if (*pfVar8 < local_18) {
          fVar4 = local_18;
        }
        pfVar8 = pfVar8 + 4;
        param_1[6] = fVar4;
        fVar5 = _DAT_0081fd40;
        param_2 = (float *)((int)param_2 + -1);
      } while (param_2 != (float *)0x0);
      *param_1 = fVar3 - _DAT_0081fd40;
      param_1[1] = local_8 - fVar5;
      param_1[2] = local_c - fVar5;
      param_1[4] = local_10 + fVar5;
      param_1[5] = local_14 + fVar5;
      param_1[6] = fVar4 + fVar5;
      FUN_0080600c(_DAT_0081fd3c);
      param_1[0x3b] = 1.0;
      return;
    }
  } while( true );
}


/* ---- FUN_0081bec3 @ 0081bec3 ---- */

void __fastcall FUN_0081bec3(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 local_14;
  
  FUN_00805cbc(0x80);
  FUN_00805cbc(0x1000);
  FUN_00805cbc(0x400);
  FUN_00805cbc(0x40);
  param_1[0x5252] = 0;
  param_1[0x5253] = 0;
  param_1[0x5254] = 0;
  param_1[0x5255] = 0;
  param_1[0x5257] = 0;
  param_1[0x5256] = 0;
  FUN_00805a4d();
  param_1[0x5258] = 0;
  FUN_00819c56();
  uVar1 = FUN_00801c05();
  param_1[0x54dc] = uVar1;
  FUN_00801bae(0,local_1c);
  param_1[0x54df] = 0;
  param_1[0x54dd] = local_18;
  param_1[0x54de] = local_14;
  param_1[0x54e0] = 0;
  param_1[0x54e1] = 0;
  param_1[0x54e2] = 0;
  param_1[0x54e3] = 0;
  param_1[0x5250] = 0xffffffff;
  param_1[0x5251] = 0xffffffff;
  *param_1 = 0;
  param_1[0x5550] = 0;
  puVar3 = param_1 + 0x5452;
  for (iVar2 = 0x70; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  uVar1 = FUN_0080166b(4,6);
  param_1[0x5250] = uVar1;
  uVar1 = FUN_0080166b(4,2);
  param_1[0x5251] = uVar1;
  FUN_00817d8d();
  FUN_0081ae3b();
  FUN_00819d78();
  puVar3 = param_1 + 0x53fa;
  for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined1 *)((int)param_1 + 0x14fe9) = 8;
  *(undefined1 *)(param_1 + 0x53fa) = 1;
  return;
}


/* ---- FUN_0081c027 @ 0081c027 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0081c027(int param_1,int param_2,undefined4 param_3,float param_4,int param_5)

{
  char cVar1;
  float *pfVar2;
  undefined4 *puVar3;
  float fVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  float *pfVar8;
  int *piVar9;
  float *pfVar10;
  float local_cc [32];
  int local_4c [8];
  uint local_2c;
  float local_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float *local_18;
  int local_14;
  int local_10;
  uint local_c;
  int local_8;
  
  local_8 = param_1;
  local_10 = 0;
  if (0 < *(int *)(param_2 + 0x60)) {
    local_14 = 0;
    do {
      piVar6 = (int *)(*(int *)(param_2 + 0x5c) + local_14);
      piVar9 = local_4c;
      for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
        *piVar9 = *piVar6;
        piVar6 = piVar6 + 1;
        piVar9 = piVar9 + 1;
      }
      uVar7 = local_2c & 3;
      iVar5 = 0;
      local_c = uVar7;
      if (((param_5 == 0) && (uVar7 == 0)) || ((param_5 == 1 && (uVar7 != 0)))) {
        do {
          FUN_00806305(param_3,local_4c[iVar5] * 0x50 + *(int *)(param_2 + 0x7c));
          iVar5 = iVar5 + 1;
        } while (iVar5 < 8);
        if (uVar7 == 0) {
LAB_0081c0df:
          pfVar2 = (float *)operator_new(0x1d8);
          local_18 = pfVar2;
          puVar3 = (undefined4 *)FUN_00806b54();
          *puVar3 = pfVar2;
          FUN_00805cbc(0);
          FUN_00805cbc(0);
          FUN_00805cbc(0);
          pfVar8 = local_cc;
          pfVar10 = pfVar2 + 0x56;
          for (iVar5 = 0x20; iVar5 != 0; iVar5 = iVar5 + -1) {
            *pfVar10 = *pfVar8;
            pfVar8 = pfVar8 + 1;
            pfVar10 = pfVar10 + 1;
          }
        }
        else {
          if (uVar7 == 1) {
            pfVar2 = (float *)operator_new(0x128);
          }
          else {
            if (uVar7 != 2) goto LAB_0081c0df;
            pfVar2 = (float *)operator_new(0x128);
          }
          puVar3 = (undefined4 *)FUN_00806b54();
          *puVar3 = pfVar2;
        }
        FUN_0081bb6f(local_cc,local_2c);
        pfVar2[0x42] = local_28;
        pfVar2[0x43] = fStack_24;
        pfVar2[0x44] = fStack_20;
        pfVar2[0x45] = fStack_1c;
        pfVar2[0x3d] = param_4;
        pfVar8 = pfVar2 + 0x3e;
        iVar5 = 2;
        do {
          *pfVar8 = 0.0;
          if (pfVar8[6] != 0.0) {
            fVar4 = (float)operator_new(0xb4);
            *pfVar8 = fVar4;
            FUN_00817d8d();
            *(float *)*pfVar8 = pfVar8[6];
            *(float *)((int)*pfVar8 + 0x54) = (pfVar2[4] + *pfVar2) * _DAT_0081f2ac;
            *(float *)((int)*pfVar8 + 0x58) = pfVar2[1];
            *(float *)((int)*pfVar8 + 0x5c) = (pfVar2[6] + pfVar2[2]) * _DAT_0081f2ac;
            *(undefined4 *)((int)*pfVar8 + 0xb0) = 0x23;
          }
          pfVar8 = pfVar8 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        if (local_c == 0) {
LAB_0081c267:
          local_c = 0;
          if (*(int *)(local_8 + 8) != 1 && -1 < *(int *)(local_8 + 8) + -1) {
            do {
              iVar5 = local_8;
              cVar1 = FUN_0081a181(*(undefined4 *)(*(int *)(local_8 + 4) + local_c * 4),pfVar2,
                                   local_cc);
              if (cVar1 != '\0') {
                puVar3 = (undefined4 *)FUN_00806b54();
                *puVar3 = local_18;
                puVar3 = (undefined4 *)FUN_00806b54();
                *puVar3 = *(undefined4 *)(*(int *)(iVar5 + 4) + local_c * 4);
              }
              local_c = local_c + 1;
            } while ((int)local_c < *(int *)(iVar5 + 8) + -1);
          }
        }
        else if (local_c == 1) {
          iVar5 = 0;
          if (0 < *(int *)(local_8 + 8)) {
            do {
              cVar1 = FUN_0081a181(*(undefined4 *)(*(int *)(local_8 + 4) + iVar5 * 4),pfVar2,
                                   local_cc);
              if (cVar1 != '\0') {
                puVar3 = (undefined4 *)FUN_00806b54();
                *puVar3 = pfVar2;
              }
              iVar5 = iVar5 + 1;
            } while (iVar5 < *(int *)(local_8 + 8));
          }
        }
        else {
          if (local_c != 2) goto LAB_0081c267;
          iVar5 = 0;
          if (0 < *(int *)(local_8 + 8)) {
            do {
              cVar1 = FUN_0081a181(*(undefined4 *)(*(int *)(local_8 + 4) + iVar5 * 4),pfVar2,
                                   local_cc);
              if (cVar1 != '\0') {
                puVar3 = (undefined4 *)FUN_00806b54();
                *puVar3 = pfVar2;
              }
              iVar5 = iVar5 + 1;
            } while (iVar5 < *(int *)(local_8 + 8));
          }
        }
      }
      local_10 = local_10 + 1;
      local_14 = local_14 + 0x34;
    } while (local_10 < *(int *)(param_2 + 0x60));
  }
  return;
}


/* ---- FUN_0081c2e4 @ 0081c2e4 ---- */

void FUN_0081c2e4(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  if ((param_2 == 0) || (*(int *)(param_1 + 0x1f0) != 0)) {
    *(int *)(param_1 + 0x1f0) = param_2;
  }
  else {
    iVar1 = FUN_0081b115(*(undefined4 *)(param_1 + 0x234),*(undefined4 *)(param_1 + 0x238),
                         *(undefined4 *)(param_1 + 0x23c),*(undefined4 *)(param_1 + 0x240));
    if (iVar1 != 0) {
      *(int *)(param_1 + 0x1f0) = param_2;
      piVar2 = (int *)(param_1 + 0x210);
      iVar3 = 5;
      do {
        *piVar2 = iVar1;
        piVar2 = piVar2 + 0x20;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  return;
}


/* ---- FUN_0081c341 @ 0081c341 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0081c341(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  char cVar5;
  int iVar6;
  float *pfVar7;
  float *pfVar8;
  float local_8;
  
  if (*(int *)(param_2 + 0x14) != 0) {
    if ((*(int *)(param_2 + 0x1c) == 0) || (iVar6 = FUN_00819fea(param_2 + 0x50,0), iVar6 != 0)) {
      iVar6 = FUN_0081b115(*(undefined4 *)(param_2 + 0x50),*(undefined4 *)(param_2 + 0x54),
                           *(undefined4 *)(param_2 + 0x58),*(undefined4 *)(param_2 + 0x5c));
      if (iVar6 == 0) {
        return;
      }
      *(int *)(param_2 + 0x1c) = iVar6;
    }
    *(undefined4 *)(param_2 + 0x14) = 0;
  }
  local_8 = *(float *)(param_1 + 0x15390);
  iVar6 = *(int *)(param_2 + 0xc);
  if (iVar6 == 1) {
LAB_0081c3b2:
    pfVar7 = (float *)(param_2 + 0x44);
    fVar1 = 0.0;
    iVar6 = 5;
    pfVar8 = pfVar7;
    do {
      fVar1 = fVar1 + *pfVar8;
      pfVar8 = pfVar8 + 0x20;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    iVar6 = 5;
    fVar1 = fVar1 * _DAT_0081fd28 * _DAT_0081f370;
    do {
      *pfVar7 = *pfVar7 * _DAT_0081fb60 + fVar1;
      pfVar7 = pfVar7 + 0x20;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  else if (iVar6 != 2) {
    if (iVar6 == 3) goto LAB_0081c3b2;
    if (iVar6 != 4) goto LAB_0081c420;
  }
  local_8 = *(float *)(param_1 + 0x15394);
  if (*(int *)(param_1 + 0x15360) != 0) {
    local_8 = 0.0;
  }
  *(undefined4 *)(param_2 + 0x28) = *(undefined4 *)(param_1 + 0x1539c);
  if (*(char *)(param_1 + 0x15364) == '\0') {
    *(undefined4 *)(param_2 + 0x28) = *(undefined4 *)(param_1 + 0x15398);
  }
LAB_0081c420:
  pfVar7 = (float *)(param_2 + 0x60);
  fVar4 = 1.0 - *(float *)(param_2 + 0x28);
  pfVar8 = (float *)(param_2 + 0x40);
  *(undefined4 *)(param_2 + 0x28) = 0;
  FUN_00805f1f(pfVar8,pfVar7);
  fVar1 = *pfVar7;
  fVar2 = *(float *)(param_2 + 100);
  fVar3 = *(float *)(param_2 + 0x68);
  *pfVar7 = *pfVar8;
  *(undefined4 *)(param_2 + 100) = *(undefined4 *)(param_2 + 0x44);
  *(undefined4 *)(param_2 + 0x68) = *(undefined4 *)(param_2 + 0x48);
  *(undefined4 *)(param_2 + 0x6c) = *(undefined4 *)(param_2 + 0x4c);
  *(float *)(param_2 + 0x40) = fVar4 * *pfVar8 + (*pfVar8 - fVar4 * fVar1);
  *(float *)(param_2 + 0x44) =
       (fVar4 * *(float *)(param_2 + 0x44) - local_8) + (*(float *)(param_2 + 0x44) - fVar4 * fVar2)
  ;
  *(float *)(param_2 + 0x48) =
       fVar4 * *(float *)(param_2 + 0x48) + (*(float *)(param_2 + 0x48) - fVar4 * fVar3);
  *(undefined4 *)(param_2 + 0x4c) = 0x3f800000;
  cVar5 = FUN_0081b5bd(param_2,0);
  if (cVar5 != '\0') {
    *(undefined4 *)(param_2 + 0x28) = 0x3dcccccd;
    *(float *)(param_2 + 100) = local_8 + *(float *)(param_2 + 100);
  }
  return;
}


/* ---- FUN_0081c4c4 @ 0081c4c4 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0081c4c4(undefined4 *param_1)

{
  float fVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 local_390 [105];
  undefined4 local_1ec [16];
  undefined1 local_1ac [192];
  undefined1 local_ec [64];
  undefined4 local_ac [16];
  int local_6c;
  int iStack_68;
  int iStack_64;
  int iStack_60;
  undefined1 local_5c [16];
  int local_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  undefined4 local_3c;
  int local_38;
  int iStack_34;
  int iStack_30;
  int local_2c;
  float local_28;
  float local_24;
  float local_20;
  int local_18;
  int local_14;
  int *local_10;
  int *local_c;
  int *local_8;
  
  if (param_1[0x67] != 0) {
    FUN_0081abbd(param_1 + 0x79);
  }
  puVar5 = param_1;
  puVar6 = local_390;
  for (iVar4 = 0xa9; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  FUN_0081a880(local_1ac);
  puVar5 = local_1ec;
  puVar6 = local_ac;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  FUN_008064ec();
  FUN_00805c2c(local_ac,local_1ac);
  bVar2 = false;
  local_18 = 0;
  if (0 < *(int *)(local_14 + 0x14844)) {
    local_10 = (int *)(local_14 + 0x44);
    do {
      local_c = (int *)*local_10;
      local_8 = local_c + 0x10;
      while( true ) {
        local_38 = *local_8;
        iStack_34 = local_8[1];
        iStack_30 = local_8[2];
        local_2c = local_8[3];
        if ((((param_1[0x68] == 0) || ((7 < local_8[-0xd] && (local_8[-0xd] < 0x10)))) &&
            ((undefined4 *)local_8[-8] != param_1)) &&
           (iVar4 = FUN_00819fea(&local_38,0), iVar4 == 0)) {
          local_4c = *local_8;
          iStack_48 = local_8[1];
          iStack_44 = local_8[2];
          iStack_40 = local_8[3];
          local_38 = local_4c;
          iStack_34 = iStack_48;
          iStack_30 = iStack_44;
          local_2c = iStack_40;
          FUN_008062e2(local_ec);
          FUN_00805f1f(&local_38,&local_4c);
          fVar1 = local_28 * local_28 + local_24 * local_24 + local_20 * local_20;
          if ((float)_DAT_0081fd50 <= fVar1) {
            FUN_0080600c((float)_DAT_0081f358 / SQRT(fVar1));
            cVar3 = FUN_0081a0e3(&local_38,&local_28,local_5c,&local_3c);
            if (cVar3 == '\0') {
              bVar2 = true;
            }
            FUN_0080604f(&local_28,local_3c);
            FUN_0080604f(local_5c,_DAT_0081fda4);
            local_2c = 0x3f800000;
            local_6c = *local_8;
            iStack_68 = local_8[1];
            iStack_64 = local_8[2];
            iStack_60 = local_8[3];
            *local_8 = local_38;
            local_8[1] = iStack_34;
            local_8[2] = iStack_30;
            local_8[3] = 0x3f800000;
            cVar3 = FUN_0081b5bd(local_c,1);
            if (cVar3 != '\0') {
              bVar2 = true;
            }
            *local_8 = local_6c;
            local_8[1] = iStack_68;
            local_8[2] = iStack_64;
            local_8[3] = iStack_60;
          }
          else {
            bVar2 = true;
          }
        }
        if (*local_c != 0) break;
        local_c = local_c + 0x20;
        local_8 = local_8 + 0x20;
      }
      local_18 = local_18 + 1;
      local_10 = local_10 + 1;
    } while (local_18 < *(int *)(local_14 + 0x14844));
    if (bVar2) {
      param_1[0x4e] = 1;
      return;
    }
  }
  param_1[0x40] = param_1[0x40] & 0xffffffdf;
  puVar5 = param_1 + 0x79;
  puVar6 = param_1 + 0x69;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  param_1[0x4e] = 0;
  FUN_0081a880(param_1 + 0x69);
  return;
}


/* ---- FUN_0081c728 @ 0081c728 ---- */

void __thiscall FUN_0081c728(int param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int *piVar4;
  int local_8;
  
  local_8 = 0;
  if (0 < *(int *)(param_1 + 0x14848)) {
    puVar2 = (undefined4 *)(param_1 + 0x10044);
    do {
      piVar3 = (int *)*puVar2;
      while( true ) {
        FUN_00819f7c(piVar3);
        if (*piVar3 != 0) break;
        piVar3 = piVar3 + 5;
      }
      local_8 = local_8 + 1;
      puVar2 = puVar2 + 1;
    } while (local_8 < *(int *)(param_1 + 0x14848));
  }
  local_8 = 0;
  if (0 < *(int *)(param_1 + 0x14844)) {
    puVar2 = (undefined4 *)(param_1 + 0x44);
    do {
      piVar3 = (int *)*puVar2;
      while( true ) {
        FUN_0081c341(piVar3);
        if (*piVar3 != 0) break;
        piVar3 = piVar3 + 0x20;
      }
      local_8 = local_8 + 1;
      puVar2 = puVar2 + 1;
    } while (local_8 < *(int *)(param_1 + 0x14844));
  }
  local_8 = 0;
  if (0 < *(int *)(param_1 + 0x1484c)) {
    piVar3 = (int *)(param_1 + 0x14044);
    do {
      iVar1 = *piVar3;
      FUN_0080659e(iVar1 + 0x224,iVar1 + 0x264,param_2);
      FUN_0081c4c4(iVar1);
      local_8 = local_8 + 1;
      piVar3 = piVar3 + 1;
    } while (local_8 < *(int *)(param_1 + 0x1484c));
  }
  local_8 = 0;
  if (0 < *(int *)(param_1 + 0x14844)) {
    param_2 = (int *)(param_1 + 0x44);
    do {
      piVar4 = (int *)*param_2;
      piVar3 = piVar4 + 0xe;
      while( true ) {
        FUN_00805f44(piVar3 + -2);
        piVar3[-2] = 0;
        piVar3[-1] = 0;
        *piVar3 = 0;
        piVar3[1] = 0;
        if (*piVar4 != 0) break;
        piVar4 = piVar4 + 0x20;
        piVar3 = piVar3 + 0x20;
      }
      local_8 = local_8 + 1;
      param_2 = param_2 + 1;
    } while (local_8 < *(int *)(param_1 + 0x14844));
  }
  return;
}


/* ---- FUN_0081c852 @ 0081c852 ---- */

undefined4
FUN_0081c852(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined1 local_14 [16];
  
  FUN_00805f1f(param_2,param_1);
  cVar1 = FUN_0081b45a(local_14,param_2,param_1,param_3,&local_24,&param_1,0,0);
  if (cVar1 == '\0') {
    uVar2 = 0;
  }
  else {
    FUN_0080604f(local_14,param_1);
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = local_24;
      param_4[1] = uStack_20;
      param_4[2] = uStack_1c;
      param_4[3] = uStack_18;
    }
    uVar2 = 1;
  }
  return uVar2;
}


/* ---- FUN_0081c8bb @ 0081c8bb ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0081c8bb(undefined4 param_1,float *param_2,undefined4 param_3)

{
  uint uVar1;
  float *pfVar2;
  float local_88 [33];
  
  uVar1 = 0;
  pfVar2 = local_88 + 2;
  do {
    pfVar2[-2] = -(((float)(uVar1 & 1) - _DAT_0081f2ac) * *param_2);
    pfVar2[-1] = -(((float)((int)uVar1 >> 1 & 1) - _DAT_0081f2ac) * param_2[1]);
    *pfVar2 = -(((float)((int)uVar1 >> 2 & 1) - _DAT_0081f2ac) * param_2[2]);
    pfVar2[1] = 1.0;
    FUN_00806349(param_1);
    uVar1 = uVar1 + 1;
    pfVar2 = pfVar2 + 4;
  } while ((int)uVar1 < 8);
  FUN_0081bb6f(local_88,param_3);
  return;
}


/* ---- FUN_0081c951 @ 0081c951 ---- */

void __thiscall FUN_0081c951(int param_1,int param_2,int param_3)

{
  char *pcVar1;
  int iVar2;
  
  if (0 < *(int *)(param_1 + 0x1e4)) {
    FUN_0081c2e4(param_1,1);
    iVar2 = *(int *)(param_1 + 0x54);
    if (iVar2 < param_2) {
      *(int *)(param_1 + 0x1e4) = *(int *)(param_1 + 0x1e4) + ((iVar2 - iVar2 / 4) - param_2);
    }
    else {
      *(int *)(param_1 + 0x1e4) = *(int *)(param_1 + 0x1e4) + param_2 / -4;
    }
    if (*(int *)(param_1 + 0x1e4) < 1) {
      *(undefined4 *)(param_1 + 0x1e4) = 0;
      if (0 < *(int *)(param_1 + 0x6c)) {
        pcVar1 = (char *)(*(int *)(param_1 + 0x6c) + 0x14fe8 + param_3);
        *pcVar1 = *pcVar1 + '\x01';
      }
    }
  }
  return;
}


/* ---- FUN_0081c9c1 @ 0081c9c1 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0081c9c1(int param_1,undefined4 *param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  byte *pbVar4;
  float10 fVar5;
  undefined1 local_84 [48];
  undefined4 local_54;
  float local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  float local_34 [3];
  undefined4 local_28;
  float local_24;
  float local_20;
  float local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  undefined4 *local_c;
  char *local_8;
  
  local_34[0] = _DAT_0081f2ac;
  local_34[2] = _DAT_0081f2ac;
  local_10 = param_1 + 0x348;
  local_28 = 0;
  local_44 = 0;
  puVar3 = (undefined4 *)(param_1 + 0x50);
  local_34[1] = 0.25;
  local_40 = 0;
  local_8 = "";
  local_3c = 0;
  local_38 = 0;
  do {
    local_24 = (float)(int)local_8[-1];
    local_14 = (int)local_8[1];
    local_20 = (float)(int)*local_8;
    local_1c = (float)local_14;
    local_18 = 0;
    local_c = puVar3;
    FUN_00805f88(local_34);
    FUN_00805f44(param_2);
    FUN_0081a939(&local_24,&local_44,param_3);
    local_8 = local_8 + 3;
    puVar3[-0x11] = param_4 + 1;
    *puVar3 = *param_2;
    puVar3[1] = param_2[1];
    puVar3[2] = param_2[2];
    puVar3[3] = param_2[3];
    local_c[-9] = 0x3f800000;
    local_c[-0xc] = local_10;
    puVar3 = local_c + 0x20;
  } while ((int)local_8 < 0x81fdd0);
  *(int *)(param_1 + 0xc) = param_4;
  *(undefined4 *)(param_1 + 0x200) = 1;
  pbVar4 = &DAT_0081fdad;
  puVar2 = (undefined4 *)(param_1 + 0x284);
  local_c = puVar3;
  do {
    puVar2[-1] = 0;
    *puVar2 = 0;
    puVar2[1] = (uint)pbVar4[-1] * 0x80 + param_1;
    iVar1 = (uint)*pbVar4 * 0x80 + param_1;
    puVar2[2] = iVar1;
    FUN_00805f1f(puVar2[1] + 0x40,iVar1 + 0x40);
    fVar5 = (float10)FUN_00806202();
    puVar2[3] = (float)fVar5;
    pbVar4 = pbVar4 + 2;
    puVar2 = puVar2 + 5;
  } while ((int)pbVar4 < 0x81fdc1);
  *(undefined4 *)(param_1 + 0x334) = 1;
  FUN_00805a4d();
  local_24 = _DAT_0081f2ac;
  local_1c = _DAT_0081f2ac;
  local_18 = 0;
  local_20 = 1.5;
  FUN_0081c8bb(local_84,&local_24,1);
  FUN_00805a4d();
  local_54 = *param_2;
  uStack_4c = param_2[2];
  uStack_48 = param_2[3];
  local_50 = (float)param_2[1] + _DAT_0081fda8;
  FUN_0081a7f8(local_84);
  return;
}


/* ---- FUN_0081cb71 @ 0081cb71 ---- */

void __thiscall
FUN_0081cb71(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6,undefined4 param_7)

{
  undefined4 uVar1;
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 local_14;
  
  FUN_00801bae(0,local_1c);
  *(undefined4 *)(param_1 + 0x14948) = param_2;
  *(undefined4 *)(param_1 + 0x1494c) = param_3;
  *(undefined4 *)(param_1 + 0x14950) = param_4;
  *(undefined4 *)(param_1 + 0x14954) = param_5;
  *(undefined4 *)(param_1 + 0x15374) = local_18;
  *(undefined4 *)(param_1 + 0x15378) = local_14;
  *(undefined4 *)(param_1 + 0x1495c) = param_6;
  *(undefined4 *)(param_1 + 0x14958) = param_7;
  uVar1 = FUN_0081b115(param_2,param_3,param_4,param_5);
  *(undefined4 *)(param_1 + 0x15380) = param_2;
  *(undefined4 *)(param_1 + 0x15384) = param_3;
  *(undefined4 *)(param_1 + 0x15388) = param_4;
  *(undefined4 *)(param_1 + 0x14960) = uVar1;
  *(undefined4 *)(param_1 + 0x1537c) = param_3;
  *(undefined4 *)(param_1 + 0x1538c) = param_5;
  FUN_0081c9c1(param_1 + 0x14948,uVar1,1);
  return;
}


/* ---- FUN_0081cc09 @ 0081cc09 ---- */

void FUN_0081cc09(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int in_stack_00000048;
  undefined4 in_stack_0000004c;
  undefined4 auStack_e4 [13];
  undefined4 uStack_b0;
  int iStack_ac;
  undefined1 *puStack_a8;
  undefined1 *puStack_a4;
  undefined1 *puStack_a0;
  undefined4 local_90 [16];
  undefined1 local_50 [68];
  int local_c;
  int local_8;
  
  iVar1 = param_1;
  puStack_a0 = (undefined1 *)(param_1 + 0x124);
  puStack_a4 = (undefined1 *)0x81cc2a;
  FUN_008063b2();
  local_c = *(int *)(param_1 + 0x148);
  if (*(int *)(param_1 + 0x148) == 0) {
    local_c = 1;
  }
  if (*(char *)(param_1 + 0x4c) != '\0') {
    in_stack_00000048 = param_1;
  }
  local_8 = 0;
  if (0 < local_c) {
    do {
      if ((*(int *)(iVar1 + 0x148) == 0) || (local_8 != 0)) {
        puStack_a0 = &stack0x00000008;
        puStack_a4 = local_50;
        puStack_a8 = (undefined1 *)0x81cc77;
        FUN_00805c2c();
        puVar4 = local_90;
        puVar5 = (undefined4 *)&stack0x00000008;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar5 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar5 = puVar5 + 1;
        }
      }
      param_1 = 0;
      if (0 < *(int *)(iVar1 + 0x10)) {
        do {
          puStack_a0 = (undefined1 *)in_stack_0000004c;
          iVar2 = *(int *)(iVar1 + 0xc);
          puStack_a4 = (undefined1 *)in_stack_00000048;
          puVar4 = (undefined4 *)&stack0x00000008;
          puVar5 = auStack_e4;
          for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
          }
          FUN_0081cc09(*(undefined4 *)(iVar2 + param_1 * 4));
          param_1 = param_1 + 1;
        } while (param_1 < *(int *)(iVar1 + 0x10));
      }
      if (*(int *)(iVar1 + 0x1c) != 0) {
        puStack_a0 = (undefined1 *)in_stack_0000004c;
        puStack_a8 = &stack0x00000008;
        puStack_a4 = (undefined1 *)in_stack_00000048;
        uStack_b0 = 0x81ccd8;
        iStack_ac = *(int *)(iVar1 + 0x1c);
        FUN_0081c027();
      }
      local_8 = local_8 + 1;
    } while (local_8 < local_c);
  }
  return;
}


/* ---- FUN_0081ccee @ 0081ccee ---- */

void __fastcall FUN_0081ccee(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = 0;
  *(undefined1 *)(param_1 + 0x15365) = 1;
  if (0 < *(int *)(param_1 + 0x28)) {
    do {
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x24) + iVar1 * 4) + 0x124) = 0;
      iVar1 = iVar1 + 1;
    } while (iVar1 < *(int *)(param_1 + 0x28));
  }
  FUN_0081cb71(*(undefined4 *)(param_1 + 0x153c4),*(undefined4 *)(param_1 + 0x153c8),
               *(undefined4 *)(param_1 + 0x153cc),*(undefined4 *)(param_1 + 0x153d0),0,0);
  *(undefined4 *)(param_1 + 0x15380) = *(undefined4 *)(param_1 + 0x14948);
  *(undefined4 *)(param_1 + 0x15384) = *(undefined4 *)(param_1 + 0x1494c);
  *(undefined4 *)(param_1 + 0x15388) = *(undefined4 *)(param_1 + 0x14950);
  *(undefined4 *)(param_1 + 0x1538c) = *(undefined4 *)(param_1 + 0x14954);
  *(undefined4 *)(param_1 + 0x1537c) = *(undefined4 *)(param_1 + 0x1494c);
  puVar2 = (undefined4 *)(param_1 + 0x14fea);
  for (iVar1 = 0x3f; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)puVar2 = 0;
  *(undefined1 *)(param_1 + 0x14fe9) = 0;
  DAT_014a0984 = 2;
  return;
}


/* ---- FUN_0081cd76 @ 0081cd76 ---- */

void __fastcall FUN_0081cd76(int param_1)

{
  undefined4 *puVar1;
  int local_8;
  
  FUN_0081cb71(*(undefined4 *)(param_1 + 0x153c4),*(undefined4 *)(param_1 + 0x153c8),
               *(undefined4 *)(param_1 + 0x153cc),*(undefined4 *)(param_1 + 0x153d0),0,0);
  local_8 = 0;
  puVar1 = (undefined4 *)(param_1 + 0x15160);
  do {
    if ((*(char *)(param_1 + 0x15008 + local_8) != '\0') && (puVar1[-6] != 0)) {
      FUN_0081cb71(puVar1[-4],puVar1[-3],puVar1[-2],puVar1[-1],*puVar1,0);
    }
    local_8 = local_8 + 1;
    puVar1 = puVar1 + 7;
  } while (local_8 < 0x10);
  *(undefined4 *)(param_1 + 0x1497c) = 100;
  if (*(int *)(param_1 + 0x1498c) < 200) {
    *(int *)(param_1 + 0x1498c) = 200;
  }
  return;
}


/* ---- FUN_0081ce11 @ 0081ce11 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_0081ce11(int param_1,undefined4 *param_2,int param_3)

{
  char cVar1;
  float10 fVar2;
  undefined4 local_14;
  float local_10;
  undefined8 local_c;
  
  FUN_00805f1f(param_2,param_1 + 0x15520);
  fVar2 = (float10)FUN_00806202();
  if ((float10)*(float *)(param_1 + 0x15530) <= fVar2) {
LAB_0081ce9a:
    local_c._0_4_ = 0;
  }
  else {
    local_14 = *param_2;
    local_c = *(undefined8 *)(param_2 + 2);
    local_10 = (float)param_2[1] + _DAT_0081f2ac;
    if (param_3 != 0) {
      cVar1 = FUN_0081c852(param_1 + 0x15520,&local_14,&param_3,0);
      if (cVar1 != '\0') goto LAB_0081ce9a;
    }
    local_c._0_4_ =
         (undefined4)
         (longlong)
         ROUND((_DAT_0081f2bc - (float)fVar2 / *(float *)(param_1 + 0x15530)) *
               (float)*(int *)(param_1 + 0x15534));
  }
  return (undefined4)local_c;
}


/* ---- FUN_0081cea2 @ 0081cea2 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0081cea2(int param_1)

{
  int *piVar1;
  char *pcVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  int iVar8;
  bool bVar9;
  int *local_10;
  int local_c;
  undefined4 *local_8;
  
  local_c = 0;
  if (0 < *(int *)(param_1 + 0x28)) {
    do {
      iVar8 = *(int *)(*(int *)(param_1 + 0x24) + local_c * 4);
      iVar5 = *(int *)(iVar8 + 0x124);
      if ((-1 < iVar5) && (iVar5 < 0x40000000)) {
        iVar5 = iVar5 + -10;
        if (iVar5 < 0) {
          iVar5 = 0;
        }
        *(int *)(iVar8 + 0x124) = iVar5;
      }
      if (*(char *)(*(byte *)(iVar8 + 0x109) + 0x14fe8 + param_1) != '\0') {
        bVar4 = *(byte *)(iVar8 + 0x108) & 0xf0;
        local_8 = (undefined4 *)0x0;
        if (0x70 < bVar4) {
          if (bVar4 == 0x80) {
            if ((*(byte *)(iVar8 + 0x120) & 2) != 0) {
              bVar9 = *(int *)(param_1 + 0x14970) == 0;
              goto LAB_0081d063;
            }
          }
          else {
            if (bVar4 == 0x90) {
              bVar9 = *(char *)(iVar8 + 0x119) == '\0';
              goto LAB_0081d063;
            }
            if (bVar4 == 0xa0) goto LAB_0081d065;
            if (bVar4 == 0xb0) {
              local_8 = (undefined4 *)(*(uint *)(iVar8 + 0x120) >> 1 & 1);
            }
            else if (bVar4 == 0xc0) {
              bVar9 = (*(ushort *)(iVar8 + 0x118) & 0xff02) == 0;
              goto LAB_0081d063;
            }
          }
          goto LAB_0081d06c;
        }
        if (bVar4 == 0x70) {
          if (((*(byte *)(iVar8 + 0x120) & 2) != 0) && (*(int *)(iVar8 + 0x124) == 0)) {
            *(undefined4 *)(iVar8 + 0x124) = 300000;
            goto LAB_0081d065;
          }
          goto LAB_0081d06c;
        }
        if (bVar4 == 0x10) {
          bVar9 = (*(byte *)(iVar8 + 0x118) & 2) == 0;
LAB_0081d063:
          if (!bVar9) {
LAB_0081d065:
            local_8 = (undefined4 *)0x1;
          }
        }
        else {
          if (bVar4 == 0x20) {
            bVar9 = (*(byte *)(iVar8 + 0x11c) & 2) == 0;
            goto LAB_0081d063;
          }
          if (bVar4 != 0x30) {
            if (bVar4 == 0x40) {
              if (((*(byte *)(iVar8 + 0x120) & 2) != 0) && (*(int *)(iVar8 + 0x124) == 0)) {
                *(undefined4 *)(iVar8 + 0x124) = 10000;
                goto LAB_0081d065;
              }
              goto LAB_0081d06c;
            }
            if (bVar4 == 0x50) {
              if (((*(byte *)(iVar8 + 0x120) & 2) != 0) && (*(int *)(iVar8 + 0x124) == 0)) {
                *(undefined4 *)(iVar8 + 0x124) = 30000;
                goto LAB_0081d065;
              }
              goto LAB_0081d06c;
            }
            if (((bVar4 != 0x60) || ((*(byte *)(iVar8 + 0x120) & 2) == 0)) ||
               (*(int *)(iVar8 + 0x124) != 0)) goto LAB_0081d06c;
            *(undefined4 *)(iVar8 + 0x124) = 60000;
            goto LAB_0081d065;
          }
          if (((*(byte *)(iVar8 + 0x120) & 2) != 0) && (*(int *)(iVar8 + 0x124) == 0)) {
            *(undefined4 *)(iVar8 + 0x124) = 0x7fffffff;
            goto LAB_0081d065;
          }
        }
LAB_0081d06c:
        bVar4 = *(byte *)(iVar8 + 0x10a);
        uVar7 = bVar4 & 0xf;
        piVar1 = (int *)(param_1 + 0x1497c + uVar7 * 4);
        switch(*(byte *)(iVar8 + 0x108) & 0xf) {
        case 1:
          if (local_8 != (undefined4 *)0x0) {
            *(undefined1 *)(bVar4 + 0x14fe8 + param_1) = 1;
          }
          break;
        case 2:
          if (local_8 != (undefined4 *)0x0) {
            *(undefined1 *)(bVar4 + 0x14fe8 + param_1) = 0;
          }
          break;
        case 3:
          if (local_8 != (undefined4 *)0x0) {
            pcVar2 = (char *)(bVar4 + 0x14fe8 + param_1);
            *pcVar2 = *pcVar2 == '\0';
          }
          break;
        case 4:
          *(undefined1 *)(bVar4 + 0x14fe8 + param_1) = local_8._0_1_;
          break;
        case 5:
          if (local_8 != (undefined4 *)0x0) {
            iVar5 = *(int *)(iVar8 + 0x10c);
LAB_0081d184:
            *piVar1 = iVar5;
          }
          break;
        case 6:
          if (local_8 != (undefined4 *)0x0) {
            iVar5 = *(int *)(iVar8 + 0x10c);
            iVar3 = *piVar1;
            if (iVar5 < *piVar1) {
LAB_0081d121:
              iVar5 = iVar3;
            }
            goto LAB_0081d184;
          }
          break;
        case 7:
          if (local_8 != (undefined4 *)0x0) {
            iVar5 = *(int *)(iVar8 + 0x10c);
            iVar3 = *piVar1;
            if (*piVar1 < iVar5) goto LAB_0081d121;
            goto LAB_0081d184;
          }
          break;
        case 8:
          if (local_8 != (undefined4 *)0x0) {
            if ((*(int *)(param_1 + 0x1497c + uVar7 * 4) == 0) && (7 < uVar7)) {
              *(uint *)(param_1 + 0x1496c) = uVar7 - 8;
            }
            iVar5 = *(int *)(iVar8 + 0x10c) + *piVar1;
            iVar3 = *(int *)(param_1 + 0x149bc + uVar7 * 4);
            if (iVar3 <= iVar5) goto LAB_0081d121;
            goto LAB_0081d184;
          }
          break;
        case 9:
          if (local_8 != (undefined4 *)0x0) {
            iVar5 = *piVar1 - *(int *)(iVar8 + 0x10c);
            if (iVar5 < 1) {
              iVar5 = 0;
            }
            goto LAB_0081d184;
          }
          break;
        case 10:
          if (local_8 != (undefined4 *)0x0) {
            *(float *)(param_1 + 0x15354) =
                 (float)*(int *)(iVar8 + 0x10c) * _DAT_0081f2c4 + *(float *)(param_1 + 0x15354);
          }
          break;
        case 0xb:
          if (local_8 != (undefined4 *)0x0) {
            *(undefined1 *)((*(uint *)(iVar8 + 0x10c) & 0xf) + 0x15008 + param_1) = 1;
          }
        }
      }
      local_c = local_c + 1;
      *(undefined4 *)(iVar8 + 0x118) = 0;
      *(undefined4 *)(iVar8 + 0x11c) = 0;
      *(undefined4 *)(iVar8 + 0x120) = 0;
    } while (local_c < *(int *)(param_1 + 0x28));
  }
  puVar6 = (undefined4 *)(param_1 + 0x150e8);
  iVar8 = 0;
  do {
    if (((*(uint *)(param_1 + 0x14e5c) | *(uint *)(param_1 + 0x14e64)) &
        1 << ((char)iVar8 + 8U & 0x1f)) != 0) {
      FUN_00819cf4(*puVar6);
    }
    iVar8 = iVar8 + 1;
    puVar6 = puVar6 + 1;
  } while (iVar8 < 8);
  local_c = 0;
  if (0 < *(int *)(param_1 + 0x1484c)) {
    local_10 = (int *)(param_1 + 0x14044);
    do {
      iVar8 = *local_10;
      if (*(int *)(iVar8 + 0x1a0) != 0) {
        local_8 = (undefined4 *)(param_1 + 0x150e8);
        iVar5 = 0;
        do {
          if (((*(uint *)(iVar8 + 0x118) | *(uint *)(iVar8 + 0x120)) &
              1 << ((char)iVar5 + 8U & 0x1f)) != 0) {
            FUN_0081c951(*local_8,param_1);
          }
          local_8 = local_8 + 1;
          iVar5 = iVar5 + 1;
        } while (iVar5 < 8);
      }
      local_10 = local_10 + 1;
      local_c = local_c + 1;
      *(undefined4 *)(iVar8 + 0x118) = 0;
      *(undefined4 *)(iVar8 + 0x11c) = 0;
      *(undefined4 *)(iVar8 + 0x120) = 0;
    } while (local_c < *(int *)(param_1 + 0x1484c));
  }
  return;
}


/* ---- FUN_0081d2d3 @ 0081d2d3 ---- */

void __thiscall FUN_0081d2d3(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = param_2 * 0x1c + param_1;
  if ((*(int *)(iVar1 + 0x15148) != 0) || (param_2 == 1)) {
    puVar2 = (undefined4 *)((param_2 + 0xc0c) * 0x1c + param_1);
    FUN_0081cb71(*puVar2,puVar2[1],puVar2[2],puVar2[3],*(undefined4 *)(iVar1 + 0x15160),0);
    FUN_00804a47(0xb,0x3f800000,0,0xac44);
  }
  return;
}


/* ---- FUN_0081d33e @ 0081d33e ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0081d33e(int param_1,undefined4 *param_2,float param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 *puVar4;
  int iVar5;
  char cVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  bool bVar10;
  float10 fVar11;
  undefined1 local_8c [16];
  undefined4 local_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 local_6c;
  float local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 local_5c;
  float local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  float local_4c [4];
  undefined4 local_3c;
  float local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 *local_c;
  int local_8;
  
  puVar4 = param_2;
  if ((int)param_2[0x79] < 1) {
    return;
  }
  puVar7 = param_2 + 0x39;
  puVar9 = param_2;
  for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar9 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar9 = puVar9 + 1;
  }
  local_1c = param_2[0x8d];
  local_18 = (float)param_2[0x8e];
  uStack_14 = param_2[0x8f];
  uStack_10 = param_2[0x90];
  local_8 = param_1;
  FUN_00805f1f(&local_1c,(undefined4 *)(param_1 + 0x14948));
  local_4c[1] = 0.0;
  fVar11 = (float10)FUN_00806223();
  iVar8 = local_8;
  fVar1 = (float)fVar11;
  local_6c = *(undefined4 *)(param_1 + 0x14948);
  uStack_64 = *(undefined4 *)(param_1 + 0x14950);
  uStack_60 = *(undefined4 *)(param_1 + 0x14954);
  local_68 = *(float *)(param_1 + 0x1494c) + _DAT_0081f2ac;
  local_5c = local_1c;
  uStack_54 = uStack_14;
  uStack_50 = uStack_10;
  local_58 = local_18 + _DAT_0081f2ac;
  local_c = *(undefined4 **)(local_8 + 0x14960);
  if (param_2[0x7c] == 0) {
    if ((fVar1 < (float)param_2[0x11]) &&
       (cVar6 = FUN_0081c852(&local_6c,&local_5c,&local_c,0), cVar6 == '\0')) {
      FUN_0081c2e4(param_2,1);
    }
    bVar10 = true;
    if (param_2[0x7c] == 0) goto LAB_0081d44c;
  }
  if (((float)param_2[0x11] < fVar1) &&
     (cVar6 = FUN_0081c852(&local_6c,&local_5c,&local_c,0), cVar6 != '\0')) {
    FUN_0081c2e4(param_2,0);
    param_2[0x7c] = 0;
  }
  bVar10 = param_2[0x7c] == 0;
LAB_0081d44c:
  fVar3 = _DAT_0081f2bc;
  if (!bVar10) {
    fVar2 = _DAT_0081fd48 / (float)param_2[0x17] + (float)param_2[0x7a];
    param_2[0x7a] = fVar2;
    if (fVar3 <= fVar2) {
      param_2[0x7a] = 0x3f800000;
    }
    fVar2 = _DAT_0081fd48 / (float)param_2[0x19] + (float)param_2[0x7b];
    param_2[0x7b] = fVar2;
    if (fVar3 <= fVar2) {
      param_2[0x7b] = 0x3f800000;
    }
    if (_DAT_0081fdd0 <= fVar1) {
      if (((((float)param_2[0x7b] == fVar3) && ((float)param_2[0x7a] == fVar3)) &&
          (0 < (int)param_2[0x18])) && (param_2[0x78] != 0)) {
        param_2[0x7b] = 0;
        local_3c = *(undefined4 *)(iVar8 + 0x14948);
        uStack_34 = *(undefined4 *)(iVar8 + 0x14950);
        uStack_30 = *(undefined4 *)(iVar8 + 0x14954);
        local_38 = *(float *)(iVar8 + 0x1494c) + fVar3;
        local_2c = param_2[0xc];
        local_24 = param_2[0xe];
        local_20 = param_2[0xf];
        local_28 = (float)param_2[0xd] + fVar3;
        cVar6 = FUN_0081c852(&local_3c,&local_2c,local_8 + 0x14960,0);
        iVar8 = local_8;
        if (cVar6 == '\0') {
          puVar7 = (undefined4 *)operator_new(0xb4);
          local_c = puVar7;
          FUN_00817d8d();
          puVar7[6] = 0;
          puVar7[0x11] = param_2[0x2f];
          puVar7[0x12] = param_2[0x30];
          puVar7[0x13] = param_2[0x31];
          puVar7[0x14] = param_2[0x32];
          local_c[0x15] = param_2[0x33];
          local_c[0x16] = param_2[0x34];
          local_c[0x17] = param_2[0x35];
          local_c[0x18] = param_2[0x36];
          *local_c = param_2[0x78];
          local_c[0x2b] = param_2;
          FUN_00818047(local_c);
          iVar8 = local_8;
        }
      }
    }
    else if ((((float)param_2[0x7b] == fVar3) && ((float)param_2[0x7a] == fVar3)) &&
            (0 < (int)param_2[0x16])) {
      param_2[0x7a] = 0;
      FUN_00819cf4(param_2[0x16]);
    }
    fVar3 = (float)param_2[0x10];
    if ((float)param_2[0x12] <= fVar1) {
      fVar2 = (float)param_2[0x1c];
    }
    else {
      fVar2 = (float)param_2[0x1d];
    }
    fVar1 = fVar1 - fVar2;
    param_3 = -(float)param_2[0x10];
    if ((fVar1 < fVar3) && (fVar3 = fVar1, fVar1 < param_3 != (fVar1 == param_3))) {
      fVar3 = param_3;
    }
    FUN_0080604f(local_4c,-fVar3);
    FUN_00805f66(param_2 + 0x8d);
    iVar5 = local_8;
    fVar1 = *(float *)(iVar8 + 0x15394) + *(float *)(iVar8 + 0x153a4);
    local_7c = param_2[0x8d];
    uStack_78 = param_2[0x8e];
    param_3 = (float)param_2[0x84];
    uStack_74 = param_2[0x8f];
    uStack_70 = param_2[0x90];
    local_3c = param_2[0x8d];
    param_2[399] = param_2[399] | 0x10;
    uStack_34 = param_2[0x8f];
    uStack_30 = param_2[0x90];
    local_38 = (float)param_2[0x8e] - fVar1;
    local_2c = 0;
    local_24 = 0;
    local_20 = 0;
    local_28 = -1.0;
    cVar6 = FUN_0081b45a(&local_2c,&local_3c,&local_7c,&param_3,local_8c,&local_c,0,0);
    param_2 = (undefined4 *)fVar1;
    if (cVar6 != '\0') {
      param_2 = (undefined4 *)((float)local_c + fVar1);
    }
    puVar4[399] = puVar4[399] & 0xffffffef;
    if ((float)param_2 < *(float *)(iVar5 + 0x15394) + *(float *)(iVar5 + 0x153a4)) {
      local_18 = ((*(float *)(iVar5 + 0x153a4) - *(float *)(iVar5 + 0x15394)) - (float)param_2) *
                 *(float *)(iVar5 + 0x153a0) + *(float *)(iVar5 + 0x15394) + local_18;
    }
    FUN_00819d55(&local_1c);
  }
  fVar3 = _DAT_0081f2bc;
  puVar4[0x33] = puVar4[0x8d];
  puVar4[0x34] = puVar4[0x8e];
  puVar4[0x35] = puVar4[0x8f];
  puVar4[0x36] = puVar4[0x90];
  puVar4[0x2f] = 0;
  fVar11 = (float10)fpatan(-(float10)local_4c[0],-(float10)local_4c[2]);
  puVar4[0x30] = (float)(fVar11 * (float10)_DAT_0081fcc0);
  puVar4[0x31] = 0;
  puVar4[0x32] = 0;
  fVar1 = (float)puVar4[0x7a] - _DAT_0081f2ac;
  bVar10 = fVar1 < _DAT_0081f374;
  puVar4[0x2b] = fVar1;
  if (bVar10) {
    puVar4[0x2b] = fVar1 + fVar3;
  }
  fVar1 = (float)puVar4[0x7b] - _DAT_0081f2ac;
  bVar10 = fVar1 < _DAT_0081f374;
  puVar4[0x2c] = fVar1;
  if (bVar10) {
    puVar4[0x2c] = fVar1 + fVar3;
  }
  puVar4[0x4a] = 0x23;
  puVar4[0x2d] = (float)(int)puVar4[0x79] / (float)(int)puVar4[0x14];
  return;
}


/* ---- Exec_KKrieger_Monster @ 0081d7d6 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Exec_KKrieger_Monster(int param_1,int param_2)

{
  float *pfVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  float *pfVar6;
  undefined4 *puVar7;
  float *pfVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  undefined4 local_ac [16];
  undefined1 local_6c [64];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  iVar2 = FUN_00817b57(param_1,0x7f4);
  puVar7 = (undefined4 *)(iVar2 + 0x14);
  local_8 = (undefined4 *)iVar2;
  if (*(char *)(iVar2 + 0x10) == '\0') {
LAB_0081d811:
    if (DAT_014a0984 == 0) goto LAB_0081d9b4;
  }
  else {
    puVar4 = puVar7;
    for (iVar5 = 0x1f8; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    if (*(char *)(iVar2 + 0x10) == '\0') goto LAB_0081d811;
  }
  puVar4 = *(undefined4 **)(param_1 + 0x94);
  local_c = puVar4;
  FUN_00817d8d();
  *(undefined4 *)(iVar2 + 0xd0) = *puVar4;
  *(undefined4 *)(iVar2 + 0xd4) = puVar4[1];
  *(undefined4 *)(iVar2 + 0xd8) = puVar4[2];
  *(undefined4 *)(iVar2 + 0xe0) = local_c[3];
  *(undefined4 *)(iVar2 + 0xe4) = local_c[4];
  *(undefined4 *)(iVar2 + 0xe8) = local_c[5];
  pfVar1 = (float *)(iVar2 + 0x54);
  pfVar6 = (float *)(local_c + 6);
  pfVar8 = pfVar1;
  for (iVar5 = 0xe; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar8 = *pfVar6;
    pfVar6 = pfVar6 + 1;
    pfVar8 = pfVar8 + 1;
  }
  *pfVar1 = *pfVar1 * _DAT_0081f2c4;
  uVar3 = FUN_0080e11f(0);
  *(undefined4 *)(iVar2 + 500) = uVar3;
  *(undefined4 *)(iVar2 + 0x1f8) = *(undefined4 *)(iVar2 + 100);
  puVar4 = (undefined4 *)(param_2 + 0x94f0);
  puVar9 = puVar7;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar9 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar9 = puVar9 + 1;
  }
  FUN_00805f44(param_2 + 0x9520);
  *(undefined4 *)(iVar2 + 0x8c) = 0;
  FUN_00805a4d();
  *(undefined4 *)(iVar2 + 0x128) = *(undefined4 *)(iVar2 + 0xe0);
  *(undefined4 *)(iVar2 + 300) = *(undefined4 *)(iVar2 + 0xe4);
  *(undefined4 *)(iVar2 + 0x130) = *(undefined4 *)(iVar2 + 0xe8);
  *(undefined4 *)(iVar2 + 0x134) = *(undefined4 *)(iVar2 + 0xec);
  *(undefined4 *)(iVar2 + 0x134) = 0x3f800000;
  *(undefined4 **)(iVar2 + 0x138) = puVar7;
  FUN_00817d8d();
  FUN_00805a9d(*(undefined4 *)(iVar2 + 0xd0),*(undefined4 *)(iVar2 + 0xd4),
               *(undefined4 *)(iVar2 + 0xd8));
  local_2c = local_c[0x14];
  local_20 = 0;
  local_14 = local_c[0x19];
  local_28 = local_c[0x15];
  local_18 = (float)local_c[0x18];
  local_24 = local_c[0x16];
  local_1c = local_c[0x17];
  local_10 = 0;
  FUN_008061a4(local_6c,&local_1c);
  local_1c = *(undefined4 *)(param_2 + 0x9520);
  local_14 = *(undefined4 *)(param_2 + 0x9528);
  local_10 = *(undefined4 *)(param_2 + 0x952c);
  local_18 = *(float *)(param_2 + 0x9524) + _DAT_0081f2ac;
  uVar10 = 3;
  uVar3 = FUN_0081b115(local_1c,local_18,local_14,local_10);
  FUN_0081c9c1(&local_1c,uVar3,uVar10);
  FUN_0081c8bb(local_6c,&local_2c,1);
  FUN_0081a7f8(param_2 + 0x94f0);
  *(undefined4 **)(iVar2 + 0x6f0) = puVar7;
  *(int *)((int)local_8 + 8) = iVar2 + 0xa8;
LAB_0081d9b4:
  if (0 < *(int *)(iVar2 + 0x1f8)) {
    puVar4 = puVar7;
    puVar9 = (undefined4 *)(iVar2 + 0x7b4);
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar9 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar9 = puVar9 + 1;
    }
    puVar4 = (undefined4 *)FUN_00806b54();
    *puVar4 = puVar7;
    if (*(int *)(iVar2 + 0x204) != 0) {
      FUN_0081ae0f(*(undefined4 *)(param_2 + 0x1358));
    }
    local_8 = (undefined4 *)(param_2 + 0x94f0);
    puVar7 = local_8;
    puVar4 = local_ac;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar4 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar4 = puVar4 + 1;
    }
    FUN_00805a4d();
    uVar3 = 1;
    iVar2 = iVar2 + 0x8c;
    FUN_0080e106(0);
    FUN_0081966f(param_2,iVar2,uVar3);
    puVar7 = local_ac;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *local_8 = *puVar7;
      puVar7 = puVar7 + 1;
      local_8 = local_8 + 1;
    }
  }
  return;
}


/* ---- FUN_0081da41 @ 0081da41 ---- */

void FUN_0081da41(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 auStack_98 [14];
  undefined4 uStack_60;
  int iStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_44 [16];
  
  uStack_54 = 0x81da54;
  FUN_00805a4d();
  uStack_54 = 0;
  uStack_58 = 0x81da5e;
  iVar2 = FUN_0080e106();
  if ((*(code **)(iVar2 + 0x24) == Exec_Misc_Nop__OpE0_Exec) ||
     (*(int *)(*(int *)(iVar2 + 0x18) + 4) == 8)) {
    uStack_54 = param_3;
    uStack_58 = param_2;
    uStack_60 = 0x81daa7;
    iStack_5c = iVar2;
    FUN_0081da41();
  }
  else {
    uStack_54 = 3;
    uStack_58 = 0x81da7b;
    FUN_00817a85();
    uStack_54 = param_3;
    uVar1 = *(undefined4 *)(iVar2 + 0x18);
    puVar3 = local_44;
    puVar4 = auStack_98;
    uStack_58 = uVar1;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    FUN_0081cc09(uVar1);
  }
  return;
}


/* ---- FUN_0081daae @ 0081daae ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_0081daae(int param_1,uint param_2)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  *(uint *)(param_1 + 0x1553c) = param_2 & 0x8001ffff;
  uVar2 = param_2 & 0x8001ffff;
  if (uVar2 < 0x65) {
    if (uVar2 == 100) {
LAB_0081dc08:
      *(undefined4 *)(param_1 + 0x1535c) = *(undefined4 *)(param_1 + 0x153b4);
      DAT_014a0988 = 0;
      return 1;
    }
    if (uVar2 < 0x3a) {
      if (uVar2 != 0x39) {
        if (uVar2 < 0x35) {
          if (uVar2 == 0x34) goto LAB_0081db06;
          if (uVar2 == 0x20) {
            if (*(char *)(param_1 + 0x15364) == '\0') {
              return 0;
            }
            if (*(int *)(param_1 + 0x15368) == 0) {
              *(undefined4 *)(param_1 + 0x15354) = *(undefined4 *)(param_1 + 0x153c0);
              FUN_00804a47(4,_DAT_0081fdd4,0,0xac44);
              *(undefined4 *)(param_1 + 0x15368) = 100;
              return 0;
            }
            return 0;
          }
          iVar3 = uVar2 - 0x31;
        }
        else {
          if (uVar2 == 0x35) goto LAB_0081db06;
          iVar3 = uVar2 - 0x36;
        }
        if (((iVar3 != 0) && (iVar3 != 1)) && (iVar3 != 2)) {
          return 0;
        }
      }
LAB_0081db06:
      if (DAT_014a0988 != 0) {
        FUN_0081d2d3(param_2 & 0xf);
        DAT_014a0988 = 0;
        return 1;
      }
      iVar3 = (int)(char)(&DAT_0083f7f8)[param_2 & 7];
      if (-1 < iVar3) {
        if (*(int *)(param_1 + 0x1499c + iVar3 * 4) != 0) {
          *(int *)(param_1 + 0x1496c) = iVar3;
          return 1;
        }
        return 1;
      }
      return 1;
    }
    if (uVar2 < 0x4f) {
      if (uVar2 == 0x4e) {
LAB_0081dc55:
        if (DAT_014a0988 == 0) {
          DAT_014a0988 = 0;
          return 1;
        }
        puVar4 = (undefined4 *)(param_1 + 0x149bc);
        puVar5 = (undefined4 *)(param_1 + 0x1497c);
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar5 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar5 = puVar5 + 1;
        }
        DAT_014a0988 = 0;
        return 1;
      }
      if (uVar2 != 0x41) {
        if (uVar2 != 0x44) {
          if (uVar2 != 0x4b) {
            if (uVar2 == 0x4d) {
              DAT_014a0988 = 1;
              return 1;
            }
            return 0;
          }
          goto LAB_0081dc78;
        }
        goto LAB_0081dc08;
      }
    }
    else {
      if (uVar2 == 0x53) goto LAB_0081dc48;
      if (uVar2 == 0x57) goto LAB_0081dc8a;
      if (uVar2 == 0x59) goto LAB_0081dcca;
      if (uVar2 != 0x61) {
        return 0;
      }
    }
    fVar1 = -*(float *)(param_1 + 0x153b4);
    goto LAB_0081dd04;
  }
  if (uVar2 < 0x80000042) {
    if (uVar2 != 0x80000041) {
      if (0x77 < uVar2) {
        if (uVar2 != 0x79) {
          if (uVar2 == 0x10021) {
            *(undefined4 *)(param_1 + 0x14970) = 1;
            return 1;
          }
          if ((uVar2 != 0x10025) && (uVar2 != 0x10028)) {
            return 0;
          }
          *(undefined4 *)(param_1 + 0x14974) = 1;
          return 1;
        }
LAB_0081dcca:
        *(uint *)(param_1 + 0x15360) = (uint)(*(uint *)(param_1 + 0x15360) == 0);
        return 1;
      }
      if (uVar2 == 0x77) {
LAB_0081dc8a:
        *(undefined4 *)(param_1 + 0x15358) = *(undefined4 *)(param_1 + 0x153b8);
        DAT_014a0988 = 0;
        return 1;
      }
      if (uVar2 == 0x6b) {
LAB_0081dc78:
        FUN_00819cf4(10);
        return 0;
      }
      if (uVar2 == 0x6d) {
        DAT_014a0988 = 1;
        return 1;
      }
      if (uVar2 == 0x6e) goto LAB_0081dc55;
      if (uVar2 != 0x73) {
        return 0;
      }
LAB_0081dc48:
      fVar1 = -*(float *)(param_1 + 0x153bc);
      goto LAB_0081dd37;
    }
  }
  else {
    if (0x80000064 < uVar2) {
      if ((uVar2 != 0x80000073) && (uVar2 != 0x80000077)) {
        if ((uVar2 != 0x80010025) && (uVar2 != 0x80010028)) {
          return 0;
        }
        *(undefined4 *)(param_1 + 0x14974) = 0;
        return 1;
      }
LAB_0081dd35:
      fVar1 = 0.0;
LAB_0081dd37:
      *(float *)(param_1 + 0x15358) = fVar1;
      DAT_014a0988 = 0;
      return 1;
    }
    if ((uVar2 != 0x80000064) && (uVar2 != 0x80000044)) {
      if ((uVar2 == 0x80000053) || (uVar2 == 0x80000057)) goto LAB_0081dd35;
      if (uVar2 != 0x80000061) {
        return 0;
      }
    }
  }
  fVar1 = 0.0;
LAB_0081dd04:
  *(float *)(param_1 + 0x1535c) = fVar1;
  DAT_014a0988 = 0;
  return 1;
}


/* ---- FUN_0081dd4c @ 0081dd4c ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0081dd4c(int *param_1,int param_2,int param_3)

{
  float *pfVar1;
  float fVar2;
  bool bVar3;
  float fVar4;
  float fVar5;
  char cVar6;
  int iVar7;
  undefined4 uVar8;
  int *piVar9;
  int iVar10;
  undefined4 *puVar11;
  int *piVar12;
  undefined4 *puVar13;
  ushort uVar14;
  undefined1 local_80 [4];
  int local_7c;
  int local_78;
  undefined1 local_68 [16];
  int local_58;
  int iStack_54;
  int iStack_50;
  int iStack_4c;
  int local_48;
  float local_44;
  int iStack_40;
  int iStack_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  int local_14;
  int *local_10;
  float local_c;
  float local_8;
  
  if (param_1[0x5258] == 0) {
    return;
  }
  if (param_1[0x5286] == 0) {
    return;
  }
  param_1[0x5550] = param_1[0x5550] + param_3;
  cVar6 = *(char *)((int)param_1 + 0x14fe9);
  if (cVar6 != '\0') {
    if (cVar6 == '\x02') {
      FUN_0081ccee();
      return;
    }
    if (cVar6 != '\x03') {
      return;
    }
    FUN_0080102e();
    return;
  }
  *param_1 = param_2;
  local_10 = (int *)param_1[0x54dc];
  iVar7 = FUN_00801c05();
  iVar7 = iVar7 - (int)local_10;
  param_1[0x54dc] = (int)local_10 + iVar7;
  FUN_00801bae(0,local_80);
  if (iVar7 < 1000) {
    param_1[0x5257] =
         (int)((float)(local_7c - param_1[0x54dd]) * (float)param_1[0x54eb] + (float)param_1[0x5257]
              );
    local_10 = (int *)(local_78 - param_1[0x54de]);
    fVar2 = (float)(int)local_10 * (float)param_1[0x54ec] + (float)param_1[0x5256];
    bVar3 = fVar2 < _DAT_0081fcbc;
    param_1[0x5256] = (int)fVar2;
    fVar4 = _DAT_0081fcbc;
    if ((bVar3) && (fVar4 = fVar2, fVar2 < _DAT_0081fdec != (fVar2 == _DAT_0081fdec))) {
      fVar4 = _DAT_0081fdec;
    }
    param_1[0x5256] = (int)fVar4;
  }
  param_1[0x54dd] = local_7c;
  param_1[0x54de] = local_78;
  if (param_1[0x54d8] == 0) {
    iVar7 = 0;
  }
  else {
    iVar7 = param_1[0x5256];
  }
  FUN_00805a9d(iVar7,param_1[0x5257],0);
  fVar4 = _DAT_0081fb60;
  fVar2 = _DAT_0081f2ac;
  if (param_1[0x525b] != param_1[0x525a]) {
    if ((float)param_1[0x5523] < _DAT_0081fb60) {
      param_1[0x5523] = (int)((float)param_3 * _DAT_0081fde8 + (float)param_1[0x5523]);
    }
    param_1[0x5523] = (int)((float)param_3 * _DAT_0081fd48 + (float)param_1[0x5523]);
    goto LAB_0081dfb0;
  }
  if (_DAT_0081f370 <= (float)param_1[0x5523]) {
    if (((float)param_1[0x5523] <= _DAT_0081fde4) && ((float)param_1[0x54d6] <= _DAT_0081f374))
    goto LAB_0081dfb0;
    fVar5 = (float)param_3 * _DAT_0081fde0 + (float)param_1[0x5523];
    param_1[0x5523] = (int)fVar5;
    if (fVar5 <= fVar4) goto LAB_0081dfb0;
    if ((float)param_1[0x54d6] <= _DAT_0081f374) {
      param_1[0x5523] = 0x3e800000;
      goto LAB_0081dfb0;
    }
    fVar5 = fVar5 - fVar2;
    param_1[0x5523] = (int)fVar5;
    uVar14 = (ushort)(fVar5 < (float)_DAT_0081fcf8) << 8 |
             (ushort)(fVar5 == (float)_DAT_0081fcf8) << 0xe;
  }
  else {
    fVar4 = (float)param_3 * _DAT_0081fd48 + (float)param_1[0x5523];
    param_1[0x5523] = (int)fVar4;
    uVar14 = (ushort)(fVar4 < _DAT_0081f370) << 8 | (ushort)(fVar4 == _DAT_0081f370) << 0xe;
  }
  if (uVar14 == 0) {
    param_1[0x5523] = 0x3e800000;
  }
LAB_0081dfb0:
  if (((float)param_1[0x54d6] != _DAT_0081f374) || ((float)param_1[0x54d7] != _DAT_0081f374)) {
    fVar4 = (float)param_3 * _DAT_0081fd48 + (float)param_1[0x5544];
    param_1[0x5544] = (int)fVar4;
    if (fVar2 < fVar4) {
      param_1[0x5544] = (int)(fVar4 - fVar2);
      uVar8 = _DAT_0081fddc;
      iVar7 = 1 - param_1[0x5545];
      param_1[0x5545] = iVar7;
      FUN_00804a47(iVar7,uVar8,0,0xac44);
    }
  }
  if (param_1[0x5547] != 0) {
    local_10 = (int *)FUN_0081b115(param_1[0x5548],param_1[0x5549],param_1[0x554a],param_1[0x554b]);
    iVar7 = 0;
    if (0 < param_1[0xe]) {
      do {
        piVar9 = param_1;
        uVar8 = FUN_0081ce11(*(int *)(*(int *)(*(int *)(param_2 + 0x1358) + 0x34) + iVar7 * 4) +
                             0x30,local_10);
        FUN_0081c951(uVar8,piVar9);
        iVar7 = iVar7 + 1;
      } while (iVar7 < param_1[0xe]);
    }
    param_1[0x554d] = param_1[0x554d] / 2;
    uVar8 = FUN_0081ce11(param_1 + 0x5252,local_10);
    FUN_00819cf4(uVar8);
    param_1[0x5547] = 0;
  }
  if (param_1[0x525d] != 0) {
    piVar9 = param_1 + 0x525a;
    if (param_1[*piVar9 / 2 + 0x5263] == 0) {
      FUN_00804a47(0xf,_DAT_0081fddc,0,0xac44);
    }
    piVar12 = param_1 + *piVar9 / 2 + 0x5263;
    if ((((0 < *piVar12) && (*piVar9 == param_1[0x525b])) &&
        ((float)param_1[0x525e] < _DAT_0081f374 != ((float)param_1[0x525e] == _DAT_0081f374))) &&
       (_DAT_0081f370 <= (float)param_1[0x5523])) {
      *piVar12 = *piVar12 + -1;
      iVar7 = *piVar9;
      param_1[0x525e] = param_1[iVar7 + 0x5442];
      if ((*(byte *)(param_1 + iVar7 + 0x544a) & 1) == 0) {
        param_1[0x525d] = 0;
      }
      if (param_1[iVar7 + 0x5524] != 0) {
        piVar9 = (int *)operator_new(0xb4);
        local_10 = piVar9;
        FUN_00817d8d();
        fVar4 = _DAT_0081fd98;
        piVar9[6] = 0;
        fVar2 = (float)param_1[0x5257];
        piVar9[0x11] = (int)((float)param_1[0x5256] * fVar4);
        piVar9[0x12] = (int)(fVar2 * fVar4);
        piVar9[0x13] = 0;
        piVar9[0x14] = 0;
        piVar9[0x15] = param_1[0x5252];
        piVar9[0x16] = param_1[0x5253];
        piVar9[0x17] = param_1[0x5254];
        piVar9[0x18] = param_1[0x5255];
        local_10[0x16] = (int)((float)param_1[0x54df] + (float)param_1[0x54d2]);
        *local_10 = param_1[param_1[0x525a] + 0x5524];
        FUN_00818047(local_10);
      }
      if ((*(byte *)(param_1 + param_1[0x525a] + 0x544a) & 1) == 0) {
        param_1[0x525d] = 0;
      }
    }
  }
  pfVar1 = (float *)(param_1 + 0x525e);
  if (_DAT_0081f374 <= *pfVar1) {
    *pfVar1 = *pfVar1 - (float)param_3 * _DAT_0081fd48;
  }
  if ((0 < param_3) && (local_8 = 0.0, 0 < param_1[0x5211])) {
    local_10 = param_1 + 0x11;
    do {
      piVar12 = (int *)*local_10;
      piVar9 = piVar12 + 0x10;
      while( true ) {
        if (piVar9[-0xc] != 0) {
          FUN_00805f1f(piVar9,piVar9 + 8);
          local_c = (float)param_3;
          FUN_0080600c(local_c);
          FUN_00805f44(piVar9);
          FUN_00805f66(piVar9 + 0xc);
          FUN_0080604f(&local_28,1.0 / local_c);
          piVar9[-0xc] = 0;
        }
        if (*piVar12 != 0) break;
        piVar12 = piVar12 + 0x20;
        piVar9 = piVar9 + 0x20;
      }
      local_8 = (float)((int)local_8 + 1);
      local_10 = local_10 + 1;
    } while ((int)local_8 < param_1[0x5211]);
  }
  local_10 = (int *)0x0;
  if (0 < param_3) {
    local_c = (float)param_3;
    do {
      if (0 < param_1[0x54da]) {
        param_1[0x54da] = param_1[0x54da] + -1;
      }
      local_8 = (float)param_1[0x54e5] + (float)param_1[0x54e9];
      if (param_1[0x5286] != 0) {
        local_58 = param_1[0x528f];
        iStack_54 = param_1[0x5290];
        iStack_50 = param_1[0x5291];
        iStack_4c = param_1[0x5292];
        local_14 = param_1[0x5258];
        local_48 = param_1[0x528f];
        iStack_40 = param_1[0x5291];
        iStack_3c = param_1[0x5292];
        local_44 = (float)param_1[0x5290] - local_8;
        param_1[0x5391] = param_1[0x5391] | 0x10;
        local_38 = 0;
        local_30 = 0;
        local_2c = 0;
        local_34 = 0xbf800000;
        cVar6 = FUN_0081b45a(&local_38,&local_48,&local_58,&local_14,local_68,&local_18,
                             param_1 + 0x527f,0);
        if (cVar6 != '\0') {
          local_8 = local_18 + local_8;
        }
        param_1[0x5391] = param_1[0x5391] & 0xffffffef;
      }
      local_28 = 0;
      local_24 = 0.0;
      local_20 = 0;
      local_1c = 0;
      FUN_0080604f(param_1 + 0x54c2,param_1[0x54d7]);
      FUN_0080604f(param_1 + 0x54ca,param_1[0x54d6]);
      local_24 = local_24 + (float)param_1[0x54d5];
      *(undefined1 *)(param_1 + 0x54d9) = 0;
      param_1[0x54d5] = 0;
      if ((float)param_1[0x54e5] + (float)param_1[0x54e9] <= local_8) {
        fVar2 = local_c * _DAT_0081fd48 + (float)param_1[0x5546];
      }
      else {
        if (_DAT_0081fdd8 <= (float)param_1[0x5546]) {
          FUN_00804a47(5,0x3f800000,0,0xac44);
          param_1[0x5545] = 0;
          param_1[0x5544] = 0;
        }
        *(undefined1 *)(param_1 + 0x54d9) = 1;
        local_24 = (((float)param_1[0x54e9] - (float)param_1[0x54e5]) - local_8) *
                   (float)param_1[0x54e8] + (float)param_1[0x54e5] + local_24;
        fVar2 = 0.0;
      }
      param_1[0x5546] = (int)fVar2;
      FUN_00819d55(&local_28);
      FUN_00805a9d(0,param_1[0x5257],0);
      param_1[0x53f6] = param_1[0x5252];
      param_1[0x53f7] = param_1[0x5253];
      param_1[0x53f8] = param_1[0x5254];
      param_1[0x53f9] = param_1[0x5255];
      param_1[0x53f7] = (int)((float)param_1[0x53f7] + _DAT_0081fda8);
      param_1[0x53e6] = param_1[0x53f6];
      fVar2 = (float)(int)local_10 + _DAT_0081f2bc;
      param_1[0x53e7] = param_1[0x53f7];
      param_1[0x53e8] = param_1[0x53f8];
      param_1[0x53e9] = param_1[0x53f9];
      FUN_0081c728(fVar2 / local_c);
      param_1[0x5252] = param_1[0x528f];
      param_1[0x5253] = param_1[0x5290];
      param_1[0x5254] = param_1[0x5291];
      param_1[0x5255] = param_1[0x5292];
      FUN_0081cea2(param_2);
      param_1[0x54e0] = param_1[0x5252];
      param_1[0x54e1] = param_1[0x5253];
      param_1[0x54e2] = param_1[0x5254];
      param_1[0x54e3] = param_1[0x5255];
      fVar2 = ((float)param_1[0x5253] - (float)param_1[0x54df]) * (float)param_1[0x54f5] +
              (float)param_1[0x54df];
      param_1[0x54df] = (int)fVar2;
      iVar7 = 0;
      param_1[0x54e1] = (int)(fVar2 + (float)param_1[0x54d2]);
      if (0 < param_1[0xe]) {
        do {
          FUN_0081d33e(*(undefined4 *)(param_1[0xd] + iVar7 * 4),param_2);
          iVar7 = iVar7 + 1;
        } while (iVar7 < param_1[0xe]);
      }
      param_1[0x525c] = 0;
      if (((param_1[0x5258] == 0) || (iVar7 = FUN_00819fea(param_1 + 0x5252,0), iVar7 != 0)) &&
         (iVar7 = FUN_0081b115(param_1[0x5252],param_1[0x5253],param_1[0x5254],param_1[0x5255]),
         iVar7 != 0)) {
        param_1[0x5258] = iVar7;
      }
      local_10 = (int *)((int)local_10 + 1);
    } while ((int)local_10 < param_3);
  }
  local_8 = 0.0;
  if (0 < param_1[0x5213]) {
    piVar9 = param_1 + 0x5011;
    do {
      iVar7 = *piVar9;
      if (*(int *)(iVar7 + 0x138) == 0) {
        puVar11 = (undefined4 *)(iVar7 + 0x264);
        puVar13 = (undefined4 *)(iVar7 + 0x224);
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          *puVar13 = *puVar11;
          puVar11 = puVar11 + 1;
          puVar13 = puVar13 + 1;
        }
      }
      local_8 = (float)((int)local_8 + 1);
      piVar9 = piVar9 + 1;
    } while ((int)local_8 < param_1[0x5213]);
  }
  *param_1 = 0;
  if ((param_1[0x525f] == 0) && (*(char *)((int)param_1 + 0x14fe9) == '\0')) {
    FUN_0081cd76();
  }
  if (0 < DAT_014a0984) {
    DAT_014a0984 = DAT_014a0984 + -1;
  }
  return;
}


/* ---- FUN_0081e642 @ 0081e642 ---- */

void FUN_0081e642(undefined4 param_1,undefined4 param_2)

{
  FUN_0081ae3b();
  FUN_0081da41(param_1,param_2,0);
  FUN_0081da41(param_1,param_2,1);
  return;
}


/* ---- FUN_0081e670 @ 0081e670 ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0081e670(int param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined *puVar5;
  int in_EAX;
  int iVar6;
  int iVar7;
  int *piVar8;
  float10 fVar9;
  int local_18;
  int local_c;
  int local_8;
  
  piVar8 = (int *)(*(int *)(in_EAX + 4) + 0xc + in_EAX);
  iVar1 = *piVar8;
  FUN_00807fd6();
  local_8 = 0;
  if (0 < iVar1) {
    piVar8 = piVar8 + 2;
    do {
      iVar7 = 0x10000;
      if (piVar8[1] - *piVar8 < 0x10000) {
        iVar7 = piVar8[1] - *piVar8;
      }
      fVar9 = (float10)FUN_008056db(_DAT_0081fd30,
                                    (double)((float)(int)*(char *)((int)piVar8 + -2) * _DAT_0081fd28
                                            * _DAT_0081fd44));
      FUN_00807f11();
      FUN_00807d71(&DAT_014a09a8,iVar7);
      puVar5 = PTR_DAT_0083f808;
      fVar4 = _DAT_0081fc98;
      fVar3 = _DAT_0081f2c4;
      iVar6 = 0;
      local_c = iVar7;
      if (0 < iVar7) {
        do {
          fVar2 = (float)fVar9;
          if (iVar6 < 1000) {
            fVar2 = (float)iVar6 * (float)fVar9 * fVar3;
          }
          if (iVar7 + -1000 < iVar6) {
            fVar2 = (float)local_c * fVar2 * fVar3;
          }
          local_18 = (int)(longlong)ROUND(fVar2 * *(float *)(&DAT_014a09a8 + iVar6 * 4) * fVar4);
          if (local_18 < 0x7fff) {
            if (local_18 < -0x7ffe) {
              local_18 = -0x7fff;
            }
          }
          else {
            local_18 = 0x7fff;
          }
          *(short *)(puVar5 + iVar6 * 4) = (short)local_18;
          local_18 = (int)(longlong)ROUND(fVar2 * *(float *)(&DAT_014a09ac + iVar6 * 4) * fVar4);
          if (local_18 < 0x7fff) {
            if (local_18 < -0x7ffe) {
              local_18 = -0x7fff;
            }
          }
          else {
            local_18 = 0x7fff;
          }
          iVar6 = iVar6 + 1;
          *(short *)(puVar5 + iVar6 * 4 + -2) = (short)local_18;
          local_c = local_c + -1;
        } while (iVar6 < iVar7);
      }
      FUN_00801e27(puVar5,iVar7,4,*(undefined1 *)((int)piVar8 + -3));
      FUN_008040d8(*(int *)(param_1 + 0x14) + local_8,*(int *)(param_1 + 0x14) + iVar1);
      piVar8 = piVar8 + 4;
      local_8 = local_8 + 1;
    } while (local_8 < iVar1);
  }
  FUN_00807ef2();
  return;
}


/* ---- FUN_0081e80f @ 0081e80f ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0081e80f(undefined2 *param_1,int param_2)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int local_10;
  
  DAT_015289a8 = DAT_015289a8 + param_2;
  for (; 0 < param_2; param_2 = param_2 - iVar3) {
    iVar3 = 0x1000;
    if (param_2 < 0x1001) {
      iVar3 = param_2;
    }
    FUN_00807d71(&DAT_015209a8,iVar3);
    iVar1 = iVar3 * 2;
    pfVar2 = (float *)&DAT_015209a8;
    if (0 < iVar1) {
      do {
        local_10 = (int)(longlong)ROUND(*pfVar2 * _DAT_0081fc98);
        if (local_10 < 0x7fff) {
          if (local_10 < -0x7ffe) {
            local_10 = -0x7fff;
          }
        }
        else {
          local_10 = 0x7fff;
        }
        *param_1 = (short)local_10;
        param_1 = param_1 + 1;
        pfVar2 = pfVar2 + 1;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
  }
  if (0x619283 < DAT_015289a8) {
    FUN_00807fd6(*DAT_014a099c,0xac44);
    FUN_00807f11(0);
    DAT_015289a8 = 0;
  }
  return;
}


/* ---- FUN_0081e8cb @ 0081e8cb ---- */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0081e8cb(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 local_3c [28];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  undefined *local_8;
  
  if (param_1 == 2) {
    local_8 = &DebugData_kx;
    DAT_014a099c = (undefined4 *)operator_new(0x40);
    FUN_0081859c(&local_8);
    iVar1 = operator_new(0x958c);
    if (iVar1 == 0) {
      DAT_014a098c = 0;
    }
    else {
      DAT_014a098c = FUN_008197eb();
    }
    DAT_014a09a4 = 0;
    FUN_0080607a();
    FUN_0081511e();
    DAT_014a0998 = operator_new(0x15548);
    FUN_0081bec3();
    FUN_00801c05();
    *(undefined4 **)(DAT_014a098c + 0x1350) = DAT_014a099c + 0xc;
    *(undefined4 *)(DAT_014a098c + 0x1354) = DAT_014a099c[0xd];
    *(undefined4 *)(DAT_014a098c + 0x1358) = DAT_014a0998;
    FUN_00817f4d();
    FUN_00818ec0(0,0);
    FUN_00819016(DAT_014a098c);
    FUN_00817fba();
    iVar1 = operator_new(0x237c);
    if (iVar1 == 0) {
      DAT_014a09a4 = 0;
    }
    else {
      DAT_014a09a4 = FUN_00807492();
    }
    FUN_0081e670(DAT_014a099c);
    FUN_00807fd6(*DAT_014a099c,0xac44);
    FUN_00807f11(0);
    FUN_00801dea(0,0x40,0);
    local_1c = 0;
    local_18 = 0;
    local_14 = 0;
    local_10 = 0;
    DAT_014a0990 = DAT_014a099c[5] * 0x98 + -0x98 + DAT_014a099c[4];
    FUN_0081e642(DAT_014a0990,DAT_014a098c);
    FUN_0081cb71(local_1c,local_18,local_14,local_10,0,0);
    _DAT_015289bc = FUN_00801c05();
    _DAT_015289b4 = 0.0;
    DAT_015289b0 = 0;
  }
  else if (param_1 == 3) {
    FUN_0081daae(param_2);
  }
  else if (param_1 == 6) {
    iVar1 = FUN_00801c05();
    DAT_015289b8 = iVar1 - _DAT_015289bc;
    FUN_00818ec0((int)(((longlong)DAT_015289b8 * 0x760000) / 60000),DAT_015289b8);
    FUN_00818ba7(DAT_014a098c);
    FUN_0081af9e(DAT_014a098c);
    FUN_0081b0f1();
    FUN_008023a5(0);
    local_20 = 0;
    FUN_00801037(local_3c);
    FUN_008012d2();
    FUN_0080221c();
    FUN_00819e7b(DAT_014a098c + 0x135c);
    *(undefined4 *)(DAT_014a098c + 0x14bc) = _DAT_0081f108;
    FUN_0081429e();
    *(undefined1 *)(DAT_0140e128 + 0x185c) = 1;
    *(undefined4 *)(DAT_0140e128 + 0x1864) = DAT_014a0998;
    FUN_00818d42(DAT_014a098c);
    uVar5 = 0x3f800000;
    uVar4 = 0xffffffff;
    uVar3 = 0;
    uVar2 = FUN_008142e1(0,4,1);
    FUN_00814e2f(*(undefined4 *)(DAT_0140e128 + 0xe4),uVar2,uVar3,uVar4,uVar5);
    *(undefined1 *)(DAT_0140e128 + 0x185c) = 0;
    FUN_0081429e();
    FUN_00817fba();
    FUN_0080577f();
    local_c = DAT_015289b8 - DAT_015289b0;
    DAT_015289ac = DAT_015289ac + 1;
    _DAT_014a0994 = (_DAT_0081fc24 / (float)local_c - _DAT_015289b4) * _DAT_0081fcc8 + _DAT_015289b4
    ;
    if (DAT_015289ac == 0x10) {
      DAT_015289ac = 0;
    }
    iVar1 = DAT_015289b8 / 10 - DAT_015289b0 / 10;
    if (10 < iVar1) {
      iVar1 = 10;
    }
    _DAT_015289b4 = _DAT_014a0994;
    FUN_0081dd4c(DAT_014a098c,iVar1);
    DAT_015289b0 = DAT_015289b8;
  }
  return 1;
}


