add_requires("gtest")
add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})
target("main_example")
    set_kind("binary")
    set_languages("c++17")
    add_files("src/**.cc")
    add_files("example/**.cc")
    add_includedirs("include")
    set_symbols("debug")  -- 启用调试符号
    set_optimize("none")  -- 禁用优化以便于调试

target("tests")
    set_kind("binary")
    set_languages("c++17")
    add_files("src/**.cc")
    add_files("tests/*.cc")
    add_includedirs("include")
    add_packages("gtest")
    set_symbols("debug")  -- 启用调试符号
    set_optimize("none")  -- 
    before_build(function (target)
        -- 获取构建输出目录
        local build_dir = target:targetdir();
        -- 打印提示信息
        print("Cleaning build directory: " .. build_dir)
        -- 清理构建输出目录
        os.tryrm(build_dir)
        -- 重新创建构建输出目录
        os.mkdir(build_dir)
end)