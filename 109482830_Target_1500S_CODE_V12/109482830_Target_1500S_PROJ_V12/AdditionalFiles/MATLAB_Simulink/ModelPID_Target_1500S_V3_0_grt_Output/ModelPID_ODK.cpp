/*
 * This file was generated using "SIMATIC Target 1500S for Simulink"
 * Target Language Compiler provided by Siemens AG.
 *
 * Simulink model name          : ModelPID
 * Model version                : 1.162
 *
 * File name                    : ModelPID_ODK.cpp
 * File creation date           : 2019-05-28 16:36:14
 *
 * Target 1500S version         : V3.0
 * Simulink system target file  : Target_1500S_V3_0_grt.tlc
 *
 * ODK 1500S version            : V2.5
 *
 * MATLAB version               : 9.5 (R2018b) 24-May-2018
 * MATLAB Coder version         : 4.1 (R2018b) 24-May-2018
 * Simulink version             : 9.2 (R2018b) 24-May-2018
 * Simulink Coder version       : 9.0 (R2018b) 24-May-2018
 *
 */

#include <stddef.h>
#include "ODK_Functions.h"
#include "ODK_CpuReadWriteData.h"
#include "rtwtypes.h"
#include "ModelPID.h"
#include "ModelPID_private.h"
#include "Target_Params.h"
#include <vector>

boolean_T initialized = false;
boolean_T terminated = false;
RWLock *rw_lock = NULL;
void modelTerminate()
{
  if (terminated) {
    return;
  }

  terminated = true;
  initialized = false;
  ModelPID_terminate();
  if (rw_lock != NULL)
    delete(rw_lock);
}

void modelInitialize()
{
  if (initialized) {
    return;
  }

  ModelPID_initialize();
  initialized = true;
  terminated = false;
}

/*
 * OnLoad() is invoked after the application binary was loaded.
 * @return ODK_SUCCESS       notify, that no error occurs
 *                            - OnRun() will be invoked automatically
 *         any other value   notify, that an error occurs (user defined)
 *                            - OnUnload() will be invoked automatically
 *                            - ODK application will be unloaded automatically
 */
EXPORT_API ODK_RESULT OnLoad(void)
{
  modelInitialize();
  return ODK_SUCCESS;
}

/*
 * OnUnload() is invoked before the application binary is unloaded or when
 *            ODK-Host terminates.
 * @return ODK_SUCCESS       notify, that no error occurs
 *         any other value   notify, that an error occurs (user defined)
 *                            - ODK application will be unloaded anyway
 */
EXPORT_API ODK_RESULT OnUnload(void)
{
  // place your code here
  modelTerminate();
  return ODK_SUCCESS;
}

/*
 * OnRun() is invoked when the CPU transitions to the RUN state and
 *         after OnLoad().
 * @return Does not affect the load operation or state transition.
 */
EXPORT_API ODK_RESULT OnRun(void)
{
  // place your code here
  modelInitialize();
  return ODK_SUCCESS;
}

/*
 * OnStop() is invoked when the CPU transitions to the STOP/SHUTDOWN state
 *          or before unloading the ODK application.
 * In case of a CPU transition RUN->STOP this function will be canceled,
 * when execution overruns a reaction time of more than ~20ms.
 * @return Does not affect the load operation or state transition.
 */
EXPORT_API ODK_RESULT OnStop(void)
{
  modelTerminate();
  return ODK_SUCCESS;
}

/*
 * main() is defined for windows debugging, only.
 * Therefore all automatically invoked functions (OnLoad, OnRun, OnStop, OnUnload)
 * have to be called manually.
 */
#ifdef _DEBUG

int main (int argc, char* argv[])
{
  ODK_RESULT ret = ODK_SUCCESS;
  ret = OnLoad();

  // error handling
  ret = OnRun();

  // error handling

  // place your test code here
  ret = OnStop();

  // error handling
  ret = OnUnload();

  // error handling
  return ret;
}

#endif                                 // _DEBUG

_ODK_FUNCTION_ONESTEP {
  ModelPID_U.setpoint = setpoint;
  ModelPID_U.processValue = processValue;
  if (rw_lock != NULL)
    rw_lock->RdLock();
  ModelPID_step();
  if (rw_lock != NULL)
    rw_lock->RdUnlock();
  outPID = ModelPID_Y.outPID;
  internalSignals.sig_sum = ModelPID_B.sig_sum;
  internalSignals.outpid = ModelPID_B.outpid;
  internalSignals.setpoint = ModelPID_B.setpoint;
  internalSignals.processval = ModelPID_B.processval;
  return ODK_SUCCESS;
}
  _ODK_FUNCTION_READWRITEPARAMETERS
{
  if (rw_lock == NULL)
    rw_lock = new RWLock();
  if (!write) {
    rw_lock->RdLock();
    inOutParams.ModelPID_PIDController_D = ModelPID_P.PIDController_D;
    inOutParams.ModelPID_PIDController_I = ModelPID_P.PIDController_I;
    inOutParams.ModelPID_PIDController_InitialConditionForFilter =
      ModelPID_P.PIDController_InitialConditionForFilter;
    inOutParams.ModelPID_PIDController_InitialConditionForIntegrator =
      ModelPID_P.PIDController_InitialConditionForIntegrator;
    inOutParams.ModelPID_PIDController_LowerSaturationLimit =
      ModelPID_P.PIDController_LowerSaturationLimit;
    inOutParams.ModelPID_PIDController_N = ModelPID_P.PIDController_N;
    inOutParams.ModelPID_PIDController_P = ModelPID_P.PIDController_P;
    inOutParams.ModelPID_PIDController_UpperSaturationLimit =
      ModelPID_P.PIDController_UpperSaturationLimit;
    inOutParams.ModelPID_Integrator_gainval = ModelPID_P.Integrator_gainval;
    inOutParams.ModelPID_Filter_gainval = ModelPID_P.Filter_gainval;
    inOutParams.ModelPID_Gain_Gain = ModelPID_P.Gain_Gain;
    inOutParams.ModelPID_Gain1_Gain = ModelPID_P.Gain1_Gain;
    rw_lock->RdUnlock();
    return ODK_SUCCESS;
  }

  // Check which members will be updated
  std::vector<UpdatedParam> v;
  rw_lock->RdLock();
  if (ModelPID_P.PIDController_D != inOutParams.ModelPID_PIDController_D)
    v.push_back( UpdatedParam(&(ModelPID_P.PIDController_D),
      inOutParams.ModelPID_PIDController_D) );
  if (ModelPID_P.PIDController_I != inOutParams.ModelPID_PIDController_I)
    v.push_back( UpdatedParam(&(ModelPID_P.PIDController_I),
      inOutParams.ModelPID_PIDController_I) );
  if (ModelPID_P.PIDController_InitialConditionForFilter !=
      inOutParams.ModelPID_PIDController_InitialConditionForFilter)
    v.push_back( UpdatedParam
                (&(ModelPID_P.PIDController_InitialConditionForFilter),
                 inOutParams.ModelPID_PIDController_InitialConditionForFilter) );
  if (ModelPID_P.PIDController_InitialConditionForIntegrator !=
      inOutParams.ModelPID_PIDController_InitialConditionForIntegrator)
    v.push_back( UpdatedParam
                (&(ModelPID_P.PIDController_InitialConditionForIntegrator),
                 inOutParams.ModelPID_PIDController_InitialConditionForIntegrator)
                );
  if (ModelPID_P.PIDController_LowerSaturationLimit !=
      inOutParams.ModelPID_PIDController_LowerSaturationLimit)
    v.push_back( UpdatedParam(&(ModelPID_P.PIDController_LowerSaturationLimit),
      inOutParams.ModelPID_PIDController_LowerSaturationLimit) );
  if (ModelPID_P.PIDController_N != inOutParams.ModelPID_PIDController_N)
    v.push_back( UpdatedParam(&(ModelPID_P.PIDController_N),
      inOutParams.ModelPID_PIDController_N) );
  if (ModelPID_P.PIDController_P != inOutParams.ModelPID_PIDController_P)
    v.push_back( UpdatedParam(&(ModelPID_P.PIDController_P),
      inOutParams.ModelPID_PIDController_P) );
  if (ModelPID_P.PIDController_UpperSaturationLimit !=
      inOutParams.ModelPID_PIDController_UpperSaturationLimit)
    v.push_back( UpdatedParam(&(ModelPID_P.PIDController_UpperSaturationLimit),
      inOutParams.ModelPID_PIDController_UpperSaturationLimit) );
  if (ModelPID_P.Integrator_gainval != inOutParams.ModelPID_Integrator_gainval)
    v.push_back( UpdatedParam(&(ModelPID_P.Integrator_gainval),
      inOutParams.ModelPID_Integrator_gainval) );
  if (ModelPID_P.Filter_gainval != inOutParams.ModelPID_Filter_gainval)
    v.push_back( UpdatedParam(&(ModelPID_P.Filter_gainval),
      inOutParams.ModelPID_Filter_gainval) );
  if (ModelPID_P.Gain_Gain != inOutParams.ModelPID_Gain_Gain)
    v.push_back( UpdatedParam(&(ModelPID_P.Gain_Gain),
      inOutParams.ModelPID_Gain_Gain) );
  if (ModelPID_P.Gain1_Gain != inOutParams.ModelPID_Gain1_Gain)
    v.push_back( UpdatedParam(&(ModelPID_P.Gain1_Gain),
      inOutParams.ModelPID_Gain1_Gain) );
  rw_lock->RdUnlock();

  // Write only those to be updated
  if (v.size() > 0) {
    rw_lock->WrLock();
    size_t s = v.size();
    for (size_t i=0;i<s;i++) {
      v[i].AssignValue();
    }

    rw_lock->WrUnlock();
  }

  v.clear();
  return ODK_SUCCESS;
}
