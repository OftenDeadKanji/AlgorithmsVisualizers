add_library(ImGui "imgui-SFML.cpp" "imgui.cpp" "imgui_demo.cpp" "imgui_draw.cpp" "imgui_tables.cpp" "imgui_widgets.cpp")

target_include_directories(ImGui PRIVATE "../../include/")
target_include_directories(ImGui PRIVATE "../../include/ImGUI/")