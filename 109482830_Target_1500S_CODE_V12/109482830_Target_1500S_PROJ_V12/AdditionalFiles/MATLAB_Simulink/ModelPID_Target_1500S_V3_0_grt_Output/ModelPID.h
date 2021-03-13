/*
 * ModelPID.h
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

#ifndef RTW_HEADER_ModelPID_h_
#define RTW_HEADER_ModelPID_h_
#include <string.h>
#include <stddef.h>
#ifndef ModelPID_COMMON_INCLUDES_
# define ModelPID_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* ModelPID_COMMON_INCLUDES_ */

#include "ModelPID_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T sig_sum;                      /* '<Root>/Sum' */
  real_T outpid;                       /* '<S77>/Saturation' */
  real_T setpoint;                     /* '<Root>/Gain' */
  real_T processval;                   /* '<Root>/Gain1' */
} B_ModelPID_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S56>/Integrator' */
  real_T Filter_DSTATE;                /* '<S38>/Filter' */
} DW_ModelPID_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T setpoint;                     /* '<Root>/setpoint' */
  real_T processValue;                 /* '<Root>/processValue' */
} ExtU_ModelPID_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T outPID;                       /* '<Root>/outPID' */
} ExtY_ModelPID_T;

/* Parameters (default storage) */
struct P_ModelPID_T_ {
  real_T PIDController_D;              /* Mask Parameter: PIDController_D
                                        * Referenced by: '<S33>/Derivative Gain'
                                        */
  real_T PIDController_I;              /* Mask Parameter: PIDController_I
                                        * Referenced by: '<S46>/Integral Gain'
                                        */
  real_T PIDController_InitialConditionForFilter;/* Mask Parameter: PIDController_InitialConditionForFilter
                                                  * Referenced by: '<S38>/Filter'
                                                  */
  real_T PIDController_InitialConditionForIntegrator;/* Mask Parameter: PIDController_InitialConditionForIntegrator
                                                      * Referenced by: '<S56>/Integrator'
                                                      */
  real_T PIDController_LowerSaturationLimit;/* Mask Parameter: PIDController_LowerSaturationLimit
                                             * Referenced by: '<S77>/Saturation'
                                             */
  real_T PIDController_N;              /* Mask Parameter: PIDController_N
                                        * Referenced by: '<S66>/Filter Coefficient'
                                        */
  real_T PIDController_P;              /* Mask Parameter: PIDController_P
                                        * Referenced by: '<S73>/Proportional Gain'
                                        */
  real_T PIDController_UpperSaturationLimit;/* Mask Parameter: PIDController_UpperSaturationLimit
                                             * Referenced by: '<S77>/Saturation'
                                             */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S56>/Integrator'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S38>/Filter'
                                        */
  real_T Gain_Gain;                    /* Expression: 1
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T Gain1_Gain;                   /* Expression: 1
                                        * Referenced by: '<Root>/Gain1'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_ModelPID_T {
  const char_T *errorStatus;
};

/* Block parameters (default storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_ModelPID_T ModelPID_P;

#ifdef __cplusplus

}
#endif

/* Block signals (default storage) */
extern B_ModelPID_T ModelPID_B;

/* Block states (default storage) */
extern DW_ModelPID_T ModelPID_DW;

#ifdef __cplusplus

extern "C" {

#endif

  /* External inputs (root inport signals with default storage) */
  extern ExtU_ModelPID_T ModelPID_U;

  /* External outputs (root outports fed by signals with default storage) */
  extern ExtY_ModelPID_T ModelPID_Y;

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void ModelPID_initialize(void);
  extern void ModelPID_step(void);
  extern void ModelPID_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_ModelPID_T *const ModelPID_M;

#ifdef __cplusplus

}
#endif

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<Root>/Signal Conversion' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ModelPID'
 * '<S1>'   : 'ModelPID/PIDController'
 * '<S2>'   : 'ModelPID/PIDController/Anti-windup'
 * '<S3>'   : 'ModelPID/PIDController/D Gain'
 * '<S4>'   : 'ModelPID/PIDController/Filter'
 * '<S5>'   : 'ModelPID/PIDController/Filter ICs'
 * '<S6>'   : 'ModelPID/PIDController/I Gain'
 * '<S7>'   : 'ModelPID/PIDController/Ideal P Gain'
 * '<S8>'   : 'ModelPID/PIDController/Ideal P Gain Fdbk'
 * '<S9>'   : 'ModelPID/PIDController/Integrator'
 * '<S10>'  : 'ModelPID/PIDController/Integrator ICs'
 * '<S11>'  : 'ModelPID/PIDController/N Copy'
 * '<S12>'  : 'ModelPID/PIDController/N Gain'
 * '<S13>'  : 'ModelPID/PIDController/P Copy'
 * '<S14>'  : 'ModelPID/PIDController/Parallel P Gain'
 * '<S15>'  : 'ModelPID/PIDController/Reset Signal'
 * '<S16>'  : 'ModelPID/PIDController/Saturation'
 * '<S17>'  : 'ModelPID/PIDController/Saturation Fdbk'
 * '<S18>'  : 'ModelPID/PIDController/Sum'
 * '<S19>'  : 'ModelPID/PIDController/Sum Fdbk'
 * '<S20>'  : 'ModelPID/PIDController/Tracking Mode'
 * '<S21>'  : 'ModelPID/PIDController/Tracking Mode Sum'
 * '<S22>'  : 'ModelPID/PIDController/postSat Signal'
 * '<S23>'  : 'ModelPID/PIDController/preSat Signal'
 * '<S24>'  : 'ModelPID/PIDController/Anti-windup/Back Calculation'
 * '<S25>'  : 'ModelPID/PIDController/Anti-windup/Cont. Clamping Ideal'
 * '<S26>'  : 'ModelPID/PIDController/Anti-windup/Cont. Clamping Parallel'
 * '<S27>'  : 'ModelPID/PIDController/Anti-windup/Disabled'
 * '<S28>'  : 'ModelPID/PIDController/Anti-windup/Disc. Clamping Ideal'
 * '<S29>'  : 'ModelPID/PIDController/Anti-windup/Disc. Clamping Parallel'
 * '<S30>'  : 'ModelPID/PIDController/Anti-windup/Passthrough'
 * '<S31>'  : 'ModelPID/PIDController/D Gain/Disabled'
 * '<S32>'  : 'ModelPID/PIDController/D Gain/External Parameters'
 * '<S33>'  : 'ModelPID/PIDController/D Gain/Internal Parameters'
 * '<S34>'  : 'ModelPID/PIDController/Filter/Cont. Filter'
 * '<S35>'  : 'ModelPID/PIDController/Filter/Differentiator'
 * '<S36>'  : 'ModelPID/PIDController/Filter/Disabled'
 * '<S37>'  : 'ModelPID/PIDController/Filter/Disc. Backward Euler Filter'
 * '<S38>'  : 'ModelPID/PIDController/Filter/Disc. Forward Euler Filter'
 * '<S39>'  : 'ModelPID/PIDController/Filter/Disc. Trapezoidal Filter'
 * '<S40>'  : 'ModelPID/PIDController/Filter ICs/Disabled'
 * '<S41>'  : 'ModelPID/PIDController/Filter ICs/External IC'
 * '<S42>'  : 'ModelPID/PIDController/Filter ICs/Internal IC - Differentiator'
 * '<S43>'  : 'ModelPID/PIDController/Filter ICs/Internal IC - Filter'
 * '<S44>'  : 'ModelPID/PIDController/I Gain/Disabled'
 * '<S45>'  : 'ModelPID/PIDController/I Gain/External Parameters'
 * '<S46>'  : 'ModelPID/PIDController/I Gain/Internal Parameters'
 * '<S47>'  : 'ModelPID/PIDController/Ideal P Gain/External Parameters'
 * '<S48>'  : 'ModelPID/PIDController/Ideal P Gain/Internal Parameters'
 * '<S49>'  : 'ModelPID/PIDController/Ideal P Gain/Passthrough'
 * '<S50>'  : 'ModelPID/PIDController/Ideal P Gain Fdbk/Disabled'
 * '<S51>'  : 'ModelPID/PIDController/Ideal P Gain Fdbk/External Parameters'
 * '<S52>'  : 'ModelPID/PIDController/Ideal P Gain Fdbk/Internal Parameters'
 * '<S53>'  : 'ModelPID/PIDController/Ideal P Gain Fdbk/Passthrough'
 * '<S54>'  : 'ModelPID/PIDController/Integrator/Continuous'
 * '<S55>'  : 'ModelPID/PIDController/Integrator/Disabled'
 * '<S56>'  : 'ModelPID/PIDController/Integrator/Discrete'
 * '<S57>'  : 'ModelPID/PIDController/Integrator ICs/Disabled'
 * '<S58>'  : 'ModelPID/PIDController/Integrator ICs/External IC'
 * '<S59>'  : 'ModelPID/PIDController/Integrator ICs/Internal IC'
 * '<S60>'  : 'ModelPID/PIDController/N Copy/Disabled'
 * '<S61>'  : 'ModelPID/PIDController/N Copy/Disabled wSignal Specification'
 * '<S62>'  : 'ModelPID/PIDController/N Copy/External Parameters'
 * '<S63>'  : 'ModelPID/PIDController/N Copy/Internal Parameters'
 * '<S64>'  : 'ModelPID/PIDController/N Gain/Disabled'
 * '<S65>'  : 'ModelPID/PIDController/N Gain/External Parameters'
 * '<S66>'  : 'ModelPID/PIDController/N Gain/Internal Parameters'
 * '<S67>'  : 'ModelPID/PIDController/N Gain/Passthrough'
 * '<S68>'  : 'ModelPID/PIDController/P Copy/Disabled'
 * '<S69>'  : 'ModelPID/PIDController/P Copy/External Parameters Ideal'
 * '<S70>'  : 'ModelPID/PIDController/P Copy/Internal Parameters Ideal'
 * '<S71>'  : 'ModelPID/PIDController/Parallel P Gain/Disabled'
 * '<S72>'  : 'ModelPID/PIDController/Parallel P Gain/External Parameters'
 * '<S73>'  : 'ModelPID/PIDController/Parallel P Gain/Internal Parameters'
 * '<S74>'  : 'ModelPID/PIDController/Parallel P Gain/Passthrough'
 * '<S75>'  : 'ModelPID/PIDController/Reset Signal/Disabled'
 * '<S76>'  : 'ModelPID/PIDController/Reset Signal/External Reset'
 * '<S77>'  : 'ModelPID/PIDController/Saturation/Enabled'
 * '<S78>'  : 'ModelPID/PIDController/Saturation/Passthrough'
 * '<S79>'  : 'ModelPID/PIDController/Saturation Fdbk/Disabled'
 * '<S80>'  : 'ModelPID/PIDController/Saturation Fdbk/Enabled'
 * '<S81>'  : 'ModelPID/PIDController/Saturation Fdbk/Passthrough'
 * '<S82>'  : 'ModelPID/PIDController/Sum/Passthrough_I'
 * '<S83>'  : 'ModelPID/PIDController/Sum/Passthrough_P'
 * '<S84>'  : 'ModelPID/PIDController/Sum/Sum_PD'
 * '<S85>'  : 'ModelPID/PIDController/Sum/Sum_PI'
 * '<S86>'  : 'ModelPID/PIDController/Sum/Sum_PID'
 * '<S87>'  : 'ModelPID/PIDController/Sum Fdbk/Disabled'
 * '<S88>'  : 'ModelPID/PIDController/Sum Fdbk/Enabled'
 * '<S89>'  : 'ModelPID/PIDController/Sum Fdbk/Passthrough'
 * '<S90>'  : 'ModelPID/PIDController/Tracking Mode/Disabled'
 * '<S91>'  : 'ModelPID/PIDController/Tracking Mode/Enabled'
 * '<S92>'  : 'ModelPID/PIDController/Tracking Mode Sum/Passthrough'
 * '<S93>'  : 'ModelPID/PIDController/Tracking Mode Sum/Tracking Mode'
 * '<S94>'  : 'ModelPID/PIDController/postSat Signal/Feedback_Path'
 * '<S95>'  : 'ModelPID/PIDController/postSat Signal/Forward_Path'
 * '<S96>'  : 'ModelPID/PIDController/preSat Signal/Feedback_Path'
 * '<S97>'  : 'ModelPID/PIDController/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_ModelPID_h_ */
