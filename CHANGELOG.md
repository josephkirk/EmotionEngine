# Emotion Engine Changelog

## [1.0.1] - 2025-04-18

### Optimized
- Reduced redundancy and simplified code across EmotionState, EmotionComponent, and EmotionSystemLibrary classes
- Added a private helper method in EmotionSystemLibrary to reduce redundant code for getting the default emotion library
- Simplified null checks in EmotionComponent methods using ternary operators
- Implemented proper fallback to default emotion library in InitializeEmotionState
- Use FPolarCoordinate instead of custom FVACoordinate.

### Improved
- Clarified component responsibilities:
  - EmotionState: Manages the internal state of emotions
  - EmotionComponent: Handles actor integration and external influences
  - EmotionSystemLibrary: Provides utility functions for blueprints
- Optimized AreEmotionsAdjacent to use GetEmotionDistance to avoid code duplication
- Improved code readability and maintainability

## [1.0.0] - Initial Release

### Added
- Core emotion system based on Valence-Arousal model
- EmotionComponent for attaching to actors
- EmotionState for managing emotional state
- EmotionSystemLibrary for blueprint utility functions
- Support for emotion combinations and interactions
- Emotion influence system with spring-based physics
- Polar coordinate system for emotion representation
- Emotion zones for environmental influence
- Emotion library asset for managing emotion definitions
- Editor support for creating and managing emotion assets
