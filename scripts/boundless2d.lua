-- Global
BUILD_LIBS = {}
BUILD_MODULES = {}

-- Project discovery functions

function bl2d_include_folder(name)
    for dir in mox_discover_subfolders("../src/" .. name)
    do 
        hmox_project_dir = "../src/" .. name .. "/" .. dir .. "/" 
        local buildFile = hmox_project_dir .. "build.lua" 
        if os.isfile(buildFile) then
            include(buildFile)
        end
    end
end

-- File generation functions

function replace_pattern(content, patterns)
    for k,v in pairs(patterns) 
    do
        content = string.gsub(content, "<<" .. k .. ">>", v)
    end

    return content
end

function generate_file(outfile, template, patterns)
    content = io.readfile(template)
    content = replace_pattern(content, patterns)
    io.writefile(outfile, content)
end

function generate_module_h_or_cpp_ondemand(name, ending) 
    local f = "./" .. name .. "." .. ending;
    if os.isfile(f) == false then
        patterns = {}
        patterns["name_dt"] = name
        patterns["name_us"] = string.gsub(name, "%.", "_")
        generate_file(f, "../../../../templates/lua_module/module." .. ending, patterns)
    end
end

function generate_register_modules(modules) 
    local includes = ""
    local regcalls = ""
    
    for i,v in ipairs(modules)
    do
        includes = includes .. 
            "#include <" .. v .. "/" .. v .. ".h>" .. "\n"
        regcalls = regcalls .. 
            "    ::bl2d::ModuleManager::Get().Register<bl2d::modules::" .. v:gsub("%.", "_") .. ">();" .. "\n"
    end

    local patterns = {}
    patterns["module_includes"] = includes
    patterns["module_regcalls"] = regcalls

    generate_file("./register_modules.cpp", "../../../../templates/lua_module/register_modules.cpp", patterns)
end

function generate_file_ondemand(template, patterns, out) 
    if os.isfile(out) == false then
        generate_file(out, template, patterns)
    end
end

function generate_app_files(name)
    patterns = {}
    patterns["app_name"] = name
    
    generate_file_ondemand("../../../../templates/lua_app/main.cpp", patterns, "./main.cpp")
    generate_file_ondemand("../../../../templates/lua_app/app.h", patterns, "./" .. name .. ".h")
    generate_file_ondemand("../../../../templates/lua_app/app.cpp", patterns, "./" .. name .. ".cpp")
end

-- Project template function

function bl2d_project(name)
    -- Basic setup
    mox_project(name)
    mox_cpp("C++20")

    -- Custom include paths
    includedirs {
        "%{wks.location}/" .. cmox_src_folder .. "/bl2d/common/api/",
        "%{wks.location}/" .. cmox_src_folder .. "/bl2d/modules/",
    }
    
    -- Project type
    filter { "configurations:Debug*" }
        defines { cmox_macro_prefix .. "CONSOLE_APP" }
    filter {}
    filter { "configurations:not Debug*" }
        defines { cmox_macro_prefix .. "WINDOWED_APP" }
    filter {}

    -- Silence
    defines {
        "_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING"
    }

    -- OS Specific stuff
    filter {"system:Windows"}
        links {
            "wbemuuid.lib"
        }
    filter {}
end

function bl2d_headers(name)
    bl2d_project(name)

    -- Project Type
    mox_none()
end

function bl2d_lib(name)
    bl2d_project(name)

    -- Project Type
    mox_staticlib()

    -- Produce lib
    table.insert(BUILD_LIBS, name)
end

function bl2d_module(name)
    bl2d_project(name)

    -- Project Type
    mox_staticlib()

    -- Produce module
    table.insert(BUILD_MODULES, name)

    -- Generate module main files
    generate_module_h_or_cpp_ondemand(name, "h")
    generate_module_h_or_cpp_ondemand(name, "cpp")
end

function bl2d_console()
    mox_console()
end

function bl2d_windowed()
    mox_windowed()
end

function bl2d_application(name)
    bl2d_project(name)

    -- Project Type
    filter { "configurations:Debug*" }
        bl2d_console()
    filter {}
    filter { "configurations:not Debug*" }
        bl2d_windowed()
    filter {}

    -- Consume common and modules
    links(BUILD_LIBS)
    links(BUILD_MODULES)
    
    -- Generate a modules file
    generate_register_modules(BUILD_MODULES)
    generate_app_files(name)
end
