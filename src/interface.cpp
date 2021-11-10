#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

#ifndef CLASS_HEADER_MODEL_LOADER
#define CLASS_HEADER_MODEL_LOADER
#include "model_loader.h"
#endif

#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "initialize_globals.h"
#endif

const glm::vec2 InterfaceScene1::Part1::window_constraints = glm::vec2(500.0f, 350.0f);
const glm::vec2 InterfaceScene1::window_constraints        = glm::vec2(500.0f, 600.0f);

namespace ImGuiMarkdown {
  void LinkCallback( ImGui::MarkdownLinkCallbackData data_ )
  {
      #ifdef _WIN32
        std::string url( data_.link, data_.linkLength );
        if( !data_.isImage )
        {
            ShellExecuteA( NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL );
        }
      #endif
  }

  inline ImGui::MarkdownImageData ImageCallback( ImGui::MarkdownLinkCallbackData data_ )
  {
      std::string filename(data_.link, data_.link + data_.linkLength);
      Image image =  g_Images[filename.c_str()];
      // > C++14 can use ImGui::MarkdownImageData imageData{ true, false, image, ImVec2( 40.0f, 20.0f ) };
      ImGui::MarkdownImageData imageData;
      imageData.isValid =         true;
      imageData.useLinkCallback = false;
      imageData.user_texture_id = (ImTextureID)(intptr_t) image.texture_id;
      imageData.size            = ImVec2( image.size.x , image.size.y );

      // For image resize when available size.x > image width, add
      ImVec2 const contentSize = ImGui::GetContentRegionAvail();
      if( imageData.size.x > contentSize.x )
      {
          float const ratio = imageData.size.y/imageData.size.x;
          imageData.size.x = contentSize.x;
          imageData.size.y = contentSize.x*ratio;
      }

      return imageData;
  }

  void Markdown( const std::string& markdown_ )
  {
      // You can make your own Markdown function with your prefered string container and markdown config.
      // > C++14 can use ImGui::MarkdownConfig mdConfig{ LinkCallback, NULL, ImageCallback, ICON_FA_LINK, { { H1, true }, { H2, true }, { H3, false } }, NULL };
      mdConfig.linkCallback =         LinkCallback;
      mdConfig.tooltipCallback =      NULL;
      mdConfig.imageCallback =        ImageCallback;
      mdConfig.userData =             NULL;
      ImGui::Markdown( markdown_.c_str(), markdown_.length(), mdConfig );
  }
}

Interface::Interface(bool show_demo_window)
{
  LoadImages();
  m_show_demo_window = show_demo_window;
}

void Interface::Init(GLFWwindow *window, const char *glsl_version)
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  Globals::g_Io = &ImGui::GetIO();
  (void)Globals::g_Io;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  // LoadFonts();
  Load3DFonts();
}

void Interface::Show(GLFWwindow *window)
{
  Start();
  if (m_show_demo_window)   { ImGui::ShowDemoWindow(&m_show_demo_window); };
  if (show_app_metrics)     { ImGui::ShowMetricsWindow(&show_app_metrics); }
  if (show_app_style_editor){ ImGui::Begin("Style Editor", &show_app_style_editor); ImGui::ShowStyleEditor(); ImGui::End(); }
  if (show_app_about)       { ImGui::ShowAboutWindow(&show_app_about); }

  ImGuiWindowFlags window_flags = 0;
  window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

  ImGui::SetNextWindowPos(ImVec2(60, 20), ImGuiCond_Once);
  window_flags |= ImGuiWindowFlags_MenuBar;
  {
    ImGui::Begin("Settings", NULL, window_flags);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Tools"))
        {
            ImGui::MenuItem("Metrics", NULL, &show_app_metrics);
            ImGui::MenuItem("Style Editor", NULL, &show_app_style_editor);
            ImGui::MenuItem("About Dear ImGui", NULL, &show_app_about);
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    };

    SceneLoader();
    ImGui::End();
  }


  // Rendering
  ImGui::Render();

  int display_w, display_h;
  glfwGetFramebufferSize(window, &display_w, &display_h);
  // glViewport(0, 0, display_w, display_h);

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Interface::Load3DFonts() {

  FT_Library ft;
  if (FT_Init_FreeType(&ft))
  {
      fprintf(stderr, "ERROR::FREETYPE: Could not init FreeType Library\n");
      return;
  }

  FT_Face face;
  if (FT_New_Face(ft, "../misc/fonts/Roboto-Medium.ttf", 0, &face))
  {
      fprintf(stderr, "ERROR::FREETYPE: Failed to load font\n");
      return;
  }


  FT_Set_Pixel_Sizes(face, 0, 48);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
  for (unsigned char c = 0; c < 128; c++)
  {
      // load character glyph
      if (FT_Load_Char(face, c, FT_LOAD_RENDER))
      {
          fprintf(stderr, "ERROR::FREETYTPE: Failed to load Glyph\n");
          continue;
      }
      // generate texture
      unsigned int texture;
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexImage2D(
          GL_TEXTURE_2D,
          0,
          GL_RED,
          face->glyph->bitmap.width,
          face->glyph->bitmap.rows,
          0,
          GL_RED,
          GL_UNSIGNED_BYTE,
          face->glyph->bitmap.buffer
      );
      // set texture options
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      // now store character for later use
      Character character = {
          texture,
          glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
          glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
          (unsigned int) face->glyph->advance.x
      };
      Characters.insert(std::pair<char, Character>(c, character));
  }
}

void Interface::LoadFonts()
{
  // Load Fonts
  // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
  // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
  // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
  // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
  // - Read 'misc/fonts/README.txt' for more instructions and details.
  // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
  //Globals::g_Io.Fonts->AddFontDefault();
  //Globals::g_Io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
  //Globals::g_Io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
  //Globals::g_Io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
  //Globals::g_Io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
  //ImFont* font = Globals::g_Io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, Globals::g_Io.Fonts->GetGlyphRangesJapanese());
  //IM_ASSERT(font != NULL);
}

void Interface::LoadImages() {
  Image mars;
  mars.size = glm::vec2(512,512);
  mars.texture_id = LoadTextureImage("../data/img_mars.jpg");

  g_Images["mars"] = mars;
}

void Interface::CleanUp()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void Interface::Start()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void Interface::SceneLoader()
{
  ImGui::Combo("Change Scene", &g_CurrentScene, "1. Simple Triangle\0 \
2. 2D drawing Binary Clock\0 \
3. Matrix Transformations\0 \
4. Bezier Lines and Movement\0 \
5. Shading and Lighting Basics\0 \
6. Texture Mapping and Lighting\0 \
7. Multiple Lights\0 \
8. Frustum\0 \
9. Projection Matrix Deformation\0 \
10. Texture Mapping\0", 6);

  ImGui::Separator();

  switch (g_CurrentScene)
  {
  case 0:
    InterfaceScene1::ShowControls();
    break;
  case 1:
    InterfaceScene2::ShowControls();
    break;
  case 2:
    InterfaceScene3::ShowControls();
    break;
  case 3:
    InterfaceScene4::ShowControls();
    break;
  case 4:
    InterfaceScene5::ShowControls();
    break;
  case 5:
    InterfaceScene6::ShowControls();
    break;
  case 6:
    InterfaceScene7::ShowControls();
    break;
  case 7:
    InterfaceScene8::ShowControls();
    break;
  case 8:
    InterfaceScene9::ShowControls();
    break;
  case 9:
    InterfaceScene10::ShowControls();
    break;
  }
}

void Interface::CameraSettings()
{
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Separator();

  // Edit 3 floats representing a color
  ImGui::Text("Change Clear Color");
  ImGui::ColorEdit3("clear color", (float *)&g_ClearColor);
  ImGui::Separator();

  ImGui::Checkbox("Perspective Projection", &g_UsePerspectiveProjection);
  ImGui::Checkbox("Backface Culling", &g_BackfaceCulling);
  ImGui::Separator();

  ImGui::Text("Frustum Settings");
  ImGui::SliderFloat("Near Plane", &g_FrustumNearPlane, -100.0f, 100.0f);
  ImGui::SliderFloat("Far Plane", &g_FrustumFarPlane, -100.0f, 100.0f);
  ImGui::Separator();

  ImGui::SliderFloat("Far Plane", &g_FrustumFarPlane, -100.0f, 100.0f);
}

void Interface::DebugSettings()
{
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Text("%d vertices, %d indices (%d triangles)", ImGui::GetIO().MetricsRenderVertices, ImGui::GetIO().MetricsRenderIndices, ImGui::GetIO().MetricsRenderIndices / 3);

  ImGui::Separator();

  ImGui::Text("Current scene: %d", g_CurrentScene);
  ImGui::Text("Elapsed frames: %d", g_Frames);
  ImGui::Text("Elapsed updates: %d", g_Updates);

  ImGui::Checkbox("Show demo window", &m_show_demo_window);
}