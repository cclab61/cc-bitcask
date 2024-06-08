add_requires("gtest")

add_rules("mode.debug", "mode.release")

target("main_example")
    set_kind("binary")
    add_files("src/**.cc")
    add_files("example/**.cc")
    add_includedirs("include")
    set_symbols("debug")  -- 启用调试符号
    set_optimize("none")  -- 禁用优化以便于调试

target("tests")
    set_kind("binary")
    add_files("tests/*.cc")
    add_packages("gtest")
    set_symbols("debug")  -- 启用调试符号
    set_optimize("none")  -- 禁用优化以便于调试