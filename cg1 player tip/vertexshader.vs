#version 400 core
layout (location = 0) in vec2 aPos;        // Позиция вершины
layout (location = 1) in vec2 aTexCoord;   // Текстурные координаты

out vec2 TexCoord;  // Переменная для передачи текстурных координат во фрагментный шейдер

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);  // Позиция вершин
    TexCoord = aTexCoord;                // Передаем текстурные координаты во фрагментный шейдер
}
