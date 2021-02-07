# CMakeList.txt : projet CMake pour universeBuilder, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)
project ("universeBuilder")

include_directories( "Include/" "Include/external" "lib/ImGui" "Include/freetype" "lib/GLFW/include" "lib/GLEW/include" )

find_package(imgui CONFIG)

set(SRCS
	"lib/ImGui/imgui.cpp"
	"lib/ImGui/imgui_demo.cpp"
	"lib/ImGui/imgui_tables.cpp"
	"lib/ImGui/imgui_widgets.cpp"
	"lib/ImGui/imgui_draw.cpp"
	"lib/ImGui/imgui_impl_opengl3.cpp"
	"lib/ImGui/imgui_impl_glfw.cpp"

	"src/Misc/Debug.cpp"
	
	"src/UniverseBuilder.cpp"
	"src/Graphics/VertexArray.cpp"
	"src/Graphics/VertexBuffer.cpp"
	"src/Graphics/VertexBufferLayout.cpp"
	"src/Graphics/IndexBuffer.cpp"
  "src/Graphics/Shader.cpp")

set(imgui_sources
)

set(imgui_headers
  "lib/ImGui/imconfig.h"
  "lib/ImGui/imgui.h"
  "lib/ImGui/imstb_rectpack.h"
  "lib/ImGui/imstb_truetype.h"
  "lib/ImGui/imgui_internal.h"
  "lib/ImGui/imstb_textedit.h"
  "lib/ImGui/imgui_impl_glfw.h"
  "lib/ImGui/imgui_impl_opengl3.h"
)

#set(imgui_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/ImGui)


find_package(OpengL REQUIRED COMPONENTS OpenGL)


add_executable(output ${SRCS})

target_link_libraries(output ./libs/GLFW/glfw3)
target_link_libraries(output ./libs/GLEW/glew32)
target_link_libraries(output ./libs/freetype/freetype)
target_link_libraries(output OpenGL::GL)

file(COPY "./lib/GLFW/lib-vc2019/glfw3.lib" DESTINATION ${CMAKE_BINARY_DIR}/libs/GLFW/)
file(COPY "./lib/GLFW/lib-vc2019/glfw3.dll" DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY "./lib/GLEW/lib/glew32.lib" DESTINATION ${CMAKE_BINARY_DIR}/libs/GLEW/)
file(COPY "./lib/GLEW/bin/Release/x64/glew32.dll" DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY "./lib/freetype/freetype.lib" DESTINATION ${CMAKE_BINARY_DIR}/libs/freetype/)
file(COPY "./lib/freetype/freetype.dll" DESTINATION ${CMAKE_BINARY_DIR}/)
#file(COPY "./lib/GLFW/lib-vc2019/glfw3.dll" DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY "./Ressources" DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY "./Shaders" DESTINATION ${CMAKE_BINARY_DIR}/)