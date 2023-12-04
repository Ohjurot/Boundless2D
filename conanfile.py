from conan import ConanFile

class Boundless2DRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "PremakeDeps"

    def requirements(self):
        self.requires("spdlog/1.12.0")
        self.requires("fmt/10.1.1")

    def configure(self):
        if self.settings.os == "Windows":
            self.options["spdlog"].wchar_support = True
