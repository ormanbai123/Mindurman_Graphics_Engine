//#include "Shader.h"
#include "window.h"
//#include "Matrix.h"
//#include<GL/glew.h>


window::window(int width, int height, const char title[]) {
    // Initiliaze GLFW
    if (!glfwInit())
        std::cout<<"Failed to initliaze GLFW";

    // Make window unresizable
    int win_res = GLFW_RESIZABLE;
    glfwWindowHint(win_res, GLFW_FALSE);

    // Create GLFW window
    winHeight = height; winWidth = width; //winaspectRatio = (float)height / (float)width; 
    winaspectRatio = (float)width / (float)height;

	m_win = glfwCreateWindow(winWidth, winHeight, title, NULL, NULL);
    if (!m_win)
    {
        glfwTerminate();
        std::cout << "Failed to create window";
    }

    // Create OpenGL context
    glfwMakeContextCurrent(m_win);

    glewInit();

}

window::~window() {
    glfwTerminate();
}

void window::cls() {
 // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Close window when "ESCAPE" is PRESSED
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

Camera fps_cam{ vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, -1.0f) , vec2() };

void window::mouse_callback(GLFWwindow* win, double x_pos, double y_pos)
{
    fps_cam.input_mouse(x_pos, y_pos, fps_cam.vDir);
}

void window::input(GLFWwindow* win) {

    /*double mouseX; double mouseY;
    glfwGetCursorPos(win, &mouseX, &mouseY);
    fps_cam.input_mouse(mouseX, mouseY, fps_cam.vDir);*/

    // Camera movement
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
        fps_cam.vPos += fps_cam.vDir;
    }
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
        fps_cam.vPos -= fps_cam.vDir;
    }
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
        vec3 lefto; //lefto = lefto.getCrossProduct(fps_cam.vUp, fps_cam.vDir);
        lefto = lefto.getCrossProduct(fps_cam.vDir, fps_cam.vUp);
        lefto.normalize();
        fps_cam.vPos -= lefto;
    }
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
        vec3 righto; righto = righto.getCrossProduct(fps_cam.vDir, fps_cam.vUp);
        righto.normalize();
        fps_cam.vPos += righto;
    }

    if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS) {
        fps_cam.vPos += fps_cam.vUp;
    }
    if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS) {
        fps_cam.vPos -= fps_cam.vUp;
    }

    // Moving light
    if (glfwGetKey(win, GLFW_KEY_I) == GLFW_PRESS) {
        light += vec3(0.0f, 0.0f, 1.0f);
    }
    if (glfwGetKey(win, GLFW_KEY_J) == GLFW_PRESS) {
        light += vec3(-1.0f, 0.0f, 0.0f);
    }
    if (glfwGetKey(win, GLFW_KEY_K) == GLFW_PRESS) {
        light += vec3(0.0f, 0.0f, -1.0f);
    }
    if (glfwGetKey(win, GLFW_KEY_L) == GLFW_PRESS) {
        light += vec3(1.0f, 0.0f, 0.0f);
    }
    if (glfwGetKey(win, GLFW_KEY_U) == GLFW_PRESS) {
        light += vec3(0.0f, 1.0f, 0.0f);
    }
    if (glfwGetKey(win, GLFW_KEY_O) == GLFW_PRESS) {
        light += vec3(0.0f, -1.0f, 0.0f);
    }

}

void window::begin() {
    std::cout << glGetString(GL_VERSION) << std::endl; // Check OpenGL version

    glfwSetKeyCallback(m_win, key_callback);
    glfwSetCursorPosCallback(m_win, mouse_callback);

    Shader myshader("shader_1.vert.txt", "shader_1.frag.txt");
    GLuint program = myshader.rtrnProgram();
    myshader.delShader(); //Delete shader

  /*  float vertices[] = {
        1.0f, 0.0f, -2.0f,
        0.0f, 0.0f, -2.0f,
        0.0f, 0.0f, -3.0f,
        1.0f, 0.0f, -3.0f,

        1.0f, 1.0f, -2.0f,
        0.0f, 1.0f, -2.0f,
        0.0f, 1.0f, -3.0f,
        1.0f, 1.0f, -3.0f,
    };*/

  /*  float vertices[] = {
       1.0f, 0.0f, -2.0f,   1.0f, 0.0f, 
       0.0f, 0.0f, -2.0f,   0.0f, 0.0f,
       0.0f, 0.0f, -3.0f,   0.0f, 1.0f,
       1.0f, 0.0f, -3.0f,   1.0f, 1.0f,

       1.0f, 1.0f, -2.0f,   1.0f, 0.25f,
       0.0f, 1.0f, -2.0f,   0.0f, 0.25f,
       0.0f, 1.0f, -3.0f,   0.0f, 0.75f,
       1.0f, 1.0f, -3.0f,   1.0f, 0.75f,
    };*/

   /* unsigned int indices[] = {
        0, 1, 5,
        0, 5, 4,
        0, 4, 7,
        0, 7, 3,
        4, 5, 6,
        4, 6, 7,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        0, 3, 2,
        0, 2, 1
    };*/
    
    glfwSetInputMode(m_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    fps_cam.set_win_centre(vec2((float)winWidth/2.0f, (float)winHeight/2.0f));

    mat4x4 transmat; transmat.makeTranslation(0.0f, 2.0f, -6.0f);
    mat4x4 viewmat; viewmat.makeView(fps_cam.vPos, fps_cam.vPos + fps_cam.vDir, fps_cam.vUp);
    mat4x4 projmat; /*testmat.makeIdentity(); */ projmat.makePerspective(0.1f, 100.0f, math_pi / 2, winaspectRatio);

    //GLuint VBO; glGenBuffers(1, &VBO); /*glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);*/

    //GLuint VAO; glGenVertexArrays(1, &VAO); glBindVertexArray(VAO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);


    // VBO - vertex buffer objects // VAO - vertex array object // EBO - element buffer object(simply array of indices)
    //GLuint VBO, VAO, EBO;
    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    //glBindVertexArray(VAO);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    ///*new for textures*/ 
    ///*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);*/

    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindVertexArray(0);


    ////Textures mytexture("pixelDio.png");

    //while (!glfwWindowShouldClose(m_win)) {

    //    input(m_win);

    //    cls();

    //    /* new for textures*/  /* mytexture.bindTexture(); */

    //    glUseProgram(program); 

    //    GLuint u_view = glGetUniformLocation(program, "view"); viewmat.makeView(win_cam, vec3(win_cam+target), camUp); glUniformMatrix4fv(u_view, 1, GL_FALSE, &viewmat.mat4[0][0]);
    //    GLuint tran = glGetUniformLocation(program, "transform"); glUniformMatrix4fv(tran, 1, GL_FALSE, &testmat.mat4[0][0]);
    //   
    //    glBindVertexArray(VAO);

    //    //cls();

    //    //glDrawArrays(GL_TRIANGLES, 0, 3);

    //    /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/   glDrawElements(GL_TRIANGLES, /*sizeof(indices)/sizeof(indices[0])*/ 36, GL_UNSIGNED_INT, 0);

    //    /* Swap front and back buffers */
    //    glfwSwapBuffers(m_win);
    //    /* Poll for and process events */
    //    glfwPollEvents();

    //}


    //

    // Depth Test & Face culling
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    //glFrontFace(GL_CW);

    // Flip UV's
    stbi_set_flip_vertically_on_load(true);

    //-----------NEW-----------------LOADING MODEL----------------------------
    //Model myModel("Models/sponza/sponza.obj");  //teapot.obj //Sketchfab.obj classroom.obj
    //Model myModel("Models/sponza_v1/sponza.obj");
    Model myModel("Models/Door/Door.obj");
    //Model myModel("Models/sibenik/sibenik.obj");
    //Model myModel("Models/teapot.obj");
    //Model myModel("Models/sampleCube/cube.obj");
    //Model myModel("Models/holodeck/holodeck.obj");
    //Model myModel("Models/lEmpire/lost_empire.obj");

    while (!glfwWindowShouldClose(m_win)) {

        input(m_win); 

        cls();

        /* new for textures*/  /* mytexture.bindTexture(); */

        glUseProgram(program);

        // Set lighting uniforms
        glUniform3f(glGetUniformLocation(program, "cameraPos"), fps_cam.vPos.x, fps_cam.vPos.y, fps_cam.vPos.z);
        glUniform3f(glGetUniformLocation(program, "lightPosition"), light.x, light.y, light.z);

        // Set matrix uniforms
        GLuint u_view = glGetUniformLocation(program, "view"); //viewmat.makeView(win_cam, vec3(win_cam + target), camUp); 
        viewmat.makeView(fps_cam.vPos, fps_cam.vPos + fps_cam.vDir, fps_cam.vUp); glUniformMatrix4fv(u_view, 1, GL_FALSE, &viewmat.mat4[0][0]);
        GLuint u_proj = glGetUniformLocation(program, "projection"); glUniformMatrix4fv(u_proj, 1, GL_FALSE, &projmat.mat4[0][0]);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        myModel.Draw(myshader, program);

        /* Swap front and back buffers */
        glfwSwapBuffers(m_win);
        /* Poll for and process events */
        glfwPollEvents();

    }

    
}
