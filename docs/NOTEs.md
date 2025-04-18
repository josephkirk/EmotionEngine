# AI emotion system that is data driven.

## Design
- An EmotionComponent with current Valence-Arousal 2D coordinate (VACoordinate) and a radius. An array holding active emotions.
- An Emotion have intensity from 1 to 100, a decay rate, an influence radius and a VACoordinate. Intensity degrade over time with decay rate.
- An external stimulus ( dialogue , event, object ...) can trigger an emotion with intensity and add it to EmotionComponent make it active.
- An emotion can be a combination of 2 or more emotions  ( reference pluchik's wheel of emotion), this emotion can only be triggered if the required emotions are active.
- An emotion have sub emotion tag that activated when the intensity of the emotion reach a threshold.
- An emotion can link with another emotion's intensity with a mapping of how threhold of both intensities can trigger and new emotion tags. 
- An active emotion with intensity not zero pull the EmotionComponent's Current mood ( present as a  set of 2 coordinates) toward it with pull strength that stronger the further away the target V-A using linear spring model. One coordinate is in core emotion space and the other is in combined emotion space.

- A core emotion space is a polar coordinate system with partitioned segments limit by angle and radius range that define the space of emotions called emotion zones.
![](images/VA_Intensity.png)

- A combined emotion space is a cartesian coordinate system with voronoi cells with each cell representing a unique combination of emotions.
![](images/VA_Combination.png)

- A dormant emotion is an emotion that is not active but can be triggered by a stimulus or gameplay tag event.