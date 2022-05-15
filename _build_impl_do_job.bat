@set GENERATOR_NAME=%1
@set GENERATOR_ARCH=%2
@set TARGET_TOOLSET=%3
@set TARGET_PLATFORM=%4
@set TARGET_CONFIG=%5
@set FINAL_TARGET_ROOT=%PROJECT_TARGET_ROOT%/%TARGET_TOOLSET%/%TARGET_PLATFORM%/%TARGET_CONFIG%
@set FINAL_TARGET_ROOT_DOS_COMPAT=FINAL_TARGET_ROOT
@call :CHANGE_SLASH FINAL_TARGET_ROOT_DOS_COMPAT

@echo ------------------------
@echo Building %PROJECT_NAME% (%TARGET_TOOLSET%/%TARGET_PLATFORM%/%TARGET_CONFIG%) to %FINAL_TARGET_ROOT%
@echo Generator              : %GENERATOR_NAME%
@echo Generator Target Arch  : %GENERATOR_ARCH%
@echo Target Toolset         : %TARGET_TOOLSET%
@echo Target Arch Name       : %TARGET_PLATFORM%
@echo Target Config          : %TARGET_CONFIG%

@set CMAKE_GENERATE_INVOKE_ARGS_BASE=-G %GENERATOR_NAME% -A %GENERATOR_ARCH% -DCMAKE_INSTALL_PREFIX=%FINAL_TARGET_ROOT%
@echo CMAKE Base invoke args=%CMAKE_GENERATE_INVOKE_ARGS_BASE%

@set CMAKE_ARG_CONFIG_TYPE=-DCMAKE_BUILD_TYPE=%TARGET_CONFIG% -DCMAKE_CONFIGURATION_TYPE=%TARGET_CONFIG%

@rem if (JINJA2CPP_BUILD_SHARED)
@rem     set(JINJA2CPP_PIC ON)
@rem     set(JINJA2CPP_MSVC_RUNTIME_TYPE "/MD")
@rem endif ()
@rem CMAKE_CONFIGURATION_TYPE
@rem JINJA2CPP_BUILD_SHARED
@rem BUILD_SHARED_LIBS
@rem   - cmake .. -G %GENERATOR% -DCMAKE_BUILD_TYPE=%configuration% -DJINJA2CPP_MSVC_RUNTIME_TYPE=%MSVC_RUNTIME_TYPE% -DJINJA2CPP_DEPS_MODE=%DEPS_MODE% %EXTRA_CMAKE_ARGS%
@rem   - cmake --build . --target all --config %configuration%


@set SANITIZERS_CFG=
@if "%TARGET_CONFIG%"=="Debug" goto SANITIZERS_DEBUG_CFG
:SANITIZERS_RELEASE_CFG
@rem set SANITIZERS_CFG=-DJINJA2CPP_WITH_SANITIZERS=address+undefined
:SANITIZERS_DEBUG_CFG

@set CXX17=-DJINJA2CPP_CXX_STANDARD=17


@rem set GENERATE_ONLY=0

@if exist .build rd /S /Q .build
@mkdir .build

@cd .build

@rem address+undefined|memory
@echo --- Invoking CMake Generation 
@cmake .. %CMAKE_GENERATE_INVOKE_ARGS_BASE% %CMAKE_ARG_CONFIG_TYPE% -DJINJA2CPP_DEPS_MODE=internal %SANITIZERS_CFG% %CXX17%
@if "%GENERATE_ONLY%"=="1" goto BUILD_SKIPPED
@echo --- Invoking CMake Build 
@cmake --build . %HOST% %CMAKE_ARG_CONFIG_TYPE% --target install --config %TARGET_CONFIG% %SANITIZERS_CFG% %CXX17%
:BUILD_SKIPPED
@cd ..

@rem Post-clean, rem this if your want to see build generated files
@if "%GENERATE_ONLY%"=="1" goto CLEAN_BUILD_SKIPPED
@if "%KEEP_BUILD_DIR%"=="1" goto CLEAN_BUILD_SKIPPED
@if exist .build rd /S /Q .build
:CLEAN_BUILD_SKIPPED

@exit /B



@rem https://www.robvanderwoude.com/battech_convertcase.php
:CHANGE_SLASH
@SET %~1=!%~1:/=\!
@exit /b
