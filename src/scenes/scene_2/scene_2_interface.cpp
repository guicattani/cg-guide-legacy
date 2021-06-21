#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

void InterfaceScene2::ShowControls()
{
  ImGui::Text("This is a text specific of Scene 2");
}

void InterfaceScene2::ShowText() {
  ImGui::TextWrapped("This text should automatically wrap on the edge of the window. The current implementation for text wrapping follows simple rules suitable for English and possibly other languages.");

}
