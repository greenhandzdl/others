#ifndef FREEGLUT_TEMPLATE_COMMON_H
#define FREEGLUT_TEMPLATE_COMMON_H

/**
 * @file common.h
 * @brief Common definitions and platform-specific configurations for FreeGLUT Template with GLEW
 *
 * This header handles the inclusion of GLUT/FreeGLUT and GLEW headers
 * in the correct order for different platforms.
 */

// Platform detection
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION

#ifdef USE_GLEW
// Include GLEW before GLUT on macOS
#include <GL/glew.h>
#endif

#ifdef USE_FREEGLUT
// Using FreeGLUT from Homebrew
#include <GL/freeglut.h>
#else
// Using macOS native GLUT framework
#include <GLUT/glut.h>
#endif
#else
// Linux and other platforms
#ifdef USE_GLEW
// Include GLEW BEFORE GLUT on Linux (GLEW must be included before gl.h)
#include <GL/glew.h>
#include <GL/freeglut.h>
#else
#include <GL/freeglut.h>
#endif
#endif

// Common macros and utilities
#define APP_NAME "FreeGLUT + GLEW Template"
#define APP_VERSION "1.0.0"

// Window defaults
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "FreeGLUT + GLEW Template Application"

#endif // FREEGLUT_TEMPLATE_COMMON_H
