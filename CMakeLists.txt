# Make Menu Navigation System Library
# https://github.com/VladVanyuk/VirtLiquidCrystal
# MIT License

cmake_minimum_required(VERSION 3.5)

idf_component_register(SRCS "LiquidCrystal_Base.cpp" "LiquidCrystal.cpp" "LiquidCrystal_I2C.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES arduino)

project(LiquidCrystal_Base)