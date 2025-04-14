# Valence-Arousal model for emotion representation.

![Valence Arousal Model](https://www.researchgate.net/publication/330861905/figure/fig1/AS:745108341268483@1554659080356/The-2D-valence-arousal-model-of-emotion-proposed-by-Russel-50.png)

**1. Emotional Valence Explained**

* **Definition:** Valence is the fundamental positive (pleasant) or negative (unpleasant) quality of an emotional experience. It's the core feeling of "goodness" or "badness" associated with an emotion.
* **Spectrum:** It's best understood as a continuous dimension ranging from highly positive (e.g., joy, ecstasy, bliss) through neutral, down to highly negative (e.g., fear, grief, agony).
* **Core Component:** It's one of the most basic ways we categorize feelings – Does it feel good or bad?
* **Limitation:** While fundamental, valence alone doesn't capture everything about an emotion. As discussed with the BAS/BIS paper, emotions with the same valence (e.g., Anger and Fear are both negative) can lead to very different motivations and actions (Approach vs. Withdrawal).

**2. The Valence-Arousal (V-A) Model**

This is a widely used "dimensional" model (contrasting with "categorical" models like Plutchik's wheel) primarily associated with James Russell. It proposes that most, if not all, emotional states can be described and plotted based on their position along two fundamental, independent dimensions:

1.  **Valence (V):** The horizontal axis, representing pleasantness.
    * Runs from Max Negative/Unpleasant (e.g., -1) on the left.
    * Through Neutral (0) in the center.
    * To Max Positive/Pleasant (e.g., +1) on the right.
2.  **Arousal (A):** The vertical axis, representing the level of physiological activation, energy, intensity, or mobilization associated with the emotion.
    * Runs from Min Arousal/Calm/Inactive (e.g., 0 or sometimes -1) at the bottom.
    * To Max Arousal/Excited/Activated (e.g., 1) at the top.

**Designing Emotions with Valence-Arousal (V-A) Coordinates:**


* **Representation:** Instead of (or in addition to) discrete emotion labels with a single 1-100 intensity, the AI's current emotional state could be represented as a point in this 2D space: `CurrentEmotionState = (Valence_Value, Arousal_Value)`.
    * *Example Ranges:* Valence: [-1.0, +1.0], Arousal: [0.0, 1.0]
* **Mapping Discrete Emotions:** Your named emotions correspond to regions or points in this space:
    * **High Arousal, Positive Valence (Top-Right):** Ecstasy (V: +0.9, A: 0.9), Excitement (V: +0.7, A: 0.8), Happy (V: +0.8, A: 0.7)
    * **Low Arousal, Positive Valence (Bottom-Right):** Content (V: +0.6, A: 0.3), Calm (V: +0.3, A: 0.1), Relaxed (V: +0.4, A: 0.2)
    * **Low Arousal, Negative Valence (Bottom-Left):** Sad (V: -0.6, A: 0.2), Bored (V: -0.3, A: 0.1), Depressed (V: -0.7, A: 0.1)
    * **High Arousal, Negative Valence (Top-Left):** Afraid (V: -0.8, A: 0.9), Angry (V: -0.7, A: 0.8), Stressed (V: -0.5, A: 0.7), Tense (V: -0.4, A: 0.8)
* **Intensity -> Arousal:** Your previous 1-100 intensity scale primarily maps to the **Arousal** dimension. Higher intensity means higher arousal. The valence might become more extreme too, but arousal is the key correlate.
* **Variations:** Variations of a base emotion (like contentment vs happiness vs ecstasy) represent different points within the same general quadrant, usually varying more significantly on the Arousal axis, but potentially also Valence.

**What Does This Mean for AI Design? (Implications):**

1.  **Continuous State:** Represents emotions as a continuous space rather than discrete buckets. This allows for:
    * **Smoother Transitions:** The AI's emotional state point (V, A) can move gradually, reflecting subtle shifts in mood.
    * **Blended Emotions:** The point might fall *between* typical emotion categories, representing mixed feelings.
    * **Nuance:** Captures states like "calmly happy" (low A, pos V) vs. "excitedly happy" (high A, pos V).
2.  **Link to Behavior:**
    * **Arousal -> Activity Level:** High arousal naturally maps to higher energy behaviors (faster movement, louder voice, more frequent actions). Low arousal maps to passivity, slowness, quietness.
    * **Valence -> Basic Motivation:** Positive valence tends to promote engagement, exploration, and approach. Negative valence tends to promote avoidance, withdrawal, or cessation of activity. *(Caveat: Still has the Anger problem - see limitations)*.
3.  **Input Mapping:** Game events can be designed to push the AI's V-A point in specific directions.
    * Sudden threat: Large negative shift in V, large positive shift in A.
    * Achieving a minor goal: Small positive shift in V, small positive shift in A.
    * Relaxing in a safe place: Shift towards positive V, shift towards low A.
4.  **Integration with Other Systems:**
    * **Physiology:** Arousal has strong links. High `Adrenaline` pushes Arousal up. Low `Stamina`/`Condition` pulls Arousal down. `Pain` pulls Valence down and Arousal up.
    * **Mental State:** High `Stress` might increase baseline Arousal or make the point more volatile. `Fatigue` pulls Arousal down. `Morale` correlates with Valence.
    * **Personality:** Neuroticism could expand the range towards negative Valence and high Arousal. Extraversion could expand towards positive Valence.
5.  **Limitations:**
    * **Action Tendency Ambiguity:** The V-A model alone doesn't distinguish between emotions with similar V-A profiles but different action tendencies (e.g., Anger vs. Fear). You likely still need a mechanism (like the BAS/BIS approach or explicit action tendency mapping) layered on top to drive behavior correctly.
    * **Specificity:** While good for general mood and activation, it doesn't capture the specific cognitive appraisals or nuances that differentiate emotions like Guilt vs. Sadness (both low A, negative V) without additional context or labels.

u
## Redesigned Emotion System using V-A Coordinates

### **Core Representation:**

The primary emotional state of an AI is no longer a set of discrete emotion intensities, but a single coordinate pair: CurrentEmotionalState = (Valence, Arousal).
Valence (V): Ranges from -1.0 (Highly Unpleasant) to +1.0 (Highly Pleasant).
Arousal (A): Ranges from 0.0 (Completely Calm/Inactive) to 1.0 (Highly Activated/Energized).
Emotion Labels: Discrete labels ("Happy," "Angry," "Sad," "Calm") now correspond to regions within the V-A space. A function get_dominant_emotion_label(V, A) can map the current coordinates to the closest descriptive label when needed (e.g., for logging, specific behavior checks, or dialogue hints).
System Dynamics:

Input Processing: Game events, physiological changes, mental state shifts, etc., are processed by the InputProcessor/Mapper. This mapper calculates delta_Valence and delta_Arousal based on the stimulus, context, AI personality (OCEAN/BAS/BIS), and current state.
State Update: The core update becomes vector addition (with clamping): NewV = Clamp(CurrentV + delta_V, -1.0, 1.0) NewA = Clamp(CurrentA + delta_A, 0.0, 1.0)
Homeostasis/Decay: The (V, A) point naturally decays towards a baseline state over time (e.g., V=0, A=0.1 - slightly alert neutral). Decay rates can be influenced by personality (e.g., Neuroticism slows decay from negative valence) or mental states (e.g., high Stress maintains higher baseline Arousal).
Interaction:
Output: The current (V, A) state directly influences:
Behavioral Energy: Arousal level dictates animation speed, vocal volume, action frequency/intensity.
General Mood/Approach: Valence biases towards approach/engagement (positive V) or avoidance/withdrawal (negative V). Influences facial expression pleasantness, dialogue tone.
Input: V-A state influences other systems (e.g., sustained negative V drains 'Morale'; high A increases 'Stress'). It also provides context for the InputProcessor when evaluating new events.
What it Means for Game Design? (Implications)

Organic Mood Shifts: NPCs feel more psychologically continuous. Their mood can drift subtly based on minor events or internal states, rather than abruptly switching between discrete emotions.
Subtle Expressions: Allows for representing states like "calmly content," "agitatedly unhappy," "tired and grumpy," etc., based on the V-A position.
Direct Link to Animation/Voice: Arousal provides a natural parameter for controlling the energy of animations and voice modulation. Valence controls the positive/negative aspect of expressions.
Emergent Behavior: Complex emotional arcs can emerge from the interplay of V-A dynamics, decay, and interaction with other systems (Physiology, Mental State, Goals).
Pros and Cons

**Pros:**

Smooth Transitions: More naturalistic and less "robotic" mood changes.
Nuance & Blending: Can represent intermediate or mixed feelings without needing countless discrete labels.
Dimensional Control: Provides direct control over the two most fundamental aspects of emotion (pleasantness and energy).
Efficiency: Core state is just two numbers; updates can be computationally simple.
**Cons:**

Behavioral Ambiguity (The Anger Problem): Valence alone doesn't determine approach/avoidance. Anger (neg V, high A) and Fear (neg V, high A) occupy similar V-A space but demand opposite actions. Requires an additional layer for Action Tendency.
Loss of Categorical Specificity: Cannot easily distinguish between emotions like Sadness vs. Guilt vs. Boredom based only on V-A coordinates, as they cluster in the low A / negative V quadrant. Specific behaviors or dialogue tied to these distinct feelings become harder to trigger directly from V-A alone.
Interpretation Layer Needed: Requires functions to map V-A coordinates back to understandable labels or behavioral modes for decision-making systems (Behavior Trees, Planners) or player feedback.
Tuning: Balancing the V & A deltas from various events and the decay rates to achieve believable, stable-yet-responsive behavior requires careful tuning.
Addressing Simplicity: "Spread Spectrum" of Emotions

### **Richer design of emotion**
A single (V, A) point can indeed feel too simplistic, representing only the dominant feeling. To model a richer "spread" or internal conflict:

V-A State + Explicit Action Tendency (Recommended):

Design: Keep the single (V, A) point for the core feeling (pleasantness/arousal). Add a separate state variable: CurrentActionTendency (e.g., APPROACH, WITHDRAW, ATTACK, FREEZE, ENGAGE, DISENGAGE).
How it Works: The InputProcessor (using event data, V-A state, context, personality/BAS/BIS, goals) determines the appropriate ActionTendency. For example, a threat event moves V-A to high-A/negative-V. If BAS > BIS, tendency might be ATTACK; if BIS > BAS, tendency might be FLEE.
Benefit: Directly solves the main behavioral ambiguity of the V-A model while keeping the core feeling representation simple.
Primary V-A State + Secondary "Echoes":

Design: Maintain the primary (V, A) point. Add a small list (1-3) of secondary V-A vectors representing recent strong emotions or conflicting feelings, each with a lower intensity/influence and faster decay.
How it Works: If the AI is primarily Happy (high V, mid A) but just had a brief scare, a secondary Fear "echo" (neg V, high A, low influence) might persist for a short time.
Benefit: Models lingering feelings or internal conflict. Useful for driving subtle "leakage" in expression (e.g., primary Happy expression, but secondary Fear echo causes slightly tense body language).
Multiple Active Emotion Sources:

Design: Instead of one net V-A point, track several active "emotion sources," each with its own target V-A coordinate, current intensity, and decay. The AI's felt state could be the vector sum or a weighted average, while behavior might be influenced by the strongest or most motivationally relevant source.
Benefit: More directly models situations with genuinely conflicting simultaneous stimuli (e.g., bittersweet moments).
Cost: Significantly increases complexity in tracking and blending these sources.
Probability Distribution over V-A Space:

Design: Represent the state as a probability density function (e.g., a 2D Gaussian) over the V-A space. The peak is the most likely state, the spread (variance) represents uncertainty or blended feelings.
Benefit: Mathematically represents ambiguity and mixed states.
Cost: Computationally intensive and complex to interpret for direct action/expression.
Conclusion for Redesign:

Using a V-A coordinate system as the core provides a fluid, dimensional representation of emotion, excellent for modeling mood intensity and pleasantness.

**Recommendation:** For a practical and effective system, combine the V-A coordinate (Proposal #1) with an explicit ActionTendency state (Proposal #4). This leverages the strengths of V-A for representing the feeling (Valence, Arousal) while directly addressing its main weakness by adding a separate mechanism for the behavioral urge. You can further add richness using "Secondary Echoes" (Proposal #3) to handle expression leakage and lingering feelings if needed. This layered approach offers a good balance between nuanced representation and implementable complexity.

Okay, this is a very interesting and practical interpretation! Let's break down this design where "Intensity" is a property of an external *stimulus* that *pulls* the AI's V-A state.

## **Redesigned Concept:**

1.  **Core AI State:** Remains the 2D coordinate `CurrentEmotionalState = (Valence, Arousal)`. No third axis is needed for the state itself.
2.  **External Stimuli:** Events (dialogue, object interaction, combat hit, environment change) generate temporary "Emotional Stimuli" or "Influence Vectors."
3.  **Stimulus Properties:** Each active stimulus has:
    * **Target Emotion V-A:** The prototypical `(targetV, targetA)` coordinates of the emotion the stimulus is trying to evoke (e.g., an insult targets the 'Anger' coordinates; a compliment targets the 'Happy' coordinates).
    * **Intensity:** A value (`currentIntensity`) representing the stimulus's current strength or influence magnitude. This value starts at an `initialIntensity` determined by the event's significance and then *decays over time*.
    * **Decay Rate:** How quickly the `currentIntensity` fades.
4.  **Mechanism ("Pulling"):** The AI's `CurrentEmotionalState(V, A)` is constantly influenced by two main forces:
    * **Baseline Regulation:** A persistent pull back towards a neutral baseline state (e.g., V=0, A=0.1). This represents homeostasis or mood decay.
    * **Active Stimuli:** Each active stimulus exerts a pull *from* the `CurrentEmotionalState` *towards* the stimulus's `targetV, targetA`. The strength of this pull is proportional to the stimulus's `currentIntensity`.
5.  **State Update:** In each update cycle, the AI's V-A coordinates move based on the *vector sum* of the baseline regulation pull and all active stimulus pulls.

**Detailed Dynamics:**

* **Event Occurs:** `Event(Type='Insult', Significance=High)`
* **Input Mapping:** `InputProcessor` determines:
    * Target Emotion Node: Anger (`targetV=-0.7, targetA=0.8`)
    * Initial Intensity: High (`initialIntensity=80`)
    * Decay Rate: Moderate (`decayRate=0.5` intensity units per second)
* **Stimulus Created:** A new `EmotionalStimulus` object is added to a list of active stimuli for this AI.
* **Update Loop (each tick):**
    1.  Calculate `Vector_Decay`: Points from `Current(V, A)` towards `Baseline(V, A)`. Magnitude might depend on distance from baseline.
    2.  `Net_Stimulus_Pull = (0, 0)`
    3.  For each `stimulus` in `active_stimuli`:
        * `Vector_To_Target = (stimulus.targetV - CurrentV, stimulus.targetA - CurrentA)`
        * `Pull_Strength = stimulus.currentIntensity * ScalingFactor`
        * `Stimulus_Pull_Vector = normalize(Vector_To_Target) * Pull_Strength`
        * `Net_Stimulus_Pull += Stimulus_Pull_Vector`
        * `stimulus.currentIntensity -= stimulus.decayRate * DeltaTime`
        * If `stimulus.currentIntensity <= 0`, remove it from `active_stimuli`.
    4.  `Total_Delta_Vector = Vector_Decay + Net_Stimulus_Pull`
    5.  `NewV = Clamp(CurrentV + Total_Delta_Vector.V * DeltaTime, -1, 1)`
    6.  `NewA = Clamp(CurrentA + Total_Delta_Vector.A * DeltaTime, 0, 1)`
    7.  `Current(V, A) = (NewV, NewA)`

**What This Means / Implications:**

* **Intensity Belongs to the Event:** "Intensity" is clearly defined as the strength and persistence of an *external influence*, not an intrinsic dimension of the AI's feeling itself (Arousal covers the internal activation aspect).
* **Natural Blending:** Multiple simultaneous or overlapping events contribute their pulls concurrently. The AI's state moves based on the weighted vector sum, creating very natural blending and transitions. A calming influence can counteract an agitating one.
* **Transient Effects:** Emotions triggered by events feel transient. They pull the state, but as their intensity decays, the baseline regulation takes over, pulling the state back towards neutral unless other stimuli are introduced.
* **No Need for 3D State:** The core AI state remains elegantly 2D (V-A).
* **Rich Dynamics:** Complex emotional trajectories can emerge from the interplay of multiple pulls with different intensities, targets, and decay rates, plus the baseline pull.

**Pros and Cons of this Specific Model:**

* **Pros:**
    * **Intuitive Input Model:** Directly models events "pushing" or "pulling" the AI's mood.
    * **Elegant Blending:** Handles multiple influences naturally via vector addition.
    * **Smooth Decay:** Stimulus intensity decay provides organic fading of emotional responses.
    * **Keeps Core State Simple:** Avoids adding a potentially ambiguous third dimension to the AI's state.
    * **Clear Role for "Intensity":** Defines it unambiguously as a stimulus property.

* **Cons:**
    * **Implementation Overhead:** Requires managing a list of active stimuli per AI, updating their decay, and calculating vector sums each tick.
    * **Tuning Complexity:** Requires careful tuning of `initialIntensity` and `decayRate` for *every type* of emotional event, plus the `ScalingFactor` and the strength of the baseline decay. Getting the "feel" right takes effort.
    * **Action Tendency Still Separate:** Like the basic V-A model, this doesn't inherently solve the Anger vs. Fear action tendency problem. You still need a separate layer that determines the `ActionTendency` based on the *type* of stimulus causing the pull, the resulting V-A state, context, goals, etc.

**Conclusion:**

This is a very strong and elegant way to handle external emotional stimuli within a Valence-Arousal framework. By defining "Intensity" as a decaying property of the *stimulus* rather than a dimension of the AI's *state*, you create a system where events exert a transient, intensity-weighted "pull" on the AI's core V-A mood coordinate. This allows for natural blending, smooth transitions, and complex dynamics while keeping the AI's fundamental emotional state representation simple (2D). It's a compelling alternative to adding a third state axis and provides a clear mechanism for how external factors influence the AI's mood trajectory. Remember to complement it with an Action Tendency layer for robust behavioral output.