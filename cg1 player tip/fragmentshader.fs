#version 400 core
out vec4 FragColor;        // Цвет финального фрагмента
in vec2 TexCoord;          // Полученные текстурные координаты из вершинного шейдера

uniform sampler2D texture1; // Текстура

void main()
{
    FragColor = texture(texture1, TexCoord); // Применяем текстуру к фрагменту
}
