# AMD rccl
# A package of optimized primitives for collective multi-GPU communication.

licenses(["notice"])  # BSD

exports_files(["LICENSE"])

load("@local_config_rocm//rocm:build_defs.bzl", "rocm_default_copts", "if_rocm")

cc_library(
    name = "rccl",
    srcs = if_rocm(glob(["src/*.cpp"]) + glob(["src/*.h"])),
    hdrs = if_rocm(["inc/rccl.h", "inc/rccl-version.h"]),
    copts = [
        "-Iexternal/rccl_archive/src",
        "-Iexternal/rccl_archive/inc",
        "-O3",
    ] + rocm_default_copts(),
    linkopts = select({
        "//conditions:default": [
            "-lrt",
        ],
    }),
    strip_include_prefix = "inc",
    visibility = ["//visibility:public"],
    deps = ["@local_config_rocm//rocm:rocm_headers"],
)

genrule(
    name = "rccl_version",
    message = "Creating RCCL version header...",
    srcs = ["inc/rccl-version.h.in"],
    outs = ["inc/rccl-version.h"],
    cmd = ("sed " +
           "-e 's/@rccl_VERSION_MAJOR@/0/g' " +
           "-e 's/@rccl_VERSION_MINOR@/7/g' " +
           "-e 's/@rccl_VERSION_PATCH@/1/g' " +
           "-e 's/@rccl_VERSION_TWEAK@//g' " +
           "$< >$@"),
)
