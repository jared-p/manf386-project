/*
 * ModelPID_data.cpp
 *
 * Sponsored Third Party Support License -- for use only to support
 * products interfaced to MathWorks software under terms specified in your
 * company's restricted use license agreement.
 *
 * Code generation for model "ModelPID".
 *
 * Model version              : 1.162
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C++ source code generated on : Tue May 28 16:36:11 2019
 *
 * Target selection: Target_1500S_V3_0_grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-32 (Windows32)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ModelPID.h"
#include "ModelPID_private.h"

/* Block parameters (default storage) */
P_ModelPID_T ModelPID_P = {
  /* Mask Parameter: PIDController_D
   * Referenced by: '<S33>/Derivative Gain'
   */
  8.5,

  /* Mask Parameter: PIDController_I
   * Referenced by: '<S46>/Integral Gain'
   */
  0.065,

  /* Mask Parameter: PIDController_InitialConditionForFilter
   * Referenced by: '<S38>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditionForIntegrator
   * Referenced by: '<S56>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_LowerSaturationLimit
   * Referenced by: '<S77>/Saturation'
   */
  0.0,

  /* Mask Parameter: PIDController_N
   * Referenced by: '<S66>/Filter Coefficient'
   */
  5.0,

  /* Mask Parameter: PIDController_P
   * Referenced by: '<S73>/Proportional Gain'
   */
  1.9,

  /* Mask Parameter: PIDController_UpperSaturationLimit
   * Referenced by: '<S77>/Saturation'
   */
  100.0,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S56>/Integrator'
   */
  0.1,

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S38>/Filter'
   */
  0.1,

  /* Expression: 1
   * Referenced by: '<Root>/Gain'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<Root>/Gain1'
   */
  1.0
};
