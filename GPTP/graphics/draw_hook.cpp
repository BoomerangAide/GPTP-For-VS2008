#include "draw_hook.h"
#include "../SCBW/api.h"
#include "../hook_tools.h"
#include "graphics_misc.h"

namespace {

//-------- Draw hook taken from BWAPI --------//
bool wantRefresh = false;
void __stdcall DrawHook(graphics::Bitmap *surface, Bounds *bounds) {
  if (wantRefresh) {
    wantRefresh = false;
    scbw::refreshScreen();
  }

  oldDrawGameProc(surface, bounds);

  //if ( BW::BWDATA::GameScreenBuffer->isValid() )
  //{
  //  unsigned int numShapes = BWAPI::BroodwarImpl.drawShapes();
  //  
  //  if ( numShapes )
  //    wantRefresh = true;
  //}
  if (graphics::drawAllShapes() > 0)
    wantRefresh = true;
}

} //unnamed namespace

namespace hooks {

void injectDrawHook() {
  memoryPatch(0x004BD68D, &DrawHook);
}

} //hooks
