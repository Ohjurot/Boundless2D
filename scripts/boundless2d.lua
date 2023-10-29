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

-- Project template function

function bl2d_project(name)
    -- Basic setup
    mox_project(name)
    mox_cpp("C++20")
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
end

function bl2d_application(name)
    bl2d_project(name)

    -- Project Type
    filter { "configurations:Debug*" }
        mox_console()
    filter {}
    filter { "configurations:not Debug*" }
        mox_windowed()
    filter {}

    -- Consume common and modules
    links(BUILD_LIBS)
    links(BUILD_MODULES)
end
