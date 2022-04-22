@set DEF_TARGET_ROOT=C:
@set DEF_PROJECT_NAME=Project

@call _build_impl_setup_target_root.bat %1 %2

@rem set HOST=-T host=x64
@set HOST=

@set PROJECT_TARGET_ROOT_DOS_COMPAT=PROJECT_TARGET_ROOT
@call :CHANGE_SLASH PROJECT_TARGET_ROOT_DOS_COMPAT_DOS_COMPAT
@if exist %PROJECT_TARGET_ROOT_DOS_COMPAT% rd /S /Q %PROJECT_TARGET_ROOT_DOS_COMPAT%


@rem Config - RelWithDebInfo
@rem Config - MinSizeRel

@call _build_impl_do_job.bat "Visual Studio 15 2017" Win32 msvc2017 x86 Debug
@call _build_impl_do_job.bat "Visual Studio 15 2017" Win32 msvc2017 x86 Release
@call _build_impl_do_job.bat "Visual Studio 15 2017" x64   msvc2017 x64 Debug
@call _build_impl_do_job.bat "Visual Studio 15 2017" x64   msvc2017 x64 Release

@call _build_impl_do_job.bat "Visual Studio 16 2019" Win32 msvc2019 x86 Debug
@call _build_impl_do_job.bat "Visual Studio 16 2019" Win32 msvc2019 x86 Release
@call _build_impl_do_job.bat "Visual Studio 16 2019" x64   msvc2019 x64 Debug
@call _build_impl_do_job.bat "Visual Studio 16 2019" x64   msvc2019 x64 Release

@exit /B


@rem https://www.robvanderwoude.com/battech_convertcase.php
:CHANGE_SLASH
@SET %~1=!%~1:/=\!
@exit /b


