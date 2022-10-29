#include "PulseProcTzx.h"
#include <cstring>

PulseProcTzx::PulseProcTzx(
  PulseProcTap* ppTap,
  PulseProcStdHeader* header,
  PulseProcStdByteStream* data,
  PulseProcTone* end,
  PulseProcPauseMillis* pause
) :
  _pptBlock(ppTap, header, data, end, pause),
  _tsPerMs(0)
{}
  
void PulseProcTzx::init(
    PulseProc *nxt,
    uint32_t tsPerMs
) {
  next(nxt);
  _tsPerMs = tsPerMs;
}

int32_t PulseProcTzx::advance(
  InputStream *is,
  bool *pstate,
  PulseProc **top
) {
  DBG_PULSE("PulseProcTzx: Loading TZX\n");

  _pptHeader.init(&_pptIndex);
  _pptIndex.init(&_pptBlock, &_bi);
  _pptBlock.init(next(), &_bi, _tsPerMs);
  *top = &_pptHeader;
  
  return PP_CONTINUE;
}
