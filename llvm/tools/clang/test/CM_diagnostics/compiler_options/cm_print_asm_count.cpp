#include <cm/cm.h>

#ifdef CM_GENX
#warning CM_GENX defined
#else
#warning CM_GENX not defined
#endif

#ifdef CM_GEN7_5
#warning CM_GEN7_5 defined
#endif

#ifdef CM_GEN8
#warning CM_GEN8 defined
#endif

#ifdef CM_GEN8_5
#warning CM_GEN8_5 defined
#endif

#ifdef CM_GEN9
#warning CM_GEN9 defined
#endif

#ifdef CM_GEN9_5
#warning CM_GEN9_5 defined
#endif

#ifdef CM_GEN10
#warning CM_GEN10 defined
#endif

#ifdef CM_GEN11
#warning CM_GEN11 defined
#endif

_GENX_MAIN_
void test1(SurfaceIndex S, vector<uchar,64> i) {
  vector<uchar,16> v = i.select<16,1>(0)  +
                       i.select<16,1>(16) +
                       i.select<16,1>(32) +
                       i.select<16,1>(48);
  write(S,0,0,v);
}

_GENX_MAIN_
void test2(SurfaceIndex S) {
}

// The Finalizer isn't called as we haven't specified a target so the
// -mCM_print_asm_count option has no effect.
// RUN: %cmc -Qxcm_print_asm_count %w 2>&1 | FileCheck %w 
//
// RUN: %cmc /Qxcm_print_asm_count %w 2>&1 | FileCheck %w 

// CHECK: cm_print_asm_count.cpp(6,2) :  warning: CM_GENX not defined [-W#warnings]
// CHECK: 1 warning generated.
// CHECK-NOT: -platform
// CHECK-NOT: asm_count

// The Finalizer is called as we have specified a target so the -mCM_print_asm_count
// option causes the gen asm instruction counts to be printed
// RUN: %cmc -Qxcm_jit_target=BDW -Qxcm_print_asm_count %w 2>&1 | FileCheck --check-prefix=CHECK-BDW %w
// RUN: rm %W.isa %W_0.visaasm %W_0.asm %W_0.dat %W_1.visaasm %W_1.asm %W_1.dat
//
// RUN: %cmc /Qxcm_jit_target=BDW /Qxcm_print_asm_count %w 2>&1 | FileCheck --check-prefix=CHECK-BDW %w 
// RUN: rm %W.isa %W_0.visaasm %W_0.asm %W_0.dat %W_1.visaasm %W_1.asm %W_1.dat

// CHECK-BDW: cm_print_asm_count.cpp(4,2) :  warning: CM_GENX defined [-W#warnings]
// CHECK-BDW: cm_print_asm_count.cpp(14,2) :  warning: CM_GEN8 defined [-W#warnings]
// CHECK-BDW: 2 warnings generated.
// CHECK-BDW: -platform BDW
// CHECK-BDW: Kernel cm_print_asm_count_0 : {{[0-9]+}} asm_count 
// CHECK-BDW: Kernel cm_print_asm_count_1 : {{[0-9]+}} asm_count 
// CHECK-BDW-NOT: asm_count
