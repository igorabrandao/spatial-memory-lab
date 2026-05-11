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
