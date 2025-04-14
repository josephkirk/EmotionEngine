**1. Potential Types of Mental States**

These are longer-term, more persistent states compared to the often more volatile primary emotions. They represent underlying conditions influencing behavior and emotional response.

* **Sanity / Mental Stability:** Resistance to psychological stress, horror, cognitive dissonance. Low levels can lead to irrationality, hallucinations, paranoia, erratic behavior.
* **Morale / Resolve:** Confidence in succeeding, willingness to persist in goals or combat. Influenced by victories, losses, leadership, perceived odds. Low morale leads to fear, retreat, surrender, reduced effectiveness.
* **Focus / Concentration:** Ability to maintain attention on tasks, resist distractions. Affected by stress, fatigue, environment clarity, immediate threats. Low focus impairs complex actions (aiming, spellcasting, strategy).
* **Fatigue / Energy:** Physical and mental exhaustion level. Affected by exertion, lack of rest, injury, illness. Low energy reduces speed, power, reaction time, increases task failure rates.
* **Stress Level:** Accumulated physiological and psychological stress. Affected by danger, social pressure, uncertainty, pain, high cognitive load. High stress negatively impacts Focus, Sanity, Fatigue, and can amplify negative emotions.
* **Confidence / Self-Esteem:** The AI's belief in its own capabilities. Influenced by past performance, social feedback, known skills vs. challenges. Affects risk assessment, dialogue stance, initiative.
* **Alertness / Awareness:** How vigilant the AI is to its surroundings. Affected by perceived threat level, fatigue, time of day, environment. Influences detection capabilities.

**2. Relationship Between Emotion & Mental State Systems**

They have a crucial bidirectional relationship:

* **Emotions Affect Mental States (Often Gradually):**
    * **Chronic Negative Emotions Erode States:** Prolonged periods of high-intensity *Fear* or *Disgust* can decrease *Sanity*. Constant *Fear* or *Sadness* (due to losses) can lower *Morale*. High *Anger* or *Fear* can increase *Stress Level*. Intense emotional experiences can break *Focus*. This impact often accumulates over time.
    * **Positive Emotions Can Restore States:** Sustained periods of *Joy* (especially related to safety/success) or *Trust* (in allies/environment) might slowly restore *Morale*, reduce *Stress*, or even slightly bolster *Sanity* (feeling secure).
    * *Mechanism:* This might involve logic that runs periodically, checking the intensity and duration of key emotions and applying corresponding changes to Mental State variables.

* **Mental States Affect Emotional Responses (Modulation):**
    * **States Act as Filters/Amplifiers:** The AI's current Mental State influences how it reacts emotionally to new events.
    * *Examples:*
        * Low *Sanity* might cause unpredictable emotional reactions or amplify *Fear*.
        * Low *Morale* might increase susceptibility to *Fear* or *Sadness*.
        * High *Stress* might lower the threshold for *Anger* and amplify *Fear*.
        * Low *Focus* might lead to dampened or delayed emotional responses.
        * High *Fatigue* might increase irritability (*Anger*) or induce *Sadness*.
        * High *Confidence* might dampen *Fear* when facing challenges.
    * *Mechanism:* The `map_event_to_stimuli` logic (which translates game events into emotion deltas) should *read* the relevant Mental States and adjust the calculated `delta` values accordingly.

* **Game Events Can Affect Both Directly:**
    * A single event can have immediate impacts on both systems. *Example:* A terrifying monster appears -> Immediate `+Fear` (Emotion) and `-Sanity` (Mental State). *Example:* Winning a decisive battle -> Immediate `+Joy` (Emotion) and `+Morale` (Mental State).

**3. Architecture Design Exploration**

How do we structure the AI to accommodate both systems?

**Key Components:**

* `GameWorldInterface`: Provides information about game events, AI status, environment.
* `AIController/Brain`: Main coordinating component.
* `InputProcessor/Mapper`: Translates game events into system inputs (emotion deltas, state changes), potentially modified by current state.
* `EmotionSystem`: Manages base emotions, intensities, links, variations, opposites.
* `MentalStateSystem`: Manages persistent states like Sanity, Morale, Fatigue.
* `BehaviorModules`: (Action Selection, Dialogue Manager, Animation Controller, etc.) Read state information to determine AI actions.

**Architecture Options:**

**A. Layered / Separate Systems:**

```
+---------------------+      +-------------------------+
| GameWorldInterface  |----->|  AIController / Brain   |
+---------------------+      +-------+-----------+-----+
                                     |           |
                                     v           v
                          +--------------+   +--------------------+
                          | InputProcessor |-->| MentalStateSystem  |
                          |    / Mapper    |   |(Sanity, Morale...) |
                          +------+---------+   +--------+-----------+
                                 |                      |
                                 v                      v Output Read by Behavior
                          +----------------+            |
                          | EmotionSystem  |------------+
                          |(Joy, Fear...)  |
                          +----------------+

Interaction Logic resides primarily in AIController/InputProcessor:
1. Event -> InputProcessor -> Calculates initial Emotion deltas & direct Mental State changes.
2. InputProcessor -> Updates EmotionSystem & MentalStateSystem.
3. AIController periodically:
   - Reads EmotionSystem state -> Calculates gradual impact on Mental States -> Updates MentalStateSystem.
   - Reads MentalStateSystem state -> Updates parameters/rules within InputProcessor/Mapper for future event processing.
4. BehaviorModules read from both systems.
```

* **Pros:** Good separation of concerns, modular. Emotion dynamics and Mental State management are distinct.
* **Cons:** Cross-system influence logic (Emotions affecting States over time, States modifying emotional response) needs careful management, potentially in the `AIController` or `InputProcessor`, which could become complex.

**B. Integrated State Manager:**

```
+---------------------+      +--------------------------+
| GameWorldInterface  |----->|   AI State Manager       |
+---------------------+      |--------------------------|
                             | - InputProcessor/Mapper  |
                             | - Emotion Subsystem      |
                             | - Mental State Subsystem |
                             | - Cross-Influence Logic  |
                             +-------------+------------+
                                           |
                                           v Output Read by Behavior
                                     (Behavior Modules)

Interaction Logic is internal to the AIStateManager:
1. Event -> AIStateManager.
2. Internal Mapper calculates direct Emotion deltas & Mental State changes based on event AND current internal state (both emotions & mental states).
3. Internal update cycle applies changes, handles emotion links/opposites, AND applies cross-influences (e.g., high Fear drain on Sanity) within the same manager.
4. BehaviorModules query the unified AIStateManager.
```

* **Pros:** Tightly integrated, potentially simpler handling of direct cross-influences within a single update cycle.
* **Cons:** Less modular, can become a large, complex "god object". Harder to modify or replace individual subsystems (emotions vs. mental states).

**C. Blackboard Architecture:**

```
+---------------------+      +-----------------------+      +-------------------+
| GameWorldInterface  |----->| InputProcessor/Mapper |----->|     Blackboard    |
+---------------------+      +-----------------------+      |-------------------|
                                     ^                      | - Emotion States  |
                                     | Read Context         | - Mental States   |
                                     |                      | - Percepts        |
+----------------+               +---|----------------+     | - Goals           |
| EmotionSystem  |<--------------|   (Other Systems)  |----->| - ...             |
| (Reads/Writes BB)|------------>| (MentalStateSystem,|     +--------^----------+
+----------------+               | Behavior Modules...) |            | Read State
                                 +--------------------+            |
                                                                  (Behavior Modules)

Interaction Logic is distributed:
1. Event -> InputProcessor -> Writes initial stimuli/changes to Blackboard.
2. EmotionSystem: Reads stimuli & context from BB -> Calculates updates -> Writes Emotion state back to BB.
3. MentalStateSystem: Reads stimuli, context, *current emotions* from BB -> Calculates updates -> Writes Mental State back to BB.
4. Specialized "Influence Processors" (optional): Periodically read BB (e.g., Emotion duration) -> Calculate impacts (e.g., Sanity drain) -> Write back to BB.
5. BehaviorModules: Read all necessary state info from BB.
```

* **Pros:** Highly decoupled and modular. Systems only need to know about the Blackboard, not each other directly. Flexible and extensible.
* **Cons:** Data flow can be less obvious. Potential for "read-after-write" hazards if update order isn't managed. Can have performance overhead depending on implementation.

**Choosing an Architecture:**

* **Layered:** Good for clear separation if cross-system interactions aren't excessively complex.
* **Integrated:** Might be simpler if the interactions between emotions and mental states are very tight and happen rapidly within the same "tick".
* **Blackboard:** Often favored in complex AI for its flexibility and decoupling, allowing different teams or developers to work on separate systems interacting via the shared state.

The best choice depends on the complexity of your AI, the desired level of interaction between the systems, and your team's development practices. For a complex game AI, the **Blackboard** or a well-structured **Layered** approach are often strong contenders.