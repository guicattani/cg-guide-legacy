#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

#ifndef CLASS_HEADER_BEZIER
#define CLASS_HEADER_BEZIER
#include "bezier.h"
#endif

void InterfaceScene4::ShowControls()
{
  ImGui::SliderFloat3("A", (float *)&g_Scene4->a, -3.0f, 3.0f);
  ImGui::SliderFloat3("B", (float *)&g_Scene4->b, -3.0f, 3.0f);
  ImGui::SliderFloat3("C", (float *)&g_Scene4->c, -3.0f, 3.0f);
  ImGui::SliderFloat3("D", (float *)&g_Scene4->d, -3.0f, 3.0f);

  ImGui::Separator();

  ImGui::Checkbox("Hold time", &g_HoldTime);

  ImVec4 pink(1.00f, 0.00f, 0.75f, 1.0f), cyan(0.00f, 0.75f, 1.00f, 1.0f);
  struct Funcs
    {
        static float Sin(void*, int i) { return -1.0f + 2.0f * sinf(i * 0.01f); }
        static float BezierX(void*, int i) {
          return bezier3(i * 0.01f, g_Scene4->a, g_Scene4->b, g_Scene4->c, g_Scene4->d).x;
        }
        static float BezierY(void*, int i) {
          return bezier3(i * 0.01f, g_Scene4->a, g_Scene4->b, g_Scene4->c, g_Scene4->d).y;
        }
        static float BezierZ(void*, int i) {
          return bezier3(i * 0.01f, g_Scene4->a, g_Scene4->b, g_Scene4->c, g_Scene4->d).z;
        }
    };

  if (g_Scene4->a != g_Scene4->aMonitor ||
      g_Scene4->b != g_Scene4->bMonitor ||
      g_Scene4->c != g_Scene4->cMonitor ||
      g_Scene4->d != g_Scene4->dMonitor ) {

      g_Scene4->graphMinMax.x = MinMax{100.0f, -100.0f};
      g_Scene4->graphMinMax.y = MinMax{100.0f, -100.0f};
      g_Scene4->graphMinMax.z = MinMax{100.0f, -100.0f};
      bezier3MinMax(&g_Scene4->graphMinMax, g_Scene4->a, g_Scene4->b, g_Scene4->c, g_Scene4->d);
  }

  g_Scene4->aMonitor = g_Scene4->a;
  g_Scene4->bMonitor = g_Scene4->b;
  g_Scene4->cMonitor = g_Scene4->c;
  g_Scene4->dMonitor = g_Scene4->d;

  ImGui::Text("Min Max X: %f %f", (float) g_Scene4->graphMinMax.x.min, (float) g_Scene4->graphMinMax.x.max);
  ImGui::Text("Min Max Y: %f %f", (float) g_Scene4->graphMinMax.y.min, (float) g_Scene4->graphMinMax.y.max);
  ImGui::Text("Min Max Z: %f %f", (float) g_Scene4->graphMinMax.z.min, (float) g_Scene4->graphMinMax.z.max);

  ImGui::PlotVar("s = f(t)", g_Scene4->t, g_HoldTime, 0.0f, 1.0f);
  ImGui::SameLine();
  ImGui::HelpMarker("f(t) = 0.5 * sin(3.14 * (t - 0.5)) + 0.5");
  ImGui::PlotLinesWithIndicator("BezierX(s)", Funcs::BezierX, NULL, 100, 0, NULL, g_Scene4->graphMinMax.x.min, g_Scene4->graphMinMax.x.max, ImVec2(200,80), g_Scene4->t);
  ImGui::PlotLinesWithIndicator("BezierY(s)", Funcs::BezierY, NULL, 100, 0, NULL, g_Scene4->graphMinMax.y.min, g_Scene4->graphMinMax.y.max, ImVec2(200,80), g_Scene4->t);
  ImGui::PlotLinesWithIndicator("BezierZ(s)", Funcs::BezierZ, NULL, 100, 0, NULL, g_Scene4->graphMinMax.z.min, g_Scene4->graphMinMax.z.max, ImVec2(200,80), g_Scene4->t);


  ImGui::Separator();

  ImGui::Text("Camera");
  ImGui::Text("Position: %f %f %f %f", (float) g_Scene4->camera->position[0],
                                       (float) g_Scene4->camera->position[1],
                                       (float) g_Scene4->camera->position[2],
                                       (float) g_Scene4->camera->position[3]);
  ImGui::Text("Theta: %f", (float) g_Scene4->camera->theta);
  ImGui::Text("Phi: %f", (float) g_Scene4->camera->phi);
}

void InterfaceScene4::ShowText()
{
  ImGui::TextWrapped("This text should automatically wrap on the edge of the window. The current implementation for text wrapping follows simple rules suitable for English and possibly other languages.");

}