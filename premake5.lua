workspace "Eero"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Eero"
include "Sandbox"