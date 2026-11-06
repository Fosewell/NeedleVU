# NeedleVU

**A VU meter audio plugin.**

NeedleVU is an audio plugin project focused on providing a straightforward VU metering experience for audio production and engineering workflows.

This repository contains the source code and development files for NeedleVU.

## Project Status

Format, Platform, Status: 
 
 AU: macOS (Builds and loads)
 
 VST3: macOS (Builds and loads)
 
 VST3: Windows (Not yet built)
 
 AAX: Pro Tools (Not currently supported)

## Features

- VU meter display
- Audio plugin format support through JUCE
- AU and VST3 builds for macOS

*Additional features and specifications will be documented as development progresses.*

## Development Environment

- Framework: JUCE
- Language: C++
- IDE / Build environment: Xcode
- Current development platform: macOS


## Building

NeedleVU is currently developed and built on macOS.

To build the plugin:

1. Clone or download this repository.
2. Open the project using its configured JUCE build workflow.
3. Open the generated Xcode project, if applicable.
4. Select the desired plugin format and build configuration.
5. Build the AU and VST3 targets.
6. Test the resulting plugins in a compatible DAW.

*Detailed build instructions will be added as the development workflow is finalized.*

## Project Structure

The repository contains the source code, project configuration, and supporting files used to develop NeedleVU.

Key directories and files:
- `Source/` — Plugin source code, if using the standard JUCE layout.
- `Builds/` — Generated platform-specific project files, if included.
- `README.md` — Project documentation.

## Roadmap

- [x] Initial AU build for macOS
- [x] Initial VST3 build for macOS
- [ ] Expand macOS DAW compatibility testing
- [ ] Build and test Windows VST3
- [ ] Prepare beta distribution packages
- [ ] Collect peer feedback
- [ ] Refine plugin functionality and interface

## Beta Testing

Beta builds will be distributed separately through the NeedleVU-Beta repository.

Please report bugs, compatibility issues, and suggestions through the designated feedback channels.

## Licensing

NeedleVU is built using the JUCE framework.

Project licensing and distribution terms are to be documented before public distribution.

---

**NeedleVU — In Development**
