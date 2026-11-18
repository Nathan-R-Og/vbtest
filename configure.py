import argparse
import ninja_syntax
from glob import glob

from pathlib import Path
from typing import Dict, List, Set, Union
import os
import shutil

NINJA_FILE = "build.ninja"
OUT_NAME = "vbtest"
BUILD_FOLDER = "build/"

PREFIX  = "tools/v810-gcc/bin/v810-"
CC      = f"{PREFIX}gcc"
AS      = f"{PREFIX}as"
OBJCOPY = f"{PREFIX}objcopy"

CFLAGS  = "-Iinclude -O2 -Wall -mv810"
LDFLAGS = f"-T vb.ld -nostdlib -Wl,-Map={BUILD_FOLDER}{OUT_NAME}.map"

TARGET  = f"{BUILD_FOLDER}{OUT_NAME}.vb"
ELF     = f"{BUILD_FOLDER}{OUT_NAME}.elf"

ninja = None

defines = []

class Dependency(object):
    def __init__(self, file_path:str):
        self.base_file = file_path
        if file_path.endswith(".2bpp"):
            self.type = "png"
            self.base_file = self.base_file.replace("build/", "")
            self.origin_file = self.base_file.replace(".2bpp", ".png")
        else:
            self.type = "bin"

    #get the o path
    def get_build_path(self):
        self.build = BUILD_FOLDER+self.base_file
        return self.build

    #generate rule for ninja
    def generate_artifact(self):
        if self.type == "png":
            return (self.build, self.origin_file, "2bpp", self.origin_file)
        else:
            return (self.build, self.base_file, "copy", self.base_file)


def build(
    object_paths: Union[Path, List[Path]] = [],
    src_paths: List[Path] = [],
    task: str = "",
    implicit: List[str] = [],
    variables: Dict[str, str] = {},
    implicit_outputs: List[str] = [],
):
    if not isinstance(object_paths, list):
        object_paths = [object_paths]

    object_strs = [str(obj) for obj in object_paths]

    if not isinstance(src_paths, list):
        src_paths = [src_paths]

    global ninja
    ninja.build(
        outputs=object_strs,
        rule=task,
        inputs=[str(s) for s in src_paths],
        implicit=implicit,
        variables=variables,
        implicit_outputs=implicit_outputs,
    )

def make_ninja():
    os.mkdir(BUILD_FOLDER)

    global defines
    defines = " ".join(["-D "+define for define in defines])

    global ninja
    ninja = ninja_syntax.Writer(open(NINJA_FILE, "w"))

    ninja.rule(
        "cc",
        command=f"{CC} {CFLAGS} -save-temps=obj -c $in -o $out",
        description="Compiling...",
    )

    ninja.rule(
        "as",
        command=f"{AS} $in -o $out",
        description="Assembling...",
    )

    ninja.rule(
        "ld",
        command=f"{CC} {LDFLAGS} -o $out $in",
        description="Linking...",
    )

    ninja.rule(
        "rom",
        command=f"{OBJCOPY} -O binary $in $out",
        description="Creating ROM...",
    )

    ninja.rule(
        "copy",
        command=f"cp -r $in $out",
        description="Copying file...",
    )

    ninja.rule(
        "2bpp",
        command=f"python3 tools/twobppcompile.py $in $out",
        description="Copying file...",
    )

    c_files = glob("src/**/*.c", recursive=True)
    s_files = glob("src/**/*.s", recursive=True)
    c_files += glob("src/**/*.S", recursive=True)
    code_files = c_files + s_files

    existing_dependencies : list[Dependency] = []

    o_files = []
    for file in code_files:
        dependencies : list[Dependency] = getDependencies(file)
        out_dependencies = []
        for dependency in dependencies:
            b_path = dependency.get_build_path()
            if not b_path in out_dependencies:
                out_dependencies.append(b_path)
            if not dependency.base_file in existing_dependencies:
                ninja_todo = dependency.generate_artifact()
                if ninja_todo != None:
                    build(*ninja_todo)
            existing_dependencies.append(dependency.base_file)



        out_file = os.path.basename(file).split(".",1)[0]+".o"
        out_dir = BUILD_FOLDER+os.path.dirname(file).replace("\\", "/")+"/"
        full_out = out_dir+out_file
        o_files.append(full_out)
        if file in c_files:
            build(full_out, file, "cc", implicit=out_dependencies)
        else:
            build(full_out, file, "as", implicit=out_dependencies)

    build(ELF, o_files, "ld", implicit=o_files)
    build(TARGET, ELF, "rom", implicit=[ELF])

def getDependencies(file):
    kind = file.split(".", 1)[-1]
    out = []
    lines = open(file, "r").readlines()
    i = 0
    if kind.lower() == "s":
        while i < len(lines):
            line = lines[i].strip()
            if line.find(".include") != -1:
                path = line.split(" ")[1].replace(",","")[1:-1]
                out += getDependencies(path)
            elif line.find(".incbin") != -1:
                path = line.split(" ")[1].replace(",","")[1:-1]
                out.append(Dependency(path))
            i += 1
    return out

def convImg(file):
    base = file.split("/")
    base.pop(0)
    base = "/".join(base)
    base = base.replace(".png", "")

    return f"{BUILD_FOLDER}{base}.2bpp"

if __name__ == "__main__":
    ninja_artifacts = ["build.ninja", ".ninja_log"]
    for file in ninja_artifacts:
        if os.path.exists(file):
            os.remove(file)
    shutil.rmtree("build/")

    make_ninja()

