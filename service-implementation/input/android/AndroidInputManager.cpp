#include "AndroidInputManager.hpp"
#include "AndroidOut.h"
#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <cassert>

AndroidInputManager::AndroidInputManager(android_app* pApp) : m_pApp(pApp) {}

AndroidInputManager::~AndroidInputManager() {}

void AndroidInputManager::pollEvents() {
    assert(m_pInputListener != nullptr);

  // handle all queued inputs
  for (auto i = 0; i < m_pApp->motionEventsCount; i++) {
    // cache the current event
    auto& motionEvent = m_pApp->motionEvents[i];

    // cache the current action
    auto action = motionEvent.action;

    // Find the pointer index, mask and bitshift to turn it into a readable
    // value
    auto pointerIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >>
                        AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
    aout << "Pointer " << pointerIndex << ":";

    // get the x and y position of this event
    auto& pointer = motionEvent.pointers[pointerIndex];
    auto x = GameActivityPointerAxes_getX(&pointer);
    auto y = GameActivityPointerAxes_getY(&pointer);
    aout << "(" << x << ", " << y << ") ";

    // Only consider touchscreen events, like touches
    auto actionMasked = action & AINPUT_SOURCE_TOUCHSCREEN;

    // determine the kind of event it is
    switch (actionMasked) {
      case AMOTION_EVENT_ACTION_DOWN:
      case AMOTION_EVENT_ACTION_POINTER_DOWN:
        aout << "Pointer Down";
        m_pInputListener->onMousePressed(x, y);
        break;

      case AMOTION_EVENT_ACTION_UP:
      case AMOTION_EVENT_ACTION_POINTER_UP:
        aout << "Pointer Up";
        m_pInputListener->onMouseReleased(x, y);
        break;

      default:
        aout << "Pointer Move";
        m_pInputListener->onMouseMoved(x, y);
    }

    aout << std::endl;
  }

  // clear inputs, be careful as this will clear it for anyone listening to
  // these events
  android_app_clear_motion_events(m_pApp);
}
