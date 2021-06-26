#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

void InterfaceScene1::Part1::ShowControls()
{
  ImGui::TextColored(ImVec4(1.0f,1.0f,1.0f,1.0f), "See details first!");
}

void InterfaceScene1::Part1::ShowText() {
  ImGui::TextColored(ImVec4(0.0f,1.0f,1.0f,1.0f), "Drawing your first triangle");
  const std::string markdownText  = u8R"(
    Test
    )";
   ImGuiMarkdown::Markdown(markdownText);
   ImGui::SameLine();

  if (ImGui::Button(">>"))
  {
    g_Scene1->current_part = 2;
  }
}

void InterfaceScene1::ShowControls()
{
  ImGui::ColorEdit3("First vertex Color",  (float *)&g_Scene1->first_vertex_color);
  ImGui::ColorEdit3("Second vertex Color", (float *)&g_Scene1->second_vertex_color);
  ImGui::ColorEdit3("Third vertex Color",  (float *)&g_Scene1->third_vertex_color);
}

void InterfaceScene1::ShowText() {
  ImGui::TextColored(ImVec4(0.0f,1.0f,1.0f,1.0f), "Drawing your first triangle");
  const std::string markdownText  = u8R"(
    hello ~test~ HELLOO
    hi ~test~ hi
    HELLOO     ~test~ aaaaaaaaaaaaaaaaaaaaaaaaHELLOO
    ~test~
    # H1 Header: Text and Links
    You can add [links like this one to enkisoftware](https://www.enkisoftware.com/) and lines will wrap well.
    You can also insert images ![Mars](mars)
    Horizontal rules:
    ***
    ___
    *Emphasis* and **strong emphasis** change the appearance of the text.
    ## H2 Header: indented text.
      This text has an indent (two leading spaces).
        This one has two.
    ### H3 Header: Lists
      * Unordered lists
        * Lists can be indented with two extra spaces.
      * Lists can have [links like this one to Avoyd](https://www.avoyd.com/) and *emphasized text*
    )";
   ImGuiMarkdown::Markdown(markdownText);

  if (ImGui::Button("<<"))
  {
    g_Scene1->current_part = 1;
  }
}
