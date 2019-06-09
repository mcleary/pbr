from conans import ConanFile, CMake

class Pbr(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = (
        "glfw/d834f01ca43c0f5ddd31b00a7fc2f48abbafa3da@thales/stable", 
        "glm/0.9.9.4@g-truc/stable", 
        "stb/20190512@conan/stable", 
        "glbinding/3.1.0@thales/stable"
    )    
    default_options = {
        "glfw:shared": True,
        "glbinding:shared": True
    }
    generators = "cmake", "visual_studio"
    
    
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin") # From bin to bin
        self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin