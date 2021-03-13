/*
 * ModelPID.cpp
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

/* Block signals (default storage) */
B_ModelPID_T ModelPID_B;

/* Block states (default storage) */
DW_ModelPID_T ModelPID_DW;

/* External inputs (root inport signals with default storage) */
ExtU_ModelPID_T ModelPID_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_ModelPID_T ModelPID_Y;

/* Real-time model */
RT_MODEL_ModelPID_T ModelPID_M_;
RT_MODEL_ModelPID_T *const ModelPID_M = &ModelPID_M_;

/* Model step function */
void ModelPID_step(void)
{
  real_T rtb_FilterCoefficient;
  real_T u0;

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/processValue'
   *  Inport: '<Root>/setpoint'
   */
  ModelPID_B.sig_sum = ModelPID_U.setpoint - ModelPID_U.processValue;

  /* Gain: '<S66>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S38>/Filter'
   *  Gain: '<S33>/Derivative Gain'
   *  Sum: '<S38>/SumD'
   */
  rtb_FilterCoefficient = (ModelPID_P.PIDController_D * ModelPID_B.sig_sum -
    ModelPID_DW.Filter_DSTATE) * ModelPID_P.PIDController_N;

  /* Sum: '<S86>/Sum' incorporates:
   *  DiscreteIntegrator: '<S56>/Integrator'
   *  Gain: '<S73>/Proportional Gain'
   */
  u0 = (ModelPID_P.PIDController_P * ModelPID_B.sig_sum +
        ModelPID_DW.Integrator_DSTATE) + rtb_FilterCoefficient;

  /* Saturate: '<S77>/Saturation' */
  if (u0 > ModelPID_P.PIDController_UpperSaturationLimit) {
    ModelPID_B.outpid = ModelPID_P.PIDController_UpperSaturationLimit;
  } else if (u0 < ModelPID_P.PIDController_LowerSaturationLimit) {
    ModelPID_B.outpid = ModelPID_P.PIDController_LowerSaturationLimit;
  } else {
    ModelPID_B.outpid = u0;
  }

  /* End of Saturate: '<S77>/Saturation' */

  /* Outport: '<Root>/outPID' */
  ModelPID_Y.outPID = ModelPID_B.outpid;

  /* Gain: '<Root>/Gain' incorporates:
   *  Inport: '<Root>/setpoint'
   */
  ModelPID_B.setpoint = ModelPID_P.Gain_Gain * ModelPID_U.setpoint;

  /* Gain: '<Root>/Gain1' incorporates:
   *  Inport: '<Root>/processValue'
   */
  ModelPID_B.processval = ModelPID_P.Gain1_Gain * ModelPID_U.processValue;

  /* Update for DiscreteIntegrator: '<S56>/Integrator' incorporates:
   *  Gain: '<S46>/Integral Gain'
   */
  ModelPID_DW.Integrator_DSTATE += ModelPID_P.PIDController_I *
    ModelPID_B.sig_sum * ModelPID_P.Integrator_gainval;

  /* Update for DiscreteIntegrator: '<S38>/Filter' */
  ModelPID_DW.Filter_DSTATE += ModelPID_P.Filter_gainval * rtb_FilterCoefficient;
}

/* Model initialize function */
void ModelPID_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(ModelPID_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &ModelPID_B), 0,
                sizeof(B_ModelPID_T));

  /* states (dwork) */
  (void) memset((void *)&ModelPID_DW, 0,
                sizeof(DW_ModelPID_T));

  /* external inputs */
  (void)memset(&ModelPID_U, 0, sizeof(ExtU_ModelPID_T));

  /* external outputs */
  ModelPID_Y.outPID = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S56>/Integrator' */
  ModelPID_DW.Integrator_DSTATE =
    ModelPID_P.PIDController_InitialConditionForIntegrator;

  /* InitializeConditions for DiscreteIntegrator: '<S38>/Filter' */
  ModelPID_DW.Filter_DSTATE = ModelPID_P.PIDController_InitialConditionForFilter;
}

/* Model terminate function */
void ModelPID_terminate(void)
{
  /* (no terminate code required) */
}
