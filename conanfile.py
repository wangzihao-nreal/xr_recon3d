from conan import ConanFile
from conan.tools.cmake import CMake
from conan.tools.files import copy
import os

class Project(ConanFile):

    # all project are the same:
    python_requires = "project_base/1.0"
    python_requires_extend = "project_base.ProjectBase"

    def init(self):
        base = self.python_requires["project_base"].module.ProjectBase
        self.settings = base.settings
        self.options.update(base.options, base.default_options)
        self.revision_mode = base.revision_mode

    def set_name(self):
        self.name = "example"

    # difference between project:
    def requirements(self):
        self.requires(super().override_require("xr_recon3d/master"))
        self.requires(super().override_require("eigen/3.3.7"))
        self.requires(super().override_require("opencv/4.5.5"))

