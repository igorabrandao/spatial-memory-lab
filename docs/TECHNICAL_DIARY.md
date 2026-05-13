# 2026-05-113

Problems:

- Renderer getting bloatted
- Rendering the multiple meshes in the scene
- Camera perspective

Hypothesis:

- The renderer seems to be the main component of the platform. As a result every piece of the render loop is getting insite of it.
- Drawing, transforming and handling different meshes involved duplicating or using similar codes.
- Adjusting the camera perspective manually can be a huge pain.

Testing:

- I've trying to separate the smaller components inside the renderer such as: update vs render fns().
- Today I've created 2 meshes, one for a cube and another for the grid.
- Did some playgroung with glm::lookAt()

Results:

- Even if we have more separating on the codebase inside the renderer + new modules in the platform, the renderer continues to be the most complex piece of the platform.
- Not much to say about the meshes situation, I didn't have much time to think about it. For now the only solution I can think of is having an array of meshes to handle them individually without increasing the codebase exponentially.
- Not much to say about it either, but as far I know it's possible creating some scenes controls including zoom-in/out, camera rotation and movement to the axis.

# 2026-05-12

Problem:

- Rendering the initial window

Hypothesis:

- The app itself doesn't have the necessary instructions to create an OS window and handle inputs.

Testing:

- Integrating the GLFW and OpenGL libraries.

Results:

- In the desktop_app it was created an initial `main.cpp` file responsible for starting the initial window.
- Basically it follows the standard rendering procedures:
  - Initialize the GLFW;
  - Generate the pointer to a new window;
  - Setup the context (which windows we're going to manipulate);
  - Create the rendering loop (get events -> clear window -> refresh its state);
  - Destroy the window instance;

Notes:

- OpenGL is meant for rendering inside a window.
- GLFW is responsible for connecting with the OS to create the window itself + events handling.

# 2026-05-11

Problem:

- Defining the project's initial structure and linking with CMakeLists.txt files.

Hypothesis:

- An engine that renders image from an external device at least need the modules defined
  as folders inside the `src` folder.

Testing:

- Separating the modules responsibilities based key tasks such as:
  - Providing the types;
  - Handling the network/communication;
  - Calculations, image rendering etc.

Results:

- As a result we find out the initial scaffolding for the platform.
- We splitted the platform based on its internal engines (`src` folder), the applications that will validate them (`apps` folder) and third-party libraries that will be needed in the future
  (`libs` folder).
- Also we did experimentation with ways of compiling and running the project with a `build.sh` and `makefile`, the latter demonstrated a better degree of flexibility and control over the build process.
