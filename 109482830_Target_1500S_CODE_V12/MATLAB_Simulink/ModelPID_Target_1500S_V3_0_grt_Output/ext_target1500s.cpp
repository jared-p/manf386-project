#include <stddef.h>
#include "rtwtypes.h"
#include "ext_work.h"
#include "ext_svr.h"
#include "ext_target1500s.h"
#include "rtiostream_target1500s.h"
#include "ModelPID.h"
#include "ODK_Types.h"
#include "ODK_Functions.h"
#include "updown_util.h"

extern int_T volatile startModel;
extern TargetSimStatus volatile modelStatus;
int ExtModeBusy = 0;
enum ExtModeStates{
  ST_IDLE,
  ST_RECEIVE,
  ST_SEND,
  ST_DISCON,
  ST_DISCON_GRACEFULL
};

extern "C" {
  extern boolean_T HasError;
  extern void freeMemory();
}
  void waitForStartIfNecessary()
{
  if (ExtWaitForStartPkt() && !startModel) {
    rtExtModeOneStep(,1,(boolean_T *)&rtmGetStopRequested(ModelPID_M));
    if (!startModel) {
      return;
    }
  }

  if (modelStatus != TARGET_STATUS_PAUSED) {
    modelStatus = TARGET_STATUS_RUNNING;
  }
}

void pauseExternalMode()
{
  if (!startModel) {
    rtExtModeOneStep(,1,(boolean_T *)&rtmGetStopRequested(ModelPID_M));
  }
}

void ModelPID_initialize_ext()
{
  freeMemory();
  ModelPID_initialize();
  rtParseArgsForExtMode(SIMULINK_STREAM, NULL);
  rtSetTFinalForExtMode(&rtmGetTFinal(ModelPID_M));
  rtExtModeCheckInit(1);
}

void ModelPID_terminate_ext(bool resetBuffer)
{
  rtExtModeShutdown(1);
  ModelPID_terminate();
  if (resetBuffer) {
    rtIOStreamClose(ODK1500S_STREAM);
  }
}

boolean_T extModeStep()
{
  if ((rtmGetErrorStatus(ModelPID_M) == (NULL)) && !rtmGetStopRequested
      (ModelPID_M)) {
    rtExtModeOneStep(,1,(boolean_T *)&rtmGetStopRequested(ModelPID_M));
    if (ExtModeBusy > 10) {
      return true;
    }

    ModelPID_step();
  } else if (rtmGetErrorStatus(ModelPID_M)) {
    ODK_TRACE("%s",rtmGetErrorStatus(ModelPID_M));
    return false;
  } else {
    ODK_TRACE("Stop Requested");
    return false;
  }

  rtExtModeCheckEndTrigger();
  return true;
}

bool ModelPID_step_ext()
{
  switch (modelStatus) {
   case TARGET_STATUS_WAITING_TO_START:
    waitForStartIfNecessary();
    return true;

   case TARGET_STATUS_PAUSED:
    pauseExternalMode();
    return true;

   case TARGET_STATUS_RUNNING:
    startModel = false;
    return extModeStep();

   default:
    return true;
  }
}

bool modelTransfer(                    /*IN*/
                   const ODK_UINT32& receiveLength,/*OUT*/
                   ODK_UINT32& sendLength,/*INOUT*/
                   ODK_BYTE bufferToModel[65536],/*INOUT*/
                   ODK_BYTE bufferFromModel[65536])
{
  ODK_BYTE* dbToModel = &bufferToModel[0];
  ODK_BYTE* dbFromModel = &bufferFromModel[0];
  int sendResult = 0;
  int streamID = ODK1500S_STREAM;
  if (receiveLength > 0) {
    size_t bytesTransferred = 0;
    sendResult = rtIOStreamSend(streamID, dbToModel, receiveLength,
      &bytesTransferred);
  }

  if (sendResult == -1) {
    return false;
  }

  size_t sizeRead = 0;
  rtIOStreamRecv(streamID,
                 dbFromModel, 0x10000,&sizeRead);
  sendLength = sizeRead;
  return true;
}

void setError(ODK_BOOL& funcError,     /*OUT*/
              ODK_WORD& funcStatus,ODK_UINT32& stateOut)
{
  funcStatus = 1;
  funcError = true;
  stateOut = ST_DISCON_GRACEFULL;
}

_ODK_FUNCTION_EXTMODEINTERNAL {
  funcStatus = 0;
  funcError = false;
  stateOut = stateIn;
  if (HasError) {                      //Memory Error
    setError(funcError,funcStatus,stateOut);
    return ODK_SUCCESS;
  }

  if (rtmGetErrorStatus(ModelPID_M) != (NULL)) {
    setError(funcError,funcStatus,stateOut);
    return ODK_SUCCESS;
  }

  switch (stateIn){
   case ST_SEND:
    ExtModeBusy++;
    break;

   case ST_RECEIVE:
    if (!modelTransfer(receiveLength,sendLength,bufferToModel,bufferFromModel))
    {
      setError(funcError,funcStatus,stateOut);
    } else {
      stateOut = (sendLength > 0) ? ST_SEND: ST_RECEIVE;
    }

    ExtModeBusy = 0;
    break;

   default:
    ExtModeBusy = 0;
  }

  return ODK_SUCCESS;
}
