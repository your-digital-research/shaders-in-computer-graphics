# Shaders In Computer Graphics

This repository, developed by [Davit Badalyan](https://github.com/davit-badalyan), contains a practical rendering application and research materials for a master's thesis on **Shaders In Computer Graphics**.

## Table of Contents

- [About](#about)
- [Preview](#preview)
- [Getting Started](#getting-started)
- [Planned Features](#planned-features)
- [Useful Links](#useful-links)
- [License](#license)

## <a name="about"></a> About

The purpose of this project is to research Shaders and Computer Graphics by building a Practical Rendering Application that demonstrates their capabilities and use cases. The application allows users to create, manipulate, and experiment with Shaders, showcasing what can be achieved with them and how they function in a Real-Time Rendering Environment.

At its core, this project is a Minimal Rendering Application designed to serve as an experimental environment where Example Scenes can be easily created, Shaders can be tested and iterated on, and various Computer Graphics Techniques can be explored. The primary goal is to provide a Hands-On Learning Experience for understanding Shader Programming and fundamental Computer Graphics Concepts.

Beyond research and learning, the project is built with Extensibility and Modularity in mind, serving as a foundation that can later be developed into a more substantial system, such as a Game Engine or a more comprehensive Graphics Framework.

I would like to extend my sincere gratitude to my mentors, [Bagrat Dabaghyan](https://github.com/dBagrat) and [Andranik Melikyan](https://github.com/andranik3949), for their invaluable support, guidance, and mentorship throughout this project.

## <a name="preview"></a> Preview

### Showcases

<video src="https://github.com/user-attachments/assets/c5a35089-b3fb-49a7-849a-cc465bb54783" controls width="100%" alt="Cube Showcase">
  Your browser does not support the video tag.
</video>

---

### Screenshots

#### Rainbow Triangle

![Triangle Example](Assets/Images/triangle-example.png)

---

#### UV Quad

![Quad Example](Assets/Images/quad-example.png)

---

#### Rotating Cube

![Cube Example](Assets/Images/cube-example.png)

---

#### Fresnel Sphere

![Sphere Example](Assets/Images/sphere-example.png)

---

#### Wavy Plane

![Plane Example](Assets/Images/plane-example.png)

## <a name="getting-started"></a> Getting Started

### Prerequisites

**Note:** Prerequisites will be listed here once the build process is stabilized across all platforms.

### Building and Running

**Note:** This application was built and tested on macOS. There are known issues with the Windows and Linux building and running process. This section will be updated with detailed instructions for all platforms.

**Development System Specifications:**

- macOS 26.2 (25C56)
- Apple M1 Pro
- 16 GB RAM

**IDE / Editor:**

- Visual Studio Code (VS Code)
- CLion

**Build Tools:**

- CMake 4.1.2 (minimum 3.10 required)
- Apple Clang 17.0.0 (C++17 compiler)

**Graphics API:**

- OpenGL 3.3+

**Dependencies & Libraries:**

- **GLFW** - Window Creation and Input Management
- **GLM** - OpenGL Mathematics Library
- **GLAD** - OpenGL Function Loader
- **ImGui** - Immediate mode GUI Framework

## <a name="planned-features"></a> Planned Features

### Core Development

- [ ] Resolve cross-platform compilation and build system compatibility for Linux and Windows environments
- [ ] Refactor core architecture and scene management subsystem
- [ ] Optimize existing scene implementations and rendering performance
- [ ] Enhance mesh data structure with comprehensive vertex attributes (normals, tangents, bitangents, etc...)
- [ ] Integrate texture loading pipeline and texture mapping functionality
- [ ] Implement 3D model import and mesh processing pipeline
- [ ] Implement physically-based lighting and illumination models

## <a name="useful-links"></a> Useful Links

Here is a list of references, books, tutorials, and online courses that were used during the development and helped throughout the process:

### 1. Fundamentals of Computer Graphics

- [Medium - Graphics Pipeline](https://medium.com/@rakadian/graphics-pipeline-9e4bb2d28f58)
- [Wikipedia - Graphics Pipeline](https://en.wikipedia.org/wiki/Graphics_pipeline)
- [Wikipedia - Computer Graphics](https://en.wikipedia.org/wiki/Computer_graphics)
- [LMU - Computer Graphics Basics](https://cs.lmu.edu/~ray/notes/graphicsintro/)
- [GeeksforGeeks - Computer Graphics](https://www.geeksforgeeks.org/computer-graphics-2/#basics-)
- [Wikipedia - Rendering (Computer Graphics)](<https://en.wikipedia.org/wiki/Rendering_(computer_graphics)>)
- [GeeksforGeeks - Introduction to Computer Graphics](https://www.geeksforgeeks.org/introduction-to-computer-graphics/)

### 2. Mathematics, Geometry, and Rendering Methods

- [Scratchapixel 4.0 - Geometry](https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry/coordinate-systems.html#)
- [uxcel - 3D Coordinates System](https://app.uxcel.com/courses/3d-design-foundations/d-coordinates-system-038)
- [GeeksforGeeks - Radiosity Rendering](https://www.geeksforgeeks.org/radiosity-rendering-in-computer-graphics/)
- [Kent State University - Rendering Methods](https://www.cs.kent.edu/~farrell/cg00/lectures/rendering/render.html)

### 3. Color Models and Color Spaces

- [Wikipedia - Color Models](https://en.wikipedia.org/wiki/Color_model)
- [NTUA Physics Dept. - Color Models](https://www.physics.ntua.gr/~konstant/HetCluster/intel12.1/ipp/ipp_manual/IPPI/ippi_ch6/ch6_color_models.htm)
- [Tutorials Point - Color Models in Computer Graphics](https://www.tutorialspoint.com/computer_graphics/computer_graphics_color_models.htm)
- [Programming Design Systems - Color Models and Spaces](https://programmingdesignsystems.com/color/color-models-and-color-spaces/index.html)
- [Medium - Understanding RGB and HSV for Computer Vision](https://medium.com/@DIYCoding/color-models-in-image-processing-understanding-rgb-and-hsv-for-computer-vision-a629641cdc40)
- [GeeksforGeeks - Difference Between RGB, CMYK, HSV, and YIQ](https://www.geeksforgeeks.org/difference-between-rgb-cmyk-hsv-and-yiq-color-models/)

### 4. Graphics APIs and GPU Programming

- [Modern GL](https://glumpy.github.io/modern-gl.html#)
- [Medium - Understanding Graphics APIs](https://medium.com/@joseak.tech/understanding-graphics-apis-0ae8a5a7cbdf)
- [ReplayBird - Best Graphics APIs and Alternatives](https://blog.replaybird.com/graphic-apis-best-alternatives/)

### 5. OpenGL and Practical Graphics Programming

- [OpenGLBook](https://openglbook.com)
- [Learn OpenGL](https://learnopengl.com)
- [OpenGL Insights](https://openglinsights.com/toc.html)
- [Modern OpenGL Guide](https://open.gl/introduction)
- [Graphics Programming](https://graphics-programming.org)

#### GitHub Repositories

- [Glitter](https://github.com/Polytonic/Glitter)
- [LearnOpenGL](https://github.com/JoeyDeVries/LearnOpenGL)
- [The Book of Shaders (GitHub)](https://github.com/patriciogonzalezvivo/thebookofshaders?tab=readme-ov-file)
- [3D Game Shaders for Beginners](https://github.com/lettier/3d-game-shaders-for-beginners)

### 6. Shaders and Ray Tracing

- [The Book of Shaders](https://thebookofshaders.com)
- [Making Software - Shaders](https://www.makingsoftware.com/chapters/shaders)
- [Branch Education - How Ray Tracing Works](https://www.youtube.com/watch?v=iOlehM5kNSk&t=1s)

### 7. GPU Architecture and Game Graphics

- [Branch Education - How Graphics Cards Work](https://www.youtube.com/watch?v=h9Z4oGN89MU)
- [Adrian Courrèges - Graphics Studies Compilation](https://www.adriancourreges.com/blog/2020/12/29/graphics-studies-compilation/)
- [Branch Education - How Video Game Graphics Work](https://www.youtube.com/watch?v=C8YtdC8mxTU)

### 8. Academic Lectures and Open Courses

- [The Cherno - OpenGL](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)
- [Jon Macey - Lectures](https://nccastaff.bournemouth.ac.uk/jmacey/)
- [Tutorials Point - Computer Graphics](https://www.tutorialspoint.com/computer_graphics/index.htm)
- [Introduction to Computer Graphics (HWS)](https://math.hws.edu/graphicsbook/)
- [Introduction to Computer Graphics (Open Textbook)](https://open.umn.edu/opentextbooks/textbooks/introduction-to-computer-graphics)
- [Keenan Crane - Computer Graphics Course (YouTube)](https://www.youtube.com/watch?v=W6yEALqsD7k&list=PL9_jI1bdZmz2emSh0UQ5iOdT2xRHFHL7E)
- [Basics of Computer Graphics - K.C.S.Kasi Nadar College](https://kcskasinadarcollege.in/download/files/computer_science/notes/study_material/cs_study_material_graphics.pdf)
- [Cem Yuksel - Introduction to Computer Graphics (YouTube)](https://www.youtube.com/watch?v=vLSphLtKQ0o&list=PLplnkTzzqsZTfYh4UbhLGpI5kGd5oW_Hh)

### 9. History and Evolution

- [Medium - Computer Graphics in the Era of AI](https://nettricegaskins.medium.com/computer-graphics-in-the-era-of-ai-from-the-1960s-to-the-present-420f371d9c1b)
- [William Fetter, E.A.T., and 1960s Collaborations](https://www.historylink.org/File/20542)
- [William Fetter Biography (Science Museum Group)](https://collection.sciencemuseumgroup.org.uk/people/cp167300/william-fetter)

### 10. Community Discussions & Book Collections

- [Real-Time Rendering Graphics](https://www.realtimerendering.com/books.html)
- [Computer Graphics Books Collection](https://www.goodreads.com/shelf/show/computer-graphics)
- [Reddit - Best Textbooks/Resources for Learning Graphics Programming](https://www.reddit.com/r/GraphicsProgramming/comments/14sbgbi/what_are_the_best_textbooksresources_for_learning/)

### 11. Books

- [Modern OpenGL Guide](https://docs.google.com/document/d/1IQwWxrLW1jHBBzs4EneTSo-tQ8lDZMadMPJ5Ci-6v_A/edit?tab=t.0)
- [Game Graphics Programming](https://www.amazon.com/Game-Graphics-Programming-Allen-Sherrod/dp/1584505168)
- [Introduction to Computer Graphics](https://math.hws.edu/eck/cs424/downloads/graphicsbook-linked.pdf)
- [Learn OpenGL (Offline 2nd Printing)](https://learnopengl.com/book/offline%20learnopengl.pdf)
- [Fundamentals of Computer Graphics (5th Edition)](https://www.amazon.com/Fundamentals-Computer-Graphics-Steve-Marschner-ebook/dp/B098TWMBV4)
- [Foundations of Game Engine Development – Volume 2, Rendering](https://www.amazon.com/dp/0985811757/?tag=terathon-20)

## <a name="license"></a> License

This repository is licensed under the [MIT License](https://opensource.org/license/mit/).

If you have any questions, encounter issues, or wish to share suggestions, please open an issue.

Happy coding!
