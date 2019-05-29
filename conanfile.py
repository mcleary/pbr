from conans import ConanFile, CMake

class Pbr(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "glfw/3.3@bincrafters/stable", "glm/0.9.9.4@g-truc/stable", "stb/20190512@conan/stable"
    generators = "cmake", "visual_studio"
    
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()