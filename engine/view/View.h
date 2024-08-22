#ifndef View_h
#define View_h

#include "core/StructuralSprite.hpp"
#include "input/InputListener.hpp"

class ViewManager;

class View : public StructuralSprite, public InputListener {
 public:
  View() {};
  virtual ~View() {};

  virtual void initialize(ViewManager* pViewManager) = 0;
  virtual void onEnter(void* param) {};
};

#endif /* View_h */
